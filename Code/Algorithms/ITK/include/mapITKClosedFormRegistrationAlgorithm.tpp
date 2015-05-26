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


#ifndef __ITK_CLOSED_FORM_REGISTRATION_ALGORITHM_TPP
#define __ITK_CLOSED_FORM_REGISTRATION_ALGORITHM_TPP

#include "mapAlgorithmException.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			bool
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			isReusable() const
			{
				return true;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::FieldRepRequirement::Type
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			isMovingRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::FieldRepRequirement::Type
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			isTargetRepresentationRequired() const
			{
				typename TransformModelType::InverseTransformBasePointer spInverseModel = this->_spTransform->GetInverseTransform();

				if (spInverseModel.IsNotNull())
				{
					// you can invert it thus no rep is needed
					return FieldRepRequirement::No;
				}
				else
				{
					return FieldRepRequirement::Unkown;
				}
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			ITKClosedFormRegistrationAlgorithm()
			{
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			~ITKClosedFormRegistrationAlgorithm()
			{
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::AlgorithmType
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			getAlgorithmType() const
			{
				return Superclass::ATAnalytic;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			void
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			configureAlgorithm()
			{
				//default implementation does nothing.
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			bool
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			doDetermineRegistration()
			{
				bool resultAvailable = true;

				this->InvokeEvent(events::InitializingAlgorithmEvent());

				if (!this->getMovingPointSet())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving point set.");
				}

				if (!this->getTargetPointSet())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target point set.");
				}

				//create method
				this->_internalSolver = InternalSolverMethodType::New();
				this->_spTransform = TransformModelType::New();

				//assemble registration components
				this->InvokeEvent(events::AlgorithmEvent(this, "Initializing solver."));

				this->_internalSolver->SetTransform(_spTransform);

				//Connect point sets
				this->InvokeEvent(events::AlgorithmEvent(this, "Connect point sets to itk registration method."));

				typename InternalSolverMethodType::LandmarkPointContainer mLm;
				typename InternalSolverMethodType::LandmarkPointContainer tLm;
				convertPointSetToLandmarks(this->getMovingPointSet().GetPointer(), mLm);
				convertPointSetToLandmarks(this->getTargetPointSet().GetPointer(), tLm);
				this->_internalSolver->SetFixedLandmarks(tLm);
				this->_internalSolver->SetMovingLandmarks(mLm);

				this->InvokeEvent(events::StartingAlgorithmEvent());

				this->_internalSolver->InitializeTransform();

				this->InvokeEvent(events::StoppedAlgorithmEvent());

				this->finalizeAlgorithm();

				this->InvokeEvent(events::FinalizedAlgorithmEvent());

				return resultAvailable;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			void
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			finalizeAlgorithm()
			{
				RegistrationPointer spResult = NULL;

				if (!_spTransform)
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine final registration. No transform model present on internal level (getTransformInternal()). Please ensure proper setup of algorithm.");
				}

				//clone the transform model
				typename TransformModelType::Pointer spFinalTransformModel =	dynamic_cast<TransformModelType*>(_spTransform->Clone().GetPointer());

				if (spFinalTransformModel.IsNull())
				{
					std::ostringstream modelStrm;
					_spTransform->Print(modelStrm);
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine final registration. Unable to clone transform model. Current model: " <<modelStrm.str());
				}


				//now build the inverse kernel (main kernel of a closed form based registration algorithm using itk::LandmarkInitializer)
				typedef core::ModelBasedRegistrationKernel<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>
				InverseKernelType;

				typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
				spIKernel->setTransformModel(spFinalTransformModel);

				//now build the direct kernel via inversion of the inverse kernel
				typedef core::InverseRegistrationKernelGenerator<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>
				GeneratorType;
				typename GeneratorType::Pointer spGenerator = GeneratorType::New();
				typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;
				typename DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*
						(spIKernel.GetPointer()), this->getMovingRepresentation());

				if (spDKernel.IsNull())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine direct mapping kernel of final registration. Current inverse kernel: "
									  << spIKernel);
				}

				//now create the registration an set the kernels
				spResult = RegistrationType::New();
				core::RegistrationManipulator<RegistrationType> manipulator(spResult);

				manipulator.setDirectMapping(spDKernel);
				manipulator.setInverseMapping(spIKernel);
				manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				_spFinalizedRegistration = spResult;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			typename ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::RegistrationPointer
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			bool
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
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
						outdated = _spFinalizedRegistration->GetMTime() < this->getTargetPointSetMTime();
					}
				}

				return outdated;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TITKTransform, class TIdentificationPolicy>
			void
			ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::PrintSelf(os, indent);

				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};


		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
