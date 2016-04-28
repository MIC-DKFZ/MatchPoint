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
// @version $Revision: 1316 $ (last changed revision)
// @date    $Date: 2016-04-13 14:50:09 +0200 (Mi, 13 Apr 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Core/test/mapGenericFieldGeneratingCombinationFunctorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkScaleTransform.h"

#include "litCheckMacros.h"
#include "litTransformFieldTester.h"

#include "mapGenericKernelCombinationFieldSource.h"
#include "mapFieldByModelFunctor.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapLazyRegistrationKernel.h"
#include "mapFieldDecomposer.h"

#include "itkIdentityTransform.h"

namespace map
{
	namespace testing
	{


    int mapGenericKernelCombiningFieldSourceTest(int, char*[])
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
			typedef core::GenericKernelCombinationFieldSource<2, 2, 2, ::map::core::continuous::ScalarType> SourceType;
      SourceType::Pointer spSource = SourceType::New();

      CHECK(NULL == spSource->GetSourceKernel1());
      CHECK(NULL == spSource->GetSourceKernel2());

      spSource->SetSourceKernel1(spModelKernel);
      spSource->SetSourceKernel2(spFieldKernel);

      spSource->SetSize(spInRep->getRepresentedLocalImageRegion().GetSize());
      spSource->SetOrigin(spInRep->getOrigin());
      spSource->SetSpacing(spInRep->getSpacing());
      spSource->SetDirection(spInRep->getDirection());

			//Test the functor io
      CHECK(spSource.IsNotNull());

      CHECK(spModelKernel.GetPointer() == spSource->GetSourceKernel1());
      CHECK(spFieldKernel.GetPointer() == spSource->GetSourceKernel2());

			//Test field generation, hence we've combined a field with its inverse transform model
			//the resulting field must be an identity transform
      SourceType::OutputImageType::Pointer spResult = NULL;

			CHECK_NO_THROW(spSource->Update());
      spResult = spSource->GetOutput();
			CHECK(spResult.IsNotNull());

      lit::TransformFieldTester< SourceType::OutputImageType, PreCachedKernelType::TransformType>
			tester;
			typedef itk::IdentityTransform< ::map::core::continuous::ScalarType, 2> IdentityTransformType;

			IdentityTransformType::Pointer spIdentityTransform = IdentityTransformType::New();

			tester.setReferenceTransform(spIdentityTransform);
      tester.setActualField(spResult);
			tester.setCheckThreshold(1e-6);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
