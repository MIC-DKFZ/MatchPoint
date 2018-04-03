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


#ifndef __MAP_NONE_STATIC_LOAD_POLICY_H
#define __MAP_NONE_STATIC_LOAD_POLICY_H

namespace map
{
	namespace core
	{
		namespace services
		{
			//forward declaration
			template <class TProviderBase>
			class ServiceRepositoryPolicyLoadInterface;

			/*! @class NoneStaticLoadPolicy
			* @brief Loading policy with no default provider.
			*
			* This policy loads nothing, therefore a repository using this policy has no default providers.
			*
			* @ingroup LoadPolicies
			* @tparam TProviderBase Base class of the service providers loaded by the policy.
			*/
			template <class TProviderBase>
			class NoneStaticLoadPolicy
			{
			protected:
				/*! Standard class typedefs. */
				typedef ServiceRepositoryPolicyLoadInterface<TProviderBase> LoadInterfaceType;
				typedef TProviderBase                           ProviderBaseType;
				typedef typename ProviderBaseType::Pointer      ProviderBasePointer;

				/*! Loading of all default providers.
				 * @eguarantee basic
				 */
				void loadStaticProviders();

				/*! Registers the loading interface that should be used by the policy.
				 * @eguarantee strong
				 * @param [in] interface Reference to the interface that should used by the policy when
				 * loading providers.
				 */
				void registerInterfaceForStaticLoading(LoadInterfaceType& loadInterface);

				NoneStaticLoadPolicy();
				~NoneStaticLoadPolicy();

			private:
				typedef NoneStaticLoadPolicy<TProviderBase> Self;
				NoneStaticLoadPolicy(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapNoneStaticLoadPolicy.tpp"
#endif

#endif
