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

#include "itkImageRegionIterator.h"

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
                typename FieldType::Pointer spField = FieldType::New();

                typename InFieldRepresentationType::ImageRegionType region =
                    Superclass::_spInFieldRepresentation->getRepresentedLocalImageRegion();
                spField->SetRegions(region);
                spField->SetOrigin(Superclass::_spInFieldRepresentation->getOrigin());
                spField->SetSpacing(Superclass::_spInFieldRepresentation->getSpacing());
                spField->SetDirection(Superclass::_spInFieldRepresentation->getDirection());
                spField->Allocate();

                typedef itk::ImageRegionIterator<FieldType> IteratorType;
                IteratorType iterator(spField, region);

                typedef typename SourceKernel2BaseType::MappingVectorType::Superclass VectorSuperclassType;
                typename SourceKernel2BaseType::MappingVectorType nullVector;
                    nullVector.VectorSuperclassType::operator = (this->_nullPoint);

                for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
                {
                    typename IteratorType::IndexType index = iterator.GetIndex();
                    typename FieldType::PointType inPoint;
                    spField->TransformIndexToPhysicalPoint(index, inPoint);

                    typename SourceKernel1BaseType::OutputPointType interimPoint;
                    
                    bool valid = _spSourceKernel1->mapPoint(inPoint, interimPoint);

                    typename SourceKernel2BaseType::OutputPointType endPoint;
                    bool valid2 = _spSourceKernel2->mapPoint(interimPoint, endPoint);

                    typename SourceKernel2BaseType::MappingVectorType outVector = nullVector;

                    if (valid && valid2)
                    {
                        PointVectorCombinationPolicy<VInputDimensions, VOutputDimensions>::computeVector(inPoint,
                            endPoint, outVector);
                    }
                    else
                    {
                        if (! this->_useNullPoint)
                        {
                            mapDefaultExceptionMacro(<< "Error. Cannot generate combined kernel. At least one source kernel was not able to map points. valid source kernel 1: " << valid << "; valid source kernel 2:" << valid2);
                        }
                    }

                    iterator.Set(outVector);
                }

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
