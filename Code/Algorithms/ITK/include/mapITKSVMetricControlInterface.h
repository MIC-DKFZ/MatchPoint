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




#ifndef __ITK_SV_METRIC_CONTROL_INTERFACE_H
#define __ITK_SV_METRIC_CONTROL_INTERFACE_H

#include "mapITKMetricControlInterface.h"

#include "itkSingleValuedCostFunction.h"


namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKSVMetricControlInterface
			@brief Interface for controller classes that form a virtual wrapper around itk::SingleValuedCostFunctions
			@ingroup ITK
			*/
			class MAPAlgorithmsITK_EXPORT ITKSVMetricControlInterface : public ITKMetricControlInterface
			{
			public:
				using Self = ITKSVMetricControlInterface;
				using Superclass = ITKMetricControlInterface;
				using Pointer = ::itk::SmartPointer<Self>;
				using ConstPointer = ::itk::SmartPointer<const Self>;

				itkTypeMacro(ITKSVMetricControlInterface, ITKMetricControlInterface);

				using SVMetricBaseType = ::itk::SingleValuedCostFunction;

				virtual SVMetricBaseType* getSVMetric() = 0;
				virtual const SVMetricBaseType* getSVMetric() const = 0;

			protected:
				ITKSVMetricControlInterface();
				~ITKSVMetricControlInterface() override;

			private:
				//No copy constructor allowed
				ITKSVMetricControlInterface(const Self& source) = delete;
				void operator=(const Self&) = delete;  //purposely not implemented
			};

		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#endif
