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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapVolumeSizeTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapVolumeSize.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		int mapVolumeSizeTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			core::continuous::VolumeSize<2> size1 = {{1, 2}};
			core::continuous::VolumeSize<2> size2;
			size2.fill(2);
			core::continuous::VolumeSize<2> size3;
			size3 = size2;
			core::continuous::VolumeSize<2> nonPositiveSize1 = {{2, -2}};

			CHECK_EQUAL(1, size1.getElement(0));
			CHECK_EQUAL(1, size1[0]);
			CHECK_EQUAL(2, size1.getElement(1));
			CHECK_EQUAL(2, size1[1]);

			CHECK_EQUAL(2, size2.getElement(0));
			CHECK_EQUAL(2, size2[0]);
			CHECK_EQUAL(2, size2.getElement(0));
			CHECK_EQUAL(2, size2[0]);

			CHECK(size1 != size2);
			CHECK(size2 == size3);

			size2[0] = 1;

			CHECK(size1 == size2);
			CHECK(size2 != size3);

			size2.setElement(0, 2);

			CHECK(size2 == size3);

			CHECK(size1.isPositive());
			CHECK(!nonPositiveSize1.isPositive());

			CHECK_EQUAL(2, size1.getVolumeSizeDimension());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
