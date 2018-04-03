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


#ifndef __MAP_REGISTRATION_KERNEL_COMBINATOR_BASE_TPP
#define __MAP_REGISTRATION_KERNEL_COMBINATOR_BASE_TPP

namespace map
{
	namespace core
	{
		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		void
		RegistrationKernelCombinatorBase<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
		};

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		RegistrationKernelCombinatorBase<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		RegistrationKernelCombinatorBase()
		{};

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		RegistrationKernelCombinatorBase<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		~RegistrationKernelCombinatorBase() {};


	} // end namespace core
} // end namespace map

#endif
