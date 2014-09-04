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

		int mapRSimpleMappingTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string mapRPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			std::string inputPath = "Input Data path not set.";
      std::string regPath = "Reg data path not set.";
      std::string outputPath = "Output data path not set.";
      std::string refPath = "Reference data path not set.";

			map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();
      spExec->setSharedOutputPipes(true);

			map::utilities::ProcessExecutor::ArgumentListType args;

      if (argc > 1)
			{
				inputPath = argv[1];
			}

      if (argc > 2)
      {
        regPath = argv[2];
      }

      if (argc > 3)
      {
        outputPath = argv[3];
      }

      if (argc > 4)
      {
        refPath = argv[4];
      }

      args.push_back(inputPath);
      args.push_back(regPath);
      args.push_back("-o");
      args.push_back(outputPath);

      unsigned int index = 5;
      while (index < argc)
      {
        args.push_back(argv[index++]);
      }

			//////////////////////////////////////////////////
			// Test: behavior on simple mapping task.

			CHECK(spExec->execute(mapRPath, "mapR", args));
			CHECK_EQUAL(0, spExec->getExitValue());

      // Check result against reference
      typedef itk::Image<unsigned char, 3> TestImageType;

      TestImageType::Pointer refImage = map::io::readImage<unsigned char, unsigned char, 3>(refPath);
      TestImageType::Pointer outputImage = map::io::readImage<unsigned char, unsigned char, 3>(outputPath);

	    lit::ImageTester<TestImageType, TestImageType> tester;
	    tester.setExpectedImage(refImage);
	    tester.setActualImage(outputImage);
	    tester.setCheckThreshold(0.0);

	    CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
