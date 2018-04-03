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

#include "itksys/SystemTools.hxx"

#include "mapLogbook.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
      int mapLogbookTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

      ::map::core::String logPath = "";

      if (argc < 2)
          return EXIT_FAILURE;

      logPath = argv[1];

      itksys::SystemTools::RemoveFile(logPath.c_str()); //ensure that the logfile is not there
      CHECK_NO_THROW(::map::core::Logbook::setDefaultLogFileName(logPath));
			CHECK_NO_THROW(::map::core::Logbook::info("first entry and initialization"));
      CHECK_NO_THROW(::map::core::Logbook::flush());

      CHECK(itksys::SystemTools::FileExists(logPath.c_str(), true));

      //check deactivated default log
      CHECK_NO_THROW(::map::core::Logbook::setDefaultLogFileName(""));
      CHECK_NO_THROW(::map::core::Logbook::info("make an entry to *new* log file to ensure that the old one is released."));
      itksys::SystemTools::RemoveFile(logPath.c_str());
      CHECK_NO_THROW(::map::core::Logbook::info("this should go no where."));
      CHECK_NO_THROW(::map::core::Logbook::flush());

      CHECK(!itksys::SystemTools::FileExists(logPath.c_str(), true));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
