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


#ifndef __MAP_ITK_IMAGE_REGISTRATION_ALGORITHM_TPP
#define __MAP_ITK_IMAGE_REGISTRATION_ALGORITHM_TPP

#include "itkMutexLockHolder.h"
#include "itkExtractImageFilter.h"

#include "mapAlgorithmException.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"

#include "mapITKMVNLOptimizerControlInterface.h"
#include "mapITKSVNLOptimizerControlInterface.h"
#include "mapMaskBoundingBoxHelper.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::FieldRepRequirement::Type
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			isMovingRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::FieldRepRequirement::Type
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			isTargetRepresentationRequired() const
			{
				return FieldRepRequirement::No;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::IterationCountType
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			doGetCurrentIteration() const
			{
				return this->_currentIterationCount;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::IterationCountType
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			hasIterationCount() const
			{
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			isReusable() const
			{
				return true;
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			ITKImageRegistrationAlgorithm()
			{
				_finalizedTransformParameters.clear();
				_currentTransformParameters.clear();
				_currentIterationCount = 0;
				_spInternalMovingImage = NULL;
				_spInternalTargetImage = NULL;
				_CropInputImagesByMask = true;

				//now set the policy event slots
				typedef ::itk::ReceptorMemberCommand<Self> AlgorithmCommandType;

				typename AlgorithmCommandType::Pointer spInterpolatorCmd = AlgorithmCommandType::New();
				spInterpolatorCmd->SetCallbackFunction(this, &Self::onInterpolatorChange);
				InterpolatorPolicyType::_spOnChange = spInterpolatorCmd;

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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			~ITKImageRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			configureAlgorithm()
			{
				//default implementation does nothing;
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::TransformParametersType
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			getCurrentTransformParameters() const
			{
				typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock> LockHolderType;
				LockHolderType holder(this->_currentIterationLock);

				return this->_currentTransformParameters;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			setCurrentTransformParameters(const TransformParametersType& param)
			{
				typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock> LockHolderType;
				LockHolderType holder(this->_currentIterationLock);

				this->_currentTransformParameters = param;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::InterimRegistrationPointer
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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
						mapExceptionMacro(AlgorithmException,
						                  << "Error. Cannot determine interim registration. Unable to clone transform model. Current model: "
						                  << *pTransformModel);
					}

					//set the parameter of the interim transform model to the current transform parameters of the algorithm
					//We set the parameter by Value and not by using SetParameter() because otherwise
					//it could cause errors with itk transforms that only keep a pointer to their parameters (e.g. itk::BSplineDeformableTransform).
					//This transforms would be invalid as soon as we leave this method.
					spInterimTransformModel->SetParametersByValue(
					    this->getCurrentTransformParameters());

					//now build the inverse kernel (main kernel of a image based registration algorithm)
					typedef core::ModelBasedRegistrationKernel<InterimRegistrationType::TargetDimensions, InterimRegistrationType::MovingDimensions>
					InverseKernelType;

					typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
					spIKernel->setTransformModel(spInterimTransformModel);

					//now build the direct kernel via inversion of the inverse kernel
					typedef core::InverseRegistrationKernelGenerator<InterimRegistrationType::TargetDimensions, InterimRegistrationType::MovingDimensions>
					GeneratorType;
					typename GeneratorType::Pointer spGenerator = GeneratorType::New();
					typedef typename GeneratorType::InverseKernelBaseType DirectKernelType;
					typename DirectKernelType::Pointer spDKernel = spGenerator->generateInverse(*
					        (spIKernel.GetPointer()), pMovingRepresentation);

					if (spDKernel.IsNull())
					{
						mapExceptionMacro(AlgorithmException,
						                  << "Error. Cannot determine direct mapping kernel of interim registration. Current inverse kernel: "
						                  << spIKernel);
					}

					//now create the registration an set the kernels
					spResult = InterimRegistrationType::New();
					core::RegistrationManipulator<InterimRegistrationType> manipulator(spResult);

					manipulator.setDirectMapping(spDKernel);
					manipulator.setInverseMapping(spIKernel);
					manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				}

				return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			prepCheckValidity()
			{
				if (!this->getTransformInternal())
				{
					mapExceptionMacro(AlgorithmException,
					                  << "Cannot start algorithm; no transformation model available.");
				}

				if (!this->getInterpolatorInternal())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no interpolator available.");
				}

				if (!this->getOptimizerInternal())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no optimizer available.");
				}

				if (!this->getMetricInternal())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no metric available.");
				}

				if (!this->getMovingImage())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving image.");
				}

				if (!this->getTargetImage())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target image.");
				}
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			prepPrepareSubComponents()
			{
				this->prepareTransform();
				this->prepareInterpolator();
				this->prepareMetric();
				this->prepareOptimizer();
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			prepAssembleSubComponents()
			{
				this->_internalRegistrationMethod->SetMetric(this->getMetricInternal()->getImageToImageMetric());
				this->_internalRegistrationMethod->SetOptimizer(this->getOptimizerInternal()->getSVNLOptimizer());
				this->_internalRegistrationMethod->SetTransform(this->getTransformInternal());
				this->_internalRegistrationMethod->SetInterpolator(this->getInterpolatorInternal());
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			prepPerpareInternalInputData()
			{
				typedef ::itk::ExtractImageFilter<MovingImageType, MovingImageType> MovingExtractFilterType;
				typedef ::itk::ExtractImageFilter<TargetImageType, TargetImageType> TargetExtractFilterType;

				typename MovingExtractFilterType::Pointer movingFilter = MovingExtractFilterType::New();

				::map::core::OStringStream os;
				::map::core::OStringStream os2;

				if (this->getCropInputImagesByMask())
				{
					if (this->getTargetMask().IsNotNull())
					{
						//we have a mask -> so construct the image region
						typename TargetImageType::RegionType boundedRegion;

						if (::map::algorithm::MaskBoundingBoxHelper<TargetImageType::ImageDimension>::computeBoundingImageRegion(
						        this->getTargetMask(), this->getInternalTargetImage(), boundedRegion))
						{
							if (boundedRegion.Crop(this->getInternalTargetImage()->GetLargestPossibleRegion()))
							{
								os << "Target mask: set -> target image space region is set to: " <<::std::endl << boundedRegion;
								typename TargetExtractFilterType::Pointer targetFilter = TargetExtractFilterType::New();
								targetFilter->SetExtractionRegion(boundedRegion);
								targetFilter->SetInput(this->getInternalTargetImage());
								targetFilter->Update();
								typename TargetImageType::Pointer newTarget = targetFilter->GetOutput();
								newTarget->DisconnectPipeline();
								this->setInternalTargetImage(newTarget);
							}
							else
							{
								os << "Target mask: set, but invalid (not within the bufferd target image) -> use complete target image.";
							}
						}
						else
						{
							os << "Target mask: set, but invalid (cannot compute bounding box) -> use complete target image.";
						}
					}
					else
					{
						os << "Target mask: none -> use complete target image.";
					}

					this->InvokeEvent(events::AlgorithmEvent(this, os.str()));

					if (this->getMovingMask().IsNotNull())
					{
						//we have a mask -> so construct the image region
						typename MovingImageType::RegionType boundedRegion;

						if (::map::algorithm::MaskBoundingBoxHelper<MovingImageType::ImageDimension>::computeBoundingImageRegion(
						        this->getMovingMask(), this->getInternalMovingImage(), boundedRegion))
						{
							if (boundedRegion.Crop(this->getInternalMovingImage()->GetLargestPossibleRegion()))
							{
								os2 << "Moving mask: set -> moving image space region is set to: " <<::std::endl << boundedRegion;
								typename MovingExtractFilterType::Pointer movingFilter = MovingExtractFilterType::New();
								movingFilter->SetExtractionRegion(boundedRegion);
								movingFilter->SetInput(this->getInternalMovingImage());
								movingFilter->Update();
								typename MovingImageType::Pointer newMoving = movingFilter->GetOutput();
								newMoving->DisconnectPipeline();
								this->setInternalMovingImage(newMoving);
							}
							else
							{
								os2 << "Moving mask: set, but invalid (not within the bufferd moving image) -> use complete moving image.";
							}
						}
						else
						{
							os2 << "Moving mask: set, but invalid (cannot compute bounding box) -> use complete moving image.";
						}
					}
					else
					{
						os2 << "Moving mask: none -> use complete moving image.";
					}

					this->InvokeEvent(events::AlgorithmEvent(this, os2.str()));

				}
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			prepSetInternalInputData()
			{
				//Connect images
				this->InvokeEvent(events::AlgorithmEvent(this, "Connect images to itk registration method."));
				this->_internalRegistrationMethod->SetFixedImage(this->getInternalTargetImage());
				this->_internalRegistrationMethod->SetMovingImage(this->getInternalMovingImage());

				//Connect masks if present
				this->InvokeEvent(events::AlgorithmEvent(this, "Connect masks to registration metric."));

				if (this->getMovingMask().IsNotNull())
				{
					//add moving mask
					this->getMetricInternal()->getImageToImageMetric()->SetMovingImageMask(this->getMovingMask());
				}

				if (this->getTargetMask().IsNotNull())
				{
					//add target mask
					this->getMetricInternal()->getImageToImageMetric()->SetFixedImageMask(this->getTargetMask());
				}

				this->_internalRegistrationMethod->SetFixedImageRegion(
				    this->getInternalTargetImage()->GetLargestPossibleRegion());
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

				this->InvokeEvent(events::AlgorithmEvent(this, os.str()));
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			prepFinalizePreparation()
			{
				//initialize registration components after assembly
				this->prepareTransformAfterAssembly();
				this->prepareInterpolatorAfterAssembly();
				this->prepareMetricAfterAssembly();
				this->prepareOptimizerAfterAssembly(this->getMetricInternal()->getMinimizeToOptimize());
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			prepareAlgorithm()
			{
				this->prepCheckValidity();

				this->_currentIterationCount = 0;
				this->_spFinalizedRegistration = NULL;
				this->_spInternalMovingImage = NULL;
				this->_spInternalTargetImage = NULL;

				this->_finalizedTransformParameters.Fill(0);

				//create method
				this->_internalRegistrationMethod = InternalRegistrationMethodType::New();

				//initialize registration components
				this->InvokeEvent(events::AlgorithmEvent(this, "Transfer cached MetaProperties."));
				this->configureAlgorithmByMetaProperties();

				//initialize registration components
				this->InvokeEvent(events::AlgorithmEvent(this, "Initializing registration components."));
				this->prepPrepareSubComponents();

				//assemble registration components
				this->InvokeEvent(events::AlgorithmEvent(this,
				                  "Initializing itk multi resolution registration method."));
				this->prepAssembleSubComponents();

				this->InvokeEvent(events::AlgorithmEvent(this, "Initializing/Preparing input data."));

				this->prepPerpareInternalInputData();

				this->InvokeEvent(events::AlgorithmEvent(this, "Passing input data to internal algorithm."));
				this->prepSetInternalInputData();

				//possibility to initialize internal registration method after assembly
				this->prepInitializeTransformation();

				//initialize registration components after assembly
				this->InvokeEvent(events::AlgorithmEvent(this, "Finalizing initialization..."));
				this->prepFinalizePreparation();

				//Register observers
				if (_onIterationObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onIterationEvent);
					_onIterationObserver = core::ObserverSentinel::New(this->getOptimizerInternal()->getSVNLOptimizer(),
					                       ::itk::IterationEvent(), spCommand);
				}

				if (_onGeneralOptimizerObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onGeneralOptimizerEvent);
					_onGeneralOptimizerObserver = core::ObserverSentinel::New(
					                                  this->getOptimizerInternal()->getSVNLOptimizer(), ::itk::AnyEvent(), spCommand);
				}

				if (_onGeneralMetricObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onGeneralMetricEvent);
					_onGeneralMetricObserver = core::ObserverSentinel::New(
					                               this->getMetricInternal()->getImageToImageMetric(), ::itk::AnyEvent(), spCommand);
				}

				if (_onGeneralInterpolatorObserver.IsNull())
				{
					typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
					spCommand->SetCallbackFunction(this, &Self::onGeneralInterpolatorEvent);
					_onGeneralInterpolatorObserver = core::ObserverSentinel::New(this->getInterpolatorInternal(),
					                                 ::itk::AnyEvent(), spCommand);
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			runAlgorithm()
			{
				this->_internalRegistrationMethod->Update();
				this->_stopConditionDescription = this->getOptimizerInternal()->getStopConditionDescription();

				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

				//clone the transform model
				typename TransformBaseType::Pointer spFinalTransformModel = pTransformModel->Clone();

				if (spFinalTransformModel.IsNull())
				{
					mapExceptionMacro(AlgorithmException,
					                  << "Error. Cannot determine final registration. Unable to clone transform model. Current model: " <<
					                  *pTransformModel);
				}

				TransformParametersType lastTransformParameters =
				    this->_internalRegistrationMethod->GetLastTransformParameters();

				//set the parameter of the final transform model to the final transform parameters of the algorithm
				spFinalTransformModel->SetParametersByValue(
				    lastTransformParameters); //this line is need to ensure correct cloning for
				//itk transforms that only keep a pointer to their parameters (e.g. itk::BSplineDeformableTransform).
				//Thoose transforms can cause problems with optimizers that only keep the parameters localy (e.g. itk::LBFGSOptimizer).
				//Excplicit resetting the parameters is a work arround to this problem.

				//now build the inverse kernel (main kernel of a image based registration algorithm)
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

				//ensure that settings changed to the registration determination process are reseted to default
				this->configureAlgorithm();

				//now create the registration an set the kernels
				spResult = RegistrationType::New();
				core::RegistrationManipulator<RegistrationType> manipulator(spResult);

				manipulator.setDirectMapping(spDKernel);
				manipulator.setInverseMapping(spIKernel);
				manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

				//store the final results
				_spFinalizedRegistration = spResult;
				_finalizedTransformParameters = lastTransformParameters;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::RegistrationPointer
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			doGetRegistration() const
			{
				return _spFinalizedRegistration;
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onIterationEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				::map::core::OStringStream os;
				TransformParametersType currentParams =
				    this->getTransformInternal()->GetParameters();

				bool hasCurrentPosition = this->getOptimizerInternal()->hasCurrentPosition();
				typename OptimizerBaseType::OptimizerPositionType currentPosition =
				    this->getOptimizerInternal()->getCurrentPosition();

				bool hasCurrentValue = this->getOptimizerInternal()->hasCurrentValue();
				typename OptimizerBaseType::SVNLMeasureType currentValue =
				    this->getOptimizerInternal()->getCurrentMeasure();

				this->_currentIterationLock.Lock();
				++_currentIterationCount;
				_currentTransformParameters = currentParams;

				os << "Iteration #" << _currentIterationCount << "; params: ";

				os << currentParams << "; optimizer position: ";

				if (hasCurrentPosition)
				{
					os << currentPosition;
				}
				else
				{
					os << "unkown";
				}

				os << "; metric value: ";

				if (hasCurrentValue)
				{
					os << currentValue;
				}
				else
				{
					os << "unkown";
				}

				this->_currentIterationLock.Unlock();

				this->InvokeEvent(events::AlgorithmIterationEvent(this, os.str()));
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onGeneralOptimizerEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller, "internal optimizer event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onGeneralMetricEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller, "internal metric event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onGeneralInterpolatorEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller, "internal interpolator event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onGeneralTransformEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller, "internal transform event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onGeneralRegistrationMethodEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				events::AlgorithmWrapperEvent wrappedEvent(eventObject, caller,
				        "internal registration method event");
				this->InvokeEvent(wrappedEvent);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onOptimizerChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					// we can directly reset the observer sentinel befor the optimizer will be unregistered
					this->_onGeneralOptimizerObserver = NULL;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onMetricChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel befor the metric will be unregistered
					this->_onGeneralMetricObserver = NULL;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onInterpolatorChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel befor the interpolator will be unregistered
					this->_onGeneralInterpolatorObserver = NULL;
				}
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			onTransformChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel befor the transform will be unregistered
					this->_onGeneralTransformObserver = NULL;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			bool
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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
						outdated = _spFinalizedRegistration->GetMTime() < InterpolatorPolicyType::GetMTime();
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
						outdated = _spFinalizedRegistration->GetMTime() < this->getMovingImageMTime();
					}

					if (!outdated)
					{
						outdated = _spFinalizedRegistration->GetMTime() < this->getTargetImageMTime();
					}

					if (!outdated)
					{
						//check if the target mask has been changed
						outdated = _spFinalizedRegistration->GetMTime() < this->getTargetMaskMTime();
					}

					if (!outdated)
					{
						//check if the moving mask has been changed
						outdated = _spFinalizedRegistration->GetMTime() < this->getMovingMaskMTime();
					}

				}

				return outdated;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::OptimizerMeasureType
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::InternalRegistrationMethodType&

			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			getInternalRegistrationMethod()
			{
				return *(this->_internalRegistrationMethod.GetPointer());
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::PrintSelf(os, indent);
				MaskedRegistrationAlgorithmBase<TMovingImage::ImageDimension, TTargetImage::ImageDimension>::PrintSelf(
				    os, indent);

				os << indent << "Current itertation count: " << _currentIterationCount << std::endl;
				os << indent << "Current transform parameters: " << _currentTransformParameters << std::endl;
				os << indent << "Finalized transform parameters: " << _finalizedTransformParameters << std::endl;
				os << indent << "Finalized registration: " << _spFinalizedRegistration << std::endl;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
				#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("CropInputImagesByMasks", typeid(bool),
				                true,
				                true));
				#endif
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::MetaPropertyPointer
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "CropInputImagesByMasks")
				{
					spResult = ::map::core::MetaProperty<bool>::New(this->_CropInputImagesByMask);
				}

				return spResult;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "CropInputImagesByMasks")
				{
					bool crop;
					::map::core::unwrapMetaProperty(pProperty, crop);
					this->_CropInputImagesByMask = crop;
				}
				else
				{
					assert(false); //any other property name should have been excluded or allready handled by the calling function.
				}
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::MovingImageConstPointer
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			getInternalMovingImage() const
			{
				MovingImageConstPointer result = this->getMovingImage();

				if (this->_spInternalMovingImage.IsNotNull())
				{
					result = _spInternalMovingImage;
				}

				return result;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			typename ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::TargetImageConstPointer
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			getInternalTargetImage() const
			{
				TargetImageConstPointer result = this->getTargetImage();

				if (this->_spInternalTargetImage.IsNotNull())
				{
					result = _spInternalTargetImage;
				}

				return result;
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			setInternalMovingImage(MovingImageType* image)
			{
				_spInternalMovingImage = image;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TInternalRegistrationMethod>
			void
			ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>::
			setInternalTargetImage(TargetImageType* image)
			{
				_spInternalTargetImage = image;
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
