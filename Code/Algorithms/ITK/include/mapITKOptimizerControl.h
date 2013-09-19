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




#ifndef __ITK_OPTIMIZER_CONTROL_H
#define __ITK_OPTIMIZER_CONTROL_H

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKOptimizerControl
			This class is the master definition for the template specialization.
			It is a dummy and not for practical use. For every optimizer there must be a proper
			specialization of this class (using the right interfaces and implementing the
			abstract functions).
			To define a controller for a special optimizer use template specialization
			(template<> class ITKOptimizerControl<itk::MySpecialOptimizer>)
			and reimplement the class interface.
			See e.g. ITKOptimizerControl<itk::PowellOptimizer> as an specialized example.
			@remark specialized ITKOptimizerControl should instantiates a concrete optimizer
			when constructed. You can set a new one, but ITKOptimizerControl has always an
			optimizer under control.
			@template TConcreteOptimizer type of the concrete optimizer controlled by the class
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<class TConcreteOptimizer>
			class ITKOptimizerControl;
		}
	}
}

#endif
