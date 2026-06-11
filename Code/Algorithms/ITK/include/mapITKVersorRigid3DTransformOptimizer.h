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




#ifndef __ITK_VERSOR_RIGID_3D_TRANSFORM_OPTIMIZER_H
#define __ITK_VERSOR_RIGID_3D_TRANSFORM_OPTIMIZER_H

// Since ITK 5 itk::VersorRigid3DTransformOptimizer is just an alias for
// itk::VersorTransformOptimizer, so the template specialization of
// ITKOptimizerControl lives in mapITKVersorTransformOptimizer.h and serves
// both type names; defining it here as well would be a redefinition.
#include "mapITKVersorTransformOptimizer.h"
#include "itkVersorRigid3DTransformOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			typedef ITKOptimizerControl< ::itk::VersorRigid3DTransformOptimizer>
			VersorRigid3DTransformOptimizerControl;

		}
	}
}

#endif
