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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapFieldByModelFieldCombinationFunctorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapFieldByModelFieldCombinationFunctor.h"
#include "mapFieldByModelFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"
#include "mapFieldBasedRegistrationKernels.h"

#include "mapITKScaleTransform.h"

#include "itkIdentityTransform.h"

namespace map
{
	namespace testing
	{


		int mapFieldByModelFieldCombinationFunctorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;

			ModelKernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
			ModelKernelType::RepresentationDescriptorType::PointType origin;
			origin.Fill(0);
			ModelKernelType::RepresentationDescriptorType::SizeType size;
			size.fill(10);
			ModelKernelType::RepresentationDescriptorType::Pointer spInRep = ModelKernelType::RepresentationDescriptorType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			ModelKernelType::RepresentationDescriptorType::PointType illegalOrigin;
			illegalOrigin.Fill(100);
			ModelKernelType::RepresentationDescriptorType::Pointer spIllegalInRep = ModelKernelType::RepresentationDescriptorType::New();
			spIllegalInRep->setSize(size);
			spIllegalInRep->setSpacing(spacing);
			spIllegalInRep->setOrigin(illegalOrigin);

			//Model kernel generation
			typedef algorithm::itk::ITKTransformModel< itk::ScaleTransform<core::continuous::ScalarType, 2> > TransformType;

			ModelKernelType::Pointer spModelKernel = ModelKernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 0.3;
			params[1] = 0.3;
			spTransform->getTransform()->SetParameters(params);

			//Field kernel (generate by using inverse transform)
			TransformType::InverseTransformModelBasePointer spInverseTransform;
			spTransform->getInverse(spInverseTransform);

			spModelKernel->setTransformModel(spTransform);

			typedef core::functors::FieldByModelFunctor<2, 2> FunctorType;
			FunctorType::Pointer spFieldFunctor = FunctorType::New(*spInverseTransform, spInRep);
			//uses this functor to generate the test field
			FunctorType::FieldPointer spField = spFieldFunctor->generateField();

			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel FieldKernelType;

			FieldKernelType::Pointer spFieldKernel = FieldKernelType::New();

			spFieldKernel->setField(*(spField.GetPointer()));

			//Establish combination functor for test
			typedef core::functors::FieldByModelFieldCombinationFunctor<2, 2, 2> CombinatorFunctorType;
			CombinatorFunctorType::Pointer spTestFunctor = CombinatorFunctorType::New(*(spModelKernel.GetPointer()), *(spFieldKernel.GetPointer()), spInRep);


			//Test the functor io
			CHECK(spTestFunctor.IsNotNull());

			CHECK(spFieldKernel == spTestFunctor->getSourceFieldKernel());
			CHECK(spModelKernel == spTestFunctor->getSourceModelKernel());
			CHECK(spModelKernel.GetPointer() == spTestFunctor->get1stSourceKernelBase());
			CHECK(spFieldKernel.GetPointer() == spTestFunctor->get2ndSourceKernelBase());

			CombinatorFunctorType::Pointer spFuncAnother = dynamic_cast<CombinatorFunctorType *>(spTestFunctor->CreateAnother().GetPointer());
			CHECK(spFuncAnother->getSourceFieldKernel() == spTestFunctor->getSourceFieldKernel());
			CHECK(spFuncAnother->getSourceModelKernel() == spTestFunctor->getSourceModelKernel());
			CHECK(spFuncAnother->getInFieldRepresentation() == spTestFunctor->getInFieldRepresentation());
			CHECK(spFuncAnother->GetNameOfClass() == spTestFunctor->GetNameOfClass());


			//Test field generation, hence we've combined a field with its inverse transform model
			//the resulting field must be an identity transform
			CombinatorFunctorType::FieldPointer spResultField = NULL;
			CHECK_NO_THROW(spResultField = spTestFunctor->generateField());
			CHECK(spResultField.IsNotNull());

			lit::TransformFieldTester<CombinatorFunctorType::FieldType, ModelKernelType::TransformType::TransformBaseType> tester;
			typedef itk::IdentityTransform<core::continuous::ScalarType, 2> IdentityTransformType;

			IdentityTransformType::Pointer spIdentityTransform = IdentityTransformType::New();

			tester.setReferenceTransform(spIdentityTransform);
			tester.setActualField(spResultField);
			tester.setCheckThreshold(1e-6);

			CHECK_TESTER(tester);

			//Test invalid mapping request: In field representation descriptor specifies unsupported region
			typedef core::functors::FieldByModelFieldCombinationFunctor<2, 2, 2> CombinatorFunctorType;
			CombinatorFunctorType::Pointer spIllegalTestFunctor = CombinatorFunctorType::New(*(spModelKernel.GetPointer()), *(spFieldKernel.GetPointer()), spIllegalInRep);

			CombinatorFunctorType::FieldPointer spIllegalResultField = NULL;

			CHECK_THROW_EXPLICIT(spIllegalResultField = spIllegalTestFunctor->generateField(), core::RepresentationException);

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
