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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapNullRegistrationKernel.tpp $
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
		precomputeKernel()
		{
			mapDefaultExceptionMacro( << "Error. Cannot precompute kernel/field. NullRegistrationKernel is not a valid Kernel and cannot be precomputed.");
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
		doMapPoint(const InputPointType &inPoint, OutputPointType &outPoint) const
		{
			return false;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		NullRegistrationKernel<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream &os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
		};

	} // end namespace core
} // end namespace map

#endif
