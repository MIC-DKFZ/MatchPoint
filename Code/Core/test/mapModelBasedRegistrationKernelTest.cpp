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

#include "mapModelBasedRegistrationKernel.h"
#include "litCheckMacros.h"
#include "mapITKTranslationTransform.h"

#include "itkTranslationTransform.h"

namespace map
{
	namespace testing
	{

		int mapModelBasedRegistrationKernelTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::ModelBasedRegistrationKernel<2, 2> KernelType;
			typedef algorithm::itk::ITKTransformModel< itk::TranslationTransform<core::continuous::ScalarType, 2> >
			TransformType;

			KernelType::Pointer spKernel = KernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 5;
			params[1] = -5;
			spTransform->getTransform()->SetParameters(params);

			spKernel->setTransformModel(spTransform);

			KernelType::InputPointType inPoint;
			inPoint.Fill(0);
			KernelType::OutputPointType referencePoint = spTransform->getTransform()->TransformPoint(inPoint);

			KernelType::InputVectorType inVector;
			inVector.Fill(4);
			KernelType::OutputVectorType referenceVector = spTransform->getTransform()->TransformVector(
						inVector);

			KernelType::OutputVectorType resultVector;
			KernelType::OutputPointType resultPoint;

			CHECK_EQUAL(false, spKernel->hasLimitedRepresentation());
			CHECK_EQUAL(true, spKernel->getLargestPossibleRepresentation().IsNull());
			CHECK_EQUAL(spTransform.GetPointer(), spKernel->getTransformModel());
			CHECK_EQUAL(params, spKernel->getParameters());
			CHECK_EQUAL(spTransform->GetNameOfClass(), spKernel->getModelName());

			resultPoint = spKernel->transformPoint(inPoint);
			CHECK_EQUAL(referencePoint, resultPoint);

			resultVector = spKernel->transformVector(inVector);
			CHECK_EQUAL(referenceVector, resultVector);

			//reset result
			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
