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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldByModelInversionFunctor.tpp $
*/

#ifndef __MAP_FIELD_BY_MODEL_INVERSION_FUNCTOR_TPP
#define __MAP_FIELD_BY_MODEL_INVERSION_FUNCTOR_TPP

#include "mapFieldByModelInversionFunctor.h"
#include "mapIterativeInverseTransformToDisplacementFieldSource.h"
#include "mapLogbookMacros.h"

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
				typedef typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::FieldPointer FieldPointer;
				typedef typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::FieldType    FieldType;
				typedef typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::TransformModelType    TransformModelType;
				typedef typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::InFieldRepresentationType    InFieldRepresentationType;

				static inline FieldPointer generate(const TransformModelType *pTransformModel, const InFieldRepresentationType *pInFieldRepresentation,
				                                    double stopValue, unsigned int nrOfIterations)
				{
					mapExceptionStaticMacro(ExceptionObject, << "Error unsymmetric field inversion not implemented yet.");
					return NULL;
				}
			};

			template <unsigned int VDimensions>
			class FieldByModelInversionFunctorHelper<VDimensions, VDimensions>
			{
			public:
				typedef typename FieldByModelInversionFunctor<VDimensions, VDimensions>::FieldPointer FieldPointer;
				typedef typename FieldByModelInversionFunctor<VDimensions, VDimensions>::FieldType    FieldType;
				typedef typename FieldByModelInversionFunctor<VDimensions, VDimensions>::TransformModelType    TransformModelType;
				typedef typename FieldByModelInversionFunctor<VDimensions, VDimensions>::InFieldRepresentationType    InFieldRepresentationType;

				static inline FieldPointer generate(const TransformModelType *pTransformModel, const InFieldRepresentationType *pInFieldRepresentation,
				                                    double stopValue, unsigned int nrOfIterations)
				{
					typedef itk::map::IterativeInverseTransformToDisplacementFieldSource<FieldType, typename TransformModelType::ScalarType> FieldSourceType;

					typename FieldSourceType::Pointer spFieldSource = FieldSourceType::New();

					spFieldSource->SetTransform(pTransformModel->getTransform());

					spFieldSource->SetSpacing(pInFieldRepresentation->getSpacing());
					spFieldSource->SetOrigin(pInFieldRepresentation->getOrigin());
					spFieldSource->SetDirection(pInFieldRepresentation->getDirection());

					typename InFieldRepresentationType::ImageRegionType region = pInFieldRepresentation->getRepresentedLocalImageRegion();

					spFieldSource->SetSize(region.GetSize());

					spFieldSource->SetNumberOfIterations(nrOfIterations);
					spFieldSource->SetStopValue(stopValue);

					typename FieldType::Pointer spField = spFieldSource->GetOutput();
					spFieldSource->Update();

					return spField;
				}
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::FieldPointer
			FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
			generateField() const
			{
				mapLogInfoMacro( << "Generate field by model inversion");

				typename FieldType::Pointer spField = FieldByModelInversionFunctorHelper<VInputDimensions, VOutputDimensions>::generate(_spTransformModel, Superclass::_spInFieldRepresentation, _stopValue , _nrOfIterations);

				return spField;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::TransformModelType *
			FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
			getTransformModel(void) const
			{
				return _spTransformModel;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::Pointer
			FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
			New(const TransformModelType &model,
			    const InFieldRepresentationType *pInFieldRepresentation)
			{
				assert(pInFieldRepresentation);
				Pointer spFieldByModelInversionFunctor = new Self(model, pInFieldRepresentation);
				spFieldByModelInversionFunctor->UnRegister();
				return spFieldByModelInversionFunctor;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename ::itk::LightObject::Pointer
			FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
			CreateAnother(void) const
			{
				::itk::LightObject::Pointer smartPtr;
				Pointer spNew = Self::New(*_spTransformModel, Superclass::_spInFieldRepresentation).GetPointer();
				smartPtr = spNew;
				spNew->setNumberOfIterations(this->getNumberOfIterations());
				spNew->setStopValue(this->getStopValue());
				return smartPtr;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
			FieldByModelInversionFunctor(const TransformModelType &model,
			                             const InFieldRepresentationType *pInFieldRepresentation):
				Superclass(pInFieldRepresentation), _spTransformModel(&model), _nrOfIterations(20), _stopValue(0.0)
			{
				assert(pInFieldRepresentation);
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
			~FieldByModelInversionFunctor() {}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			FieldByModelInversionFunctor<VInputDimensions, VOutputDimensions>::
			PrintSelf(std::ostream &os, itk::Indent indent) const
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
