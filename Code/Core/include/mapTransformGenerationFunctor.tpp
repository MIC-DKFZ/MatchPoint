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


#ifndef __MAP_TRANSFORM_GENERATION_FUNCTOR_TPP
#define __MAP_TRANSFORM_GENERATION_FUNCTOR_TPP

#include "mapTransformGenerationFunctor.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const typename
			TransformGenerationFunctor<VInputDimensions, VOutputDimensions>::InFieldRepresentationType*
			TransformGenerationFunctor<VInputDimensions, VOutputDimensions>::
			getInFieldRepresentation(void) const
			{
				return _spInFieldRepresentation;
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			TransformGenerationFunctor<VInputDimensions, VOutputDimensions>::
			TransformGenerationFunctor(const InFieldRepresentationType* pInFieldRepresentation):
            _spInFieldRepresentation(pInFieldRepresentation), _useNullPoint(false)
			{
                _nullPoint.Fill(itk::NumericTraits<map::core::continuous::ScalarType>::NonpositiveMin());
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			TransformGenerationFunctor<VInputDimensions, VOutputDimensions>::
			~TransformGenerationFunctor()
			{
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			TransformGenerationFunctor<VInputDimensions, VOutputDimensions>::
			PrintSelf(std::ostream& os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "In field representation: " << std::endl << _spInFieldRepresentation << std::endl;
			};


		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
