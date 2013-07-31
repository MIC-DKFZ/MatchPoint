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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapAffineMatrixDecomposerTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapModelBasedRegistrationKernel.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "litCheckMacros.h"
#include "mapITKTranslationTransform.h"
#include "mapAffineMatrixDecomposer.h"

namespace map
{
	namespace testing
	{

		int mapAffineMatrixDecomposerTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::AffineMatrixDecomposer<2, 2> DecomposerType;

			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;
			typedef algorithm::itk::ITKTransformModel< itk::TranslationTransform<core::continuous::ScalarType, 2> > TransformType;
			typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel FieldKernelType;

			ModelKernelType::Pointer spKernel = ModelKernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 5;
			params[1] = -5;
			spTransform->getTransform()->SetParameters(params);

			spKernel->setTransformModel(spTransform);

			FieldKernelType::Pointer spFieldKernel = FieldKernelType::New();


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
