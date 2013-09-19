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


#ifndef __MAP_POINTSET_MAPPING_PERFORMER_REQUEST_H
#define __MAP_POINTSET_MAPPING_PERFORMER_REQUEST_H

#include "mapMappingPerformerRequestBase.h"
#include <ostream>


namespace map
{
	namespace core
	{
		/*! @class PointSetMappingPerformerRequest
		* This class is used by MappingPerformer for requests dealing with pointsets.
		* @ingroup MappingTask
		* @sa MappingPerformerBase
		* @sa PointMappingPerformerBase
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputData Type of the input data.
			* @tparam TResultData Type of the data in the target space.
		*/
		template <class TRegistration, class TInputData, class TResultData>
		class PointSetMappingPerformerRequest: public
			MappingPerformerRequestBase<TRegistration, TInputData, TResultData>
		{
		public:
			typedef MappingPerformerRequestBase<TRegistration, TInputData, TResultData> Superclass;

			typedef typename Superclass::ResultDataType ResultDataType;
			typedef typename Superclass::RegistrationType RegistrationType;
			typedef typename Superclass::InputDataType InputDataType;
			typedef typename ResultDataType::PixelType ErrorPointValueType;

			PointSetMappingPerformerRequest(const RegistrationType* pRegistration,
											const InputDataType* pInputData, bool throwOnMappingError, const ErrorPointValueType& errorValue);
			virtual ~PointSetMappingPerformerRequest();

			PointSetMappingPerformerRequest(const PointSetMappingPerformerRequest&);

			void operator=(const PointSetMappingPerformerRequest&);

			bool _throwOnMappingError;
			ErrorPointValueType _errorValue;
		};

		template <class TRegistration, class TInputData, class TResultData>
		std::ostream& operator<<(std::ostream& os,
								 const PointSetMappingPerformerRequest<TRegistration, TInputData, TResultData>& request)
		{
			os << "Registration: ";

			if (request._spRegistration.IsNull())
			{
				os << "NULL" << std::endl;
			}
			else
			{
				os << request._spRegistration << std::endl;
			};

			os << "Input data: ";

			if (request._spInputData.IsNull())
			{
				os << "NULL" << std::endl;
			}
			else
			{
				os << request._spInputData << std::endl;
			};

			os << "ThrowOnMappingError: " << request._throwOnMappingError << std::endl;

			os << "Error value: " << request._errorValue << std::endl;

			return os;
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapPointSetMappingPerformerRequest.tpp"
#endif

#endif
