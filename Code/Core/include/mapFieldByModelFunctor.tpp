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

#ifndef __MAP_FIELD_BY_MODEL_FUNCTOR_TPP
#define __MAP_FIELD_BY_MODEL_FUNCTOR_TPP

#include "mapFieldByModelFunctor.h"
#include "mapLogbookMacros.h"
#include "mapPointVectorCombinationPolicy.h"
#include "mapGenericVectorFieldTransform.h"

#include "itkImageRegionIterator.h"

namespace map
{
    namespace core
    {

        template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
        typename RegistrationTopology < VInputDimensions,
            VOutputDimensions >::DirectFieldPointer
            generateFieldFromTransform(const typename RegistrationTopology < VInputDimensions,
            VOutputDimensions >::DirectTransformType* transform, const FieldRepresentationDescriptor<VInputDimensions>* inDesc)
        {
            if (!transform)
            {
                mapDefaultExceptionStaticMacro(<< "Error. Cannot generate field out of transform. Passed transform is NULL.")
            }

            if (!inDesc)
            {
                mapDefaultExceptionStaticMacro(<< "Error. Cannot generate field out of transform. Passed input field representation descriptor is is NULL.")
            }

            typedef typename RegistrationTopology <VInputDimensions, VOutputDimensions >::DirectFieldType FieldType;
            typename RegistrationTopology <VInputDimensions, VOutputDimensions >::DirectFieldPointer spField = FieldType::New();
            typedef itk::ImageRegionIterator< FieldType > IteratorType;

            typename FieldType::RegionType region =
                inDesc->getRepresentedLocalImageRegion();

            //allocate image memory
            spField->SetRegions(region);
            spField->SetSpacing(inDesc->getSpacing());
            spField->SetOrigin(inDesc->getOrigin());
            spField->SetDirection(inDesc->getDirection());
            spField->Allocate();

            //sample the transform into a vector field
            IteratorType iterator(spField, spField->GetLargestPossibleRegion());

            for (iterator.GoToBegin(); !(iterator.IsAtEnd()); ++iterator)
            {
                typename FieldType::IndexType index = iterator.GetIndex();
                typename FieldType::PointType inPoint;
                spField->TransformIndexToPhysicalPoint(index, inPoint);

                typename RegistrationTopology < VInputDimensions,
                    VOutputDimensions >::DirectTransformType::OutputPointType outPoint =
                    transform->TransformPoint(inPoint);

                typename FieldType::ValueType value;
                ::map::core::PointVectorCombinationPolicy<VInputDimensions, VOutputDimensions>::computeVector(inPoint, outPoint, value);
                iterator.Set(value);
            }

            return spField;
        };

        namespace functors
        {

            /*! Helper class for a workaround.
            * right now we only support symmetric inversion. Must be implemented later on.
            * Template specialization allows the compiling of the code even in unsupported
            * cases.
            * @todo: Implement suitable solutions for unsymmetric cases (like VectorCombinationPolicy)
            */
            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            class FieldByModelFunctorHelper
            {
            public:
                typedef typename ::itk::GenericVectorFieldTransform<::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> TransformType;
                typedef typename TransformType::Pointer TransformPointer;
                typedef typename FieldByModelFunctor<VInputDimensions, VOutputDimensions>::SourceTransformModelType
                    SourceTransformModelType;
                typedef typename
                    FieldByModelFunctor<VInputDimensions, VOutputDimensions>::InFieldRepresentationType
                    InFieldRepresentationType;

                static inline TransformPointer generate(const SourceTransformModelType* pTransformModel,
                    const InFieldRepresentationType* pInFieldRepresentation)
                {
                    mapExceptionStaticMacro(ExceptionObject,
                        << "Error unsymmetric field inversion not implemented yet.");
                    return NULL;
                }
            };

            template <unsigned int VDimensions>
            class FieldByModelFunctorHelper < VDimensions, VDimensions >
            {
            public:
                typedef typename FieldByModelFunctor<VDimensions, VDimensions>::FieldType FieldType;
                typedef typename ::itk::GenericVectorFieldTransform<::map::core::continuous::ScalarType, VDimensions, VDimensions> TransformType;
                typedef typename TransformType::Pointer TransformPointer;
                typedef typename FieldByModelFunctor<VDimensions, VDimensions>::SourceTransformModelType
                    SourceTransformModelType;
                typedef typename FieldByModelFunctor<VDimensions, VDimensions>::InFieldRepresentationType
                    InFieldRepresentationType;

                static inline TransformPointer generate(const SourceTransformModelType* pTransformModel,
                    const InFieldRepresentationType* pInFieldRepresentation)
                {
                    typename FieldType::Pointer spField = generateFieldFromTransform<VDimensions, VDimensions>(pTransformModel, pInFieldRepresentation);

                    typename TransformPointer spResult = TransformType::New();
                    spResult->SetDisplacementField(spField);
                    return spResult.GetPointer();
                }
            };

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename FieldByModelFunctor<VInputDimensions, VOutputDimensions>::TransformPointer
                FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
                generateTransform() const
            {
                mapLogInfoMacro(<< "Generate field by model sampling");

                typedef typename FieldByModelFunctorHelper<VInputDimensions, VOutputDimensions>::TransformType FieldTransformType;
                    typename FieldTransformType::Pointer spResult =
                    FieldByModelFunctorHelper<VInputDimensions, VOutputDimensions>::generate(_spTransformModel,
                    Superclass::_spInFieldRepresentation);

                typedef typename ::itk::map::NULLVectorAwareLinearInterpolateImageFunction < FieldTransformType::GenericVectorFieldType, FieldTransformType::ScalarType> InterpolatorType;
                typename InterpolatorType::Pointer interpolator = InterpolatorType::New();
                interpolator->SetNullVectorUsage(_useNullPoint);
                InterpolatorType::OutputType nullVector;
                nullVector.Superclass::operator = (_nullPoint);
                interpolator->SetNullVector(nullVector);

                spResult->SetInterpolator(interpolator);
                spResult->SetUseNullPoint(_useNullPoint);
                spResult->SetNullPoint(_nullPoint);

                return spResult.GetPointer();
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            const typename FieldByModelFunctor<VInputDimensions, VOutputDimensions>::SourceTransformModelType*
                FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
                getSourceTransformModel(void) const
            {
                return _spTransformModel;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename FieldByModelFunctor<VInputDimensions, VOutputDimensions>::Pointer
                FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
                New(const SourceTransformModelType* model,
                const InFieldRepresentationType* pInFieldRepresentation)
            {
                assert(pInFieldRepresentation);
                Pointer spFieldByModelFunctor = new Self(model, pInFieldRepresentation);
                spFieldByModelFunctor->UnRegister();
                return spFieldByModelFunctor;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename ::itk::LightObject::Pointer
                FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
                CreateAnother(void) const
            {
                ::itk::LightObject::Pointer smartPtr;
                smartPtr = Self::New(_spTransformModel, Superclass::_spInFieldRepresentation).GetPointer();
                return smartPtr;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
                FieldByModelFunctor(const SourceTransformModelType* model,
                const InFieldRepresentationType* pInFieldRepresentation) :
                Superclass(pInFieldRepresentation), _spTransformModel(model)
            {
                assert(pInFieldRepresentation);
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
                ~FieldByModelFunctor() {}

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            void
                FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
                PrintSelf(std::ostream& os, itk::Indent indent) const
            {
                Superclass::PrintSelf(os, indent);
                os << indent << "Transform model: " << _spTransformModel << std::endl;
            }


        } // end namespace functors
    } // end namespace core
} // end namespace map

#endif
