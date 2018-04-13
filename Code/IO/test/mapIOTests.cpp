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

// this file defines the mapCoreTests for the test driver
// and all it expects is that you have a function called RegisterTests
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapExceptionObject.h"

#include "litMultiTestsMain.h"

namespace map
{
	namespace testing
	{
		void registerTests()
		{
			LIT_REGISTER_TEST(mapMatrixModelBasedKernelWriterTest);
			LIT_REGISTER_TEST(mapMatrixModelBasedKernelLoaderTest);
			LIT_REGISTER_TEST(mapNullRegistrationKernelWriterTest);
			LIT_REGISTER_TEST(mapExpandingFieldKernelWriterTest);
			LIT_REGISTER_TEST(mapLazyFileFieldKernelLoaderTest);
      LIT_REGISTER_TEST(mapLazyFieldFileKernelWriterTest);
      LIT_REGISTER_TEST(mapFieldKernelLoaderTest);
			LIT_REGISTER_TEST(mapInvertingKernelWriterTest);
			LIT_REGISTER_TEST(mapInvertingKernelLoaderTest);
			LIT_REGISTER_TEST(mapRegistrationFileWriterTest);
			LIT_REGISTER_TEST(mapRegistrationFileReaderTest);
		}
	}
}

int main(int argc, char* argv[])
{
	int result = 0;

	map::testing::registerTests();

	try
	{
		result = lit::multiTestsMain(argc, argv);
	}
	catch (const map::core::ExceptionObject& e)
	{
		std::cerr << "MatchPoint test driver caught an MatchPoint exception:\n";
		e.Print(std::cerr);
		std::cerr << "\n";
		result = -1;
	}
	catch (const itk::ExceptionObject& e)
	{
		std::cerr << "MatchPoint test driver caught an ITK exception:\n";
		std::cerr << e.GetFile() << ":" << e.GetLine() << ":\n"
				  << e.GetDescription() << "\n";
		result = -1;
	}
	catch (const std::exception& e)
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
