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

#include "mapPointSetByModelPerformer.h"
#include "mapRegistration.h"
#include "mapRegistrationManipulator.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapTestKernelBase.h"
#include "mapITKTranslationTransform.h"

#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		int mapPointSetByModelPerformerTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			typedef core::Registration<2, 3> Registration2Type;
			typedef core::continuous::Elements<2>::InternalPointSetType InputDataType;
			typedef core::continuous::Elements<2>::InternalPointSetType ResultDataType;
			typedef core::continuous::Elements<3>::InternalPointSetType ResultData2Type;
			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;
			typedef TestKernelBase<2, 2> IllegalKernelType;

			typedef core::PointSetByModelPerformer<RegistrationType, InputDataType, ResultDataType>
			PerformerType;
			typedef core::PointSetByModelPerformer<Registration2Type, InputDataType, ResultData2Type>
			Performer2Type;

			//Now we create the kernels
			ModelKernelType::Pointer spKernel = ModelKernelType::New();
			IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();
			ModelKernelType::Pointer spIllegalModelKernel = ModelKernelType::New(); //has no transform model

			//setting up model kernel
			typedef ::itk::TranslationTransform<core::continuous::ScalarType, 2> TransformType;

			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 5;
			params[1] = -5;
			spTransform->SetParameters(params);

			spKernel->setTransformModel(spTransform);

			//creating registrations
			RegistrationType::Pointer spRegistration = RegistrationType::New();
			RegistrationType::Pointer spIllegalRegistration1 = RegistrationType::New();
			RegistrationType::Pointer spIllegalRegistration2 = RegistrationType::New();

			core::RegistrationManipulator<RegistrationType> manipulator1(spRegistration);
			manipulator1.setDirectMapping(spKernel);
			manipulator1.setInverseMapping(spIllegalKernel);

			core::RegistrationManipulator<RegistrationType> manipulator2(spIllegalRegistration1);
			manipulator2.setDirectMapping(spIllegalKernel);
			manipulator2.setInverseMapping(spIllegalKernel);

			core::RegistrationManipulator<RegistrationType> manipulator3(spIllegalRegistration2);
			manipulator3.setDirectMapping(spIllegalModelKernel);
			manipulator3.setInverseMapping(spIllegalKernel);

			//create input data
			InputDataType::PointType point;
			point[0] = 3.0;
			point[1] = -7.0;

			InputDataType::Pointer spInputSet = InputDataType::New();
			spInputSet->SetPoint(0, point);
			spInputSet->SetPoint(1, point);
			spInputSet->SetPointData(1, 42);

			//Create requests
			// valid request
			PerformerType::RequestType request(spRegistration.GetPointer(), spInputSet.GetPointer(), true, 0);
			// illegal request
			PerformerType::RequestType illegalRequest1(spRegistration.GetPointer(), spInputSet.GetPointer(),
					true, 0);
			illegalRequest1._spInputData = NULL;
			// illegal request: field, field
			PerformerType::RequestType illegalRequest2(spIllegalRegistration1.GetPointer(),
					spInputSet.GetPointer(), true, 0);
			// illegal request: field, field
			PerformerType::RequestType illegalRequest3(spIllegalRegistration2.GetPointer(),
					spInputSet.GetPointer(), true, 0);

			//creating the combinator
			PerformerType::Pointer spPerformer = PerformerType::New();

			//TEST
			CHECK_EQUAL(false, spPerformer->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(false, spPerformer->canHandleRequest(illegalRequest2));
			CHECK_EQUAL(true, spPerformer->canHandleRequest(
							illegalRequest3)); //is illegal because the model kernel is invalid, but theoretically it can be handled by the performer
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request));

			CHECK_EQUAL("PointSetByModelPerformer<Registration<2,2>>", PerformerType::getStaticProviderName());
			CHECK_EQUAL("PointSetByModelPerformer<Registration<2,3>>", Performer2Type::getStaticProviderName());
			CHECK_EQUAL(PerformerType::getStaticProviderName(), spPerformer->getProviderName());

			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest1), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest3), core::ServiceException);

			ResultDataType::Pointer spResultSet;
			CHECK_NO_THROW(spResultSet = spPerformer->performMapping(request));

			//check the registration of the point set
			ResultDataType::PointType referencePoint;
			ResultDataType::PixelType referencePointData = 42;
			referencePoint[0] = 8.0;
			referencePoint[1] = -12.0;
			ResultDataType::PointType resultPoint;
			ResultDataType::PixelType resultPointData;

			CHECK(spResultSet.IsNotNull());
			CHECK(spResultSet->GetPoints()->Size() == 2);
			CHECK(spResultSet->GetPoint(0, &resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);
			CHECK(spResultSet->GetPoint(1, &resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);
			CHECK(spResultSet->GetPointData(1, &resultPointData));
			CHECK_EQUAL(referencePointData, resultPointData);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
