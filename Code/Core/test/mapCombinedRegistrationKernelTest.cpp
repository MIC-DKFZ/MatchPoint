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

#include "mapCombinedRegistrationKernel.h"
#include "mapGenericFieldGeneratingCombinationFunctor.h"
#include "mapFieldByModelFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"
#include "mapLazyRegistrationKernel.h"
#include "mapPreCachedRegistrationKernel.h"

#include "itkScaleTransform.h"

namespace map
{
	namespace testing
	{

		typedef core::functors::GenericFieldGeneratingCombinationFunctor<2, 2, 2> CombinatorFunctorType;
		typedef core::CombinedRegistrationKernel<2, 2, 2> KernelType;

		void generateKernel(KernelType::Pointer& spKernel, CombinatorFunctorType::Pointer& spFunctor)
		{
			typedef core::PreCachedRegistrationKernel<2, 2> ModelKernelType;

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
			typedef itk::ScaleTransform< ::map::core::continuous::ScalarType, 2> TransformType;

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
			FunctorType::Pointer spFieldFunctor = FunctorType::New(spInverseTransform, spInRep);
      spFieldFunctor->setNullPointUsage(true);
      //uses this functor to generate the test field

			typedef core::LazyRegistrationKernel<2, 2> FieldKernelType;

			FieldKernelType::Pointer spFieldKernel = FieldKernelType::New();

			spFieldKernel->setTransformFunctor(spFieldFunctor);

			//Establish combination functor for test
			spFunctor = CombinatorFunctorType::New(spModelKernel, spFieldKernel, spInRep);
      spFunctor->setNullPointUsage(true);
			spKernel = KernelType::New();
			spKernel->setTransformFunctor(spFunctor);
		}

		int mapCombinedRegistrationKernelTest(int, char* [])
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
			CHECK(!(spKernel->transformExists())); //if field exists, the kernel has illegally created the field
			//instead of just passing through the representation
			/// #2
			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_ARRAY_CLOSE(referencePoint, resultPoint, 2, 1e-5);
      CHECK(!(spKernel->transformExists())); //if field exists, the kernel has illegally created the field
			//instead of just using the source kernels for point mapping.
			resultPoint.Fill(11);
			CHECK_EQUAL(false, spKernel->mapPoint(invalidInPoint, resultPoint));
			CHECK_EQUAL(invalidReferencePoint, resultPoint);
      CHECK(!(spKernel->transformExists())); //if field exists, the kernel has illegally created the field
			//instead of just using the source kernels for point mapping.

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
