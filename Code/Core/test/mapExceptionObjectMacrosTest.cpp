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

#include "mapExceptionObjectMacros.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		/*This is needed as a work around to ensure the correct working of mapDeclareExcpetionClassMacro
		  in this test unit. */
#if (defined(_WIN32) || defined(WIN32)) && !defined(MAP_STATIC)
#undef MAPCore_EXPORT
#define MAPCore_EXPORT __declspec(dllexport)
#endif

		//Test the macro declaration and definition of exception classes
		mapDeclareExceptionClassMacro(TestException, map::core::ExceptionObject);

		/*This is needed as a work around to ensure the correct working of mapDeclareExcpetionClassMacro
		  in this test unit. */
#if (defined(_WIN32) || defined(WIN32)) && !defined(MAP_STATIC)
#undef MAPCore_EXPORT
#  define MAPCore_EXPORT __declspec(dllimport)
#endif

		mapDefineExceptionClassMacro(TestException);

		int mapExceptionObjectMacrosTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			//now check if the macro definition of the TestException class worked well.
			TestException e;

			TestException e1("test.file", 1);

			TestException e2(std::string("test.file"), 1);

			TestException e3(std::string("test.file"), 1, "Description", "Location");

			CHECK_EQUAL("", e.GetFile());
			CHECK_EQUAL(0, e.GetLine());
			CHECK_EQUAL("", e.GetDescription());
			CHECK_EQUAL("", e.GetLocation());

			CHECK_EQUAL("test.file", e1.GetFile());
			CHECK_EQUAL(1, e1.GetLine());
			CHECK_EQUAL("None", e1.GetDescription());
			CHECK_EQUAL("Unknown", e1.GetLocation());

			CHECK_EQUAL("test.file", e2.GetFile());
			CHECK_EQUAL(1, e2.GetLine());
			CHECK_EQUAL("None", e2.GetDescription());
			CHECK_EQUAL("Unknown", e2.GetLocation());

			CHECK_EQUAL("test.file", e3.GetFile());
			CHECK_EQUAL(1, e3.GetLine());
			CHECK_EQUAL("Description", e3.GetDescription());
			CHECK_EQUAL("Location", e3.GetLocation());

			CHECK_EQUAL("map::TestException", e.GetNameOfClass());

			//check cloning
			TestException::BaseExceptionType* pClone = NULL;

			CHECK_NO_THROW(pClone = e3.clone());

			CHECK(pClone != NULL);

			CHECK_EQUAL(e3.GetNameOfClass(), pClone->GetNameOfClass());

			CHECK_EQUAL(e3.GetFile(), pClone->GetFile());
			CHECK_EQUAL(e3.GetLine(), pClone->GetLine());
			CHECK_EQUAL(e3.GetDescription(), pClone->GetDescription());
			CHECK_EQUAL(e3.GetLocation(), pClone->GetLocation());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map

