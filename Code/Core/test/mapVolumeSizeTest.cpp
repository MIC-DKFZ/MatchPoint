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

#include <stdlib.h>

#include "litCheckMacros.h"

#include "mapSDXMLStrWriter.h"
#include "mapVolumeSize.h"

namespace map
{
	namespace testing
	{
		int mapVolumeSizeTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			::map::core::continuous::VolumeSize<2> size1 = {{1, 2}};
			::map::core::continuous::VolumeSize<2> size2;
			size2.fill(2);
			::map::core::continuous::VolumeSize<2> size3;
			size3 = size2;
			::map::core::continuous::VolumeSize<2> nonPositiveSize1 = {{2, -2}};

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

			//Testing streaming
			structuredData::Element::Pointer spSDElement;
			CHECK_NO_THROW(spSDElement = core::continuous::VolumeSize<2>::streamToStructuredData(size1));
			structuredData::XMLStrWriter::Pointer xmlStrWriter = structuredData::XMLStrWriter::New();

			::map::core::continuous::VolumeSize<2> size1_clone =
				::map::core::continuous::VolumeSize<2>::streamFromStructuredData(spSDElement);
			CHECK_ARRAY_EQUAL(size1, size1_clone, 2);

			CHECK_THROW(::map::core::continuous::VolumeSize<3>::streamFromStructuredData(
							spSDElement)); //wrong dimensionality

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
