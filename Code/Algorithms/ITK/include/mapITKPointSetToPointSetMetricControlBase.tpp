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


#ifndef __ITK_POINTSET_TO_POINTSET_METRIC_CONTROL_BASE_TPP
#define __ITK_POINTSET_TO_POINTSET_METRIC_CONTROL_BASE_TPP

#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteMetric>
			void
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			setMetric(ConcreteMetricType* pMetric)
			{
				if (!pMetric)
				{
					mapDefaultExceptionMacro( << "Cannot set metric. Passed pointer to metric is NULL");
				}

				_spMetric = pMetric;
				this->Modified();
			}

			template<class TConcreteMetric>
			unsigned long
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			GetMTime() const
			{
				unsigned long mt = Superclass::GetMTime();

				if (mt < _spMetric->GetMTime())
				{
					mt = _spMetric->GetMTime();
				}

				return mt;
			};

			template<class TConcreteMetric>
			typename ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::MetricBaseType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getMetric()
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			const typename ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::MetricBaseType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getMetric() const
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			typename ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::MVMetricBaseType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getMVMetric()
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			const typename ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::MVMetricBaseType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getMVMetric() const
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			typename ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::PointSetToPointSetMetricBaseType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getPointSetToPointSetMetric()
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			const typename
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::PointSetToPointSetMetricBaseType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getPointSetToPointSetMetric() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			typename ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::ConcreteMetricType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getConcreteMetric()
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			const typename ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::ConcreteMetricType*
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			getConcreteMetric() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			~ITKPointSetToPointSetMetricControlBase()
			{
			}

			template<class TConcreteMetric>
			ITKPointSetToPointSetMetricControlBase<TConcreteMetric>::
			ITKPointSetToPointSetMetricControlBase()
			{
				_spMetric = ConcreteMetricType::New();
			}

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
