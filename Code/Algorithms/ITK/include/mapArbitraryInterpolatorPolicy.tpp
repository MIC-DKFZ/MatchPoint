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


#include "mapAlgorithmEvents.h"

#ifndef __ARBITRARY_INTERPOLATOR_POLICY_TPP
#define __ARBITRARY_INTERPOLATOR_POLICY_TPP

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TInputImage, class TCoordRep>
			unsigned long
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			GetMTime() const
			{
				unsigned long mt = _mTime.getMTime();
				return mt;
			};

			template<class TInputImage, class TCoordRep>
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			ArbitraryInterpolatorPolicy()
			{
			}

			template<class TInputImage, class TCoordRep>
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			~ArbitraryInterpolatorPolicy()
			{
			}


			template<class TInputImage, class TCoordRep>
			typename ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::InterpolatorType*
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			getInterpolatorInternal()
			{
				return _spInterpolator;
			}

			template<class TInputImage, class TCoordRep>
			const typename ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::InterpolatorType*
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			getInterpolatorInternal() const
			{
				return _spInterpolator;
			}

			template<class TInputImage, class TCoordRep>
			typename ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::InterpolatorType*
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			getInterpolator()
			{
				return _spInterpolator;
			}

			template<class TInputImage, class TCoordRep>
			const typename ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::InterpolatorType*
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			getInterpolator() const
			{
				return _spInterpolator;
			}

			template<class TInputImage, class TCoordRep>
			void
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			setInterpolator(InterpolatorType* pInterpolator)
			{
				if (pInterpolator != _spInterpolator.GetPointer())
				{
					//there is really the need to change
					if (this->_spOnChange.IsNotNull())
					{
						::map::events::UnregisterAlgorithmComponentEvent unRegEvent(_spInterpolator.GetPointer(),
								"Unregister current interpolator");
						this->_spOnChange->Execute((::itk::Object*)NULL, unRegEvent);
					}

					_spInterpolator  = pInterpolator;
					_mTime.setWatchedObject(pInterpolator);

					if (this->_spOnChange.IsNotNull())
					{
						::map::events::RegisterAlgorithmComponentEvent regEvent(_spInterpolator.GetPointer(),
								"Register new interpolator");
						this->_spOnChange->Execute((::itk::Object*)NULL, regEvent);
					}
				}
			}

			template<class TInputImage, class TCoordRep>
			void
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			prepareInterpolator()
			{
				//default implementation does nothing;
			}

			template<class TInputImage, class TCoordRep>
			void
			ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>::
			prepareInterpolatorAfterAssembly()
			{
				//default implementation does nothing;
			}

		}
	}
}

#endif
