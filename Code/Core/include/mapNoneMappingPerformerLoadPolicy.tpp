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


#ifndef __MAP_NONE_MAPPING_PERFORMER_LOAD_POLICY_TPP
#define __MAP_NONE_MAPPING_PERFORMER_LOAD_POLICY_TPP

#include "mapNoneMappingPerformerLoadPolicy.h"

namespace map
{
	namespace core
	{
		template <class TProviderBase>
		void
		NoneMappingPerformerLoadPolicy<TProviderBase>::
		doLoading()
		{
		};

		template <class TProviderBase>
		NoneMappingPerformerLoadPolicy<TProviderBase>::
		NoneMappingPerformerLoadPolicy()
		{
		};

		template <class TProviderBase>
		NoneMappingPerformerLoadPolicy<TProviderBase>::
		~NoneMappingPerformerLoadPolicy()
		{
		};

	} // end namespace core
} // end namespace map

#endif
