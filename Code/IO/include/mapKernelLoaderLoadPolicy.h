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

#ifndef __MAP_KERNEL_LOADER_LOAD_POLICY_H
#define __MAP_KERNEL_LOADER_LOAD_POLICY_H


#include "mapGenericStaticLoadPolicyBase.h"
#include "mapRegistrationKernelLoaderBase.h"
#include "mapMAPIOExports.h"

namespace map
{
	namespace io
	{
		/*! @class KernelLoaderLoadPolicy
		* @brief Load class used by RegistrationFileLoader to populate its service stacks.
		*
		* It loads the following providers:
		* - MatrixModelBasedKernelLoader<2,2>
		* - MatrixModelBasedKernelLoader<3,3>
		* - InvertingKernelLoader<2,2>
		* - InvertingKernelLoader<3,3>
		* - LazyFileFieldKernelLoader<2,2>
		* - LazyFileFieldKernelLoader<3,3>
		* - FieldKernelLoader<2,2>
		* - FieldKernelLoader<3,3>
		* - NullKernelLoader<2,2>
		* - NullKernelLoader<2,3>
		* - NullKernelLoader<3,3>
		* - NullKernelLoader<3,2>
		* .
		* @ingroup LoadPolicies
		* @ingroup RegOperation
		* @sa RegistrationFileReader
		*/
		class MAPIO_EXPORT KernelLoaderLoadPolicy : public
			::map::core::services::GenericStaticLoadPolicyBase<RegistrationKernelLoaderBase >
		{
		protected:
			/*! Standard class typedefs. */
			typedef core::services::GenericStaticLoadPolicyBase <RegistrationKernelLoaderBase> Superclass;
			typedef Superclass::ProviderBaseType      ProviderBaseType;
			typedef Superclass::ProviderBasePointer   ProviderBasePointer;
			typedef Superclass::LoadInterfaceType     LoadInterfaceType;

			virtual void doLoading();

			KernelLoaderLoadPolicy();
			~KernelLoaderLoadPolicy();

		private:
			KernelLoaderLoadPolicy(const KernelLoaderLoadPolicy&);  //purposely not implemented
			void operator=(const KernelLoaderLoadPolicy&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#endif
