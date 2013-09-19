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

#ifndef __MAP_TEST_FIELD_GENERATION_FUNCTOR_H
#define __MAP_TEST_FIELD_GENERATION_FUNCTOR_H

#include "mapFieldGenerationFunctor.h"

#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class TestFieldGenerationFunctor : public
			map::core::functors::FieldGenerationFunctor<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef TestFieldGenerationFunctor<VInputDimensions, VOutputDimensions>  Self;
			typedef map::core::functors::FieldGenerationFunctor<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;
			typedef typename Superclass::InFieldRepresentationType InFieldRepresentationType;
			typedef typename Superclass::FieldType FieldType;
			typedef typename Superclass::FieldPointer FieldPointer;

			itkTypeMacro(TestFieldGenerationFunctor, FieldGenerationFunctor);

			static Pointer New(const InFieldRepresentationType* pInFieldRepresentation)
			{
				Pointer smartPtr = new Self(pInFieldRepresentation);
				smartPtr->UnRegister();
				return smartPtr;
			}

			virtual FieldPointer generateField() const
			{
				FieldPointer spFieldPointer = doGenerateField();
				_spCurrentFieldPointer = spFieldPointer;
				return spFieldPointer;
			}

			mutable FieldPointer _spCurrentFieldPointer;

		protected:

			FieldPointer doGenerateField() const
			{
				FieldPointer spField = FieldType::New();

				typedef itk::ImageRegionIterator< FieldType > IteratorType;
				typename InFieldRepresentationType::ImageRegionType region =
					Superclass::_spInFieldRepresentation->getRepresentedLocalImageRegion();

				spField->SetRegions(region);
				spField->SetSpacing(Superclass::_spInFieldRepresentation->getSpacing());
				spField->Allocate();

				IteratorType iterator(spField, spField->GetLargestPossibleRegion());

				for (iterator.GoToBegin(); !(iterator.IsAtEnd()); ++iterator)
				{
					typename FieldType::IndexType index = iterator.GetIndex();
					typename FieldType::ValueType value;
					value.Fill(index[0] + index[1]);

					iterator.Set(value);
				}

				return spField;
			}

			TestFieldGenerationFunctor(const InFieldRepresentationType* pInFieldRepresentation):
				Superclass(pInFieldRepresentation)
			{};

			virtual ~TestFieldGenerationFunctor() {};

		private:
			TestFieldGenerationFunctor(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};


	} // end namespace testing
} // end namespace map

#endif
