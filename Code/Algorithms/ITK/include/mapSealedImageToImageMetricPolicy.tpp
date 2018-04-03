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


#ifndef __SEALED_IMAGE_TO_IMAGE_METRIC_POLICY_TPP
#define __SEALED_IMAGE_TO_IMAGE_METRIC_POLICY_TPP

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TConcreteMetric>
			typename SealedImageToImageMetricPolicy<TConcreteMetric>::ConcreteMetricControlType*
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			getConcreteMetricControl()
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			const typename SealedImageToImageMetricPolicy<TConcreteMetric>::ConcreteMetricControlType*
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			getConcreteMetricControl() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			SealedImageToImageMetricPolicy()
			{
				_spMetric = ConcreteMetricControlType::New();
			}

			template<class TConcreteMetric>
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			~SealedImageToImageMetricPolicy()
			{
			}

			template<class TConcreteMetric>
			typename SealedImageToImageMetricPolicy<TConcreteMetric>::MetricControlType*
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			getMetricInternal()
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			const typename SealedImageToImageMetricPolicy<TConcreteMetric>::MetricControlType*
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			getMetricInternal() const
			{
				return _spMetric;
			}

			template<class TConcreteMetric>
			void
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			prepareMetric()
			{
				//default implementation does nothing;
			}

			template<class TConcreteMetric>
			void
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			prepareMetricAfterAssembly()
			{
				//default implementation does nothing;
			}

			template<class TConcreteMetric>
			unsigned long
			SealedImageToImageMetricPolicy<TConcreteMetric>::
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
			SealedImageToImageMetricPolicy<TConcreteMetric>::
			indicateModification() const
			{
				_mTime.Modified();
			};
		}
	} // end namespace algorithm
} // end namespace map

#endif
