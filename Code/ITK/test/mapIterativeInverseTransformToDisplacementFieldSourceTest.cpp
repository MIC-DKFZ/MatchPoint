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

#include "mapIterativeInverseTransformToDisplacementFieldSource.h"
#include "mapContinuousElements.h"
#include "mapDiscreteElements.h"

#include "litTransformFieldTester.h"
#include "litCheckMacros.h"

#include "itkImage.h"
#include "itkScaleTransform.h"


namespace map
{
	namespace testing
	{

		int mapIterativeInverseTransformToDisplacementFieldSourceTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: Number of iterations
			//           2: Stop value
			//           3: Check threshold

			PREPARE_DEFAULT_TEST_REPORTING;

			unsigned int nrOfIterations = 40;
			double stopValue = 0.1;
			double checkThreshold = 0.1;

			if (argc > 1)
			{
				std::istringstream istream;
				istream.str(argv[1]);
				istream >> nrOfIterations;
			}

			if (argc > 2)
			{
				std::istringstream istream;
				istream.str(argv[2]);
				istream >> stopValue;
			}

			if (argc > 3)
			{
				std::istringstream istream;
				istream.str(argv[3]);
				istream >> checkThreshold;
			}

			typedef core::discrete::Elements<2>::VectorFieldType VectorFieldType;

			typedef itk::map::IterativeInverseTransformToDisplacementFieldSource<VectorFieldType, core::continuous::ScalarType>
			FieldSourceType;

			typedef itk::ScaleTransform<map::core::continuous::ScalarType, 2> TransformType;

			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params.fill(3.0);
			spTransform->SetParameters(params);

			VectorFieldType::SpacingType spacing(0.5);
			VectorFieldType::PointType origin;
			origin.Fill(0);
			VectorFieldType::SizeType size;
			size.Fill(20);

			FieldSourceType::Pointer spFieldSource = FieldSourceType::New();

			spFieldSource->SetTransform(spTransform.GetPointer());
			CHECK_EQUAL(spTransform.GetPointer(), spFieldSource->GetTransform());

			spFieldSource->SetSpacing(spacing);
			CHECK_EQUAL(spacing, spFieldSource->GetSpacing());

			spFieldSource->SetSize(size);
			CHECK_EQUAL(size, spFieldSource->GetSize());

			spFieldSource->SetOrigin(origin);
			CHECK_EQUAL(origin, spFieldSource->GetOrigin());

			spFieldSource->SetNumberOfIterations(nrOfIterations);
			spFieldSource->SetStopValue(stopValue);

			VectorFieldType::Pointer spField = spFieldSource->GetOutput();
			spFieldSource->Update();
			CHECK(spField.IsNotNull());
			CHECK_EQUAL(spacing, spField->GetSpacing());
			CHECK_EQUAL(size, spField->GetLargestPossibleRegion().GetSize());
			CHECK_EQUAL(origin, spField->GetOrigin());

			//invert transform
			TransformType::Pointer spInverseTransform = TransformType::New();
			spTransform->GetInverse(spInverseTransform);

			lit::TransformFieldTester<VectorFieldType, TransformType> tester;
			tester.setReferenceTransform(spInverseTransform);
			tester.setActualField(spField);
			tester.setCheckThreshold(checkThreshold);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
