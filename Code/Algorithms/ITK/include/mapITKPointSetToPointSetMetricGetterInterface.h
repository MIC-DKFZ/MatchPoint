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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKPointSetToPointSetMetricGetterInterface.h $
*/




#ifndef __MAP_ITK_POINT_SET_TO_POINT_SET_METRIC_GETTER_INTERFACE_H
#define __MAP_ITK_POINT_SET_TO_POINT_SET_METRIC_GETTER_INTERFACE_H

#include "mapITKPointSetToPointSetMetricControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ITKPointSetToPointSetMetricGetterInterface
			* Interface inherited by every algorithm that is able to get and change (by none const getter) an PointSetToPointSetMetric
			@ingroup AlgorithmFacets
			*/
			template<class TMovingPointSet, class TTargetPointSet>
			class ITKPointSetToPointSetMetricGetterInterface
			{
			public:
				typedef ITKPointSetToPointSetMetricGetterInterface<TMovingPointSet, TTargetPointSet> Self;

				typedef itk::ITKPointSetToPointSetMetricControlInterface<TMovingPointSet, TTargetPointSet> MetricType;

				/*! @brief gets the metric
				 @eguarantee no fail
				 @return pointer to a MetricBaseType object
				*/
				virtual MetricType *getMetricControl() = 0;

				/*! @brief gets the metric
				 @eguarantee no fail
				 @return pointer to a MetricBaseType object
				*/
				virtual const MetricType *getMetricControl() const = 0;

			protected:
				ITKPointSetToPointSetMetricGetterInterface() {};
				virtual ~ITKPointSetToPointSetMetricGetterInterface() {};

			private:
				//No copy constructor allowed
				ITKPointSetToPointSetMetricGetterInterface(const Self &source);
				void operator=(const Self &); //purposely not implemented

			};

		}
	}
}

#endif
