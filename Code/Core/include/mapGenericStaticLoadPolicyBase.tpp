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


#ifndef __MAP_GERNERIC_STATIC_LOAD_POLICY_BASE_TPP
#define __MAP_GERNERIC_STATIC_LOAD_POLICY_BASE_TPP

#include "mapGenericStaticLoadPolicyBase.h"
#include "mapConfigure.h"

#include <cassert>

namespace map
{
	namespace core
	{
		namespace services
		{

			/*! Loading of all default providers by calling doLoading.
			* Before this call it will be checked if the interface has been registered
			* @pre Loading interface must have been registered.
			* @eguarantee basic
			*/
			template <class TProviderBase>
			void
			GenericStaticLoadPolicyBase<TProviderBase>::
			loadStaticProviders()
			{
				assert(_pLoadInterface != nullptr);
				doLoading();
			};

			/*! Registers the loading interface that should be used by the policy.
			* @eguarantee strong
			* @param [in] interface Reference to the interface that should used by the policy when
			* loading providers.
			*/
			template <class TProviderBase>
			void
			GenericStaticLoadPolicyBase<TProviderBase>::
			registerInterfaceForStaticLoading(LoadInterfaceType& loadInterface)
			{
				_pLoadInterface = &loadInterface;
			};

			template <class TProviderBase>
			GenericStaticLoadPolicyBase<TProviderBase>::
			GenericStaticLoadPolicyBase()
			= default;

			template <class TProviderBase>
			GenericStaticLoadPolicyBase<TProviderBase>::
			~GenericStaticLoadPolicyBase()
			= default;

		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
