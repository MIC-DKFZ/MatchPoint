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

#include "itkImage.h"
#include "itkBoxSpatialObject.h"

#include "mapMaskBoundingBoxHelper.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		int mapMaskBoundingBoxHelperTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef ::itk::Image<int, 2> ImageType;
			ImageType::Pointer image = ImageType::New();
			ImageType::DirectionType direction;
			direction[0][0] = 0.866;
			direction[1][0] = -0.5;
			direction[0][1] = 0.5;
			direction[1][1] = 0.866;
			image->SetDirection(direction);
			ImageType::PointType origin;
			origin.Fill(-20);
			image->SetOrigin(origin);
			ImageType::SizeType size;
			size.Fill(100);
			image->SetRegions(size);
			image->Allocate();
			image->FillBuffer(0);

			typedef ::itk::BoxSpatialObject<2> MaskType;
			MaskType::Pointer mask = MaskType::New();

			MaskType::SizeType maskSize;
			maskSize[0] = 10;
			maskSize[1] = 15;
			mask->SetSizeInObjectSpace(maskSize);

			ImageType::RegionType region;

			CHECK_THROW(map::algorithm::MaskBoundingBoxHelper<2>::computeBoundingImageRegion(NULL, image,
						region));
			CHECK_THROW(map::algorithm::MaskBoundingBoxHelper<2>::computeBoundingImageRegion(mask, NULL,
						region));
			CHECK_THROW(map::algorithm::MaskBoundingBoxHelper<2>::computeBoundingImageRegion(NULL, NULL,
						region));

			CHECK(map::algorithm::MaskBoundingBoxHelper<2>::computeBoundingImageRegion(mask, image, region));

			CHECK_EQUAL(0, region.GetIndex(0));
			CHECK_EQUAL(27, region.GetIndex(1));
			CHECK_EQUAL(17, region.GetSize(0));
			CHECK_EQUAL(19, region.GetSize(1));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
