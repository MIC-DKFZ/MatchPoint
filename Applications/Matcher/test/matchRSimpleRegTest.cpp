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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/test/matchRSimpleMappingTest.cpp $
*/

#include "itksys/SystemTools.hxx"

#include "litCheckMacros.h"
#include "litImageTester.h"

#include "mapProcessExecutor.h"
#include "mapImageReader.h"
#include "mapFileDispatch.h"
#include "mapDeploymentDLLAccess.h"
#include "mapAffineMatrixDecomposer.h"
#include "mapRegistrationFileReader.h"

namespace map
{
	namespace testing
	{

		//defined by mapDeploymentTests.cpp. It is tha path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char* _callingAppPath;

    template<unsigned int IDim>
    bool checkRegKernel(const ::map::core::RegistrationBase* reg, const ::map::core::RegistrationBase* ref, bool decomposeInverse)
    {
      const ::map::core::Registration<IDim, IDim>* castedReg = dynamic_cast<const ::map::core::Registration<IDim, IDim>*>(reg);
      const ::map::core::Registration<IDim, IDim>* castedRef = dynamic_cast<const ::map::core::Registration<IDim, IDim>*>(ref);

      typename ::map::core::AffineMatrixDecomposer<IDim, IDim>::MatrixType matrix;
      typename ::map::core::AffineMatrixDecomposer<IDim, IDim>::OffsetType offset;
      typename ::map::core::AffineMatrixDecomposer<IDim, IDim>::MatrixType refMatrix;
      typename ::map::core::AffineMatrixDecomposer<IDim, IDim>::OffsetType refOffset;

      if (decomposeInverse)
      {
        if (!::map::core::AffineMatrixDecomposer<IDim, IDim>::decomposeKernel(&(castedReg->getInverseMapping()), matrix, offset))
          return false;
        if (!::map::core::AffineMatrixDecomposer<IDim, IDim>::decomposeKernel(&(castedRef->getInverseMapping()), refMatrix, refOffset))
          return false;
      }
      else
      {
        if (!::map::core::AffineMatrixDecomposer<IDim, IDim>::decomposeKernel(&(castedReg->getDirectMapping()), matrix, offset))
          return false;
        if (!::map::core::AffineMatrixDecomposer<IDim, IDim>::decomposeKernel(&(castedRef->getDirectMapping()), refMatrix, refOffset))
          return false;
      }

      //check matrix
      for (unsigned int r = 0; r < IDim; ++r)
      {
        for (unsigned int c = 0; c < IDim; ++c)
        {
          if (!lit::AreClose(refMatrix[r][c], matrix[r][c], 0.001))
            return false;
        }
      }
      //check offset
      for (unsigned int r = 0; r < IDim; ++r)
      {
        if (!lit::AreClose(refOffset[r], offset[r], 0.02))
          return false;
      }
      return true;
    }

    bool checkReg(const ::map::core::String& regFile, const ::map::core::String& refRegFile, bool decomposeInverse)
    {
      ::map::io::RegistrationFileReader::Pointer reader = ::map::io::RegistrationFileReader::New();

      auto reg = reader->read(regFile);
      auto ref = reader->read(refRegFile);

      if (reg->getMovingDimensions() == 2)
      {
        return checkRegKernel<2>(reg, ref, decomposeInverse);
      }
      else
      {
        return checkRegKernel<3>(reg, ref, decomposeInverse);
      }
    };


    int matchRSimpleRegTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string matchRPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			std::string movingPath = "Moving Data path not set.";
      std::string targetPath = "Target data path not set.";
      std::string algPath = "Algorithm path not set.";
      std::string outputPath = "Output data path not set.";
      std::string refPath = "Reference data path not set.";

			map::utilities::ProcessExecutor::Pointer spExec = map::utilities::ProcessExecutor::New();
      spExec->setSharedOutputPipes(true);

			map::utilities::ProcessExecutor::ArgumentListType args;

      if (argc > 1)
			{
				movingPath = argv[1];
			}

      if (argc > 2)
      {
        targetPath = argv[2];
      }

      if (argc > 3)
      {
        algPath = ::map::deployment::getDeploymentDLLMDRAPrefix()+"_"+argv[3]+::map::deployment::getDeploymentDLLExtension();
        algPath = ::map::core::FileDispatch::createFullPath(::map::core::FileDispatch::getPath(_callingAppPath), algPath);
      }

      if (argc > 4)
      {
        outputPath = argv[4];
      }

      if (argc > 5)
      {
        refPath = argv[5];
      }

      args.push_back(movingPath);
      args.push_back(targetPath);
      args.push_back(algPath);
      args.push_back("-o");
      args.push_back(outputPath);

      unsigned int index = 6;
      while (index < argc)
      {
        args.push_back(argv[index++]);
      }

			//////////////////////////////////////////////////
			// Test: behavior on simple registration task.

			CHECK(spExec->execute(matchRPath, "matchR", args));
			CHECK_EQUAL(0, spExec->getExitValue());

      CHECK(checkReg(outputPath, refPath, true));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
