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
#include "mapModelModelKernelCombinator.h"
#include "mapFieldModelKernelCombinator.h"
#include "mapModelFieldKernelCombinator.h"
#include "mapFieldFieldKernelCombinator.h"
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
			typedef ModelModelKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
			ModelModelCombinatorType;
			typedef FieldModelKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
			FieldModelCombinatorType;
			typedef ModelFieldKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
			ModelFieldCombinatorType;
			typedef FieldFieldKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
			FieldFieldCombinatorType;
			typedef NullRegistrationKernelCombinator<TProviderBase::InputDimensions, TProviderBase::InterimDimensions, TProviderBase::OutputDimensions>
			NullRegistrationKernelCombinatorType;

			typename ModelModelCombinatorType::Pointer spModelModelCombinator = ModelModelCombinatorType::New();
			typename FieldModelCombinatorType::Pointer spFieldModelCombinator = FieldModelCombinatorType::New();
			typename ModelFieldCombinatorType::Pointer spModelFieldCombinator = ModelFieldCombinatorType::New();
			typename FieldFieldCombinatorType::Pointer spFieldFieldCombinator = FieldFieldCombinatorType::New();
			typename NullRegistrationKernelCombinatorType::Pointer spNullCombinator =
				NullRegistrationKernelCombinatorType::New();

			services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(Superclass::_pLoadInterface);

			if (!loader.addProviderByPolicy(spNullCombinator))
			{
				mapLogWarningObjMacro("NullRegistationKernelCombinator was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(spModelModelCombinator))
			{
				mapLogWarningObjMacro("ModelModelKernelCombinator was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(spFieldModelCombinator))
			{
				mapLogWarningObjMacro("FieldModelKernelCombinator was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(spModelFieldCombinator))
			{
				mapLogWarningObjMacro("ModelFieldKernelCombinator was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(spFieldFieldCombinator))
			{
				mapLogWarningObjMacro("FieldFieldKernelCombinator was not added because it was already on the service stack!");
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
