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




#ifndef __MAP_ITK_IMAGE_TO_IMAGE_METRIC_SETTER_INTERFACE_H
#define __MAP_ITK_IMAGE_TO_IMAGE_METRIC_SETTER_INTERFACE_H

#include "mapITKImageToImageMetricControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKImageToImageMetricSetterInterface
			* Interface inherited by every algorithm that is able to set and change (by none const getter) an ImageToImageMetric
			@ingroup AlgorithmFacets
			*/
			template<class TMovingImage, class TTargetImage>
			class ITKImageToImageMetricSetterInterface
			{
			public:
				typedef ITKImageToImageMetricSetterInterface<TMovingImage, TTargetImage> Self;

				typedef algorithm::itk::ITKImageToImageMetricControlInterface<TMovingImage, TTargetImage>
				MetricControlType;

				/*! sets the metric
				  @eguarantee strong
				  @param metric the metric
				 */
				virtual void setMetricControl(MetricControlType* metric) = 0;

			protected:
				ITKImageToImageMetricSetterInterface() {};
				virtual ~ITKImageToImageMetricSetterInterface() {};

			private:
				//No copy constructor allowed
				ITKImageToImageMetricSetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#endif
