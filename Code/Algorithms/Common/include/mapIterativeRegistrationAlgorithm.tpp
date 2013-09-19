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


#ifndef __ITERATIVE_REGISTRATION_ALGORITHM_TPP
#define __ITERATIVE_REGISTRATION_ALGORITHM_TPP

#include "mapAlgorithmStateChangeEvent.h"

namespace map
{
	namespace algorithm
	{

		// **** public methods ****
		// ************************
		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		typename IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::InterimRegistrationPointer
		IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getInterimRegistration(const MovingRepresentationDescriptorType* pMovingRepresentation,
							   const TargetRepresentationDescriptorType* pTargetRepresentation) const
		{
			const MovingRepresentationDescriptorType* pInterimMovingRepresentation = pMovingRepresentation;
			const TargetRepresentationDescriptorType* pInterimTargetRepresentation = pTargetRepresentation;

			if (!pInterimMovingRepresentation)
			{
				pInterimMovingRepresentation = this->getMovingRepresentation();
			}

			if (!pInterimTargetRepresentation)
			{
				pInterimTargetRepresentation = this->getTargetRepresentation();
			}

			return determineInterimRegistration(pInterimMovingRepresentation, pInterimTargetRepresentation);
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		typename IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::AlgorithmType
		IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getAlgorithmType() const
		{
			return RegistrationAlgorithmBase::ATIterative;
		};

		// **** protected methods ****
		// ***************************
		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		IterativeRegistrationAlgorithm()
		{
		}

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		~IterativeRegistrationAlgorithm()
		{
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		bool
		IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		doDetermineRegistration()
		{
			bool resultAvailable = true;
			bool iterationSuccess = false;

			this->setCurrentState(Superclass::AlgorithmState::Initializing);
			this->InvokeEvent(events::InitializingAlgorithmEvent());

			try
			{
				this->prepareAlgorithm();
			}
			catch (...)
			{
				this->setCurrentState(Superclass::AlgorithmState::Pending);
				throw;
			}

			if (Superclass::AlgorithmState::Stopping != this->getCurrentState())
			{
				//go on with the algorithm
				this->setCurrentState(Superclass::AlgorithmState::Running);
				this->InvokeEvent(events::StartingAlgorithmEvent());

				try
				{
					iterationSuccess = this->runAlgorithm();
				}
				catch (...)
				{
					this->setCurrentState(Superclass::AlgorithmState::Pending);
					throw;
				}
			}

			if ((this->getCurrentState() == Superclass::AlgorithmState::Stopping) || !iterationSuccess)
			{
				//stopped, by user interaction
				this->setCurrentState(Superclass::AlgorithmState::Stopped);
				this->InvokeEvent(events::StoppedAlgorithmEvent(NULL, "aborted by user"));
				resultAvailable = false;
			}
			else
			{
				//normal termination of the algorithm -> finalize
				this->setCurrentState(Superclass::AlgorithmState::Stopped);
				this->InvokeEvent(events::StoppedAlgorithmEvent(NULL, _stopConditionDescription));

				this->setCurrentState(Superclass::AlgorithmState::Finalizing);
				this->InvokeEvent(events::FinalizingAlgorithmEvent());

				try
				{
					this->finalizeAlgorithm();
				}
				catch (...)
				{
					this->setCurrentState(Superclass::AlgorithmState::Stopped);
					throw;
				}

				this->setCurrentState(Superclass::AlgorithmState::Finalized);
				this->InvokeEvent(events::FinalizedAlgorithmEvent());

				resultAvailable = true;
			}

			return resultAvailable;
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		typename IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::OptimizerMeasureType
		IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getCurrentOptimizerValue() const
		{
			OptimizerMeasureType result;

			if (this->hasCurrentOptimizerValue())
			{
				result = this->doGetCurrentOptimizerValue();
			}

			return result;
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		bool
		IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		stopAlgorithm()
		{
			bool result = false;

			if (this->getCurrentState() == Superclass::AlgorithmState::Initializing ||
				this->getCurrentState() == Superclass::AlgorithmState::Running)
			{
				result = doStopAlgorithm();

				if (result)
				{
					this->setCurrentState(Superclass::AlgorithmState::Stopping);
				}
			}
			else if (this->getCurrentState() == Superclass::AlgorithmState::Stopping ||
					 this->getCurrentState() == Superclass::AlgorithmState::Stopped ||
					 this->getCurrentState() == Superclass::AlgorithmState::Finalizing ||
					 this->getCurrentState() == Superclass::AlgorithmState::Finalized)
			{
				result = true;
			}

			return result;
		};

	} // end namespace algorithm
} // end namespace map

#endif
