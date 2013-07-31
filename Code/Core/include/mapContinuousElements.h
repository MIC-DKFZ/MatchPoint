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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapContinuousElements.h $
*/


#ifndef __MAP_CONTINUOUS_ELEMENTS_H
#define __MAP_CONTINUOUS_ELEMENTS_H

#include "mapContinuous.h"
#include "mapVolumeSize.h"

#include "itkPoint.h"
#include "itkVector.h"
#include "itkPointSet.h"
#include "itkDefaultStaticMeshTraits.h"

namespace map
{
	namespace core
	{
		namespace continuous
		{
			template <unsigned int VDimensions>
			struct Elements
			{
			public:
				typedef itk::Point<ScalarType, VDimensions>   PointType;
				typedef itk::Vector<ScalarType, VDimensions>  VectorType;
				typedef itk::Vector<ScalarType, VDimensions>  SpacingType;
				typedef VolumeSize<VDimensions>               VolumeSizeType;
				typedef itk::PointSet<ScalarType, VDimensions, itk::DefaultStaticMeshTraits<ScalarType, VDimensions, VDimensions, ScalarType> > InternalPointSetType;
			};

		} // end namespace continuous
	} // end namespace core
} // end namespace map

#endif
