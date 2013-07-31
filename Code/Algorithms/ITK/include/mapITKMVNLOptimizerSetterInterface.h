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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKMVNLOptimizerSetterInterface.h $
*/




#ifndef __ITK_MVNL_OPTIMIZER_SETTER_INTERFACE_H
#define __ITK_MVNL_OPTIMIZER_SETTER_INTERFACE_H

#include "mapITKMVNLOptimizerControlInterface.h"

#include "itkOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKMVNLOptimizerSetterInterface
			 * Interface inherited by every algorithm that is able to set or change (none const getter) a multiple valued non linear optimizer
			 @ingroup AlgorithmFacets
			 */
			class MAPAlgorithmsITK_EXPORT ITKMVNLOptimizerSetterInterface
			{
			public:
				typedef ITKMVNLOptimizerSetterInterface Self;

				typedef algorithm::itk::ITKMVNLOptimizerControlInterface ITKOptimizerControlType;

				/*! sets the optimizer
				  @eguarantee strong
				  @param optimizer the optimizer
				 */
				virtual void setITKOptimizerControl(ITKOptimizerControlType *pOptimizer) = 0;

			protected:
				ITKMVNLOptimizerSetterInterface() {};
				virtual ~ITKMVNLOptimizerSetterInterface() {};

			private:
				//No copy constructor allowed
				ITKMVNLOptimizerSetterInterface(const Self &source);
				void operator=(const Self &); //purposely not implemented

			};
		}
	}
}


#endif
