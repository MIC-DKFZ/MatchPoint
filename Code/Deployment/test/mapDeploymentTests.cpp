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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/test/mapDeploymentTests.cpp $
*/

// this file defines the mapCoreTests for the test driver
// and all it expects is that you have a function called registerTests()
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapExceptionObject.h"
#include "litMultiTestsMain.h"

namespace map
{
	namespace testing
	{

		const char *_callingAppPath = NULL;

		void registerTests()
		{
			LIT_REGISTER_TEST(mapDeploymentDLLHelperTest);
			LIT_REGISTER_TEST(mapDeploymentDLLInfoTest);
			LIT_REGISTER_TEST(mapDeploymentDLLHandleTest);
			LIT_REGISTER_TEST(mapDeploymentDLLAccessTest);
			LIT_REGISTER_TEST(mapDeploymentDLLBrowserTest);
			LIT_REGISTER_TEST(mapDeploymentDLLConfigTest);
		}

	} //namespace testing
} //namespace map


int main(int argc, char *argv[])
{
	int result = 0;

	map::testing::registerTests();

	if (argc > 0)
	{
		map::testing::_callingAppPath = argv[0];
	}

	try
	{
		result = lit::multiTestsMain(argc, argv);
	}
	catch (const map::core::ExceptionObject &e)
	{
		std::cerr << "MatchPoint test driver caught an MatchPoint exception:\n";
		e.Print(std::cerr);
		std::cerr << "\n";
		result = -1;
	}
	catch (const itk::ExceptionObject &e)
	{
		std::cerr << "MatchPoint test driver caught an ITK exception:\n";
		std::cerr << e.GetFile() << ":" << e.GetLine() << ":\n"
		          << e.GetDescription() << "\n";
		result = -1;
	}
	catch (const std::exception &e)
	{
		std::cerr << "MatchPoint test driver caught an exception:\n";
		std::cerr << e.what() << "\n";
		result = -1;
	}
	catch (...)
	{
		std::cerr << "MatchPoint test driver caught an unknown exception!!!\n";
		result = -1;
	}

	return result;
}
