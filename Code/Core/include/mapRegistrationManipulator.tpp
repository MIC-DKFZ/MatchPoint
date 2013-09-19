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


#ifndef __REGISTRATION_MANIPULATOR_TPP
#define __REGISTRATION_MANIPULATOR_TPP

#include "mapRegistrationManipulator.h"

namespace map
{
	namespace core
	{

		template<typename TRegistration>
		void
		RegistrationManipulator<TRegistration>::
		setDirectMapping(typename RegistrationType::DirectMappingType* pKernel)
		{
			_pInterface->setDirectMapping(pKernel);
		};

		template<typename TRegistration>
		void
		RegistrationManipulator<TRegistration>::
		setInverseMapping(typename RegistrationType::InverseMappingType* pKernel)
		{
			_pInterface->setInverseMapping(pKernel);
		};

		template<typename TRegistration>
		void
		RegistrationManipulator<TRegistration>::
		setTagValues(const TagMapType& tags)
		{
			_pInterface->setTagValues(tags);
		};

		template<typename TRegistration>
		typename RegistrationManipulator<TRegistration>::TagMapType&
		RegistrationManipulator<TRegistration>::
		getTagValues()
		{
			return _pInterface->getTagValues();
		};

		template<typename TRegistration>
		RegistrationManipulator<TRegistration>::
		RegistrationManipulator(RegistrationType* pI): _pInterface(pI)
		{
			assert(pI);
		};

	} // end namespace core
} // end namespace map

#endif
