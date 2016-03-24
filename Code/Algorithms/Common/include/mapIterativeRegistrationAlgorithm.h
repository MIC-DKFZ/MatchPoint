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




#ifndef __ITERATIVE_REGISTRATION_ALGORITHM_H
#define __ITERATIVE_REGISTRATION_ALGORITHM_H

#include "mapIterativeAlgorithmBase.h"
#include "mapRegistrationAlgorithm.h"
#include "mapFieldRepresentationDescriptor.h"
#include "mapInterimRegistrationResultAccessInterface.h"
#include "mapStoppableAlgorithmInterface.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{

		/*! @class IterativeRegistrationAlgorithm
		@brief This is the default implementation for iterative and (potentially) stoppable registration algorithms
		@ingroup Algorithms
		*/
		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		class IterativeRegistrationAlgorithm: public
			RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>, public IterativeAlgorithmBase,
		public facet::InterimRegistrationResultAccessInterface<VMovingDimensions, VTargetDimensions>,
		public facet::StoppableAlgorithmInterface
		{
		public:
			typedef IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions> Self;
			typedef RegistrationAlgorithm<VMovingDimensions, VTargetDimensions> Superclass;

			typedef facet::InterimRegistrationResultAccessInterface<VMovingDimensions, VTargetDimensions>
			InterimInterfaceType;

			typedef typename InterimInterfaceType::InterimRegistrationType InterimRegistrationType;
			typedef typename InterimRegistrationType::Pointer          InterimRegistrationPointer;

			typedef typename InterimInterfaceType::MovingRepresentationDescriptorType
			MovingRepresentationDescriptorType;
			typedef typename InterimInterfaceType::TargetRepresentationDescriptorType
			TargetRepresentationDescriptorType;

			typedef typename InterimInterfaceType::OptimizerMeasureType OptimizerMeasureType;
			typedef typename RegistrationAlgorithmBase::AlgorithmType AlgorithmType;

			/*! @brief gets the registration result that has been computed in the last iteration.
			This interim registration may have other representation descriptors, passed as function
			arguments. Calls determineInterimRegistration to generate the registration.
			@param [in] pMovingRepresentation Pointer to the interim moving space representation descriptor.
			If pointer is NULL the default descriptor of the algorithm will be used.
			@param [in] pTargetRepresentation Pointer to the interim target space representation descriptor.
			If pointer is NULL the default descriptor of the algorithm will be used.
			@eguarantee strong
			@return the interim registration result as smart pointer. If the algorithm is not able to determine
			an interim registration, the smart pointer will point to NULL.
			@retval a Registration object
			@sa Registration
			*/
			virtual InterimRegistrationPointer getInterimRegistration(const MovingRepresentationDescriptorType*
					pMovingRepresentation = NULL,
					const TargetRepresentationDescriptorType* pTargetRepresentation = NULL) const;


			/*! @brief gets the current value/cost of the optimizer iteration of the registration algorithm
			@eguarantee strong
			@return returns the optimizers current value/cost
			*/
			virtual OptimizerMeasureType getCurrentOptimizerValue() const;

			virtual AlgorithmType getAlgorithmType() const;

			virtual bool stopAlgorithm();

		protected:

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
					const TargetRepresentationDescriptorType* pTargetRepresentation) const = 0;

			/*! Performes the computation of the registration.
			* First prepareAlgorithm() will be called, then the algorithm state will be changed to AlgorithmState::Running and runAlgorithm()
			* will be called. After runAlgorithm() is finished the state will be changed to AlgorithmState::Stopped and onAlgorithmStopped() will
			* be called.
			* @return Indicates of the registration was successfully determined (e.g. could be
			* false if an iterative algorithm was stopped prematurely by the user).
			* @remark To change the algorithmic behaviour you should overwrite prepareAlgorithm() or runAlgorithm().
			* This method should only be changed if you also want to change the state management of algorithms based on this class.
			* @eguarantee strong
			*/
			virtual bool doDetermineRegistration();

			/*! This method should do all preperation tasks right before the algorithms execution. At the and of this method
			* the algorithm should be set up and ready to use.
			* @remark If you want to change the execution style, then overwrite runAlgorithm().
			@eguarantee strong
			*/
			virtual void prepareAlgorithm() = 0;

			/*! This method should just execute the algorithm/iteration loop.
			* @remark If you want to change the initialization or the finalization, then overwrite prepareAlgorithm() or finalizeAlgorithm().
			* @return Indicates of the registration was successfully determined (e.g. could be
			* false if an iterative algorithm was stopped prematurely by the user).
			* @eguarantee strong
			*/
			virtual bool runAlgorithm() = 0;

			/*! This method should do all the finalization work (e.g. generating the registration based on the iteration results).
			* @remark If you want to change the initialization or the iteration, then overwrite prepareAlgorithm() or runAlgorithm().
			@eguarantee strong
			*/
			virtual void finalizeAlgorithm() = 0;

			/*! return the optimizer value(s) of the current iteration step.
			Will be called by getCurrentOptimizerValue() if hasCurrentValue() returns true.
			@eguarantee strong
			@return current measure
			*/
			virtual OptimizerMeasureType doGetCurrentOptimizerValue() const = 0;

			/*! Stops the algorithm. This is used by the default implementation of stopAlgorithm and should be implemented by derivating classes.
			  @eguarantee strong
			  @return returns the success of stopping
			  @retval true if algorithm has been successfully stopped
			  @retval false otherwise
			 */
			virtual bool doStopAlgorithm() = 0;

			IterativeRegistrationAlgorithm();
			virtual ~IterativeRegistrationAlgorithm();

			/*! Description of the reason/condition that lead to the last stopping of the algorithm.
			 * it is used by this class to fill the comment of the StopAlgorithmEvent. Derived classes
			 * my use this variable to specify the reason.\n
			 * An empty string indicates that either no run has terminated yet or that the reason was not
			 * specified.
			 * @remark This value should have only informative character and should not control or influence algorithmic or program
			 * behavior*/
			::map::core::String _stopConditionDescription;
		private:
			//No copy constructor allowed
			IterativeRegistrationAlgorithm(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

	}

}

#ifndef MatchPoint_MANUAL_TPP
#include "mapIterativeRegistrationAlgorithm.tpp"
#endif


#endif
