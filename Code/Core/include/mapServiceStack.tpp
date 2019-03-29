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


#ifndef __MAP_SERVICE_STACK_TPP
#define __MAP_SERVICE_STACK_TPP

#include "mapServiceStack.h"
#include "mapServiceProvider.h"

#include <algorithm>

namespace map
{
	namespace core
	{
		namespace services
		{

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			typename ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::Pointer
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			New(bool doRehash)
			{
				Pointer smartPtr = new Self;
				smartPtr->UnRegister();

				if (doRehash)
				{
					smartPtr->rehash();
				}

				return smartPtr;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			::itk::LightObject::Pointer
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			CreateAnother() const
			{
				::itk::LightObject::Pointer smartPtr;
				smartPtr = Self::New(false).GetPointer();
				return smartPtr;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			typename ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::ProviderBaseType*
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			getProvider(const RequestType& request) const
			{
				ProviderBaseType* pResult = nullptr;

				this->lock();

				// search vector in reverse order, because ServiceStack should operate by the LIFU principle (last in, first used)
				// thus the lastest added provider suitable for a request should be used.
				for (auto pos = _providers.rbegin();
					 pos != _providers.rend(); ++pos)
				{
					if ((*pos)->canHandleRequest(request))
					{
						pResult = *pos;
						break;
					}
				}

				this->unlock();

				return pResult;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			typename ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::ProviderBaseType*
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			getProvider(const String& providerName) const
			{
				ProviderBaseType* pResult = NULL;

				this->lock();

				// search vector in reverse order, because ServiceStack should operate by the LIFU principle (last in, first used)
				// thus the lastest added provider suitable for a request should be used.
				for (typename ProviderVectorType::const_reverse_iterator pos = _providers.rbegin();
					 pos != _providers.rend(); ++pos)
				{
					if ((*pos)->getProviderName() == providerName)
					{
						pResult = *pos;
						break;
					}
				}

				this->unlock();

				return pResult;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			providerIsAvailable(const RequestType& request) const
			{
				return getProvider(request) != NULL;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			registerProvider(ProviderBaseType* pProvider)
			{
				this->lock();

				bool result = registerProviderInternal(pProvider);

				this->unlock();

				return result;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			registerProviderInternal(ProviderBaseType* pProvider)
			{
				auto finding = std::find(_providers.begin(), _providers.end(),
						pProvider);
				bool result = false;

				if (finding == _providers.end())
				{
					//not in stack so add provider
					result = true;
					pProvider->Register();
					_providers.push_back(pProvider);
				}

				return result;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			unregisterProviderByPointer(ProviderBaseType* pProvider)
			{
				this->lock();

				bool result = unregisterProviderByPointerInternal(pProvider);

				this->unlock();

				return result;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			unregisterProviderByPointerInternal(ProviderBaseType* pProvider)
			{
				auto finding = std::find(_providers.begin(), _providers.end(),
						pProvider);
				bool result = false;

				if (finding != _providers.end())
				{
					//add provider
					result = true;
					(*finding)->UnRegister();
					_providers.erase(finding);
				}

				return result;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			unregisterProvider(const String& providerName)
			{
				this->lock();

				bool result = false;

				// search vector in reverse order, because ServiceStack should operate by the LIFU principle (last in, first used)
				// thus the lastest added provider suitable for a request should be used.
				typename ProviderVectorType::iterator finding = _providers.end();

				for (typename ProviderVectorType::iterator pos = _providers.begin(); pos != _providers.end(); ++pos)
				{
					if ((*pos)->getProviderName() == providerName)
					{
						finding = pos;
					}
				}

				if (finding != _providers.end())
				{
					result = true;
					(*finding)->UnRegister();
					_providers.erase(finding);
				}

				this->unlock();

				return result;
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			void
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			unregisterAll()
			{
				this->lock();

				while (!_providers.empty())
				{
					_providers.back()->UnRegister();
					_providers.pop_back();
				}

				this->unlock();
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			void
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			rehash()
			{
				this->unregisterAll();

				this->lock();
				StaticLoadPolicyType::loadStaticProviders();
				this->unlock();
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			ServiceStack()
			{
				StaticLoadPolicyType::registerInterfaceForStaticLoading(*this);
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			~ServiceStack()
			{
				this->unregisterAll();
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			addProviderByPolicy(ProviderBaseType* pProvider)
			{
				return registerProviderInternal(pProvider);
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			bool
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			removeProviderByPolicy(ProviderBaseType* pProvider)
			{
				return unregisterProviderByPointerInternal(pProvider);
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			void
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			PrintSelf(std::ostream& os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "Provider count: " << _providers.size() << std::endl;
				os << indent << "Stack content (in descending priority): " << std::endl;
				itk::Indent indent2 = indent.GetNextIndent();

				for (auto pos = _providers.rbegin();
					 pos != _providers.rend(); ++pos)
				{
					os << indent2 << (*pos)->getProviderName() << std::endl;
				}
			};

			template <class TProviderBase,  class TStaticLoadPolicy, class TThreadingPolicy>
			unsigned int
			ServiceStack<TProviderBase, TStaticLoadPolicy, TThreadingPolicy>::
			size() const
			{
				return _providers.size();
			};


		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
