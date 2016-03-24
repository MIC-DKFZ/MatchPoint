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


#ifndef __ITK_MULTI_RES_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_TPP
#define __ITK_MULTI_RES_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_TPP

#include <itkHistogramMatchingImageFilter.h>

#include "mapAlgorithmException.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationManipulator.h"
#include "mapAlgorithmWrapperEvent.h"
#include "mapMetaProperty.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			typename ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::IterationCountType
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			doGetMaxIterations() const
			{
				typename InternalMultiResRegFilterType::NumberOfIterationsType iterations =
					this->_multiResFilter->GetNumberOfIterations();
				IterationCountType result = 0;

				if (iterations.size() > _currentLevelCount)
				{
					result = iterations[_currentLevelCount];
				}

				return result;
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			ITKMultiResPDEDeformableRegistrationAlgorithm()
			{
				this->_spInternalMovingImage = NULL;
				this->_spInternalTargetImage = NULL;
				this->_multiResFilter = InternalMultiResRegFilterType::New();
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			~ITKMultiResPDEDeformableRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			configureAlgorithm()
			{
				Superclass::configureAlgorithm();

				this->setResolutionLevels(3);
				this->_multiResFilter = InternalMultiResRegFilterType::New();
				this->_numberOfIterations = 10;
			}

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			typename ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::ResolutionLevelCountType
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			doGetCurrentLevel() const
			{
				return this->_currentLevelCount;
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			bool
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			hasLevelCount() const
			{
				return true;
			};


			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			bool
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			doStopAlgorithm()
			{
				bool result = false;

				this->_multiResFilter->StopRegistration();

				return result;
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepCheckValidity()
			{
				Superclass::prepCheckValidity();

				if (!this->getMovingPyramideInternal())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Cannot start algorithm; no moving image pyramide available.");
				}

				if (!this->getTargetPyramideInternal())
				{
					mapExceptionMacro(AlgorithmException,
									  << "Cannot start algorithm; no target image pyramide available.");
				}
			}

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepPrepareSubComponents()
			{
				Superclass::prepPrepareSubComponents();

				this->preparePyramides();
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepAssembleSubComponents()
			{
				Superclass::prepAssembleSubComponents();

				this->_multiResFilter->SetRegistrationFilter(&(this->getInternalRegistrationMethod()));
				this->_multiResFilter->SetMovingImagePyramid(this->getMovingPyramideInternal());
				this->_multiResFilter->SetFixedImagePyramid(this->getTargetPyramideInternal());
			}

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepPerpareInternalInputData()
			{
				Superclass::prepPerpareInternalInputData();
				this->InvokeEvent(::map::events::AlgorithmEvent(this,
								  "Pass resolution level count to itk registration method."));
				this->_multiResFilter->SetNumberOfLevels(this->getResolutionLevels());
			}

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepSetInternalInputData()
			{
				//Connect images
				this->InvokeEvent(::map::events::AlgorithmEvent(this,
								  "Connect images to itk multi res PDE registration filter."));
				this->_multiResFilter->SetFixedImage(this->_spInternalTargetImage);
				this->_multiResFilter->SetMovingImage(this->_spInternalMovingImage);
			}

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepInitializeTransformation()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepFinalizePreparation()
			{
				Superclass::prepFinalizePreparation();

				typename InternalMultiResRegFilterType::NumberOfIterationsType iterations;
				iterations.SetSize(this->getResolutionLevels());
				iterations.Fill(this->_numberOfIterations);
				this->_multiResFilter->SetNumberOfIterations(iterations);

				this->preparePyramidesAfterAssembly();
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			prepareAlgorithm()
			{
				/*check once before start to change internal state*/
				this->prepCheckValidity();

				this->_currentLevelCount = 0;

				Superclass::prepareAlgorithm();

				//Register level observers
				typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onLevelEvent);
				this->_multiResFilter->AddObserver(::itk::IterationEvent(), spCommand);
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			bool
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			runAlgorithm()
			{
				this->_multiResFilter->Update();
				return true;
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			onLevelEvent(::itk::Object* caller, const ::itk::EventObject& eventObject)
			{
				if (!(::itk::IterationEvent().CheckEvent(&eventObject)))
				{
					return;
				}

				typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock > LockHolderType;

				this->_currentIterationLock.Lock();
				this->_currentLevelLock.Lock();

				::map::core::OStringStream os;

				bool hasCurrentValue = this->hasCurrentOptimizerValue();
				OptimizerMeasureType currentValue = this->getCurrentOptimizerValue();

				++_currentLevelCount;
				this->_currentIterationCount = 0;

				os << "Resolution level finished: final level metric value: ";

				if (hasCurrentValue)
				{
					os << currentValue[0];
				}
				else
				{
					os << "unkown";
				}

				os << std::endl;

				os << "New Level #" << _currentLevelCount;

				this->_currentIterationLock.Unlock();
				this->_currentLevelLock.Unlock();

				this->InvokeEvent(::map::events::AlgorithmResolutionLevelEvent(this, os.str()));
				this->doInterLevelSetup();
			};


			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			doInterLevelSetup()
			{
				//default implementation does nothing
			}

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			bool
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			registrationIsOutdated() const
			{
				bool outdated = Superclass::registrationIsOutdated();


				if (!outdated)
				{
					outdated = this->_spFinalizedRegistration->GetMTime() < this->getTargetPyramideMTime();
				}

				if (!outdated)
				{
					outdated = this->_spFinalizedRegistration->GetMTime() < this->getMovingPyramideMTime();
				}

				return outdated;
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			onTargetImagePyramideChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel before the target pyramide will be unregistered
					this->_onGeneralTargePyramideObserver = NULL;
				}
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			onMovingImagePyramideChange(const ::itk::EventObject& eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel before the moving pyramide will be unregistered
					this->_onGeneralMovingPyramideObserver = NULL;
				}
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			PrintSelf(std::ostream& os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				os << indent << "Current level count: " << _currentLevelCount << std::endl;
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			typename ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::MetaPropertyPointer
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "NumberOfIterations")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(_numberOfIterations);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				return spResult;
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			void
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "NumberOfIterations")
				{
					unsigned long num;
					map::core::unwrapMetaProperty(pProperty, num);
					_numberOfIterations = num;
				}
				else
				{
					Superclass::doSetProperty(name, pProperty);
				}
			};

			template < class TImageType, class TIdentificationPolicy, class TInternalRegistrationFilter, class TDisplacementField, class TPyramidesPolicy>
			typename TDisplacementField::Pointer
			ITKMultiResPDEDeformableRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy>::
			getFinalDisplacementField()
			{
				return this->_multiResFilter->GetOutput();
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
