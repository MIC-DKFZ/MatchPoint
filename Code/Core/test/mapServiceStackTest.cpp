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
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		typedef core::services::ServiceStack<TestServiceProviderBase> TestServiceStackType;

		int mapServiceStackTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestServiceStackType::Pointer spStack = TestServiceStackType::New();

			TestServiceProvider<1>::Pointer spProvider1 = TestServiceProvider<1>::New();
			TestServiceProvider<1>::Pointer spProvider1b = TestServiceProvider<1>::New();
			TestServiceProvider<2>::Pointer spProvider2 = TestServiceProvider<2>::New();
			TestServiceProvider<3>::Pointer spProvider3 = TestServiceProvider<3>::New();

			//check basic registration
			CHECK_EQUAL(true, spStack->registerProvider(spProvider1));
			CHECK_EQUAL(false, spStack->registerProvider(spProvider1));
			CHECK_EQUAL(true, spStack->registerProvider(spProvider2));
			CHECK_EQUAL(true, spStack->registerProvider(spProvider3));
			CHECK_EQUAL(3, spStack->size()); //must contain 3 providers by now

			//check basic provider retrieval by request
			CHECK_EQUAL(spProvider1, spStack->getProvider(1));
			CHECK_EQUAL(spProvider2, spStack->getProvider(2));
			CHECK_EQUAL(spProvider3, spStack->getProvider(3));
			CHECK(NULL == spStack->getProvider(4)); //this request cannot be handled

			//check basic provider retrieval by provider name
			CHECK_EQUAL(spProvider1, spStack->getProvider(spProvider1->getProviderName()));
			CHECK_EQUAL(spProvider2, spStack->getProvider(spProvider2->getProviderName()));
			CHECK_EQUAL(spProvider3, spStack->getProvider(spProvider3->getProviderName()));
			CHECK(NULL == spStack->getProvider("non_existant"));

			//check provider check
			CHECK_EQUAL(true, spStack->providerIsAvailable(1));
			CHECK_EQUAL(false, spStack->providerIsAvailable(4));

			//register second provider that can handle request "1", in order to
			//check "LIFU feature" (last in, first used)
			CHECK_EQUAL(true, spStack->registerProvider(spProvider1b));
			CHECK_EQUAL(4, spStack->size()); //now we should have 4 providers

			//checking for request "1" should now return latest registered provider
			CHECK_EQUAL(spProvider1b, spStack->getProvider(1));
			CHECK_EQUAL(spProvider1b, spStack->getProvider(spProvider1->getProviderName()));

			//remove second request "1" provider (sr1p)
			CHECK_EQUAL(true, spStack->unregisterProviderByPointer(spProvider1b));
			CHECK_EQUAL(3, spStack->size()); //size must now be 3 again
			//remove sr1p a second time -> no change
			CHECK_EQUAL(false, spStack->unregisterProviderByPointer(spProvider1b));
			CHECK_EQUAL(3, spStack->size());
			//size still 3, first request "1" provider (fr1p) should not be removed
			CHECK_EQUAL(spProvider1, spStack->getProvider(1)); //so check for it

			//register sr1p once again
			spStack->registerProvider(spProvider1b);
			CHECK_EQUAL(4, spStack->size());
			//remove sr1p by name -> only sr1p but not fr1p should be removed
			CHECK_EQUAL(true, spStack->unregisterProvider(spProvider1b->getProviderName()));
			CHECK_EQUAL(3, spStack->size());
			CHECK_EQUAL(spProvider1, spStack->getProvider(1));
			CHECK(spProvider1b != spStack->getProvider(1));

			//remove fr1p by using the same provider name
			CHECK_EQUAL(true, spStack->unregisterProvider(spProvider1b->getProviderName()));
			CHECK(spProvider1 != spStack->getProvider(1));
			CHECK_EQUAL(2, spStack->size());

			//try to remove fr1p by using the same provider name again
			//-> fails no provider with this name in stack
			CHECK_EQUAL(false, spStack->unregisterProvider(spProvider1b->getProviderName()));

			//check unregisterAll
			CHECK_NO_THROW(spStack->unregisterAll());
			CHECK_EQUAL(0, spStack->size());

			//check reHash
			spStack->registerProvider(spProvider1);
			CHECK_EQUAL(1, spStack->size());
			CHECK_NO_THROW(spStack->rehash());
			CHECK_EQUAL(0, spStack->size());

			//check smartpointer functionality
			spStack->registerProvider(spProvider1);
			TestServiceProvider<1>* pProvider1 = spProvider1;
			spProvider1 = NULL;
			//because stack operates like a smart pointer access to provider must still be legal
			CHECK_NO_THROW(pProvider1->GetReferenceCount());
			//  spStack->unregisterProvider(pProvider1->getProviderName());
			//  //now access should be illegal
			//  CHECK_THROW(pProvider1->getProviderName());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
