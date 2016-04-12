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

#include "mapGenericFieldGeneratingCombinationFunctor.h"
#include "mapFieldByModelFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapLazyRegistrationKernel.h"
#include "mapFieldDecomposer.h"

#include "itkIdentityTransform.h"

namespace map
{
	namespace testing
	{


		int mapGenericFieldGeneratingCombinationFunctorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::PreCachedRegistrationKernel<2, 2> PreCachedKernelType;

			PreCachedKernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
			PreCachedKernelType::RepresentationDescriptorType::PointType origin;
			origin.Fill(0);
			PreCachedKernelType::RepresentationDescriptorType::SizeType size;
			size.fill(10);
			PreCachedKernelType::RepresentationDescriptorType::Pointer spInRep =
				PreCachedKernelType::RepresentationDescriptorType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			PreCachedKernelType::RepresentationDescriptorType::PointType illegalOrigin;
			illegalOrigin.Fill(100);
			PreCachedKernelType::RepresentationDescriptorType::Pointer spIllegalInRep =
				PreCachedKernelType::RepresentationDescriptorType::New();
			spIllegalInRep->setSize(size);
			spIllegalInRep->setSpacing(spacing);
			spIllegalInRep->setOrigin(illegalOrigin);

			//Model kernel generation
			typedef ::itk::ScaleTransform< ::map::core::continuous::ScalarType, 2> TransformType;

			PreCachedKernelType::Pointer spModelKernel = PreCachedKernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 0.3;
			params[1] = 0.3;
			spTransform->SetParameters(params);

			//Field kernel (generate by using inverse transform)
			TransformType::InverseTransformBasePointer spInverseTransform =	spTransform->GetInverseTransform();

			spModelKernel->setTransformModel(spTransform);

			typedef core::functors::FieldByModelFunctor<2, 2> FunctorType;
			FunctorType::Pointer spFieldFunctor = FunctorType::New(spInverseTransform, spInRep);
			//uses this functor to generate the test field

			typedef core::LazyRegistrationKernel<2, 2> FieldKernelType;

			FieldKernelType::Pointer spFieldKernel = FieldKernelType::New();

			spFieldKernel->setTransformFunctor(spFieldFunctor);

			//Establish combination functor for test
			typedef core::functors::GenericFieldGeneratingCombinationFunctor<2, 2, 2> CombinatorFunctorType;
			CombinatorFunctorType::Pointer spTestFunctor = CombinatorFunctorType::New(
					spModelKernel, spFieldKernel, spInRep);

			//Test the functor io
			CHECK(spTestFunctor.IsNotNull());

			CHECK(spModelKernel.GetPointer() == spTestFunctor->get1stSourceKernelBase());
			CHECK(spFieldKernel.GetPointer() == spTestFunctor->get2ndSourceKernelBase());

			CombinatorFunctorType::Pointer spFuncAnother = dynamic_cast<CombinatorFunctorType*>
					(spTestFunctor->CreateAnother().GetPointer());
			CHECK(spFuncAnother->get1stSourceKernelBase() == spTestFunctor->get1stSourceKernelBase());
			CHECK(spFuncAnother->get2ndSourceKernelBase() == spTestFunctor->get2ndSourceKernelBase());
			CHECK(spFuncAnother->getInFieldRepresentation() == spTestFunctor->getInFieldRepresentation());
			CHECK(spFuncAnother->GetNameOfClass() == spTestFunctor->GetNameOfClass());


			//Test field generation, hence we've combined a field with its inverse transform model
			//the resulting field must be an identity transform
			CombinatorFunctorType::TransformPointer spResult = NULL;
			CHECK_NO_THROW(spResult = spTestFunctor->generateTransform());
			CHECK(spResult.IsNotNull());

      ::map::core::FieldDecomposer<2, 2>::FieldConstPointer actualField;
      bool validField = ::map::core::FieldDecomposer<2, 2>::decomposeTransform(spResult, actualField);
      CHECK(validField);

      lit::TransformFieldTester< ::map::core::FieldDecomposer<2, 2>::FieldType, PreCachedKernelType::TransformType>
			tester;
			typedef itk::IdentityTransform< ::map::core::continuous::ScalarType, 2> IdentityTransformType;

			IdentityTransformType::Pointer spIdentityTransform = IdentityTransformType::New();

			tester.setReferenceTransform(spIdentityTransform);
      tester.setActualField(actualField);
			tester.setCheckThreshold(1e-6);

			CHECK_TESTER(tester);

			//Test invalid mapping request: In field representation descriptor specifies unsupported region
			CombinatorFunctorType::Pointer spIllegalTestFunctor = CombinatorFunctorType::New(spModelKernel, spFieldKernel, spIllegalInRep);

			CombinatorFunctorType::TransformPointer spIllegalResultFieldTransform = NULL;

      CHECK_THROW_EXPLICIT(spIllegalResultFieldTransform = spIllegalTestFunctor->generateTransform(),
								 core::RepresentationException);

			//now activiate padding to avoid the exception and get a padded field

			spIllegalTestFunctor->setNullPointUsage(true);
			CombinatorFunctorType::PaddingVectorType paddingValue;
			paddingValue.Fill(42);
			spIllegalTestFunctor->setNullPoint(paddingValue);

      CHECK_NO_THROW(spIllegalResultFieldTransform = spIllegalTestFunctor->generateTransform());
			CHECK(spIllegalTestFunctor.IsNotNull());

      validField = ::map::core::FieldDecomposer<2, 2>::decomposeTransform(spIllegalResultFieldTransform, actualField);
      CHECK(validField);

			//check if the padding value was used

      ::map::core::FieldDecomposer<2, 2>::FieldType::IndexType index;
			index.Fill(1);

      CHECK_EQUAL(actualField->GetPixel(index), paddingValue);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
