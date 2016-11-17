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
// @version $Revision: 1026 $ (last changed revision)
// @date    $Date: 2015-08-05 16:27:57 +0200 (Mi, 05 Aug 2015) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/test/matchRBasicUsageTest.cpp $
*/

#include "itksys/SystemTools.hxx"

#include "litCheckMacros.h"

#include "mapProcessExecutor.h"

namespace map
{
	namespace testing
	{

		//defined by mapDeploymentTests.cpp. It is tha path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char* _callingAppPath;

		int matchRBasicUsageTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string matchRPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			std::string dataPath = "Data path not set.";

			if (argc > 1)
			{
				dataPath = argv[1];
			}


			map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();

			map::utilities::ProcessExecutor::ArgumentListType args;
			//////////////////////////////////////////////////
			// Test: behavior on basic usage.

			//Test not enough parameters
			CHECK(spExec->execute(matchRPath, "matchR", args));
			CHECK_EQUAL(2, spExec->getExitValue());

			args.clear();
			args.push_back("-h");
			CHECK(spExec->execute(matchRPath, "matchR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			args.clear();
			args.push_back("--help");
			CHECK(spExec->execute(matchRPath, "matchR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			args.clear();
			args.push_back("-?");
			CHECK(spExec->execute(matchRPath, "matchR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			args.clear();
			args.push_back("-v");
			CHECK(spExec->execute(matchRPath, "matchR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
