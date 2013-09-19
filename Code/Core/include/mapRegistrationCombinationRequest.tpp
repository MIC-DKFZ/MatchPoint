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

#ifndef __MAP_REGISTRATION_COMBINATION_REQUEST_TPP
#define __MAP_REGISTRATION_COMBINATION_REQUEST_TPP

#include "mapRegistrationCombinationRequest.h"

namespace map
{
	namespace core
	{

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		RegistrationCombinationRequest<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		RegistrationCombinationRequest(const Kernel1BaseType* pKernel1, const Kernel2BaseType* pKernel2):
			_spKernel1(pKernel1), _spKernel2(pKernel2)
		{
			assert(pKernel1);
			assert(pKernel2);
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		RegistrationCombinationRequest<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		RegistrationCombinationRequest(const Kernel1BaseType& kernel1, const Kernel2BaseType& kernel2):
			_spKernel1(&kernel1), _spKernel2(&kernel2)
		{
		};

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		RegistrationCombinationRequest<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		~RegistrationCombinationRequest()
		{
			// intentionally left blank
		}


		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		RegistrationCombinationRequest<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		RegistrationCombinationRequest(const RegistrationCombinationRequest& req):
			_spKernel1(req._spKernel1), _spKernel2(req._spKernel2)
		{
			assert(_spKernel1.IsNotNull());
			assert(_spKernel2.IsNotNull());
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		void
		RegistrationCombinationRequest<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		operator=(const RegistrationCombinationRequest& req)
		{
			if (&req != this)
			{
				_spKernel1 = req._spKernel1;
				_spKernel2 = req._spKernel2;
			}
		}


	} // end namespace core
} // end namespace map

#endif
