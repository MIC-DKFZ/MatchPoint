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


#ifndef __FIXED_POINT_SET_METRIC_POLICY_TPP
#define __FIXED_POINT_SET_METRIC_POLICY_TPP

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteMetric>
			FixedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			FixedPointSetToPointSetMetricPolicy()
			{
			}

			template<class TConcreteMetric>
			FixedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			~FixedPointSetToPointSetMetricPolicy()
			{
			}

			template<class TConcreteMetric>
			typename FixedPointSetToPointSetMetricPolicy<TConcreteMetric>::MetricControlType*
			FixedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			getMetricControl()
			{
				return Superclass::getConcreteMetricControl();
			};

			template<class TConcreteMetric>
			const typename FixedPointSetToPointSetMetricPolicy<TConcreteMetric>::MetricControlType*
			FixedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			getMetricControl() const
			{
				return Superclass::getConcreteMetricControl();
			};

		}
	} // end namespace algorithm
} // end namespace map

#endif
