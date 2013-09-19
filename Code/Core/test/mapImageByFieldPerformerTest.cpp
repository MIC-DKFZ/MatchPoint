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

#include "mapImageByFieldPerformer.h"
#include "mapRegistration.h"
#include "mapRegistrationManipulator.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapTestKernelBase.h"

#include "litCheckMacros.h"
#include "litImageTester.h"

#include "itkLinearInterpolateImageFunction.h"

namespace map
{
	namespace testing
	{

		typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel FieldKernelType;

		namespace
		{
			FieldKernelType::FieldType::Pointer generateField()
			{
				FieldKernelType::FieldType::Pointer spField = FieldKernelType::FieldType::New();

				FieldKernelType::FieldType::RegionType::SizeType size = {300, 100};
				FieldKernelType::FieldType::RegionType region(size);
				FieldKernelType::FieldType::SpacingType spacing(1.0);
				//Generate imagegrid
				spField->SetRegions(region);
				spField->SetSpacing(spacing);
				spField->Allocate();

				FieldKernelType::FieldType::ValueType value;
				value[0] = -15;
				value[1] = -10;

				spField->FillBuffer(value);

				return spField;
			}
		}

		int mapImageByFieldPerformerTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: input image
			//           2: reference image
			//           3: reference image 2
			//           4: reference image 3
			//           5: Check threshold
			//           6: test output file name pattern

			PREPARE_DEFAULT_TEST_REPORTING;

			double checkThreshold = 0.1;
			std::string inputImageFileName = "";
			std::string referenceImageFileName = "";
			std::string referenceImageFile2Name = "";
			std::string referenceImageFile3Name = "";
			std::string testImageFileName = "";

			if (argc > 1)
			{
				inputImageFileName = argv[1];
			}

			if (argc > 2)
			{
				referenceImageFileName = argv[2];
			}

			if (argc > 3)
			{
				referenceImageFile2Name = argv[3];
			}

			if (argc > 4)
			{
				referenceImageFile3Name = argv[4];
			}

			if (argc > 5)
			{
				std::istringstream istream;
				istream.str(argv[5]);
				istream >> checkThreshold;
			}

			if (argc > 6)
			{
				testImageFileName = argv[6];
			}

			typedef core::Registration<2, 2> RegistrationType;
			typedef core::Registration<2, 3> Registration2Type;
			typedef core::discrete::Elements<2>::InternalImageType InputDataType;
			typedef core::discrete::Elements<2>::InternalImageType ResultDataType;
			typedef core::discrete::Elements<3>::InternalImageType ResultData2Type;
			typedef TestKernelBase<2, 2> IllegalKernelType;

			typedef core::ImageByFieldPerformer<RegistrationType, InputDataType, ResultDataType> PerformerType;
			typedef core::ImageByFieldPerformer<Registration2Type, InputDataType, ResultData2Type>
			Performer2Type;

			//Now we create the kernels
			FieldKernelType::Pointer spKernel = FieldKernelType::New();
			IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();

			spKernel->setField(*(generateField().GetPointer()));

			//creating registrations
			RegistrationType::Pointer spRegistration = RegistrationType::New();
			RegistrationType::Pointer spIllegalRegistration1 = RegistrationType::New();

			core::RegistrationManipulator<RegistrationType> manipulator1(spRegistration);
			manipulator1.setDirectMapping(spIllegalKernel);
			manipulator1.setInverseMapping(spKernel);

			core::RegistrationManipulator<RegistrationType> manipulator2(spIllegalRegistration1);
			manipulator2.setDirectMapping(spIllegalKernel);
			manipulator2.setInverseMapping(spIllegalKernel);

			//load input and reference data
			InputDataType::Pointer spInputImage =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					inputImageFileName);
			ResultDataType::Pointer spReferenceImage =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					referenceImageFileName);
			ResultDataType::Pointer spReferenceImage2 =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					referenceImageFile2Name);
			ResultDataType::Pointer spReferenceImage3 =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					referenceImageFile3Name);

			PerformerType::RequestType::ResultImageDescriptorType::Pointer spFieldRep =
				core::createFieldRepresentation(*spInputImage);
			PerformerType::RequestType::ResultImageDescriptorType::Pointer spFieldRep2 =
				core::createFieldRepresentation(*spInputImage);
			PerformerType::RequestType::ResultImageDescriptorType::Pointer spFieldRep3 =
				core::createFieldRepresentation(*spInputImage);

			PerformerType::RequestType::ResultImageDescriptorType::PointType newOrigin;
			newOrigin[0] = 10.0;
			newOrigin[1] = -10.0;
			spFieldRep2->setOrigin(newOrigin);

			spFieldRep3->setSpacing(PerformerType::RequestType::ResultImageDescriptorType::SpacingType(4.0));

			typedef itk::LinearInterpolateImageFunction<InputDataType, core::continuous::ScalarType>
			InterpolatorType;
			InterpolatorType::Pointer spInterpolator = InterpolatorType::New();

			//Create requests
			// valid request
			PerformerType::RequestType request(spRegistration.GetPointer(), spInputImage.GetPointer(),
											   spFieldRep.GetPointer(), spInterpolator, true, 0, false, 0);
			// valid request
			PerformerType::RequestType request2(spRegistration.GetPointer(), spInputImage.GetPointer(),
												spFieldRep2.GetPointer(), spInterpolator, false, 50, false, 0);
			// valid request
			PerformerType::RequestType request3(spRegistration.GetPointer(), spInputImage.GetPointer(),
												spFieldRep3.GetPointer(), spInterpolator, false, 50, false, 0);
			// valid request
			PerformerType::RequestType request4(spRegistration.GetPointer(), spInputImage.GetPointer(),
												spFieldRep2.GetPointer(), spInterpolator, true, 0, false, 0);
			// illegal request
			PerformerType::RequestType illegalRequest1(spRegistration.GetPointer(), spInputImage.GetPointer(),
					spFieldRep.GetPointer(), spInterpolator, true, 0, false, 0);
			illegalRequest1._spInputData = NULL;
			// illegal request
			PerformerType::RequestType illegalRequest2(spIllegalRegistration1.GetPointer(),
					spInputImage.GetPointer(), spFieldRep.GetPointer(), spInterpolator, true, 0, false, 0);
			// illegal request
			PerformerType::RequestType illegalRequest3(spRegistration.GetPointer(), spInputImage.GetPointer(),
					spFieldRep.GetPointer(), spInterpolator, true, 0, false, 0);
			illegalRequest3._spResultDescriptor = NULL;
			// illegal request
			PerformerType::RequestType illegalRequest4(spRegistration.GetPointer(), spInputImage.GetPointer(),
					spFieldRep.GetPointer(), spInterpolator, true, 0, false, 0);
			illegalRequest4._spInterpolateFunction = NULL;
			// "illegal request" as long there is no implementation that supports exception throwing in the case of mapping outside of the input image
			PerformerType::RequestType illegalRequest5(spRegistration.GetPointer(), spInputImage.GetPointer(),
					spFieldRep.GetPointer(), spInterpolator, true, 0, true, 0);

			//creating the combinator
			PerformerType::Pointer spPerformer = PerformerType::New();

			//TEST
			CHECK_EQUAL(false, spPerformer->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(false, spPerformer->canHandleRequest(illegalRequest2));
			CHECK_EQUAL(true, spPerformer->canHandleRequest(
							illegalRequest3)); //is illegal because result descriptor is invalid, but theoretically it can be handled by the performer
			CHECK_EQUAL(true, spPerformer->canHandleRequest(
							illegalRequest4)); //is illegal because interpolate function is invalid, but theoretically it can be handled by the performer
			CHECK_EQUAL(true, spPerformer->canHandleRequest(
							illegalRequest5)); //is illegal because parts are not implemented yet (see performer documentation), but theoretically it can be handled by the performer
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request));
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request2));
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request3));
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request4));

			CHECK_EQUAL("ImageByFieldPerformer<Registration<2,2>>", PerformerType::getStaticProviderName());
			CHECK_EQUAL("ImageByFieldPerformer<Registration<2,3>>", Performer2Type::getStaticProviderName());
			CHECK_EQUAL(PerformerType::getStaticProviderName(), spPerformer->getProviderName());

			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest1), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest3), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest4), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest5), core::ServiceException);

			ResultDataType::Pointer spResultImage;
			CHECK_NO_THROW(spResultImage = spPerformer->performMapping(request));

			//check the registration of the image
			CHECK(spResultImage.IsNotNull());

			lit::ImageTester<ResultDataType, itk::Image<unsigned char, 2> > tester;
			tester.setExpectedImage(spReferenceImage);
			tester.setActualImage(spResultImage);
			tester.setCheckThreshold(checkThreshold);
			tester.setCheckImageGeometry(false);
			tester.setTestFileName(testImageFileName + "_1");
			tester.setSaveTestFiles(true);

			CHECK_TESTER(tester);

			CHECK_NO_THROW(spResultImage = spPerformer->performMapping(request2));

			//check the registration of the image
			CHECK(spResultImage.IsNotNull());

			lit::ImageTester<ResultDataType, itk::Image<unsigned char, 2> > tester2;
			tester2.setExpectedImage(spReferenceImage2);
			tester2.setActualImage(spResultImage);
			tester2.setCheckThreshold(checkThreshold);
			tester2.setCheckImageGeometry(false);
			tester2.setTestFileName(testImageFileName + "_2");
			tester2.setSaveTestFiles(true);

			CHECK_TESTER(tester2);

			CHECK_NO_THROW(spResultImage = spPerformer->performMapping(request3));

			//check the registration of the image
			CHECK(spResultImage.IsNotNull());

			lit::ImageTester<ResultDataType, itk::Image<unsigned char, 2> > tester3;
			tester3.setExpectedImage(spReferenceImage3);
			tester3.setActualImage(spResultImage);
			tester3.setCheckThreshold(checkThreshold);
			tester3.setCheckImageGeometry(false);
			tester3.setTestFileName(testImageFileName + "_3");
			tester3.setSaveTestFiles(true);

			CHECK_TESTER(tester3);

			CHECK_THROW_EXPLICIT(spPerformer->performMapping(request4), core::MappingException);


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
