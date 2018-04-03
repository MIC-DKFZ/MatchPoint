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

#include "mapFieldByFileLoadFunctor.h"
#include "litCheckMacros.h"
#include "litFieldTester.h"
#include "mapLazyRegistrationKernel.h"
#include "mapFieldDecomposer.h"

#include "itkImageRegionIterator.h"
#include "itkImageFileReader.h"

namespace map
{
	namespace testing
	{

		int mapFieldByFileLoadFunctorTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: test field file

			PREPARE_DEFAULT_TEST_REPORTING;

			::map::core::String filePath = "";
			double checkThreshold = 0.1;

			if (argc > 1)
			{
				std::istringstream istream;
				istream.str(argv[1]);
				istream >> filePath;
			}

			if (argc > 2)
			{
				std::istringstream istream;
				istream.str(argv[2]);
				istream >> checkThreshold;
			}

			typedef core::functors::FieldByFileLoadFunctor<2, 2> FieldFunctorType;
			FieldFunctorType::Pointer spFieldFunc = FieldFunctorType::New(filePath, NULL);

			CHECK(spFieldFunc.IsNotNull());

			CHECK(spFieldFunc->getFieldFilePath() == filePath);

			// test CreateAnother
			FieldFunctorType::Pointer spFieldFuncAnother = dynamic_cast<FieldFunctorType*>
					(spFieldFunc->CreateAnother().GetPointer());
			CHECK(spFieldFuncAnother->getInFieldRepresentation() == spFieldFunc->getInFieldRepresentation());
			CHECK(spFieldFuncAnother->GetNameOfClass() == spFieldFunc->GetNameOfClass());
			CHECK(spFieldFuncAnother->getFieldFilePath() == spFieldFunc->getFieldFilePath());

			// test generateTransform
			FieldFunctorType::FieldType::Pointer spGeneratedField = NULL;
      FieldFunctorType::TransformPointer spGeneratedFieldTransform = NULL;
      CHECK_NO_THROW(spGeneratedFieldTransform = spFieldFunc->generateTransform());
      ::map::core::FieldDecomposer<2, 2>::decomposeTransform(spGeneratedFieldTransform, spGeneratedField);
      CHECK(spGeneratedField.IsNotNull());

			typedef ::itk::ImageFileReader<FieldFunctorType::FieldType> ReaderType;
			ReaderType::Pointer spReader = ReaderType::New();
			spReader->SetFileName(filePath);
			FieldFunctorType::FieldType::Pointer spRefField = spReader->GetOutput();
			spReader->Update();

      //test the fields

			lit::FieldTester<FieldFunctorType::FieldType> tester;
			tester.setExpectedField(spRefField);
			tester.setActualField(spGeneratedField);
			tester.setCheckThreshold(checkThreshold);

			CHECK_TESTER(tester);

			//test invalid path
			FieldFunctorType::Pointer spInvalidFieldFunc = FieldFunctorType::New("lalalal", NULL);
      CHECK_THROW_EXPLICIT(spGeneratedFieldTransform = spInvalidFieldFunc->generateTransform(),
								 ::itk::ExceptionObject);


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
