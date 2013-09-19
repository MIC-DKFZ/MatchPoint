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


#ifndef __MAP_GERNERIC_STATIC_LOAD_POLICY_BASE_H
#define __MAP_GERNERIC_STATIC_LOAD_POLICY_BASE_H

namespace map
{
	namespace core
	{
		namespace services
		{
			//forward declaration
			template <class TProviderBase>
			class ServiceRepositoryPolicyLoadInterface;

			/*! @class GenericStaticLoadPolicyBase
			* @brief Base class of a policy with default providers.
			*
			* You can design a loading policy from scratch but if you just want to load a certain number
			* of default providers in a special sequenze, this is the easiest way. Deriver from this class and
			* override doLoading().
			*
			* @ingroup LoadPolicies
			* @tparam TProviderBase Base class of the service providers loaded by the policy.
			*/
			template <class TProviderBase>
			class GenericStaticLoadPolicyBase
			{
			protected:
				/*! Standard class typedefs. */
				typedef ServiceRepositoryPolicyLoadInterface<TProviderBase> LoadInterfaceType;
				typedef TProviderBase                               ProviderBaseType;
				typedef typename ProviderBaseType::Pointer          ProviderBasePointer;
				typedef GenericStaticLoadPolicyBase<TProviderBase>  Self;

				/*! Loading of all default providers by calling doLoading.
				 * Before this call it will be checked if the interface has been registered
				 * @pre Loading interface must have been registered.
				 * @eguarantee basic
				 */
				void loadStaticProviders();

				/*! Registers the loading interface that should be used by the policy.
				 * @eguarantee strong
				 * @param [in] interface Reference to the interface that should used by the policy when
				 * loading providers.
				 */
				void registerInterfaceForStaticLoading(LoadInterfaceType& loadInterface);

				/*! This method should be overwritten in derived classes to realize the loading
						 * of default providers via the registered interface (_pLoadInterface). The interface is guaranteed to be set
						 * when the method is called.
						 * @pre _pLoadInterface is set to an interface instance by LoadStaticProviders*/;
				virtual void doLoading() = 0;

				/*! Pointer to the load interface*/
				LoadInterfaceType* _pLoadInterface;

				GenericStaticLoadPolicyBase();
				~GenericStaticLoadPolicyBase();

			private:
				GenericStaticLoadPolicyBase(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapGenericStaticLoadPolicyBase.tpp"
#endif

#endif
