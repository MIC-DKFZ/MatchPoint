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


#ifndef __MAP_MAPPING_PERFORMER_REQUEST_BASE_TPP
#define __MAP_MAPPING_PERFORMER_REQUEST_BASE_TPP

#include "mapMappingPerformerRequestBase.h"
#include <assert.h>

namespace map
{
	namespace core
	{

		// Diese Datei ist ein Stub und muss noch ausimplementiert werden.

		template <class TRegistration, class TInputData, class TResultData>
		MappingPerformerRequestBase<TRegistration, TInputData, TResultData>::
		MappingPerformerRequestBase(const RegistrationType& registration, const InputDataType& inputData):
			_spRegistration(&registration), _spInputData(&inputData)
		{}

		template <class TRegistration, class TInputData, class TResultData>
		MappingPerformerRequestBase<TRegistration, TInputData, TResultData>::
		MappingPerformerRequestBase(const RegistrationType* pRegistration, const InputDataType* pInputData):
			_spRegistration(pRegistration), _spInputData(pInputData)
		{
			assert(pRegistration);
			assert(pInputData);
		}

		template <class TRegistration, class TInputData, class TResultData>
		MappingPerformerRequestBase<TRegistration, TInputData, TResultData>::
		~MappingPerformerRequestBase()
		{}


	} // end namespace core
} // end namespace map

#endif
