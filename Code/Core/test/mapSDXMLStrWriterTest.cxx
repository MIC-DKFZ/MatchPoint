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
#include "mapSDXMLStrWriter.h"
#include "mapSDXMLStrReader.h"
#include "mapSDExceptions.h"
#include "litCheckMacros.h"

namespace map
{
  namespace testing
  {
    int mapSDXMLStrWriterTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      core::String dataStr1 = "<Main type='demo'>boss<Sub id='1'>1st</Sub><Sub attr2='###' id='2'>2nd</Sub><Sub id='3'><Sub id='3.1'/></Sub><Add/></Main>";

      map::structuredData::XMLStrReader::Pointer spReader = map::structuredData::XMLStrReader::New();
      map::structuredData::XMLStrWriter::Pointer spWriter = map::structuredData::XMLStrWriter::New();

      map::structuredData::Element::Pointer spMain;

      spMain = spReader->readXMLContent(dataStr1);

      core::String result = "";

      CHECK_NO_THROW(result = spWriter->write(spMain));

      CHECK_EQUAL(dataStr1, result);

      CHECK_THROW(spWriter->write(NULL));

      map::structuredData::XMLIntendedStrWriter::Pointer spWriter2 = map::structuredData::XMLIntendedStrWriter::New();

      core::String intendedResult = "";
      core::String intendedDataStr = "<Main type='demo'>boss\n  <Sub id='1'>1st</Sub>\n  <Sub attr2='###' id='2'>2nd</Sub>\n  <Sub id='3'>\n    <Sub id='3.1'/>\n  </Sub>\n  <Add/>\n</Main>\n";

      CHECK_NO_THROW(intendedResult = spWriter2->write(spMain));

      CHECK_EQUAL(intendedDataStr, intendedResult);


      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace Testing
} //namespace FREE
