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

#include "litCheckMacros.h"
#include "mapAlgorithmIdentificationInterface.h"

namespace map
{
	namespace testing
	{
		mapGenerateAlgorithmUIDPolicyMacro(TestUIDPolicy, "de.dkfz.matchpoint", "TestInterface", "1.0.0",
										   "<Profile><Description>description</Description></Profile>");

		namespace
		{

			class TestIdentificationInterface : public algorithm::facet::AlgorithmIdentificationInterface,
				public TestUIDPolicy
			{
			public:
				mapDefineAlgorithmIdentificationByPolicyMacro;

				TestIdentificationInterface()
				{
				}
			};

		}

		int mapAlgorithmIdentificationBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestIdentificationInterface testInterface;

			TestIdentificationInterface::UIDPointer spUID;
			TestIdentificationInterface::UIDPointer spUIDStatic;

			CHECK_NO_THROW(spUIDStatic = TestIdentificationInterface::UID());

			CHECK_EQUAL("de.dkfz.matchpoint", spUIDStatic->getNamespace());
			CHECK_EQUAL("TestInterface", spUIDStatic->getName());
			CHECK_EQUAL("1.0.0", spUIDStatic->getVersion());
			//Remark: cannot be tested because tag is dynamically generated CHECK_EQUAL("x", spUIDStatic->getBuildTag());
			CHECK_EQUAL("<Profile><Description>description</Description></Profile>",
						TestIdentificationInterface::AlgorithmProfile());
			CHECK_EQUAL("description", TestIdentificationInterface::AlgorithmDescription());


			CHECK_NO_THROW(spUID = testInterface.getUID());

			CHECK_EQUAL("de.dkfz.matchpoint", spUID->getNamespace());
			CHECK_EQUAL("TestInterface", spUID->getName());
			CHECK_EQUAL("1.0.0", spUID->getVersion());
			CHECK_EQUAL("<Profile><Description>description</Description></Profile>",
						testInterface.getAlgorithmProfile());
			CHECK_EQUAL("description", testInterface.getAlgorithmDescription());

			CHECK(map::algorithm::compareUIDs(spUID, spUIDStatic));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
