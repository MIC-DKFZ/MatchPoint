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


#ifndef __MAP_FIELD_BY_FIELD_INVERSION_FUNCTOR_TPP
#define __MAP_FIELD_BY_FIELD_INVERSION_FUNCTOR_TPP

#include "mapFieldByFieldInversionFunctor.h"
#include "mapLogbookMacros.h"

#include "itkIterativeInverseDisplacementFieldImageFilter.h"

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
			class FieldByFieldInversionFunctorHelper
			{
			public:
				typedef typename FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::FieldPointer
				FieldPointer;
				typedef typename FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::FieldType
				FieldType;
				typedef typename
				FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::SourceFieldKernelType
				SourceFieldKernelType;
				typedef typename
				FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::InFieldRepresentationType
				InFieldRepresentationType;

				static inline FieldPointer generate(const SourceFieldKernelType* pSourceFieldKernel,
													const InFieldRepresentationType* pInFieldRepresentation,
													double stopValue, unsigned int nrOfIterations)
				{
					mapExceptionStaticMacro(ExceptionObject,
											<< "Error unsymmetric field inversion not implemented yet.");
					return NULL;
				}
			};

			template <unsigned int VDimensions>
			class FieldByFieldInversionFunctorHelper<VDimensions, VDimensions>
			{
			public:
				typedef typename FieldByFieldInversionFunctor<VDimensions, VDimensions>::FieldPointer FieldPointer;
				typedef typename FieldByFieldInversionFunctor<VDimensions, VDimensions>::FieldType    FieldType;
				typedef typename FieldByFieldInversionFunctor<VDimensions, VDimensions>::SourceFieldType
				SourceFieldType;
				typedef typename FieldByFieldInversionFunctor<VDimensions, VDimensions>::SourceFieldConstPointer
				SourceFieldConstPointer;
				typedef typename FieldByFieldInversionFunctor<VDimensions, VDimensions>::SourceFieldKernelType
				SourceFieldKernelType;
				typedef typename FieldByFieldInversionFunctor<VDimensions, VDimensions>::InFieldRepresentationType
				InFieldRepresentationType;

				static inline FieldPointer generate(const SourceFieldKernelType* pSourceFieldKernel,
													const InFieldRepresentationType* pInFieldRepresentation,
													double stopValue, unsigned int nrOfIterations)
				{
					typedef itk::IterativeInverseDisplacementFieldImageFilter<SourceFieldType, FieldType>
					FieldInverterType;

					mapLogInfoStaticMacro( << "Generate field by field inversion");

					typename FieldInverterType::Pointer spFieldInverter = FieldInverterType::New();

					SourceFieldConstPointer spSourceField = pSourceFieldKernel->getField();

					spFieldInverter->SetInput(spSourceField);
					spFieldInverter->SetNumberOfIterations(nrOfIterations);
					spFieldInverter->SetStopValue(stopValue);

					FieldPointer spField = spFieldInverter->GetOutput();
					spFieldInverter->Update();

					return spField;
				}
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::FieldPointer
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			generateField() const
			{
				FieldPointer spField =
					FieldByFieldInversionFunctorHelper<VInputDimensions, VOutputDimensions>::generate(
						_spSourceFieldKernel, Superclass::_spInFieldRepresentation, _stopValue, _nrOfIterations);

				return spField;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::SourceFieldKernelType*
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			getSourceFieldKernel(void) const
			{
				return _spSourceFieldKernel;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::Pointer
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			New(const SourceFieldKernelType& sourceFieldKernel,
				const InFieldRepresentationType* pInFieldRepresentation)
			{
				assert(pInFieldRepresentation);
				Pointer spFieldByFieldInversionFunctor = new Self(sourceFieldKernel, pInFieldRepresentation);
				spFieldByFieldInversionFunctor->UnRegister();
				return spFieldByFieldInversionFunctor;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename ::itk::LightObject::Pointer
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			CreateAnother(void) const
			{
				::itk::LightObject::Pointer smartPtr;
				Pointer spNew = Self::New(*_spSourceFieldKernel, Superclass::_spInFieldRepresentation).GetPointer();
				smartPtr = spNew;
				spNew->setNumberOfIterations(this->getNumberOfIterations());
				spNew->setStopValue(this->getStopValue());
				return smartPtr;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			FieldByFieldInversionFunctor(const SourceFieldKernelType& sourceFieldKernel,
										 const InFieldRepresentationType* pInFieldRepresentation):
				Superclass(pInFieldRepresentation), _spSourceFieldKernel(&sourceFieldKernel), _nrOfIterations(20),
				_stopValue(0.0)
			{
				assert(pInFieldRepresentation);
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			~FieldByFieldInversionFunctor() {}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			PrintSelf(std::ostream& os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "Number of iterations: " << _nrOfIterations << std::endl;
				os << indent << "Stop value: " << _stopValue << std::endl;
				os << indent << "Source field kernel: " << _spSourceFieldKernel << std::endl;
			}


			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			unsigned long
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			getNumberOfIterations() const
			{
				return _nrOfIterations;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			setNumberOfIterations(unsigned long nrOfIterations)
			{
				_nrOfIterations = nrOfIterations;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			double
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			getStopValue() const
			{
				return _stopValue;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			FieldByFieldInversionFunctor<VInputDimensions, VOutputDimensions>::
			setStopValue(double stopValue)
			{
				_stopValue = stopValue;
			}

		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
