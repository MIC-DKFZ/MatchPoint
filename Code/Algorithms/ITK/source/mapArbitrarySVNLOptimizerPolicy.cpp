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



#include "mapArbitrarySVNLOptimizerPolicy.h"
#include "mapAlgorithmEvents.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{


			unsigned long
			ArbitrarySVNLOptimizerPolicy::
			GetMTime() const
			{
				unsigned long mt = _mTime.getMTime();
				return mt;
			};

			void
			ArbitrarySVNLOptimizerPolicy::
			setAutomaticOptimizationDirection(bool automatic)
			{
				_automaticOptimizationDirection = automatic;
			};

			bool
			ArbitrarySVNLOptimizerPolicy::
			getAutomaticOptimizationDirection() const
			{
				return _automaticOptimizationDirection;
			};

			void
			ArbitrarySVNLOptimizerPolicy::
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

			ArbitrarySVNLOptimizerPolicy::
			ArbitrarySVNLOptimizerPolicy() : _automaticOptimizationDirection(true)
			{
			};

			ArbitrarySVNLOptimizerPolicy::
			~ArbitrarySVNLOptimizerPolicy()
			{
			};

			ArbitrarySVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitrarySVNLOptimizerPolicy::
			getOptimizerInternal()
			{
				return _spOptimizerControl;
			}

			const ArbitrarySVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitrarySVNLOptimizerPolicy::
			getOptimizerInternal() const
			{
				return _spOptimizerControl;
			}

			ArbitrarySVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitrarySVNLOptimizerPolicy::
			getITKOptimizerControl()
			{
				return _spOptimizerControl;
			}

			const ArbitrarySVNLOptimizerPolicy::ITKOptimizerControlType*
			ArbitrarySVNLOptimizerPolicy::
			getITKOptimizerControl() const
			{
				return _spOptimizerControl;
			}

			ArbitrarySVNLOptimizerPolicy::OptimizerControlType*
			ArbitrarySVNLOptimizerPolicy::
			getOptimizerControl()
			{
				return _spOptimizerControl;
			}

			const ArbitrarySVNLOptimizerPolicy::OptimizerControlType*
			ArbitrarySVNLOptimizerPolicy::
			getOptimizerControl() const
			{
				return _spOptimizerControl;
			}

			void
			ArbitrarySVNLOptimizerPolicy::
			prepareOptimizer()
			{
				//default implementation does nothing;
			};


			void
			ArbitrarySVNLOptimizerPolicy::
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