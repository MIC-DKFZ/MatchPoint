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



#include "mapMetaPropertyBase.h"

namespace map
{
	namespace core
	{

		void
		MetaPropertyBase
		::PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			os << indent << "[UNKNOWN_PRINT_CHARACTERISTICS]" << std::endl;
		}

		MetaPropertyBase
		::MetaPropertyBase()
		{
			//Nothing to do here
		}

		MetaPropertyBase
		::~MetaPropertyBase()
		{
			//Nothing to do here
		}

	}
}