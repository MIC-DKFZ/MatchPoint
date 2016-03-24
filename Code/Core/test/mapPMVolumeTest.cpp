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

#include "mapPMVolume.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		int mapPMVolumeTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			::map::core::continuous::PMVolume::SizeType size(2);
			size[0] = 1;
			size[1] = 2;
			::map::core::continuous::PMVolume::OriginType origin(2);
			origin[0] = 5;
			origin[1] = 6;


			::map::core::continuous::PMVolume volume1(size);
			::map::core::continuous::PMVolume volume2(origin, size);
			::map::core::continuous::PMVolume volume3(volume2);

			CHECK_EQUAL(0, volume1.getOrigin(0));
			CHECK_EQUAL(0, volume1.getOrigin(1));
			CHECK_EQUAL(1, volume1.getSize(0));
			CHECK_EQUAL(2, volume1.getSize(1));
			CHECK_EQUAL(5, volume2.getOrigin(0));
			CHECK_EQUAL(6, volume2.getOrigin(1));
			CHECK_EQUAL(1, volume2.getSize(0));
			CHECK_EQUAL(2, volume2.getSize(1));
			CHECK_EQUAL(volume2, volume3);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
