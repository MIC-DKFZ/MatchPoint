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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldByModelFieldCombinationFunctor.tpp $
*/

#ifndef __MAP_FIELD_BY_MODEL_FIELD_COMBINATION_FUNCTOR_TPP
#define __MAP_FIELD_BY_MODEL_FIELD_COMBINATION_FUNCTOR_TPP

#include "mapFieldByModelFieldCombinationFunctor.h"
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
			typename FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::FieldPointer
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			generateField() const
			{
				FieldPointer spField = FieldType::New();

				typename InFieldRepresentationType::ImageRegionType region = Superclass::_spInFieldRepresentation->getRepresentedLocalImageRegion();
				spField->SetRegions(region);
				spField->SetOrigin(Superclass::_spInFieldRepresentation->getOrigin());
				spField->SetSpacing(Superclass::_spInFieldRepresentation->getSpacing());
				spField->SetDirection(Superclass::_spInFieldRepresentation->getDirection());
				spField->Allocate();

				typedef itk::ImageRegionIterator<FieldType> IteratorType;
				IteratorType iterator(spField, region);

				typedef itk::LinearInterpolateImageFunction<typename SourceFieldKernelType::FieldType , continuous::ScalarType> InterpolatorType;
				typename InterpolatorType::Pointer spInterpolator = InterpolatorType::New();
				spInterpolator->SetInputImage(_spSourceFieldKernel->getField());

				for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
				{
					typename IteratorType::IndexType index = iterator.GetIndex();
					typename FieldType::PointType inPoint;
					spField->TransformIndexToPhysicalPoint(index, inPoint);
					typename SourceModelKernelType::OutputPointType interimPoint = _spSourceModelKernel->transformPoint(inPoint);

					typename SourceModelKernelType::OutputVectorType firstVector;
					PointVectorCombinationPolicy<VInputDimensions, VInterimDimensions>::computeVector(inPoint, interimPoint, firstVector);

					typename IteratorType::PixelType outVector(CombinationInterface::_paddingVector);

					if (!spInterpolator->IsInsideBuffer(interimPoint))
					{
						if (! CombinationInterface::_usePadding)
						{
							//throw the exception
							mapExceptionMacro(RepresentationException, << "Cannot combine kernels. Point is not inside supported region of second kernel. Point: " << interimPoint);
						}

						//otherwise just use padding vector
					}
					else
					{
						typename InterpolatorType::OutputType secondVector = spInterpolator->Evaluate(interimPoint);
						PointVectorCombinationPolicy<VInterimDimensions, VOutputDimensions>::combineVectors(firstVector, secondVector, outVector);
					}

					iterator.Set(outVector);
				}

				return spField;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceFieldKernelType *
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			getSourceFieldKernel(void) const
			{
				return _spSourceFieldKernel;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceModelKernelType *
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			getSourceModelKernel(void) const
			{
				return _spSourceModelKernel;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel1BaseType *
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get1stSourceKernelBase(void) const
			{
				return getSourceModelKernel();
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::SourceKernel2BaseType *
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			get2ndSourceKernelBase(void) const
			{
				return getSourceFieldKernel();
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			typename FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::Pointer
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			New(const SourceModelKernelType &modelKernel,
			    const SourceFieldKernelType &fieldKernel,
			    const InFieldRepresentationType *pInFieldRepresentation)
			{
				assert(pInFieldRepresentation);
				Pointer spFieldByModelFieldCombinationFunctor = new Self(modelKernel, fieldKernel, pInFieldRepresentation);
				spFieldByModelFieldCombinationFunctor->UnRegister();
				return spFieldByModelFieldCombinationFunctor;
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			::itk::LightObject::Pointer
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			CreateAnother(void) const
			{
				::itk::LightObject::Pointer smartPtr;
				Pointer spNew = Self::New(*_spSourceModelKernel, *_spSourceFieldKernel, Superclass::_spInFieldRepresentation).GetPointer();
				smartPtr = spNew;
				return smartPtr;
			}


			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			FieldByModelFieldCombinationFunctor(const SourceModelKernelType &modelKernel,
			                                    const SourceFieldKernelType &fieldKernel,
			                                    const InFieldRepresentationType *pInFieldRepresentation):
				Superclass(pInFieldRepresentation), _spSourceModelKernel(&modelKernel), _spSourceFieldKernel(&fieldKernel)
			{
				assert(pInFieldRepresentation);
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			~FieldByModelFieldCombinationFunctor()
			{
			}

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			void
			FieldByModelFieldCombinationFunctor<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			PrintSelf(std::ostream &os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "Source model kernel: " << _spSourceModelKernel << std::endl;
				os << indent << "Source field kernel: " << _spSourceFieldKernel << std::endl;
			}

		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
