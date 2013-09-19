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

#include "mapFieldRepresentationDescriptor.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		int mapFieldRepresentationDescriptorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			//Prepration
			core::FieldRepresentationDescriptor<2>::SpacingType spacing;
			spacing.Fill(0.5);

			core::FieldRepresentationDescriptor<2>::PointType origin;
			origin.SetElement(0, 0);
			origin.SetElement(1, 5);

			core::FieldRepresentationDescriptor<2>::SizeType size;
			size.setElement(0, 10);
			size.setElement(1, 15);

			core::FieldRepresentationDescriptor<2>::VolumeType volume(origin, size);

			core::FieldRepresentationDescriptor<2>::ImageRegionType::IndexType regionIndex;
			regionIndex[0] = 0;
			regionIndex[1] = 3;

			core::FieldRepresentationDescriptor<2>::PointType regionOrigin;
			regionOrigin.SetElement(0, regionIndex[0]*spacing[0]);
			regionOrigin.SetElement(1, regionIndex[1]*spacing[1]);

			core::FieldRepresentationDescriptor<2>::ImageRegionType::IndexType localIndex;
			localIndex[0] = 0;
			localIndex[1] = 0;

			core::FieldRepresentationDescriptor<2>::ImageRegionType::SizeType regionSize;
			regionSize[0] = 5;
			regionSize[1] = 8;

			core::FieldRepresentationDescriptor<2>::DirectionType direct1;
			core::FieldRepresentationDescriptor<2>::DirectionType direct2;
			direct1.SetIdentity();
			direct2.SetIdentity();
			direct2.GetVnlMatrix().put(0, 0, 2);

			core::FieldRepresentationDescriptor<2>::ImageRegionType localRegion(localIndex, regionSize);

			//Testing
			core::FieldRepresentationDescriptor<2>::Pointer spFRD =
				core::FieldRepresentationDescriptor<2>::New();

			CHECK_NO_THROW(spFRD->setSize(size));
			CHECK_NO_THROW(spFRD->setOrigin(origin));
			CHECK_NO_THROW(spFRD->setSpacing(spacing));
			CHECK_NO_THROW(spFRD->setDirection(direct2));

			CHECK_ARRAY_EQUAL(spFRD->getSize(), size, 2);
			CHECK_ARRAY_EQUAL(spFRD->getOrigin(), origin, 2);
			CHECK_ARRAY_EQUAL(spFRD->getSpacing(), spacing, 2);
			CHECK(spFRD->getDirection() == direct2);

			spFRD->setDirection(direct1);

			core::FieldRepresentationDescriptor<2>::Pointer spFRDbyRegion = core::createFieldRepresentation(
						localRegion, spacing);

			/*! @TODO Add correct test for new getRepresentedLocalImageRegion */
			//CHECK_EQUAL(localRegion,spFRDbyRegion->getRepresentedLocalImageRegion(regionOrigin));
			CHECK_EQUAL(localRegion, spFRDbyRegion->getRepresentedLocalImageRegion());

			core::FieldRepresentationDescriptor<2>::Pointer spFRDbyVolume = core::createFieldRepresentation(
						volume, spacing);

			CHECK_EQUAL(volume, spFRDbyVolume->getRepresentedVolume());

			CHECK((*spFRDbyVolume) == (*spFRDbyVolume));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
