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

#include "itkScaleTransform.h"
#include "itkIdentityTransform.h"

#include "mapFieldByFieldFieldCombinationFunctor.h"
#include "mapFieldByModelFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"
#include "mapFieldBasedRegistrationKernels.h"

namespace map
{
	namespace testing
	{


		int mapFieldByFieldFieldCombinationFunctorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel FieldKernelType;

			// create representation descriptors spInRep, spIllegalInRep, spOutRep
			FieldKernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
			FieldKernelType::RepresentationDescriptorType::PointType origin;
			origin.Fill(0);
			FieldKernelType::RepresentationDescriptorType::SizeType size;
			size.fill(10);
			FieldKernelType::RepresentationDescriptorType::Pointer spInRep =
				FieldKernelType::RepresentationDescriptorType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			FieldKernelType::RepresentationDescriptorType::PointType illegalOrigin;
			illegalOrigin.Fill(100);
			FieldKernelType::RepresentationDescriptorType::Pointer spIllegalInRep =
				FieldKernelType::RepresentationDescriptorType::New();
			spIllegalInRep->setSize(size);
			spIllegalInRep->setSpacing(spacing);
			spIllegalInRep->setOrigin(illegalOrigin);

			//Setting up transform and inverse
			typedef itk::ScaleTransform<::map::core::continuous::ScalarType, 2> TransformType;

			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 0.3;
			params[1] = 0.3;
			spTransform->SetParameters(params);

			TransformType::InverseTransformBasePointer spInverseTransform = spTransform->GetInverseTransform();

			typedef core::functors::FieldByModelFunctor<2, 2> FunctorType;

			FunctorType::Pointer spFieldFunctor1 = FunctorType::New(*spTransform, spInRep);
			FunctorType::Pointer spFieldFunctor2 = FunctorType::New(*spInverseTransform, spInRep);

			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel FieldKernel1Type;
			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel FieldKernel2Type;

			//Field kernel 1 (generate by using transform)
			//uses this functor to generate the test field
			FunctorType::FieldPointer spField1 = spFieldFunctor1->generateField();
			//Field kernel 2 (generate by using inverse transform)
			//uses this functor to generate the test field
			FunctorType::FieldPointer spField2 = spFieldFunctor2->generateField();

			FieldKernel1Type::Pointer spFieldKernel1 = FieldKernel1Type::New();
			spFieldKernel1->setField(*(spField1.GetPointer()));

			FieldKernel2Type::Pointer spFieldKernel2 = FieldKernel2Type::New();
			spFieldKernel2->setField(*(spField2.GetPointer()));

			//Establish combination functor for test
			typedef core::functors::FieldByFieldFieldCombinationFunctor<2, 2, 2> CombinatorFunctorType;
			CombinatorFunctorType::Pointer spTestFunctor = CombinatorFunctorType::New(*
					(spFieldKernel1.GetPointer()), *(spFieldKernel2.GetPointer()), spInRep);

			//Test the functor io
			CHECK(spTestFunctor.IsNotNull());

			CHECK(spFieldKernel1 == spTestFunctor->get1stSourceFieldKernel());
			CHECK(spFieldKernel2 == spTestFunctor->get2ndSourceFieldKernel());
			CHECK(spFieldKernel1.GetPointer() == spTestFunctor->get1stSourceKernelBase());
			CHECK(spFieldKernel2.GetPointer() == spTestFunctor->get2ndSourceKernelBase());

			CombinatorFunctorType::Pointer spFuncAnother = dynamic_cast<CombinatorFunctorType*>
					(spTestFunctor->CreateAnother().GetPointer());
			CHECK(spFuncAnother->get1stSourceFieldKernel() == spTestFunctor->get1stSourceFieldKernel());
			CHECK(spFuncAnother->get2ndSourceFieldKernel() == spTestFunctor->get2ndSourceFieldKernel());
			CHECK(spFuncAnother->getInFieldRepresentation() == spTestFunctor->getInFieldRepresentation());
			CHECK(spFuncAnother->GetNameOfClass() == spTestFunctor->GetNameOfClass());


			//Test field generation, hence we've combined a field with its inverse transform model
			//the resulting field must be an identity transform
			CombinatorFunctorType::FieldPointer spResultField = NULL;
			CHECK_NO_THROW(spResultField = spTestFunctor->generateField());
			CHECK(spResultField.IsNotNull());

			typedef itk::IdentityTransform<::map::core::continuous::ScalarType, 2> IdentityTransformType;
			lit::TransformFieldTester<CombinatorFunctorType::FieldType, IdentityTransformType> tester;

			IdentityTransformType::Pointer spIdentityTransform = IdentityTransformType::New();

			tester.setReferenceTransform(spIdentityTransform);
			tester.setActualField(spResultField);
			tester.setCheckThreshold(1e-6);

			CHECK_TESTER(tester);

			//Test invalid mapping request: In field representation descriptor specifies unsupported region
			CombinatorFunctorType::Pointer spIllegalTestFunctor = CombinatorFunctorType::New(*
					(spFieldKernel1.GetPointer()), *(spFieldKernel2.GetPointer()), spIllegalInRep);

			CombinatorFunctorType::FieldPointer spIllegalResultField = NULL;

			CHECK_THROW_EXPLICIT(spIllegalResultField = spIllegalTestFunctor->generateField(),
								 core::RepresentationException);

			//now activiate padding to avoid the exception and get a padded field

			spIllegalTestFunctor->setUsePadding(true);
			CombinatorFunctorType::PaddingVectorType paddingValue;
			paddingValue.Fill(42);
			spIllegalTestFunctor->setPaddingVector(paddingValue);

			CHECK_NO_THROW(spIllegalResultField = spIllegalTestFunctor->generateField());
			CHECK(spIllegalTestFunctor.IsNotNull());

			//check if the padding value was used

			FieldKernelType::FieldType::IndexType index;
			index.Fill(1);

			CHECK_EQUAL(spIllegalResultField->GetPixel(index), paddingValue);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
