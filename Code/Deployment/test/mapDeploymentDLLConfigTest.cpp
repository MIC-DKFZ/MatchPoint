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


#include "mapDeploymentDLLAccess.h"
#include "mapLogbook.h"
#include "mapFileDispatch.h"

#include "litCheckMacros.h"

#include "itksys/SystemTools.hxx"
#include "itkDynamicLoader.h"

namespace map
{
	namespace testing
	{

		//defined by mapDeploymentTests.cpp. It is tha path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char* _callingAppPath;

		int mapDeploymentDLLConfigTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			map::core::String dllPath = itksys::SystemTools::GetProgramPath(_callingAppPath);
			map::core::String logPath = dllPath;

			if (argc > 1)
			{
				logPath = argv[1];
			}

			logPath = map::core::FileDispatch::createFullPath(logPath, "DeploymentSyncTest.log");

			if (itksys::SystemTools::FileExists(logPath.c_str(), true))
			{
				itksys::SystemTools::RemoveFile(logPath.c_str());
			}

			map::core::Logbook::setDefaultLogFileName(logPath);
			map::core::Logbook::fatal("Initialize Log for sync test. Waiting for dll entry...");

			//Test open special test dll that should post a special log entryfile in the test log
			deployment::DLLHandle::Pointer spHandle1 = NULL;

			std::string validDLLPath = map::core::FileDispatch::createFullPath(dllPath,
									   map::core::String(itksys::DynamicLoader::LibPrefix()) + "mapTestAlgorithmConfig" +
									   itksys::DynamicLoader::LibExtension());

			spHandle1 = map::deployment::openDeploymentDLL(validDLLPath);

			map::algorithm::RegistrationAlgorithmBase::Pointer spInstance = NULL;
			spInstance = map::deployment::getRegistrationAlgorithm(spHandle1);

			//now test for the log entry;
			map::core::Logbook::flush();
			std::ifstream logFile;
			logFile.open(logPath.c_str());
			map::core::String fileContent;

			bool foundDLLTokenInLog = false;

			while (!logFile.fail())
			{
				map::core::String line;
				logFile >> line;
				fileContent.append(line);
			}

			logFile.close();

			foundDLLTokenInLog = map::core::String::npos != fileContent.find("TestEntryOfTheDll.");

			CHECK(foundDLLTokenInLog);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
