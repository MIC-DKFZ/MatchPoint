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


#ifndef __MAP_SERVICE_STACK_H
#define __MAP_SERVICE_STACK_H

#include "mapString.h"
#include "mapNoneStaticLoadPolicy.h"
#include "mapFastLockedThreadingPolicy.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"

#include "itkObject.h"

namespace map
{
	namespace core
	{
		namespace services
		{

			/*! @class ServiceStack
			* @brief Class is implements a kind of "run time dynamic" switch yard
			*
			* In different parts of the code MatchPoint uses a dynamic dispatch mechanism
			* to get a proper provider for a needed type of service (e.g. the inversion of
			* registration kernels). This is normaly done by a ServiceStack. ServiceStacks
			* contain a number of service provider. If a suitable provider should be found
			* each provider in the stack, from top (last added) to bottom (first added) will
			* asked if it can handle the request. The first provider proclaiming itself suitable
			* will be selected. So it can be seen like switch-cases with breaks.
			* The default providers of a stack can be adjusted by the loading policy passed
			* as template TStaticLoadPolicy (1). The threading behaviour of the class can
			* be changed by TThreadingPolicy. \n
			* @remark the Stack will act like a smart pointer for providers, thus it increases the
			* reference count (on register) and decreases it (on unregister) if needed.
			* (1): The concept of policy based class designed is explained in the following book:\
			* Andrei Alexandrescu: Modern C++ Design, C++ In-Depth Series, Addison Wesley, 2001.
			*
			* @sa ServiceProvider
			* @ingroup Services
			* @tparam TProviderBase Base class of the service providers handled by the stack.
			* must be based on ServicProvider
			* @tparam TStaticLoadPolicy Policy defines the default providers of the stack and there sequence
			* @tparam TThreadingPolicy Policy defines the stack will handles issues of the use in a multi
			* threadding context.
			* @TODO Mit die providerliste als eigene Classe kapseln, dann kann sie elegant als pimpel genutzt werden und
			* und wir erreichen eine strong guarantee be remove all und rehash.
			*/
			template <class TProviderBase, class TStaticLoadPolicy = NoneStaticLoadPolicy<TProviderBase>, class TThreadingPolicy = FastLockedThreadingPolicy>
			class ServiceStack: public itk::Object, public TStaticLoadPolicy, public TThreadingPolicy,
				public ServiceRepositoryPolicyLoadInterface<TProviderBase>
			{
			public:
				/*! Standard class typedefs. */
				typedef ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>  Self;
				typedef itk::Object                    Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;

				typedef TStaticLoadPolicy                       StaticLoadPolicyType;
				typedef TThreadingPolicy                        ThreadingPolicyType;
				typedef TProviderBase                           ProviderBaseType;
				typedef typename ProviderBaseType::Pointer      ProviderBasePointer;
				typedef typename ProviderBaseType::RequestType  RequestType;

				itkTypeMacro(ServiceProvider, itk::Object);

				/*! Static methods that creates a provider stack, registeres the stack to the load policy
				 * and calls rehash for the first time to ensure that all the default providers are loaded.
				 * Thus it is a specialized version of the itkNewMacro()
				 * @eguarantee strong
				 * @param [in] doRehash Indicates if rehash should be called directly after creating the stack.
				 * @return Smart pointer to the new stack*/
				static Pointer New(bool doRehash = true);
				/*! Creates a stack via New and returns it as a LightObject smart pointer.
				 * @eguarantee strong
				 * @return Smart pointer to the new stack as LightObject*/
				virtual ::itk::LightObject::Pointer CreateAnother(void) const;

				/*! Returns a pointer to the provider that might can handle the request.
				 * @eguarantee strong
				 * @param [in] request Referenz to the request specifing the requirements on the provider
				 * @return Pointer to a suitable provider. Return value may be null.
				 * @retval NULL There was no suitable provider in the stack.
				 */
				ProviderBaseType* getProvider(const RequestType& request) const;

				/*! Returns a pointer to the provider with the specified name.
				 * @eguarantee strong
				 * @param [in] providerName String referenz to the wanted provider name.
				 * @return Pointer to a suitable provider. Return value may be null.
				 * @retval NULL There was no suitable provider in the stack.
				 */
				ProviderBaseType* getProvider(const String& providerName) const;

				/*! Indicates if there is a provider that can handle the passed request.
				 * @eguarantee strong
				 * @param [in] request Referenz to the request specifing the requirements on the provider
				 * @return Boolean that indicates if there is at least on suitable provider.
				 * @retval true There is a suitable provider in the stack.
				 * @retval false There is no suitable provider in the stack.
				 */
				bool providerIsAvailable(const RequestType& request) const;

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
				bool registerProvider(ProviderBaseType* pProvider);

				/*! Removes the provider (identified only by the pointer address) from the stack.
				 * @eguarantee strong
				 * @param [in] pProvider Pointer to the provider that should be removed from stack.
				 * @return Boolean that indicates if there was a provider (identified by pointer)
				 * on the stack.
				 * @retval true The provider instance was on the stack and was removed.
				 * @retval false The provider instance is not a part of the stack.
				 */
				bool unregisterProviderByPointer(ProviderBaseType* pProvider);

				/*! Removes the topmost entry of a given provider (identified by the provider name)
				 * from the stack.
				 * @eguarantee strong
				 * @param [in] providerName String reference to the provider name that identifies the provider.
				 * @return Boolean that indicates if the provider (identified by pointer) has at least one mor
				 * entry on the stack.
				 * @retval true There is no more entry for this provider in the stack.
				 * @retval false There is at least one more entry for this provider in the stack.
				 */
				bool unregisterProvider(const String& providerName);

				/*! Removes all providers from the stack.
				 * @eguarantee basic*/
				void unregisterAll();

				/*! Clears the stack (unregisterAll) and loads all default providers by calling StaticLoadPolicyType::loadStaticProviders().
				 * @eguarantee basic*/
				void rehash();

				/*! returns the size of the stack*/
				unsigned int size() const;

			protected:
				ServiceStack();
				virtual ~ServiceStack();

				typedef std::vector<ProviderBaseType*> ProviderVectorType;

				ProviderVectorType _providers;

				/*!Implements the ServiceRepositoryPolicyLoadInterface that allows loading policies to remove or add providers from the stack.
				 * This methods just adds the given provider to providers and registers the use of the object.
				 * @remark This impolementation uses unregisterProviderByPointerInternal() under the assumption that this method is only invoked by
				 * loadStaticProviders() of the policy and this method itself is only invoked by this->rehash() which does the mutex locking*/
				virtual bool addProviderByPolicy(ProviderBaseType* pProvider);

				/*! Registers a given provider in the stack. The new provider will be topmost and therefore
				 * will be favored over providers registered earlier. The stack will behave like a smartpointer
				 * for the registered provider, thus as long as a provider is registered he won't be deleted.
				 * An instance of a provider (identified via pointer) can only added once to the stack. If the instance
				 * is already on the stack, the stack will stay unchanged.
				* This method is not secured via the mutex is used by registerProvider() and addProviderByPolicy()
				 * @eguarantee strong
				 * @param [in] pProvider Pointer to the provider that should be added.
				 * @return Boolean that indicates if the provider (identified by provider name) has been added.
				 * @retval true The provider was added as topmost element to the stack.
				 * @retval false The provider was already on the stack. Stack is unchanged.
				 * @post Stack is unchanged or added provider is the topmost element on the stack.
				 */
				bool registerProviderInternal(ProviderBaseType* pProvider);

				/*!Implements the ServiceRepositoryPolicyLoadInterface that allows loading policies to remove or add providers from the stack
				 * This methods just removes the given provider from the provider list, if present, and lowers the reference count of the object.
				 * @remark This impolementation uses unregisterProviderByPointerInternal() under the assumption that this method is only invoked by
				 * loadStaticProviders() of the policy and this method itself is only invoked by this->rehash() which does the mutex locking*/
				virtual bool removeProviderByPolicy(ProviderBaseType* pProvider);

				/*! Removes the provider (identified only by the pointer address) from the stack.
				* This method is not secured via the mutex is used by unregisterProviderByPointer() and removeProviderByPolicy()
				 * @eguarantee strong
				 * @param [in] pProvider Pointer to the provider that should be removed from stack.
				 * @return Boolean that indicates if there was a provider (identified by pointer)
				 * on the stack.
				 * @retval true The provider instance was on the stack and was removed.
				 * @retval false The provider instance is not a part of the stack.
				 */
				bool unregisterProviderByPointerInternal(ProviderBaseType* pProvider);

				/*! Methods invoked by itk::LightObject::Print().  */
				virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			private:
				ServiceStack(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapServiceStack.tpp"
#endif

#endif
