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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapImageMappingPerformerRequestTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapImageMappingPerformerRequest.h"
#include "mapRegistration.h"

#include "litCheckMacros.h"

#include "itkLinearInterpolateImageFunction.h"

namespace map
{
	namespace testing
	{
		int mapImageMappingPerformerRequestTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			RegistrationType::Pointer spRegistration = RegistrationType::New();

			typedef core::discrete::Elements<2>::InternalImageType InputImageType;
			InputImageType::Pointer spInputImage = InputImageType::New();

			typedef core::ImageMappingPerformerRequest<RegistrationType, InputImageType, InputImageType> RequestType;

			bool _throwOnMappingError = true;
			RequestType::ErrorValueType _errorValue = 42;

			bool _throwOnOutOfInputAreaError = false;
			RequestType::PaddingValueType _paddingValue = 23;

			RequestType::ResultImageDescriptorType::Pointer spDescriptor = RequestType::ResultImageDescriptorType::New();

			typedef itk::LinearInterpolateImageFunction<InputImageType, core::continuous::ScalarType> InterpolatorType;
			InterpolatorType::Pointer spInterpolator = InterpolatorType::New();

			// create a first RequestType object
			RequestType request1(spRegistration, spInputImage, spDescriptor, spInterpolator, _throwOnMappingError, _errorValue, _throwOnOutOfInputAreaError, _paddingValue);

			CHECK(spRegistration.GetPointer() == request1._spRegistration.GetPointer());
			CHECK(spInputImage.GetPointer() == request1._spInputData.GetPointer());
			CHECK(spDescriptor.GetPointer() == request1._spResultDescriptor.GetPointer());
			CHECK(_throwOnMappingError == request1._throwOnMappingError);
			CHECK(_errorValue == request1._errorValue);
			CHECK(_throwOnOutOfInputAreaError == request1._throwOnOutOfInputAreaError);
			CHECK(_paddingValue == request1._paddingValue);

			// use the copy constructor to create a third RequestType object
			// and check if the copy constructor worked correctly
			RequestType request3(request1);
			CHECK(spRegistration.GetPointer() == request3._spRegistration.GetPointer());
			CHECK(spInputImage.GetPointer() == request3._spInputData.GetPointer());
			CHECK(spDescriptor.GetPointer() == request3._spResultDescriptor.GetPointer());
			CHECK(_throwOnMappingError == request3._throwOnMappingError);
			CHECK(_errorValue == request3._errorValue);
			CHECK(_throwOnOutOfInputAreaError == request3._throwOnOutOfInputAreaError);
			CHECK(_paddingValue == request3._paddingValue);

			// use the operator= the create a RequestType object
			// and check it
			request3._spRegistration = NULL;
			request3._spInputData = NULL;
			request3._spResultDescriptor = NULL;
			request3._throwOnMappingError = false;
			request3._errorValue = 0;
			request3._throwOnOutOfInputAreaError = true;
			request3._paddingValue = 0;


			request3 = request1;
			CHECK(spRegistration.GetPointer() == request3._spRegistration.GetPointer());
			CHECK(spInputImage.GetPointer() == request3._spInputData.GetPointer());
			CHECK(spDescriptor.GetPointer() == request3._spResultDescriptor.GetPointer());
			CHECK(_throwOnMappingError == request3._throwOnMappingError);
			CHECK(_errorValue == request3._errorValue);
			CHECK(_throwOnOutOfInputAreaError == request3._throwOnOutOfInputAreaError);
			CHECK(_paddingValue == request3._paddingValue);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
