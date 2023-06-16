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
// @version $Revision: 1285 $ (last changed revision)
// @date    $Date: 2016-03-30 17:47:52 +0200 (Mi, 30 Mrz 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/Core/include/mapPreCachedRegistrationKernel.tpp $
*/

#ifndef __PRE_CACHED_REGISTRATION_KERNEL_TPP
#define __PRE_CACHED_REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"
#include "mapGenericVectorFieldTransform.h"

#include "mapFieldDecomposer.h"

namespace map
{
    namespace core
    {

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        void
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            setTransformModel(TransformType* transform)
        {
            _spTransform = transform;
        };


        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            transformExists() const
        {
            return _spTransform.IsNotNull();
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        typename PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            getLargestPossibleRepresentation() const
        {
            if (_spTransform.IsNull())
            {
                mapDefaultExceptionStaticMacro(<<
                    "Error. Cannot get representation descriptor in PreCachedTransformPolicy. Transform is not set.");
            }

            RepresentationDescriptorConstPointer spRepresentation;

            typename ::map::core::FieldDecomposer<VInputDimensions, VOutputDimensions>::FieldConstPointer pField;

            if (::map::core::FieldDecomposer<VInputDimensions, VOutputDimensions>::decomposeTransform(_spTransform, pField))
            {
                spRepresentation = createFieldRepresentation(*(pField.GetPointer()));
            }

            return spRepresentation;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        const typename
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::TransformType*
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            getTransformModel() const
        {
            return _spTransform;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            checkAndPrepareTransform() const
        {
            return _spTransform.IsNotNull();
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        const typename PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::OutputPointType
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            getNullPoint() const
        {
            typedef itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> CastedTransformType;
            const CastedTransformType* castedTrans = dynamic_cast<const CastedTransformType*>(_spTransform.GetPointer());

            MappingVectorType result;
            if (castedTrans)
            {
                typedef typename MappingVectorType::Superclass VectorSuperclassType;
                result.VectorSuperclassType::operator = (castedTrans->GetNullPoint());
            }
            return result.GetDataPointer();
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            usesNullPoint() const
        {
            typedef itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> CastedTransformType;
            const CastedTransformType* castedTrans = dynamic_cast<const CastedTransformType*>(_spTransform.GetPointer());

            if (castedTrans)
            {
                return castedTrans->GetUseNullPoint();
            }
            else
            {
                return false;
            }
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            PreCachedRegistrationKernel()
        {
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            ~PreCachedRegistrationKernel()
        {
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        ::itk::LightObject::Pointer
          PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
          InternalClone() const
        {
          Pointer clone = Self::New();
          clone->_spTransform = this->_spTransform;
          return clone.GetPointer();
        }

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        void
            PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
            PrintSelf(std::ostream& os, itk::Indent indent) const
        {
            Superclass::PrintSelf(os, indent);

            if (_spTransform.IsNotNull())
            {
                os << indent << "Transform : " << std::endl << _spTransform << std::endl;
            }
            else
            {
                os << indent << "Transform : NULL" << std::endl;
            }

            os << indent << "Use null vector: " << this->usesNullPoint() << std::endl;
            os << indent << "Null vector: " << this->getNullPoint() << std::endl;
        };

    } // end namespace core
} // end namespace map

#endif
