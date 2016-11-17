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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/test/matchRSimpleMappingTest.cpp $
*/

#include "itksys/SystemTools.hxx"

#include "litCheckMacros.h"
#include "litImageTester.h"

#include "mapProcessExecutor.h"
#include "mapImageReader.h"

namespace map
{
	namespace testing
	{

		//defined by mapDeploymentTests.cpp. It is tha path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char* _callingAppPath;

    int matchRSimpleRegTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string matchRPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			std::string movingPath = "Moving Data path not set.";
      std::string targetPath = "Target data path not set.";
      std::string outputPath = "Output data path not set.";
      std::string refPath = "Reference data path not set.";

			map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();
      spExec->setSharedOutputPipes(true);

			map::utilities::ProcessExecutor::ArgumentListType args;

      if (argc > 1)
			{
				movingPath = argv[1];
			}

      if (argc > 2)
      {
        targetPath = argv[2];
      }

      if (argc > 3)
      {
        outputPath = argv[3];
      }

      if (argc > 4)
      {
        refPath = argv[4];
      }

      args.push_back(movingPath);
      args.push_back(targetPath);
      args.push_back("-o");
      args.push_back(outputPath);

      unsigned int index = 5;
      while (index < argc)
      {
        args.push_back(argv[index++]);
      }

			//////////////////////////////////////////////////
			// Test: behavior on simple registration task.

			CHECK(spExec->execute(matchRPath, "matchR", args));
			CHECK_EQUAL(0, spExec->getExitValue());

      // Check result against reference
      //@TODO: Test reg result

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
