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


#ifndef __ARBITRARY_POINT_SET_TO_POINT_SET_METRIC_POLICY_TPP
#define __ARBITRARY_POINT_SET_TO_POINT_SET_METRIC_POLICY_TPP

#include "mapAlgorithmEvents.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TMovingPointSet, class TTargetPointSet>
			::itk::ModifiedTimeType
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			GetMTime() const
			{
				auto mt = _mTime.getMTime();
				return mt;
			};

			template<class TMovingPointSet, class TTargetPointSet>
			void
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			setMetricControl(MetricControlType* pMetric)
			{
				if (pMetric != _spMetric.GetPointer())
				{
					//there is really the need to change
					if (this->_spOnChange.IsNotNull())
					{
						::map::events::UnregisterAlgorithmComponentEvent unRegEvent(_spMetric.GetPointer(),
								"Unregister current metric");
						this->_spOnChange->Execute((::itk::Object*)NULL, unRegEvent);
					}

					_spMetric  = pMetric;
					_mTime.setWatchedObject(pMetric);

					if (this->_spOnChange.IsNotNull())
					{
						::map::events::RegisterAlgorithmComponentEvent regEvent(_spMetric.GetPointer(), "Register new metric");
						this->_spOnChange->Execute((::itk::Object*)NULL, regEvent);
					}
				}
			};

			template<class TMovingPointSet, class TTargetPointSet>
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			ArbitraryPointSetToPointSetMetricPolicy()
			{
			};

			template<class TMovingPointSet, class TTargetPointSet>
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			~ArbitraryPointSetToPointSetMetricPolicy()
			{
			};

			template<class TMovingPointSet, class TTargetPointSet>
			typename ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::MetricControlType*

			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			getMetricInternal()
			{
				return _spMetric;
			};

			template<class TMovingPointSet, class TTargetPointSet>
			const typename
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::MetricControlType*
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			getMetricInternal() const
			{
				return _spMetric;
			};

			template<class TMovingPointSet, class TTargetPointSet>
			typename ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::MetricControlType*

			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			getMetricControl()
			{
				return _spMetric;
			};

			template<class TMovingPointSet, class TTargetPointSet>
			const typename
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::MetricControlType*
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			getMetricControl() const
			{
				return _spMetric;
			};

			template<class TMovingPointSet, class TTargetPointSet>
			void
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			prepareMetric()
			{
				//default implementation does nothing;
			};

			template<class TMovingPointSet, class TTargetPointSet>
			void
			ArbitraryPointSetToPointSetMetricPolicy<TMovingPointSet, TTargetPointSet>::
			prepareMetricAfterAssembly()
			{
				//default implementation does nothing;
			};

		}
	} // end namespace algorithm
} // end namespace map

#endif
