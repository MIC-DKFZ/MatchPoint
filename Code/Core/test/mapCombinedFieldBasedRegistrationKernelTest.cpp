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

#include "mapCombinedFieldBasedRegistrationKernel.h"
#include "mapFieldByModelFieldCombinationFunctor.h"
#include "mapFieldByModelFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"
#include "mapFieldBasedRegistrationKernels.h"

#include "itkScaleTransform.h"

namespace map
{
	namespace testing
	{

		typedef core::functors::FieldByModelFieldCombinationFunctor<2, 2, 2> CombinatorFunctorType;
		typedef core::CombinedFieldBasedRegistrationKernel<2, 2, 2> KernelType;

		void generateKernel(KernelType::Pointer& spKernel, CombinatorFunctorType::Pointer& spFunctor)
		{
			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;

			ModelKernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
			ModelKernelType::RepresentationDescriptorType::PointType origin;
			origin.Fill(0);
			ModelKernelType::RepresentationDescriptorType::SizeType size;
			size.fill(10);
			ModelKernelType::RepresentationDescriptorType::Pointer spInRep =
				ModelKernelType::RepresentationDescriptorType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			//Model kernel generation
			typedef itk::ScaleTransform<::map::core::continuous::ScalarType, 2> TransformType;

			ModelKernelType::Pointer spModelKernel = ModelKernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 0.3;
			params[1] = 0.3;
			spTransform->SetParameters(params);

			spModelKernel->setTransformModel(spTransform);

			//Field kernel (generate by using inverse transform)
			TransformType::InverseTransformBasePointer spInverseTransform =	spTransform->GetInverseTransform();

			typedef core::functors::FieldByModelFunctor<2, 2> FunctorType;
			FunctorType::Pointer spFieldFunctor = FunctorType::New(*spInverseTransform, spInRep);
			//uses this functor to generate the test field
			FunctorType::FieldPointer spField = spFieldFunctor->generateField();

			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel FieldKernelType;

			FieldKernelType::Pointer spFieldKernel = FieldKernelType::New();

			spFieldKernel->setField(*(spField.GetPointer()));

			//Establish combination functor for test
			spFunctor = CombinatorFunctorType::New(*(spModelKernel.GetPointer()), *(spFieldKernel.GetPointer()),
												   spInRep);

			spKernel = KernelType::New();
			spKernel->setFieldFunctor(*(spFunctor.GetPointer()));
		}

		int mapCombinedFieldBasedRegistrationKernelTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			KernelType::Pointer spKernel;
			CombinatorFunctorType::Pointer spFunctor;
			generateKernel(spKernel, spFunctor);

			KernelType::InputPointType inPoint;
			inPoint.Fill(3);
			KernelType::OutputPointType referencePoint;
			referencePoint.Fill(3);

			KernelType::InputPointType invalidInPoint;
			invalidInPoint.Fill(50);
			KernelType::OutputPointType invalidReferencePoint;
			invalidReferencePoint.Fill(0.0);

			KernelType::OutputPointType resultPoint;

			//TESTS #1
			KernelType::RepresentationDescriptorConstPointer spKernelRep =
				spKernel->getLargestPossibleRepresentation();
			CHECK(!(spKernel->fieldExists())); //if field exists, the kernel has illegally created the field
			//instead of just passing through the representation
			/// #2
			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_ARRAY_CLOSE(referencePoint, resultPoint, 2, 1e-5);
			CHECK(!(spKernel->fieldExists())); //if field exists, the kernel has illegally created the field
			//instead of just using the source kernels for point mapping.
			resultPoint.Fill(11);
			CHECK_EQUAL(false, spKernel->mapPoint(invalidInPoint, resultPoint));
			CHECK_EQUAL(invalidReferencePoint, resultPoint);
			CHECK(!(spKernel->fieldExists())); //if field exists, the kernel has illegally created the field
			//instead of just using the source kernels for point mapping.

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
