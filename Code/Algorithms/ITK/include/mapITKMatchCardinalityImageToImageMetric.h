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




#ifndef __MAP_ITK_MATCH_CARDINALITY_IMAGE_TO_IMAGE_METRIC_CONTROL_H
#define __MAP_ITK_MATCH_CARDINALITY_IMAGE_TO_IMAGE_METRIC_CONTROL_H

#include "mapITKMetricControl.h"
#include "mapITKImageToImageMetricControlBase.h"
#include "itkMatchCardinalityImageToImageMetric.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::MatchCardinalityImageToImageMetric.
			@ingroup ITK
			@ingroup MetricControl
			*/
			template<class TMovingImage, class TTargetImage>
			class ITKMetricControl< ::itk::MatchCardinalityImageToImageMetric<TTargetImage, TMovingImage> > :
				public ITKImageToImageMetricControlBase< ::itk::MatchCardinalityImageToImageMetric<TTargetImage, TMovingImage> >
			{
			public:
				typedef ITKMetricControl< ::itk::MatchCardinalityImageToImageMetric<TTargetImage, TMovingImage> >
				Self;
				typedef ITKImageToImageMetricControlBase< ::itk::MatchCardinalityImageToImageMetric<TTargetImage, TMovingImage> >
				Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKMetricControl, ITKImageToImageMetricControlBase);
				itkNewMacro(Self);

				virtual bool getMinimizeToOptimize() const
				{
					return !getMaximizeToOptimize();
				};

				virtual bool getMaximizeToOptimize() const
				{
					bool result = false;

					const typename Superclass::MetricBaseType* pMetric = Superclass::getMetric();

					if (pMetric)
					{
						typedef ::itk::MatchCardinalityImageToImageMetric<TTargetImage, TMovingImage> MetricType;

						const MetricType* pCastedMetric = dynamic_cast<const MetricType*>(pMetric);

						if (pCastedMetric)
						{
							result = pCastedMetric->GetMeasureMatches();
						}
					}

					return result;
				};

			protected:
				virtual ~ITKMetricControl() {};
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
