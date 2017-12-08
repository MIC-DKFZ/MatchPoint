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


#include "mapSimpleRegistrationInfo.h"

#include "litCheckMacros.h"

#include <stdlib.h>
#include "mapOntologyExceptions.h"

namespace iro
{
  namespace testing
  {

    int mapSimpleRegistrationInfoTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      ::iro::scenario::SimpleRegistrationInfo info;

      ::iro::scenario::SimpleInformationSpace::Pointer spMovingIS(new ::iro::scenario::SimpleInformationSpace);
      ::iro::scenario::SimpleInformationSpace::Pointer spTargetIS(new ::iro::scenario::SimpleInformationSpace);
      spMovingIS->setUID("1");
      spTargetIS->setUID("2");
      ::iro::scenario::SimpleProblemStatement::Pointer spPS(new ::iro::scenario::SimpleProblemStatement);
      ::iro::scenario::SimpleProblemStatement::Pointer spPS2(new ::iro::scenario::SimpleProblemStatement);
      
      ::iro::scenario::SimpleTransformationInfo::Pointer spTInfo1(new ::iro::scenario::SimpleTransformationInfo);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTInfo2(new ::iro::scenario::SimpleTransformationInfo);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTInfo3(new ::iro::scenario::SimpleTransformationInfo);
      ::iro::scenario::SimpleTransformationInfo::Pointer spTInfo4(new ::iro::scenario::SimpleTransformationInfo);

      spTInfo1->setMovingIS(spMovingIS);
      spTInfo1->setTargetIS(spTargetIS);
      spTInfo1->setAssociatedProblemStatement(spPS);
      spTInfo1->setSupportedDataRepresentation(::iro::DataRepresentation::Continuous);

      spTInfo2->setMovingIS(spMovingIS);
      spTInfo2->setTargetIS(spTargetIS);
      spTInfo2->setAssociatedProblemStatement(spPS);
      spTInfo2->setSupportedDataRepresentation(::iro::DataRepresentation::Discrete);

      spTInfo3->setMovingIS(spTargetIS);
      spTInfo3->setTargetIS(spMovingIS);
      spTInfo3->setAssociatedProblemStatement(spPS);
      spTInfo3->setSupportedDataRepresentation(::iro::DataRepresentation::Discrete);

      spTInfo4->setMovingIS(spMovingIS);
      spTInfo4->setTargetIS(spTargetIS);
      spTInfo4->setAssociatedProblemStatement(spPS2);
      spTInfo4->setSupportedDataRepresentation(::iro::DataRepresentation::Discrete);

      //check default values
      CHECK(!(info.getMovingIS()));
      CHECK(!(info.getTargetIS()));
      CHECK(!(info.getAssociatedProblemStatement()));
      CHECK(!(info.getContinuousTransformation()));
      CHECK(!(info.getDiscreteTransformation()));

      //check setter and getter
      CHECK_NO_THROW(info.setTransformations(spTInfo1,spTInfo2));
      CHECK_THROW_EXPLICIT(info.setTransformations(spTInfo2,spTInfo1),::iro::exceptions::InvalidArgument); //wrong data representations
      CHECK_EQUAL(spTInfo1.get(), info.getContinuousTransformation().get());
      CHECK_EQUAL(spTInfo2.get(), info.getDiscreteTransformation().get());
      CHECK_EQUAL(spPS.get(), info.getAssociatedProblemStatement().get());
      CHECK_EQUAL(spMovingIS.get(), info.getMovingIS().get());
      CHECK_EQUAL(spTargetIS.get(), info.getTargetIS().get());

      CHECK_THROW_EXPLICIT(info.setTransformations(::iro::scenario::SimpleTransformationInfo::Pointer(),spTInfo1),::iro::exceptions::InvalidArgument); //wrong data representations
      CHECK_THROW_EXPLICIT(info.setTransformations(spTInfo2,::iro::scenario::SimpleTransformationInfo::Pointer()),::iro::exceptions::InvalidArgument); //wrong data representations

      CHECK_THROW_EXPLICIT(info.setTransformations(spTInfo1,spTInfo3),::iro::exceptions::InvalidArgument); //wrong IS
      CHECK_EQUAL(spTInfo1.get(), info.getContinuousTransformation().get()); //info stays unchanged
      CHECK_EQUAL(spTInfo2.get(), info.getDiscreteTransformation().get()); //info stays unchanged
      CHECK_EQUAL(spPS.get(), info.getAssociatedProblemStatement().get());
      CHECK_EQUAL(spMovingIS.get(), info.getMovingIS().get());
      CHECK_EQUAL(spTargetIS.get(), info.getTargetIS().get());

      CHECK_THROW_EXPLICIT(info.setTransformations(spTInfo1,spTInfo4),::iro::exceptions::InvalidArgument); //wrong problem statement
      CHECK_EQUAL(spTInfo1.get(), info.getContinuousTransformation().get()); //info stays unchanged
      CHECK_EQUAL(spTInfo2.get(), info.getDiscreteTransformation().get()); //info stays unchanged
      CHECK_EQUAL(spPS.get(), info.getAssociatedProblemStatement().get());
      CHECK_EQUAL(spMovingIS.get(), info.getMovingIS().get());
      CHECK_EQUAL(spTargetIS.get(), info.getTargetIS().get());

      CHECK_NO_THROW(info.setTransformations(::iro::scenario::SimpleTransformationInfo::Pointer(),spTInfo4));
      CHECK(NULL == info.getContinuousTransformation().get());
      CHECK_EQUAL(spTInfo4.get(), info.getDiscreteTransformation().get());
      CHECK_EQUAL(spPS2.get(), info.getAssociatedProblemStatement().get());
      CHECK_EQUAL(spMovingIS.get(), info.getMovingIS().get());
      CHECK_EQUAL(spTargetIS.get(), info.getTargetIS().get());

      CHECK_NO_THROW(info.setTransformations(spTInfo1,::iro::scenario::SimpleTransformationInfo::Pointer()));
      CHECK_EQUAL(spTInfo1.get(), info.getContinuousTransformation().get());
      CHECK(NULL == info.getDiscreteTransformation().get());
      CHECK_EQUAL(spPS.get(), info.getAssociatedProblemStatement().get());
      CHECK_EQUAL(spMovingIS.get(), info.getMovingIS().get());
      CHECK_EQUAL(spTargetIS.get(), info.getTargetIS().get());

      //check compliance

      CHECK(info.checkProblemCompliance(spPS.get()));
      CHECK(!info.checkProblemCompliance(spPS2.get()));

      //check clone
      ::iro::scenario::SimpleRegistrationInfo::Pointer spClone;
      CHECK_NO_THROW(spClone = info.clone());
      CHECK(spClone);

      CHECK_EQUAL(info.getContinuousTransformation().get(), spClone->getContinuousTransformation().get());
      CHECK_EQUAL(info.getDiscreteTransformation().get(), spClone->getDiscreteTransformation().get());
      CHECK_EQUAL(info.getMovingIS().get(), spClone->getMovingIS().get());
      CHECK_EQUAL(info.getTargetIS().get(), spClone->getTargetIS().get());
      CHECK_EQUAL(info.getAssociatedProblemStatement().get(), spClone->getAssociatedProblemStatement().get());

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
