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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/test/mapAlgorithmIdentificationBaseTest.cpp $
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
		namespace
		{
			class TestIdentificationInterface : public algorithm::facet::AlgorithmIdentificationInterface
			{
			public:
				mapDefineAlgorithmUIDMacro("DKFZ::SIDT", "TestInterface", "1.0.0", "x");

				TestIdentificationInterface()
				{
				}
			};

			class TestIdentificationInterface2 : public algorithm::facet::AlgorithmIdentificationInterface
			{
			public:
				mapDefineAlgorithmUIDWithAutmaticBuildNRMacro("DKFZ::SIDT", "TestInterface2", "1.0.0");

				TestIdentificationInterface2()
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

			TestIdentificationInterface2::UIDPointer spUID2;

			CHECK_NO_THROW(spUIDStatic = TestIdentificationInterface::UID());

			CHECK_EQUAL("DKFZ::SIDT", spUIDStatic->getNamespace());
			CHECK_EQUAL("TestInterface", spUIDStatic->getName());
			CHECK_EQUAL("1.0.0", spUIDStatic->getVersion());
			CHECK_EQUAL("x", spUIDStatic->getBuildTag());

			CHECK_NO_THROW(spUID = testInterface.getUID());

			CHECK_EQUAL("DKFZ::SIDT", spUID->getNamespace());
			CHECK_EQUAL("TestInterface", spUID->getName());
			CHECK_EQUAL("1.0.0", spUID->getVersion());
			CHECK_EQUAL("x", spUID->getBuildTag());

			CHECK_NO_THROW(spUID2 = TestIdentificationInterface2::UID());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
