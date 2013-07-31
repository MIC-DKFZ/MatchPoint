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
// @version $Revision: 4910 $ (last changed revision)
// @date    $Date: 2013-07-30 14:08:21 +0200 (Di, 30 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapDiscreteElements.h $
*/


#ifndef __MAP_DISCRETE_ELEMENTS_H
#define __MAP_DISCRETE_ELEMENTS_H

#include "mapContinuousElements.h"
#include "mapDiscrete.h"

#include "itkImage.h"
#include "itkSize.h"

namespace map
{
	namespace core
	{
		namespace discrete
		{
			template <unsigned int VDimensions>
			struct Elements
			{
			public:
				typedef itk::Image<InternalPixelType, VDimensions> InternalImageType;
				typedef typename InternalImageType::RegionType ImageRegionType;
				typedef itk::Image< typename ::map::core::continuous::Elements<VDimensions>::VectorType, VDimensions> VectorFieldType;
				typedef itk::Size<VDimensions> SizeType;
			};

		} // end namespace continuous
	} // end namespace core
} // end namespace map

#endif
