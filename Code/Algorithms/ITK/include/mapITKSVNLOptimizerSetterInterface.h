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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKSVNLOptimizerSetterInterface.h $
*/




#ifndef __ITK_OPTIMIZER_SETTER_INTERFACE_H
#define __ITK_OPTIMIZER_SETTER_INTERFACE_H

#include "itkOptimizer.h"

#include "mapITKSVNLOptimizerControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKSVNLOptimizerSetterInterface
			 * Interface inherited by every algorithm that is able to set or change (none const getter) an optimizer
			 @ingroup AlgorithmFacets
			 */
			class MAPAlgorithmsITK_EXPORT ITKSVNLOptimizerSetterInterface
			{
			public:
				typedef ITKSVNLOptimizerSetterInterface Self;

				typedef algorithm::itk::ITKSVNLOptimizerControlInterface ITKOptimizerControlType;

				/*! sets the optimizer
				  @eguarantee strong
				  @param optimizer the optimizer
				 */
				virtual void setITKOptimizerControl(ITKOptimizerControlType *pOptimizer) = 0;

			protected:
				ITKSVNLOptimizerSetterInterface() {};
				virtual ~ITKSVNLOptimizerSetterInterface() {};

			private:
				//No copy constructor allowed
				ITKSVNLOptimizerSetterInterface(const Self &source);
				void operator=(const Self &); //purposely not implemented

			};
		}
	}
}


#endif
