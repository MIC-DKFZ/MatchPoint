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

#ifndef __MAP_REGISTRATION_COMBINATION_REQUEST_H
#define __MAP_REGISTRATION_COMBINATION_REQUEST_H

#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace core
	{
		/*! @class RegistrationCombinationRequest
		* @brief Request class used by RegistrationCombinator.
		*
		* This class is used as request type for the provider stack of RegistrationCombinator
		* @ingroup RegOperation
		* @sa RegistrationCombinator
			* @tparam VInputDimensions Dimensions of the input space of the  first kernel.
			* @tparam VInterimDimensions Dimensions of the output space of the first kernel and the input space of the second.
			* @tparam VOutputDimensions Dimensions of the output space of the second kernel.
			*/
		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		class RegistrationCombinationRequest
		{
		public:
			typedef RegistrationKernelBase<VInputDimensions, VInterimDimensions> Kernel1BaseType;
			using Kernel1BaseConstPointer = typename Kernel1BaseType::ConstPointer;

			typedef RegistrationKernelBase<VInterimDimensions, VOutputDimensions> Kernel2BaseType;
			using Kernel2BaseConstPointer = typename Kernel2BaseType::ConstPointer;

			Kernel1BaseConstPointer _spKernel1;
			Kernel2BaseConstPointer _spKernel2;

			/*! Constructor
			 * \pre pKernel1 and pKernel2 must not be NULL*/
			RegistrationCombinationRequest(const Kernel1BaseType* pKernel1, const Kernel2BaseType* pKernel2);
			RegistrationCombinationRequest(const Kernel1BaseType& kernel1, const Kernel2BaseType& kernel2);
			~RegistrationCombinationRequest();

			RegistrationCombinationRequest(const RegistrationCombinationRequest& /*req*/);
			void operator=(const RegistrationCombinationRequest& /*req*/);
		};

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		std::ostream& operator<<(std::ostream& os,
								 const RegistrationCombinationRequest<VInputDimensions, VInterimDimensions, VOutputDimensions>&
								 request)
		{
			os << "Kernel1: " << request._spKernel1 << std::endl;
			os << "Kernel2: " << request._spKernel2 << std::endl;
			return os;
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapRegistrationCombinationRequest.tpp"
#endif

#endif
