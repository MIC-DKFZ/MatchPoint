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

#include "mapPreCachedRegistrationKernel.h"
#include "mapArtifactGenerator.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"

namespace map
{
	namespace testing
	{

		int mapRegistrationKernelTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::PreCachedRegistrationKernel<2, 2> KernelType;

			KernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
			KernelType::RepresentationDescriptorType::PointType origin;
			origin.Fill(0);
			KernelType::RepresentationDescriptorType::SizeType size;
			size.fill(5);
			KernelType::RepresentationDescriptorType::Pointer spInRep =
				KernelType::RepresentationDescriptorType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

      KernelType::OutputVectorType nullVector(-100000000);
      KernelType::OutputPointType nullVectorAsPoint(-100000000);
      KernelType::OutputPointType defaultNullPoint(
          ::itk::NumericTraits<KernelType::OutputPointType::ValueType>::NonpositiveMin());

			KernelType::Pointer spKernel = KernelType::New();

      typedef ::itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, 2, 2> FieldTransformType;
      FieldTransformType::Pointer transformModel = testing::wrapFieldInTransform<2>(generate2DScaleFieldWithNull(createSimpleDescriptor<2>(10, 0.5), nullVector).GetPointer());
      spKernel->setTransformModel(transformModel);

      typedef ::itk::map::NULLVectorAwareLinearInterpolateImageFunction < FieldTransformType::GenericVectorFieldType, FieldTransformType::ScalarType> InterpolatorType;
      InterpolatorType::Pointer interpolator = InterpolatorType::New();
      transformModel->SetInterpolator(interpolator);

			KernelType::InputPointType inPoint;
			inPoint.Fill(3);
			KernelType::OutputPointType referencePoint;
			referencePoint[0] = 0.9;
			referencePoint[1] = 1.2;

			KernelType::InputPointType invalidInPoint;
			invalidInPoint.Fill(50);
			KernelType::OutputPointType invalidReferencePoint;
			invalidReferencePoint.Fill(0.0);

			KernelType::InputPointType nullPoint;
			nullPoint.Fill(0.5);
			KernelType::OutputPointType nullReferencePoint;
			nullReferencePoint[0] = -99999999.5;
			nullReferencePoint[1] = -99999999.5;

			KernelType::InputPointType closeNullPoint;
			closeNullPoint.Fill(0.7);
			KernelType::OutputPointType closeNullReferencePoint;
			closeNullReferencePoint[0] = 0.21;
			closeNullReferencePoint[1] = 0.28;


			KernelType::OutputPointType resultPoint;


			//check defaults
			CHECK_EQUAL(false, spKernel->usesNullPoint());
			CHECK_EQUAL(defaultNullPoint, spKernel->getNullPoint());

			//check the null vector aware implementation of map point

			//1st without Null vector awarenes
      transformModel->SetUseNullPoint(false);
      
      resultPoint.Fill(0);
      CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_ARRAY_CLOSE(referencePoint, resultPoint, 2, 1e-5);

			resultPoint.Fill(11);
			CHECK_EQUAL(true, spKernel->mapPoint(invalidInPoint, resultPoint));
      CHECK_EQUAL(invalidInPoint, resultPoint);

			resultPoint.Fill(11);
			CHECK_EQUAL(true, spKernel->mapPoint(nullPoint, resultPoint));
			CHECK_ARRAY_CLOSE(nullReferencePoint, resultPoint, 2, 1e-5);

			resultPoint.Fill(11);
			CHECK_EQUAL(true, spKernel->mapPoint(closeNullPoint, resultPoint));

			//2nd with Null vector awarenes
      transformModel->SetUseNullPoint(true);
      interpolator->SetNullVectorUsage(true);

      CHECK_EQUAL(true, spKernel->usesNullPoint());

			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_ARRAY_CLOSE(referencePoint, resultPoint, 2, 1e-5);

			resultPoint.Fill(11);
			CHECK_EQUAL(false, spKernel->mapPoint(invalidInPoint, resultPoint));
			CHECK_EQUAL(invalidReferencePoint, resultPoint);

			resultPoint.Fill(11);
      CHECK_EQUAL(true, spKernel->mapPoint(nullPoint, resultPoint));
      CHECK_ARRAY_CLOSE(nullReferencePoint, resultPoint, 2, 1e-5);

			resultPoint.Fill(11);
			CHECK_EQUAL(true, spKernel->mapPoint(closeNullPoint, resultPoint));

			//3rd with Null vector awarenes (other null vector)
      transformModel->SetNullPoint(nullVectorAsPoint);
      interpolator->SetNullVector(nullVector);

      CHECK_EQUAL(nullVectorAsPoint, spKernel->getNullPoint());

			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_ARRAY_CLOSE(referencePoint, resultPoint, 2, 1e-5);

			resultPoint.Fill(11);
			CHECK_EQUAL(false, spKernel->mapPoint(invalidInPoint, resultPoint));
			CHECK_EQUAL(invalidReferencePoint, resultPoint);

			resultPoint.Fill(11);
      CHECK_EQUAL(false, spKernel->mapPoint(nullPoint, resultPoint));
      CHECK_EQUAL(invalidReferencePoint, resultPoint);

			resultPoint.Fill(11);
			CHECK_EQUAL(false, spKernel->mapPoint(closeNullPoint, resultPoint));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
