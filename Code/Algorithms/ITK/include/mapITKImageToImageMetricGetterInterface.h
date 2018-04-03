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




#ifndef __MAP_ITK_IMAGE_TO_IMAGE_METRIC_GETTER_INTERFACE_H
#define __MAP_ITK_IMAGE_TO_IMAGE_METRIC_GETTER_INTERFACE_H

#include "mapITKImageToImageMetricControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKImageToImageMetricGetterInterface
			* Interface inherited by every algorithm that is able to get and change (by none const getter) an ImageToImageMetric
			@ingroup AlgorithmFacets
			*/
			template<class TMovingImage, class TTargetImage>
			class ITKImageToImageMetricGetterInterface
			{
			public:
				typedef ITKImageToImageMetricGetterInterface<TMovingImage, TTargetImage> Self;

				typedef itk::ITKImageToImageMetricControlInterface<TMovingImage, TTargetImage> MetricType;

				/*! @brief gets the metric
				 @eguarantee no fail
				 @return pointer to a MetricBaseType object
				*/
				virtual MetricType* getMetricControl() = 0;

				/*! @brief gets the metric
				 @eguarantee no fail
				 @return pointer to a MetricBaseType object
				*/
				virtual const MetricType* getMetricControl() const = 0;

			protected:
				ITKImageToImageMetricGetterInterface() {};
				virtual ~ITKImageToImageMetricGetterInterface() {};

			private:
				//No copy constructor allowed
				ITKImageToImageMetricGetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#endif
