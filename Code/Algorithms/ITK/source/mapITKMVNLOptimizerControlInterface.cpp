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



#include "mapITKMVNLOptimizerControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{


			ITKMVNLOptimizerControlInterface::MVNLMeasureType
			ITKMVNLOptimizerControlInterface::
			getCurrentMeasure() const
			{
				MVNLMeasureType result;

				if (this->hasCurrentValue())
				{
					result = this->doGetCurrentMeasure();
				}

				return result;
			};

			ITKMVNLOptimizerControlInterface::OptimizerMeasureType
			ITKMVNLOptimizerControlInterface::
			doGetCurrentValue() const
			{
				OptimizerMeasureType result;

				MVNLMeasureType measure = this->doGetCurrentMeasure();

				for (MVNLMeasureType::iterator pos = measure.begin(); pos != measure.end(); ++pos)
				{
					result.push_back(*pos);
				}

				return result;
			};

			ITKMVNLOptimizerControlInterface::
			ITKMVNLOptimizerControlInterface()
			{
			};

			ITKMVNLOptimizerControlInterface::
			~ITKMVNLOptimizerControlInterface()
			{
			};

		}
	}
}
