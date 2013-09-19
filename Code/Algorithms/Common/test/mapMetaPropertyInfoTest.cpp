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

#include "mapMetaPropertyInfo.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		int mapMetaPropertyInfoTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;


			const std::type_info& intTypeInfo = typeid(int);
			const std::type_info& boolPointerTypeInfo = typeid(bool*);

			map::algorithm::MetaPropertyInfo::Pointer spInfo1 = map::algorithm::MetaPropertyInfo::New("Test1",
					intTypeInfo);
			map::algorithm::MetaPropertyInfo::Pointer spInfo2 = map::algorithm::MetaPropertyInfo::New("Test2",
					boolPointerTypeInfo, false, true);
			map::algorithm::MetaPropertyInfo::Pointer spInfo3 = map::algorithm::MetaPropertyInfo::New("Test3",
					intTypeInfo, true, false);

			CHECK_EQUAL("Test1", spInfo1->getName());
			CHECK_EQUAL(intTypeInfo.name(), spInfo1->getTypeName());
			CHECK(intTypeInfo == spInfo1->getTypeInfo());
			CHECK_EQUAL(true, spInfo1->isReadable());
			CHECK_EQUAL(false, spInfo1->isWritable());

			CHECK_EQUAL("Test2", spInfo2->getName());
			CHECK_EQUAL(boolPointerTypeInfo.name(), spInfo2->getTypeName());
			CHECK(boolPointerTypeInfo == spInfo2->getTypeInfo());
			CHECK_EQUAL(false, spInfo2->isReadable());
			CHECK_EQUAL(true, spInfo2->isWritable());

			CHECK_EQUAL("Test3", spInfo3->getName());
			CHECK_EQUAL(intTypeInfo.name(), spInfo3->getTypeName());
			CHECK(intTypeInfo == spInfo3->getTypeInfo());
			CHECK_EQUAL(true, spInfo3->isReadable());
			CHECK_EQUAL(false, spInfo3->isWritable());

			CHECK_NO_THROW(spInfo1->Print(std::cout));

			map::algorithm::MetaPropertyInfo::Pointer spInfoClone;

			CHECK_NO_THROW(spInfoClone = dynamic_cast<map::algorithm::MetaPropertyInfo*>
										 (spInfo2->CreateAnother().GetPointer()));

			CHECK_EQUAL(spInfo2->getName(), spInfoClone->getName());
			CHECK_EQUAL(spInfo2->getTypeName(), spInfoClone->getTypeName());
			CHECK(spInfo2->getTypeInfo() == spInfoClone->getTypeInfo());
			CHECK_EQUAL(spInfo2->isReadable(), spInfoClone->isReadable());
			CHECK_EQUAL(spInfo2->isWritable(), spInfoClone->isWritable());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
