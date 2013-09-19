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




#ifndef __MAP_ITK_MATTES_MUTUAL_INFORMATION_IMAGE_TO_IMAGE_METRIC_H
#define __MAP_ITK_MATTES_MUTUAL_INFORMATION_IMAGE_TO_IMAGE_METRIC_H

#include "mapITKMetricControl.h"
#include "mapITKImageToImageMetricControlBase.h"
#include "itkMattesMutualInformationImageToImageMetric.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::MattesMutualInformationImageToImageMetric.
			@ingroup ITK
			@ingroup MetricControl
			*/
			template<class TMovingImage, class TTargetImage>
			class ITKMetricControl< ::itk::MattesMutualInformationImageToImageMetric<TTargetImage, TMovingImage> >
				: public ITKImageToImageMetricControlBase< ::itk::MattesMutualInformationImageToImageMetric<TTargetImage, TMovingImage> >
			{
			public:
				typedef ITKMetricControl< ::itk::MattesMutualInformationImageToImageMetric<TTargetImage, TMovingImage> >
				Self;
				typedef ITKImageToImageMetricControlBase< ::itk::MattesMutualInformationImageToImageMetric<TTargetImage, TMovingImage> >
				Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKMetricControl, ITKImageToImageMetricControlBase);
				itkNewMacro(Self);

				virtual bool getMinimizeToOptimize() const
				{
					return true;
				};

				virtual bool getMaximizeToOptimize() const
				{
					return false;
				};

			protected:
				virtual ~ITKMetricControl()
				{
					Superclass::_spMetric->ReinitializeSeed();
				};
				ITKMetricControl() {};

			private:
				//No copy constructor allowed
				ITKMetricControl(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#endif
