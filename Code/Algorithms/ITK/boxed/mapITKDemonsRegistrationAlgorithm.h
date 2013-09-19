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




#ifndef __MAP_DEMONS_REGISTRATION_ALGORITHM_H
#define __MAP_DEMONS_REGISTRATION_ALGORITHM_H

#include "itkDemonsRegistrationFilter.h"

#include "mapContinuous.h"
#include "mapDiscreteElements.h"

#include "mapIterativeRegistrationAlgorithm.h"
#include "mapImageRegistrationAlgorithmBase.h"
#include "mapMetaPropertyAlgorithmBase.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
    mark code as components of this project
 */
namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			mapGenerateAlgorithmUIDPolicyMacro(ITKDemonsRegistationUIDPolicy, "de.dkfz.matchpoint",
											   "ITKDemonsRegistrationAlgorithm", "1.0.0", "");

			/*! @class ITKDemonsRegistrationAlgorithm
			    @brief The class wraps the itk::DemonsRegistrationFilter as MatchPoint algorithm
			    @ingroup Boxed
			 */
			template < class TMovingImage, class TTargetImage,
					 class TIdentificationPolicy = ITKDemonsRegistationUIDPolicy >
			class ITKDemonsRegistrationAlgorithm : public
				IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>,
			public ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>,
			public TIdentificationPolicy,
			public MetaPropertyAlgorithmBase
			{
			public:
				typedef ITKDemonsRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy> Self;
				typedef IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>
				Superclass;
				typedef TIdentificationPolicy IdentificationPolicyType;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKDemonsRegistrationAlgorithm, IterativeRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef typename
				IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>::OptimizerMeasureType
				OptimizerMeasureType;

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;
				typedef typename RegistrationAlgorithmBase::AlgorithmType AlgorithmType;
				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;
				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;
				typedef typename Superclass::InterimRegistrationType InterimRegistrationType;
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;
				typedef typename Superclass::IterationCountType IterationCountType;

				mapDefineAlgorithmIdentificationByPolicyMacro;

				// IterativeRegistrationAlgorithm
				/*! @eguarantee strong*/
				virtual bool isStoppable() const;

				/*! has the algorithm an iteration count?
				@eguarantee no fail
				@return Indicates if the algorithm can determine its current iteration count
				*/
				virtual bool hasIterationCount() const;

				/*! has the algorithm an maximum iteration count?
				@eguarantee no fail
				@return Indicates if the algorithm can determine its maximum iteration count
				*/
				virtual bool hasMaxIterationCount() const;

				/*! This function indicates of the optimizer of the iterative registration algorithm is
				* able to return its current metric/optimizer value(s)?
				@eguarantee no fail
				@return Indicates if the algorithm can determine its current value.
				*/
				virtual bool hasCurrentOptimizerValue() const;

			protected:
				ITKDemonsRegistrationAlgorithm();
				virtual ~ITKDemonsRegistrationAlgorithm();

				typedef typename ::map::core::discrete::Elements< Superclass::TargetDimensions >::VectorFieldType
				DisplacementFieldType;
				typedef ::itk::DemonsRegistrationFilter<TTargetImage, TMovingImage, DisplacementFieldType>
				InternalRegistrationMethodType;

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

				/*! This method should do all the special initialization work of the internal registration method.
				 * By default it just sets the initial transformation parameter for the methods to the values of the transform
				 * and sets the fixed image region if a target mask is set.
				  @eguarantee strong
				 */
				virtual void prepInitializeTransformation();

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

				typename InternalRegistrationMethodType::Pointer _internalRegistrationMethod;

			private:

				/*! Smartpointer to the finalized registration. Will be set by finalizeAlgorithm()*/
				typename RegistrationType::Pointer _spFinalizedRegistration;

				/*! The count if the iterations, since starting the registration algorithm the last time.
				 * 0 indicates that no iteration has been processed yet.*/
				IterationCountType _currentIterationCount;

				/*! The lock is used to manage the access to the member variable _currentIterationCount.*/
				mutable ::itk::SimpleFastMutexLock _currentIterationLock;

				/*! This member function is called by the observer of the optimizer, when ever a IterationEvent is invoked.*/
				void onIterationEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! This member function is called by the observer of the transform for all kind of events. It serves as a pass through.*/
				void onGeneralRegistrationMethodEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				ITKDemonsRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKDemonsRegistrationAlgorithm.tpp"
#endif

#endif
