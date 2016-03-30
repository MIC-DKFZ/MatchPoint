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




#ifndef __FIELD_BASED_REGISTRATION_KERNELS_H
#define __FIELD_BASED_REGISTRATION_KERNELS_H

#include "mapConcreteFieldBasedRegistrationKernel.h"
#include "mapPreCachedTransformPolicy.h"
#include "mapLazyTransformPolicy.h"

namespace map
{
	namespace core
	{

		/*!@brief  FieldKernels is a struct that allows easy access to the two default field kernels of MatchPoint
		 * This struct is used as a workarround/convinience because PreCachedFieldBasedRegistrationKernel and
		 * ConcreteFieldBasedRegistrationKernel are only partially templated classes and cannot be defined directly
		 * in the namespace as a typedef.
		 * @ingroup RegKernel
		 */
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		struct FieldKernels
		{
			typedef ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, PreCachedTransformPolicy>
			PreCachedFieldBasedRegistrationKernel;

			typedef ConcreteFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions, LazyTransformPolicy>
			LazyFieldBasedRegistrationKernel;
		};

	}
}

#endif
