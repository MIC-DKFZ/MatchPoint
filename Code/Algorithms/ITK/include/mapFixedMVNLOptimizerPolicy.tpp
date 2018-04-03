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


#ifndef __FIXED_MVNL_OPTIMIZER_POLICY_TPP
#define __FIXED_MVNL_OPTIMIZER_POLICY_TPP

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteOptimizer>
			const typename FixedMVNLOptimizerPolicy<TConcreteOptimizer>::OptimizerControlType*
			FixedMVNLOptimizerPolicy<TConcreteOptimizer>::
			getOptimizerControl() const
			{
				return Superclass::getOptimizerInternal();
			};

			template<class TConcreteOptimizer>
			typename FixedMVNLOptimizerPolicy<TConcreteOptimizer>::OptimizerControlType*
			FixedMVNLOptimizerPolicy<TConcreteOptimizer>::
			getOptimizerControl()
			{
				return Superclass::getOptimizerInternal();
			};

			template<class TConcreteOptimizer>
			const typename FixedMVNLOptimizerPolicy<TConcreteOptimizer>::ITKOptimizerControlType*
			FixedMVNLOptimizerPolicy<TConcreteOptimizer>::
			getITKOptimizerControl() const
			{
				return Superclass::getOptimizerInternal();
			};

			template<class TConcreteOptimizer>
			typename FixedMVNLOptimizerPolicy<TConcreteOptimizer>::ITKOptimizerControlType*
			FixedMVNLOptimizerPolicy<TConcreteOptimizer>::
			getITKOptimizerControl()
			{
				return Superclass::getOptimizerInternal();
			};

			template<class TConcreteOptimizer>
			FixedMVNLOptimizerPolicy<TConcreteOptimizer>::
			FixedMVNLOptimizerPolicy()
			{
			};

			template<class TConcreteOptimizer>
			FixedMVNLOptimizerPolicy<TConcreteOptimizer>::
			~FixedMVNLOptimizerPolicy() {};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
