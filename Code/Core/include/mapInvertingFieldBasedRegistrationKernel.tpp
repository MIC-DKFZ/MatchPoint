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

#ifndef __INVERTING_FIELD_BASED_REGISTRATION_KERNEL_TPP
#define __INVERTING_FIELD_BASED_REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InvertingFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		InvertingFieldBasedRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InvertingFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		~InvertingFieldBasedRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		InvertingFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent.GetNextIndent() << "Source kernel :" << _SourceKernel << std::endl;
		};

	} // end namespace core
} // end namespace map

#endif
