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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapNoneStaticLoadPolicy.tpp $
*/


#ifndef __MAP_NONE_STATIC_LOAD_POLICY_TPP
#define __MAP_NONE_STATIC_LOAD_POLICY_TPP

#include "mapNoneStaticLoadPolicy.h"

namespace map
{
	namespace core
	{
		namespace services
		{

			template <class TProviderBase>
			void
			NoneStaticLoadPolicy<TProviderBase>::
			loadStaticProviders()
			{
				//nothing to load;
			};

			template <class TProviderBase>
			void
			NoneStaticLoadPolicy<TProviderBase>::
			registerInterfaceForStaticLoading(LoadInterfaceType &loadInterface)
			{
				//we don't need an interface
			};

			template <class TProviderBase>
			NoneStaticLoadPolicy<TProviderBase>::
			NoneStaticLoadPolicy()
			{
			};

			template <class TProviderBase>
			NoneStaticLoadPolicy<TProviderBase>::
			~NoneStaticLoadPolicy()
			{
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
