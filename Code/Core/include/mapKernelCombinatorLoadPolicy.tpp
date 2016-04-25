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


#ifndef __MAP_KERNEL_COMBINATOR_LOAD_POLICY_TPP
#define __MAP_KERNEL_COMBINATOR_LOAD_POLICY_TPP

#include "mapKernelCombinatorLoadPolicy.h"
#include "mapPreCachedKernelCombinator.h"
#include "mapLazyFieldKernelCombinator.h"
#include "mapNullRegistrationKernelCombinator.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"

namespace map
{
	namespace core
	{

		template <class TProviderBase>
		void
		KernelCombinatorLoadPolicy<TProviderBase>::
		doLoading()
		{
        typedef PreCachedKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
            PreCachedKernelCombinatorType;
      typedef LazyFieldKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
          LazyFieldKernelCombinatorType;
			typedef NullRegistrationKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
			NullRegistrationKernelCombinatorType;

      typename PreCachedKernelCombinatorType::Pointer spPreCachedCombinator = PreCachedKernelCombinatorType::New();
      typename LazyFieldKernelCombinatorType::Pointer spLazyFieldCombinator = LazyFieldKernelCombinatorType::New();
			typename NullRegistrationKernelCombinatorType::Pointer spNullCombinator =
				NullRegistrationKernelCombinatorType::New();

			services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(Superclass::_pLoadInterface);

      if (!loader.addProviderByPolicy(spLazyFieldCombinator))
			{
				mapLogWarningObjMacro("ModelModelKernelCombinator was not added because it was already on the service stack!");
			}

      if (!loader.addProviderByPolicy(spPreCachedCombinator))
			{
				mapLogWarningObjMacro("FieldModelKernelCombinator was not added because it was already on the service stack!");
			}

      if (!loader.addProviderByPolicy(spNullCombinator))
      {
          mapLogWarningObjMacro("NullRegistationKernelCombinator was not added because it was already on the service stack!");
      }

    }

		template <class TProviderBase>
		KernelCombinatorLoadPolicy<TProviderBase>::
		KernelCombinatorLoadPolicy()
		{ }

		template <class TProviderBase>
		KernelCombinatorLoadPolicy<TProviderBase>::
		~KernelCombinatorLoadPolicy()
		{ }


	} // end namespace core
} // end namespace map

#endif
