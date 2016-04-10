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

#include "mapPreCachedKernelCombinator.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapNullRegistrationKernel.h"

#include "mapITKTranslationTransform.h"
#include "mapITKEuler2DTransform.h"

#include "litCheckMacros.h"

namespace map
{
    namespace testing
    {

        ::itk::Euler2DTransform<map::core::continuous::ScalarType>::Pointer
            generateTestTransform(double rotation, double x, double y)
        {
            typedef ::itk::Euler2DTransform<map::core::continuous::ScalarType> ModelType;
            ModelType::Pointer transform = ModelType::New();
            transform->SetAngleInDegrees(rotation);
            ::itk::Euler2DTransform<map::core::continuous::ScalarType>::OffsetType offset;
            offset[0] = x;
            offset[1] = y;
            transform->SetOffset(offset);

            return transform;
        }

        ::itk::TranslationTransform<map::core::continuous::ScalarType, 2>::Pointer
            generateTestTranslationTransform(double x, double y)
        {
            typedef ::itk::TranslationTransform<map::core::continuous::ScalarType, 2> ModelType;
            ModelType::Pointer transform = ModelType::New();
            ::itk::TranslationTransform<map::core::continuous::ScalarType, 2>::ParametersType offset(2);
            offset[0] = x;
            offset[1] = y;
            transform->SetParameters(offset);

            return transform;
        }

        int mapPreCachedKernelCombinatorTest(int argc, char* argv[])
        {
            PREPARE_DEFAULT_TEST_REPORTING;

            typedef core::PreCachedRegistrationKernel<2, 2> KernelType;
            typedef core::NullRegistrationKernel<2, 2> IllegalKernelType;

            typedef core::PreCachedKernelCombinator<2, 2, 2> CombinatorType;
            typedef core::PreCachedKernelCombinator<2, 3, 2> Combinator2Type;
            typedef core::PreCachedKernelCombinator<3, 2, 2> Combinator3Type;
            typedef core::PreCachedKernelCombinator<2, 2, 3> Combinator4Type;

            // setting up the representation descriptor based on the model kernel
            KernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
            KernelType::RepresentationDescriptorType::PointType origin;
            origin.Fill(0);
            KernelType::RepresentationDescriptorType::SizeType size;
            size.fill(20);

            KernelType::RepresentationDescriptorType::Pointer spInRep =
                KernelType::RepresentationDescriptorType::New();
            spInRep->setSize(size);
            spInRep->setSpacing(spacing);
            spInRep->setOrigin(origin);

            //Now we create the kernels
            KernelType::Pointer spKernel1 = KernelType::New();
            KernelType::Pointer spKernel2 = KernelType::New();
            KernelType::Pointer spMOKernel1 = KernelType::New();
            KernelType::Pointer spMOKernel2 = KernelType::New();

            spKernel1->setTransformModel(generateTestTranslationTransform(11, -80));

            spMOKernel1->setTransformModel(generateTestTransform(itk::Math::pi / 2.0, 11, -80));
            spMOKernel2->setTransformModel(generateTestTransform(-0.2, 2, 78));

            IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();


            //creating the combinator
            CombinatorType::Pointer spCombinator = CombinatorType::New();

            //Create requests

            // valid request: model and matrix offset based model
            CombinatorType::RequestType request(spKernel1, spMOKernel1);
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

            CHECK_EQUAL("PreCachedKernelCombinator<2,2,2>", CombinatorType::getStaticProviderName());
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

            // test combination support for matrix offset based transform with uniform dimensionality
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
            CHECK(resultKernel->mapPoint(inPoint1, combinedResult1));
            map::core::continuous::Elements<2>::PointType combinedResult2;
            CHECK(resultKernel->mapPoint(inPoint2, combinedResult2));

            map::core::continuous::Elements<2>::PointType refPoint1;
            spMOKernel1->mapPoint(inPoint1, refPoint1);
            spMOKernel2->mapPoint(refPoint1, refPoint1);

            map::core::continuous::Elements<2>::PointType refPoint2;
            spMOKernel1->mapPoint(inPoint2, refPoint2);
            spMOKernel2->mapPoint(refPoint2, refPoint2);

            CHECK_CLOSE(refPoint1[0], combinedResult1[0], 0.0000001);
            CHECK_CLOSE(refPoint1[1], combinedResult1[1], 0.0000001);
            CHECK_CLOSE(refPoint2[0], combinedResult2[0], 0.0000001);
            CHECK_CLOSE(refPoint2[1], combinedResult2[1], 0.0000001);

            // test if combination of transforms with uniform dimensionality and matrix offset based
            // produces the right transform
            const KernelType* castedResultKernel = dynamic_cast<const KernelType*>(resultKernel.GetPointer());
            CHECK(castedResultKernel != NULL);

            typedef ::itk::MatrixOffsetTransformBase<map::core::continuous::ScalarType, 2, 2> MatrixOffsetTransformType;
            const MatrixOffsetTransformType* matrixOffsetTransform = dynamic_cast<const MatrixOffsetTransformType*>(castedResultKernel->getTransformModel());
            CHECK(matrixOffsetTransform != NULL);

            // test combination support of transforms with uniform dimensionality but not all are matrix offset based
            CHECK_NO_THROW(resultKernel = spCombinator->combineKernels(request, spInRep));

            CHECK(resultKernel->mapPoint(inPoint1, combinedResult1));
            CHECK(resultKernel->mapPoint(inPoint2, combinedResult2));

            spKernel1->mapPoint(inPoint1, refPoint1);
            spMOKernel1->mapPoint(refPoint1, refPoint1);

            spKernel1->mapPoint(inPoint2, refPoint2);
            spMOKernel1->mapPoint(refPoint2, refPoint2);

            CHECK_CLOSE(refPoint1[0], combinedResult1[0], 0.0000001);
            CHECK_CLOSE(refPoint1[1], combinedResult1[1], 0.0000001);
            CHECK_CLOSE(refPoint2[0], combinedResult2[0], 0.0000001);
            CHECK_CLOSE(refPoint2[1], combinedResult2[1], 0.0000001);

            // test if combination of transforms with uniform dimensionality but not all are matrix offset based
            // produces the right transform
            castedResultKernel = dynamic_cast<const KernelType*>(resultKernel.GetPointer());
            CHECK(castedResultKernel != NULL);

            typedef ::itk::CompositeTransform<map::core::continuous::ScalarType, 2> CompositeTransformType;
            const CompositeTransformType* compositeTransform = dynamic_cast<const CompositeTransformType*>(castedResultKernel->getTransformModel());
            CHECK(compositeTransform != NULL);

            RETURN_AND_REPORT_TEST_SUCCESS;
        }
    } //namespace testing
} //namespace map
