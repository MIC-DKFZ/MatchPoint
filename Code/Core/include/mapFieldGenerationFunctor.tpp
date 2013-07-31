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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldGenerationFunctor.tpp $
*/


#ifndef __MAP_FIELD_GENERATION_FUNCTOR_TPP
#define __MAP_FIELD_GENERATION_FUNCTOR_TPP

#include "mapFieldGenerationFunctor.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			const typename FieldGenerationFunctor<VInputDimensions, VOutputDimensions>::InFieldRepresentationType *
			FieldGenerationFunctor<VInputDimensions, VOutputDimensions>::
			getInFieldRepresentation(void) const
			{
				return _spInFieldRepresentation;
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldGenerationFunctor<VInputDimensions, VOutputDimensions>::
			FieldGenerationFunctor(const InFieldRepresentationType *pInFieldRepresentation):
				_spInFieldRepresentation(pInFieldRepresentation)
			{
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			FieldGenerationFunctor<VInputDimensions, VOutputDimensions>::
			~FieldGenerationFunctor()
			{
			};

			template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
			void
			FieldGenerationFunctor<VInputDimensions, VOutputDimensions>::
			PrintSelf(std::ostream &os, itk::Indent indent) const
			{
				Superclass::PrintSelf(os, indent);
				os << indent << "In field representation: " << std::endl << _spInFieldRepresentation << std::endl;
			};


		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
