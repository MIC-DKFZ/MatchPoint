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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKMetricControl.h $
*/




#ifndef __ITK_METRIC_CONTROL_H
#define __ITK_METRIC_CONTROL_H

#include "mapITKMetricControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKMetricControl
			This class is the master copy for the template specialization.
			It is a dummy and not for practical use. For every metric there must be a proper specialization of this
			class (using the right interfaces and implementing the abstract functions.
			To define a controller for a special metric use template specialization
			(template<> class ITKMetricControl<itk::MySpecialMetric>)
			and reimplement the class interface.
			See e.g. ITKMetricControl<itk::MattesMutualInformationMetric> as an specialized example.
			@remark ITKMetricControl should always instantiates a concrete optimizer when constructed.
			@template TConcreteMetric type of the concrete metric controlled by the class
			@ingroup ITK
			@ingroup MetricControl
			*/
			template<class TConcreteMetric>
			class ITKMetricControl;
		}
	}
}

#endif
