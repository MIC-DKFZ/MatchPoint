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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapPointSetMappingPerformerRequest.tpp $
*/


#ifndef __MAP_POINTSET_MAPPING_PERFORMER_REQUEST_TPP
#define __MAP_POINTSET_MAPPING_PERFORMER_REQUEST_TPP

#include "mapPointSetMappingPerformerRequest.h"

namespace map
{
	namespace core
	{

		template <class TRegistration, class TInputData, class TResultData>
		PointSetMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		PointSetMappingPerformerRequest(const RegistrationType *pRegistration, const InputDataType *pInputData, bool throwOnMappingError, const ErrorPointValueType &errorValue):
			Superclass(pRegistration, pInputData), _throwOnMappingError(throwOnMappingError), _errorValue(errorValue)
		{}


		template <class TRegistration, class TInputData, class TResultData>
		PointSetMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		~PointSetMappingPerformerRequest()
		{ }

		template <class TRegistration, class TInputData, class TResultData>
		PointSetMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		PointSetMappingPerformerRequest(const PointSetMappingPerformerRequest &other):
			Superclass(other._spRegistration, other._spInputData), _throwOnMappingError(other._throwOnMappingError), _errorValue(other._errorValue)
		{
			assert(other._spRegistration.IsNotNull());
			assert(other._spInputData.IsNotNull());
		}

		template <class TRegistration, class TInputData, class TResultData>
		void
		PointSetMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		operator=(const PointSetMappingPerformerRequest &other)
		{
			Superclass::_spRegistration = other._spRegistration;
			Superclass::_spInputData = other._spInputData;
			_throwOnMappingError = other._throwOnMappingError;
			_errorValue = other._errorValue;
			assert(Superclass::_spRegistration.IsNotNull());
			assert(Superclass::_spInputData.IsNotNull());
		}


	} // end namespace core
} // end namespace map

#endif
