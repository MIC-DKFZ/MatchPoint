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
#include "mapAlgorithmProfileHelper.h"

namespace map
{
	namespace testing
	{

		int mapAlgorithmProfileHelperTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			::map::core::String validStr =
				"<Profile><Contact>sbr@dkfz.de</Contact><Description>My test description.</Description></Profile>";
			::map::core::String validStr_noDesc = "<Profile></Profile>";
			::map::core::String validStr_full =
				"<Profile><Description>desc</Description><Contact>contact1</Contact><Contact>contact2</Contact><Terms>the terms</Terms><Characteristics><DataType>Image</DataType><ComputationStyle>Analytic</ComputationStyle><Deterministic/><ResolutionStyle>Single</ResolutionStyle><DimMoving>3</DimMoving><ModalityMoving>ModType1</ModalityMoving><ModalityMoving>ModType2</ModalityMoving><DimTarget>2</DimTarget><ModalityTarget>any</ModalityTarget><Subject>sub1</Subject><Object>obj1</Object><TransformModel>rigid</TransformModel><TransformDomain>global</TransformDomain><Optimization>opt1</Optimization><Metric>metric1</Metric></Characteristics><Keywords><Keyword>key1</Keyword><Keyword>key2</Keyword><Keyword>key3</Keyword></Keywords></Profile>";

			::map::core::String emptyStr = "";
			::map::core::String invalidStr = "<profile></profile>";
			::map::core::String invalidStr2 = "<profile>";

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
			// Test profile values getter functions

			CHECK_EQUAL("My test description.", algorithm::profile::getDescription(spValidProfile));
			CHECK_EQUAL("", algorithm::profile::getDescription(spValidProfile_noDesc));
			CHECK_EQUAL("", algorithm::profile::getDescription(spInvalidProfile));

			CHECK(2 == algorithm::profile::getContact(spValidProfile_full).size());
			CHECK_EQUAL("contact1", algorithm::profile::getContact(spValidProfile_full)[0]);
			CHECK_EQUAL("contact2", algorithm::profile::getContact(spValidProfile_full)[1]);
			CHECK(0 == algorithm::profile::getContact(spValidProfile_noDesc).size());

			std::string value;
			CHECK(::map::algorithm::profile::getTerms(spValidProfile_full, value));
			CHECK_EQUAL("the terms", value);
			CHECK(!algorithm::profile::getTerms(spValidProfile_noDesc, value));

			CHECK(1 == algorithm::profile::getDataType(spValidProfile_full).size());
			CHECK_EQUAL("Image", algorithm::profile::getDataType(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getDataType(spValidProfile_noDesc).size());

			CHECK(1 == algorithm::profile::getComputationStyle(spValidProfile_full).size());
			CHECK_EQUAL("Analytic", algorithm::profile::getComputationStyle(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getComputationStyle(spValidProfile_noDesc).size());

			CHECK(::map::algorithm::profile::isDeterministic(spValidProfile_full));
			CHECK(!algorithm::profile::isDeterministic(spValidProfile_noDesc));

			CHECK(1 == algorithm::profile::getResolutionStyle(spValidProfile_full).size());
			CHECK_EQUAL("Single", algorithm::profile::getResolutionStyle(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getResolutionStyle(spValidProfile_noDesc).size());

			unsigned int dimValue;
			CHECK(::map::algorithm::profile::getMovingDimensions(spValidProfile_full, dimValue));
			CHECK_EQUAL(3, dimValue);
			CHECK(!algorithm::profile::getMovingDimensions(spValidProfile_noDesc, dimValue));

			CHECK(2 == algorithm::profile::getMovingModality(spValidProfile_full).size());
			CHECK_EQUAL("ModType1", algorithm::profile::getMovingModality(spValidProfile_full)[0]);
			CHECK_EQUAL("ModType2", algorithm::profile::getMovingModality(spValidProfile_full)[1]);
			CHECK(0 == algorithm::profile::getMovingModality(spValidProfile_noDesc).size());

			CHECK(::map::algorithm::profile::getTargetDimensions(spValidProfile_full, dimValue));
			CHECK_EQUAL(2, dimValue);
			CHECK(!algorithm::profile::getTargetDimensions(spValidProfile_noDesc, dimValue));

			CHECK(1 == algorithm::profile::getTargetModality(spValidProfile_full).size());
			CHECK_EQUAL("any", algorithm::profile::getTargetModality(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getTargetModality(spValidProfile_noDesc).size());

			CHECK(1 == algorithm::profile::getSubject(spValidProfile_full).size());
			CHECK_EQUAL("sub1", algorithm::profile::getSubject(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getSubject(spValidProfile_noDesc).size());

			CHECK(1 == algorithm::profile::getObject(spValidProfile_full).size());
			CHECK_EQUAL("obj1", algorithm::profile::getObject(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getObject(spValidProfile_noDesc).size());

			CHECK(1 == algorithm::profile::getTransformModel(spValidProfile_full).size());
			CHECK_EQUAL("rigid", algorithm::profile::getTransformModel(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getTransformModel(spValidProfile_noDesc).size());

			CHECK(1 == algorithm::profile::getTransformDomain(spValidProfile_full).size());
			CHECK_EQUAL("global", algorithm::profile::getTransformDomain(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getTransformDomain(spValidProfile_noDesc).size());

			CHECK(1 == algorithm::profile::getOptimization(spValidProfile_full).size());
			CHECK_EQUAL("opt1", algorithm::profile::getOptimization(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getOptimization(spValidProfile_noDesc).size());

			CHECK(1 == algorithm::profile::getMetric(spValidProfile_full).size());
			CHECK_EQUAL("metric1", algorithm::profile::getMetric(spValidProfile_full)[0]);
			CHECK(0 == algorithm::profile::getMetric(spValidProfile_noDesc).size());

			CHECK(3 == algorithm::profile::getKeywords(spValidProfile_full).size());
			CHECK_EQUAL("key1", algorithm::profile::getKeywords(spValidProfile_full)[0]);
			CHECK_EQUAL("key2", algorithm::profile::getKeywords(spValidProfile_full)[1]);
			CHECK_EQUAL("key3", algorithm::profile::getKeywords(spValidProfile_full)[2]);
			CHECK(0 == algorithm::profile::getKeywords(spValidProfile_noDesc).size());


			//////////////////////////////////////////////////////////
			// Test profile values getter functions (string version
			CHECK_EQUAL("My test description.", algorithm::profile::getDescription(validStr));
			CHECK_EQUAL("", algorithm::profile::getDescription(validStr_noDesc));
			CHECK_EQUAL("", algorithm::profile::getDescription(invalidStr));

			CHECK(2 == algorithm::profile::getContact(validStr_full).size());
			CHECK_EQUAL("contact1", algorithm::profile::getContact(validStr_full)[0]);
			CHECK_EQUAL("contact2", algorithm::profile::getContact(validStr_full)[1]);
			CHECK(0 == algorithm::profile::getContact(validStr_noDesc).size());

			CHECK(::map::algorithm::profile::getTerms(validStr_full, value));
			CHECK_EQUAL("the terms", value);
			CHECK(!algorithm::profile::getTerms(validStr_noDesc, value));

			CHECK(1 == algorithm::profile::getDataType(validStr_full).size());
			CHECK_EQUAL("Image", algorithm::profile::getDataType(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getDataType(validStr_noDesc).size());

			CHECK(1 == algorithm::profile::getComputationStyle(validStr_full).size());
			CHECK_EQUAL("Analytic", algorithm::profile::getComputationStyle(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getComputationStyle(validStr_noDesc).size());

			CHECK(::map::algorithm::profile::isDeterministic(validStr_full));
			CHECK(!algorithm::profile::isDeterministic(validStr_noDesc));

			CHECK(1 == algorithm::profile::getResolutionStyle(validStr_full).size());
			CHECK_EQUAL("Single", algorithm::profile::getResolutionStyle(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getResolutionStyle(validStr_noDesc).size());

			CHECK(::map::algorithm::profile::getMovingDimensions(validStr_full, dimValue));
			CHECK_EQUAL(3, dimValue);
			CHECK(!algorithm::profile::getMovingDimensions(validStr_noDesc, dimValue));

			CHECK(2 == algorithm::profile::getMovingModality(validStr_full).size());
			CHECK_EQUAL("ModType1", algorithm::profile::getMovingModality(validStr_full)[0]);
			CHECK_EQUAL("ModType2", algorithm::profile::getMovingModality(validStr_full)[1]);
			CHECK(0 == algorithm::profile::getMovingModality(validStr_noDesc).size());

			CHECK(::map::algorithm::profile::getTargetDimensions(validStr_full, dimValue));
			CHECK_EQUAL(2, dimValue);
			CHECK(!algorithm::profile::getTargetDimensions(validStr_noDesc, dimValue));

			CHECK(1 == algorithm::profile::getTargetModality(validStr_full).size());
			CHECK_EQUAL("any", algorithm::profile::getTargetModality(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getTargetModality(validStr_noDesc).size());

			CHECK(1 == algorithm::profile::getSubject(validStr_full).size());
			CHECK_EQUAL("sub1", algorithm::profile::getSubject(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getSubject(validStr_noDesc).size());

			CHECK(1 == algorithm::profile::getObject(validStr_full).size());
			CHECK_EQUAL("obj1", algorithm::profile::getObject(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getObject(validStr_noDesc).size());

			CHECK(1 == algorithm::profile::getTransformModel(validStr_full).size());
			CHECK_EQUAL("rigid", algorithm::profile::getTransformModel(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getTransformModel(validStr_noDesc).size());

			CHECK(1 == algorithm::profile::getTransformDomain(validStr_full).size());
			CHECK_EQUAL("global", algorithm::profile::getTransformDomain(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getTransformDomain(validStr_noDesc).size());

			CHECK(1 == algorithm::profile::getOptimization(validStr_full).size());
			CHECK_EQUAL("opt1", algorithm::profile::getOptimization(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getOptimization(validStr_noDesc).size());

			CHECK(1 == algorithm::profile::getMetric(validStr_full).size());
			CHECK_EQUAL("metric1", algorithm::profile::getMetric(validStr_full)[0]);
			CHECK(0 == algorithm::profile::getMetric(validStr_noDesc).size());

			CHECK(3 == algorithm::profile::getKeywords(validStr_full).size());
			CHECK_EQUAL("key1", algorithm::profile::getKeywords(validStr_full)[0]);
			CHECK_EQUAL("key2", algorithm::profile::getKeywords(validStr_full)[1]);
			CHECK_EQUAL("key3", algorithm::profile::getKeywords(validStr_full)[2]);
			CHECK(0 == algorithm::profile::getKeywords(validStr_noDesc).size());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
