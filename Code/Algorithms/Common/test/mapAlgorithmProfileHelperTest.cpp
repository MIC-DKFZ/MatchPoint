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
#include "mapAlgorithmProfileHelper.h"

namespace map
{
  namespace testing
  {
    
    int mapAlgorithmProfileHelperTest(int, char* [])
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      core::String validStr = "<Profile><Contact>sbr@dkfz.de</Contact><Description>My test description.</Description></Profile>";
      core::String validStr_noDesc = "<Profile><Contact>sbr@dkfz.de</Contact></Profile>";
      core::String emptyStr = "";
      core::String invalidStr = "<profile></profile>";
      core::String invalidStr2 = "<profile>";

      //////////////////////////////////////////////////////////
      // Test parseProfileString
      
      structuredData::Element::Pointer spValidProfile;
      CHECK_NO_THROW(spValidProfile = algorithm::parseProfileString(validStr));
      CHECK(spValidProfile.IsNotNull());

      structuredData::Element::Pointer spValidProfile_noDesc;
      CHECK_NO_THROW(spValidProfile_noDesc = algorithm::parseProfileString(validStr_noDesc));
      CHECK(spValidProfile_noDesc.IsNotNull());

      structuredData::Element::Pointer spInvalidProfile;
      CHECK_NO_THROW(spInvalidProfile = algorithm::parseProfileString(emptyStr));
      CHECK(spInvalidProfile.IsNull());

      CHECK_NO_THROW(spInvalidProfile = algorithm::parseProfileString(invalidStr));
      CHECK(spInvalidProfile.IsNull());

      CHECK_NO_THROW(spInvalidProfile = algorithm::parseProfileString(invalidStr2));
      CHECK(spInvalidProfile.IsNull());

      //////////////////////////////////////////////////////////
      // Test getAlgorithmDescription

      CHECK_EQUAL("My test description.", algorithm::getAlgorithmDescription(spValidProfile));
      CHECK_EQUAL("", algorithm::getAlgorithmDescription(spValidProfile_noDesc));
      CHECK_EQUAL("", algorithm::getAlgorithmDescription(spInvalidProfile));

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace map
