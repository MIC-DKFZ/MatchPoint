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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/test/mapRegistrationFileReaderTest.cpp $
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

namespace map
{
	namespace testing
	{

		int mapRegistrationFileReaderTest(int argc, char *argv[])
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

			// create the generator
			typedef io::RegistrationFileReader ReaderType;
			ReaderType::Pointer spReader = ReaderType::New();

			typedef core::Registration<2, 2> RegistrationType;

			// check whether the LoadPolicy worked for the stacks
			typedef ReaderType::LoaderStackType LoaderStackType;

			CHECK(NULL != LoaderStackType::getProvider(io::MatrixModelBasedKernelLoader<2>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(io::MatrixModelBasedKernelLoader<3>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(io::NullRegistrationKernelLoader<2, 2>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(io::NullRegistrationKernelLoader<2, 3>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(io::NullRegistrationKernelLoader<3, 2>::getStaticProviderName()));
			CHECK(NULL != LoaderStackType::getProvider(io::NullRegistrationKernelLoader<3, 3>::getStaticProviderName()));

			// create a ModelBasedKernels for testing

			core::RegistrationBase::Pointer spRegistrationBase;

			CHECK_NO_THROW(spRegistrationBase = spReader->read(refRegFile3));
			CHECK_EQUAL("RegistrationFileWriterTest.reg3", spRegistrationBase->getRegistrationUID());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
