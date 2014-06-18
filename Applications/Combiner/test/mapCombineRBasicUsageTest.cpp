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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/test/mapRBasicUsageTest.cpp $
*/

#include "itksys/SystemTools.hxx"

#include "litCheckMacros.h"

#include "mapProcessExecutor.h"

namespace map
{
	namespace testing
	{

		//defined by mapCombineRTests.cpp. It is the path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char* _callingAppPath;

		int combineRBasicUsageTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string combineRPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();

			map::utilities::ProcessExecutor::ArgumentListType args;
			//////////////////////////////////////////////////
			// Test: behavior on basic usage.

			//Test not enough parameters
			CHECK(spExec->execute(combineRPath, "combineR", args));
			CHECK_EQUAL(2, spExec->getExitValue());

			args.clear();
			args.push_back("-h");
			CHECK(spExec->execute(combineRPath, "combineR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			args.clear();
			args.push_back("--help");
			CHECK(spExec->execute(combineRPath, "combineR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			args.clear();
			args.push_back("-?");
			CHECK(spExec->execute(combineRPath, "combineR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			args.clear();
			args.push_back("-v");
			CHECK(spExec->execute(combineRPath, "combineR", args));
			CHECK_EQUAL(1, spExec->getExitValue());

			args.clear();
			args.push_back("dummy");
			CHECK(spExec->execute(combineRPath, "combineR", args));
			CHECK_EQUAL(3, spExec->getExitValue());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
