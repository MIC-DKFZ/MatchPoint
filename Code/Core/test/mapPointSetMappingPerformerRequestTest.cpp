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

#include "mapPointSetMappingPerformerRequest.h"
#include "mapRegistration.h"

#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{
		int mapPointSetMappingPerformerRequestTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			RegistrationType::Pointer spRegistration = RegistrationType::New();

			typedef core::continuous::Elements<2>::InternalPointSetType InputPointSetType;
			InputPointSetType::Pointer spInputPointSet = InputPointSetType::New();

			typedef core::PointSetMappingPerformerRequest<RegistrationType, InputPointSetType, InputPointSetType>
			RequestType;

			bool _throwOnMappingError = true;
			RequestType::ErrorPointValueType _errorValue = 42;

			// create a first RequestType object
			RequestType request1(spRegistration, spInputPointSet, _throwOnMappingError, _errorValue);

			CHECK(spRegistration.GetPointer() == request1._spRegistration.GetPointer());
			CHECK(spInputPointSet.GetPointer() == request1._spInputData.GetPointer());
			CHECK(_throwOnMappingError == request1._throwOnMappingError);
			CHECK(_errorValue == request1._errorValue);

			// use the copy constructor to create a third RequestType object
			// and check if the copy constructor worked correctly
			RequestType request3(request1);
			CHECK(spRegistration.GetPointer() == request3._spRegistration.GetPointer());
			CHECK(spInputPointSet.GetPointer() == request3._spInputData.GetPointer());
			CHECK(_throwOnMappingError == request3._throwOnMappingError);
			CHECK(_errorValue == request3._errorValue);

			// use the operator= the create a RequestType object
			// and check it
			request3._spRegistration = NULL;
			request3._spInputData = NULL;
			request3._throwOnMappingError = false;
			request3._errorValue = 0;


			request3 = request1;
			CHECK(spRegistration.GetPointer() == request3._spRegistration.GetPointer());
			CHECK(spInputPointSet.GetPointer() == request3._spInputData.GetPointer());
			CHECK(_throwOnMappingError == request3._throwOnMappingError);
			CHECK(_errorValue == request3._errorValue);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
