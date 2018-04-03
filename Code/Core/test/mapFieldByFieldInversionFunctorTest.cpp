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

#include "mapFieldByModelFunctor.h"
#include "mapFieldByFieldInversionFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapArtifactGenerator.h"

#include "itkScaleTransform.h"
#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{

		int mapFieldByFieldInversionFunctorTest(int argc, char* argv[])
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
			typedef itk::ScaleTransform< ::map::core::continuous::ScalarType, 2> TransformType;

			TransformType::Pointer spModel = TransformType::New();

			ModelFunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
			ModelFunctorType::InFieldRepresentationType::PointType origin;
			origin.Fill(0);
			ModelFunctorType::InFieldRepresentationType::SizeType size;
			size.fill(2);
			ModelFunctorType::TransformType::ParametersType params(2);
			params.fill(3.0);
			spModel->SetParameters(params);

			ModelFunctorType::InFieldRepresentationType::Pointer spInRep =
				ModelFunctorType::InFieldRepresentationType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			ModelFunctorType::Pointer spFunc = ModelFunctorType::New(spModel, spInRep);

			ModelFunctorType::TransformPointer spSourceFieldTransform = NULL;
			spSourceFieldTransform = spFunc->generateTransform();


			// we use the source model for analytic inversion
			TransformType::InverseTransformBasePointer
			spInverseModel = spModel->GetInverseTransform();


			// test the FieldByFieldInversionFunctor
			typedef core::functors::FieldByFieldInversionFunctor<2, 2> FieldInversionFunctorType;
			typedef core::PreCachedRegistrationKernel<2,2> PreCachedKernelType;
			PreCachedKernelType::Pointer spSourceKernel = PreCachedKernelType::New();
			spSourceKernel->setTransformModel(spSourceFieldTransform.GetPointer());

			// reuse of spInRep
			FieldInversionFunctorType::Pointer spFieldInversionFunc = FieldInversionFunctorType::New(
						spSourceKernel, spInRep);
			spFieldInversionFunc->setStopValue(stopValue);
			spFieldInversionFunc->setNumberOfIterations(nrOfIterations);

			CHECK(spFieldInversionFunc.IsNotNull());

			CHECK(spFieldInversionFunc->getStopValue() == stopValue);
			CHECK(spFieldInversionFunc->getNumberOfIterations() == nrOfIterations);
			CHECK(spSourceKernel == spFieldInversionFunc->getSourceFieldKernel());

			// test CreateAnother
			FieldInversionFunctorType::Pointer spFieldInversionFuncAnother =
				dynamic_cast<FieldInversionFunctorType*>(spFieldInversionFunc->CreateAnother().GetPointer());
			CHECK(spFieldInversionFuncAnother->getSourceFieldKernel() ==
				  spFieldInversionFunc->getSourceFieldKernel());
			CHECK(spFieldInversionFuncAnother->getInFieldRepresentation() ==
				  spFieldInversionFunc->getInFieldRepresentation());
			CHECK(spFieldInversionFuncAnother->GetNameOfClass() == spFieldInversionFunc->GetNameOfClass());
			CHECK(spFieldInversionFuncAnother->getStopValue() == spFieldInversionFunc->getStopValue());
			CHECK(spFieldInversionFuncAnother->getNumberOfIterations() ==
				  spFieldInversionFunc->getNumberOfIterations());

			// test generateField
      FieldInversionFunctorType::TransformPointer spGeneratedFieldTransform = NULL;
      CHECK_NO_THROW(spGeneratedFieldTransform = spFieldInversionFunc->generateTransform());
      CHECK(spGeneratedFieldTransform.IsNotNull());
      FieldInversionFunctorType::FieldType::Pointer spGeneratedField = testing::unwrapTransformField(spGeneratedFieldTransform.GetPointer());

			// use the inverted model spInverseModel to compare results

			lit::TransformFieldTester<FieldInversionFunctorType::FieldType, ModelFunctorType::TransformType>
			tester;
			tester.setReferenceTransform(spInverseModel);
			tester.setActualField(spGeneratedField);
			tester.setCheckThreshold(checkThreshold);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
