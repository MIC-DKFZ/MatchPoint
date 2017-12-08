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


#include "mapOntologyResult.h"

#include "litCheckMacros.h"

#include <stdlib.h>

namespace iro
{
  namespace testing
  {

    struct ResultTestStruct
    {
      int _a;
      bool _b;
      ResultTestStruct(int a, bool b): _a(a), _b(b) {};
    };

    int mapOntologyResultTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      //now check if the macro definition of the TestException class worked well.
      typedef iro::Result<int> IntResultType;
      typedef iro::Result<ResultTestStruct> StructResultType;

      IntResultType ir(10,0);
      IntResultType ir2(21,5);
      IntResultType ir3(ir);

      CHECK_EQUAL(10,ir.getValue());
      CHECK_EQUAL(0,ir.getRevision());
      CHECK_EQUAL(21,ir2.getValue());
      CHECK_EQUAL(5,ir2.getRevision());
      CHECK_EQUAL(10,ir3.getValue());
      CHECK_EQUAL(0,ir3.getRevision());

      ir3 = ir2;

      CHECK_EQUAL(21,ir3.getValue());
      CHECK_EQUAL(5,ir3.getRevision());

      int value = 0;
      value = ir;

      CHECK_EQUAL(ir.getValue(),value);

      StructResultType sr(ResultTestStruct(42,true),21);

      const StructResultType& constSR = sr;

      CHECK_EQUAL(42,(*sr)._a);
      CHECK_EQUAL(true,(*sr)._b);
      CHECK_EQUAL(42,sr->_a);
      CHECK_EQUAL(true,sr->_b);

      CHECK_EQUAL(42,(*constSR)._a);
      CHECK_EQUAL(true,(*constSR)._b);
      CHECK_EQUAL(42,constSR->_a);
      CHECK_EQUAL(true,constSR->_b);

      /////////////////////////////////////////////////////////////////////
      //redo the tests for the share pointer specialication

      typedef iro::Result< std::shared_ptr<ResultTestStruct> > SPStructResultType;

      std::shared_ptr<ResultTestStruct> spSR(new ResultTestStruct(21,false));
      std::shared_ptr<ResultTestStruct> spSR2(new ResultTestStruct(63,false));

      SPStructResultType ssr(spSR,11);
      SPStructResultType ssr2(spSR2,13);

      CHECK(ssr.getValue().get() == spSR.get());
      CHECK_EQUAL(11,ssr.getRevision());
      CHECK(ssr2.getValue().get() == spSR2.get());
      CHECK_EQUAL(13,ssr2.getRevision());

      ssr2 = ssr;

      CHECK(ssr2.getValue().get() == ssr.getValue().get());
      CHECK_EQUAL(ssr.getRevision(),ssr2.getRevision());

      std::shared_ptr<ResultTestStruct> spTestSR = ssr;
      std::shared_ptr<ResultTestStruct> spTestSR2(ssr);

      CHECK(ssr.getValue().get() == spTestSR.get());
      CHECK(ssr.getValue().get() == spTestSR2.get());

      CHECK_EQUAL(21,(*ssr)._a);
      CHECK_EQUAL(false,(*ssr)._b);
      CHECK_EQUAL(21,ssr->_a);
      CHECK_EQUAL(false,ssr->_b);

      const SPStructResultType& constSSR = ssr;

      CHECK_EQUAL(21,(*constSSR)._a);
      CHECK_EQUAL(false,(*constSSR)._b);
      CHECK_EQUAL(21,constSSR->_a);
      CHECK_EQUAL(false,constSSR->_b);

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
