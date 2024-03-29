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
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"

#include "itkScaleTransform.h"

#include "mapArtifactGenerator.h"

namespace map
{
	namespace testing
	{

		int mapFieldByModelFunctorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::functors::FieldByModelFunctor<3, 3> FunctorType;


			//Model kernel generation
			typedef itk::ScaleTransform< ::map::core::continuous::ScalarType, 3> ScaleTransformType;

      FunctorType::TransformType::Pointer spModel = ScaleTransformType::New().GetPointer();

			FunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
			FunctorType::InFieldRepresentationType::PointType origin;
			origin.Fill(0);
			FunctorType::InFieldRepresentationType::SizeType size;
			size.fill(2);
      FunctorType::TransformType::ParametersType params(3);
			params.fill(2.0);
			spModel->SetParameters(params);

			FunctorType::InFieldRepresentationType::Pointer spInRep =
				FunctorType::InFieldRepresentationType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			FunctorType::Pointer spFunc = FunctorType::New(spModel, spInRep);


			CHECK(spFunc.IsNotNull());

      CHECK(spModel == spFunc->getSourceTransformModel());

			FunctorType::Pointer spFuncAnother = dynamic_cast<FunctorType*>
												 (spFunc->CreateAnother().GetPointer());
      CHECK(spFuncAnother->getSourceTransformModel() == spFunc->getSourceTransformModel());
			CHECK(spFuncAnother->getInFieldRepresentation() == spFunc->getInFieldRepresentation());
			CHECK(spFuncAnother->GetNameOfClass() == spFunc->GetNameOfClass());

			// test generateField

      FunctorType::TransformPointer spFieldTransform;
      CHECK_NO_THROW(spFieldTransform = spFunc->generateTransform());
      CHECK(spFieldTransform.IsNotNull());
      FunctorType::FieldType::Pointer spField = testing::unwrapTransformField(spFieldTransform.GetPointer());

      lit::TransformFieldTester<FunctorType::FieldType, FunctorType::TransformType>
			tester;
			tester.setReferenceTransform(spModel);
			tester.setActualField(spField);
			tester.setCheckThreshold(0.0);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
