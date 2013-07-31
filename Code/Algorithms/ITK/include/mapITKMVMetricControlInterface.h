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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKMVMetricControlInterface.h $
*/




#ifndef __ITK_MV_METRIC_CONTROL_INTERFACE_H
#define __ITK_MV_METRIC_CONTROL_INTERFACE_H

#include "itkMultipleValuedCostFunction.h"

#include "mapITKMetricControlInterface.h"
#include "mapMAPAlgorithmsITKExports.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKMVMetricControlInterface
			@brief Interface for controller classes that form a virtual wrapper around itk::MultipleValuedCostFunctions
			@ingroup ITK
			*/
			class MAPAlgorithmsITK_EXPORT ITKMVMetricControlInterface : public ITKMetricControlInterface
			{
			public:
				typedef ITKMVMetricControlInterface Self;
				typedef ITKMetricControlInterface Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKMVMetricControlInterface, ITKMetricControlInterface);

				typedef ::itk::MultipleValuedCostFunction MVMetricBaseType;

				virtual MVMetricBaseType *getMVMetric() = 0;
				virtual const MVMetricBaseType *getMVMetric() const = 0;

			protected:
				ITKMVMetricControlInterface();
				virtual ~ITKMVMetricControlInterface();

			private:
				//No copy constructor allowed
				ITKMVMetricControlInterface(const Self &source);
				void operator=(const Self &); //purposely not implemented
			};

		}
	}
}

#endif
