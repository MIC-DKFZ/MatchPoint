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

#ifndef __MAP_IMAGE_REGISTRATION_ALGORITHM_TPP
#define __MAP_IMAGE_REGISTRATION_ALGORITHM_TPP

#include "mapAlgorithmException.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"

#include "mapITKMVNLOptimizerControlInterface.h"
#include "mapITKSVNLOptimizerControlInterface.h"
#include "itkMutexLockHolder.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			isStoppable() const
			{
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::IterationCountType
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetCurrentIteration() const
			{
				return this->_currentIterationCount;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::IterationCountType
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetMaxIterations() const
			{
				return this->_internalRegistrationMethod->GetNumberOfIterations();
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasIterationCount() const
			{
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasMaxIterationCount() const
			{
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			hasCurrentOptimizerValue() const
			{
				//TODO
				return false;
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			ITKDemonsRegistrationAlgorithm()
			{
				_currentIterationCount = 0;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			~ITKDemonsRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::InterimRegistrationPointer
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			determineInterimRegistration(const MovingRepresentationDescriptorType* pMovingRepresentation,
										 const TargetRepresentationDescriptorType* pTargetRepresentation) const
			{
				//TODO

				//InterimRegistrationPointer spResult = NULL;

				//if (this->_currentIterationCount>0)
				//{ //the algorithm has iterated at least once so we can determin an interim registration
				//  const TransformBaseType* pTransformModel = this->getTransformInternal();
				//  if (!pTransformModel)
				//  {
				//    mapExceptionMacro(AlgorithmException, <<"Error. Cannot determine interim registration. No transform model present on internal level (getTransformInternal(). Pleas ensure proper setup of algorithm.");
				//  }

				//  //clone the transform model
				//  TransformBaseType::Pointer spInterimTransformModel = pTransformModel->clone();

				//  if (spInterimTransformModel.IsNull())
				//  {
				//    mapExceptionMacro(AlgorithmException, <<"Error. Cannot determine interim registration. Unable to clone transform model. Current model: "<<*pTransformModel);
				//  }

				//  //set the parameter of the interim transform model to the current transform parameters of the algorithm
				//  //We set the parameter by Value and not by using SetParameter() because otherwise
				//  //it could cause errors with itk transforms that only keep a pointer to their parameters (e.g. itk::BSplineDeformableTransform).
				//  //This transforms would be invalid as soon as we leave this method.
				//  spInterimTransformModel->SetParametersByValue(this->getCurrentTransformParameters());

				//  //now build the inverse kernel (main kernel of a image based registration algorithm)
				//  typedef core::PreCachedRegistrationKernel<InterimRegistrationType::TargetDimensions, InterimRegistrationType::MovingDimensions> InverseKernelType;

				//  InverseKernelType::Pointer spIKernel = InverseKernelType::New();
				//  spIKernel->setTransformModel(spInterimTransformModel);

				//  //now build the direct kernel via inversion of the inverse kernel
				//  typedef core::InverseRegistrationKernelGenerator<InterimRegistrationType::TargetDimensions, InterimRegistrationType::MovingDimensions> GeneratorType;
				//  GeneratorType::Pointer spGenerator = GeneratorType::New();
				//  typedef GeneratorType::InverseKernelBaseType DirectKernelType;
				//  DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*(spIKernel.GetPointer()), pMovingRepresentation);

				//  if (spDKernel.IsNull())
				//  {
				//    mapExceptionMacro(AlgorithmException, <<"Error. Cannot determine direct mapping kernel of interim registration. Current inverse kernel: "<<spIKernel);
				//  }

				//  //now create the registration an set the kernels
				//  spResult = InterimRegistrationType::New();
				//  core::RegistrationManipulator<InterimRegistrationType::MovingDimensions, InterimRegistrationType::TargetDimensions> manipulator(spResult);

				//  manipulator.setDirectMapping(spDKernel);
				//  manipulator.setInverseMapping(spIKernel);
				//  manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				//}
				//return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doStopAlgorithm()
			{
				bool result = true;
				_internalRegistrationMethod->StopRegistration();
				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepareAlgorithm()
			{
				if (!this->getMovingImage())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving image.");
				}

				if (!this->getTargetImage())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target image.");
				}

				this->_currentIterationCount = 0;

				//create method
				this->_internalRegistrationMethod = InternalRegistrationMethodType::New();

				//initialize registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Transfer cached MetaProperties."));
				this->configureAlgorithmByMetaProperties();

				//assemble registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing itk registration method."));
				this->prepInitializeTransformation();

				//Connect images
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Connect images to itk registration method."));
				this->_internalRegistrationMethod->SetFixedImage(this->getTargetImage());
				this->_internalRegistrationMethod->SetMovingImage(this->getMovingImage());

				//Register observers
				typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onIterationEvent);
				this->_internalRegistrationMethod->AddObserver(::itk::IterationEvent(), spCommand);

				spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onGeneralRegistrationMethodEvent);
				this->_internalRegistrationMethod->AddObserver(::itk::AnyEvent(), spCommand);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			runAlgorithm()
			{
				this->_internalRegistrationMethod->Update();
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			finalizeAlgorithm()
			{
				typename RegistrationType::Pointer spResult = NULL;

				//now build the inverse kernel (main kernel of a image based registration algorithm)
				typedef typename
				::map::core::FieldKernels<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions>::PreCachedFieldBasedRegistrationKernel
				InverseKernelType;

				typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
				spIKernel->setField(this->_internalRegistrationMethod->GetDeformationField());

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
				::map::core::RegistrationManipulator<InterimRegistrationType> manipulator(spResult);

				manipulator.setDirectMapping(spDKernel);
				manipulator.setInverseMapping(spIKernel);
				manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				_spFinalizedRegistration = spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			prepInitializeTransformation()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::RegistrationPointer
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			onIterationEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock > LockHolderType;
				LockHolderType holder(this->_currentIterationLock);

				//*@TODO seems to be extremly outdated. rework needed.

				//bool hasCurrentValue = this->getOptimizerInternal()->hasCurrentValue();
				//OptimizerBaseType::SVNLMeasureType currentValue = this->getOptimizerInternal()->getCurrentMeasure();

				//        this->_currentIterationLock.Lock();
				//        ++_currentIterationCount;
				//        _currentTransformParameters = currentParams;

				//        os << "Iteration #"<<_currentIterationCount << "; params: ";

				//        os << currentParams << "; optimizer position: ";

				//        if (hasCurrentPosition)
				//        {
				//          os << currentPosition;
				//        }
				//        else
				//        {
				//          os << "unkown";
				//        }

				//        os << "; metric value: ";
				//        if (hasCurrentValue)
				//        {
				//          os << currentValue;
				//        }
				//        else
				//        {
				//          os << "unkown";
				//        }

				//        this->_currentIterationLock.Unlock();

				//        this->InvokeEvent(::map::events::AlgorithmIterationEvent(this,os.str()));
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			onGeneralRegistrationMethodEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller,
						"internal registration method event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			bool
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			registrationIsOutdated() const
			{
				bool outdated = _spFinalizedRegistration.IsNull();

				if (_spFinalizedRegistration.IsNotNull())
				{
					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = _internalRegistrationMethod->GetMovingImage() != this->getMovingImage();
					}

					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = _internalRegistrationMethod->GetFixedImage() != this->getTargetImage();
					}
				}

				return outdated;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			typename ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::OptimizerMeasureType
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			doGetCurrentOptimizerValue() const
			{
				OptimizerMeasureType result;

				//*@TODO Return of current optimization value

				//const OptimizerBaseType* pOptimizer = this->getOptimizerInternal();
				//
				//if (pOptimizer)
				//{
				//  if (pOptimizer->hasCurrentValue())
				//  {
				//    result = pOptimizer->getCurrentValue();
				//  }
				//}
				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			void
			ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::PrintSelf(os, indent);

				os << indent << "Current itertation count: " << _currentIterationCount << std::endl;
				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};


		} // end namespace boxed
	} // end namespace algorithm
} // end namespace map

#endif
