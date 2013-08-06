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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/test/mapDeploymentDLLInfoTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapDeploymentDLLInfo.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapDeploymentDLLInfoTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			map::algorithm::UID::Pointer spUID = map::algorithm::UID::New("de.dkfz.matchpoint.test", "TestDummy", "1.0.0", "x");
			map::deployment::DLLInfo::Pointer spInfo = map::deployment::DLLInfo::New(spUID, "testfile.dll", "profile");

			CHECK_EQUAL(spUID.GetPointer(), &(spInfo->getAlgorithmUID()));
			CHECK_EQUAL("testfile.dll", spInfo->getLibraryFilePath());
      CHECK_EQUAL("profile", spInfo->getAlgorithmProfileStr());

			CHECK_THROW(map::deployment::DLLInfo::New(NULL, "file_with_NULL_UID.dll", ""));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
