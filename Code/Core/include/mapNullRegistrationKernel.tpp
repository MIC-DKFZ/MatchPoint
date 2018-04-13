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

#ifndef __NULL_REGISTRATION_KERNEL_TPP
#define __NULL_REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename NullRegistrationKernel<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
		NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
		getLargestPossibleRepresentation() const
		{
			RepresentationDescriptorConstPointer spRep = NULL;
			return spRep;
		};


		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
		precomputeKernel() const
		{
			mapDefaultExceptionMacro( <<
									  "Error. Cannot precompute kernel/field. NullRegistrationKernel is not a valid Kernel and cannot be precomputed.");
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
		NullRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
		~NullRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
		doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const
		{
			return false;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
		};

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    ::itk::LightObject::Pointer
      NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
      InternalClone() const
    {
      Pointer clone = Self::New();
      return clone.GetPointer();
    }

	} // end namespace core
} // end namespace map

#endif
