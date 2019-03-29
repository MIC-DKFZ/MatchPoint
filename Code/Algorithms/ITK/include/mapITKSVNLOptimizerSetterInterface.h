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
				using Self = ITKSVNLOptimizerSetterInterface;

				using ITKOptimizerControlType = algorithm::itk::ITKSVNLOptimizerControlInterface;

				/*! sets the optimizer
				  @eguarantee strong
				  @param optimizer the optimizer
				 */
				virtual void setITKOptimizerControl(ITKOptimizerControlType* pOptimizer) = 0;

			protected:
				ITKSVNLOptimizerSetterInterface() = default;
				virtual ~ITKSVNLOptimizerSetterInterface() = default;

			private:
				//No copy constructor allowed
				ITKSVNLOptimizerSetterInterface(const Self& source) = delete;
				void operator=(const Self&) = delete;  //purposely not implemented

			};
		}  // namespace facet
	}  // namespace algorithm
}  // namespace map


#endif
