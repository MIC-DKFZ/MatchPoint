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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKMultiResImageRegistrationAlgorithm.tpp $
*/


#ifndef __ITK_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_TPP
#define __ITK_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_TPP

#include "mapAlgorithmException.h"
#include "mapModelBasedRegistrationKernel.h"
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			typename ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::ResolutionLevelCountType
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			doGetCurrentLevel() const
			{
				return this->_currentLevelCount;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			bool
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			hasLevelCount() const
			{
				return true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			ITKMultiResImageRegistrationAlgorithm()
			{
				_currentLevelCount = 0;
				_firstLevelEvent = true;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			~ITKMultiResImageRegistrationAlgorithm()
			{
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			prepCheckValidity()
			{
				Superclass::prepCheckValidity();

				if (!this->getMovingPyramideInternal())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no moving image pyramide available.");
				}

				if (!this->getTargetPyramideInternal())
				{
					mapExceptionMacro(AlgorithmException, << "Cannot start algorithm; no target image pyramide available.");
				}
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			prepPrepareSubComponents()
			{
				Superclass::prepPrepareSubComponents();

				this->preparePyramides();
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			prepAssembleSubComponents()
			{
				Superclass::prepAssembleSubComponents();

				this->getInternalRegistrationMethod().SetMovingImagePyramid(this->getMovingPyramideInternal());
				this->getInternalRegistrationMethod().SetFixedImagePyramid(this->getTargetPyramideInternal());
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			prepSetInternalInputData()
			{
				Superclass::prepSetInternalInputData();

				this->InvokeEvent(events::AlgorithmEvent(this, "Pass resolution schedules to itk registration method."));
				this->getInternalRegistrationMethod().SetSchedules(this->getTargetSchedule(), this->getMovingSchedule());
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			prepFinalizePreparation()
			{
				Superclass::prepFinalizePreparation();

				this->preparePyramidesAfterAssembly();
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			prepareAlgorithm()
			{
				/*check once before start to change internal state*/
				this->prepCheckValidity();

				this->_firstLevelEvent = true;
				this->_currentLevelCount = 0;

				Superclass::prepareAlgorithm();

				//Register level observers
				typename ::itk::MemberCommand<Self>::Pointer spCommand = ::itk::MemberCommand<Self>::New();
				spCommand->SetCallbackFunction(this, &Self::onLevelEvent);
				this->getInternalRegistrationMethod().AddObserver(::itk::IterationEvent(), spCommand);
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			onLevelEvent(::itk::Object *caller, const ::itk::EventObject &eventObject)
			{
				if (!(::itk::IterationEvent().CheckEvent(&eventObject)))
				{
					return;
				}

				typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock > LockHolderType;

				this->_currentIterationLock.Lock();
				this->_currentLevelLock.Lock();

				::map::core::OStringStream os;

				if (!this->_firstLevelEvent)
				{
					TransformParametersType currentParams = this->getTransformInternal()->getTransform()->GetParameters();

					bool hasCurrentPosition = this->getOptimizerInternal()->hasCurrentPosition();
					typename OptimizerBaseType::OptimizerPositionType currentPosition = this->getOptimizerInternal()->getCurrentPosition();

					bool hasCurrentValue = this->getOptimizerInternal()->hasCurrentValue();
					typename OptimizerBaseType::SVNLMeasureType currentValue = this->getOptimizerInternal()->getCurrentMeasure();

					++_currentLevelCount;
					this->_currentIterationCount = 0;

					this->_currentTransformParameters = currentParams;

					os << "Resolution level finished: final level params: ";

					if (hasCurrentPosition)
					{
						os << currentParams;
					}
					else
					{
						os << "unkown";
					}

					os << "; final level metric value: ";

					if (hasCurrentValue)
					{
						os << currentValue;
					}
					else
					{
						os << "unkown";
					}

					os << std::endl;
				}
				else
				{
					this->_firstLevelEvent = false;
				}

				os << "New Level #" << _currentLevelCount;

				this->_currentIterationLock.Unlock();
				this->_currentLevelLock.Unlock();

				this->InvokeEvent(events::AlgorithmResolutionLevelEvent(this, os.str()));
				this->doInterLevelSetup();
			};


			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			doInterLevelSetup()
			{
				//default implementation does nothing
			}

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			onTargetImagePyramideChange(const ::itk::EventObject &eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel befor the target pyramide will be unregistered
					this->_onGeneralTargePyramideObserver = NULL;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			onMovingImagePyramideChange(const ::itk::EventObject &eventObject)
			{
				map::events::UnregisterAlgorithmComponentEvent unregEvent;

				if (unregEvent.CheckEvent(&eventObject))
				{
					//we can directly reset the observer sentinel befor the moving pyramide will be unregistered
					this->_onGeneralMovingPyramideObserver = NULL;
				}
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			bool
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
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

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			void
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			PrintSelf(std::ostream &os, ::itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);

				os << indent << "Current level count: " << _currentLevelCount << std::endl;
			};

			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy, class TInterpolatorPolicy, class TMetricPolicy, class TOptimizerPolicy, class TTransformPolicy, class TPyramidesPolicy, class TInternalRegistrationMethod>
			bool
			ITKMultiResImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod>::
			doStopAlgorithm()
			{
				this->getInternalRegistrationMethod().StopRegistration();
				Superclass::doStopAlgorithm();
				return true;
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
