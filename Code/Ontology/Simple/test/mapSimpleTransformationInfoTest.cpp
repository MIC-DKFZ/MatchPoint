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


#include "mapSimpleTransformationInfo.h"
#include "mapSimpleAlgorithmExecutionInfo.h"

#include "litCheckMacros.h"

#include <stdlib.h>

namespace iro
{
  namespace testing
  {

    int mapSimpleTransformationInfoTest(int, char* [] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      ::iro::scenario::SimpleTransformationInfo info;

      ::iro::scenario::SimpleInformationSpace::Pointer spMovingIS(new ::iro::scenario::SimpleInformationSpace);
      ::iro::scenario::SimpleInformationSpace::Pointer spTargetIS(new ::iro::scenario::SimpleInformationSpace);
      ::iro::scenario::SimpleProblemStatement::Pointer spPS(new ::iro::scenario::SimpleProblemStatement);
      ::iro::scenario::SimpleProblemStatement::Pointer spPS2(new ::iro::scenario::SimpleProblemStatement);
      ::iro::scenario::SimpleAlgorithmExecutionInfo::Pointer spExecInfo(new ::iro::scenario::SimpleAlgorithmExecutionInfo);

      //check default values
      CHECK(!(info.getMovingIS()));
      CHECK(!(info.getTargetIS()));
      CHECK(!(info.getAssociatedProblemStatement()));

      CHECK( info.getSupportedDataRepresentation() == ::iro::DataRepresentation::Discrete);
      CHECK_EQUAL( "", info.getUID());
      CHECK( info.getFOVScope() == ::iro::FOVScope::Local );

      CHECK(!(info.getAlgorithmExecutionInfo()));

      //check setter
      CHECK_NO_THROW(info.setMovingIS(spMovingIS));
      CHECK_NO_THROW(info.setTargetIS(spTargetIS));
      CHECK_NO_THROW(info.setAssociatedProblemStatement(spPS));
      CHECK_NO_THROW(info.setSupportedDataRepresentation(::iro::DataRepresentation::Continuous));
      CHECK_NO_THROW(info.setUID("TestInfo"));
      CHECK_NO_THROW(info.setFOVScope(::iro::FOVScope::Global));
      CHECK_NO_THROW(info.setAlgorithmExecutionInfo(spExecInfo));

      //check getter
      CHECK_EQUAL(spMovingIS.get(), info.getMovingIS().get());
      CHECK_EQUAL(spTargetIS.get(), info.getTargetIS().get());
      CHECK_EQUAL(spPS.get(), info.getAssociatedProblemStatement().get());
      CHECK_EQUAL(spExecInfo.get(), info.getAlgorithmExecutionInfo().get());

      CHECK_EQUAL("TestInfo", info.getUID());
      CHECK_EQUAL(::iro::FOVScope::Global, info.getFOVScope());
      CHECK_EQUAL(::iro::DataRepresentation::Continuous, info.getSupportedDataRepresentation());

      //check compliance

      CHECK(info.checkProblemCompliance(spPS.get()));
      CHECK(!info.checkProblemCompliance(spPS2.get()));

      //check clone
      ::iro::scenario::SimpleTransformationInfo::Pointer spClone;
      CHECK_NO_THROW(spClone = info.clone());
      CHECK(spClone);

      CHECK_EQUAL(info.getMovingIS().get(), spClone->getMovingIS().get());
      CHECK_EQUAL(info.getTargetIS().get(), spClone->getTargetIS().get());
      CHECK_EQUAL(info.getAssociatedProblemStatement().get(), spClone->getAssociatedProblemStatement().get());
      CHECK_EQUAL(info.getAlgorithmExecutionInfo().get(), spClone->getAlgorithmExecutionInfo().get());

      CHECK_EQUAL(info.getUID(), spClone->getUID());
      CHECK_EQUAL(info.getFOVScope(), spClone->getFOVScope());
      CHECK_EQUAL(info.getSupportedDataRepresentation(), spClone->getSupportedDataRepresentation());

      //check traits
      scenario::SimpleTransformationInfoTraits::Type info2;
      scenario::SimpleTransformationInfoTraits::Pointer spInfo2;
      scenario::SimpleTransformationInfoTraits::ConstPointer spConstInfo2;


      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace iro
