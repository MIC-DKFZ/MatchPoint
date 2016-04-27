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

#ifndef __MAP_GENERIC_FIELD_GENERATING_COMBINATION_FUNCTOR_TPP
#define __MAP_GENERIC_FIELD_GENERATING_COMBINATION_FUNCTOR_TPP

#include "mapGenericFieldGeneratingCombinationFunctor.h"
#include "mapRepresentationException.h"
#include "mapPointVectorCombinationPolicy.h"
#include "mapRegistrationKernel.h"
#include "mapGenericVectorFieldTransform.h"
#include "mapNULLVectorAwareLinearInterpolateImageFunction.h"
#include "mapGenericKernelCombinationFieldSource.h"

namespace map
{
    namespace core
    {
        namespace functors
        {
            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            typename GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::TransformPointer
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                generateTransform() const
            {
                typedef map::core::GenericKernelCombinationFieldSource<VInputDimensions, VInterimDimensions, VOutputDimensions, typename FieldType::PixelType::ValueType> FieldSourceType;
                typename FieldSourceType::Pointer source = FieldSourceType::New();

                typedef typename SourceKernel2BaseType::MappingVectorType::Superclass VectorSuperclassType;
                typename SourceKernel2BaseType::MappingVectorType nullVector;
                nullVector.VectorSuperclassType::operator = (this->_nullPoint);

                source->SetSize(Superclass::_spInFieldRepresentation->getRepresentedLocalImageRegion().GetSize());
                source->SetOrigin(Superclass::_spInFieldRepresentation->getOrigin());
                source->SetSpacing(Superclass::_spInFieldRepresentation->getSpacing());
                source->SetDirection(Superclass::_spInFieldRepresentation->getDirection());

                source->SetSourceKernel1(_spSourceKernel1);
                source->SetSourceKernel2(_spSourceKernel2);
                source->SetUseNullPoint(this->_useNullPoint);
                source->SetNullPoint(this->_nullPoint);

                source->Update();

                typename FieldType::Pointer spField = source->GetOutput();

                typedef ::itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> FieldTransformType;
                typename FieldTransformType::Pointer spResult = FieldTransformType::New();
                spResult->SetDisplacementField(spField);

                typedef ::itk::map::NULLVectorAwareLinearInterpolateImageFunction < typename FieldTransformType::GenericVectorFieldType, typename FieldTransformType::ScalarType> InterpolatorType;
                typename InterpolatorType::Pointer interpolator = InterpolatorType::New();
                interpolator->SetNullVectorUsage(this->_useNullPoint);
                interpolator->SetNullVector(nullVector);

                spResult->SetInterpolator(interpolator);
                spResult->SetUseNullPoint(this->_useNullPoint);
                spResult->SetNullPoint(this->_nullPoint);
                return spResult.GetPointer();
            }


            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            const typename
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel1BaseType*
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                get1stSourceKernelBase(void) const
            {
                return _spSourceKernel1;
            }

            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            const typename
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel2BaseType*
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                get2ndSourceKernelBase(void) const
            {
                return _spSourceKernel2;
            }

            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            typename GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::Pointer
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                New(const SourceKernel1BaseType* kernel1,
                const SourceKernel2BaseType* kernel2,
                const InFieldRepresentationType* pInFieldRepresentation)
            {
                assert(pInFieldRepresentation);
                Pointer spGenericFieldGeneratingCombinationFunctor = new Self(kernel1, kernel2,
                    pInFieldRepresentation);
                spGenericFieldGeneratingCombinationFunctor->UnRegister();
                return spGenericFieldGeneratingCombinationFunctor;
            }

            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            ::itk::LightObject::Pointer
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                CreateAnother(void) const
            {
                ::itk::LightObject::Pointer smartPtr;
                Pointer spNew = Self::New(_spSourceKernel1, _spSourceKernel2,
                    Superclass::_spInFieldRepresentation).GetPointer();
                smartPtr = spNew;
                return smartPtr;
            }

            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                GenericFieldGeneratingCombinationFunctor(const SourceKernel1BaseType* kernel1,
                const SourceKernel2BaseType* kernel2,
                const InFieldRepresentationType* pInFieldRepresentation) :
                Superclass(pInFieldRepresentation), _spSourceKernel1(kernel1),
                _spSourceKernel2(kernel2)
            {
                assert(pInFieldRepresentation);
                assert(kernel1);
                assert(kernel2);
            }

            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                ~GenericFieldGeneratingCombinationFunctor()
            {
            }

            template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
            void
                GenericFieldGeneratingCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
                PrintSelf(std::ostream& os, itk::Indent indent) const
            {
                Superclass::PrintSelf(os, indent);
                os << indent << "Source 1st kernel: " << _spSourceKernel1 << std::endl;
                os << indent << "Source 2nd kernel: " << _spSourceKernel2 << std::endl;
            }
        } // end namespace functors
    } // end namespace core
} // end namespace map

#endif
