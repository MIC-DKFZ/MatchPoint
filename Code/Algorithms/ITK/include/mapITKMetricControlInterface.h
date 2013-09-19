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




#ifndef __ITK_METRIC_CONTROL_INTERFACE_H
#define __ITK_METRIC_CONTROL_INTERFACE_H

#include "mapMacros.h"

#include "itkObject.h"
#include "itkCostFunction.h"

#include "mapMAPAlgorithmsITKExports.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKMetricControlInterface
			@brief Interface for controller classes that form a virtual wrapper around itk cost functions.
			This wrapper is used because some metric trait information (e.g. optimization direction are
			not covered by the polymorphic class design of itk::CostFunction.
			@ingroup ITK
			*/
			class MAPAlgorithmsITK_EXPORT ITKMetricControlInterface : public ::itk::Object
			{
			public:
				typedef ITKMetricControlInterface Self;
				typedef ::itk::Object Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKMetricControlInterface, itk::Object);

				typedef ::itk::CostFunction MetricBaseType;

				/*! Should an optimizer minimize the metric to optimize it?
				@eguarantee no fail
				*/
				virtual bool getMinimizeToOptimize() const = 0;

				/*! Should an optimizer maximize the metric to optimize it?
				@eguarantee no fail
				*/
				virtual bool getMaximizeToOptimize() const = 0;

				virtual MetricBaseType* getMetric() = 0;
				virtual const MetricBaseType* getMetric() const = 0;

			protected:

				ITKMetricControlInterface();
				virtual ~ITKMetricControlInterface();

			private:
				//No copy constructor allowed
				ITKMetricControlInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#endif
