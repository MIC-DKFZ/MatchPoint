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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/test/mapStateTestCommand.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapStateTestCommand.h"
#include "mapAlgorithmStateChangeEvent.h"

namespace map
{
	namespace testing
	{

		void
		StateTestCommand::
		checkEvent(const itk::Object *caller, const itk::EventObject &e)
		{
			const map::events::AlgorithmStateChangeEvent *pChangeEvent = dynamic_cast<const map::events::AlgorithmStateChangeEvent *>(&e);
			_oldStates.push_back(pChangeEvent->getOldState());
			_newStates.push_back(pChangeEvent->getNewState());
		};

		StateTestCommand::
		StateTestCommand() {};
		StateTestCommand::
		~StateTestCommand() {};

	} //namespace testing
} //namespace map
