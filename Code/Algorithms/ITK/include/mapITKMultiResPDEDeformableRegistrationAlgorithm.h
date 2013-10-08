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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKMultiResPDEDeformableRegistrationAlgorithm.h $
*/




#ifndef __ITK_MULTI_RES_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_H
#define __ITK_MULTI_RES_PDE_DEFORMABLE_REGISTRATION_ALGORITHM_H

#include "mapContinuous.h"
#include "mapDiscreteElements.h"

#include "mapITKPDEDeformableRegistrationAlgorithmBase.h"
#include "mapObserverSentinel.h"
#include "mapModificationTimeValidator.h"
#include "mapMultiResImageRegistrationAlgorithmBase.h"
#include "mapArbitraryImagePyramidesPolicy.h"

#include "itkMultiResolutionPDEDeformableRegistration.h"
#include "itkSimpleFastMutexLock.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKMultiResPDEDeformableRegistrationAlgorithm
			@brief The class for an image registration algorithm based on ITK
			@ingroup Algorithms
			@ingroup ITK
			*/
			template < class TImageType,
			         class TIdentificationPolicy,
               class TInternalRegistrationFilter,
							 class TDisplacementField = core::discrete::Elements<typename TImageType::ImageDimension>::VectorFieldType ,
							 class TPyramidesPolicy = ArbitraryImagePyramidesPolicy<TImageType, TImageType> >
			class ITKMultiResPDEDeformableRegistrationAlgorithm : public ITKPDEDeformableRegistrationAlgorithmBase< TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter >,
				public MultiResImageRegistrationAlgorithmBase<TImageType, TImageType, TPyramidesPolicy>
			{
			public:
				typedef ITKMultiResPDEDeformableRegistrationAlgorithm < TImageType, TIdentificationPolicy, TInternalRegistrationFilter, TDisplacementField, TPyramidesPolicy > Self;
				typedef ITKPDEDeformableRegistrationAlgorithmBase < TImageType, TIdentificationPolicy, TDisplacementField, TInternalRegistrationFilter >  Superclass;

				typedef MultiResImageRegistrationAlgorithmBase<TImageType, TImageType, TPyramidesPolicy> MultiResRegistrationAlgorithmType;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKMultiResPDEDeformableRegistrationAlgorithm, ITKPDEDeformableRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef TIdentificationPolicy IdentificationPolicyType;
				typedef TPyramidesPolicy      PyramidesPolicyType;

				typedef typename IterativeRegistrationAlgorithm<TImageType::ImageDimension, TImageType::ImageDimension>::OptimizerMeasureType OptimizerMeasureType;
				typedef ImageRegistrationAlgorithmBase<TImageType, TImageType> ImageRegistrationAlgorithmBaseType;

				typedef typename Superclass::TargetImageType TargetImageType;
				typedef typename Superclass::MovingImageType MovingImageType;
				typedef typename Superclass::MovingImageConstPointer MovingImageConstPointer;
				typedef typename Superclass::TargetImageConstPointer TargetImageConstPointer;

				typedef typename MultiResRegistrationAlgorithmType::ScheduleType ScheduleType;
				typedef typename MultiResRegistrationAlgorithmType::ResolutionLevelCountType ResolutionLevelCountType;
				typedef typename MultiResRegistrationAlgorithmType::TargetImagePyramideBaseType TargetImagePyramideBaseType;
				typedef typename MultiResRegistrationAlgorithmType::MovingImagePyramideBaseType MovingImagePyramideBaseType;
				typedef typename MultiResRegistrationAlgorithmType::TargetImagePyramideBasePointer TargetImagePyramideBasePointer;
				typedef typename MultiResRegistrationAlgorithmType::MovingImagePyramideBasePointer MovingImagePyramideBasePointer;

				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;

				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;
				typedef typename Superclass::IterationCountType IterationCountType;

				typedef typename MetaPropertyAlgorithmBase::MetaPropertyPointer MetaPropertyPointer;
				typedef typename MetaPropertyAlgorithmBase::MetaPropertyNameType MetaPropertyNameType;
				typedef typename MetaPropertyAlgorithmBase::MetaPropertyVectorType MetaPropertyVectorType;

				/*! Indicates if the current processed level can be deduced
				@eguarantee no fail
				*/
				virtual bool hasLevelCount() const;

			protected:
				ITKMultiResPDEDeformableRegistrationAlgorithm();
				virtual ~ITKMultiResPDEDeformableRegistrationAlgorithm();

				typedef TInternalRegistrationFilter InternalRegistrationMethodType;
				typedef typename Superclass::InterimRegistrationType InterimRegistrationType;
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;

				/*! @reimplemented*/
				virtual void configureAlgorithm();

        /*! @reimplemented*/
        virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType &name) const;

        /*! @reimplemented*/
        virtual void doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty);

				virtual bool doStopAlgorithm();

				/*! This method should just execute the iteration loop.
				* @remark If you want to change the initialization or the finalization, then overwrite prepareAlgorithm() or finalizeAlgorithm().
				* @return Indicates of the registration was successfully determined (e.g. could be
				* false if an iterative algorithm was stopped prematurely by the user).
				* @eguarantee strong
				*/
				virtual bool runAlgorithm();


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
				@remark If you want to alter settings depending on the resolution level use the method doInterLevelSetup()
				@remark configureAlgorithmByMetaProperties is called after preCheckValidity and before prepPerpareSubComponent.
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
				* @remark The default implementation does nothing.*/
				virtual void prepPrepareSubComponents();

				/*! This method is the slot where sub components are set to the internal registration method.
				* @remark The default implementation does nothing.*/
				virtual void prepAssembleSubComponents();

				/*! This method is the slot for internal preprocessing of input data. This method should
				* be reimplemented if you want to prepare the input data before they go into the internal
				* registration method. E.g. blurring or normalizing the moving and target image before registration.
				* @remark The default implementation uses an itk::HistogrammMatchingFilter to normalize the gray values of the input image.
				* @remark Implementations of this method should work on _spInternalMoving and _spInternalTargetImage. In the default
				* implementation of prepSetInternalInputData() these member will be passed to the internal algorithm.
				@eguarantee strong
				*/
				virtual void prepPerpareInternalInputData();

				/*! This method is the slot for passing relevant input data to the internal algorithm or its components.
				* @remark The default implementation passes _spInternalMoving and _spInternalTargetImage, sets the schedules, the fixed image region of the registration and the metric masks.
				@eguarantee strong
				*/
				virtual void prepSetInternalInputData();

				/*! This method is a slot that is used for the initialization of the transformation model used
				* by the internal registration algorithm.
				* @remark By default it just sets the initial transformation parameter for the internal registration methods to the current values of the transform.
				@eguarantee strong
				*/
				virtual void prepInitializeTransformation();

				/*! This method is the slot for final steps in the preparation process
				* @remark The default implementation calls the prepareAfterAssembly methods of the sub component policies.
				@eguarantee strong
				*/
				virtual void prepFinalizePreparation();

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

				/*! Methods invoked by derivated classes.  */
				virtual void PrintSelf(std::ostream &os, ::itk::Indent indent) const;

				/*! @brief gets the maximum number of the algorithm's iterations
				@eguarantee strong
				@return returns the algorithm's maximum iterations count
				*/
				virtual IterationCountType doGetMaxIterations() const;

        virtual typename TDisplacementField::Pointer getFinalDisplacementField();

			private:
				typedef ::itk::MultiResolutionPDEDeformableRegistration<TImageType, TImageType, TDisplacementField> InternalMultiResRegFilterType;

				/*! Wrapping class that manage the multi resolution approach with PDEDeformable filter*/
				typename InternalMultiResRegFilterType::Pointer _multiResFilter;

				/*! The count of the levels, since starting the registration algorithm the last time.
				* 0 indicates that no level has been processed yet.*/
				ResolutionLevelCountType _currentLevelCount;

        /*! Cache for the number of iterations, defined by the user/developer.*/
        unsigned long _numberOfIterations;

				/*! The lock is used to manage the access to the member variable _currentLevelCount.*/
				mutable ::itk::SimpleFastMutexLock _currentLevelLock;

				mutable core::ObserverSentinel::Pointer _onLevelObserver;
				mutable core::ObserverSentinel::Pointer _onGeneralTargePyramideObserver;
				mutable core::ObserverSentinel::Pointer _onGeneralMovingPyramideObserver;

				/*! This member function is called by the observer of the optimizer, when ever a LevelEvent is invoked.*/
				void onLevelEvent(::itk::Object *caller, const ::itk::EventObject &eventObject);

				/*! This member function is called by the transform policy if the transform model instance changes.*/
				void onTargetImagePyramideChange(const ::itk::EventObject &eventObject);

				/*! This member function is called by the transform policy if the transform model instance changes.*/
				void onMovingImagePyramideChange(const ::itk::EventObject &eventObject);

				ITKMultiResPDEDeformableRegistrationAlgorithm(const Self &source);
				void operator=(const Self &); //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKMultiResPDEDeformableRegistrationAlgorithm.tpp"
#endif

#endif
