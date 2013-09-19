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

#include "mapFieldByModelInversionFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"

#include "mapITKScaleTransform.h"

#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{

		int mapFieldByModelInversionFunctorTest(int argc, char* argv[])
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

			typedef core::functors::FieldByModelInversionFunctor<2, 2> FunctorType;
			typedef algorithm::itk::ITKTransformModel< itk::ScaleTransform<core::continuous::ScalarType, 2> >
			TransformType;

			TransformType::Pointer spModel = TransformType::New();

			FunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
			FunctorType::InFieldRepresentationType::PointType origin;
			origin.Fill(0);
			FunctorType::InFieldRepresentationType::SizeType size;
			size.fill(10);
			FunctorType::TransformModelType::ParametersType params(2);
			params.fill(3.0);
			spModel->getTransform()->SetParameters(params);

			FunctorType::InFieldRepresentationType::Pointer spInRep =
				FunctorType::InFieldRepresentationType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			FunctorType::Pointer spFunc = FunctorType::New(*spModel, spInRep);
			spFunc->setStopValue(stopValue);
			spFunc->setNumberOfIterations(nrOfIterations);

			CHECK(spFunc.IsNotNull());

			CHECK(spFunc->getStopValue() == stopValue);
			CHECK(spFunc->getNumberOfIterations() == nrOfIterations);
			CHECK(spModel == spFunc->getTransformModel());

			FunctorType::Pointer spFuncAnother = dynamic_cast<FunctorType*>
												 (spFunc->CreateAnother().GetPointer());
			CHECK(spFuncAnother->getTransformModel() == spFunc->getTransformModel());
			CHECK(spFuncAnother->getInFieldRepresentation() == spFunc->getInFieldRepresentation());
			CHECK(spFuncAnother->GetNameOfClass() == spFunc->GetNameOfClass());
			CHECK(spFuncAnother->getStopValue() == spFunc->getStopValue());
			CHECK(spFuncAnother->getNumberOfIterations() == spFunc->getNumberOfIterations());

			// test generateField
			FunctorType::FieldPointer spField = NULL;
			CHECK_NO_THROW(spField = spFunc->generateField());
			CHECK(spField.IsNotNull());

			TransformType::InverseTransformModelBasePointer
			spInverseModel; //barra = TransformType::InverseTransformModelType::New();
			spModel->getInverse(spInverseModel);


			lit::TransformFieldTester<FunctorType::FieldType, FunctorType::TransformModelType::TransformBaseType>
			tester;
			tester.setReferenceTransform(spInverseModel->getTransform());
			tester.setActualField(spField);
			tester.setCheckThreshold(checkThreshold);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
