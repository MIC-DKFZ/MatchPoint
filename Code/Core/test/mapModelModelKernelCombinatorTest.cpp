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

#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

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

			FieldKernelType::Pointer spIllegalKernel = FieldKernelType::New();


			//creating the combinator
			CombinatorType::Pointer spCombinator = CombinatorType::New();

			//Create requests

			// valid request: model, model
			CombinatorType::RequestType request(spKernel1, spKernel2);
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

			// this should not be thrown any more as soon as the ModelModelKernelCombinator has been finished
			CHECK_THROW_EXPLICIT(spCombinator->combineKernels(request, spInRep), core::ServiceException);


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
