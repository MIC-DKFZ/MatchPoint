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
// @version $Revision: 1287 $ (last changed revision)
// @date    $Date: 2016-04-01 18:02:24 +0200 (Fr, 01 Apr 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/Core/include/mapFieldDecomposer.tpp $
*/

#ifndef __FIELD_DECOMPOSER_TPP
#define __FIELD_DECOMPOSER_TPP

#include "mapFieldDecomposer.h"
#include "mapRegistrationKernel.h"
#include "mapGenericVectorFieldTransform.h"
#include "itkDisplacementFieldTransform.h"

namespace map
{
    namespace core
    {

        /** Convinience helper to extract a vector field out of transforms/kernel
        * if they are basead on a field..*/
        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        struct FieldDecomposerHelper
        {
        public:

            typedef typename FieldDecomposer<VInputDimensions, VOutputDimensions>::TransformType TransformType;
            typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectFieldType FieldType;
            typedef typename FieldType::ConstPointer FieldConstPointer;
            typedef typename FieldType::Pointer FieldPointer;

            static bool decomposeTransform(const TransformType* pTransform, FieldConstPointer& field)
            {
                bool result = false;
                typedef ::itk::GenericVectorFieldTransform<::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> GenericFieldTransformType;

                const GenericFieldTransformType* castedGenericFieldTransform = dynamic_cast<const GenericFieldTransformType*>(pTransform);
                if (castedGenericFieldTransform)
                { //try to directly use the field
                    field = dynamic_cast<const FieldType*>(castedGenericFieldTransform->GetDisplacementField());
                    result = true;
                }

                return result;
            };

            static bool decomposeTransform(TransformType* pTransform, FieldPointer& field)
            {
                bool result = false;
                typedef ::itk::GenericVectorFieldTransform<::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> GenericFieldTransformType;

                GenericFieldTransformType* castedGenericFieldTransform = dynamic_cast<GenericFieldTransformType*>(pTransform);
                if (castedGenericFieldTransform)
                { //try to directly use the field
                    field = dynamic_cast<const FieldType*>(castedGenericFieldTransform->GetDisplacementField());
                    result = true;
                }

                return result;
            };

        };

        /** Convinience helper to extract a vector field out of transforms/kernel
        * if they are basead on a field..*/
        template<unsigned int VDimensions>
        struct FieldDecomposerHelper<VDimensions, VDimensions>
        {
        public:
            typedef typename FieldDecomposer<VDimensions, VDimensions>::TransformType TransformType;
            typedef typename RegistrationTopology<VDimensions, VDimensions>::DirectFieldType FieldType;
            typedef typename FieldType::ConstPointer FieldConstPointer;
            typedef typename FieldType::Pointer FieldPointer;

            static bool decomposeTransform(const TransformType* pTransform, FieldConstPointer& field)
            {
                bool result = false;
                typedef ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VDimensions> FieldTransformType;
                typedef ::itk::GenericVectorFieldTransform<::map::core::continuous::ScalarType, VDimensions, VDimensions> GenericFieldTransformType;

                const FieldTransformType* castedFieldTransform = dynamic_cast<const FieldTransformType*>(pTransform);
                const GenericFieldTransformType* castedGenericFieldTransform = dynamic_cast<const GenericFieldTransformType*>(pTransform);
                if (castedFieldTransform)
                { //try to directly use the field
                    field = dynamic_cast<const FieldType*>(castedFieldTransform->GetDisplacementField());
                    result = true;
                }
                else if (castedGenericFieldTransform)
                { //try to directly use the field
                    field = dynamic_cast<const FieldType*>(castedGenericFieldTransform->GetDisplacementField());
                    result = true;
                }

                return result;
            };

            static bool decomposeTransform(TransformType* pTransform, FieldPointer& field)
            {
                bool result = false;
                typedef ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VDimensions> FieldTransformType;
                typedef ::itk::GenericVectorFieldTransform<::map::core::continuous::ScalarType, VDimensions, VDimensions> GenericFieldTransformType;

                FieldTransformType* castedFieldTransform = dynamic_cast<FieldTransformType*>(pTransform);
                GenericFieldTransformType* castedGenericFieldTransform = dynamic_cast<GenericFieldTransformType*>(pTransform);
                if (castedFieldTransform)
                { //try to directly use the field
                    field = dynamic_cast<const FieldType*>(castedFieldTransform->GetDisplacementField());
                    result = true;
                }
                else if (castedGenericFieldTransform)
                { //try to directly use the field
                    field = dynamic_cast<const FieldType*>(castedGenericFieldTransform->GetDisplacementField());
                    result = true;
                }

                return result;
            };

        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            FieldDecomposer<VInputDimensions, VOutputDimensions>::
            decomposeTransform(const TransformType* pTransform, FieldConstPointer& field)
        {
            if (!pTransform)
            {
                mapDefaultExceptionStaticMacro(<<
                    "Error decomposing field of transform. Passed kernel pointer is NULL.");
            };

            bool result = FieldDecomposerHelper<VInputDimensions, VOutputDimensions>::decomposeTransform(pTransform, field);
            return result;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            FieldDecomposer<VInputDimensions, VOutputDimensions>::
            decomposeTransform(TransformType* pTransform, FieldPointer& field)
        {
            if (!pTransform)
            {
                mapDefaultExceptionStaticMacro(<<
                    "Error decomposing field of transform. Passed kernel pointer is NULL.");
            };

            bool result = FieldDecomposerHelper<VInputDimensions, VOutputDimensions>::decomposeTransform(pTransform, field);
            return result;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            FieldDecomposer<VInputDimensions, VOutputDimensions>::
            decomposeKernel(const KernelType* pKernel, FieldConstPointer& field)
        {
            bool result = false;

            if (!pKernel)
            {
                mapDefaultExceptionStaticMacro(<<
                    "Error decomposing field of kernel. Passed kernel pointer is NULL.");
            };

            const RegistrationKernel<VInputDimensions, VOutputDimensions>* castedKernel = dynamic_cast<const RegistrationKernel<VInputDimensions, VOutputDimensions>*>(pKernel);

            if (castedKernel)
            {
                result = decomposeTransform(castedKernel->getTransformModel(),field);
            }
            return result;
        };

    }
}

#endif
