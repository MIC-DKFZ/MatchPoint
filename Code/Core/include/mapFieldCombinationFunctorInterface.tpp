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


#ifndef __MAP_FIELD_COMBINATION_FUNCTOR_INTERFACE_TPP
#define __MAP_FIELD_COMBINATION_FUNCTOR_INTERFACE_TPP

#include "mapFieldCombinationFunctorInterface.h"

namespace map
{
	namespace core
	{
		namespace functors
		{

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			void
			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			setUsePadding(bool usePadding)
			{
				_usePadding = usePadding;
			};

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			void
			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			setPaddingVector(const PaddingVectorType& vector)
			{
				_paddingVector = vector;
			};

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			bool
			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			getUsePadding() const
			{
				return _usePadding;
			};

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			const typename
			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::PaddingVectorType&

			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			getPaddingVector() const
			{
				return _paddingVector;
			};

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			FieldCombinationFunctorInterface() : _usePadding(false)
			{
				_paddingVector.Fill(0.0);
			};

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			~FieldCombinationFunctorInterface() {};

			template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
			void
			FieldCombinationFunctorInterface<VInputDimensions, VInterimDimensions, VOutputDimensions>::
			PrintSelf(std::ostream& os, itk::Indent indent) const
			{
				os << indent << "Use padding:    " << _usePadding << std::endl;
				os << indent << "Padding vector: " << _paddingVector << std::endl;
			};

		} // end namespace functors
	} // end namespace core
} // end namespace map

#endif
