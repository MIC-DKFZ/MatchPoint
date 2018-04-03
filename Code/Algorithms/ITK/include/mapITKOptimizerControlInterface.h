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




#ifndef __ITK_OPTIMIZER_CONTROL_INTERFACE_H
#define __ITK_OPTIMIZER_CONTROL_INTERFACE_H

#include "itkObject.h"
#include "itkOptimizer.h"

#include "mapOptimizerControlInterface.h"
#include "mapMAPAlgorithmsITKExports.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKOptimizerControlInterface
			@brief Interface for controller classes that form a virtual wrapper around itk optimizers.
			This wrapper is used because stopping the optimizer is not covered by the polymorphic class
			design of itk::optimizer. Therefor there is no native and general way to stop an itk::optimizer
			or at least check if it can be stopped.
			@ingroup ITK
			*/
			class MAPAlgorithmsITK_EXPORT ITKOptimizerControlInterface : public ::itk::Object,
				public OptimizerControlInterface
			{
			public:
				typedef ITKOptimizerControlInterface Self;
				typedef ::itk::Object Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKOptimizerControlInterface, itk::Object);

				typedef ::itk::Optimizer OptimizerBaseType;

				virtual OptimizerBaseType* getOptimizer() = 0;
				virtual const OptimizerBaseType* getOptimizer() const = 0;

				/*! clones the optimizer control and the controlled optimizer.
				 * @remark: The function guarantees that all settings of controlled optimizer
				 * are cloned, but its optimization state must not be cloned as well. Thus the function
				 * guarantees the same like instancing the same class again and transferring all properties
				 * of the source instance to the destination instance via setter and getter.
				 * @remark: It is a "deep" copy,so the controlled optimizer is a new instance as well.
				 * @eguarantee strong
				 * @remark Implement the function for special optimizer control classes.
				 * @return Smartpointer to the cloned optimizer control.*/
				virtual Pointer clone() const = 0;

				virtual const core::String getStopConditionDescription() const;

			protected:
				ITKOptimizerControlInterface();
				virtual ~ITKOptimizerControlInterface();

			private:
				//No copy constructor allowed
				ITKOptimizerControlInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#endif
