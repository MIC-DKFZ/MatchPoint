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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapSDElementTest.cpp $
*/
#include "mapSDElement.h"
#include "mapSDExceptions.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapSDElementTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			structuredData::Element::Pointer spMain = structuredData::Element::New();
			structuredData::Element::Pointer spSub1 = structuredData::Element::createElement("Sub", "1");
			structuredData::Element::Pointer spSub2 = structuredData::Element::createElement("Sub", "2");
			structuredData::Element::Pointer spSub3 = structuredData::Element::createElement("Sub", "3");
			structuredData::Element::Pointer spSub4 = structuredData::Element::createElement("Sub", "4");

			const structuredData::Element *pConstMain = spMain.GetPointer();

			//check element init
			CHECK_EQUAL("", spMain->getTag());
			CHECK_EQUAL("", spMain->getValue());
			CHECK_EQUAL(0, spMain->getSubElementsCount());
			CHECK_EQUAL(0, spMain->getAttributeNames().size());

			//check tag and value interface
			spMain->setTag("Main");
			CHECK_EQUAL("Main", spMain->getTag());

			spMain->setValue("boss");
			CHECK_EQUAL("boss", spMain->getValue());

			//check createElement
			CHECK_EQUAL("Sub", spSub1->getTag());
			CHECK_EQUAL("1", spSub1->getValue());
			CHECK_EQUAL(0, spSub1->getSubElementsCount());
			CHECK_EQUAL(0, spSub1->getAttributeNames().size());


			////////////////////////////
			//check attribute methods

			spMain->addSubElement(spSub1);

			//set
			CHECK(!(spMain->setAttribute("a1", "1")));
			CHECK(!(spMain->setAttribute("a2", "2nd")));
			CHECK(spMain->setAttribute("a1", "1st"));

			//Get
			CHECK_EQUAL("1st", spMain->getAttribute("a1"));
			CHECK_EQUAL("2nd", spMain->getAttribute("a2"));
			CHECK_THROW_EXPLICIT(spMain->getAttribute("unkown"), map::core::MissingIdentifierException);

			//Exists
			CHECK_EQUAL(true, spMain->attributeExists("a1"));
			CHECK_EQUAL(false, spSub1->attributeExists("a1")); //check for: no recursive setting by default
			CHECK_EQUAL(false, spMain->attributeExists("unkown"));

			//AttributeNames
			spMain->setAttribute("a3", "3rd");
			spMain->setAttribute("a4", "4th");
			spSub1->setAttribute("a4", "4th");

			structuredData::Element::AttributeNameVectorType names;

			CHECK_NO_THROW(names = spMain->getAttributeNames());

			CHECK_EQUAL("a1", names[0]);
			CHECK_EQUAL("a2", names[1]);
			CHECK_EQUAL("a4", names[3]);
			CHECK_EQUAL(4, names.size());

			//remove attributes
			CHECK_EQUAL(false, spMain->removeAttribute("unkown"));
			CHECK_EQUAL(true, spMain->removeAttribute("a1"));
			CHECK_EQUAL(false, spMain->attributeExists("a1"));
			CHECK_EQUAL(true, spMain->removeAttribute("a3"));
			CHECK_EQUAL(false, spMain->attributeExists("a3"));
			CHECK_EQUAL(true, spMain->removeAttribute("a4"));
			CHECK_EQUAL(false, spMain->attributeExists("a4"));
			CHECK_EQUAL(true, spSub1->attributeExists("a4")); //check for: no recursive delete by default

			names = spMain->getAttributeNames();

			CHECK_EQUAL("a2", names[0]);
			CHECK_EQUAL(1, names.size());

			//reset attributes

			CHECK_NO_THROW(spMain->resetAttributes());
			names = spMain->getAttributeNames();
			CHECK_EQUAL(0, names.size());

			spMain->resetSubElements();
			spSub1->resetAttributes();

			/////////////////////////////////////
			// Sub element interface part

			CHECK_EQUAL(0, spMain->getSubElementsCount());

			//adding, inserting and itterators

			CHECK(spMain->getSubElementBegin() == spMain->getSubElementEnd());

			CHECK_EQUAL(0, spMain->addSubElement(spSub1));
			CHECK_EQUAL(1, spMain->addSubElement(spSub4));
			CHECK_THROW_EXPLICIT(spMain->addSubElement(NULL), map::core::ExceptionObject);

			structuredData::Element::SubElementIteratorType pos = spMain->getSubElementBegin();

			CHECK_EQUAL(spSub1.GetPointer(), pos->GetPointer());
			++pos;
			CHECK_EQUAL(spSub4.GetPointer(), pos->GetPointer());

			CHECK_THROW_EXPLICIT(spMain->insertSubElement(NULL, pos), map::core::ExceptionObject);
			CHECK_NO_THROW(pos = spMain->insertSubElement(spSub3, pos));
			CHECK_EQUAL(spSub3.GetPointer(), pos->GetPointer());

			CHECK_THROW_EXPLICIT(spMain->insertSubElement(NULL, 1), map::core::ExceptionObject);
			CHECK_THROW_EXPLICIT(spMain->insertSubElement(spSub2, 100), map::core::OutOfRangeException);
			CHECK_THROW_EXPLICIT(spMain->insertSubElement(spSub2, -1), map::core::OutOfRangeException);
			CHECK_NO_THROW(spMain->insertSubElement(spSub2, 1));

			CHECK_EQUAL(4, spMain->getSubElementsCount());
			CHECK_EQUAL(2, spSub1->GetReferenceCount()); //sub elements should
			CHECK_EQUAL(2, spSub2->GetReferenceCount()); //now be referenced by
			CHECK_EQUAL(2, spSub3->GetReferenceCount()); //their smart pointer
			CHECK_EQUAL(2, spSub4->GetReferenceCount()); //and by the main element

			//check whole sequenz by iterator
			//non const
			pos = spMain->getSubElementBegin();
			CHECK_EQUAL(spSub1.GetPointer(), pos->GetPointer());
			CHECK_EQUAL(spSub2.GetPointer(), (++pos)->GetPointer());
			CHECK_EQUAL(spSub3.GetPointer(), (++pos)->GetPointer());
			CHECK_EQUAL(spSub4.GetPointer(), (++pos)->GetPointer());
			CHECK(spMain->getSubElementEnd() == ++pos);
			//const
			structuredData::Element::ConstSubElementIteratorType cpos = pConstMain->getSubElementBegin();
			CHECK_EQUAL(spSub1.GetPointer(), cpos->GetPointer());
			CHECK_EQUAL(spSub2.GetPointer(), (++cpos)->GetPointer());
			CHECK_EQUAL(spSub3.GetPointer(), (++cpos)->GetPointer());
			CHECK_EQUAL(spSub4.GetPointer(), (++cpos)->GetPointer());
			CHECK(pConstMain->getSubElementEnd() == ++cpos);

			//check getSubElement
			//non const
			CHECK_THROW_EXPLICIT(spMain->getSubElement(4), map::core::OutOfRangeException);
			CHECK_THROW_EXPLICIT(spMain->getSubElement(-1), map::core::OutOfRangeException);
			CHECK_EQUAL(spSub1.GetPointer(), spMain->getSubElement(0));
			CHECK_EQUAL(spSub3.GetPointer(), spMain->getSubElement(2));
			CHECK_EQUAL(spSub4.GetPointer(), spMain->getSubElement(3));

			//const
			CHECK_THROW_EXPLICIT(pConstMain->getSubElement(4), map::core::OutOfRangeException);
			CHECK_THROW_EXPLICIT(pConstMain->getSubElement(-1), map::core::OutOfRangeException);
			CHECK_EQUAL(spSub1.GetPointer(), pConstMain->getSubElement(0));
			CHECK_EQUAL(spSub3.GetPointer(), pConstMain->getSubElement(2));
			CHECK_EQUAL(spSub4.GetPointer(), pConstMain->getSubElement(3));

			//check index remove
			CHECK_THROW_EXPLICIT(spMain->removeSubElement(4), map::core::OutOfRangeException);
			CHECK_THROW_EXPLICIT(spMain->removeSubElement(-1), map::core::OutOfRangeException);

			spMain->removeSubElement(0);
			CHECK_EQUAL(1, spSub1->GetReferenceCount());
			CHECK_EQUAL(spMain->getSubElementBegin()->GetPointer(), spSub2.GetPointer());
			spMain->removeSubElement(1);
			CHECK_EQUAL(1, spSub3->GetReferenceCount());
			CHECK_EQUAL(2, spMain->getSubElementsCount());
			spMain->removeSubElement(1);
			CHECK_EQUAL(1, spSub4->GetReferenceCount());
			CHECK_EQUAL(1, spMain->getSubElementsCount());
			CHECK_EQUAL(spMain->getSubElementBegin()->GetPointer(), spSub2.GetPointer());

			//check reset
			spMain->resetSubElements();
			CHECK_EQUAL(0, spMain->getSubElementsCount());

			//check iterator remove
			//add all elements again
			spMain->addSubElement(spSub1);
			spMain->addSubElement(spSub2);
			spMain->addSubElement(spSub3);
			spMain->addSubElement(spSub4);

			pos = spMain->getSubElementBegin();
			//remove the second element and check if the returned iterator designates the third one
			CHECK_EQUAL(spSub3.GetPointer(), (spMain->removeSubElement(++pos))->GetPointer());
			CHECK_EQUAL(1, spSub2->GetReferenceCount());
			CHECK_EQUAL(3, spMain->getSubElementsCount());

			pos = spMain->getSubElementBegin();
			pos = pos + 2;
			//remove the fourth element and check if the returned iterator designates the end
			CHECK(spMain->getSubElementEnd() == spMain->removeSubElement(pos));
			CHECK_EQUAL(1, spSub4->GetReferenceCount());
			CHECK_EQUAL(2, spMain->getSubElementsCount());

			//check reset and printing
			spMain->setAttribute("a1", "1");

			CHECK_NO_THROW(spMain->Print(std::cout));

			spMain->reset();
			CHECK_EQUAL(0, spMain->getSubElementsCount());
			CHECK_EQUAL(0, spMain->getAttributeNames().size());
			CHECK_EQUAL("", spMain->getValue());
			CHECK_EQUAL("Main", spMain->getTag());

			/////////////////////////////////////
			// check clone
			spMain->setTag("Main");
			spMain->setValue("boss");
			spMain->setAttribute("a3", "3rd");
			spMain->setAttribute("a4", "4th");
			spMain->addSubElement(spSub1);
			spMain->addSubElement(spSub2);
			spMain->addSubElement(spSub3);
			spMain->addSubElement(spSub4);

			structuredData::Element::Pointer spClone;

			CHECK_NO_THROW(spClone = spMain->clone());

			spMain->reset();

			CHECK_EQUAL("Main", spClone->getTag());
			CHECK_EQUAL("boss", spClone->getValue());
			CHECK_EQUAL("3rd", spClone->getAttribute("a3"));
			CHECK_EQUAL("4th", spClone->getAttribute("a4"));
			CHECK_EQUAL(2, spClone->getAttributeNames().size());
			CHECK_EQUAL(4, spClone->getSubElementsCount());

			CHECK_EQUAL("Sub", spClone->getSubElement(0)->getTag());
			CHECK_EQUAL("1", spClone->getSubElement(0)->getValue());
			CHECK_EQUAL("Sub", spClone->getSubElement(1)->getTag());
			CHECK_EQUAL("2", spClone->getSubElement(1)->getValue());

			spSub1->setValue("otherValue");
			//check if the sub elements are realy copied and therefor changes in the clone origin does not effect the clone.
			CHECK_EQUAL("1", spClone->getSubElement(0)->getValue());

			/////////////////////////////////////
			// check recursive attribute set and remove
			spMain = structuredData::Element::New();
			spSub1 = structuredData::Element::createElement("Sub", "1");
			spSub2 = structuredData::Element::createElement("Sub", "2");
			spSub3 = structuredData::Element::createElement("Sub", "3");
			spSub4 = structuredData::Element::createElement("Sub", "4");

			spMain->addSubElement(spSub1);
			spMain->addSubElement(spSub2);
			spSub2->addSubElement(spSub3);
			spSub2->addSubElement(spSub4);

			CHECK(!spMain->removeAttribute("A", false));
			CHECK(!spMain->removeAttribute("A", true));
			CHECK(!spMain->setAttribute("A", "a", false));
			CHECK_EQUAL("a", spMain->getAttribute("A"));
			CHECK(!spSub1->attributeExists("A"));
			CHECK(!spSub2->attributeExists("A"));
			CHECK(!spSub3->attributeExists("A"));
			CHECK(!spSub4->attributeExists("A"));
			CHECK(spMain->setAttribute("A", "a", true));
			CHECK_EQUAL("a", spMain->getAttribute("A"));
			CHECK_EQUAL("a", spSub1->getAttribute("A"));
			CHECK_EQUAL("a", spSub2->getAttribute("A"));
			CHECK_EQUAL("a", spSub3->getAttribute("A"));
			CHECK_EQUAL("a", spSub4->getAttribute("A"));
			CHECK(spMain->removeAttribute("A", false));
			CHECK(!spMain->attributeExists("A"));
			CHECK_EQUAL("a", spSub1->getAttribute("A"));
			CHECK_EQUAL("a", spSub2->getAttribute("A"));
			CHECK_EQUAL("a", spSub3->getAttribute("A"));
			CHECK_EQUAL("a", spSub4->getAttribute("A"));
			CHECK(spMain->removeAttribute("A", true));
			CHECK(!spMain->attributeExists("A"));
			CHECK(!spSub1->attributeExists("A"));
			CHECK(!spSub2->attributeExists("A"));
			CHECK(!spSub3->attributeExists("A"));
			CHECK(!spSub4->attributeExists("A"));
			CHECK(!spMain->setAttribute("A", "a", true));
			CHECK_EQUAL("a", spMain->getAttribute("A"));
			CHECK_EQUAL("a", spSub1->getAttribute("A"));
			CHECK_EQUAL("a", spSub2->getAttribute("A"));
			CHECK_EQUAL("a", spSub3->getAttribute("A"));
			CHECK_EQUAL("a", spSub4->getAttribute("A"));


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace Testing
} //namespace FREE
