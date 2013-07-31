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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/include/mapCheckDLLInterfaceVersion.h $
*/


#ifndef __MAP_CHECK_DLL_INTERFACE_VERSION_H
#define __MAP_CHECK_DLL_INTERFACE_VERSION_H

#include "mapMacros.h"
#include "mapMAPDeploymentExports.h"

namespace map
{
	namespace deployment
	{
		/*! @brief Checks if a passed verion is consistent with the dll interface version of the current binaries.
		 * This function is used by dll managment code to check back if they can handle the interface of a DLL
		 * (which might have been builded with other binaries and therfore an other DLL interface version).
		 * @remark Normaly you just have to include mapGetDLLInterfaceVersion.cpp to your project for adding
		 * @return Indicates of the interface version indicated by the passed values can be legaly used.
		 * True: Interface can be used. False: Interface cannot be used and is not consistent with the current interface
		 * version.
		 * @ingroup Deployment
		 */
		MAPDeployment_EXPORT bool checkDLLInterfaceVersion(unsigned int &major, unsigned int &minor);
	}
}

#endif
