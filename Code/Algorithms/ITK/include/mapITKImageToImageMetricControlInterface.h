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




#ifndef __ITK_IMAGE_TO_IMAGE_METRIC_CONTROL_INTERFACE_H
#define __ITK_IMAGE_TO_IMAGE_METRIC_CONTROL_INTERFACE_H

#include "mapITKSVMetricControlInterface.h"

#include "itkImageToImageMetric.h"


namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKImageToImageMetricControlInterface
			@brief Interface for controller classes that form a virtual wrapper around itk::SingleValuedCostFunctions
			@ingroup ITK
			*/
			template<class TMovingImage, class TTargetImage>
			class ITKImageToImageMetricControlInterface : public ITKSVMetricControlInterface
			{
			public:
				typedef ITKImageToImageMetricControlInterface<TMovingImage, TTargetImage> Self;
				typedef ITKSVMetricControlInterface Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKImageToImageMetricControlInterface, ITKSVMetricControlInterface);

				typedef ::itk::ImageToImageMetric<TMovingImage, TTargetImage> ImageToImageMetricBaseType;

				virtual ImageToImageMetricBaseType* getImageToImageMetric() = 0;
				virtual const ImageToImageMetricBaseType* getImageToImageMetric() const = 0;

			protected:
				ITKImageToImageMetricControlInterface() {};
				virtual ~ITKImageToImageMetricControlInterface() {};

			private:
				//No copy constructor allowed
				ITKImageToImageMetricControlInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#endif
