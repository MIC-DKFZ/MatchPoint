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

#include "mapSmartMetaProperty.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapSmartMetaPropertyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			const std::type_info& typeInfo = typeid(itk::LightObject*);

			itk::LightObject::Pointer refObj = itk::LightObject::New();

			typedef map::core::SmartMetaProperty<itk::LightObject> ObjProperty;

			ObjProperty::Pointer smpProp1 = ObjProperty::New(refObj);

			CHECK(typeInfo == smpProp1->getMetaPropertyTypeInfo());

			CHECK_EQUAL(typeInfo.name(), smpProp1->getMetaPropertyTypeName());

			CHECK_EQUAL(refObj.GetPointer(), smpProp1->getValue());

			smpProp1->setValue(NULL);

			CHECK(smpProp1->getValue() == NULL);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
