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
#include "mapMetaProperty.h"
#include "mapMetaPropertyAccessor.h"

#include "mapTestMetaPropertyAlgorithm.h"

namespace map
{
	namespace testing
	{

		int mapMetaPropertyAlgorithmBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef TestMetaPropertyAlgorithm TestInterfaceType;

			TestInterfaceType testInterface;


			//////////////////////////////////////
			//Test property info generation

			TestInterfaceType::MetaPropertyVectorType infos = testInterface.getPropertyInfos();

			CHECK_EQUAL(5, infos.size());
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));

			::map::algorithm::MetaPropertyInfo::Pointer spCountInfo;

			CHECK_NO_THROW(spCountInfo = testInterface.getPropertyInfo("Count"));
			CHECK(spCountInfo.IsNotNull());
			CHECK("Count" ==
				  spCountInfo->getName()); //just ensure that it is realy the right info, correct setting
			//and getting of info attributes is tested in MetaPropertInfoTest

			//now the compile methods must have been executed 2 times
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));

			::map::algorithm::MetaPropertyInfo::Pointer spSecretInfo;

			CHECK_NO_THROW(spSecretInfo = testInterface.getPropertyInfo("SecretIngredient"));
			CHECK(spSecretInfo.IsNotNull());
			CHECK("SecretIngredient" == spSecretInfo->getName());

			::map::algorithm::MetaPropertyInfo::Pointer spUnkownInfo;

			CHECK_NO_THROW(spUnkownInfo = testInterface.getPropertyInfo("UnkownProperty"));
			CHECK(spUnkownInfo.IsNull());

			//////////////////////////////////////
			//Test getProperty functions
			testInterface.recorder.resetRecorder();

			//test overloaded version: string
			TestInterfaceType::MetaPropertyPointer spSize;
			TestInterfaceType::MetaPropertyPointer spSecret;

			CHECK_NO_THROW(spSize = testInterface.getProperty("Size"));
			CHECK(spSize.IsNotNull());
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doGetPropertyID));
			int testInt = 0;
			CHECK(::map::core::unwrapMetaProperty(spSize, testInt));
			CHECK_EQUAL(testInterface._size, testInt);

			//check behaviour in case of nonreadable property
			TestInterfaceType::MetaPropertyPointer spHole;

			CHECK_NO_THROW(spHole = testInterface.getProperty("BlackHole"));
			CHECK(spHole.IsNull());
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doGetPropertyID));

			//check behaviour in case of unkown property
			TestInterfaceType::MetaPropertyPointer spUnkown;

			CHECK_NO_THROW(spUnkown = testInterface.getProperty("UnkownProperty"));
			CHECK(spUnkown.IsNull());
			CHECK_EQUAL(3, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doGetPropertyID));

			//check behaviour in case of protected property
			CHECK_NO_THROW(spSecret = testInterface.getProperty("SecretIngredient"));
			CHECK(spSecret.IsNotNull());
			CHECK_EQUAL(4, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::doGetPropertyID));
			float testfloat = 0.0;
			CHECK(::map::core::unwrapMetaProperty(spSecret, testfloat));
			CHECK_EQUAL(testInterface._secret, testfloat);

			//test overloaded version: MetaPropertyInfo
			testInterface.recorder.resetRecorder();

			::map::algorithm::MetaPropertyInfo::Pointer spHoleInfo = algorithm::MetaPropertyInfo::New("BlackHole",
					typeid(void*), false, true);
			spUnkownInfo = algorithm::MetaPropertyInfo::New("UnkownProperty", typeid(int));
			::map::algorithm::MetaPropertyInfo::Pointer spIllegalSizeInfo = algorithm::MetaPropertyInfo::New("Size",
					typeid(void*), true, true);

			TestInterfaceType::MetaPropertyPointer spCount;

			CHECK_NO_THROW(spCount = testInterface.getProperty(spCountInfo));
			CHECK(spCount.IsNotNull());
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doGetPropertyID));

			CHECK(::map::core::unwrapMetaProperty(spCount, testInt));
			CHECK_EQUAL(testInterface._count, testInt);

			//check behaviour in case of nonreadable property
			spHole = NULL;

			CHECK_NO_THROW(spHole = testInterface.getProperty(spHoleInfo));
			CHECK(spHole.IsNull());
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doGetPropertyID));

			//check behaviour in case of unkown property
			spUnkown = NULL;

			CHECK_NO_THROW(spUnkown = testInterface.getProperty(spUnkownInfo));
			CHECK(spUnkown.IsNull());
			CHECK_EQUAL(3, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doGetPropertyID));

			//check behaviour in case of illegal property
			spUnkown = NULL;

			CHECK_THROW_EXPLICIT(spUnkown = testInterface.getProperty(spIllegalSizeInfo),
								 core::ExceptionObject);

			//check behaviour in case of illegal property pointer
			CHECK_THROW_EXPLICIT(spUnkown = testInterface.getProperty(NULL), core::ExceptionObject);


			//////////////////////////////////////
			//Test setProperty functions including cache
			testInterface.recorder.resetRecorder();

			//test overloaded version: string
			testInterface._size = 0;
			auto refTime = testInterface.GetMTime();

			CHECK(testInterface.setProperty("Size", spSize));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(0, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));

			CHECK_EQUAL(0, testInterface._size); //it is not changed because it is currently stored in the cache

			CHECK(refTime < testInterface.GetMTime());
			refTime = testInterface.GetMTime();

			TestInterfaceType::MetaPropertyPointer spCachedSize;
			int testCachedInt = 0;
			CHECK_NO_THROW(spCachedSize = testInterface.getProperty("Size"));
			CHECK(::map::core::unwrapMetaProperty(spSize, testInt));
			CHECK(::map::core::unwrapMetaProperty(spCachedSize, testCachedInt));
			CHECK_EQUAL(testInt, testCachedInt);

			testInterface.configureAlgorithmByMetaProperties(); //now transfer values
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(testCachedInt, testInterface._size);

			//check behavior in case of nonwritable property
			CHECK(!testInterface.setProperty("Count", spCount));
			CHECK_EQUAL(3, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(refTime, testInterface.GetMTime());

			//check behavior in case of unknown property
			CHECK(!testInterface.setProperty("UnkownProperty", spCount));
			CHECK_EQUAL(4, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(refTime, testInterface.GetMTime());

			//check behavior in case of illegal property pointer
			CHECK_THROW_EXPLICIT(testInterface.setProperty("IllegalProperty", NULL), core::ExceptionObject);
			CHECK_EQUAL(4, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(refTime, testInterface.GetMTime());

			//check behavior in case of property pointer with wrong type
			::map::core::MetaPropertyBase::Pointer spWrongTypedValue = core::MetaProperty<bool>::New(
						false).GetPointer();
			CHECK_THROW_EXPLICIT(testInterface.setProperty("Size", spWrongTypedValue), core::ExceptionObject);
			CHECK_EQUAL(5, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(refTime, testInterface.GetMTime());


			//test overloaded version: MetaPropertyInfo
			::map::algorithm::MetaPropertyInfo::Pointer spSizeInfo = algorithm::MetaPropertyInfo::New("Size",
					typeid(int), true, true);
			spSize = core::MetaProperty<int>::New(21);

			CHECK(testInterface.setProperty(spSizeInfo, spSize));
			CHECK_EQUAL(6, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(1, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK(refTime < testInterface.GetMTime());
			refTime = testInterface.GetMTime();

			CHECK_EQUAL(testInt,
						testInterface._size); //it is not changed because it is currently stored in the cache

			CHECK_NO_THROW(spCachedSize = testInterface.getProperty("Size"));
			CHECK(::map::core::unwrapMetaProperty(spCachedSize, testCachedInt));
			CHECK_EQUAL(21, testCachedInt);

			testInterface.configureAlgorithmByMetaProperties(); //now transfer values
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(testCachedInt, testInterface._size);

			//check behaviour in case of nonwritable property
			CHECK(!testInterface.setProperty(spCountInfo, spCount));
			CHECK_EQUAL(8, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(refTime, testInterface.GetMTime());

			//check behaviour in case of unkown property
			CHECK(!testInterface.setProperty(spUnkownInfo, spCount));
			CHECK_EQUAL(9, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(refTime, testInterface.GetMTime());

			//check behaviour in case of inconsistent property/propertyinfo
			CHECK_THROW_EXPLICIT(testInterface.setProperty(spIllegalSizeInfo, spSize), core::ExceptionObject);

			//check behaviour in case of illegal property pointer
			CHECK_THROW_EXPLICIT(testInterface.setProperty(spSizeInfo, NULL), core::ExceptionObject);
			CHECK_THROW_EXPLICIT(testInterface.setProperty(NULL, spSize), core::ExceptionObject);
			CHECK_EQUAL(9, testInterface.recorder.getRecordValueCount(TestInterfaceType::compileInfosID));
			CHECK_EQUAL(2, testInterface.recorder.getRecordValueCount(TestInterfaceType::doSetPropertyID));
			CHECK_EQUAL(refTime, testInterface.GetMTime());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
