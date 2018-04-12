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


#ifndef __MAP_KERNEL_WRITER_LOAD_POLICY_TPP
#define __MAP_KERNEL_WRITER_LOAD_POLICY_TPP

#include "mapKernelWriterLoadPolicy.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"
#include "mapMatrixModelBasedKernelWriter.h"
#include "mapNullRegistrationKernelWriter.h"
#include "mapExpandingFieldKernelWriter.h"
#include "mapInvertingKernelWriter.h"
#include "mapLazyFieldFileKernelWriter.h"

namespace map
{
	namespace io
	{


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		KernelWriterLoadPolicy<VInputDimensions, VOutputDimensions>::
		doLoading()
		{
			::map::core::services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(
				Superclass::_pLoadInterface);

      typedef ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions>
          ExpandingFieldKernelWriterType;

      typename ExpandingFieldKernelWriterType::Pointer spExpandingFieldWriter =
          ExpandingFieldKernelWriterType::New();

      if (!loader.addProviderByPolicy(spExpandingFieldWriter))
      {
          mapLogWarningObjMacro("ExpandingFieldKernelWriter was not added because it was already on the service stack!");
      }
        
      typedef LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions> LazyFieldFileKernelWriterType;

      typename LazyFieldFileKernelWriterType::Pointer spLazyFileWriter = LazyFieldFileKernelWriterType::New();

      if (!loader.addProviderByPolicy(spLazyFileWriter))
      {
        mapLogWarningObjMacro("LazyFieldFileKernelWriter was not added because it was already on the service stack!");
      }

      typedef MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions> ModelKernelWriterType;

			typename ModelKernelWriterType::Pointer spModelWriter = ModelKernelWriterType::New();

			if (!loader.addProviderByPolicy(spModelWriter))
			{
				mapLogWarningObjMacro("MatrixModelBasedKernelWriter was not added because it was already on the service stack!");
			}

			typedef InvertingKernelWriter<VInputDimensions, VOutputDimensions>
			InvertingKernelWriterType;

			typename InvertingKernelWriterType::Pointer spInvertingFieldWriter =
				InvertingKernelWriterType::New();

			if (!loader.addProviderByPolicy(spInvertingFieldWriter))
			{
				mapLogWarningObjMacro("InvertingKernelWriter was not added because it was already on the service stack!");
			}

			typedef NullRegistrationKernelWriter<VInputDimensions, VOutputDimensions> NullKernelWriterType;

			typename NullKernelWriterType::Pointer spNullWriter = NullKernelWriterType::New();

			if (!loader.addProviderByPolicy(spNullWriter))
			{
				mapLogWarningObjMacro("NullRegistrationKernelWriter was not added because it was already on the service stack!");
			}

		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		KernelWriterLoadPolicy<VInputDimensions, VOutputDimensions>::
		KernelWriterLoadPolicy() { }



		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		KernelWriterLoadPolicy<VInputDimensions, VOutputDimensions>::
		~KernelWriterLoadPolicy() { }


	} // end namespace io
} // end namespace map

#endif
