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

#include "mapStaticServiceStack.h"
#include "mapTestServiceProvider.h"
#include "mapTestLoadPolicy.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		typedef core::services::ServiceStack<TestServiceProviderBase, TestLoadPolicy>
		ConcreteTestServiceStackType;
		typedef core::services::StaticServiceStack<ConcreteTestServiceStackType> StaticTestServiceStackType;

		int mapStaticServiceStackTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			CHECK(true == StaticTestServiceStackType::providerIsAvailable(1));
			CHECK(false == StaticTestServiceStackType::providerIsAvailable(5));
			CHECK(2 == StaticTestServiceStackType::size());

			StaticTestServiceStackType::registerProvider(TestServiceProvider<5>::New());
			CHECK(3 == StaticTestServiceStackType::size()); //must contain 3 providers by now
			CHECK(true == StaticTestServiceStackType::providerIsAvailable(5)); //check if provider is added
			//check if rehash() resets it properly; now only provider 1 and 2 may exist
			StaticTestServiceStackType::rehash();
			CHECK(2 == StaticTestServiceStackType::size()); //must contain 3 providers by now
			CHECK(true == StaticTestServiceStackType::providerIsAvailable(1));
			CHECK(true == StaticTestServiceStackType::providerIsAvailable(2));
			CHECK(false == StaticTestServiceStackType::providerIsAvailable(5));

			//@todo noch prüfen ob unregister und die namenssuche funktionert

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
