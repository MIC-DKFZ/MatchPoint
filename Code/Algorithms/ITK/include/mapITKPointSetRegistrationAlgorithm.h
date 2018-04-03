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




#ifndef __ITK_POINT_SET_REGISTRATION_ALGORITHM_H
#define __ITK_POINT_SET_REGISTRATION_ALGORITHM_H

#include "mapContinuous.h"

#include "mapArbitraryTransformPolicy.h"
#include "mapIterativeRegistrationAlgorithm.h"
#include "mapPointSetRegistrationAlgorithmBase.h"
#include "mapMetaPropertyAlgorithmBase.h"
#include "mapITKPointSetRegistrationAlgorithmInterface.h"
#include "mapArbitraryPointSetToPointSetMetricPolicy.h"
#include "mapArbitraryMVNLOptimizerPolicy.h"
#include "mapArbitraryTransformPolicy.h"
#include "mapObserverSentinel.h"

#include "itkPointSetToPointSetRegistrationMethod.h"
#include "itkSimpleFastMutexLock.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKPointSetRegistrationAlgorithm
			@brief The class for a point set image registration algorithm based on ITK (PointSetToPointSetRegistrationMethod)
			It implements a MetaPropertyAlgorithmInterface, but has by default no properties defined.
			@ingroup Algorithms
			*/
			template < class TMovingPointSet, class TTargetPointSet,
					 class TIdentificationPolicy,
					 class TMetricPolicy = ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>,
					 class TOptimizerPolicy = ArbitraryMVNLOptimizerPolicy,
					 class TTransformPolicy =
					 ArbitraryTransformPolicy< ::map::core::continuous::ScalarType, TMovingPointSet::PointDimension, TTargetPointSet::PointDimension>
					 >
			class ITKPointSetRegistrationAlgorithm : public
				IterativeRegistrationAlgorithm<TMovingPointSet::PointDimension, TTargetPointSet::PointDimension>,
			public PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>,
			public MetaPropertyAlgorithmBase,
			public ITKPointSetRegistrationAlgorithmInterface<TMovingPointSet, TTargetPointSet, typename TTransformPolicy::TransformScalarType>,
			public TIdentificationPolicy,
			public TMetricPolicy,
			public TOptimizerPolicy,
			public TTransformPolicy
			{
			public:
				typedef ITKPointSetRegistrationAlgorithm < TMovingPointSet, TTargetPointSet, TIdentificationPolicy,
						TMetricPolicy,
						TOptimizerPolicy, TTransformPolicy > Self;
				typedef IterativeRegistrationAlgorithm<TMovingPointSet::PointDimension, TTargetPointSet::PointDimension>
				Superclass;
				typedef ITKPointSetRegistrationAlgorithmInterface<TMovingPointSet, TTargetPointSet, typename TTransformPolicy::TransformScalarType>
				ITKRegistrationType;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKPointSetRegistrationAlgorithm, IterativeRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef TMetricPolicy         MetricPolicyType;
				typedef TOptimizerPolicy      OptimizerPolicyType;
				typedef TTransformPolicy      TransformPolicyType;
				typedef TIdentificationPolicy IdentificationPolicyType;

				typedef typename ITKRegistrationType::OptimizerBaseType OptimizerBaseType;
				typedef typename ITKRegistrationType::MetricBaseType MetricBaseType;
				typedef typename ITKRegistrationType::TransformBaseType TransformBaseType;

				typedef typename
				IterativeRegistrationAlgorithm<TMovingPointSet::PointDimension, TTargetPointSet::PointDimension>::OptimizerMeasureType
				OptimizerMeasureType;

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>
				PointSetRegistrationAlgorithmBaseType;

				typedef typename PointSetRegistrationAlgorithmBaseType::TargetPointSetType TargetPointSetType;
				typedef typename PointSetRegistrationAlgorithmBaseType::MovingPointSetType MovingPointSetType;
				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;
				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::IterationCountType IterationCountType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

				typedef typename MetaPropertyAlgorithmBase::MetaPropertyPointer MetaPropertyPointer;
				typedef typename MetaPropertyAlgorithmBase::MetaPropertyNameType MetaPropertyNameType;

				mapDefineAlgorithmIdentificationByPolicyMacro;

				// IterativeRegistrationAlgorithm
				/*! @eguarantee strong*/
				virtual bool isStoppable() const;

				/*! has the algorithm an iteration count?
				@eguarantee no fail
				@return Indicates if the algorithm can determin its current iteration count
				*/
				virtual bool hasIterationCount() const;

				/*! has the algorithm an maximum iteration count?
				@eguarantee no fail
				@return Indicates if the algorithm can determin its maximum iteration count
				*/
				virtual bool hasMaxIterationCount() const;

				/*! This function indicates of the optimizer of the iterative registration algorithm is
				* able to return its current metric/optimizer value(s)?
				@eguarantee no fail
				@return Indicates if the algorithm can determin its curent value.
				*/
				virtual bool hasCurrentOptimizerValue() const;

				virtual typename FieldRepRequirement::Type isMovingRepresentationRequired() const;

				virtual typename FieldRepRequirement::Type isTargetRepresentationRequired() const;

				virtual bool isReusable() const;

			protected:
				ITKPointSetRegistrationAlgorithm();
				virtual ~ITKPointSetRegistrationAlgorithm();

				typedef ::itk::PointSetToPointSetRegistrationMethod<TargetPointSetType, MovingPointSetType>
				InternalRegistrationMethodType;
				typedef typename Superclass::InterimRegistrationType InterimRegistrationType;
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;

				virtual void configureAlgorithm();

				// IterativeRegistrationAlgorithmInterface

				/*! @brief gets the registration result that has been computed in the last iteration.
				This result is limited by a region
				@pre pMovingRepresentation and pTargetRepresentation must not be null.
				@param [in] pMovingRepresentation Pointer to
				@eguarantee strong
				@return the interim registration result as smart pointer
				@retval a Registration object
				@sa Registration
				*/
				virtual InterimRegistrationPointer determineInterimRegistration(const
						MovingRepresentationDescriptorType* pMovingRepresentation,
						const TargetRepresentationDescriptorType* pTargetRepresentation) const;

				/*!
				* Returns the final registration
				@eguarantee strong
				*/
				virtual RegistrationPointer doGetRegistration() const;

				/*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
				* or the modification times of at least one policy is newer then the modification time of the registration.
				@eguarantee strong
				@return true if the registration should be (re)computed. False if the registration is uptodate.
				*/
				virtual bool registrationIsOutdated() const;

				virtual bool doStopAlgorithm();

				/*! This method should do all preperation tasks right befor the algorithms execution. At the and of this method
				* the algorithm should be set up and ready to use.
				* @remark If you want to change the execution style, then overwrite runAlgorithm().
				@eguarantee strong
				*/
				virtual void prepareAlgorithm();

				/*! This method should just execute the iteration loop.
				* @remark If you want to change the initialization or the finalization, then overwrite prepareAlgorithm() or finalizeAlgorithm().
				* @return Indicates of the registration was successfully determined (e.g. could be
				* false if an iterative algorithm was stopped prematurely by the user).
				* @eguarantee strong
				*/
				virtual bool runAlgorithm();

				/*! This method should do all the finalization work (e.g. generating the registration based on the iteration results).
				* @remark If you want to change the initialization or the iteration, then overwrite prepareAlgorithm() or runAlgorithm().
				@eguarantee strong
				*/
				virtual void finalizeAlgorithm();

				/*! This method should do all the special inizialization work of the internal registration method.
				* By default it just sets the initial transformation parameter for the methods to the values of the transform.
				@eguarantee strong
				*/
				virtual void prepInitializeTransformation();

				typedef typename TransformPolicyType::TransformType::ParametersType	TransformParametersType;

				/*! Gets the member variable _currentTransformParameters secured via _currentIterationLock.
				@return Copy of the current transform parameters.
				*/
				TransformParametersType getCurrentTransformParameters() const;

				/*! Sets the member variable _currentTransformParameters secured via _currentIterationLock.
				@param [in] Reference to the new current parameters.
				*/
				void setCurrentTransformParameters(const TransformParametersType& param);

				/*! return the optimizer value(s) of the current iteration step.
				Will be called by getCurrentOptimizerValue() if hasCurrentValue() returns true.
				@eguarantee strong
				@return current measure
				*/
				virtual OptimizerMeasureType doGetCurrentOptimizerValue() const;

				/*! Methods invoked by derivated classes.  */
				virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

				/*! @eguarantee strong*/
				virtual IterationCountType doGetCurrentIteration() const;

				/*! @brief gets the maximum number of the algorithm's iterations
				@eguarantee strong
				@return returns the algorithm's maximum iterations count
				*/
				virtual IterationCountType doGetMaxIterations() const;

				// MetaPropertyAlgorithmBase

				/*! @reimplemented*/
				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				/*! @reimplemented*/
				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				/*! @reimplemented*/
				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

			private:
				typename InternalRegistrationMethodType::Pointer _internalRegistrationMethod;

				/*! The current parameters of the registration transform. Will be set in every iteration step*/
				TransformParametersType _currentTransformParameters;

				/*! The parameters of the registration transform of the last successfull registration determiniation. Will be set by finalizeAlgorithm()*/
				TransformParametersType _finalizedTransformParameters;

				/*! Smartpointer to the finalized registration. Will be set by finalizeAlgorithm()*/
				typename RegistrationType::Pointer _spFinalizedRegistration;

				/*! The count if the iterations, since starting the registration algorithm the last time.
				* 0 indicates that no iteration has been processed yet.*/
				IterationCountType _currentIterationCount;

				/*! The lock is used to manage the access to the member variable _currentIterationCount.*/
				mutable ::itk::SimpleFastMutexLock _currentIterationLock;

				mutable core::ObserverSentinel::Pointer _onIterationObserver;
				mutable core::ObserverSentinel::Pointer _onGeneralOptimizerObserver;
				mutable core::ObserverSentinel::Pointer _onGeneralMetricObserver;
				mutable core::ObserverSentinel::Pointer _onGeneralTransformObserver;

				/*! This member function is called by the observer of the optimizer, when ever a IterationEvent is invoked.*/
				void onIterationEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! This member function is called by the observer of the optimizer for all kind of events. It serves as a pass through.*/
				void onGeneralOptimizerEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! This member function is called by the observer of the metric for all kind of events. It serves as a pass through.*/
				void onGeneralMetricEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! This member function is called by the observer of the transform for all kind of events. It serves as a pass through.*/
				void onGeneralTransformEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! This member function is called by the observer of the transform for all kind of events. It serves as a pass through.*/
				void onGeneralRegistrationMethodEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! This member function is called by the optimizer policy if the optimizer instance changes.*/
				void onOptimizerChange(const ::itk::EventObject& eventObject);

				/*! This member function is called by the metric policy if the metric instance changes.*/
				void onMetricChange(const ::itk::EventObject& eventObject);

				/*! This member function is called by the transform policy if the transform model instance changes.*/
				void onTransformChange(const ::itk::EventObject& eventObject);

				ITKPointSetRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKPointSetRegistrationAlgorithm.tpp"
#endif

#endif
