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

#include "mapArtifactGenerator.h"
#include "mapITKUnaryTransformModel.h"
#include "mapITKScaleTransform.h"
#include "mapFieldByModelFunctor.h"

namespace map
{
	namespace testing
	{

		core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleField(
			const core::FieldRepresentationDescriptor<2>* pRepDesc)
		{
			//Model kernel generation
			typedef algorithm::itk::ITKTransformModel< itk::ScaleTransform<core::continuous::ScalarType, 2> >
			TransformType;

			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 0.3;
			params[1] = 0.4;
			spTransform->getTransform()->SetParameters(params);

			typedef core::functors::FieldByModelFunctor<2, 2> FunctorType;
			FunctorType::Pointer spFieldFunctor = FunctorType::New(*spTransform, pRepDesc);
			//uses this functor to generate the test field
			FunctorType::FieldPointer spField = spFieldFunctor->generateField();

			return spField;
		}

		core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleFieldWithNull(
			const core::FieldRepresentationDescriptor<2>* pRepDesc,
			const map::core::continuous::Elements<2>::VectorType& nullVector)
		{

			core::discrete::Elements<2>::VectorFieldType::Pointer spField = generate2DScaleField(pRepDesc);

			core::discrete::Elements<2>::VectorFieldType::IndexType index;
			index.Fill(1);
			spField->SetPixel(index, nullVector);

			return spField;
		}
	} //namespace testing
} //namespace map
