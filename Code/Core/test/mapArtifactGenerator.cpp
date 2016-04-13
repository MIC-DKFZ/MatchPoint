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
#include "mapITKScaleTransform.h"
#include "mapFieldByModelFunctor.h"

namespace map
{
	namespace testing
	{

		::map::core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleField(
			const core::FieldRepresentationDescriptor<2>* pRepDesc)
		{
			//Model kernel generation
			typedef itk::ScaleTransform< ::map::core::continuous::ScalarType, 2> TransformType;

			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(2);
			params[0] = 0.3;
			params[1] = 0.4;
			spTransform->SetParameters(params);

      ::map::core::discrete::Elements<2>::VectorFieldType::Pointer spField = core::generateFieldFromTransform<2, 2>(spTransform, pRepDesc); 
      
			return spField;
		}

		::map::core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleFieldWithNull(
			const core::FieldRepresentationDescriptor<2>* pRepDesc,
			const map::core::continuous::Elements<2>::VectorType& nullVector)
		{

			::map::core::discrete::Elements<2>::VectorFieldType::Pointer spField = generate2DScaleField(pRepDesc);

			::map::core::discrete::Elements<2>::VectorFieldType::IndexType index;
			index.Fill(1);
			spField->SetPixel(index, nullVector);

			return spField;
		}

    ::map::core::discrete::Elements<2>::VectorFieldType::Pointer generate2DSumField(
        const core::FieldRepresentationDescriptor<2>* pRepDesc)
    {
        return generateSumField<2>(pRepDesc);
    }

	} //namespace testing
} //namespace map
