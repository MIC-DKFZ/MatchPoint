// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright c German Cancer Research Center DKFZ,
// Software development for Integrated Diagnostics and Therapy SIDT.
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------


#include "mapSimpleProblemStatement.h"
#include "mapBoostUIDPolicy.h"

#include "litCheckMacros.h"

#include <stdlib.h>
#include "mapOntologyExceptions.h"

namespace iro
{
  namespace testing
  {

    int mapSimpleProblemStatementTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      ::iro::scenario::SimpleProblemStatement ps;
      ::iro::scenario::SimpleProblemStatement ps2;

      ::iro::scenario::SimpleProblemStatement::UIDType uid = BoostUIDPolicy::generateUID();

      //check default values
      CHECK(ps.getName() == "");
      //UID is set randomly by default

      //check setter and getter
      CHECK_NO_THROW(ps.setName("Problem statement 1"));
      CHECK_NO_THROW(ps.setUID(uid));

      CHECK("Problem statement 1" == ps.getName());
      CHECK(ps.getUID() == uid);

      //check compliance

      CHECK(ps.checkComplianceOfStatement(&ps));
      CHECK(!ps.checkComplianceOfStatement(&ps2));

      //check clone
      ::iro::scenario::SimpleProblemStatement::Pointer spClone;
      CHECK_NO_THROW(spClone = ps.clone());
      CHECK(spClone);

      CHECK(ps.getUID() == spClone->getUID());
      CHECK_EQUAL(ps.getName(), spClone->getName());

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
