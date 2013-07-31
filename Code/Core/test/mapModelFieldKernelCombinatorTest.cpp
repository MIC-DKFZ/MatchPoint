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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapModelFieldKernelCombinatorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapModelFieldKernelCombinator.h"
#include "mapFieldByModelFieldCombinationFunctor.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapFieldBasedRegistrationKernels.h"

#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		int mapModelFieldKernelCombinatorTest(int argc, char *argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;
			typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel FieldKernelType;

			typedef core::ModelFieldKernelCombinator<2, 2, 2> CombinatorType;
			typedef core::ModelFieldKernelCombinator<2, 3, 2> Combinator2Type;
			typedef core::ModelFieldKernelCombinator<3, 2, 2> Combinator3Type;
			typedef core::ModelFieldKernelCombinator<2, 2, 3> Combinator4Type;

			// setting up the representation descriptor based on the first kernel
			ModelKernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
			ModelKernelType::RepresentationDescriptorType::PointType origin;
			origin.Fill(0);
			ModelKernelType::RepresentationDescriptorType::SizeType size;
			size.fill(20);

			ModelKernelType::RepresentationDescriptorType::Pointer spInRep = ModelKernelType::RepresentationDescriptorType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			//Now we create the kernels
			ModelKernelType::Pointer spKernel1 = ModelKernelType::New();
			FieldKernelType::Pointer spKernel2 = FieldKernelType::New();


			//creating the combinator
			CombinatorType::Pointer spCombinator = CombinatorType::New();

			//Create requests

			// valid request: model, field
			CombinatorType::RequestType request(spKernel1, spKernel2);
			// illegal request: model, model
			CombinatorType::RequestType illegalRequest1(spKernel1, spKernel1);
			// illegal request: field, field
			CombinatorType::RequestType illegalRequest2(spKernel2, spKernel2);
			// illegal request: field, model
			CombinatorType::RequestType illegalRequest3(spKernel2, spKernel1);

			//TEST
			CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest2));
			CHECK_EQUAL(false, spCombinator->canHandleRequest(illegalRequest3));
			CHECK_EQUAL(true, spCombinator->canHandleRequest(request));

			CHECK_EQUAL("ModelFieldKernelCombinator<2,2,2>", CombinatorType::getStaticProviderName());
			CHECK_EQUAL("ModelFieldKernelCombinator<2,3,2>", Combinator2Type::getStaticProviderName());
			CHECK_EQUAL("ModelFieldKernelCombinator<3,2,2>", Combinator3Type::getStaticProviderName());
			CHECK_EQUAL("ModelFieldKernelCombinator<2,2,3>", Combinator4Type::getStaticProviderName());
			CHECK_EQUAL(CombinatorType::getStaticProviderName(), spCombinator->getProviderName());

			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest1, spInRep), core::ServiceException);
			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest2, spInRep), core::ServiceException);
			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(illegalRequest3, spInRep), core::ServiceException);

			CombinatorType::CombinedKernelBasePointer spCombinedKernel;
			CHECK_NO_THROW(spCombinedKernel = spCombinator->combineKernels(request, spInRep));

			//check if the lazy kernel was created with the right functor
			//the testing on the right combination is done in the tests of the combination functors

			FieldKernelType *pConcreteKernel = dynamic_cast<FieldKernelType *>(spCombinedKernel.GetPointer());
			CHECK(pConcreteKernel != NULL);

			if (pConcreteKernel)
			{
				typedef core::functors::FieldByModelFieldCombinationFunctor<2, 2, 2> CombineFunctorType;

				const CombineFunctorType *pFunctor = dynamic_cast<const CombineFunctorType *>(pConcreteKernel->getFieldFunctor());
				CHECK(pFunctor != NULL);

			}

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
