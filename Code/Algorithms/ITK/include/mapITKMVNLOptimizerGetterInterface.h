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




#ifndef __ITK_MVNL_OPTIMIZER_GETTER_INTERFACE_H
#define __ITK_MVNL_OPTIMIZER_GETTER_INTERFACE_H

#include "itkOptimizer.h"

#include "mapITKMVNLOptimizerControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKMVNLOptimizerGetterInterface
			 * Interface inherited by every algorithm that is able to get or change (none const getter) a multiple valued non linear optimizer
			 @ingroup AlgorithmFacets
			 */
			class MAPAlgorithmsITK_EXPORT ITKMVNLOptimizerGetterInterface
			{
			public:
				typedef ITKMVNLOptimizerGetterInterface Self;

				typedef algorithm::itk::ITKMVNLOptimizerControlInterface ITKOptimizerControlType;

				/*! @brief gets the optimizer
				  @eguarantee no fail
				  @return pointer to an OptimizerControlType object
				 */
				virtual ITKOptimizerControlType* getITKOptimizerControl() = 0;
				/*! @brief gets the optimizer
				  @eguarantee no fail
				  @return pointer to an OptimizerControlType object
				 */
				virtual const ITKOptimizerControlType* getITKOptimizerControl() const = 0;

			protected:
				ITKMVNLOptimizerGetterInterface() {};
				virtual ~ITKMVNLOptimizerGetterInterface() {};

			private:
				//No copy constructor allowed
				ITKMVNLOptimizerGetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};
		}
	}
}


#endif
