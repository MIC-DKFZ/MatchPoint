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

#include "itkDisplacementFieldTransform.h"

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
        assert(_spTransform.IsNotNull());

        if (_spTransform.IsNull())
        {
            mapDefaultExceptionStaticMacro(<<
                "Error. Cannot get representation descriptor in PreCachedTransformPolicy. Transform is not set.");
        }

        RepresentationDescriptorConstPointer spRepresentation = NULL;

        typedef itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VInputDimensions> FieldTransformType;
        const FieldTransformType* pFieldTransformModel = dynamic_cast<const FieldTransformType*>(_spTransform.GetPointer());
        if (pFieldTransformModel)
        {
            if (pFieldTransformModel->GetDisplacementField())
            {
                spRepresentation = createFieldRepresentation(*(pFieldTransformModel->GetDisplacementField())).GetPointer();
            }
            else
            {
               mapDefaultExceptionStaticMacro(<<
                        "Error. Cannot get representation descriptor in PreCachedTransformPolicy. DisplacementFieldTransform has no field set.");
            }
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
    
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
		PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
        PreCachedRegistrationKernel() : _spTransform(NULL), _nullVector(
        ::itk::NumericTraits< typename MappingVectorType::ValueType >::NonpositiveMin()),
        _useNullVector(false)
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
		PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		~PreCachedRegistrationKernel()
		{
		};
    
    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    const typename PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::MappingVectorType&
        PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
        getNullVector() const
    {
        return _nullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    bool
        PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
        usesNullVector() const
    {
        return _useNullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    void
        PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
        setNullVector(const MappingVectorType& nullVector)
    {
        _nullVector = nullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    void
        PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>::
        setNullVectorUsage(bool use)
    {
        _useNullVector = use;
    };

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

      os << indent << "Use null vector: " << _useNullVector << std::endl;
      os << indent << "Null vector: " << this->_nullVector << std::endl;
		};

	} // end namespace core
} // end namespace map

#endif
