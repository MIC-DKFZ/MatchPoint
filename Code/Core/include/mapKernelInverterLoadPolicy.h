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

#ifndef __MAP_INVERTER_LOAD_POLICY_H
#define __MAP_INVERTER_LOAD_POLICY_H

#include "mapGenericStaticLoadPolicyBase.h"
#include "mapRegistrationKernelInverterBase.h"

namespace map
{
	namespace core
	{
		/*! @class KernelInverterLoadPolicy
		* @brief Load class used by InverseRegistrationKernelGenrator to populate its service stack.
		*
		* It loads the following providers:
		* - ModelBasedKernelInverter
		* - FieldBasedKernelInverter
		* - NullRegistrationKernelInverter
		* .
		*
		* @ingroup LoadPolicies
		* @ingroup RegOperation
		* @sa InverseRegistrationKernelGenrator
		* @tparam TProviderBase Base class of the service providers loaded by the policy.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class KernelInverterLoadPolicy : public
			services::GenericStaticLoadPolicyBase<RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions> >
		{
		protected:
			/*! Standard class typedefs. */
			typedef services::GenericStaticLoadPolicyBase< RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions> >
			Superclass;
			typedef typename Superclass::ProviderBaseType      ProviderBaseType;
			typedef typename Superclass::ProviderBasePointer   ProviderBasePointer;
			typedef typename Superclass::LoadInterfaceType     LoadInterfaceType;

			virtual void doLoading();

			KernelInverterLoadPolicy();
			~KernelInverterLoadPolicy();

		private:
			KernelInverterLoadPolicy(const KernelInverterLoadPolicy&);  //purposely not implemented
			void operator=(const KernelInverterLoadPolicy&);  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapKernelInverterLoadPolicy.tpp"
#endif

#endif
