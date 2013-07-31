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
// @version $Revision: 4910 $ (last changed revision)
// @date    $Date: 2013-07-30 14:08:21 +0200 (Di, 30 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapSDXMLFileReaderTest.cxx $
*/

#include "mapSDXMLFileReader.h"
#include "mapSDExceptions.h"
#include "mapSDTags.h"

#include "litCheckMacros.h"

namespace map
{
  namespace testing
  {
    int mapSDXMLFileReaderTest(int argn, char* argv[])
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      core::String dataDir = argv[1];
      core::String validFile = dataDir+"/validXML.xml";
      core::String invalidFile1 = dataDir+"/invalidXML1.xml";
      core::String invalidFile2 = dataDir+"/invalidXML2.xml";
      core::String invalidFile3 = dataDir+"/invalidXML3.xml";
      core::String invalidFile4 = dataDir+"/invalidXML4.xml";
      core::String emptyFile = dataDir+"/emptyXML.xml";

      map::structuredData::XMLFileReader::Pointer spReader = map::structuredData::XMLFileReader::New();

      map::structuredData::Element::Pointer spRoot = NULL;

      CHECK(spReader->getXMLContent().IsNull());

      CHECK_NO_THROW(spRoot = spReader->read(validFile));

      CHECK(spRoot.IsNotNull());

      CHECK_EQUAL("ROOT", spRoot->getTag());

      map::structuredData::Element::Pointer spMain = spRoot->getSubElement(0);

      CHECK(spMain.IsNotNull());
      CHECK_EQUAL("Main", spMain->getTag());
      CHECK_EQUAL("boss", spMain->getValue());
      CHECK_EQUAL("demo", spMain->getAttribute("type"));
			CHECK_EQUAL(tags::SDInternalSourceReader_file, spMain->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spMain->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(validFile, spMain->getAttribute(tags::SDInternalSourceURI));
      CHECK_EQUAL(4, spMain->getAttributeNames().size());
      CHECK_EQUAL(4, spMain->getSubElementsCount());

      map::structuredData::Element::Pointer spSub = spMain->getSubElement(0);

      CHECK(spSub.IsNotNull());
      CHECK_EQUAL("Sub", spSub->getTag());
      CHECK_EQUAL("1st", spSub->getValue());
      CHECK_EQUAL("1", spSub->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_file, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(validFile, spSub->getAttribute(tags::SDInternalSourceURI));
      CHECK_EQUAL(4, spSub->getAttributeNames().size());
      CHECK_EQUAL(0, spSub->getSubElementsCount());

      spSub = spMain->getSubElement(1);

      CHECK(spSub.IsNotNull());
      CHECK_EQUAL("Sub", spSub->getTag());
      CHECK_EQUAL("2nd", spSub->getValue());
      CHECK_EQUAL("2", spSub->getAttribute("id"));
      CHECK_EQUAL("###", spSub->getAttribute("attr2"));
			CHECK_EQUAL(tags::SDInternalSourceReader_file, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(validFile, spSub->getAttribute(tags::SDInternalSourceURI));
      CHECK_EQUAL(5, spSub->getAttributeNames().size());
      CHECK_EQUAL(0, spSub->getSubElementsCount());

      spSub = spMain->getSubElement(2);

      CHECK(spSub.IsNotNull());
      CHECK_EQUAL("Sub", spSub->getTag());
      CHECK_EQUAL("", spSub->getValue());
      CHECK_EQUAL("3", spSub->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_file, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(validFile, spSub->getAttribute(tags::SDInternalSourceURI));
      CHECK_EQUAL(4, spSub->getAttributeNames().size());
      CHECK_EQUAL(1, spSub->getSubElementsCount());
      CHECK_EQUAL("Sub", spSub->getSubElement(0)->getTag());
      CHECK_EQUAL("", spSub->getSubElement(0)->getValue());
      CHECK_EQUAL("3.1", spSub->getSubElement(0)->getAttribute("id"));
			CHECK_EQUAL(tags::SDInternalSourceReader_file, spSub->getSubElement(0)->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getSubElement(0)->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(validFile, spSub->getSubElement(0)->getAttribute(tags::SDInternalSourceURI));
      CHECK_EQUAL(4, spSub->getSubElement(0)->getAttributeNames().size());
      CHECK_EQUAL(0, spSub->getSubElement(0)->getSubElementsCount());

      spSub = spMain->getSubElement(3);

      CHECK(spSub.IsNotNull());
      CHECK_EQUAL("Add", spSub->getTag());
      CHECK_EQUAL("", spSub->getValue());
			CHECK_EQUAL(tags::SDInternalSourceReader_file, spSub->getAttribute(tags::SDInternalSourceReader));
			CHECK_EQUAL(tags::SDInternalSourceFormat_xml, spSub->getAttribute(tags::SDInternalSourceFormat));
			CHECK_EQUAL(validFile, spSub->getAttribute(tags::SDInternalSourceURI));
      CHECK_EQUAL(3, spSub->getAttributeNames().size());
      CHECK_EQUAL(0, spSub->getSubElementsCount());

      CHECK_EQUAL(spMain.GetPointer(), spReader->getXMLContent().GetPointer());

      CHECK_THROW(spReader->read(invalidFile1));
      CHECK_THROW(spReader->read(invalidFile1));
      CHECK_THROW(spReader->read(invalidFile1));
      CHECK_THROW(spReader->read(invalidFile1));
      CHECK_THROW(spReader->read(emptyFile));

      CHECK_EQUAL(spMain.GetPointer(), spReader->getXMLContent().GetPointer());

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace map
