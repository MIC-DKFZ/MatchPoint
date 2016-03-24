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

#include "mapFieldRepresentationDescriptor.h"
#include "mapSDXMLStrWriter.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		int mapFieldRepresentationDescriptorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			//Prepration
			::map::core::FieldRepresentationDescriptor<2>::SpacingType defaultSpacing;
			defaultSpacing.Fill(0.0);

			::map::core::FieldRepresentationDescriptor<2>::PointType defaultOrigin;
			defaultOrigin.Fill(0.0);

			::map::core::FieldRepresentationDescriptor<2>::SizeType defaultSize;
			defaultSize.fill(0.0);

			::map::core::FieldRepresentationDescriptor<2>::SpacingType spacing;
			spacing.Fill(0.5);

			::map::core::FieldRepresentationDescriptor<2>::PointType origin;
			origin.SetElement(0, 0);
			origin.SetElement(1, 5);

			::map::core::FieldRepresentationDescriptor<2>::SizeType size;
			size.setElement(0, 10);
			size.setElement(1, 15);

			::map::core::FieldRepresentationDescriptor<2>::VolumeType volume(origin, size);

			::map::core::FieldRepresentationDescriptor<2>::ImageRegionType::IndexType regionIndex;
			regionIndex[0] = 0;
			regionIndex[1] = 3;

			::map::core::FieldRepresentationDescriptor<2>::PointType regionOrigin;
			regionOrigin.SetElement(0, regionIndex[0]*spacing[0]);
			regionOrigin.SetElement(1, regionIndex[1]*spacing[1]);

			::map::core::FieldRepresentationDescriptor<2>::ImageRegionType::IndexType localIndex;
			localIndex[0] = 0;
			localIndex[1] = 0;

			::map::core::FieldRepresentationDescriptor<2>::ImageRegionType::SizeType regionSize;
			regionSize[0] = 5;
			regionSize[1] = 8;

			::map::core::FieldRepresentationDescriptor<2>::DirectionType direct1;
			::map::core::FieldRepresentationDescriptor<2>::DirectionType direct2;
			direct1.SetIdentity();
			direct2.SetIdentity();
			direct2.GetVnlMatrix().put(0, 0, 2);

			::map::core::FieldRepresentationDescriptor<2>::ImageRegionType localRegion(localIndex, regionSize);

			//Testing setter and getter
			::map::core::FieldRepresentationDescriptor<2>::Pointer spFRD =
				::map::core::FieldRepresentationDescriptor<2>::New();

			CHECK_ARRAY_EQUAL(spFRD->getSize(), defaultSize, 2);
			CHECK_ARRAY_EQUAL(spFRD->getOrigin(), defaultOrigin, 2);
			CHECK_ARRAY_EQUAL(spFRD->getSpacing(), defaultSpacing, 2);
			CHECK(spFRD->getDirection() == direct1);

			CHECK_NO_THROW(spFRD->setSize(size));
			CHECK_NO_THROW(spFRD->setOrigin(origin));
			CHECK_NO_THROW(spFRD->setSpacing(spacing));
			CHECK_NO_THROW(spFRD->setDirection(direct2));

			CHECK_ARRAY_EQUAL(spFRD->getSize(), size, 2);
			CHECK_ARRAY_EQUAL(spFRD->getOrigin(), origin, 2);
			CHECK_ARRAY_EQUAL(spFRD->getSpacing(), spacing, 2);
			CHECK(spFRD->getDirection() == direct2);

			//Testing streaming
			structuredData::Element::Pointer spSDElement;
			CHECK_NO_THROW(spSDElement = spFRD->streamToStructuredData());
			structuredData::XMLStrWriter::Pointer xmlStrWriter = structuredData::XMLStrWriter::New();

			::map::core::String frdStr = xmlStrWriter->write(spSDElement);
			::map::core::String refStr =
				"<FieldRepresentationDescriptor Dimensions='2'><Size><Value Row='0'>10.00000000</Value><Value Row='1'>15.00000000</Value></Size><Origin><Value Row='0'>0.0000000000</Value><Value Row='1'>5.000000000</Value></Origin><Spacing><Value Row='0'>0.5000000000</Value><Value Row='1'>0.5000000000</Value></Spacing><Direction><Value Column='0' Row='0'>2.000000000</Value><Value Column='1' Row='0'>0.0000000000</Value><Value Column='0' Row='1'>0.0000000000</Value><Value Column='1' Row='1'>1.000000000</Value></Direction></FieldRepresentationDescriptor>";

			CHECK_EQUAL(refStr, frdStr);

			::map::core::FieldRepresentationDescriptor<2>::Pointer spFRDClone =
				::map::core::FieldRepresentationDescriptor<2>::New();
			CHECK_NO_THROW(spFRDClone->streamFromStructuredData(spSDElement));

			CHECK((*spFRD) == (*spFRDClone));

			::map::core::FieldRepresentationDescriptor<3>::Pointer spFRD_wrongDim =
				::map::core::FieldRepresentationDescriptor<3>::New();
			CHECK_THROW(spFRD_wrongDim->streamFromStructuredData(spSDElement));

			//Testing other functions
			spFRD->setDirection(direct1);

			::map::core::FieldRepresentationDescriptor<2>::Pointer spFRDbyRegion = core::createFieldRepresentation(
						localRegion, spacing);

			/*! @TODO Add correct test for new getRepresentedLocalImageRegion */
			//CHECK_EQUAL(localRegion,spFRDbyRegion->getRepresentedLocalImageRegion(regionOrigin));
			CHECK_EQUAL(localRegion, spFRDbyRegion->getRepresentedLocalImageRegion());

			::map::core::FieldRepresentationDescriptor<2>::Pointer spFRDbyVolume = core::createFieldRepresentation(
						volume, spacing);

			CHECK_EQUAL(volume, spFRDbyVolume->getRepresentedVolume());

			CHECK((*spFRDbyVolume) == (*spFRDbyVolume));
			CHECK(!((*spFRDbyVolume) == (*spFRDbyRegion)));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
