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



#include "mapArbitraryMVNLOptimizerPolicy.h"
#include "mapAlgorithmEvents.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{


			unsigned long
			ArbitraryMVNLOptimizerPolicy::
			GetMTime() const
			{
				unsigned long mt = _mTime.getMTime();
				return mt;
			};

			void
			ArbitraryMVNLOptimizerPolicy::
			setAutomaticOptimizationDirection(bool automatic)
			{
				_automaticOptimizationDirection = automatic;
			};

			bool
			ArbitraryMVNLOptimizerPolicy::
			getAutomaticOptimizationDirection() const
			{
				return _automaticOptimizationDirection;
			};

			void
			ArbitraryMVNLOptimizerPolicy::
			setITKOptimizerControl(ITKOptimizerControlType* pOptimizer)
			{
				if (pOptimizer != _spOptimizerControl.GetPointer())
				{
					//there is really the need to change the optimizer
					if (this->_spOnChange.IsNotNull())
					{
						::map::events::UnregisterAlgorithmComponentEvent unRegEvent(_spOptimizerControl.GetPointer(),
								"Unregister current optimizer");
						this->_spOnChange->Execute((::itk::Object*)NULL, unRegEvent);
					}

					_mTime.setWatchedObject(pOptimizer);
					_spOptimizerControl  = pOptimizer;

					if (this->_spOnChange.IsNotNull())
					{
						::map::events::RegisterAlgorithmComponentEvent regEvent(_spOptimizerControl.GetPointer(),
								"Register new optimizer");
						this->_spOnChange->Execute((::itk::Object*)NULL, regEvent);
					}
				}
			};

			ArbitraryMVNLOptimizerPolicy::
			ArbitraryMVNLOptimizerPolicy() : _automaticOptimizationDirection(true)
			{
			};

			ArbitraryMVNLOptimizerPolicy::
			~ArbitraryMVNLOptimizerPolicy()
			{
			};

			ArbitraryMVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitraryMVNLOptimizerPolicy::
			getOptimizerInternal()
			{
				return _spOptimizerControl;
			}

			const ArbitraryMVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitraryMVNLOptimizerPolicy::
			getOptimizerInternal() const
			{
				return _spOptimizerControl;
			}

			ArbitraryMVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitraryMVNLOptimizerPolicy::
			getITKOptimizerControl()
			{
				return _spOptimizerControl;
			}

			const ArbitraryMVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitraryMVNLOptimizerPolicy::
			getITKOptimizerControl() const
			{
				return _spOptimizerControl;
			}

			ArbitraryMVNLOptimizerPolicy::OptimizerControlType*
			ArbitraryMVNLOptimizerPolicy::
			getOptimizerControl()
			{
				return _spOptimizerControl;
			}

			const ArbitraryMVNLOptimizerPolicy::OptimizerControlType*
			ArbitraryMVNLOptimizerPolicy::
			getOptimizerControl() const
			{
				return _spOptimizerControl;
			}

			void
			ArbitraryMVNLOptimizerPolicy::
			prepareOptimizer()
			{
				//default implementation does nothing;
			};


			void
			ArbitraryMVNLOptimizerPolicy::
			prepareOptimizerAfterAssembly(bool minimizeToOptimize)
			{
				if (_automaticOptimizationDirection)
				{
					_spOptimizerControl->setMinimize(minimizeToOptimize);
				}
			};
		}
	}
}