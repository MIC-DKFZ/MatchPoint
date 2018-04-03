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


#ifndef __SEALED_OPTIMIZER_POLICY_TPP
#define __SEALED_OPTIMIZER_POLICY_TPP

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteOptimizer>
			typename SealedOptimizerPolicy<TConcreteOptimizer>::ConcreteOptimizerType*
			SealedOptimizerPolicy<TConcreteOptimizer>::
			getConcreteITKOptimizer()
			{
				return _spOptimizerControl->getConcreteOptimizer();
			};

			template<class TConcreteOptimizer>
			const typename SealedOptimizerPolicy<TConcreteOptimizer>::ConcreteOptimizerType*
			SealedOptimizerPolicy<TConcreteOptimizer>::
			getConcreteITKOptimizer() const
			{
				return _spOptimizerControl->getConcreteOptimizer();
			};

			template<class TConcreteOptimizer>
			const typename SealedOptimizerPolicy<TConcreteOptimizer>::ConcreteOptimizerControlType*
			SealedOptimizerPolicy<TConcreteOptimizer>::
			getConcreteOptimizerControl() const
			{
				return _spOptimizerControl;
			};

			template<class TConcreteOptimizer>
			typename SealedOptimizerPolicy<TConcreteOptimizer>::ConcreteOptimizerControlType*
			SealedOptimizerPolicy<TConcreteOptimizer>::
			getConcreteOptimizerControl()
			{
				return _spOptimizerControl;
			};

			template<class TConcreteOptimizer>
			SealedOptimizerPolicy<TConcreteOptimizer>::
			SealedOptimizerPolicy()
			{
				_spOptimizerControl = ConcreteOptimizerControlType::New();
			};

			template<class TConcreteOptimizer>
			SealedOptimizerPolicy<TConcreteOptimizer>::
			~SealedOptimizerPolicy() {};

			template<class TConcreteOptimizer>
			typename SealedOptimizerPolicy<TConcreteOptimizer>::InternalOptimizerControlType*
			SealedOptimizerPolicy<TConcreteOptimizer>::
			getOptimizerInternal()
			{
				return _spOptimizerControl;
			};

			template<class TConcreteOptimizer>
			const typename SealedOptimizerPolicy<TConcreteOptimizer>::InternalOptimizerControlType*
			SealedOptimizerPolicy<TConcreteOptimizer>::
			getOptimizerInternal() const
			{
				return _spOptimizerControl;
			};

			template<class TConcreteOptimizer>
			void
			SealedOptimizerPolicy<TConcreteOptimizer>::
			prepareOptimizer()
			{
				//default implementation does nothing;
			};

			template<class TConcreteOptimizer>
			void
			SealedOptimizerPolicy<TConcreteOptimizer>::
			prepareOptimizerAfterAssembly(bool minimizeToOptimize)
			{
				_spOptimizerControl->setMinimize(minimizeToOptimize);
			};

			template<class TConcreteOptimizer>
			unsigned long
			SealedOptimizerPolicy<TConcreteOptimizer>::
			GetMTime() const
			{
				unsigned long mt = _mTime.GetMTime();

				if (mt < _spOptimizerControl->GetMTime())
				{
					mt = _spOptimizerControl->GetMTime();
				}

				return mt;
			};

			template<class TConcreteOptimizer>
			void
			SealedOptimizerPolicy<TConcreteOptimizer>::
			indicateModification() const
			{
				_mTime.Modified();
			};

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
