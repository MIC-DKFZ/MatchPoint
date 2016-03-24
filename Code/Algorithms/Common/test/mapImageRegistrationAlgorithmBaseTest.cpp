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

#include "litCheckMacros.h"
#include "mapDiscreteElements.h"
#include "mapImageRegistrationAlgorithmBase.h"

namespace map
{
	namespace testing
	{
		namespace
		{

			template<class TMovingImage, class TTargetImage>
			class TestImageRegistrationAlgorithmInterface : public
				::map::algorithm::ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>
			{
			public:
				TestImageRegistrationAlgorithmInterface() {};
			};
		}

		int mapImageRegistrationAlgorithmBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::discrete::Elements<2>::InternalImageType InternalImage2DType;
			typedef core::discrete::Elements<3>::InternalImageType InternalImage3DType;

			TestImageRegistrationAlgorithmInterface<InternalImage2DType, InternalImage3DType> testInterface;

			InternalImage2DType::Pointer spMovingImageReference = InternalImage2DType::New();
			InternalImage3DType::Pointer spTargetImageReference = InternalImage3DType::New();

			CHECK_EQUAL(true, testInterface.getMovingImage().IsNull());
			CHECK_EQUAL(true, testInterface.getTargetImage().IsNull());

			testInterface.setMovingImage(spMovingImageReference);
			testInterface.setTargetImage(spTargetImageReference);

			CHECK_EQUAL(spMovingImageReference.GetPointer(), testInterface.getMovingImage().GetPointer());
			CHECK_EQUAL(spTargetImageReference.GetPointer(), testInterface.getTargetImage().GetPointer());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
