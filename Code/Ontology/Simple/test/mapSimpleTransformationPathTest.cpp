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


#include "mapSimpleTransformationPath.h"
#include "mapSimpleTestHelper.h"

#include "litCheckMacros.h"

#include <stdlib.h>

namespace iro
{
  namespace testing
  {

    int mapSimpleTransformationPathTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      ::iro::scenario::SimpleTransformationPath path;

      ::iro::scenario::SimpleInformationSpace::Pointer spIS1 = generateIS("IS 1");
      ::iro::scenario::SimpleInformationSpace::Pointer spIS2 = generateIS("IS 2");
      ::iro::scenario::SimpleInformationSpace::Pointer spIS3 = generateIS("IS 3");
      ::iro::scenario::SimpleInformationSpace::Pointer spIS4 = generateIS("IS 4");
      ::iro::scenario::SimpleInformationSpace::Pointer spIS5 = generateIS("IS 5");
      ::iro::scenario::SimpleProblemStatement::Pointer spPS1(new ::iro::scenario::SimpleProblemStatement);
      ::iro::scenario::SimpleProblemStatement::Pointer spPS2(new ::iro::scenario::SimpleProblemStatement);

      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans1_2 = generateTransInfo("1->2",spIS1,spIS2,spPS1, ::iro::DataRepresentation::Continuous);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans2_3 = generateTransInfo("2->3",spIS2,spIS3,spPS1, ::iro::DataRepresentation::Continuous);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans3_4 = generateTransInfo("3->4",spIS3,spIS4,spPS2, ::iro::DataRepresentation::Continuous);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans4_3 = generateTransInfo("4->3",spIS4,spIS3,spPS2, ::iro::DataRepresentation::Continuous);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans1_2d = generateTransInfo("1->d2",spIS1,spIS2,spPS2, ::iro::DataRepresentation::Discrete);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans3_4d = generateTransInfo("3->d4",spIS3,spIS4,spPS2, ::iro::DataRepresentation::Discrete);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTrans2_5 = generateTransInfo("2->5",spIS2,spIS5,spPS2, ::iro::DataRepresentation::Continuous);

      //check default values
      CHECK(!(path.getMovingIS()));
      CHECK(!(path.getTargetIS()));
      CHECK(path.getBegin() == path.getEnd());
      CHECK(path.size() == 0);
      CHECK(path.checkProblemCompliance(spPS1.get()));

      /////////////////////////////////////////////////////
      //check adding of elements and the path behaviour

      CHECK_NO_THROW(path.appendElement(spTrans2_3));
      //current path: 2->3

      CHECK(path.getMovingIS().get() == spIS2.get());
      CHECK(path.getTargetIS().get() == spIS3.get());
      CHECK(path.getBegin()->get() == spTrans2_3.get());
      CHECK(path.size() == 1);
      CHECK(path.checkProblemCompliance(spPS1.get()));
      CHECK(!path.checkProblemCompliance(spPS2.get()));

      CHECK_THROW_EXPLICIT(path.insertElement(path.getEnd(),spTrans1_2),::iro::exceptions::InvalidMovingIS);
      CHECK_THROW_EXPLICIT(path.insertElement(path.getBegin(),spTrans1_2d),::iro::exceptions::InvalidDataRepresentation);

      CHECK_NO_THROW(path.insertElement(path.getBegin(),spTrans1_2));
      //current path: 1->2 2->3

      CHECK(path.getMovingIS().get() == spIS1.get());
      CHECK(path.getTargetIS().get() == spIS3.get());
      CHECK(path.getBegin()->get() == spTrans1_2.get());
      CHECK(path.size() == 2);
      CHECK(path.checkProblemCompliance(spPS1.get()));
      CHECK(!path.checkProblemCompliance(spPS2.get()));

      CHECK_THROW_EXPLICIT(path.insertElement(path.getBegin(),spTrans2_3),::iro::exceptions::InvalidTargetIS);
      CHECK_NO_THROW(path.removeElement(++(path.getBegin())));
      //current path: 1->2
      CHECK(path.getMovingIS().get() == spIS1.get());
      CHECK(path.getTargetIS().get() == spIS2.get());
      CHECK(path.size() == 1);

      CHECK_NO_THROW(path.appendElement(spTrans2_3));
      //current path: 1->2 2->3
      CHECK_THROW_EXPLICIT(path.insertElement(path.getBegin(),spTrans3_4),::iro::exceptions::InvalidTargetIS);
      CHECK_THROW_EXPLICIT(path.appendElement(spTrans4_3),::iro::exceptions::InvalidMovingIS);
      CHECK_THROW_EXPLICIT(path.appendElement(spTrans3_4d),::iro::exceptions::InvalidDataRepresentation);
      CHECK_NO_THROW(path.appendElement(spTrans3_4));
      //current path: 1->2 2->3 3->4

      CHECK(path.getMovingIS().get() == spIS1.get());
      CHECK(path.getTargetIS().get() == spIS4.get());
      CHECK(path.size() == 3);
      CHECK(!path.checkProblemCompliance(spPS1.get())); //its a mixed path now so both statements 
      CHECK(!path.checkProblemCompliance(spPS2.get())); //ar not compliant any more

      //reset
      CHECK_NO_THROW(path.resetElements());
      CHECK(!(path.getMovingIS()));
      CHECK(!(path.getTargetIS()));
      CHECK(path.getBegin() == path.getEnd());
      CHECK(path.size() == 0);
      CHECK(path.checkProblemCompliance(spPS1.get()));
      CHECK(path.checkProblemCompliance(spPS2.get()));

      //check if discrete support elements can no be added and continuous cause exceptions
      CHECK_NO_THROW(path.appendElement(spTrans1_2d));
      CHECK_THROW_EXPLICIT(path.appendElement(spTrans2_3),::iro::exceptions::InvalidDataRepresentation);
      CHECK(!path.checkProblemCompliance(spPS1.get()));
      CHECK(path.checkProblemCompliance(spPS2.get()));

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
