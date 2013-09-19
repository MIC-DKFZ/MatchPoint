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

#include "mapRegistrationCombinationRequest.h"
#include "mapModelBasedRegistrationKernel.h"

#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapRegistrationCombinationRequestTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			// generate kernels for testing
			typedef core::ModelBasedRegistrationKernel<2, 2> KernelType;
			KernelType::Pointer spKernel1 = KernelType::New();
			KernelType::Pointer spKernel2 = KernelType::New();
			KernelType::Pointer spKernel3 = KernelType::New();
			KernelType::Pointer spKernel4 = KernelType::New();

			// create a first RegistrationLoadRequest object with these two kernels
			// and check if the two kernels are really in the object
			core::RegistrationCombinationRequest<2, 2, 2> request1(spKernel1, spKernel2);

			CHECK(spKernel1.GetPointer() == request1._spKernel1.GetPointer());
			CHECK(spKernel2.GetPointer() == request1._spKernel2.GetPointer());


			// use the copy constructor to create a second RegistrationLoadRequest object
			// and check if the kernels are the same in the first and second object
			core::RegistrationCombinationRequest<2, 2, 2> request2(request1);
			CHECK(spKernel1.GetPointer() == request2._spKernel1.GetPointer());
			CHECK(spKernel2.GetPointer() == request2._spKernel2.GetPointer());

			// use the operator= the create a third RegistrationLoadRequest object
			// and check if the kernels are the same in the first and third object
			core::RegistrationCombinationRequest<2, 2, 2> request3(spKernel3, spKernel4);
			request3 = request1;
			CHECK(spKernel1.GetPointer() == request3._spKernel1.GetPointer());
			CHECK(spKernel2.GetPointer() == request3._spKernel2.GetPointer());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
