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

#ifndef __MAP_ARTIFACT_GENERATOR_H
#define __MAP_ARTIFACT_GENERATOR_H

#include "mapDiscreteElements.h"
#include "mapFieldRepresentationDescriptor.h"

#include "itkDisplacementFieldTransform.h"

namespace map
{
	namespace testing
	{

		/** generates a vector field by a scaletransform (0.3 x and 0.4 y factor)*/
		::map::core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleField(
			const core::FieldRepresentationDescriptor<2>* pRepDesc);

		/** generates a vector field by a scaletransform (0.3 x and 0.4 y factor) and a NULL vector in the pixel with index (1,1).*/
		::map::core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleFieldWithNull(
			const core::FieldRepresentationDescriptor<2>* pRepDesc,
			const map::core::continuous::Elements<2>::VectorType& nullVector);

    /** generates a vector 2D field. The values of the vector pixels are the sum of the pixel index.
     * Pixel with index (2,4) will have the value (6,6).*/
    ::map::core::discrete::Elements<2>::VectorFieldType::Pointer generate2DSumField(
        const core::FieldRepresentationDescriptor<2>* pRepDesc);

    template<unsigned int VDimension>
    typename ::map::core::discrete::Elements<VDimension>::VectorFieldType::Pointer
        generateSumField(const core::FieldRepresentationDescriptor<VDimension>* pRepDesc)
    {
        typedef typename ::map::core::discrete::Elements<VDimension>::VectorFieldType FieldType;
        typename FieldType::Pointer spField = FieldType::New();

        typedef itk::ImageRegionIterator< FieldType > IteratorType;

        spField->SetRegions(pRepDesc->getRepresentedLocalImageRegion());
        spField->SetOrigin(pRepDesc->getOrigin());
        spField->SetSpacing(pRepDesc->getSpacing());
        spField->SetDirection(pRepDesc->getDirection());
        spField->Allocate();

        IteratorType iterator(spField, spField->GetLargestPossibleRegion());

        for (iterator.GoToBegin(); !(iterator.IsAtEnd()); ++iterator)
        {
            typename FieldType::IndexType index = iterator.GetIndex();
            typename FieldType::ValueType::ValueType element = 0;
            for (unsigned int i = 0; i < VDimension; ++i)
            {
                element += index[i];
            }

            typename FieldType::ValueType value;
            value.Fill(element);

            iterator.Set(value);
        }

        return spField;
    }

    /**Wraps a given field into a displacment transform to be used in kernels*/
    template<unsigned int VDimension>
    typename ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VDimension>::Pointer
        convertFieldToTransform(typename ::map::core::discrete::Elements<VDimension>::VectorFieldType* field)
    {
        ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VDimension>::Pointer transform = ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VDimension>::New();
        transform->SetDisplacementField(field);
        return transform;
    }

    /**Generates a simple field descriptor with a given uniform size and spacing.*/
    template<unsigned int VDimension>
    typename core::FieldRepresentationDescriptor<VDimension>::Pointer
        createSimpleDescriptor(unsigned int sizeValue, double spacingValue)
    {
        typename ::itk::ImageRegion<VDimension>::SizeType size = { sizeValue, sizeValue };
        ::itk::ImageRegion<VDimension> region(size);
        typename ::map::core::continuous::Elements<VDimension>::SpacingType spacing(spacingValue);
        typename map::core::FieldRepresentationDescriptor<VDimension>::Pointer desc = map::core::createFieldRepresentation(region, spacing);

        return desc;
    }

    /**unwraps a field stored in a displacment transform. If not possible returns null.*/
    template<unsigned int VDimension>
    typename ::map::core::discrete::Elements<VDimension>::VectorFieldType::Pointer
        convertTransformToField(typename::itk::Transform<::map::core::continuous::ScalarType, VDimension, VDimension>* transform)
    {
        typedef ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VDimension> FieldTransformType;
        
        FieldTransformType* fieldTransform = dynamic_cast<FieldTransformType*> (transform);

        ::map::core::discrete::Elements<VDimension>::VectorFieldType::Pointer result;

        if (fieldTransform)
        {
            result = fieldTransform->GetDisplacementField();
        }

        return result;
    }

	} // end namespace testing
} // end namespace map

#endif
