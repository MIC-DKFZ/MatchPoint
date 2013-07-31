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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapPreCachedFieldBasedRegistrationKernelTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapFieldBasedRegistrationKernels.h"
#include "litCheckMacros.h"
#include "itkImage.h"
#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{
		typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel KernelType;

		KernelType::FieldType::Pointer generateField()
		{
			KernelType::FieldType::Pointer spField = KernelType::FieldType::New();

			typedef itk::ImageRegionIterator< KernelType::FieldType > IteratorType;

			KernelType::FieldType::RegionType::SizeType size = {10, 10};
			KernelType::FieldType::RegionType region(size);
			KernelType::FieldType::SpacingType spacing(0.5);
			//Generate imagegrid
			spField->SetRegions(region);
			spField->SetSpacing(spacing);
			spField->Allocate();

			IteratorType iterator(spField, spField->GetLargestPossibleRegion());

			for (iterator.GoToBegin(); !(iterator.IsAtEnd()); ++iterator)
			{
				KernelType::FieldType::IndexType index = iterator.GetIndex();
				KernelType::FieldType::ValueType value;
				value.Fill(index[0] + index[1]);

				iterator.Set(value);
			}

			return spField;
		}

		int mapPreCachedFieldBasedRegistrationKernelTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			KernelType::Pointer spKernel = KernelType::New();
			KernelType::FieldType::Pointer spField = generateField();

			spKernel->setField(*(spField.GetPointer()));

			KernelType::InputPointType inPoint;
			inPoint.Fill(2);
			KernelType::OutputPointType referencePoint;
			referencePoint.Fill(10);

			KernelType::InputPointType inPoint2;
			inPoint2.Fill(3.5);
			KernelType::OutputPointType referencePoint2;
			referencePoint2.Fill(17.5);

			KernelType::InputPointType invalidInPoint;
			invalidInPoint.Fill(50);
			KernelType::OutputPointType invalidReferencePoint;
			invalidReferencePoint.Fill(0.0);

			KernelType::OutputPointType resultPoint;

			KernelType::RepresentationDescriptorPointer spReferenceFieldRepresentation = core::createFieldRepresentation(*(spField.GetPointer()));

			CHECK_EQUAL(spField.GetPointer(), spKernel->getField());
			CHECK_EQUAL(true, spKernel->hasLimitedRepresentation());

			KernelType::RepresentationDescriptorConstPointer spFieldRepresentation = spKernel->getLargestPossibleRepresentation();
			CHECK(*(spReferenceFieldRepresentation.GetPointer()) == *(spFieldRepresentation.GetPointer()));

			//reset result
			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);
			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint2, resultPoint));
			CHECK_EQUAL(referencePoint2, resultPoint);
			resultPoint.Fill(11);
			CHECK_EQUAL(false, spKernel->mapPoint(invalidInPoint, resultPoint));
			CHECK_EQUAL(invalidReferencePoint, resultPoint);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
