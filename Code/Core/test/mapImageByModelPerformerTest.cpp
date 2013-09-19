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

#include "mapImageByModelPerformer.h"
#include "mapRegistration.h"
#include "mapRegistrationManipulator.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapTestKernelBase.h"
#include "mapITKTranslationTransform.h"

#include "litCheckMacros.h"
#include "litImageTester.h"

#include "itkLinearInterpolateImageFunction.h"

namespace map
{
	namespace testing
	{

		int mapImageByModelPerformerTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: input image
			//           2: reference image
			//           3: Check threshold
			//           4: test output file name pattern

			PREPARE_DEFAULT_TEST_REPORTING;

			double checkThreshold = 0.1;
			std::string inputImageFileName = "";
			std::string referenceImageFileName = "";
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
				std::istringstream istream;
				istream.str(argv[3]);
				istream >> checkThreshold;
			}

			if (argc > 4)
			{
				testImageFileName = argv[4];
			}

			typedef core::Registration<2, 2> RegistrationType;
			typedef core::Registration<2, 3> Registration2Type;
			typedef core::discrete::Elements<2>::InternalImageType InputDataType;
			typedef core::discrete::Elements<2>::InternalImageType ResultDataType;
			typedef core::discrete::Elements<3>::InternalImageType ResultData2Type;
			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;
			typedef TestKernelBase<2, 2> IllegalKernelType;

			typedef core::ImageByModelPerformer<RegistrationType, InputDataType, ResultDataType> PerformerType;
			typedef core::ImageByModelPerformer<Registration2Type, InputDataType, ResultData2Type>
			Performer2Type;

			//Now we create the kernels
			ModelKernelType::Pointer spKernel = ModelKernelType::New();
			IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();
			ModelKernelType::Pointer spIllegalModelKernel = ModelKernelType::New(); //has no transform model

			//setting up model kernel
			typedef algorithm::itk::ITKTransformModel< itk::TranslationTransform<core::continuous::ScalarType, 2> >
			TransformType;

			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = -15;
			params[1] = -10;
			spTransform->getTransform()->SetParameters(params);

			spKernel->setTransformModel(spTransform);

			//creating registrations
			RegistrationType::Pointer spRegistration = RegistrationType::New();
			RegistrationType::Pointer spIllegalRegistration1 = RegistrationType::New();
			RegistrationType::Pointer spIllegalRegistration2 = RegistrationType::New();

			core::RegistrationManipulator<RegistrationType> manipulator1(spRegistration);
			manipulator1.setDirectMapping(spIllegalKernel);
			manipulator1.setInverseMapping(spKernel);

			core::RegistrationManipulator<RegistrationType> manipulator2(spIllegalRegistration1);
			manipulator2.setDirectMapping(spIllegalKernel);
			manipulator2.setInverseMapping(spIllegalKernel);

			core::RegistrationManipulator<RegistrationType> manipulator3(spIllegalRegistration2);
			manipulator3.setDirectMapping(spIllegalKernel);
			manipulator3.setInverseMapping(spIllegalModelKernel);

			//load input and reference data

			InputDataType::Pointer spInputImage =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					inputImageFileName);
			ResultDataType::Pointer spReferenceImage =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					referenceImageFileName);

			PerformerType::RequestType::ResultImageDescriptorType::Pointer spFieldRep =
				core::createFieldRepresentation(*spInputImage);

			typedef itk::LinearInterpolateImageFunction<InputDataType, core::continuous::ScalarType>
			InterpolatorType;
			InterpolatorType::Pointer spInterpolator = InterpolatorType::New();

			//Create requests
			// valid request
			PerformerType::RequestType request(spRegistration.GetPointer(), spInputImage.GetPointer(),
											   spFieldRep.GetPointer(), spInterpolator, true, 0, false, 0);
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
			// illegal request
			PerformerType::RequestType illegalRequest5(spIllegalRegistration2.GetPointer(),
					spInputImage.GetPointer(), spFieldRep.GetPointer(), spInterpolator, true, 0, false, 0);
			// "illegal request" as long there is no implementation that supports exception throwing in the case of mapping outside of the input image
			PerformerType::RequestType illegalRequest6(spRegistration.GetPointer(), spInputImage.GetPointer(),
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
							illegalRequest5)); //is illegal because the model kernel is invalid, but theoretically it can be handled by the performer
			CHECK_EQUAL(true, spPerformer->canHandleRequest(
							illegalRequest6)); //is illegal because parts are not implemented yet (see performer documentation), but theoretically it can be handled by the performer
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request));

			CHECK_EQUAL("ImageByModelPerformer<Registration<2,2>>", PerformerType::getStaticProviderName());
			CHECK_EQUAL("ImageByModelPerformer<Registration<2,3>>", Performer2Type::getStaticProviderName());
			CHECK_EQUAL(PerformerType::getStaticProviderName(), spPerformer->getProviderName());

			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest1), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest3), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest4), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest5), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest6), core::ServiceException);

			ResultDataType::Pointer spResultImage;
			CHECK_NO_THROW(spResultImage = spPerformer->performMapping(request));

			//check the registration of the image
			CHECK(spResultImage.IsNotNull());

			lit::ImageTester<ResultDataType, itk::Image<unsigned char, 2> > tester;
			tester.setExpectedImage(spReferenceImage);
			tester.setActualImage(spResultImage);
			tester.setCheckThreshold(checkThreshold);
			tester.setTestFileName(testImageFileName);
			tester.setSaveTestFiles(true);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
