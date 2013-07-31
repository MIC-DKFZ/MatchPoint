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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapPointSetMappingPerformerLoadPolicy.tpp $
*/


#ifndef __MAP_POINT_MAPPING_PERFORMER_LOAD_POLICY_TPP
#define __MAP_POINT_MAPPING_PERFORMER_LOAD_POLICY_TPP

#include "mapPointSetMappingPerformerLoadPolicy.h"

#include "mapPointSetByModelPerformer.h"
#include "mapPointSetByFieldPerformer.h"

namespace map
{
	namespace core
	{
		template <class TProviderBase>
		void
		PointSetMappingPerformerLoadPolicy<TProviderBase>::
		doLoading()
		{
			typedef PointSetByModelPerformer<typename ProviderBaseType::RegistrationType, typename ProviderBaseType::InputDataType, typename ProviderBaseType::ResultDataType> PointSetByModelPerformerType;
			typedef PointSetByFieldPerformer<typename ProviderBaseType::RegistrationType, typename ProviderBaseType::InputDataType, typename ProviderBaseType::ResultDataType> PointSetByFieldPerformerType;

			typename PointSetByModelPerformerType::Pointer spModelPerformer = PointSetByModelPerformerType::New();
			typename PointSetByFieldPerformerType::Pointer spFieldPerformer = PointSetByFieldPerformerType::New();

			services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(Superclass::_pLoadInterface);

			if (!loader.addProviderByPolicy(spModelPerformer))
			{
				mapLogWarningObjMacro("PointSetByModelPerformer was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(spFieldPerformer))
			{
				mapLogWarningObjMacro("PointSetByFieldPerformer was not added because it was already on the service stack!");
			}
		};

		template <class TProviderBase>
		PointSetMappingPerformerLoadPolicy<TProviderBase>::
		PointSetMappingPerformerLoadPolicy()
		{
		};

		template <class TProviderBase>
		PointSetMappingPerformerLoadPolicy<TProviderBase>::
		~PointSetMappingPerformerLoadPolicy()
		{
		};

	} // end namespace core
} // end namespace map

#endif
