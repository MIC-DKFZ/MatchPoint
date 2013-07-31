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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/source/mapAlgorithmStateChangeEvent.cpp $
*/


#include "mapAlgorithmStateChangeEvent.h"

namespace map
{
	namespace events
	{

		AlgorithmStateChangeEvent::
		AlgorithmStateChangeEvent(const AlgorithmStateType &oldState, const AlgorithmStateType &newState): _oldState(oldState), _newState(newState)
		{};

		AlgorithmStateChangeEvent::
		~AlgorithmStateChangeEvent()
		{};

		const char *
		AlgorithmStateChangeEvent::
		GetEventName() const
		{
			return "AlgorithmStateChangeEvent";
		};

		AlgorithmStateChangeEvent::AlgorithmStateType
		AlgorithmStateChangeEvent::
		getOldState() const
		{
			return _oldState;
		};

		AlgorithmStateChangeEvent::AlgorithmStateType
		AlgorithmStateChangeEvent::
		getNewState() const
		{
			return _newState;
		};

		bool
		AlgorithmStateChangeEvent::
		CheckEvent(const ::itk::EventObject *e) const
		{
			return dynamic_cast<const Self *>(e);
		};

		::itk::EventObject *
		AlgorithmStateChangeEvent::
		MakeObject() const
		{
			return new Self(*this);
		};

		AlgorithmStateChangeEvent::
		AlgorithmStateChangeEvent(const Self &s) : Superclass(s),  _oldState(s._oldState), _newState(s._newState)
		{
		};

		void
		AlgorithmStateChangeEvent::
		Print(std::ostream &os) const
		{
			Superclass::Print(os);
			os << "Old state: " << _oldState << std::endl;
			os << "New state: " << _newState << std::endl;
		};

	}
}
