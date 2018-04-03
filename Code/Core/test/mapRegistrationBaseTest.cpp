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

#include "mapRegistrationBase.h"
#include "mapRegistrationManipulator.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{

		class TestRegistrationBase : public core::RegistrationBase
		{
		public:
			typedef TestRegistrationBase Self;
			typedef core::RegistrationBase Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(TestRegistrationBase, RegistrationBase);

			itkNewMacro(Self);

			virtual unsigned int getMovingDimensions() const
			{
				return 2;
			};

			virtual unsigned int getTargetDimensions() const
			{
				return 2;
			};

			virtual bool hasLimitedTargetRepresentation() const
			{
				return false;
			};

			virtual bool hasLimitedMovingRepresentation() const
			{
				return false;
			};

		protected:
			TestRegistrationBase()
			{
			};

			virtual ~TestRegistrationBase() {};

		private:
			//No copy constructor allowed
			TestRegistrationBase(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

		int mapRegistrationBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestRegistrationBase::Pointer spReg1 = TestRegistrationBase::New();
			TestRegistrationBase::Pointer spReg2 = TestRegistrationBase::New();
			map::core::RegistrationBaseManipulator manipulator1(spReg1);

			TestRegistrationBase::TagMapType tags;
			tags.insert(std::make_pair("test", "value"));

			TestRegistrationBase::TagMapType tagsWithUID;
			tagsWithUID.insert(std::make_pair("test2", "value2"));
			tagsWithUID.insert(std::make_pair(map::tags::RegistrationUID, "my.Personal.UID"));

			::map::core::String foundValue = "";
			::map::core::String foundValue2 = "";
			//check if a default UID is generated
			CHECK(1 == spReg1->getTags().size());
			CHECK(spReg1->getTagValue(map::tags::RegistrationUID, foundValue));
			//check if the default UID in the tags is really returned by getRegistrationUID()
			CHECK_EQUAL(foundValue, spReg1->getRegistrationUID());

			//check if a default UID is generated
			CHECK(spReg2->getTagValue(map::tags::RegistrationUID, foundValue2));
			//check if the default UID in the tags is really returned by getRegistrationUID()
			CHECK_EQUAL(foundValue2, spReg2->getRegistrationUID());

			CHECK(foundValue != foundValue2);

			//check if changing tags without UID changes UID
			manipulator1.setTagValues(tags);
			CHECK(2 == spReg1->getTags().size());
			CHECK(spReg1->getTagValue(map::tags::RegistrationUID, foundValue2));
			CHECK_EQUAL(foundValue2, spReg1->getRegistrationUID());
			CHECK_EQUAL(foundValue, foundValue2);
			CHECK(spReg1->getTagValue("test", foundValue2));
			CHECK_EQUAL("value", foundValue2);

			//check if changing tags with UID changes UID
			manipulator1.setTagValues(tagsWithUID);
			CHECK(spReg1->getTagValue(map::tags::RegistrationUID, foundValue2));
			CHECK_EQUAL(foundValue2, spReg1->getRegistrationUID());
			CHECK_EQUAL("my.Personal.UID", foundValue2);
			CHECK(!spReg1->getTagValue("test", foundValue2));
			CHECK(spReg1->getTagValue("test2", foundValue2));
			CHECK_EQUAL("value2", foundValue2);


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
