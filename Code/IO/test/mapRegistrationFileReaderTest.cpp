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

#include "litCheckMacros.h"
#include "litTextFileTester.h"
#include "mapMatrixModelBasedKernelLoader.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapITKAffineTransform.h"
#include "mapRegistrationFileReader.h"
#include "test/mapTestKernelBase.h"
#include "mapNullRegistrationKernel.h"
#include "mapNullRegistrationKernelLoader.h"
#include "mapExpandingFieldKernelLoader.h"

namespace map
{
	namespace testing
	{

		int mapRegistrationFileReaderTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: ref path

			PREPARE_DEFAULT_TEST_REPORTING;

			std::string refPath = "";

			if (argc > 1)
			{
				refPath = argv[1];
			}

			std::string refRegFile1 = refPath + "/registrationFileWriterReader_Ref1.mapr";
			std::string refRegFile2 = refPath + "/registrationFileWriterReader_Ref2.mapr";
			std::string refRegFile3 = refPath + "/registrationFileWriterReader_Ref3.mapr";
			std::string refRegFile4 = refPath + "/registrationFileWriterReader_Ref4.mapr";
      std::string refRegFile5 = refPath + "/registrationFileWriterReader_Ref5.mapr";
      std::string refRegFile6 = refPath + "/registrationFileWriterReader_Ref6.mapr";

			// create the generator
			typedef io::RegistrationFileReader ReaderType;
			ReaderType::Pointer spReader = ReaderType::New();

			typedef core::Registration<2, 2> RegistrationType;

			// check whether the LoadPolicy worked for the stacks
			typedef ReaderType::LoaderStackType LoaderStackType;

			CHECK(NULL != LoaderStackType::getProvider(
					  io::MatrixModelBasedKernelLoader<2>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(
					  io::MatrixModelBasedKernelLoader<3>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(
					  io::NullRegistrationKernelLoader<2, 2>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(
					  io::NullRegistrationKernelLoader<2, 3>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(
					  io::NullRegistrationKernelLoader<3, 2>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(
					  io::NullRegistrationKernelLoader<3, 3>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(
					  io::ExpandingFieldKernelLoader<2, 2>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(
					  io::ExpandingFieldKernelLoader<3, 3>::getStaticProviderName()));

			// create a ModelBasedKernels for testing

			core::RegistrationBase::Pointer spRegistrationBase;

			CHECK_NO_THROW(spRegistrationBase = spReader->read(refRegFile1));
			CHECK_EQUAL("RegistrationFileWriterTest.reg1", spRegistrationBase->getRegistrationUID());

			CHECK_NO_THROW(spRegistrationBase = spReader->read(refRegFile2));
			CHECK_EQUAL("RegistrationFileWriterTest.reg2", spRegistrationBase->getRegistrationUID());

			CHECK_NO_THROW(spRegistrationBase = spReader->read(refRegFile3));
			CHECK_EQUAL("RegistrationFileWriterTest.reg3", spRegistrationBase->getRegistrationUID());

			CHECK_NO_THROW(spRegistrationBase = spReader->read(refRegFile4));
			CHECK_EQUAL("RegistrationFileWriterTest.reg4", spRegistrationBase->getRegistrationUID());

      CHECK_NO_THROW(spRegistrationBase = spReader->read(refRegFile5));
      CHECK_EQUAL("RegistrationFileReaderTest.invertingKernel1", spRegistrationBase->getRegistrationUID());

      CHECK_NO_THROW(spRegistrationBase = spReader->read(refRegFile6));
      CHECK_EQUAL("RegistrationFileReaderTest.invertingKernel2", spRegistrationBase->getRegistrationUID());

      RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
