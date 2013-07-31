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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Utilities/test/mapProcessExecutorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litCheckMacros.h"
#include "mapProcessExecutor.h"

#include "itksys/SystemTools.hxx"
#include "itkCommand.h"

namespace map
{
	namespace testing
	{

		map::core::String testCOUT;
		map::core::String testCERR;

		void onRegistrationEvent(itk::Object *pCaller, const itk::EventObject &e, void *)
		{
			const map::events::ExternalProcessStdOutEvent *pEvent = dynamic_cast<const map::events::ExternalProcessStdOutEvent *>(&e);

			if (pEvent)
			{
				testCOUT = testCOUT + pEvent->getComment();
			}

			const map::events::ExternalProcessStdErrEvent *pErrEvent = dynamic_cast<const map::events::ExternalProcessStdErrEvent *>(&e);

			if (pErrEvent)
			{
				testCERR = testCERR + pErrEvent->getComment();
			}
		}

		//defined by mapDeploymentTests.cpp. It is the path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char *_callingAppPath;

		int mapProcessExecutorTest(int argc, char *argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string callingPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();

			//Add observer for algorithm events.
			itk::CStyleCommand::Pointer spCommand = itk::CStyleCommand::New();
			spCommand->SetCallback(&onRegistrationEvent);

			spExec->AddObserver(map::events::ExternalProcessOutputEvent(), spCommand);

			map::utilities::ProcessExecutor::ArgumentListType args;

			CHECK_EQUAL(false, spExec->getSharedOutputPipes());
			CHECK_NO_THROW(spExec->setSharedOutputPipes(true));
			CHECK_EQUAL(true, spExec->getSharedOutputPipes());
			CHECK_NO_THROW(spExec->setSharedOutputPipes(false));
			CHECK_EQUAL(false, spExec->getSharedOutputPipes());

			args.clear();
			args.push_back("my");
			args.push_back("test");
			args.push_back("arguments");

			testCERR = "";
			testCOUT = "";

			CHECK(spExec->execute(callingPath, "mapTestProcessExecutorApp", args));
			CHECK_EQUAL(3, spExec->getExitValue());
			CHECK_EQUAL("my test arguments ", testCOUT);
			CHECK_EQUAL("test error output", testCERR);

			args.clear();
			args.push_back(map::utilities::ProcessExecutor::getOSDependendExecutableName("mapTestProcessExecutorApp"));
			args.push_back("my");
			args.push_back("other");
			args.push_back("test");
			args.push_back("arguments");

			testCERR = "";
			testCOUT = "";

			CHECK(spExec->execute(callingPath, args));
			CHECK_EQUAL(4, spExec->getExitValue());
			CHECK_EQUAL("my other test arguments ", testCOUT);
			CHECK_EQUAL("test error output", testCERR);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
