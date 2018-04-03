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


#ifndef __ITK_IMAGE_TO_IMAGE_METRIC_CONTROL_BASE_TPP
#define __ITK_IMAGE_TO_IMAGE_METRIC_CONTROL_BASE_TPP

#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteMetric>
			void
			ITKImageToImageMetricControlBase<TConcreteMetric>::
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
			ITKImageToImageMetricControlBase<TConcreteMetric>::
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
			typename ITKImageToImageMetricControlBase<TConcreteMetric>::MetricBaseType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getMetric()
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			const typename ITKImageToImageMetricControlBase<TConcreteMetric>::MetricBaseType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getMetric() const
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			typename ITKImageToImageMetricControlBase<TConcreteMetric>::SVMetricBaseType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getSVMetric()
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			const typename ITKImageToImageMetricControlBase<TConcreteMetric>::SVMetricBaseType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getSVMetric() const
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			typename ITKImageToImageMetricControlBase<TConcreteMetric>::ImageToImageMetricBaseType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getImageToImageMetric()
			{
				return _spMetric.GetPointer();
			}

			template<class TConcreteMetric>
			const typename ITKImageToImageMetricControlBase<TConcreteMetric>::ImageToImageMetricBaseType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getImageToImageMetric() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			typename ITKImageToImageMetricControlBase<TConcreteMetric>::ConcreteMetricType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getConcreteMetric()
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			const typename ITKImageToImageMetricControlBase<TConcreteMetric>::ConcreteMetricType*
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			getConcreteMetric() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			~ITKImageToImageMetricControlBase()
			{
			}

			template<class TConcreteMetric>
			ITKImageToImageMetricControlBase<TConcreteMetric>::
			ITKImageToImageMetricControlBase()
			{
				_spMetric = ConcreteMetricType::New();
			}

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
