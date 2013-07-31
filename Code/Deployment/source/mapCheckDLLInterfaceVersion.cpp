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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/source/mapCheckDLLInterfaceVersion.cpp $
*/


#include "mapCheckDLLInterfaceVersion.h"
#include "mapConfigure.h"

namespace map
{
	namespace deployment
	{

		bool checkDLLInterfaceVersion(unsigned int &major, unsigned int &minor)
		{
			//it is assumed that a dll should at least have the same major version then these binaries.
			return (major == MAP_DLL_INTERFACE_VERSION_MAJOR);
		};

	}
}
