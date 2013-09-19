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
		checkEvent(const itk::Object* caller, const itk::EventObject& e)
		{
			const map::events::AlgorithmStateChangeEvent* pChangeEvent =
				dynamic_cast<const map::events::AlgorithmStateChangeEvent*>(&e);
			_oldStates.push_back(pChangeEvent->getOldState());
			_newStates.push_back(pChangeEvent->getNewState());
		};

		StateTestCommand::
		StateTestCommand() {};
		StateTestCommand::
		~StateTestCommand() {};

	} //namespace testing
} //namespace map
