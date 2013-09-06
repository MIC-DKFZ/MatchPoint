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
      core::String validStr_noDesc = "<Profile></Profile>";
      core::String validStr_full = "<Profile><Description>desc</Description><Contact>contact1</Contact><Contact>contact2</Contact><Terms>the terms</Terms><Characteristics><DataType>Image</DataType><ResolutionStyle>Single</ResolutionStyle><DimMoving>3</DimMoving><ModalityMoving>ModType1</ModalityMoving><ModalityMoving>ModType2</ModalityMoving><DimTarget>2</DimTarget><ModalityTarget>any</ModalityTarget><Subject>sub1</Subject><Object>obj1</Object><TransformModel>rigid</TransformModel><TransformDomain>global</TransformDomain><Optimization>opt1</Optimization></Characteristics><Keywords><Keyword>key1</Keyword><Keyword>key2</Keyword><Keyword>key3</Keyword></Keywords></Profile>";

      core::String emptyStr = "";
      core::String invalidStr = "<profile></profile>";
      core::String invalidStr2 = "<profile>";

      //////////////////////////////////////////////////////////
      // Test parseProfileString
      
      structuredData::Element::Pointer spValidProfile;
      CHECK_NO_THROW(spValidProfile = algorithm::profile::parseProfileString(validStr));
      CHECK(spValidProfile.IsNotNull());

      structuredData::Element::Pointer spValidProfile_noDesc;
      CHECK_NO_THROW(spValidProfile_noDesc = algorithm::profile::parseProfileString(validStr_noDesc));
      CHECK(spValidProfile_noDesc.IsNotNull());

      structuredData::Element::Pointer spValidProfile_full;
      CHECK_NO_THROW(spValidProfile_full = algorithm::profile::parseProfileString(validStr_full));
      CHECK(spValidProfile_full.IsNotNull());

      structuredData::Element::Pointer spInvalidProfile;
      CHECK_NO_THROW(spInvalidProfile = algorithm::profile::parseProfileString(emptyStr));
      CHECK(spInvalidProfile.IsNull());

      CHECK_NO_THROW(spInvalidProfile = algorithm::profile::parseProfileString(invalidStr));
      CHECK(spInvalidProfile.IsNull());

      CHECK_NO_THROW(spInvalidProfile = algorithm::profile::parseProfileString(invalidStr2));
      CHECK(spInvalidProfile.IsNull());

      //////////////////////////////////////////////////////////
      // Test getAlgorithmDescription

      CHECK_EQUAL("My test description.", algorithm::profile::getDescription(spValidProfile));
      CHECK_EQUAL("", algorithm::profile::getDescription(spValidProfile_noDesc));
      CHECK_EQUAL("", algorithm::profile::getDescription(spInvalidProfile));

      CHECK(2 == algorithm::profile::getContact(spValidProfile_full).size());
      CHECK_EQUAL("contact1", algorithm::profile::getContact(spValidProfile_full)[0]);
      CHECK_EQUAL("contact2", algorithm::profile::getContact(spValidProfile_full)[1]);
      CHECK(0 == algorithm::profile::getContact(spValidProfile_noDesc).size());

      std::string value;
      CHECK(algorithm::profile::getTerms(spValidProfile_full,value));
      CHECK_EQUAL("the terms", value);
      CHECK(!algorithm::profile::getTerms(spValidProfile_noDesc,value));

      CHECK(1 == algorithm::profile::getDataType(spValidProfile_full).size());
      CHECK_EQUAL("Image", algorithm::profile::getDataType(spValidProfile_full)[0]);
      CHECK(0 == algorithm::profile::getDataType(spValidProfile_noDesc).size());

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace map
