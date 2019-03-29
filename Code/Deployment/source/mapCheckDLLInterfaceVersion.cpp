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


#include "mapCheckDLLInterfaceVersion.h"
#include "mapConfigure.h"

namespace map
{
	namespace deployment
	{

		bool checkDLLInterfaceVersion(unsigned int& major, unsigned int& minor)
		{
			//it is assumed that a dll should at least have the same major version then these binaries.
			return (major == MAP_DLL_INTERFACE_VERSION_MAJOR);
		};

	}
}  // namespace map
