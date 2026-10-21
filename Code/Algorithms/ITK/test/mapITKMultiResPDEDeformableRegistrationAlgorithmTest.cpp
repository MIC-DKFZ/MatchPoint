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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <cstring>
#include <memory>
#include <vector>

#include "litCheckMacros.h"

#include "mapITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm.h"

namespace map
{
  namespace testing
  {
    typedef map::core::discrete::Elements<3>::InternalImageType ImageType;

    mapGenerateAlgorithmUIDPolicyMacro(MultiResPDEDeformableTestUIDPolicy, "de.dkfz.matchpoint.test",
                                       "MultiResPDEDeformable", "1.0.0", "");

    int mapITKMultiResPDEDeformableRegistrationAlgorithmTest(int, char* [])
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      typedef algorithm::boxed::ITKFastSymmetricForcesDemonsMultiResRegistrationAlgorithm<ImageType, MultiResPDEDeformableTestUIDPolicy>
      RegistrationAlgorithmType;

      const unsigned int instanceCount = 100;

      // Fresh heap memory is often zeroed and would hide uninitialized members. Freed blocks of
      // the algorithm's size, filled with a pattern, are likely reused for the instances below.
      {
        std::vector<std::unique_ptr<char[]> > blocks;

        for (unsigned int i = 0; i < instanceCount; ++i)
        {
          blocks.emplace_back(new char[sizeof(RegistrationAlgorithmType)]);
          std::memset(blocks.back().get(), 0x5A, sizeof(RegistrationAlgorithmType));
        }
      }

      std::vector<RegistrationAlgorithmType::Pointer> algorithms;

      for (unsigned int i = 0; i < instanceCount; ++i)
      {
        algorithms.push_back(RegistrationAlgorithmType::New());
      }

      // Before a run, an algorithm is at its first level and reports that level's maximum of
      // iterations.
      for (const auto& spAlgorithm : algorithms)
      {
        CHECK_EQUAL(0u, spAlgorithm->getCurrentLevel());
        CHECK_EQUAL(algorithms.front()->getMaxIterations(), spAlgorithm->getMaxIterations());
      }

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace map
