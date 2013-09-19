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


#ifndef __ARBITRARY_IMAGE_TO_IMAGE_METRIC_POLICY_TPP
#define __ARBITRARY_IMAGE_TO_IMAGE_METRIC_POLICY_TPP

#include "mapAlgorithmEvents.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TMovingImage, class TTargetImage>
			unsigned long
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			GetMTime() const
			{
				unsigned long mt = _mTime.getMTime();

				return mt;
			};

			template<class TMovingImage, class TTargetImage>
			void
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			setMetricControl(MetricControlType* pMetric)
			{
				if (pMetric != _spMetric.GetPointer())
				{
					//there is really the need to change
					if (this->_spOnChange.IsNotNull())
					{
						events::UnregisterAlgorithmComponentEvent unRegEvent(_spMetric.GetPointer(),
								"Unregister current metric");
						this->_spOnChange->Execute((::itk::Object*)NULL, unRegEvent);
					}

					_mTime.setWatchedObject(pMetric);
					_spMetric  = pMetric;

					if (this->_spOnChange.IsNotNull())
					{
						events::RegisterAlgorithmComponentEvent regEvent(_spMetric.GetPointer(), "Register new metric");
						this->_spOnChange->Execute((::itk::Object*)NULL, regEvent);
					}
				}
			};

			template<class TMovingImage, class TTargetImage>
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			ArbitraryImageToImageMetricPolicy()
			{
			};

			template<class TMovingImage, class TTargetImage>
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			~ArbitraryImageToImageMetricPolicy()
			{
			};

			template<class TMovingImage, class TTargetImage>
			typename ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::MetricControlType*
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			getMetricInternal()
			{
				return _spMetric;
			};

			template<class TMovingImage, class TTargetImage>
			const typename ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::MetricControlType*
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			getMetricInternal() const
			{
				return _spMetric;
			};

			template<class TMovingImage, class TTargetImage>
			typename ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::MetricControlType*
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			getMetricControl()
			{
				return _spMetric;
			};

			template<class TMovingImage, class TTargetImage>
			const typename ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::MetricControlType*
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			getMetricControl() const
			{
				return _spMetric;
			};

			template<class TMovingImage, class TTargetImage>
			void
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			prepareMetric()
			{
				//default implementation does nothing;
			};

			template<class TMovingImage, class TTargetImage>
			void
			ArbitraryImageToImageMetricPolicy<TMovingImage, TTargetImage>::
			prepareMetricAfterAssembly()
			{
				//default implementation does nothing;
			};

		}
	} // end namespace algorithm
} // end namespace map

#endif
