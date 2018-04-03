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

#include "mapMetaProperty.h"
#include "mapSmartMetaProperty.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapMetaPropertyAccessInterfaceTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			int refValue = 45;
			itk::LightObject::Pointer refObj = itk::LightObject::New();

			typedef map::core::MetaProperty<int> IntProperty;
			typedef map::core::MetaProperty<itk::LightObject*> PObjProperty;
			typedef map::core::SmartMetaProperty<itk::LightObject> SPObjProperty;

			map::core::MetaPropertyBase::Pointer smpIntProp = IntProperty::New(refValue).GetPointer();

			int refCount = refObj->GetReferenceCount();

			map::core::MetaPropertyBase::Pointer smpSPObjProp = SPObjProperty::New(refObj).GetPointer();
			//smpSPObjProp is a SmartMetaProperty, thus the reference counter must have raised by one
			CHECK_EQUAL(refCount + 1, refObj->GetReferenceCount());

			refCount = refObj->GetReferenceCount();

			map::core::MetaPropertyBase::Pointer smpPObjProp = PObjProperty::New(refObj).GetPointer();

			//smpPObjProp is no SmartMetaProperty, thus the reference counter may not change
			CHECK_EQUAL(refCount, refObj->GetReferenceCount());

			//check interface casts
			typedef map::core::MetaPropertyAccessInterface<int> IntInterfaceType;
			typedef map::core::MetaPropertyAccessInterface<itk::LightObject*> ObjPointerInterfaceType;

			IntInterfaceType* pValidIntInterface = dynamic_cast<IntInterfaceType*>(smpIntProp.GetPointer());
			CHECK(pValidIntInterface != NULL);

			IntInterfaceType* pWrongIntInterface = dynamic_cast<IntInterfaceType*>(smpSPObjProp.GetPointer());
			CHECK(pWrongIntInterface == NULL);

			ObjPointerInterfaceType* pValidSPObjInterface = dynamic_cast<ObjPointerInterfaceType*>
					(smpSPObjProp.GetPointer());
			CHECK(pValidSPObjInterface != NULL);

			ObjPointerInterfaceType* pWrongSPObjInterface = dynamic_cast<ObjPointerInterfaceType*>
					(smpIntProp.GetPointer());
			CHECK(pWrongSPObjInterface == NULL);

			ObjPointerInterfaceType* pValidPObjInterface = dynamic_cast<ObjPointerInterfaceType*>
					(smpPObjProp.GetPointer());
			CHECK(pValidPObjInterface != NULL);

			ObjPointerInterfaceType* pWrongPObjInterface = dynamic_cast<ObjPointerInterfaceType*>
					(smpIntProp.GetPointer());
			CHECK(pWrongPObjInterface == NULL);

			//check the setting and getting of property values via the interface
			CHECK_EQUAL(refValue, pValidIntInterface->getValue());

			CHECK_EQUAL(refObj.GetPointer(), pValidSPObjInterface->getValue());

			CHECK_EQUAL(refObj.GetPointer(), pValidPObjInterface->getValue());

			CHECK_NO_THROW(pValidIntInterface->setValue(21));
			CHECK_EQUAL(21, pValidIntInterface->getValue());

			CHECK_NO_THROW(pValidSPObjInterface->setValue(NULL));
			CHECK(NULL == pValidSPObjInterface->getValue());

			CHECK_NO_THROW(pValidPObjInterface->setValue(NULL));
			CHECK(NULL == pValidPObjInterface->getValue());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
