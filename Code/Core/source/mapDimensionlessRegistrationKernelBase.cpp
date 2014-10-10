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

#include "mapDimensionlessRegistrationKernelBase.h"

namespace map
{
	namespace core
	{

		void DimensionlessRegistrationKernelBase::PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent << "Input dimensions: " << getInputDimensions() << std::endl;
			os << indent << "Output dimensions: " << getOutputDimensions() << std::endl;
			os << indent << "limited Representation: " << hasLimitedRepresentation() << std::endl;
		};

		DimensionlessRegistrationKernelBase::DimensionlessRegistrationKernelBase()
		{};

		DimensionlessRegistrationKernelBase::~DimensionlessRegistrationKernelBase()
		{};

		std::ostream& operator<< (std::ostream& os,
								  const DimensionlessRegistrationKernelBase& p)
		{
			p.Print(os);
			return os;
		}

	}
}
