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
// @version $Revision: 1285 $ (last changed revision)
// @date    $Date: 2016-03-30 17:47:52 +0200 (Mi, 30 Mrz 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/Core/include/mapPreCachedRegistrationKernelInterface.h $
*/

#ifndef __PRE_CACHED_REGISTRATION_KERNEL_INTERFACE_H
#define __PRE_CACHED_REGISTRATION_KERNEL_INTERFACE_H

#include "mapRegistrationTopology.h"

namespace map
{
	namespace core
	{

		/*! @class PreCachedRegistrationKernelInterface
		    @brief class for PreCachedRegistrationKernelInterface.

		    This class is the class for the PreCachedRegistrationKernelInterface.
		    @ingroup RegKernel
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class PreCachedRegistrationKernelInterface
		{
		public:
      typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectTransformType TransformType;

      typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectMappingVectorType
          MappingVectorType;

			/*! sets the transform
			  @eguarantee no fail
			  @param transform the transform that shall be set
			*/
      virtual void setTransformModel(TransformType* transform) = 0;

		protected:
        PreCachedRegistrationKernelInterface() {};
        ~PreCachedRegistrationKernelInterface() {};

		private:
			//No copy constructor allowed
			PreCachedRegistrationKernelInterface(const PreCachedRegistrationKernelInterface&);
			void operator=(const PreCachedRegistrationKernelInterface&);  //purposely not implemented

		};

	}
}

#endif
