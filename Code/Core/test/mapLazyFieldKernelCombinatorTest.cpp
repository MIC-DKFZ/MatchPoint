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

#include "mapLazyFieldKernelCombinator.h"
#include "mapGenericFieldGeneratingCombinationFunctor.h"
#include "mapLazyRegistrationKernel.h"
#include "mapNullRegistrationKernel.h"

#include "litCheckMacros.h"

namespace map
{
    namespace testing
    {

        int mapLazyFieldKernelCombinatorTest(int argc, char* argv[])
        {
            PREPARE_DEFAULT_TEST_REPORTING;

            typedef core::LazyRegistrationKernel<2, 2> KernelType;

            typedef core::NullRegistrationKernel<2, 2> IllegalKernelType;

            typedef core::LazyFieldKernelCombinator<2, 2, 2> CombinatorType;
            typedef core::LazyFieldKernelCombinator<2, 3, 2> Combinator2Type;
            typedef core::LazyFieldKernelCombinator<3, 2, 2> Combinator3Type;
            typedef core::LazyFieldKernelCombinator<2, 2, 3> Combinator4Type;

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

            //Now we create the kernel
            KernelType::Pointer spKernel1 = KernelType::New();
            KernelType::Pointer spKernel2 = KernelType::New();


            //Now we create the illegal kernel
            IllegalKernelType::Pointer spIllegalKernel1 = IllegalKernelType::New();
            IllegalKernelType::Pointer spIllegalKernel2 = IllegalKernelType::New();

            //creating the combinator
            CombinatorType::Pointer spCombinator = CombinatorType::New();

            //Create requests

            CombinatorType::RequestType request(spKernel1, spKernel2);
            CombinatorType::RequestType illegalRequest1(spKernel1, spIllegalKernel2);
            CombinatorType::RequestType illegalRequest2(spIllegalKernel1, spKernel2);
            CombinatorType::RequestType illegalRequest3(spIllegalKernel1, spIllegalKernel2);

            //TEST
            CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest1));
            CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest2));
            CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest3));
            CHECK_EQUAL(true, spCombinator->canHandleRequest(request));

            CHECK_EQUAL("LazyFieldKernelCombinator<2,2,2>", CombinatorType::getStaticProviderName());

            CHECK_EQUAL("LazyFieldKernelCombinator<2,3,2>", Combinator2Type::getStaticProviderName());
            CHECK_EQUAL("LazyFieldKernelCombinator<3,2,2>", Combinator3Type::getStaticProviderName());
            CHECK_EQUAL("LazyFieldKernelCombinator<2,2,3>", Combinator4Type::getStaticProviderName());
            CHECK_EQUAL(CombinatorType::getStaticProviderName(), spCombinator->getProviderName());

            CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest1, spInRep),
                core::ServiceException);
            CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest2, spInRep),
                core::ServiceException);
            CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest3, spInRep),
                core::ServiceException);

            CombinatorType::CombinedKernelBasePointer spCombinedKernel;
            CHECK_NO_THROW(spCombinedKernel = spCombinator->combineKernels(request, spInRep));

            //check if the lazy kernel was created with the right functor
            //the testing on the right combination is done in the tests of the combination functors

            KernelType* pConcreteKernel = dynamic_cast<KernelType*>(spCombinedKernel.GetPointer());
            CHECK(pConcreteKernel != NULL);

            if (pConcreteKernel)
            {
                typedef core::functors::GenericFieldGeneratingCombinationFunctor<2, 2, 2> CombineFunctorType;

                const CombineFunctorType* pFunctor = dynamic_cast<const CombineFunctorType*>
                    (pConcreteKernel->getTransformFunctor());
                CHECK(pFunctor != NULL);

            }

            RETURN_AND_REPORT_TEST_SUCCESS;
        }
    } //namespace testing
} //namespace map
