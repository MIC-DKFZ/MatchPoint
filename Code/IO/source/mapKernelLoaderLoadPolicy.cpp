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


#include "mapKernelLoaderLoadPolicy.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"
#include "mapMatrixModelBasedKernelLoader.h"
#include "mapNullRegistrationKernelLoader.h"
#include "mapFieldKernelLoader.h"
#include "mapLazyFileFieldKernelLoader.h"
#include "mapInvertingFieldKernelLoader.h"

namespace map
{
	namespace io
	{

		void
		KernelLoaderLoadPolicy::
		doLoading()
		{
			::map::core::services::ServiceRepositoryPolicyLoader<LoadInterfaceType> loader(_pLoadInterface);

			if (!loader.addProviderByPolicy(MatrixModelBasedKernelLoader<2>::New()))
			{
				mapLogWarningObjMacro("MatrixModelBasedKernelLoader<2> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(MatrixModelBasedKernelLoader<3>::New()))
			{
				mapLogWarningObjMacro("MatrixModelBasedKernelLoader<3> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(NullRegistrationKernelLoader<2, 2>::New()))
			{
				mapLogWarningObjMacro("NullRegistrationKernelLoader<2,2> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(NullRegistrationKernelLoader<2, 3>::New()))
			{
				mapLogWarningObjMacro("NullRegistrationKernelLoader<2,3> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(NullRegistrationKernelLoader<3, 3>::New()))
			{
				mapLogWarningObjMacro("NullRegistrationKernelLoader<3,3> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(NullRegistrationKernelLoader<3, 2>::New()))
			{
				mapLogWarningObjMacro("NullRegistrationKernelLoader<3,2> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(InvertingFieldKernelLoader<2, 2>::New()))
			{
				mapLogWarningObjMacro("InvertingFieldKernelLoader<2,2> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(InvertingFieldKernelLoader<3, 3>::New()))
			{
				mapLogWarningObjMacro("InvertingFieldKernelLoader<3,3> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(FieldKernelLoader<2, 2>::New()))
			{
				mapLogWarningObjMacro("FieldKernelLoader<2,2> was not added because it was already on the service stack!");
			}

			if (!loader.addProviderByPolicy(FieldKernelLoader<3, 3>::New()))
			{
				mapLogWarningObjMacro("FieldKernelLoader<3,3> was not added because it was already on the service stack!");
			}

      if (!loader.addProviderByPolicy(LazyFileFieldKernelLoader<2, 2>::New()))
      {
          mapLogWarningObjMacro("LazyFileFieldKernelLoader<2,2> was not added because it was already on the service stack!");
      }

      if (!loader.addProviderByPolicy(LazyFileFieldKernelLoader<3, 3>::New()))
      {
          mapLogWarningObjMacro("LazyFileFieldKernelLoader<3,3> was not added because it was already on the service stack!");
      }
		}


		KernelLoaderLoadPolicy::
		KernelLoaderLoadPolicy() { }



		KernelLoaderLoadPolicy::
		~KernelLoaderLoadPolicy() { }


	} // end namespace io
} // end namespace map
