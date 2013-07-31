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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapFieldByFieldInversionFunctorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapFieldByModelFunctor.h"
#include "mapFieldByFieldInversionFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapITKScaleTransform.h"

#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{

		int mapFieldByFieldInversionFunctorTest(int argc, char *argv[])
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




			// We need a field, so we build one here using the FieldByModelFunctor
			typedef core::functors::FieldByModelFunctor<2, 2> ModelFunctorType;
			typedef algorithm::itk::ITKTransformModel< itk::ScaleTransform<core::continuous::ScalarType, 2> > TransformType;

			TransformType::Pointer spModel = TransformType::New();

			ModelFunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
			ModelFunctorType::InFieldRepresentationType::PointType origin;
			origin.Fill(0);
			ModelFunctorType::InFieldRepresentationType::SizeType size;
			size.fill(2);
			ModelFunctorType::TransformModelType::ParametersType params(2);
			params.fill(3.0);
			spModel->getTransform()->SetParameters(params);

			ModelFunctorType::InFieldRepresentationType::Pointer spInRep = ModelFunctorType::InFieldRepresentationType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			ModelFunctorType::Pointer spFunc = ModelFunctorType::New(*spModel, spInRep);

			ModelFunctorType::FieldPointer spSourceField = NULL;
			spSourceField = spFunc->generateField();


			// we use the source model for analytic inversion
			TransformType::InverseTransformModelBasePointer spInverseModel; //barra = TransformType::InverseTransformModelType::New();
			spModel->getInverse(spInverseModel);


			// test the FieldByFieldInversionFunctor
			typedef core::functors::FieldByFieldInversionFunctor<2, 2> FieldInversionFunctorType;
			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel PreCachedFieldKernelType;
			PreCachedFieldKernelType::Pointer spSourceKernel = PreCachedFieldKernelType::New();
			spSourceKernel->setField(*(spSourceField.GetPointer()));

			// reuse of spInRep
			FieldInversionFunctorType::Pointer spFieldInversionFunc = FieldInversionFunctorType::New(*spSourceKernel, spInRep);
			spFieldInversionFunc->setStopValue(stopValue);
			spFieldInversionFunc->setNumberOfIterations(nrOfIterations);

			CHECK(spFieldInversionFunc.IsNotNull());

			CHECK(spFieldInversionFunc->getStopValue() == stopValue);
			CHECK(spFieldInversionFunc->getNumberOfIterations() == nrOfIterations);
			CHECK(spSourceKernel == spFieldInversionFunc->getSourceFieldKernel());

			// test CreateAnother
			FieldInversionFunctorType::Pointer spFieldInversionFuncAnother = dynamic_cast<FieldInversionFunctorType *>(spFieldInversionFunc->CreateAnother().GetPointer());
			CHECK(spFieldInversionFuncAnother->getSourceFieldKernel() == spFieldInversionFunc->getSourceFieldKernel());
			CHECK(spFieldInversionFuncAnother->getInFieldRepresentation() == spFieldInversionFunc->getInFieldRepresentation());
			CHECK(spFieldInversionFuncAnother->GetNameOfClass() == spFieldInversionFunc->GetNameOfClass());
			CHECK(spFieldInversionFuncAnother->getStopValue() == spFieldInversionFunc->getStopValue());
			CHECK(spFieldInversionFuncAnother->getNumberOfIterations() == spFieldInversionFunc->getNumberOfIterations());

			// test generateField
			FieldInversionFunctorType::FieldPointer spGeneratedField = NULL;
			CHECK_NO_THROW(spGeneratedField = spFieldInversionFunc->generateField());
			CHECK(spGeneratedField.IsNotNull());

			// use the inverted model spInverseModel to compare results

			lit::TransformFieldTester<FieldInversionFunctorType::FieldType, ModelFunctorType::TransformModelType::TransformBaseType> tester;
			tester.setReferenceTransform(spInverseModel->getTransform());
			tester.setActualField(spGeneratedField);
			tester.setCheckThreshold(checkThreshold);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
