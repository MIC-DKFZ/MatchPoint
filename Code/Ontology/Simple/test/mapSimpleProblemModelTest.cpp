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


#include "mapSimpleProblemModel.h"
#include "mapBoostUIDPolicy.h"

#include "litCheckMacros.h"

#include <stdlib.h>
#include "mapOntologyExceptions.h"

namespace iro
{
  namespace testing
  {

    int mapSimpleProblemModelTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      ::iro::scenario::SimpleProblemStatement::Pointer spPS(new ::iro::scenario::SimpleProblemStatement);
      ::iro::scenario::SimpleProblemStatement::Pointer spPS2(new ::iro::scenario::SimpleProblemStatement);
      ::iro::scenario::SimpleProblemStatement::Pointer spPS3(new ::iro::scenario::SimpleProblemStatement);
      ::iro::scenario::SimpleProblemModel pm;
      const ::iro::scenario::SimpleProblemModel& cPM = pm;
      ::iro::scenario::SimpleProblemModel::UIDType uid = BoostUIDPolicy::generateUID();
      ::iro::scenario::SimpleProblemModel::UIDType unkownUid = BoostUIDPolicy::generateUID();

      //check default values
      CHECK(pm.getName() == "");
      //UID is set randomly by default
      CHECK(pm.getStatementBegin() == pm.getStatementEnd());
      CHECK(pm.getStatementCount() == 0);
      CHECK(pm.findStatement(unkownUid) == pm.getStatementEnd());
      CHECK(!pm.checkComplianceOfStatement(spPS.get()));
      CHECK(!pm.checkComplianceOfStatement(spPS2.get()));


      //check setter and getter
      CHECK_NO_THROW(pm.setName("Problem Model 1"));
      CHECK_NO_THROW(pm.setUID(uid));

      CHECK("Problem Model 1" == pm.getName());
      CHECK(pm.getUID() == uid);

      //check adding of statements and its effect
      CHECK_NO_THROW(pm.addStatement(spPS));
      CHECK(pm.getStatementBegin()->get() == spPS.get());
      CHECK(pm.getStatementCount() == 1);
      CHECK(pm.findStatement(spPS->getUID()) == pm.getStatementBegin());
      CHECK(pm.checkComplianceOfStatement(spPS.get()));
      CHECK(!pm.checkComplianceOfStatement(spPS2.get()));

      CHECK(pm.getStatementBegin()->get() == cPM.getStatementBegin()->get());
      CHECK(pm.findStatement(spPS->getUID()) == cPM.findStatement(spPS->getUID()));

      CHECK_NO_THROW(pm.addStatement(spPS2));
      CHECK(pm.getStatementCount() == 2);
      CHECK(pm.findStatement(spPS2->getUID())->get() == spPS2.get());
      CHECK(pm.checkComplianceOfStatement(spPS.get()));
      CHECK(pm.checkComplianceOfStatement(spPS2.get()));
      CHECK(!pm.checkComplianceOfStatement(spPS3.get()));

      CHECK_NO_THROW(pm.addStatement(spPS3));

      //check clone
      ::iro::scenario::SimpleProblemModel::Pointer spClone;
      CHECK_NO_THROW(spClone = pm.clone());
      CHECK(spClone);

      CHECK(pm.getUID() == spClone->getUID());
      CHECK_EQUAL(pm.getName(), spClone->getName());
      CHECK_EQUAL(pm.getStatementCount(), spClone->getStatementCount());

      ::iro::scenario::SimpleProblemModel::ProblemIterator pos = pm.getStatementBegin();
      ::iro::scenario::SimpleProblemModel::ProblemIterator posClone = spClone->getStatementBegin();
      CHECK_EQUAL(pos->get(), posClone->get());
      ++pos; ++posClone;
      CHECK_EQUAL(pos->get(), posClone->get());
      ++pos; ++posClone;
      CHECK_EQUAL(pos->get(), posClone->get());

      CHECK_NO_THROW(pos = pm.removeStatement(pm.getStatementBegin()));
      CHECK(pos == pm.getStatementBegin());
      CHECK_EQUAL(2, pm.getStatementCount());

      CHECK_NO_THROW(spClone->resetStatements());
      CHECK_EQUAL(2, pm.getStatementCount());
      CHECK_EQUAL(0, spClone->getStatementCount());

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
