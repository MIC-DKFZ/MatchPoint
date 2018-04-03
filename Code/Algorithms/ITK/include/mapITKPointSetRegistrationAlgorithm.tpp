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


#ifndef __ITK_POINT_SET_REGISTRATION_ALGORITHM_TPP
#define __ITK_POINT_SET_REGISTRATION_ALGORITHM_TPP

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
		namespace itk
		{

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			isStoppable() const
			{
				bool result = false;
				const OptimizerBaseType* pOptimizer = this->getOptimizerInternal();

				if (pOptimizer)
				{
					result = pOptimizer->isStoppable();
				}

				return result;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::IterationCountType
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			doGetCurrentIteration() const
			{
				return this->_currentIterationCount;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::IterationCountType
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			doGetMaxIterations() const
			{
				IterationCountType result = 0;
				const OptimizerBaseType* pOptimizer = this->getOptimizerInternal();

				if (pOptimizer)
				{
					result = pOptimizer->getMaxIterations();
				}

				return result;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			hasIterationCount() const
			{
				return true;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			hasMaxIterationCount() const
			{
				bool result = false;
				const OptimizerBaseType* pOptimizer = this->getOptimizerInternal();

				if (pOptimizer)
				{
					result = pOptimizer->hasMaxIterationCount();
				}

				return result;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			hasCurrentOptimizerValue() const
			{
				bool result = false;
				const OptimizerBaseType* pOptimizer = this->getOptimizerInternal();

				if (pOptimizer)
				{
					result = pOptimizer->hasCurrentValue();
				}

				return result;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::FieldRepRequirement::Type
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			isMovingRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::FieldRepRequirement::Type
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			isTargetRepresentationRequired() const
			{
				typename TransformBaseType::InverseTransformBasePointer spInverseModel = this->getTransformModel()->GetInverseTransform();

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

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			isReusable() const
			{
				return true;
			}

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			ITKPointSetRegistrationAlgorithm()
			{
				_finalizedTransformParameters.clear();
				_currentTransformParameters.clear();
				_currentIterationCount = 0;

				//now set the policy event slots
				typedef ::itk::ReceptorMemberCommand<Self> AlgorithmCommandType;

				typename AlgorithmCommandType::Pointer spOptimizerCmd = AlgorithmCommandType::New();
				spOptimizerCmd->SetCallbackFunction(this, &Self::onOptimizerChange);
				OptimizerPolicyType::_spOnChange = spOptimizerCmd;

				typename AlgorithmCommandType::Pointer spMetricCmd = AlgorithmCommandType::New();
				spMetricCmd->SetCallbackFunction(this, &Self::onMetricChange);
				MetricPolicyType::_spOnChange = spMetricCmd;

				typename AlgorithmCommandType::Pointer spTransformCmd = AlgorithmCommandType::New();
				spTransformCmd->SetCallbackFunction(this, &Self::onTransformChange);
				TransformPolicyType::_spOnChange = spTransformCmd;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			~ITKPointSetRegistrationAlgorithm()
			{
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			configureAlgorithm()
			{
				//default implementation does nothing;
			}

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::TransformParametersType
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			getCurrentTransformParameters() const
			{
				typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock> LockHolderType;
				LockHolderType holder(this->_currentIterationLock);

				return this->_currentTransformParameters;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			setCurrentTransformParameters(const TransformParametersType& param)
			{
				typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock> LockHolderType;
				LockHolderType holder(this->_currentIterationLock);

				this->_currentTransformParameters = param;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::InterimRegistrationPointer
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			determineInterimRegistration(const MovingRepresentationDescriptorType* pMovingRepresentation,
										 const TargetRepresentationDescriptorType* pTargetRepresentation) const
			{
				InterimRegistrationPointer spResult = NULL;

				if (this->_currentIterationCount > 0)
				{
					//the algorithm has iterated at least once so we can determin an interim registration
					const TransformBaseType* pTransformModel = this->getTransformInternal();

					if (!pTransformModel)
					{
						mapExceptionMacro(AlgorithmException,
										  << "Error. Cannot determine interim registration. No transform model present on internal level (getTransformInternal(). Pleas ensure proper setup of algorithm.");
					}

					//clone the transform model
					typename TransformBaseType::Pointer spInterimTransformModel = pTransformModel->Clone();

					if (spInterimTransformModel.IsNull())
					{
						std::ostringstream modelStrm;
						pTransformModel->Print(modelStrm);
						mapExceptionMacro(AlgorithmException,
										  << "Error. Cannot determine interim registration. Unable to clone transform model. Current model: "
										  << modelStrm.str());
					}

					//set the parameter of the interim transform model to the current transform parameters of the algorithm
					//We set the parameter by Value and not by using SetParameter() because otherwise
					//it could cause errors with itk transforms that only keep a pointer to their parameters (e.g. itk::BSplineDeformableTransform).
					//This transforms would be invalid as soon as we leave this method.
					spInterimTransformModel->SetParametersByValue(
						this->getCurrentTransformParameters());

					//now build the direct kernel (main kernel of a point set based registration algorithm)
					typedef core::PreCachedRegistrationKernel<InterimRegistrationType::MovingDimensions, InterimRegistrationType::TargetDimensions>
					DirectKernelType;

					typename DirectKernelType::Pointer spDKernel = DirectKernelType::New();
					spDKernel->setTransformModel(spInterimTransformModel);

					//now build the inverse kernel via inversion of the direct kernel
					typedef core::InverseRegistrationKernelGenerator<InterimRegistrationType::MovingDimensions, InterimRegistrationType::TargetDimensions>
					GeneratorType;
					typename GeneratorType::Pointer spGenerator = GeneratorType::New();
					typedef typename GeneratorType::InverseKernelBaseType InverseKernelType;
					typename InverseKernelType::Pointer spIKernel = spGenerator->generateInverse(*
							(spDKernel.GetPointer()), this->getTargetRepresentation());

					if (spIKernel.IsNull())
					{
						mapExceptionMacro(AlgorithmException,
										  << "Error. Cannot determine inverse mapping kernel of interim registration. Current direct kernel: "
										  << spDKernel);
					}

					//now create the registration an set the kernels
					spResult = InterimRegistrationType::New();
					::map::core::RegistrationManipulator<InterimRegistrationType> manipulator(spResult);

					manipulator.setDirectMapping(spDKernel);
					manipulator.setInverseMapping(spIKernel);
					manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				}

				return spResult;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			doStopAlgorithm()
			{
				bool result = false;
				OptimizerBaseType* pOptimizer = this->getOptimizerInternal();

				if (pOptimizer)
				{
					result = pOptimizer->stop();
				}

				return result;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			prepareAlgorithm()
			{
				if (!this->getTransformInternal())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Cannot start algorithm; no transformation model available.");
				}

				if (!this->getOptimizerInternal())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no optimizer available.");
				}

				if (!this->getMetricInternal())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no metric available.");
				}

				if (!this->getMovingPointSet())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving point set.");
				}

				if (!this->getTargetPointSet())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target point set.");
				}

				this->_currentIterationCount = 0;
				this->_spFinalizedRegistration = NULL;

				//create method
				this->_internalRegistrationMethod = InternalRegistrationMethodType::New();

				//initialize registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Transfer cached MetaProperties."));
				this->configureAlgorithmByMetaProperties();

				//initialize registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing registration components."));
				this->prepareTransform();
				this->prepareMetric();
				this->prepareOptimizer();

				//assemble registration components
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Initializing itk registration method."));
				this->_internalRegistrationMethod->SetMetric(
					this->getMetricInternal()->getPointSetToPointSetMetric());
				this->_internalRegistrationMethod->SetOptimizer(this->getOptimizerInternal()->getMVNLOptimizer());
				this->_internalRegistrationMethod->SetTransform(this->getTransformInternal());
				this->prepInitializeTransformation();

				//Connect point sets
				this->InvokeEvent(::map::events::AlgorithmEvent(this, "Connect point sets to itk registration method."));
				this->_internalRegistrationMethod->SetFixedPointSet(this->getTargetPointSet());
				this->_internalRegistrationMethod->SetMovingPointSet(this->getMovingPointSet());

				//initialize registration components after assembly
				this->prepareTransformAfterAssembly();
				this->prepareMetricAfterAssembly();
				this->prepareOptimizerAfterAssembly(this->getMetricInternal()->getMinimizeToOptimize());

				//Register observers
				if (_onIterationObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onIterationEvent);
					_onIterationObserver = core::ObserverSentinel::New(this->getOptimizerInternal()->getMVNLOptimizer(),
										   ::itk::IterationEvent(), spCommand);
				}

				if (_onGeneralOptimizerObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onGeneralOptimizerEvent);
					_onGeneralOptimizerObserver = core::ObserverSentinel::New(
													  this->getOptimizerInternal()->getMVNLOptimizer(), ::itk::AnyEvent(), spCommand);
				}

				if (_onGeneralMetricObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onGeneralMetricEvent);
					_onGeneralMetricObserver = core::ObserverSentinel::New(
												   this->getMetricInternal()->getPointSetToPointSetMetric(), ::itk::AnyEvent(), spCommand);
				}

				if (_onGeneralTransformObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onGeneralTransformEvent);
					_onGeneralTransformObserver = core::ObserverSentinel::New(
													  this->getTransformInternal(), ::itk::AnyEvent(), spCommand);
				}

				typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onGeneralRegistrationMethodEvent);
				this->_internalRegistrationMethod->AddObserver(::itk::AnyEvent(), spCommand);
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			runAlgorithm()
			{
				this->_internalRegistrationMethod->Update();
				this->_stopConditionDescription = this->getOptimizerInternal()->getStopConditionDescription();

				return true;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			finalizeAlgorithm()
			{
				RegistrationPointer spResult = NULL;

				//touch the sub component to ensure an actualzed modification time,
				//this is needed because in case of arbitrary policies and dll deployment
				//the components could come out of another context. So a
				//ModificationTimeValidator is needed in it could produce
				//false positives in this constellation.
				OptimizerPolicyType::GetMTime();
				MetricPolicyType::GetMTime();
				TransformPolicyType::GetMTime();

				TransformBaseType* pTransformModel = this->getTransformInternal();

				if (!pTransformModel)
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine final registration. No transform model present on internal level (getTransformInternal()). Please ensure proper setup of algorithm.");
				}

				TransformParametersType lastTransformParameters =
					this->_internalRegistrationMethod->GetLastTransformParameters();

				//clone the transform model
				pTransformModel->SetParametersByValue(
					lastTransformParameters); //this line is need to ensure correct cloning for
				//itk transforms that only keep a pointer to their parameters (e.g. itk::BSplineDeformableTransform).
				//Thoose transforms can cause problems with optimizers that only keep the parameters localy (e.g. itk::LBFGSOptimizer).
				//Excplicit resetting the parameters is a work arround to this problem.
				typename TransformBaseType::Pointer spFinalTransformModel = pTransformModel->Clone();

				if (spFinalTransformModel.IsNull())
				{
					std::ostringstream modelStrm;
					pTransformModel->Print(modelStrm);
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine final registration. Unable to clone transform model. Current model: " <<
									  modelStrm.str());
				}

				//set the parameter of the final transform model to the final transform parameters of the algorithm
				//We set the parameter by Value and not by using SetParameter() because otherwise
				//it could cause errors with itk transforms that only keep a pointer to their parameters (e.g. itk::BSplineDeformableTransform).
				//This transforms would be invalid as soon as we leave this method.
				spFinalTransformModel->SetParametersByValue(lastTransformParameters);

				//now build the direct kernel (main kernel of a point set based registration algorithm)
				typedef core::PreCachedRegistrationKernel<RegistrationType::MovingDimensions, RegistrationType::TargetDimensions>
				DirectKernelType;

				typename DirectKernelType::Pointer spDKernel = DirectKernelType::New();
				spDKernel->setTransformModel(spFinalTransformModel);

				//now build the inverse kernel via inversion of the direct kernel
				typedef core::InverseRegistrationKernelGenerator<RegistrationType::MovingDimensions, RegistrationType::TargetDimensions>
				GeneratorType;
				typename GeneratorType::Pointer spGenerator = GeneratorType::New();
				typedef typename GeneratorType::InverseKernelBaseType InverseKernelType;
				typename InverseKernelType::Pointer spIKernel = spGenerator->generateInverse(*
						(spDKernel.GetPointer()), this->getTargetRepresentation());

				if (spIKernel.IsNull())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine inverse mapping kernel of final registration. Current direct kernel: "
									  << spDKernel);
				}

				//ensure that settings changed to the registration determination process are reseted to default
				this->configureAlgorithm();

				//now create the registration an set the kernels
				spResult = RegistrationType::New();
				::map::core::RegistrationManipulator<RegistrationType> manipulator(spResult);

				manipulator.setDirectMapping(spDKernel);
				manipulator.setInverseMapping(spIKernel);
				manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				//store the final results
				_spFinalizedRegistration = spResult;
				_finalizedTransformParameters = lastTransformParameters;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			prepInitializeTransformation()
			{
				const TransformBaseType* pTransformModel = this->getTransformInternal();

				if (!pTransformModel)
				{
					mapExceptionMacro(AlgorithmException,
									  << "Error. Cannot determine interim registration. No transform model present on internal level (getTransformInternal(). Pleas ensure proper setup of algorithm.");
				}

				::map::core::OStringStream os;
				os << "Set start transformation parameters to: " <<
				   pTransformModel->GetParameters();
				//set the parameter of the transform model to the current transform parameters of the algorithm
				this->setCurrentTransformParameters(pTransformModel->GetParameters());
				this->_internalRegistrationMethod->SetInitialTransformParameters(
					pTransformModel->GetParameters());

				this->InvokeEvent(::map::events::AlgorithmEvent(this, os.str()));
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::RegistrationPointer
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};


			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onIterationEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::core::OStringStream os;
				TransformParametersType currentParams =
					this->getTransformInternal()->GetParameters();

				bool hasCurrentValue = this->getOptimizerInternal()->hasCurrentValue();
				typename OptimizerBaseType::MVNLMeasureType currentValue =
					this->getOptimizerInternal()->getCurrentMeasure();

				this->_currentIterationLock.Lock();
				++_currentIterationCount;
				_currentTransformParameters = currentParams;
				os << "Iteration #" << _currentIterationCount << "; params: " << currentParams <<
				   "; metric value: ";

				if (hasCurrentValue)
				{
					os << currentValue;
				}
				else
				{
					os << "unkown";
				}

				this->_currentIterationLock.Unlock();


				this->InvokeEvent(::map::events::AlgorithmIterationEvent(this, os.str()));
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onGeneralOptimizerEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller, "internal optimizer event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onGeneralMetricEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller, "internal metric event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onGeneralTransformEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller, "internal transform event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onGeneralRegistrationMethodEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller,
						"internal registration method event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onOptimizerChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					// we can directly reset the observer sentinel befor the optimizer will be unregistered
					this->_onGeneralOptimizerObserver = NULL;
				}
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onMetricChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel befor the metric will be unregistered
					this->_onGeneralMetricObserver = NULL;
				}
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			onTransformChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel befor the transform will be unregistered
					this->_onGeneralTransformObserver = NULL;
				}
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			bool
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			registrationIsOutdated() const
			{
				bool outdated = _spFinalizedRegistration.IsNull();

				if (_spFinalizedRegistration.IsNotNull())
				{
					if (!outdated)
					{
						outdated = _spFinalizedRegistration->GetMTime() < MetaPropertyAlgorithmBase::GetMTime();
					}

					if (!outdated)
					{
						outdated = _spFinalizedRegistration->GetMTime() < OptimizerPolicyType::GetMTime();
					}

					if (!outdated)
					{
						outdated = _spFinalizedRegistration->GetMTime() < MetricPolicyType::GetMTime();
					}

					if (!outdated)
					{
						outdated = _spFinalizedRegistration->GetMTime() < TransformPolicyType::GetMTime();
					}

					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = _internalRegistrationMethod->GetMovingPointSet() != this->getMovingPointSet();
					}

					if (!outdated)
					{
						//check if the inputs have been changed
						outdated = _internalRegistrationMethod->GetFixedPointSet() != this->getTargetPointSet();
					}
				}

				return outdated;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::OptimizerMeasureType
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			doGetCurrentOptimizerValue() const
			{
				OptimizerMeasureType result;

				const OptimizerBaseType* pOptimizer = this->getOptimizerInternal();

				if (pOptimizer)
				{
					if (pOptimizer->hasCurrentValue())
					{
						result = pOptimizer->getCurrentValue();
					}
				}

				return result;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>::PrintSelf(os, indent);

				os << indent << "Current itertation count: " << _currentIterationCount << std::endl;
				os << indent << "Current transform parameters: " << _currentTransformParameters << std::endl;
				os << indent << "Finalized transform parameters: " << _finalizedTransformParameters << std::endl;
				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
				//default implementation does nothing.
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			typename ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::MetaPropertyPointer
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				//default implementation does nothing.
				MetaPropertyPointer spDummy;
				return spDummy;
			};

			template<class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy>
			void
			ITKPointSetRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TIdentificationPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				//default implementation does nothing.
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
