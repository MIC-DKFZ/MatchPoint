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


#ifndef __MAP_IMAGE_MAPPING_PERFORMER_REQUEST_TPP
#define __MAP_IMAGE_MAPPING_PERFORMER_REQUEST_TPP

#include "mapImageMappingPerformerRequest.h"

namespace map
{
	namespace core
	{
		template <class TRegistration, class TInputData, class TResultData>
		ImageMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		ImageMappingPerformerRequest(const RegistrationType* pRegistration,
									 const InputDataType* pInputData, const ResultImageDescriptorType* pResultDescriptor,
									 InterpolateBaseType* pInterpolateFunction,
									 bool throwOnMappingError, const ErrorValueType& errorValue,
									 bool throwOnOutOfInputAreaError, PaddingValueType paddingValue):
			Superclass(pRegistration, pInputData), _spResultDescriptor(pResultDescriptor),
			_spInterpolateFunction(pInterpolateFunction),
			_throwOnMappingError(throwOnMappingError), _errorValue(errorValue),
			_throwOnOutOfInputAreaError(throwOnOutOfInputAreaError), _paddingValue(paddingValue)
		{
			assert(pResultDescriptor);
			assert(pInterpolateFunction);
		}

		template <class TRegistration, class TInputData, class TResultData>
		ImageMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		~ImageMappingPerformerRequest()
		= default;

		template <class TRegistration, class TInputData, class TResultData>
		ImageMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		ImageMappingPerformerRequest(const ImageMappingPerformerRequest& other):
			Superclass(other._spRegistration, other._spInputData),
			_spResultDescriptor(other._spResultDescriptor),
			_spInterpolateFunction(other._spInterpolateFunction),
			_throwOnMappingError(other._throwOnMappingError), _errorValue(other._errorValue),
			_throwOnOutOfInputAreaError(other._throwOnOutOfInputAreaError), _paddingValue(other._paddingValue)
		{
			assert(other._spRegistration.IsNotNull());
			assert(other._spInputData.IsNotNull());
			assert(other._spResultDescriptor.IsNotNull());
			assert(other._spInterpolateFunction);
		}

		template <class TRegistration, class TInputData, class TResultData>
		void
		ImageMappingPerformerRequest<TRegistration, TInputData, TResultData>::
		operator=(const ImageMappingPerformerRequest& other)
		{
			Superclass::_spRegistration = other._spRegistration;
			Superclass::_spInputData = other._spInputData;
			_spResultDescriptor = other._spResultDescriptor;
			_spInterpolateFunction = other._spInterpolateFunction;

			_throwOnMappingError = other._throwOnMappingError;
			_errorValue = other._errorValue;
			_throwOnOutOfInputAreaError = other._throwOnOutOfInputAreaError;
			_paddingValue = other._paddingValue;
			assert(Superclass::_spRegistration.IsNotNull());
			assert(Superclass::_spInputData.IsNotNull());
			assert(_spResultDescriptor.IsNotNull());
			assert(_spInterpolateFunction.IsNotNull());
		}


	} // end namespace core
} // end namespace map

#endif
