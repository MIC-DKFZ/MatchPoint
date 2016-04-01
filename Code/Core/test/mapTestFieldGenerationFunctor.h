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

#include "mapTransformGenerationFunctor.h"
#include "mapArtifactGenerator.h"

#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class TestFieldGenerationFunctor : public
			map::core::functors::TransformGenerationFunctor<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef TestFieldGenerationFunctor<VInputDimensions, VOutputDimensions>  Self;
      typedef map::core::functors::TransformGenerationFunctor<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;
			typedef typename Superclass::InFieldRepresentationType InFieldRepresentationType;
      typedef typename Superclass::TransformType TransformType;
      typedef typename Superclass::TransformPointer TransformPointer;

			itkTypeMacro(TestFieldGenerationFunctor, FieldGenerationFunctor);

			static Pointer New(const InFieldRepresentationType* pInFieldRepresentation)
			{
				Pointer smartPtr = new Self(pInFieldRepresentation);
				smartPtr->UnRegister();
				return smartPtr;
			}

      virtual TransformPointer generateTransform() const
			{
          _spCurrentTransform = convertFieldToTransform<VOutputDimensions>(testing::generateSumField<VOutputDimensions>(Superclass::_spInFieldRepresentation));
          return _spCurrentTransform;
			}

      mutable TransformPointer _spCurrentTransform;

		protected:

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
