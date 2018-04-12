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

#ifndef __MAP_KERNEL_WRITER_LOAD_POLICY_H
#define __MAP_KERNEL_WRITER_LOAD_POLICY_H

#include "mapGenericStaticLoadPolicyBase.h"
#include "mapRegistrationKernelWriterBase.h"

namespace map
{
	namespace io
	{
		/*! @class KernelWriterLoadPolicy
		* @brief Load class used by RegistrationFileWriter to populate its service stacks.
		*
		* It loads the following providers:
		* - NullRegistrationKernelWriter
		* - InvertingKernelWriter
		* - MatrixModelBasedKernelWriter
    * - LazyFieldFileKernelWriter
		* - ExpandingFieldKernelWriter
		* .
		* @TODO Add missing writers
		* @ingroup LoadPolicies
		* @ingroup RegOperation
		* @sa RegistrationFileWriter
		* @tparam VInputDimensions Input dimensions of the registration that should be stored to file.
		* @tparam VOutputDimensions Output dimensions of the registration that should be stored to file.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class KernelWriterLoadPolicy : public
			::map::core::services::GenericStaticLoadPolicyBase<RegistrationKernelWriterBase<VInputDimensions, VOutputDimensions> >
		{
		protected:
			/*! Standard class typedefs. */
			typedef core::services::GenericStaticLoadPolicyBase<RegistrationKernelWriterBase<VInputDimensions, VOutputDimensions> >
			Superclass;
			typedef typename Superclass::ProviderBaseType      ProviderBaseType;
			typedef typename Superclass::ProviderBasePointer   ProviderBasePointer;
			typedef typename Superclass::LoadInterfaceType     LoadInterfaceType;

			virtual void doLoading();

			KernelWriterLoadPolicy();
			~KernelWriterLoadPolicy();

		private:
			KernelWriterLoadPolicy(const KernelWriterLoadPolicy&);  //purposely not implemented
			void operator=(const KernelWriterLoadPolicy&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapKernelWriterLoadPolicy.tpp"
#endif

#endif
