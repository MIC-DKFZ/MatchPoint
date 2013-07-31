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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldByModelFunctor.tpp $
*/

#ifndef __MAP_FIELD_BY_MODEL_FUNCTOR_TPP
#define __MAP_FIELD_BY_MODEL_FUNCTOR_TPP

#include "mapFieldByModelFunctor.h"
#include "mapLogbookMacros.h"

#include "itkImageRegionIterator.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByModelFunctor<VInputDimensions, VOutputDimensions>::FieldPointer
			FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
			generateField() const
			{
				mapLogInfoMacro( << "Generate field by model sampling");

				FieldPointer spField = FieldType::New();

				typedef itk::ImageRegionIterator< FieldType > IteratorType;

				typename FieldType::RegionType region = Superclass::_spInFieldRepresentation->getRepresentedLocalImageRegion();

				//allocate image memory
				spField->SetRegions(region);
				spField->SetSpacing(Superclass::_spInFieldRepresentation->getSpacing());
				spField->SetOrigin(Superclass::_spInFieldRepresentation->getOrigin());
				spField->SetDirection(Superclass::_spInFieldRepresentation->getDirection());
				spField->Allocate();

				//sample the transform into a vector field
				IteratorType iterator(spField, spField->GetLargestPossibleRegion());

				for (iterator.GoToBegin(); !(iterator.IsAtEnd()); ++iterator)
				{
					typename FieldType::IndexType index = iterator.GetIndex();
					typename FieldType::PointType inPoint;
					spField->TransformIndexToPhysicalPoint(index, inPoint);

					typename TransformModelType::OutputPointType outPoint = _spTransformModel->getTransform()->TransformPoint(inPoint);

					typename FieldType::ValueType value = outPoint - inPoint;
					iterator.Set(value);
				}

				return spField;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const typename FieldByModelFunctor<VInputDimensions, VOutputDimensions>::TransformModelType *
			FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
			getTransformModel(void) const
			{
				return _spTransformModel;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			typename FieldByModelFunctor<VInputDimensions, VOutputDimensions>::Pointer
			FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
			New(const TransformModelType &model,
			    const InFieldRepresentationType *pInFieldRepresentation)
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
				smartPtr = Self::New(*_spTransformModel, Superclass::_spInFieldRepresentation).GetPointer();
				return smartPtr;
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
			FieldByModelFunctor(const TransformModelType &model,
			                    const InFieldRepresentationType *pInFieldRepresentation):
				Superclass(pInFieldRepresentation), _spTransformModel(&model)
			{
				assert(pInFieldRepresentation);
			}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
			~FieldByModelFunctor() {}

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			FieldByModelFunctor<VInputDimensions, VOutputDimensions>::
			PrintSelf(std::ostream &os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "Transform model: " << _spTransformModel << std::endl;
			}


		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
