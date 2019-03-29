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


#ifndef __MAP_IMAGE_MAPPING_PERFORMER_LOAD_POLICY_H
#define __MAP_IMAGE_MAPPING_PERFORMER_LOAD_POLICY_H

# include "mapGenericStaticLoadPolicyBase.h"

namespace map
{
	namespace core
	{
		/*! @class ImageMappingPerformerLoadPolicy
		* @brief Load class used by ImageMappingTask to populate its service stack.
		*
		* It loads the following providers:
		* - ImageByModelPerformer
		* - ImageByFieldPerformer
		* .
		*
		* @ingroup LoadPolicies
		* @ingroup RegTasks
		* @sa ImageMappingTask
		* @tparam TProviderBase Base class of the service providers loaded by the policy.
		*/
		template <class TProviderBase>
		class ImageMappingPerformerLoadPolicy : public services::GenericStaticLoadPolicyBase<TProviderBase>
		{
		protected:
			/*! Standard class typedefs. */
			using Superclass = services::GenericStaticLoadPolicyBase<TProviderBase>;
			using ProviderBaseType = typename Superclass::ProviderBaseType;
			using ProviderBasePointer = typename Superclass::ProviderBasePointer;
			using LoadInterfaceType = typename Superclass::LoadInterfaceType;

			void doLoading() override;

			ImageMappingPerformerLoadPolicy();
			~ImageMappingPerformerLoadPolicy();

		private:
			ImageMappingPerformerLoadPolicy(const
											ImageMappingPerformerLoadPolicy&) = delete;  //purposely not implemented
			void operator=(const ImageMappingPerformerLoadPolicy&) = delete;  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapImageMappingPerformerLoadPolicy.tpp"
#endif

#endif
