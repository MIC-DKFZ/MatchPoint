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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapSDXMLFileWriterTest.cxx $
*/
#include "mapSDXMLFileWriter.h"
#include "mapSDXMLStrReader.h"
#include "mapSDExceptions.h"

#include "mapFileDispatch.h"

#include "litCheckMacros.h"
#include "litTextFileTester.h"

namespace map
{
  namespace testing
  {
    int mapSDXMLFileWriterTest(int argn, char* argv[])
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      core::String dataStr = "<Main type='demo'>boss<Sub id='1'>1st</Sub><Sub attr2='###' id='2'>2nd</Sub><Sub id='3'><Sub id='3.1'/></Sub><Add/></Main>";

      core::String tempLocation = argv[1];
      core::String expectedFile = argv[2];
      core::String expectedFileWithXSLT = argv[3];
      core::String tempDataFile = map::core::FileDispatch::createFullPath(tempLocation.c_str(),"XMLFileWriterTest.txt");

      map::structuredData::XMLStrReader::Pointer spReader = map::structuredData::XMLStrReader::New();

      map::structuredData::Element::Pointer spMainElement = spReader->readXMLContent(dataStr);

      map::structuredData::XMLFileWriter::Pointer spWriter = map::structuredData::XMLFileWriter::New();

      lit::TextFileTester tester;

      tester.setExpectedFile(expectedFile);
      tester.setActualFile(tempDataFile);

      //test with no xslt
      CHECK_EQUAL("", spWriter->getXSLTFile());

      CHECK_NO_THROW(spWriter->write(tempDataFile,spMainElement));
      CHECK_TESTER(tester);

      //test with xslt
      CHECK_NO_THROW(spWriter->setXSLTFile("test.xsl"));
      CHECK_EQUAL("test.xsl", spWriter->getXSLTFile());
      tester.setExpectedFile(expectedFileWithXSLT);

      CHECK_NO_THROW(spWriter->write(tempDataFile,spMainElement));

      CHECK_TESTER(tester);

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace map
