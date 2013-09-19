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



#include "mapIterativeAlgorithmBase.h"

namespace map
{
	namespace algorithm
	{

		IterativeAlgorithmBase::
		IterativeAlgorithmBase()
		{
		};

		IterativeAlgorithmBase::
		~IterativeAlgorithmBase()
		{
		};

		IterativeAlgorithmBase::IterationCountType
		IterativeAlgorithmBase::
		getCurrentIteration() const
		{
			IterationCountType result = 0;

			if (this->hasIterationCount())
			{
				result = this->doGetCurrentIteration();
			}

			return result;
		};

		IterativeAlgorithmBase::IterationCountType
		IterativeAlgorithmBase::
		getMaxIterations() const
		{
			IterationCountType result = 0;

			if (this->hasMaxIterationCount())
			{
				result = this->doGetMaxIterations();
			}

			return result;
		};

	}
}


