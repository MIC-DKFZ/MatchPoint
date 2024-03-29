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


#ifndef __REGISTRATION_ALGORITHM_TPP
#define __REGISTRATION_ALGORITHM_TPP

#include "mapRegistrationAlgorithm.h"
#include "mapAlgorithmEvents.h"
#include "mapLogbookMacros.h"

#include <mutex>

namespace map
{
	namespace algorithm
	{

		// **** public methods ****
		// ************************

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		unsigned int
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getMovingDimensions() const
		{
			return VMovingDimensions;
		}

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		unsigned int
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getTargetDimensions() const
		{
			return VTargetDimensions;
		}

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		typename RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::RegistrationPointer
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getRegistration()
		{
			this->_determinationLock.lock();

			try
			{
				if (registrationIsOutdated())
				{
					mapLogInfoMacro( << "Registration is outdated. Redetermine registration.");
					this->InvokeEvent(::map::events::AlgorithmEvent(this,
									  "Registration is outdated. Redetermine registration."));
					doDetermineRegistration();
				}
			}
			catch (...)
			{
				this->_determinationLock.unlock();
				throw;
			}

			this->_determinationLock.unlock();

			return doGetRegistration();
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		const typename
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::MovingRepresentationDescriptorType*
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getMovingRepresentation() const
		{
			this->doBeforeGetMovingRepresentation();
			return _spMovingRepresentation;
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		setMovingRepresentation(const MovingRepresentationDescriptorType* pDescriptor)
		{
			if (_spMovingRepresentation.GetPointer() != pDescriptor)
			{
				this->doBeforeSetMovingRepresentation(pDescriptor);
				this->Modified();
				this->_spMovingRepresentation = pDescriptor;
				this->doAfterSetMovingRepresentation();
			}
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		const typename
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::TargetRepresentationDescriptorType*
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		getTargetRepresentation() const
		{
			this->doBeforeGetTargetRepresentation();
			return _spTargetRepresentation;
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		setTargetRepresentation(const TargetRepresentationDescriptorType* pDescriptor)
		{
			if (_spTargetRepresentation.GetPointer() != pDescriptor)
			{
				this->doBeforeSetTargetRepresentation(pDescriptor);
				this->Modified();
				this->_spTargetRepresentation = pDescriptor;
				this->doAfterSetTargetRepresentation();
			}
		};

		// **** protected methods ****
		// ***************************

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		bool
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		registrationIsOutdated() const
		{
			bool result = doGetRegistration().IsNull();
			return result;
		};


		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		RegistrationAlgorithm()
		{
			_spMovingRepresentation = nullptr;
			_spTargetRepresentation = nullptr;
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		~RegistrationAlgorithm() = default;

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		doBeforeSetMovingRepresentation(const MovingRepresentationDescriptorType* pMovingRepresentation)
		{
			//default implementation does nothing
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		doAfterSetMovingRepresentation()
		{
			//default implementation does nothing
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		doBeforeSetTargetRepresentation(const TargetRepresentationDescriptorType* pTargetRepresentation)
		{
			//default implementation does nothing
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		doAfterSetTargetRepresentation()
		{
			//default implementation does nothing
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		doBeforeGetMovingRepresentation() const
		{
			//default implementation does nothing
		};

		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		void
		RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>::
		doBeforeGetTargetRepresentation() const
		{
			//default implementation does nothing
		};

	} // end namespace algorithm
} // end namespace map

#endif
