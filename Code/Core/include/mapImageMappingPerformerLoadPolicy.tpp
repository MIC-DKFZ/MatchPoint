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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapImageMappingPerformerLoadPolicy.tpp $
*/


#ifndef __MAP_IMAGE_MAPPING_PERFORMER_LOAD_POLICY_TPP
#define __MAP_IMAGE_MAPPING_PERFORMER_LOAD_POLICY_TPP

#include "mapImageMappingPerformerLoadPolicy.h"

#include "mapImageByModelPerformer.h"
#include "mapImageByFieldPerformer.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"

namespace map
{
	namespace core
	{

		template <class TProviderBase>
		void
		ImageMappingPerformerLoadPolicy<TProviderBase>::
		doLoading()
		{
			typedef ImageByModelPerformer<typename ProviderBaseType::RegistrationType, typename ProviderBaseType::InputDataType, typename ProviderBaseType::ResultDataType> ImageByModelPerformerType;
			typedef ImageByFieldPerformer<typename ProviderBaseType::RegistrationType, typename ProviderBaseType::InputDataType, typename ProviderBaseType::ResultDataType> ImageByFieldPerformerType;

			typename ImageByModelPerformerType::Pointer spModelPerformer = ImageByModelPerformerType::New();
			typename ImageByFieldPerformerType::Pointer spFieldPerformer = ImageByFieldPerformerType::New();

			services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(Superclass::_pLoadInterface);

			if (!loader.addProviderByPolicy(spModelPerformer))
			{
				mapLogWarningObjMacro("ImageByModelPerformer was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(spFieldPerformer))
			{
				mapLogWarningObjMacro("ImageByFieldPerformer was not added because it was already on the service stack!");
			}
		}

		template <class TProviderBase>
		ImageMappingPerformerLoadPolicy<TProviderBase>::
		ImageMappingPerformerLoadPolicy()
		{
		}

		template <class TProviderBase>
		ImageMappingPerformerLoadPolicy<TProviderBase>::
		~ImageMappingPerformerLoadPolicy()
		{
		}


	} // end namespace core
} // end namespace map

#endif
