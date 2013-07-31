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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapPointSetByFieldPerformerTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapPointSetByFieldPerformer.h"
#include "mapRegistration.h"
#include "mapRegistrationManipulator.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapTestKernelBase.h"
#include "mapServiceException.h"

#include "litCheckMacros.h"

#include "itkImage.h"

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

				FieldKernelType::FieldType::RegionType::SizeType size = {30, 30};
				FieldKernelType::FieldType::RegionType region(size);
				FieldKernelType::FieldType::SpacingType spacing(0.5);
				//Generate imagegrid
				spField->SetRegions(region);
				spField->SetSpacing(spacing);
				spField->Allocate();

				FieldKernelType::FieldType::ValueType value;
				value[0] = 5;
				value[1] = -5;

				spField->FillBuffer(value);

				return spField;
			}
		}

		int mapPointSetByFieldPerformerTest(int argc, char *argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			typedef core::Registration<2, 3> Registration2Type;
			typedef core::continuous::Elements<2>::InternalPointSetType InputDataType;
			typedef core::continuous::Elements<2>::InternalPointSetType ResultDataType;
			typedef core::continuous::Elements<3>::InternalPointSetType ResultData2Type;
			typedef TestKernelBase<2, 2> IllegalKernelType;

			typedef core::PointSetByFieldPerformer<RegistrationType, InputDataType, ResultDataType> PerformerType;
			typedef core::PointSetByFieldPerformer<Registration2Type, InputDataType, ResultData2Type> Performer2Type;

			//Now we create the kernels
			FieldKernelType::Pointer spKernel = FieldKernelType::New();
			IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();

			spKernel->setField(*(generateField().GetPointer()));

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

			//create input data
			InputDataType::PointType point;
			point[0] = 3.0;
			point[1] = 7.0;

			InputDataType::PointType illegalPoint;
			illegalPoint[0] = 50.0;
			illegalPoint[1] = 60.0;


			InputDataType::Pointer spInputSet = InputDataType::New();
			spInputSet->SetPoint(0, point);
			spInputSet->SetPoint(1, point);
			spInputSet->SetPointData(1, 42);
			spInputSet->SetPoint(2, illegalPoint);
			spInputSet->SetPoint(3, point);

			//Create requests
			// valid request
			PerformerType::RequestType request(spRegistration.GetPointer(), spInputSet.GetPointer(), true, 0);
			// valid request 2 (no exception, mark point)
			PerformerType::RequestType request2(spRegistration.GetPointer(), spInputSet.GetPointer(), false, -1);
			// illegal request
			PerformerType::RequestType illegalRequest1(spRegistration.GetPointer(), spInputSet.GetPointer(), true, 0);
			illegalRequest1._spInputData = NULL;
			// illegal request: field, field
			PerformerType::RequestType illegalRequest2(spIllegalRegistration1.GetPointer(), spInputSet.GetPointer(), true, 0);

			//creating the combinator
			PerformerType::Pointer spPerformer = PerformerType::New();

			//TEST
			CHECK_EQUAL(false, spPerformer->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(false, spPerformer->canHandleRequest(illegalRequest2));
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request));
			CHECK_EQUAL(true, spPerformer->canHandleRequest(request2));

			CHECK_EQUAL("PointSetByFieldPerformer<Registration<2,2>>", PerformerType::getStaticProviderName());
			CHECK_EQUAL("PointSetByFieldPerformer<Registration<2,3>>", Performer2Type::getStaticProviderName());
			CHECK_EQUAL(PerformerType::getStaticProviderName(), spPerformer->getProviderName());

			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest1), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(illegalRequest2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spPerformer->performMapping(request), core::MappingException);

			ResultDataType::Pointer spResultSet;
			ResultDataType::PointType referencePoint;
			ResultDataType::PixelType referencePointData = 42;
			ResultDataType::PixelType errorReferencePointData = -1;
			referencePoint[0] = 8.0;
			referencePoint[1] = 2.0;
			ResultDataType::PointType resultPoint;
			ResultDataType::PixelType resultPointData;

			//check the registration of the point set
			CHECK_NO_THROW(spResultSet = spPerformer->performMapping(request2));

			CHECK(spResultSet.IsNotNull());
			CHECK_EQUAL(4, spResultSet->GetPoints()->Size());

			CHECK(spResultSet->GetPoint(0, &resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);

			CHECK(spResultSet->GetPoint(1, &resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);
			CHECK(spResultSet->GetPointData(1, &resultPointData));
			CHECK_EQUAL(referencePointData, resultPointData);

			CHECK(spResultSet->GetPoint(2, &resultPoint));
			CHECK_EQUAL(illegalPoint, resultPoint);
			CHECK(spResultSet->GetPointData(2, &resultPointData));
			CHECK_EQUAL(errorReferencePointData, resultPointData);

			CHECK(spResultSet->GetPoint(3, &resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
