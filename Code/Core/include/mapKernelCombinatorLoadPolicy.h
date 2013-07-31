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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapKernelCombinatorLoadPolicy.h $
*/


#ifndef __MAP_KERNEL_COMBINATOR_LOAD_POLICY_H
#define __MAP_KERNEL_COMBINATOR_LOAD_POLICY_H

# include "mapGenericStaticLoadPolicyBase.h"

namespace map
{
	namespace core
	{
		/*! @class KernelCombinatorLoadPolicy
		* @brief Load class used by RegistrationCombinator to populate its service stack.
		*
		* It loads the following providers:
		* - ModelModelKernelCombinator
		* - FieldModelKernelCombinator
		* - ModelFieldKernelCombinator
		* - FieldFieldKernelCombinator
		* - NullRegistrationKernelCombinator
		*
		* @ingroup LoadPolicies
		* @ingroup RegOperation
		* @sa RegistrationCombinator
		* @tparam TProviderBase Base class of the service providers loaded by the policy.
		*/
		template <class TProviderBase>
		class KernelCombinatorLoadPolicy : public services::GenericStaticLoadPolicyBase<TProviderBase>
		{
		protected:
			/*! Standard class typedefs. */
			typedef services::GenericStaticLoadPolicyBase<TProviderBase> Superclass;
			typedef typename Superclass::ProviderBaseType      ProviderBaseType;
			typedef typename Superclass::ProviderBasePointer   ProviderBasePointer;
			typedef typename Superclass::LoadInterfaceType     LoadInterfaceType;

			virtual void doLoading();

			KernelCombinatorLoadPolicy();
			~KernelCombinatorLoadPolicy();

		private:
			KernelCombinatorLoadPolicy(const KernelCombinatorLoadPolicy &); //purposely not implemented
			void operator=(const KernelCombinatorLoadPolicy &); //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapKernelCombinatorLoadPolicy.tpp"
#endif

#endif
