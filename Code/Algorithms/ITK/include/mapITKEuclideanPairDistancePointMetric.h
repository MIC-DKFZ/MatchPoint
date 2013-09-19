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




#ifndef __MAP_ITK_EUCLIDEAN_PAIR_DISTANCE_POINT_METRIC_H
#define __MAP_ITK_EUCLIDEAN_PAIR_DISTANCE_POINT_METRIC_H

#include "mapITKMetricControl.h"
#include "mapITKPointSetToPointSetMetricControlBase.h"
#include "mapEuclideanPairDistancePointMetric.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::EuclideanPairDistancePointMetric.
			@ingroup ITK
			@ingroup MetricControl
			*/
			template<class TMovingPointSet, class TTargetPointSet, class TDistanceMap>
			class ITKMetricControl< ::itk::EuclideanPairDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >
				: public ITKPointSetToPointSetMetricControlBase< ::itk::EuclideanPairDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >
			{
			public:
				typedef ITKMetricControl< ::itk::EuclideanPairDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >
				Self;
				typedef ITKPointSetToPointSetMetricControlBase< ::itk::EuclideanPairDistancePointMetric<TTargetPointSet, TMovingPointSet, TDistanceMap> >
				Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKMetricControl, ITKPointSetToPointSetMetricControlBase);
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
