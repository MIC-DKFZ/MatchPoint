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


#ifndef __SEALED_POINT_SET_TO_POINT_SET_METRIC_POLICY_TPP
#define __SEALED_POINT_SET_TO_POINT_SET_METRIC_POLICY_TPP

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteMetric>
			typename SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::ConcreteMetricControlType*
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			getConcreteMetricControl()
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			const typename SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::ConcreteMetricControlType*
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			getConcreteMetricControl() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			SealedPointSetToPointSetMetricPolicy()
			{
				_spMetric = ConcreteMetricControlType::New();
			}

			template<class TConcreteMetric>
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			~SealedPointSetToPointSetMetricPolicy()
			{
			}

			template<class TConcreteMetric>
			typename SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::MetricControlType*
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			getMetricInternal()
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			const typename SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::MetricControlType*
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			getMetricInternal() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			void
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			prepareMetric()
			{
				//default implementation does nothing;
			}

			template<class TConcreteMetric>
			void
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			prepareMetricAfterAssembly()
			{
				//default implementation does nothing;
			}

			template<class TConcreteMetric>
			unsigned long
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			GetMTime() const
			{
				unsigned long mt = _mTime.GetMTime();

				if (mt < _spMetric->GetMTime())
				{
					mt = _spMetric->GetMTime();
				}

				return mt;
			};

			template<class TConcreteMetric>
			void
			SealedPointSetToPointSetMetricPolicy<TConcreteMetric>::
			indicateModification() const
			{
				_mTime.Modified();
			};
		}
	} // end namespace algorithm
} // end namespace map

#endif
