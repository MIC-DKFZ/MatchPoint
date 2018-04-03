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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapServiceStack.h"
#include "mapTestServiceProvider.h"
#include "mapTestLoadPolicy.h"
#include "mapGenericStaticLoadPolicyBase.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		typedef core::services::ServiceStack<TestServiceProviderBase, TestLoadPolicy> TestServiceStackType;

		int mapGenericStaticLoadPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestServiceStackType::Pointer spStack1 = TestServiceStackType::New(true);
			TestServiceStackType::Pointer spStack2 = TestServiceStackType::New(false);

			//check automatic rehash on construction
			CHECK_EQUAL(2, spStack1->size()); //must contain 2 providers by now
			CHECK_EQUAL(0, spStack2->size()); //must contain 2 providers by now

			//check manual rehash on empty steck
			spStack2->rehash();
			CHECK_EQUAL(2, spStack2->size()); //must contain 2 providers by now

			//check if the right providers were loaded.
			CHECK_EQUAL(true, spStack1->providerIsAvailable(1));
			CHECK_EQUAL(true, spStack1->providerIsAvailable(2));
			CHECK_EQUAL(false, spStack1->providerIsAvailable(4)); //this request cannot be handled

			//modify stack
			spStack1->registerProvider(TestServiceProvider<5>::New());
			CHECK_EQUAL(3, spStack1->size()); //must contain 3 providers by now
			CHECK_EQUAL(true, spStack1->providerIsAvailable(5)); //check if provider is added
			//check if rehash() resets it properly; now only provider 1 and 2 may exist
			spStack1->rehash();
			CHECK_EQUAL(2, spStack1->size()); //must contain 3 providers by now
			CHECK_EQUAL(true, spStack1->providerIsAvailable(1));
			CHECK_EQUAL(true, spStack1->providerIsAvailable(2));
			CHECK_EQUAL(false, spStack1->providerIsAvailable(5));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}

	} //namespace testing
} //namespace map
