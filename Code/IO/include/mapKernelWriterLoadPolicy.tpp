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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/include/mapKernelWriterLoadPolicy.tpp $
*/


#ifndef __MAP_KERNEL_WRITER_LOAD_POLICY_TPP
#define __MAP_KERNEL_WRITER_LOAD_POLICY_TPP

#include "mapKernelWriterLoadPolicy.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"
#include "mapMatrixModelBasedKernelWriter.h"
#include "mapNullRegistrationKernelWriter.h"
#include "mapExpandingFieldKernelWriter.h"

namespace map
{
	namespace io
	{


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		KernelWriterLoadPolicy<VInputDimensions, VOutputDimensions>::
		doLoading()
		{
			core::services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(Superclass::_pLoadInterface);

			typedef MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions> ModelKernelWriterType;

			typename ModelKernelWriterType::Pointer spModelWriter = ModelKernelWriterType::New();

			if (!loader.addProviderByPolicy(spModelWriter))
			{
				mapLogWarningObjMacro("MatrixModelBasedKernelWriter was not added because it was already on the service stack!");
			}

			typedef ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions> ExpandingFieldKernelWriterType;

			typename ExpandingFieldKernelWriterType::Pointer spExpandingFieldWriter = ExpandingFieldKernelWriterType::New();

			if (!loader.addProviderByPolicy(spExpandingFieldWriter))
			{
				mapLogWarningObjMacro("ExpandingFieldKernelWriter was not added because it was already on the service stack!");
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
