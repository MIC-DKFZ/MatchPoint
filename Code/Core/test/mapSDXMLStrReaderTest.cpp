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
#include "litCheckMacros.h"

#include "mapSDXMLStrReader.h"
#include "mapSDExceptions.h"
#include "mapSDTags.h"

namespace map
{
	namespace testing
	{
		int mapSDXMLStrReaderTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			core::String dataStr1 =
				"<Main type='demo'>boss<Sub id='1'>1st</Sub><Sub id='2' attr2='###'>2nd</Sub><Sub id='3'><Sub id='3.1'/></Sub><Add/></Main>";

			map::structuredData::XMLStrReader::Pointer spReader = map::structuredData::XMLStrReader::New();

			map::structuredData::Element::Pointer spRoot = NULL;

			CHECK_NO_THROW(spRoot = spReader->read(dataStr1));

			CHECK_EQUAL("ROOT", spRoot->getTag());

			map::structuredData::Element::Pointer spMain = spRoot->getSubElement(0);

			CHECK(spMain.IsNotNull());
			CHECK_EQUAL("Main", spMain->getTag());
			CHECK_EQUAL("boss", spMain->getValue());
			CHECK_EQUAL("demo", spMain->getAttribute("type"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string,
						spMain->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spMain->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spMain->getAttributeNames().size());
			CHECK_EQUAL(4, spMain->getSubElementsCount());

			map::structuredData::Element::Pointer spSub = spMain->getSubElement(0);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Sub", spSub->getTag());
			CHECK_EQUAL("1st", spSub->getValue());
			CHECK_EQUAL("1", spSub->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spSub->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElementsCount());

			spSub = spMain->getSubElement(1);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Sub", spSub->getTag());
			CHECK_EQUAL("2nd", spSub->getValue());
			CHECK_EQUAL("2", spSub->getAttribute("id"));
			CHECK_EQUAL("###", spSub->getAttribute("attr2"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(4, spSub->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElementsCount());

			spSub = spMain->getSubElement(2);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Sub", spSub->getTag());
			CHECK_EQUAL("", spSub->getValue());
			CHECK_EQUAL("3", spSub->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string,
						spMain->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spMain->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spSub->getAttributeNames().size());
			CHECK_EQUAL(1, spSub->getSubElementsCount());
			CHECK_EQUAL("Sub", spSub->getSubElement(0)->getTag());
			CHECK_EQUAL("", spSub->getSubElement(0)->getValue());
			CHECK_EQUAL("3.1", spSub->getSubElement(0)->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string,
						spSub->getSubElement(0)->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml,
						spSub->getSubElement(0)->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spSub->getSubElement(0)->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElement(0)->getSubElementsCount());

			spSub = spMain->getSubElement(3);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Add", spSub->getTag());
			CHECK_EQUAL("", spSub->getValue());
			CHECK_EQUAL(tags::SDInternalSourceReader_string, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(2, spSub->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElementsCount());

			core::String faultyDataStr1 = "<Main/><Main/>";
			core::String faultyDataStr2 = "<Main> <Mingel> </Main> </Mingel>";
			core::String faultyDataStr3 = "</OpenEnd>";
			core::String faultyDataStr4 = "<Main> <OpenElement> </Main>";

			CHECK_THROW(spReader->read(faultyDataStr1));
			CHECK_THROW(spReader->read(faultyDataStr2));
			CHECK_THROW(spReader->read(faultyDataStr3));
			CHECK_THROW(spReader->read(faultyDataStr4));

			//check direct content access
			CHECK_NO_THROW(spMain = spReader->readXMLContent(dataStr1));

			CHECK(spMain.IsNotNull());
			CHECK_EQUAL("Main", spMain->getTag());
			CHECK_EQUAL("boss", spMain->getValue());
			CHECK_EQUAL("demo", spMain->getAttribute("type"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string,
						spMain->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spMain->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spMain->getAttributeNames().size());
			CHECK_EQUAL(4, spMain->getSubElementsCount());

			spSub = spMain->getSubElement(0);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Sub", spSub->getTag());
			CHECK_EQUAL("1st", spSub->getValue());
			CHECK_EQUAL("1", spSub->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spSub->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElementsCount());

			spSub = spMain->getSubElement(1);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Sub", spSub->getTag());
			CHECK_EQUAL("2nd", spSub->getValue());
			CHECK_EQUAL("2", spSub->getAttribute("id"));
			CHECK_EQUAL("###", spSub->getAttribute("attr2"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(4, spSub->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElementsCount());

			spSub = spMain->getSubElement(2);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Sub", spSub->getTag());
			CHECK_EQUAL("", spSub->getValue());
			CHECK_EQUAL("3", spSub->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spSub->getAttributeNames().size());
			CHECK_EQUAL(1, spSub->getSubElementsCount());
			CHECK_EQUAL("Sub", spSub->getSubElement(0)->getTag());
			CHECK_EQUAL("", spSub->getSubElement(0)->getValue());
			CHECK_EQUAL("3.1", spSub->getSubElement(0)->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_string,
						spSub->getSubElement(0)->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml,
						spSub->getSubElement(0)->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(3, spSub->getSubElement(0)->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElement(0)->getSubElementsCount());

			spSub = spMain->getSubElement(3);

			CHECK(spSub.IsNotNull());
			CHECK_EQUAL("Add", spSub->getTag());
			CHECK_EQUAL("", spSub->getValue());
			CHECK_EQUAL(tags::SDInternalSourceReader_string, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(2, spSub->getAttributeNames().size());
			CHECK_EQUAL(0, spSub->getSubElementsCount());

			core::String emptyDataStr1 = "";

			CHECK_THROW(spReader->readXMLContent(emptyDataStr1));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace Testing
} //namespace FREE
