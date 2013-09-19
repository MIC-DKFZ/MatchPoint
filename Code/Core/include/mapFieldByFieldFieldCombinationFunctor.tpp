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


#ifndef __MAP_FIELD_BY_FIELD_FIELD_COMBINATION_FUNCTOR_TPP
#define __MAP_FIELD_BY_FIELD_FIELD_COMBINATION_FUNCTOR_TPP

#include "mapFieldByFieldFieldCombinationFunctor.h"
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
			typename FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::FieldPointer
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
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

				typedef itk::LinearInterpolateImageFunction<typename SourceFieldKernel1Type::FieldType , continuous::ScalarType>
				Interpolator1Type;
				typename Interpolator1Type::Pointer spInterpolator1 = Interpolator1Type::New();
				spInterpolator1->SetInputImage(_sp1stSourceFieldKernel->getField());

				typedef itk::LinearInterpolateImageFunction<typename SourceFieldKernel2Type::FieldType , continuous::ScalarType>
				Interpolator2Type;
				typename Interpolator2Type::Pointer spInterpolator2 = Interpolator2Type::New();
				spInterpolator2->SetInputImage(_sp2ndSourceFieldKernel->getField());

				for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
				{
					typename IteratorType::IndexType index = iterator.GetIndex();
					typename FieldType::PointType inPoint;
					spField->TransformIndexToPhysicalPoint(index, inPoint);

					typename Interpolator1Type::OutputType firstVector;
					typename Interpolator2Type::OutputType secondVector;
					typename IteratorType::PixelType outVector(CombinationInterface::_paddingVector);

					// start first transformation
					if (!spInterpolator1->IsInsideBuffer(inPoint))
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
						firstVector = spInterpolator1->Evaluate(inPoint);

						typename SourceFieldKernel1Type::OutputPointType interimPoint;
						PointVectorCombinationPolicy<VInputDimensions, VInterimDimensions>::mapPoint(inPoint, firstVector,
								interimPoint);

						// start second transformation
						if (!spInterpolator2->IsInsideBuffer(interimPoint))
						{
							if (! CombinationInterface::_usePadding)
							{
								//throw the exception
								mapExceptionMacro(RepresentationException,
												  << "Cannot combine kernels. Point is not inside supported region of second kernel (field). Point: "
												  << interimPoint);
							}

							//otherwise just use padding vector
						}
						else
						{
							secondVector = spInterpolator2->Evaluate(interimPoint);
							PointVectorCombinationPolicy<VInterimDimensions, VOutputDimensions>::combineVectors(firstVector,
									secondVector, outVector);
						}
					}

					iterator.Set(outVector);
				}

				return spField;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceFieldKernel1Type*

			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get1stSourceFieldKernel(void) const
			{
				return _sp1stSourceFieldKernel;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceFieldKernel2Type*

			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get2ndSourceFieldKernel(void) const
			{
				return _sp2ndSourceFieldKernel;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel1BaseType*

			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get1stSourceKernelBase(void) const
			{
				return get1stSourceFieldKernel();
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel2BaseType*

			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get2ndSourceKernelBase(void) const
			{
				return get2ndSourceFieldKernel();
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			typename FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::Pointer
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			New(const SourceFieldKernel1Type& fieldKernel1,
				const SourceFieldKernel2Type& fieldKernel2,
				const InFieldRepresentationType* pInFieldRepresentation)
			{
				assert(pInFieldRepresentation);
				Pointer spFieldByFieldFieldCombinationFunctor = new Self(fieldKernel1, fieldKernel2,
						pInFieldRepresentation);
				spFieldByFieldFieldCombinationFunctor->UnRegister();
				return spFieldByFieldFieldCombinationFunctor;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			::itk::LightObject::Pointer
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			CreateAnother(void) const
			{
				::itk::LightObject::Pointer smartPtr;
				Pointer spNew = Self::New(*_sp1stSourceFieldKernel, *_sp2ndSourceFieldKernel,
										  Superclass::_spInFieldRepresentation).GetPointer();
				smartPtr = spNew;
				return smartPtr;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			FieldByFieldFieldCombinationFunctor(const SourceFieldKernel1Type& fieldKernel1,
												const SourceFieldKernel2Type& fieldKernel2,
												const InFieldRepresentationType* pInFieldRepresentation):
				Superclass(pInFieldRepresentation), _sp1stSourceFieldKernel(&fieldKernel1),
				_sp2ndSourceFieldKernel(&fieldKernel2)
			{
				assert(pInFieldRepresentation);
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			~FieldByFieldFieldCombinationFunctor()
			{
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			void
			FieldByFieldFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			PrintSelf(std::ostream& os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "Source field kernel 1: " << _sp1stSourceFieldKernel << std::endl;
				os << indent << "Source field kernel 2: " << _sp2ndSourceFieldKernel << std::endl;
			}

		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
