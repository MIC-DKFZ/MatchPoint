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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKPointSetToPointSetMetricControlInterface.h $
*/




#ifndef __ITK_POINTSET_TO_POINTSET_METRIC_CONTROL_INTERFACE_H
#define __ITK_POINTSET_TO_POINTSET_METRIC_CONTROL_INTERFACE_H

#include "mapITKMVMetricControlInterface.h"

#include "itkPointSetToPointSetMetric.h"


namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKPointSetToPointSetMetricControlInterface
			@brief Interface for controller classes that form a virtual wrapper around itk::PointSetToPointSetMetrics
			@ingroup ITK
			*/
			template<class TMovingPointSet, class TTargetPointSet>
			class ITKPointSetToPointSetMetricControlInterface : public ITKMVMetricControlInterface
			{
			public:
				typedef ITKPointSetToPointSetMetricControlInterface<TMovingPointSet, TTargetPointSet> Self;
				typedef ITKMVMetricControlInterface Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKPointSetToPointSetMetricControlInterface, ITKMVMetricControlInterface);

				typedef ::itk::PointSetToPointSetMetric<TMovingPointSet, TTargetPointSet> PointSetToPointSetMetricBaseType;

				virtual PointSetToPointSetMetricBaseType *getPointSetToPointSetMetric() = 0;
				virtual const PointSetToPointSetMetricBaseType *getPointSetToPointSetMetric() const = 0;

			protected:
				ITKPointSetToPointSetMetricControlInterface() {};
				virtual ~ITKPointSetToPointSetMetricControlInterface() {};

			private:
				//No copy constructor allowed
				ITKPointSetToPointSetMetricControlInterface(const Self &source);
				void operator=(const Self &); //purposely not implemented
			};

		}
	}
}

#endif
