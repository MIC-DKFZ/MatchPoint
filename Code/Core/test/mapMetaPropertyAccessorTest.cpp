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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapMetaPropertyAccessorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapMetaProperty.h"
#include "mapSmartMetaProperty.h"
#include "mapMetaPropertyAccessor.h"
#include "litCheckMacros.h"

#include "itkObject.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		int mapMetaPropertyAccessorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			int refValue = 45;
			itk::LightObject::Pointer refObj = itk::LightObject::New();

			itk::Object::Pointer refObj2 = itk::Object::New();

			typedef map::core::MetaProperty<int> IntProperty;
			typedef map::core::MetaProperty<itk::LightObject *> PObjProperty;
			typedef map::core::MetaProperty<const itk::LightObject *> PConstObjProperty;
			typedef map::core::SmartMetaProperty<itk::LightObject> SPObjProperty;
			typedef map::core::SmartMetaProperty<const itk::LightObject> SPConstObjProperty;

			map::core::MetaPropertyBase::Pointer spIntProp = IntProperty::New(refValue).GetPointer();
			map::core::MetaPropertyBase::Pointer spPObjProp = PObjProperty::New(refObj).GetPointer();
			map::core::MetaPropertyBase::Pointer spPConstObjProp = PConstObjProperty::New(refObj).GetPointer();
			map::core::MetaPropertyBase::Pointer spSPObjProp = SPObjProperty::New(refObj).GetPointer();
			map::core::MetaPropertyBase::Pointer spSPConstObjProp = SPConstObjProperty::New(refObj).GetPointer();

			int intValue = 0;
			itk::LightObject *pObj = NULL;
			const itk::LightObject *pConstObj = NULL;
			itk::LightObject::Pointer spObj;
			itk::LightObject::ConstPointer spConstObj;

			////////////////////////////////////////////////////////////////////
			//check the setting and getting of property values via the interface
			////////////////////////////////////////////////////////////////////

			//checking unpacking to normal values
			////////////////////////////////////////////////////////////////////
			CHECK(map::core::unwrapMetaProperty(spIntProp, intValue));
			CHECK_EQUAL(refValue, intValue);

			CHECK(map::core::unwrapMetaProperty(spPObjProp, intValue) == false);
			CHECK(map::core::unwrapMetaProperty(spPConstObjProp, intValue) == false);
			CHECK(map::core::unwrapMetaProperty(spSPObjProp, intValue) == false);
			CHECK(map::core::unwrapMetaProperty(spSPConstObjProp, intValue) == false);

			//checking unwraping to pointer type (pObj)
			////////////////////////////////////////////////////////////////////
			CHECK(map::core::unwrapMetaProperty(spIntProp, pObj) == false);

			CHECK(map::core::unwrapMetaProperty(spPObjProp, pObj));
			CHECK_EQUAL(refObj.GetPointer(), pObj);
			pObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spPConstObjProp, pObj) == false);

			CHECK(map::core::unwrapMetaProperty(spSPObjProp, pObj));
			CHECK_EQUAL(refObj.GetPointer(), pObj);
			pObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spSPConstObjProp, pObj) == false);

			//checking unwraping to const pointer type (pConstObj)
			////////////////////////////////////////////////////////////////////
			CHECK(map::core::unwrapMetaProperty(spIntProp, pConstObj) == false);

			CHECK(map::core::unwrapMetaProperty(spPObjProp, pConstObj));
			CHECK_EQUAL(refObj.GetPointer(), pConstObj);
			pConstObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spPConstObjProp, pConstObj));
			CHECK_EQUAL(refObj.GetPointer(), pConstObj);
			pConstObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spSPObjProp, pConstObj));
			CHECK_EQUAL(refObj.GetPointer(), pConstObj);
			pConstObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spSPConstObjProp, pConstObj));
			CHECK_EQUAL(refObj.GetPointer(), pConstObj);
			pConstObj = NULL;

			//checking unwraping to smart pointer type (spObj)
			////////////////////////////////////////////////////////////////////
			CHECK(map::core::unwrapMetaProperty(spIntProp, spObj) == false);

			CHECK(map::core::unwrapMetaProperty(spPObjProp, spObj));
			CHECK_EQUAL(refObj.GetPointer(), spObj.GetPointer());
			spObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spPConstObjProp, spObj) == false);
			spObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spSPObjProp, spObj));
			CHECK_EQUAL(refObj.GetPointer(), spObj.GetPointer());
			spObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spSPConstObjProp, spObj) == false);

			//checking unwraping to const smart pointer type (spConstObj)
			////////////////////////////////////////////////////////////////////
			CHECK(map::core::unwrapMetaProperty(spIntProp, spConstObj) == false);

			CHECK(map::core::unwrapMetaProperty(spPObjProp, spConstObj));
			CHECK_EQUAL(refObj.GetPointer(), spConstObj.GetPointer());
			spConstObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spPConstObjProp, spConstObj));
			CHECK_EQUAL(refObj.GetPointer(), spConstObj.GetPointer());
			spConstObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spSPObjProp, spConstObj));
			CHECK_EQUAL(refObj.GetPointer(), spConstObj.GetPointer());
			spConstObj = NULL;

			CHECK(map::core::unwrapMetaProperty(spSPConstObjProp, spConstObj));
			CHECK_EQUAL(refObj.GetPointer(), spConstObj.GetPointer());
			spConstObj = NULL;

			//checking unwraping and casting of smart pointer objects
			////////////////////////////////////////////////////////////////////
			typedef map::core::SmartMetaProperty<itk::Object> SPObj2Property;
			typedef map::core::SmartMetaProperty<const itk::Object> SPConstObj2Property;

			map::core::MetaPropertyBase::Pointer spSPObj2Prop = SPObj2Property::New(refObj2).GetPointer();
			map::core::MetaPropertyBase::Pointer spSPConstObj2Prop = SPConstObj2Property::New(refObj2).GetPointer();
			map::core::MetaPropertyBase::Pointer spSPObj2AsLightProp = SPObjProperty::New(refObj2).GetPointer();
			map::core::MetaPropertyBase::Pointer spSPConstObj2AsLightProp = SPConstObjProperty::New(refObj2).GetPointer();

			//test  unwrapMetaPropert: Object (wrapped as Object) -> LigthObject : it should faile
			CHECK(!map::core::unwrapMetaProperty(spSPObj2Prop, spObj));
			CHECK(!map::core::unwrapMetaProperty(spSPConstObj2Prop, spConstObj));
			CHECK(!map::core::unwrapMetaProperty(spSPObj2Prop, pObj));
			CHECK(!map::core::unwrapMetaProperty(spSPConstObj2Prop, pConstObj));
			spObj = NULL;
			spConstObj = NULL;
			pObj = NULL;
			pConstObj = NULL;

			//test unwrapMetaPropert: Object (wrapped as LigthObject) -> LigthObject : it should work
			CHECK(map::core::unwrapMetaProperty(spSPObj2AsLightProp, spObj));
			CHECK_EQUAL(refObj2.GetPointer(), spObj.GetPointer());
			CHECK(map::core::unwrapMetaProperty(spSPConstObj2AsLightProp, spConstObj));
			CHECK_EQUAL(refObj2.GetPointer(), spConstObj.GetPointer());
			CHECK(map::core::unwrapMetaProperty(spSPObj2AsLightProp, pObj));
			CHECK_EQUAL(refObj2.GetPointer(), pObj);
			CHECK(map::core::unwrapMetaProperty(spSPConstObj2AsLightProp, pConstObj));
			CHECK_EQUAL(refObj2.GetPointer(), pConstObj);
			spObj = NULL;
			spConstObj = NULL;
			pObj = NULL;
			pConstObj = NULL;

			//test unwrapCastedMetaProperty: Object (wrapped as Object) -> LigthObject : it should work
			CHECK(map::core::unwrapCastedMetaProperty(spSPObj2Prop, spObj));
			CHECK_EQUAL(refObj2.GetPointer(), spObj.GetPointer());
			CHECK(map::core::unwrapCastedMetaProperty(spSPConstObj2Prop, spConstObj));
			CHECK_EQUAL(refObj2.GetPointer(), spConstObj.GetPointer());
			CHECK(map::core::unwrapCastedMetaProperty(spSPObj2Prop, pObj));
			CHECK_EQUAL(refObj2.GetPointer(), pObj);
			CHECK(map::core::unwrapCastedMetaProperty(spSPConstObj2Prop, pConstObj));
			CHECK_EQUAL(refObj2.GetPointer(), pConstObj);
			spObj = NULL;
			spConstObj = NULL;
			pObj = NULL;
			pConstObj = NULL;

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
