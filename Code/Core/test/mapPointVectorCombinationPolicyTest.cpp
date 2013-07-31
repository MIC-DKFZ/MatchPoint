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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapPointVectorCombinationPolicyTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapPointVectorCombinationPolicy.h"
#include "litCheckMacros.h"
#include "mapContinuous.h"

namespace map
{
	namespace testing
	{
		int mapPointVectorCombinationPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::continuous::Elements<2>::VectorType Vector2DType;
			typedef core::continuous::Elements<3>::VectorType Vector3DType;
			typedef core::continuous::Elements<2>::PointType Point2DType;
			typedef core::continuous::Elements<3>::PointType Point3DType;

			typedef core::PointVectorCombinationPolicy<2, 2> Combination22PolicyType;
			typedef core::PointVectorCombinationPolicy<3, 2> Combination32PolicyType;
			typedef core::PointVectorCombinationPolicy<2, 3> Combination23PolicyType;

			Vector2DType v1;
			v1[0] = 1;
			v1[1] = 0;
			Vector2DType v2;
			v2[0] = 3;
			v2[1] = 2;
			Vector3DType v3;
			v3[0] = 4;
			v3[1] = -6;
			v3[2] = 5;

			Point2DType p1;
			p1[0] = 12;
			p1[1] = -3;
			Point2DType p2;
			p2[0] = -3;
			p2[1] = -55;
			Point3DType p3;
			p3[0] = 7;
			p3[1] = 100;
			p3[2] = -50;

			Vector2DType v1_v2_ref;
			v1_v2_ref[0] = 4;
			v1_v2_ref[1] = 2;
			Vector2DType v3_v1_ref;
			v3_v1_ref[0] = 5;
			v3_v1_ref[1] = -6;
			Vector3DType v2_v3_ref;
			v2_v3_ref[0] = 7;
			v2_v3_ref[1] = -4;
			v2_v3_ref[2] = 5;

			Point2DType p1_v2_ref;
			p1_v2_ref[0] = 15;
			p1_v2_ref[1] = -1;
			Point2DType p3_v2_ref;
			p3_v2_ref[0] = 10;
			p3_v2_ref[1] = 102;
			Point3DType p1_v3_ref;
			p1_v3_ref[0] = 16;
			p1_v3_ref[1] = -9;
			p1_v3_ref[2] = 5;

			Vector2DType p1_p2_ref;
			p1_p2_ref[0] = -15;
			p1_p2_ref[1] = -52;
			Vector3DType p1_p3_ref;
			p1_p3_ref[0] = -5;
			p1_p3_ref[1] = 103;
			p1_p3_ref[2] = -50;
			Vector2DType p3_p2_ref;
			p3_p2_ref[0] = -10;
			p3_p2_ref[1] = -155;



			CHECK_EQUAL(false, Combination22PolicyType::isDefaultImplementation());
			CHECK_EQUAL(true, Combination32PolicyType::isDefaultImplementation());
			CHECK_EQUAL(true, Combination23PolicyType::isDefaultImplementation());

			Vector2DType result_v1_v2;
			Combination22PolicyType::combineVectors(v1, v2, result_v1_v2);
			CHECK_EQUAL(v1_v2_ref, result_v1_v2);

			Vector2DType result_v3_v1;
			Combination32PolicyType::combineVectors(v3, v1, result_v3_v1);
			CHECK_EQUAL(v3_v1_ref, result_v3_v1);

			Vector3DType result_v2_v3;
			Combination23PolicyType::combineVectors(v2, v3, result_v2_v3);
			CHECK_EQUAL(v2_v3_ref, result_v2_v3);

			Point2DType result_p1_v2;
			Combination22PolicyType::mapPoint(p1, v2, result_p1_v2);
			CHECK_EQUAL(p1_v2_ref, result_p1_v2);

			Point2DType result_p3_v2;
			Combination32PolicyType::mapPoint(p3, v2, result_p3_v2);
			CHECK_EQUAL(p3_v2_ref, result_p3_v2);

			Point3DType result_p1_v3;
			Combination23PolicyType::mapPoint(p1, v3, result_p1_v3);
			CHECK_EQUAL(p1_v3_ref, result_p1_v3);

			Vector2DType result_p1_p2;
			Combination22PolicyType::computeVector(p1, p2, result_p1_p2);
			CHECK_EQUAL(p1_p2_ref, result_p1_p2);

			Vector2DType result_p3_p2;
			Combination32PolicyType::computeVector(p3, p2, result_p3_p2);
			CHECK_EQUAL(p3_p2_ref, result_p3_p2);

			Vector3DType result_p1_p3;
			Combination23PolicyType::computeVector(p1, p3, result_p1_p3);
			CHECK_EQUAL(p1_p3_ref, result_p1_p3);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
