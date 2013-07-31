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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapTransformModelBase.tpp $
*/




#ifndef __TRANSFORM_MODEL_BASE_TPP
#define __TRANSFORM_MODEL_BASE_TPP

#include "mapTransformModelBase.h"

namespace map
{
	namespace core
	{

		/*! @brief Base class for the transform model representation in MatchPoint.
		 * It serves as a wrapper arround itk:Transform to extend the transform interface
		 * by special features needed by MatchPoint. E.g.: the GetInverse() method of itk:Transform
		 * is non virutal and only suitable for symmetric transforms (input and output space have the
		 * same dimensions).
		 *
		 * \ingroup TransformModel
		 */
		template<class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>::
		TransformModelBase()
		{
		};

		template<class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>::
		~TransformModelBase()
		{
		};

		template<class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream &os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent << "Input dimensions:  " << VInputDimensions << std::endl;
			os << indent << "Output dimensions: " << VOutputDimensions << std::endl;
			os << indent << "Transform: " <<  std::endl;
			getTransform()->Print(os, indent.GetNextIndent());
			os << indent << std::endl;
		};

		template<class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		std::ostream &operator<<(std::ostream &os, const TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions> &model)
		{
			::itk::Indent indent;
			model.Print(os, indent);
			return os;
		};

	}
}

#endif
