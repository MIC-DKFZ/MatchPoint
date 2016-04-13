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

#include <itkEuler2DTransform.h>

#include "litCheckMacros.h"
#include "litTextFileTester.h"
#include "mapMatrixModelBasedKernelWriter.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapRegistrationFileWriter.h"
#include "test/mapTestKernelBase.h"
#include "mapNullRegistrationKernel.h"
#include "mapExpandingFieldKernelWriter.h"

namespace map
{
	namespace testing
	{

		int mapRegistrationFileWriterTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: test storage path
			//           2: ref path

			PREPARE_DEFAULT_TEST_REPORTING;

			std::string testPath = "";
			std::string refPath = "";

			if (argc > 1)
			{
				testPath = argv[1];
			}

			if (argc > 2)
			{
				refPath = argv[2];
			}

			std::string testRegFile1 = testPath + "/savedReg1.mapr";
			std::string testRegFile2 = testPath + "/savedReg2.mapr";
			std::string testRegFile3 = testPath + "/savedReg3.mapr";
			std::string refRegFile1 = refPath + "/registrationFileWriterReader_Ref1.mapr";
			std::string refRegFile2 = refPath + "/registrationFileWriterReader_Ref2.mapr";
			std::string refRegFile3 = refPath + "/registrationFileWriterReader_Ref3.mapr";

			// create the generator
			typedef io::RegistrationFileWriter<2, 2> WriterType;
			WriterType::Pointer spWriter = WriterType::New();

			typedef WriterType::RegistrationType RegistrationType;

			// check whether the LoadPolicy worked for the stacks
			typedef WriterType::DirectKernelWriterStackType DirectStackType;
			typedef WriterType::InverseKernelWriterStackType InverseStackType;

			CHECK(NULL != DirectStackType::getProvider(
					  io::MatrixModelBasedKernelWriter<2, 2>::getStaticProviderName()));
			CHECK(NULL != DirectStackType::getProvider(
					  io::NullRegistrationKernelWriter<2, 2>::getStaticProviderName()));
			CHECK(NULL != DirectStackType::getProvider(
					  io::ExpandingFieldKernelWriter<2, 2>::getStaticProviderName()));
			CHECK(NULL != DirectStackType::getProvider(
					  io::InvertingKernelWriter<2, 2>::getStaticProviderName()));
			CHECK(NULL != InverseStackType::getProvider(
					  io::MatrixModelBasedKernelWriter<2, 2>::getStaticProviderName()));
			CHECK(NULL != InverseStackType::getProvider(
					  io::NullRegistrationKernelWriter<2, 2>::getStaticProviderName()));
			CHECK(NULL != InverseStackType::getProvider(
					  io::ExpandingFieldKernelWriter<2, 2>::getStaticProviderName()));
			CHECK(NULL != InverseStackType::getProvider(
					  io::InvertingKernelWriter<2, 2>::getStaticProviderName()));

			// create a ModelBasedKernels for testing
			typedef core::PreCachedRegistrationKernel<2, 2> KernelType;
			KernelType::Pointer spKernel = KernelType::New();
			KernelType::Pointer spKernel2 = KernelType::New();

			typedef TestKernelBase<2, 2> IllegalKernelType;
			typedef core::NullRegistrationKernel<2, 2> NullKernelType;

			typedef ::itk::Euler2DTransform< ::map::core::continuous::ScalarType> TransformType;
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::Pointer spTransform2 = TransformType::New();

			TransformType::ParametersType params(3);
			params[0] = 1.5708;
			params[1] = 5;
			params[2] = 2;
			spTransform->SetParameters(params);
			spKernel->setTransformModel(spTransform);

			TransformType::ParametersType params2(3);
			params2[0] = -1.5708;
			params2[1] = -5;
			params2[2] = -2;
			spTransform2->SetParameters(params2);
			spKernel2->setTransformModel(spTransform2);

			// create registrations for testing purposes
			// let the writer store the registration
			RegistrationType::Pointer spValidRegistration = RegistrationType::New();
			::map::core::RegistrationManipulator<RegistrationType> manipulator(spValidRegistration.GetPointer());
			manipulator.setDirectMapping(spKernel);
			manipulator.setInverseMapping(NullKernelType::New());
			::map::core::RegistrationManipulator<RegistrationType>::TagMapType tags;
			tags.insert(std::make_pair("RegistrationUID", "RegistrationFileWriterTest.reg1"));
			manipulator.setTagValues(tags);

			RegistrationType::Pointer spValidRegistration2 = RegistrationType::New();
			::map::core::RegistrationManipulator<RegistrationType> manipulator2(spValidRegistration2.GetPointer());
			manipulator2.setDirectMapping(NullKernelType::New());
			manipulator2.setInverseMapping(spKernel);
			::map::core::RegistrationManipulator<RegistrationType>::TagMapType tags2;
			tags2.insert(std::make_pair("RegistrationUID", "RegistrationFileWriterTest.reg2"));
			manipulator2.setTagValues(tags2);

			RegistrationType::Pointer spValidRegistration3 = RegistrationType::New();
			::map::core::RegistrationManipulator<RegistrationType> manipulator3(spValidRegistration3.GetPointer());
			manipulator3.setDirectMapping(spKernel);
			manipulator3.setInverseMapping(spKernel2);
			::map::core::RegistrationManipulator<RegistrationType>::TagMapType tags3;
			tags3.insert(std::make_pair("RegistrationUID", "RegistrationFileWriterTest.reg3"));
			tags3.insert(std::make_pair("Purpose", "UnitTest"));
			manipulator3.setTagValues(tags3);

			RegistrationType::Pointer spInvalidDirectKernelRegistration = RegistrationType::New();
			::map::core::RegistrationManipulator<RegistrationType> manipulator4(
				spInvalidDirectKernelRegistration.GetPointer());
			manipulator4.setDirectMapping(IllegalKernelType::New());
			manipulator4.setInverseMapping(spKernel2);

			RegistrationType::Pointer spInvalidInverseKernelRegistration = RegistrationType::New();
			::map::core::RegistrationManipulator<RegistrationType> manipulator5(
				spInvalidInverseKernelRegistration.GetPointer());
			manipulator5.setDirectMapping(spKernel);
			manipulator5.setInverseMapping(IllegalKernelType::New());

			CHECK_NO_THROW(spWriter->write(spValidRegistration, testRegFile1));
			CHECK_NO_THROW(spWriter->write(spValidRegistration2, testRegFile2));
			CHECK_NO_THROW(spWriter->write(spValidRegistration3, testRegFile3));
			CHECK_THROW_EXPLICIT(spWriter->write(spInvalidDirectKernelRegistration, ""),
								 core::MissingProviderException);
			CHECK_THROW_EXPLICIT(spWriter->write(spInvalidInverseKernelRegistration, ""),
								 core::MissingProviderException);

			lit::TextFileTester tester;
			tester.setExpectedFile(refRegFile1);
			tester.setActualFile(testRegFile1);
			CHECK_TESTER(tester);
			tester.setExpectedFile(refRegFile2);
			tester.setActualFile(testRegFile2);
			CHECK_TESTER(tester);
			tester.setExpectedFile(refRegFile3);
			tester.setActualFile(testRegFile3);
			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
