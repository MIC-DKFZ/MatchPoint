// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
// Subversion HeadURL: $HeadURL$
*/


#ifndef __ITK_LANDMARK_KERNEL_REGISTRATION_ALGORITHM_TPP
#define __ITK_LANDMARK_KERNEL_REGISTRATION_ALGORITHM_TPP

#include "mapAlgorithmException.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"

#include "itkKernelTransform.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::FieldRepRequirement::Type
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			isMovingRepresentationRequired() const
			{
				if (this->m_GenerateField)
				{
					return FieldRepRequirement::Yes;
				}
				else
				{
					return FieldRepRequirement::No;
				}
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::FieldRepRequirement::Type
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			isTargetRepresentationRequired() const
			{
				return FieldRepRequirement::Yes;
			};


			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			ITKLandmarkKernelRegistrationAlgorithm()
			{
				m_Stiffness = 0.01;
				m_GenerateField = false;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			~ITKLandmarkKernelRegistrationAlgorithm()
			{
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::AlgorithmType
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			getAlgorithmType() const
			{
				return Superclass::ATAnalytic;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			bool
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			isReusable() const
			{
				return true;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			void
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			configureAlgorithm()
			{
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			bool
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			doDetermineRegistration()
			{
				bool resultAvailable = true;

				this->InvokeEvent(::map::events::InitializingAlgorithmEvent());

				if (!this->getMovingPointSet())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving point set.");
				}

				if (!this->getTargetPointSet())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target point set.");
				}

				this->_spFinalizedRegistration = NULL;

				//create method
				this->_spTransform = TransformModelType::New();

				//assemble registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing kernel trasform."));

				this->InvokeEvent(::map::events::StartingAlgorithmEvent());

				_spTransform->SetStiffness(this->m_Stiffness);

				typedef typename TITKTransform::PointSetPointer InternalPointSetPointer;

				InternalPointSetPointer internalTargetPS;
				InternalPointSetPointer internalMovingPS;
				convertPointSetToKernelPointSet(this->getTargetPointSet(), internalTargetPS);
				convertPointSetToKernelPointSet(this->getMovingPointSet(), internalMovingPS);

				_spTransform->SetTargetLandmarks(internalTargetPS);
				_spTransform->SetSourceLandmarks(internalMovingPS);

				_spTransform->UpdateParameters();

				this->InvokeEvent(::map::events::StoppedAlgorithmEvent());

				this->finalizeAlgorithm();

				this->InvokeEvent(::map::events::FinalizedAlgorithmEvent());

				return resultAvailable;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			void
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			finalizeAlgorithm()
			{
				RegistrationPointer spResult;

				if (!_spTransform)
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine final registration. No transform model present on internal level (getTransformInternal()). Please ensure proper setup of algorithm.");
				}

				//clone the transform model
				typename TransformModelType::Pointer spFinalTransformModel = _spTransform->Clone();

				if (spFinalTransformModel.IsNull())
				{
					std::ostringstream modelStrm;
					_spTransform->Print(modelStrm);
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine final registration. Unable to clone transform model. Current model: " << modelStrm.str());
				}


				//now build the inverse kernel (main kernel of a closed form based registration algorithm using itk::LandmarkInitializer)
				typedef core::PreCachedRegistrationKernel<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>
				InverseKernelType;

				typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
				spIKernel->setTransformModel(spFinalTransformModel);

				typedef core::NullRegistrationKernel<RegistrationType::MovingDimensions, RegistrationType::TargetDimensions>
				DirectKernelType;
				typename DirectKernelType::Pointer spDKernel = DirectKernelType::New();

				//now create the registration an set the kernels
				spResult = RegistrationType::New();
				::map::core::RegistrationManipulator<RegistrationType> manipulator(spResult);

				manipulator.setDirectMapping(spDKernel);
				manipulator.setInverseMapping(spIKernel);
				manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				_spFinalizedRegistration = spResult;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::RegistrationPointer
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			bool
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			registrationIsOutdated() const
			{
				bool outdated = _spFinalizedRegistration.IsNull();

				if (_spFinalizedRegistration.IsNotNull())
				{
					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = _spFinalizedRegistration->GetMTime() < this->getMovingPointSetMTime();
					}

					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = _spFinalizedRegistration->GetMTime() != this->getTargetPointSetMTime();
					}
				}

				return outdated;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			void
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				PointSetRegistrationAlgorithmBase<TPointSet, TPointSet>::PrintSelf(os, indent);

				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};

			template<class TPointSet, class TITKTransform, class TIdentificationPolicy>
			void
			ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>::
			convertPointSetToKernelPointSet(const TPointSet* ps,
											typename TITKTransform::PointSetPointer& kernelPS)
			{
				kernelPS = TITKTransform::PointSetType::New();
				typename TITKTransform::PointSetType::PointsContainer* pPoints = kernelPS->GetPoints();

				pPoints->insert(pPoints->begin(), ps->GetPoints()->begin(), ps->GetPoints()->end());
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
