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

#ifndef __MAP_FIELD_BY_MODEL_INVERSION_FUNCTOR_TPP
#define __MAP_FIELD_BY_MODEL_INVERSION_FUNCTOR_TPP

#include "mapFieldByModelInversionFunctor.h"
#include "mapIterativeInverseTransformToDisplacementFieldSource.h"
#include "mapLogbookMacros.h"
#include "mapGenericVectorFieldTransform.h"

namespace map
{
    namespace core
    {
        namespace functors
        {
            /*! Helper class for a workaround.
             * right now we only support symmetric inversion. Must be implemented later on.
             * Template specialization allows the compiling of the code even in unsupported
             * cases.
             * @todo: Implement suitable solutions for unsymmetric cases (like VectorCombinationPolicy)
             */
            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            class FieldByModelInversionFunctorHelper
            {
            public:
                typedef typename ::itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VInputDimensions, VOutputDimensions> TransformType;
                using TransformPointer = typename TransformType::Pointer;
                typedef typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::SourceTransformModelType
                    SourceTransformModelType;
                typedef typename
                    FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::InFieldRepresentationType
                    InFieldRepresentationType;

                static inline TransformPointer generate(const SourceTransformModelType* pTransformModel,
                    const InFieldRepresentationType* pInFieldRepresentation,
                    double stopValue, unsigned int nrOfIterations)
                {
                    mapExceptionStaticMacro(ExceptionObject,
                        << "Error unsymmetric field inversion not implemented yet.");
                    return NULL;
                }
            };

            template <unsigned int VDimensions>
            class FieldByModelInversionFunctorHelper < VDimensions, VDimensions >
            {
            public:
                typedef typename FieldByModelInversionFunctor<VDimensions, VDimensions>::FieldType FieldType;
                typedef typename ::itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, VDimensions, VDimensions> TransformType;
                using TransformPointer = typename TransformType::Pointer;
                typedef typename FieldByModelInversionFunctor<VDimensions, VDimensions>::SourceTransformModelType
                    SourceTransformModelType;
                typedef typename FieldByModelInversionFunctor<VDimensions, VDimensions>::InFieldRepresentationType
                    InFieldRepresentationType;

                static inline TransformPointer generate(const SourceTransformModelType* pTransformModel,
                    const InFieldRepresentationType* pInFieldRepresentation,
                    double stopValue, unsigned int nrOfIterations)
                {
                    typedef itk::map::IterativeInverseTransformToDisplacementFieldSource < FieldType, typename SourceTransformModelType::ScalarType >
                        FieldSourceType;

                    typename FieldSourceType::Pointer spFieldSource = FieldSourceType::New();

                    spFieldSource->SetTransform(pTransformModel);

                    spFieldSource->SetSpacing(pInFieldRepresentation->getSpacing());
                    spFieldSource->SetOrigin(pInFieldRepresentation->getOrigin());
                    spFieldSource->SetDirection(pInFieldRepresentation->getDirection());

                    typename InFieldRepresentationType::ImageRegionType region =
                        pInFieldRepresentation->getRepresentedLocalImageRegion();

                    spFieldSource->SetSize(region.GetSize());

                    spFieldSource->SetNumberOfIterations(nrOfIterations);
                    spFieldSource->SetStopValue(stopValue);

                    typename FieldType::Pointer spField = spFieldSource->GetOutput();
                    spFieldSource->Update();

                    typename TransformType::Pointer spResult = TransformType::New();
                    spResult->SetDisplacementField(spField);
                    return spResult.GetPointer();
                }
            };

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::TransformPointer
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                generateTransform() const
            {
                mapLogInfoMacro(<< "Generate field by model inversion");

                typedef typename FieldByModelInversionFunctorHelper<VInputDimensions, VOutputDimensions>::TransformType FieldTransformType;
                typename FieldTransformType::Pointer spResult =
                    FieldByModelInversionFunctorHelper<VInputDimensions, VOutputDimensions>::generate(_spTransformModel,
                    Superclass::_spInFieldRepresentation, _stopValue, _nrOfIterations);

                typedef typename ::itk::map::NULLVectorAwareLinearInterpolateImageFunction < typename FieldTransformType::GenericVectorFieldType, typename FieldTransformType::ScalarType> InterpolatorType;
                typename InterpolatorType::Pointer interpolator = InterpolatorType::New();
                interpolator->SetNullVectorUsage(this->_useNullPoint);
                typename InterpolatorType::OutputType nullVector;

                typedef typename InterpolatorType::OutputType::Superclass VectorSuperclassType;
                nullVector.VectorSuperclassType::operator = (this->_nullPoint);
                interpolator->SetNullVector(nullVector);

                spResult->SetInterpolator(interpolator);
                spResult->SetUseNullPoint(this->_useNullPoint);
                spResult->SetNullPoint(this->_nullPoint);

                return spResult.GetPointer();
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            const typename
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::SourceTransformModelType*
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                getSourceTransformModel() const
            {
                return _spTransformModel;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::Pointer
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                New(const SourceTransformModelType* model,
                const InFieldRepresentationType* pInFieldRepresentation)
            {
                assert(pInFieldRepresentation);
                assert(model);
                Pointer spFieldByModelInversionFunctor = new Self(model, pInFieldRepresentation);
                spFieldByModelInversionFunctor->UnRegister();
                return spFieldByModelInversionFunctor;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            typename ::itk::LightObject::Pointer
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                CreateAnother() const
            {
                ::itk::LightObject::Pointer smartPtr;
                Pointer spNew = Self::New(_spTransformModel, Superclass::_spInFieldRepresentation).GetPointer();
                smartPtr = spNew;
                spNew->setNumberOfIterations(this->getNumberOfIterations());
                spNew->setStopValue(this->getStopValue());
                return smartPtr;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                FieldByModelInversionFunctor(const SourceTransformModelType* model,
                const InFieldRepresentationType* pInFieldRepresentation) :
                Superclass(pInFieldRepresentation), _spTransformModel(model), _nrOfIterations(20), _stopValue(0.0)
            {
                assert(model);
                assert(pInFieldRepresentation);
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                ~FieldByModelInversionFunctor() {}

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            void
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                PrintSelf(std::ostream& os, itk::Indent indent) const
            {
                Superclass::PrintSelf(os, indent);
                os << indent << "Number of iterations: " << _nrOfIterations << std::endl;
                os << indent << "Stop value: " << _stopValue << std::endl;
                os << indent << "Transform model: " << _spTransformModel << std::endl;
            }


            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            unsigned long
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                getNumberOfIterations() const
            {
                return _nrOfIterations;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            void
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                setNumberOfIterations(unsigned long nrOfIterations)
            {
                _nrOfIterations = nrOfIterations;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            double
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                getStopValue() const
            {
                return _stopValue;
            }

            template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
            void
                FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
                setStopValue(double stopValue)
            {
                _stopValue = stopValue;
            }


        } // end namespace functors
    } // end namespace core
} // end namespace map

#endif
