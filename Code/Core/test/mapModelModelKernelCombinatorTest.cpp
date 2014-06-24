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

#include "mapModelModelKernelCombinator.h"
#include "mapFieldByFieldModelCombinationFunctor.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapFieldBasedRegistrationKernels.h"

#include "mapITKTranslationTransform.h"
#include "mapITKEuler2DTransform.h"

#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

    map::algorithm::itk::ITKTransformModel< ::itk::Euler2DTransform<map::core::continuous::ScalarType> >::Pointer
      generateTestTransform(double rotation, double x, double y)
    {
      typedef map::algorithm::itk::ITKTransformModel< ::itk::Euler2DTransform<map::core::continuous::ScalarType> > ModelType;
      ModelType::Pointer transform = ModelType::New();
      transform->getConcreteTransform()->SetAngleInDegrees(rotation);
      ::itk::Euler2DTransform<map::core::continuous::ScalarType>::OffsetType offset;
      offset[0]=x;
      offset[1]=y;
      transform->getConcreteTransform()->SetOffset(offset);
    
      return transform;
    }

		int mapModelModelKernelCombinatorTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;
			typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel FieldKernelType;

			typedef core::ModelModelKernelCombinator<2, 2, 2> CombinatorType;
			typedef core::ModelModelKernelCombinator<2, 3, 2> Combinator2Type;
			typedef core::ModelModelKernelCombinator<3, 2, 2> Combinator3Type;
			typedef core::ModelModelKernelCombinator<2, 2, 3> Combinator4Type;

			// setting up the representation descriptor based on the model kernel
			ModelKernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
			ModelKernelType::RepresentationDescriptorType::PointType origin;
			origin.Fill(0);
			ModelKernelType::RepresentationDescriptorType::SizeType size;
			size.fill(20);

			ModelKernelType::RepresentationDescriptorType::Pointer spInRep =
				ModelKernelType::RepresentationDescriptorType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			//Now we create the kernels
			ModelKernelType::Pointer spKernel1 = ModelKernelType::New();
			ModelKernelType::Pointer spKernel2 = ModelKernelType::New();
			ModelKernelType::Pointer spMOKernel1 = ModelKernelType::New();
			ModelKernelType::Pointer spMOKernel2 = ModelKernelType::New();

      spKernel1->setTransformModel(map::algorithm::itk::ITKTransformModel< ::itk::TranslationTransform< map::core::continuous::ScalarType, 2> >::New());
      spKernel2->setTransformModel(map::algorithm::itk::ITKTransformModel< ::itk::TranslationTransform< map::core::continuous::ScalarType, 2> >::New());

      spMOKernel1->setTransformModel(generateTestTransform(-10,11,-80));
      spMOKernel2->setTransformModel(generateTestTransform(21,2,78));

      FieldKernelType::Pointer spIllegalKernel = FieldKernelType::New();


			//creating the combinator
			CombinatorType::Pointer spCombinator = CombinatorType::New();

			//Create requests

			// valid request: model, model
			CombinatorType::RequestType request(spKernel1, spKernel2);
			// valid request: with 2 matrix offset based models
			CombinatorType::RequestType request2(spMOKernel1, spMOKernel2);
			// illegal request: field, field
			CombinatorType::RequestType illegalRequest1(spIllegalKernel, spIllegalKernel);
			// illegal request: field, model
			CombinatorType::RequestType illegalRequest2(spIllegalKernel, spKernel2);
			// illegal request: model, field
			CombinatorType::RequestType illegalRequest3(spKernel1, spIllegalKernel);

			//TEST
			CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest2));
			CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest3));
			CHECK_EQUAL(true, spCombinator->canHandleRequest(request));

			CHECK_EQUAL("ModelModelKernelCombinator<2,2,2>", CombinatorType::getStaticProviderName());
			CHECK_EQUAL("ModelModelKernelCombinator<2,3,2>", Combinator2Type::getStaticProviderName());
			CHECK_EQUAL("ModelModelKernelCombinator<3,2,2>", Combinator3Type::getStaticProviderName());
			CHECK_EQUAL("ModelModelKernelCombinator<2,2,3>", Combinator4Type::getStaticProviderName());
			CHECK_EQUAL(CombinatorType::getStaticProviderName(), spCombinator->getProviderName());

			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest1, spInRep),
								 core::ServiceException);
			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest2, spInRep),
								 core::ServiceException);
			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest3, spInRep),
								 core::ServiceException);

      // test combination support for matrix offset based transfor with uniform dimensionality
			// this should not be thrown any more as soon as the ModelModelKernelCombinator has been
      // completly implemented
			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(request, spInRep), core::ServiceException);

      // test combination support for matrix offset based transfor with uniform dimensionality
      CombinatorType::CombinedKernelBasePointer resultKernel;
			CHECK_NO_THROW(resultKernel = spCombinator->combineKernels(request2, spInRep));

      //now test im the mapping is correct.
      map::core::continuous::Elements<2>::PointType inPoint1;
      inPoint1[0] = 10;
      inPoint1[1] = 1000;
      
      map::core::continuous::Elements<2>::PointType inPoint2;
      inPoint2[0] = -33;
      inPoint2[1] = 420;

      map::core::continuous::Elements<2>::PointType combinedResult1;
      CHECK(resultKernel->mapPoint(inPoint1,combinedResult1));
      map::core::continuous::Elements<2>::PointType combinedResult2;
      CHECK(resultKernel->mapPoint(inPoint2,combinedResult2));

      map::core::continuous::Elements<2>::PointType refPoint1;
      spMOKernel1->mapPoint(inPoint1,refPoint1);
      spMOKernel2->mapPoint(refPoint1,refPoint1);

      map::core::continuous::Elements<2>::PointType refPoint2;
      spMOKernel1->mapPoint(inPoint2,refPoint2);
      spMOKernel2->mapPoint(refPoint2,refPoint2);

      CHECK_CLOSE(refPoint1[0], combinedResult1[0], 0.0000001);
      CHECK_CLOSE(refPoint1[1], combinedResult1[1], 0.0000001);
      CHECK_CLOSE(refPoint2[0], combinedResult2[0], 0.0000001);
      CHECK_CLOSE(refPoint2[1], combinedResult2[1], 0.0000001);
      
			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
