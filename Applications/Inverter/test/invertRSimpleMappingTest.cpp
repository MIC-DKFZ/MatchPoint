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
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/test/invertRSimpleMappingTest.cpp $
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

		int invertRSimpleMappingTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string invertRPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

      std::string regPath = "Reg data path not set.";
      std::string outputPath = "Output data path not set.";
      std::string refPath = "Reference data path not set.";

			map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();
      spExec->setSharedOutputPipes(true);

			map::utilities::ProcessExecutor::ArgumentListType args;

      if (argc > 1)
      {
        regPath = argv[1];
      }

      if (argc > 2)
      {
        outputPath = argv[2];
      }

      if (argc > 3)
      {
        refPath = argv[3];
      }

      args.push_back(regPath);
      args.push_back("-o");
      args.push_back(outputPath);

      unsigned int index = 4;
      while (index < argc)
      {
        args.push_back(argv[index++]);
      }

			//////////////////////////////////////////////////
			// Test: behavior on simple mapping task.

			CHECK(spExec->execute(invertRPath, "invertR", args));
			CHECK_EQUAL(0, spExec->getExitValue());

      // TODO: Check result against reference

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
