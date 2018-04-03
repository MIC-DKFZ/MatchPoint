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


#ifndef __MAP_STATIC_SERVICE_STACK_H
#define __MAP_STATIC_SERVICE_STACK_H

#include "mapDefaultSLStaticPolicy.h"
#include "mapFastLockedThreadingStaticPolicy.h"
#include "mapServiceStack.h"

namespace map
{
	namespace core
	{
		namespace services
		{

			/*! @class StaticServiceStack
			* @brief Class wraps a ServiceStack as an singelton.
			*
			* This class can be used as a wrapper to realize a ServiceStack as singelton, thus
			* all function calling this static stack will work on the same provider stack. Also
			* changes on the provider stack will be global.
			* Every static method that interacts with the concrete ServiceStack will call ensureStack().
			* Calling this function the first time will create the concrete ServiceStack.
			*
			* @sa ServiceStack
			* @ingroup Services
			* @tparam TConcreteServiceStack The service stack class that should be wrapped.
			* @tparam TStaticLoadStaticPolicy Policy defines the default providers of the stack and there sequence
			* @tparam TThreadingStaticPolicy Policy defines the stack will handles issues of the use in a multi
			* threadding context.
			*/
			template < class TConcreteServiceStack,
					 template <class> class TStaticLoadStaticPolicy = DefaultSLStaticPolicy,
					 class TThreadingStaticPolicy = FastLockedThreadingStaticPolicy >
			class StaticServiceStack: public TStaticLoadStaticPolicy<TConcreteServiceStack>,
				public TThreadingStaticPolicy
			{
			public:
				/*! Standard class typedefs. */
				typedef TConcreteServiceStack	 ConcreteServiceStackType;
				typedef typename ConcreteServiceStackType::Pointer                 ConcreteServiceStackPointer;
				typedef typename ConcreteServiceStackType::ProviderBaseType        ProviderBaseType;
				typedef typename ProviderBaseType::Pointer										     ProviderBasePointer;
				typedef typename ProviderBaseType::RequestType										 RequestType;

				typedef StaticServiceStack<ProviderBaseType, TStaticLoadStaticPolicy, TThreadingStaticPolicy>  Self;

				typedef TStaticLoadStaticPolicy<ConcreteServiceStackType>          StaticLoadStaticPolicyType;
				typedef typename ConcreteServiceStackType::StaticLoadPolicyType    StaticLoadPolicyType;
				typedef TThreadingStaticPolicy                                     ThreadingStaticPolicyType;
				typedef typename ConcreteServiceStackType::ThreadingPolicyType     ThreadingPolicyType;


				/*! Returns a pointer to the provider that might can handle the request.
				 * @eguarantee strong
				 * @param [in] request Referenz to the request specifing the requirements on the provider
				 * @return Pointer to a suitable provider. Return value may be null.
				 * @retval NULL There was no suitable provider in the stack.
				 */
				static ProviderBaseType* getProvider(const RequestType& request);

				/*! Returns a pointer to the provider with the specified name.
				 * @eguarantee strong
				 * @param [in] providerName String referenz to the wanted provider name.
				 * @return Pointer to a suitable provider. Return value may be null.
				 * @retval NULL There was no suitable provider in the stack.
				 */
				static ProviderBaseType* getProvider(const String& providerName);

				/*! Indicates if there is a provider that can handle the passed request.
				 * @eguarantee strong
				 * @param [in] request Referenz to the request specifing the requirements on the provider
				 * @return Boolean that indicates if there is at least on suitable provider.
				 * @retval true There is a suitable provider in the stack.
				 * @retval false There is no suitable provider in the stack.
				 */
				static bool providerIsAvailable(const RequestType& request);

				/*! Registers a given provider in the stack. The new provider will be topmost and therfore
				 * will be favored over providers registered ealier. The stack will behave like a smartpointer
				 * for the registered provider, thus as long as a provider is registered he won't be deleted.
				 * An instance of a provider (identified via pointer) can only added once to the stack. If the instance
				 * is already on the stack, the stack will stay unchanged.
				 * @eguarantee strong
				 * @param [in] pProvider Pointer to the provider that should be added.
				 * @return Boolean that indicates if the provider (identified by provider name) has been added.
				 * @retval true The provider was added as topmost element to the stack.
				 * @retval false The provider was already on the stack. Stack is unchanged.
				 * @post Stack is unchanged or added provider is the topmost element on the stack.
				 */
				static bool registerProvider(ProviderBaseType* pProvider);

				/*! Removes the provider (identified only by the pointer address) from the stack.
				 * @eguarantee strong
				 * @param [in] pProvider Pointer to the provider that should be removed from stack.
				 * @return Boolean that indicates if there was a provider (identified by pointer)
				 * on the stack.
				 * @retval true The provider instance was on the stack and was removed.
				 * @retval false The provider instance is not a part of the stack.
				 */
				static bool unregisterProviderByPointer(ProviderBaseType* pProvider);

				/*! Removes the topmost entry of a given provider (identified by the provider name)
				 * from the stack.
				 * @eguarantee strong
				 * @param [in] providerName String reference to the provider name that identifies the provider.
				 * @return Boolean that indicates if the provider (identified by pointer) has at least one mor
				 * entry on the stack.
				 * @retval true There is no more entry for this provider in the stack.
				 * @retval false There is at least one more entry for this provider in the stack.
				 */
				static bool unregisterProvider(const String& providerName);

				/*! Removes all providers from the stack.
				 * @eguarantee strong*/
				static void unregisterAll();

				/*! Clears the stack (unregisterAll) and loads all default providers by calling StaticLoadPolicyType::loadStaticProviders().
				 * @eguarantee strong*/
				static void rehash();

				static unsigned int size();

			protected:
				/*! Checks if a concrete stack exists (_spConcreteStack != NULL).
				 * If not, the stack will be created (establishConcreteStack) and _spConcreteStack will be set.
				 * @eguarantee strong*/
				static void ensureStack();

				/*! Creates a concrete stack, do static load on it and than pass it as return value.*/
				static ConcreteServiceStackPointer establishConcreteStack();

				/*! Smartpointer to the concrete stack instance. Will be created by ensureStack() if needed.*/
				static ConcreteServiceStackPointer _spConcreteStack;

				StaticServiceStack() {};
				virtual ~StaticServiceStack() {};

			private:
				StaticServiceStack(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapStaticServiceStack.tpp"
#endif

#endif
