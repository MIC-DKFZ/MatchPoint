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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapUID.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapUIDTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			map::algorithm::UID::Pointer spUID = map::algorithm::UID::New("de.dkfz.matchpoint.test",
												 "TestDummy", "1.0.0", "x");

			CHECK_EQUAL("de.dkfz.matchpoint.test", spUID->getNamespace());
			CHECK_EQUAL("TestDummy", spUID->getName());
			CHECK_EQUAL("1.0.0", spUID->getVersion());
			CHECK_EQUAL("x", spUID->getBuildTag());

			CHECK_EQUAL("de.dkfz.matchpoint.test::TestDummy::1.0.0::x", spUID->toStr());
			CHECK_NO_THROW(spUID->Print(std::cout));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
