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

#ifndef __MAP_FIELD_BY_FIELD_MODEL_COMBINATION_FUNCTOR_TPP
#define __MAP_FIELD_BY_FIELD_MODEL_COMBINATION_FUNCTOR_TPP

#include "mapFieldByFieldModelCombinationFunctor.h"
#include "mapRepresentationException.h"
#include "mapPointVectorCombinationPolicy.h"

#include "itkLinearInterpolateImageFunction.h"
#include "itkImageRegionIterator.h"

namespace map
{
	namespace core
	{
		namespace functors
		{
			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			typename FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::FieldPointer
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			generateField() const
			{
				FieldPointer spField = FieldType::New();

				typename InFieldRepresentationType::ImageRegionType region =
					Superclass::_spInFieldRepresentation->getRepresentedLocalImageRegion();
				spField->SetRegions(region);
				spField->SetOrigin(Superclass::_spInFieldRepresentation->getOrigin());
				spField->SetSpacing(Superclass::_spInFieldRepresentation->getSpacing());
				spField->SetDirection(Superclass::_spInFieldRepresentation->getDirection());
				spField->Allocate();

				typedef itk::ImageRegionIterator<FieldType> IteratorType;
				IteratorType iterator(spField, region);

				typedef  itk::LinearInterpolateImageFunction<typename SourceFieldKernelType::FieldType , continuous::ScalarType>
				InterpolatorType;
				typename InterpolatorType::Pointer spInterpolator = InterpolatorType::New();
				spInterpolator->SetInputImage(_spSourceFieldKernel->getField());

				for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
				{
					typename IteratorType::IndexType index = iterator.GetIndex();
					typename FieldType::PointType inPoint;
					spField->TransformIndexToPhysicalPoint(index, inPoint);

					typename InterpolatorType::OutputType firstVector;

					typename IteratorType::PixelType outVector(CombinationInterface::_paddingVector);

					if (!spInterpolator->IsInsideBuffer(inPoint))
					{
						if (! CombinationInterface::_usePadding)
						{
							//throw the exception
							mapExceptionMacro(RepresentationException,
											  << "Cannot combine kernels. Point is not inside supported region of first kernel (field). Point: "
											  << inPoint);
						}

						//otherwise just use padding vector
					}
					else
					{
						firstVector = spInterpolator->Evaluate(inPoint);

						typename SourceFieldKernelType::OutputPointType interimPoint;
						PointVectorCombinationPolicy<VInputDimensions, VInterimDimensions>::mapPoint(inPoint, firstVector,
								interimPoint);

						typename SourceModelKernelType::OutputPointType endPoint = _spSourceModelKernel->transformPoint(
									interimPoint);

						typename SourceModelKernelType::OutputVectorType secondVector;
						PointVectorCombinationPolicy<VInterimDimensions, VOutputDimensions>::computeVector(interimPoint,
								endPoint, secondVector);

						PointVectorCombinationPolicy<VInterimDimensions, VOutputDimensions>::combineVectors(firstVector,
								secondVector, outVector);
					}

					iterator.Set(outVector);
				}

				return spField;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceFieldKernelType*

			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			getSourceFieldKernel(void) const
			{
				return _spSourceFieldKernel;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceModelKernelType*

			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			getSourceModelKernel(void) const
			{
				return _spSourceModelKernel;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel1BaseType*

			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get1stSourceKernelBase(void) const
			{
				return getSourceFieldKernel();
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel2BaseType*

			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get2ndSourceKernelBase(void) const
			{
				return getSourceModelKernel();
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			typename FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::Pointer
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			New(const SourceFieldKernelType& fieldKernel,
				const SourceModelKernelType& modelKernel,
				const InFieldRepresentationType* pInFieldRepresentation)
			{
				assert(pInFieldRepresentation);
				Pointer spFieldByFieldModelCombinationFunctor = new Self(fieldKernel, modelKernel,
						pInFieldRepresentation);
				spFieldByFieldModelCombinationFunctor->UnRegister();
				return spFieldByFieldModelCombinationFunctor;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			::itk::LightObject::Pointer
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			CreateAnother(void) const
			{
				::itk::LightObject::Pointer smartPtr;
				Pointer spNew = Self::New(*_spSourceFieldKernel, *_spSourceModelKernel,
										  Superclass::_spInFieldRepresentation).GetPointer();
				smartPtr = spNew;
				return smartPtr;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			FieldByFieldModelCombinationFunctor(const SourceFieldKernelType& fieldKernel,
												const SourceModelKernelType& modelKernel,
												const InFieldRepresentationType* pInFieldRepresentation):
				Superclass(pInFieldRepresentation), _spSourceFieldKernel(&fieldKernel),
				_spSourceModelKernel(&modelKernel)
			{
				assert(pInFieldRepresentation);
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			~FieldByFieldModelCombinationFunctor()
			{
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			void
			FieldByFieldModelCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			PrintSelf(std::ostream& os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "Source field kernel: " << _spSourceFieldKernel << std::endl;
				os << indent << "Source model kernel: " << _spSourceModelKernel << std::endl;
			}
		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
