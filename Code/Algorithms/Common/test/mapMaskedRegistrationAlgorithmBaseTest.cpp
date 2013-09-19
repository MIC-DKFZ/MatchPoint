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
#include "mapMaskedRegistrationAlgorithmBase.h"

#include "itkBoxSpatialObject.h"

namespace map
{
	namespace testing
	{
		namespace
		{

			template<unsigned int VMovingDimension, unsigned int VTargetDimension>
			class TestMaskedRegistrationAlgorithmBase : public
				algorithm::MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>
			{
			public:
				TestMaskedRegistrationAlgorithmBase() {};
				using algorithm::MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::getTargetMaskMTime;
				using algorithm::MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::getMovingMaskMTime;
			};
		}

		int mapMaskedRegistrationAlgorithmBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef ::itk::BoxSpatialObject<2> Mask2DType;
			typedef ::itk::BoxSpatialObject<3> Mask3DType;

			TestMaskedRegistrationAlgorithmBase<2, 3> testInterface;

			Mask2DType::Pointer spMovingMask = Mask2DType::New();
			Mask3DType::Pointer spTargetMask = Mask3DType::New();

			const TestMaskedRegistrationAlgorithmBase<2, 3>::MovingMaskBaseType* pMovingBase = spMovingMask;
			const TestMaskedRegistrationAlgorithmBase<2, 3>::TargetMaskBaseType* pTargetBase = spTargetMask;

			CHECK_EQUAL(true, testInterface.getMovingMask().IsNull());
			CHECK_EQUAL(true, testInterface.getTargetMask().IsNull());

			unsigned long mmt = testInterface.getMovingMaskMTime();
			unsigned long tmt = testInterface.getTargetMaskMTime();

			testInterface.setMovingMask(spMovingMask);

			CHECK(mmt < testInterface.getMovingMaskMTime());
			CHECK(tmt == testInterface.getTargetMaskMTime());
			mmt = testInterface.getMovingMaskMTime();

			testInterface.setTargetMask(spTargetMask);

			CHECK(mmt == testInterface.getMovingMaskMTime());
			CHECK(tmt < testInterface.getTargetMaskMTime());

			tmt = testInterface.getTargetMaskMTime();

			spMovingMask->Modified();

			CHECK(mmt < testInterface.getMovingMaskMTime());
			CHECK(tmt == testInterface.getTargetMaskMTime());
			mmt = testInterface.getMovingMaskMTime();

			spTargetMask->Modified();

			CHECK(mmt == testInterface.getMovingMaskMTime());
			CHECK(tmt < testInterface.getTargetMaskMTime());

			CHECK_EQUAL(pMovingBase, testInterface.getMovingMask().GetPointer());
			CHECK_EQUAL(pTargetBase, testInterface.getTargetMask().GetPointer());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
