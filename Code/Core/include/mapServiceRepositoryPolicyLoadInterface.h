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

#ifndef __MAP_SERVICE_REPOSITORY_POLICY_LOAD_INTERFACE_H
#define __MAP_SERVICE_REPOSITORY_POLICY_LOAD_INTERFACE_H

#include "itkObject.h"
#include <assert.h>

namespace map
{
	namespace core
	{
		namespace services
		{

			//forward decleration
			template <class TInterface>
			class ServiceRepositoryPolicyLoader;

			/*! @class ServiceRepositoryPolicyLoadInterface
			* @brief Interface for repositories that load service providers via policies.
			*
			* @ingroup Services
			* @tparam TProviderBase Base class of the service providers that should be loaded.
			* must be based on ServicProvider
			*/
			template <class TProviderBase>
			class ServiceRepositoryPolicyLoadInterface
			{
			protected:
				typedef ServiceRepositoryPolicyLoadInterface<TProviderBase> Self;
				friend class ServiceRepositoryPolicyLoader<Self>;

				typedef TProviderBase  ProviderBaseType;

				/*! Registers a given provider in the stack. The new provider will be topmost and therfore
				 * will be favored over providers registered ealier. The stack will behave like a smartpointer
				 * for the registered provider, thus as long as a provider is registered he won't be deleted.
				 * An instance of a provider (identified via pointer) can only added once to the stack. If the instance
				 * is already on the stack, the stack will stay unchanged.
				 * \n Function is supposed to be used by loading policies of the repository (e.g. stack).
				 * @eguarantee strong
				 * @param [in] pProvider Pointer to the provider that should be added.
				 * @return Boolean that indicates if the provider (identified by provider name) has been added.
				 * @retval true The provider was added as topmost element to the stack.
				 * @retval false The provider was already on the stack. Stack is unchanged.
				 * @post Stack is unchanged or added provider is the topmost element on the stack.
				 */
				virtual bool addProviderByPolicy(ProviderBaseType* pProvider) = 0;

				/*! Removes the provider (identified by the pointer address) from the stack.
				 * \n Function is supposed to be used by loading policies of the repository (e.g. stack).
				 * @eguarantee strong
				 * @param [in] pProvider Pointer to the provider that should be removed from stack.
				 * @return Boolean that indicates if there was a provider (identified by pointer)
				 * on the stack.
				 * @retval true The provider instance was on the stack and was removed.
				 * @retval false The provider instance is not a part of the stack.
				 */
				virtual bool removeProviderByPolicy(ProviderBaseType* pProvider) = 0;

			protected:
				ServiceRepositoryPolicyLoadInterface() {};
				virtual ~ServiceRepositoryPolicyLoadInterface() {};

			private:
				ServiceRepositoryPolicyLoadInterface(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};


			/*! @class ServiceRepositoryPolicyLoader
			* @brief Helper class to access the ServiceRepositoryPolicyLoadInterface methods
			* of any class that implements these methods.
			* @sa ServiceRepositoryPolicyLoader
			* @ingroup Services
			* @tparam TInterface Interface the loader should interact with.
			*/
			template <class TInterface>
			class ServiceRepositoryPolicyLoader
			{
			public:
				typedef TInterface InterfaceType;
				typedef typename InterfaceType::ProviderBaseType  ProviderBaseType;

				virtual bool addProviderByPolicy(ProviderBaseType* pProvider)
				{
					return _pInterface->addProviderByPolicy(pProvider);
				};

				virtual bool removeProviderByPolicy(ProviderBaseType* pProvider)
				{
					return _pInterface->removeProviderByPolicy(pProvider);
				};

				ServiceRepositoryPolicyLoader(InterfaceType* pInterface): _pInterface(pInterface)
				{
					assert(pInterface);
				};

				virtual ~ServiceRepositoryPolicyLoader() {};

			protected:
				InterfaceType* _pInterface;

			private:
				typedef ServiceRepositoryPolicyLoader<TInterface> Self;
				ServiceRepositoryPolicyLoader(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};


		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
