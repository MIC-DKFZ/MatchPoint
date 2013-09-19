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




#ifndef __ITK_SVNL_OPTIMIZER_CONTROL_INTERFACE_H
#define __ITK_SVNL_OPTIMIZER_CONTROL_INTERFACE_H

#include "itkSingleValuedNonLinearOptimizer.h"

#include "mapITKOptimizerControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKSVNLOptimizerControlInterface
			@brief Interface for controller classes that form a virtual wrapper around itk single valued
			non linear optimizers.
			This wrapper is used because stopping the optimizer is not covered by the polymorphic class
			design of itk::optimizer. Therefor there is no native and general way to stop an itk::optimizer
			or at least check if it can be stopped.
			@ingroup ITK
			*/
			class MAPAlgorithmsITK_EXPORT ITKSVNLOptimizerControlInterface : public ITKOptimizerControlInterface
			{
			public:
				typedef ITKSVNLOptimizerControlInterface Self;
				typedef ITKOptimizerControlInterface Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKSVNLOptimizerControlInterface, ITKOptimizerControlInterface);

				typedef ::itk::SingleValuedNonLinearOptimizer SVNLOptimizerBaseType;
				typedef SVNLOptimizerBaseType::MeasureType    SVNLMeasureType;
				typedef OptimizerControlInterface::OptimizerMeasureType OptimizerMeasureType;

				virtual SVNLOptimizerBaseType* getSVNLOptimizer() = 0;
				virtual const SVNLOptimizerBaseType* getSVNLOptimizer() const = 0;

				/*! @brief gets the current value/cost of the optimizer iteration
				  @eguarantee strong
				  @return returns the optimizers current value/cost
				 */
				virtual SVNLMeasureType getCurrentMeasure() const;

			protected:
				ITKSVNLOptimizerControlInterface();
				virtual ~ITKSVNLOptimizerControlInterface();

				/*! return the cost of the current iteration step.
				Will be called by getCurrentValue() if hasCurrentValue() returns true.
				@eguarantee strong
				@return current measure
				*/
				virtual SVNLMeasureType doGetCurrentMeasure() const = 0;

				/*! Will  be called to get the current value/cost of the optimizer iteration
				 * calls doGetCurrentMeasure() and converts the result into the more general
				 * OptimizerMeasureType.
				@eguarantee strong
				@return returns the optimizers current value/cost
				*/
				virtual OptimizerMeasureType doGetCurrentValue() const;

			private:
				//No copy constructor allowed
				ITKSVNLOptimizerControlInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#endif
