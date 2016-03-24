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




#ifndef __ITK_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_H
#define __ITK_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_H

#include "mapContinuous.h"

#include "mapITKImageRegistrationAlgorithm.h"
#include "mapArbitraryImagePyramidesPolicy.h"
#include "mapModifiableMultiResImageRegistrationAlgorithmBase.h"

#include "itkMultiResolutionImageRegistrationMethod.h"
#include "itkSimpleFastMutexLock.h"


namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKMultiResImageRegistrationAlgorithm
			@brief The class is used for image registration algorithm based on ITK and using a multi resolution approach.
			If you need to react on level changes (e.g. to adapt certain algorithm parameters) you can observe the object
			for AlgorithmResolutionLevelEvent. If you derive from this class you may also reimplement the method
			doInterLevelSetup to directly react on level changes within the class implementation.
			@ingroup Algorithms
			*/
			template < class TMovingImage, class TTargetImage,
					 class TIdentificationPolicy,
					 class TInterpolatorPolicy = ArbitraryInterpolatorPolicy<TMovingImage, core::continuous::ScalarType>,
					 class TMetricPolicy = ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>,
					 class TOptimizerPolicy = ArbitrarySVNLOptimizerPolicy,
					 class TTransformPolicy =
					 ArbitraryTransformPolicy<::map::core::continuous::ScalarType, TMovingImage::ImageDimension, TTargetImage::ImageDimension>,
					 class TPyramidesPolicy = ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>,
					 class TInternalRegistrationMethod =
					 ::itk::MultiResolutionImageRegistrationMethod<TTargetImage, TMovingImage> >
			class ITKMultiResImageRegistrationAlgorithm : public
				ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>,
			public ModifiableMultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>
			{
			public:
				typedef ITKMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
						TInterpolatorPolicy, TMetricPolicy,
						TOptimizerPolicy, TTransformPolicy, TPyramidesPolicy, TInternalRegistrationMethod > Self;
				typedef ITKImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy, TInterpolatorPolicy, TMetricPolicy, TOptimizerPolicy, TTransformPolicy, TInternalRegistrationMethod>
				Superclass;

				typedef ITKImageRegistrationAlgorithmInterface<TMovingImage, TTargetImage, typename TTransformPolicy::TransformScalarType, typename TInterpolatorPolicy::CoordRepType>
				ITKRegistrationType;
				typedef ModifiableMultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>
				MultiResRegistrationAlgorithmType;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKMultiResImageRegistrationAlgorithm, ITKImageRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef TMovingImage          MovingImageType;
				typedef TTargetImage          TargetImageType;
				typedef TInterpolatorPolicy   InterpolatorPolicyType;
				typedef TMetricPolicy         MetricPolicyType;
				typedef TOptimizerPolicy      OptimizerPolicyType;
				typedef TTransformPolicy      TransformPolicyType;
				typedef TIdentificationPolicy IdentificationPolicyType;
				typedef TPyramidesPolicy      PyramidesPolicyType;

				typedef typename ITKRegistrationType::OptimizerBaseType OptimizerBaseType;
				typedef typename ITKRegistrationType::MetricBaseType MetricBaseType;
				typedef typename ITKRegistrationType::TransformBaseType TransformBaseType;
				typedef typename ITKRegistrationType::InterpolatorBaseType InterpolatorBaseType;
				typedef typename MultiResRegistrationAlgorithmType::ScheduleType ScheduleType;
				typedef typename MultiResRegistrationAlgorithmType::ResolutionLevelCountType
				ResolutionLevelCountType;
				typedef typename MultiResRegistrationAlgorithmType::TargetImagePyramideBaseType
				TargetImagePyramideBaseType;
				typedef typename MultiResRegistrationAlgorithmType::MovingImagePyramideBaseType
				MovingImagePyramideBaseType;
				typedef typename MultiResRegistrationAlgorithmType::TargetImagePyramideBasePointer
				TargetImagePyramideBasePointer;
				typedef typename MultiResRegistrationAlgorithmType::MovingImagePyramideBasePointer
				MovingImagePyramideBasePointer;

				typedef typename
				IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>::OptimizerMeasureType
				OptimizerMeasureType;
				typedef ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>
				ImageRegistrationAlgorithmBaseType;

				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;
				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::IterationCountType IterationCountType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

				typedef typename ImageRegistrationAlgorithmBaseType::MovingImageConstPointer
				MovingImageConstPointer;
				typedef typename ImageRegistrationAlgorithmBaseType::TargetImageConstPointer
				TargetImageConstPointer;

				/*! Indicates if the current processed level can be deduced
				@eguarantee no fail
				*/
				virtual bool hasLevelCount() const;

			protected:
				ITKMultiResImageRegistrationAlgorithm();
				virtual ~ITKMultiResImageRegistrationAlgorithm();

				typedef typename Superclass::InternalRegistrationMethodType InternalRegistrationMethodType;
				typedef typename Superclass::InterimRegistrationType InterimRegistrationType;
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;

				/*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
				* or the modification times of at least one policy is newer then the modification time of the registration.
				@eguarantee strong
				@return true if the registration should be (re)computed. False if the registration is uptodate.
				*/
				virtual bool registrationIsOutdated() const;

				/*! This method should do all preparation tasks right before the algorithms execution. At the and of this method
				* the algorithm should be set up and ready to use.\n
				* The method delegates the main work of initialization to several sub methods. This sub methods serves as slots
				* that can be rewritten by a algorithm developer to alter certain aspects and keep the rest untouched.\n
				* The sequence of slot calls is: \n
				* - prepCheckValidity
				* - prepPrepareSubComponents
				* - prepAssembleSubComponents
				* - prepPerpareInternalInputData
				* - prepSetInternalInputData
				* - prepInitializeTransformation
				* - prepFinalizePreparation
				* @remark If you want to change the execution style, then overwrite runAlgorithm().
				@remark If you want to alter settings of optimzer, metric or interpolator depending on
				the resolution level use the method doInterLevelSetup()
				@eguarantee strong
				*/
				virtual void prepareAlgorithm();

				/*! This method is the slot to check if all internal components and input data are properly set.
				* @remark The default implementation checks transform, interpolator, optimizer, metric, pyramides, moving and target image.
				* overload this method to alter the validity check.
				* @remark It is assumed that the implementation of this method throws an exception if the algorithm is not be configured
				* correctly.*/
				virtual void prepCheckValidity();

				/*! This method is the slot where sub components can be configured before(!) they are set to the
				* internal registration method.
				* @remark The default implementation just calls the preparation methods of the component policies.*/
				virtual void prepPrepareSubComponents();

				/*! This method is the slot where sub components are set to the internal registration method.
				* @remark The default implementation just calls the preparation methods of the component policies.*/
				virtual void prepAssembleSubComponents();

				/*! This method is the slot for passing relevant input data to the internal algorithm or its components.
				* @remark The default implementation passes _spInternalMoving and _spInternalTargetImage, sets the schedules, the fixed image region of the registration and the metric masks.
				@eguarantee strong
				*/
				virtual void prepSetInternalInputData();


				/*! This method is the slot for final steps in the preperation process
				* @remark The default implementation calls the prepareAfterAssembly methods of the sub component policies.
				@eguarantee strong
				*/
				virtual void prepFinalizePreparation();

				typedef typename TransformPolicyType::TransformType::ParametersType	TransformParametersType;

				/*! return the current resolution level number.
				Will be called by getCurrentLevel() if hasLevelCount() returns true.
				@eguarantee strong
				@return level count
				*/
				virtual ResolutionLevelCountType doGetCurrentLevel() const;

				/*! This member is called by onLevelEvent() after the envent is invoked.
				The default implementation does nothing. It can be used in derivated
				classes to directly implement any initialization or setup strategies
				between level changes (e.g. adjusting the stepsize of the optimizer.
				*/
				virtual void doInterLevelSetup();

				/*! Overloaded member that also stops on the registration method
				 * level
				 */
				virtual bool doStopAlgorithm();

				/*! Methods invoked by derivated classes.  */
				virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

			private:
				/*! The count of the levels, since starting the registration algorithm the last time.
				* 0 indicates that no level has been processed yet.*/
				ResolutionLevelCountType _currentLevelCount;

				/*!Indicates if there was any level event before*/
				bool _firstLevelEvent;

				/*! The lock is used to manage the access to the member variable _currentLevelCount.*/
				mutable ::itk::SimpleFastMutexLock _currentLevelLock;

				mutable core::ObserverSentinel::Pointer _onLevelObserver;
				mutable core::ObserverSentinel::Pointer _onGeneralTargePyramideObserver;
				mutable core::ObserverSentinel::Pointer _onGeneralMovingPyramideObserver;

				/*! This member function is called by the observer of the optimizer, when ever a LevelEvent is invoked.*/
				void onLevelEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! This member function is called by the transform policy if the transform model instance changes.*/
				void onTargetImagePyramideChange(const ::itk::EventObject& eventObject);

				/*! This member function is called by the transform policy if the transform model instance changes.*/
				void onMovingImagePyramideChange(const ::itk::EventObject& eventObject);

				ITKMultiResImageRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKMultiResImageRegistrationAlgorithm.tpp"
#endif

#endif
