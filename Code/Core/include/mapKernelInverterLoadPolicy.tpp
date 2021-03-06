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


#ifndef __MAP_INVERTER_LOAD_POLICY_TPP
#define __MAP_INVERTER_LOAD_POLICY_TPP

#include "mapKernelInverterLoadPolicy.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"
#include "mapDefaultKernelInverter.h"
#include "mapNullRegistrationKernelInverter.h"

namespace map
{
	namespace core
	{


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		KernelInverterLoadPolicy<VInputDimensions, VOutputDimensions>::
		doLoading()
		{
        typedef DefaultKernelInverter<VInputDimensions, VOutputDimensions> DefaultKernelInverterType;
			typedef NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>
			NullRegistrationKernelInverterType;

      typename DefaultKernelInverterType::Pointer spDefaultInverter = DefaultKernelInverterType::New();
			typename NullRegistrationKernelInverterType::Pointer spNullnverter =
				NullRegistrationKernelInverterType::New();

			services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(Superclass::_pLoadInterface);

			if (!loader.addProviderByPolicy(spNullnverter))
			{
				mapLogWarningObjMacro("NullRegistrationKernelInverter was not added because it was already on the service stack!");
			}

      if (!loader.addProviderByPolicy(spDefaultInverter))
			{
				mapLogWarningObjMacro("DefaultKernelInverter was not added because it was already on the service stack!");
			}

		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		KernelInverterLoadPolicy<VInputDimensions, VOutputDimensions>::
		KernelInverterLoadPolicy() { }



		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		KernelInverterLoadPolicy<VInputDimensions, VOutputDimensions>::
		~KernelInverterLoadPolicy() { }


	} // end namespace core
} // end namespace map

#endif
