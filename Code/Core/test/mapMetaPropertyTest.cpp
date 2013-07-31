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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapMetaPropertyTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapMetaProperty.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapMetaPropertyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;


			const std::type_info &intTypeInfo = typeid(int);
			const std::type_info &boolPointerTypeInfo = typeid(bool *);
			const std::type_info &constBoolPointerTypeInfo = typeid(const bool *);

			int refValue1 = 45;
			int refValue2 = 12;
			bool refValue3 = false;
			bool refValue4 = true;
			bool *refPointer1 = &refValue3;
			const bool *refPointer2 = &refValue4;

			typedef map::core::MetaProperty<int> IntProperty;
			typedef map::core::MetaProperty<bool *> BoolPointerProperty;
			typedef map::core::MetaProperty<const bool *> ConstBoolPointerProperty;

			IntProperty::Pointer smpIntProp1 = IntProperty::New(refValue1);
			IntProperty::Pointer smpIntProp2 = IntProperty::New(refValue2);

			BoolPointerProperty::Pointer smpBoolPProp = BoolPointerProperty::New(refPointer1);
			ConstBoolPointerProperty::Pointer smpConstBoolPProp = ConstBoolPointerProperty::New(refPointer2);

			CHECK(intTypeInfo == smpIntProp1->getMetaPropertyTypeInfo());
			CHECK(intTypeInfo == smpIntProp2->getMetaPropertyTypeInfo());
			CHECK(boolPointerTypeInfo == smpBoolPProp->getMetaPropertyTypeInfo());
			CHECK(constBoolPointerTypeInfo == smpConstBoolPProp->getMetaPropertyTypeInfo());

			CHECK_EQUAL(intTypeInfo.name(), smpIntProp1->getMetaPropertyTypeName());
			CHECK_EQUAL(intTypeInfo.name(), smpIntProp2->getMetaPropertyTypeName());
			CHECK_EQUAL(boolPointerTypeInfo.name(), smpBoolPProp->getMetaPropertyTypeName());
			CHECK_EQUAL(constBoolPointerTypeInfo.name(), smpConstBoolPProp->getMetaPropertyTypeName());

			CHECK_EQUAL(refValue1, smpIntProp1->getValue());
			CHECK_EQUAL(refValue2, smpIntProp2->getValue());
			CHECK_EQUAL(refPointer1, smpBoolPProp->getValue());
			CHECK_EQUAL(refPointer2, smpConstBoolPProp->getValue());

			smpIntProp1->setValue(refValue2);
			CHECK_EQUAL(refValue2, smpIntProp1->getValue());

			smpConstBoolPProp->setValue(refPointer1);
			CHECK_EQUAL(refPointer1, smpConstBoolPProp->getValue());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
