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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapArtifactGenerator.h $
*/

#ifndef __MAP_ARTIFACT_GENERATOR_H
#define __MAP_ARTIFACT_GENERATOR_H

#include "mapDiscreteElements.h"
#include "mapFieldRepresentationDescriptor.h"

namespace map
{
	namespace testing
	{

		/** generates a vector field by a scaletransform (0.3 x and 0.4 y factor)*/
		core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleField(const core::FieldRepresentationDescriptor<2> *pRepDesc);
		/** generates a vector field by a scaletransform (0.3 x and 0.4 y factor) and a NULL vector in the pixel with index (1,1).*/
		core::discrete::Elements<2>::VectorFieldType::Pointer generate2DScaleFieldWithNull(const core::FieldRepresentationDescriptor<2> *pRepDesc, const map::core::continuous::Elements<2>::VectorType &nullVector);

	} // end namespace testing
} // end namespace map

#endif
