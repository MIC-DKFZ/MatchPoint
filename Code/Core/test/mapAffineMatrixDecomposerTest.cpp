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

#include "mapPreCachedRegistrationKernel.h"
#include "litCheckMacros.h"
#include "mapITKTranslationTransform.h"
#include "mapAffineMatrixDecomposer.h"

#include "itkDisplacementFieldTransform.h"

namespace map
{
	namespace testing
	{

		int mapAffineMatrixDecomposerTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::AffineMatrixDecomposer<2, 2> DecomposerType;

			typedef core::PreCachedRegistrationKernel<2, 2> KernelType;
			typedef ::itk::TranslationTransform<::map::core::continuous::ScalarType, 2> TransformType;
      typedef ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, 2> FieldTransformType;

			KernelType::Pointer spKernel = KernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 5;
			params[1] = -5;
			spTransform->SetParameters(params);

			spKernel->setTransformModel(spTransform);

      KernelType::Pointer spFieldKernel = KernelType::New();
      spKernel->setTransformModel(FieldTransformType::New().GetPointer());

			DecomposerType::MatrixType matrix;
			DecomposerType::OffsetType offset;

			CHECK_EQUAL(true, DecomposerType::decomposeKernel(spKernel, matrix, offset));
			CHECK_EQUAL(5, offset[0]);
			CHECK_EQUAL(-5, offset[1]);
			CHECK_EQUAL(1, matrix[0][0]);
			CHECK_EQUAL(0, matrix[1][0]);
			CHECK_EQUAL(0, matrix[0][1]);
			CHECK_EQUAL(1, matrix[1][1]);

			CHECK_EQUAL(false, DecomposerType::decomposeKernel(spFieldKernel, matrix, offset));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
