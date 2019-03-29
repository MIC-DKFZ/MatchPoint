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



#include "mapOptimizerControlInterface.h"

namespace map
{
	namespace algorithm
	{

		bool
		OptimizerControlInterface::
		stop()
		{
			bool result = false;

			if (this->isStoppable())
			{
				result = this->doStop();
			}

			return result;
		};

		OptimizerControlInterface::IterationCountType
		OptimizerControlInterface::
		getCurrentIteration() const
		{
			IterationCountType result = 0;

			if (this->hasIterationCount())
			{
				result = this->doGetCurrentIteration();
			}

			return result;
		};

		OptimizerControlInterface::IterationCountType
		OptimizerControlInterface::
		getMaxIterations() const
		{
			IterationCountType result = 0;

			if (this->hasMaxIterationCount())
			{
				result = this->doGetMaxIterations();
			}

			return result;
		};

		OptimizerControlInterface::OptimizerMeasureType
		OptimizerControlInterface::
		getCurrentValue() const
		{
			OptimizerMeasureType result;

			if (this->hasCurrentValue())
			{
				result = this->doGetCurrentValue();
			}

			return result;
		};

		OptimizerControlInterface::OptimizerPositionType
		OptimizerControlInterface::
		getCurrentPosition() const
		{
			OptimizerPositionType result;

			if (this->hasCurrentPosition())
			{
				result = this->doGetCurrentPosition();
			}

			return result;
		};

		OptimizerControlInterface::OptimizerScalesType
		OptimizerControlInterface::
		getScales() const
		{
			OptimizerScalesType result;

			if (this->hasScales())
			{
				result = this->doGetScales();
			}

			return result;
		};

		OptimizerControlInterface::
		OptimizerControlInterface()
		= default;

		OptimizerControlInterface::
		~OptimizerControlInterface()
		= default;

	}  // namespace algorithm
}  // namespace map
