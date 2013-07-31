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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/source/mapAlgorithmWrapperEvent.cpp $
*/


#include "mapAlgorithmWrapperEvent.h"
#include "mapString.h"

namespace map
{
	namespace events
	{

		AlgorithmWrapperEvent::
		AlgorithmWrapperEvent(const ::itk::EventObject &wrappedEvent, ::itk::Object *wrappedCaller, const std::string &comment) : Superclass(NULL, comment)
		{
			_pWrappedCaller = wrappedCaller;
			_pWrappedEvent = wrappedEvent.MakeObject();

			::map::core::OStringStream os;
			os << "AlgorithmWrapperEvent<" << _pWrappedEvent->GetEventName() << ">";
			_cachedEventName = os.str();
		};


		AlgorithmWrapperEvent::
		~AlgorithmWrapperEvent()
		{
			delete _pWrappedEvent;
		};

		const char *
		AlgorithmWrapperEvent::
		GetEventName() const
		{
			return _cachedEventName.c_str();
		};

		bool
		AlgorithmWrapperEvent::
		CheckEvent(const ::itk::EventObject *e) const
		{
			bool result = false;
			const Self *pEvent = dynamic_cast<const Self *>(e);

			if (pEvent)
			{
				result = _pWrappedEvent->CheckEvent(&(pEvent->getWrappedEvent()));
			}

			return result;
		};

		::itk::EventObject *
		AlgorithmWrapperEvent::
		MakeObject() const
		{
			return new Self(*this);
		};

		AlgorithmWrapperEvent::
		AlgorithmWrapperEvent(const Self &s) : Superclass(NULL, s.getComment()), _pWrappedCaller(s._pWrappedCaller), _pWrappedEvent(s._pWrappedEvent->MakeObject())
		{
		};

		::itk::EventObject &
		AlgorithmWrapperEvent::
		getWrappedEvent() const
		{
			return *_pWrappedEvent;
		};

		::itk::Object *
		AlgorithmWrapperEvent::
		getWrappedCaller() const
		{
			return _pWrappedCaller;
		};

		void
		AlgorithmWrapperEvent::
		Print(std::ostream &os) const
		{
			Superclass::Print(os);
			os << "wrapped caller: " << _pWrappedCaller << std::endl;
			os << "wrapped event: " << *_pWrappedEvent << std::endl;
		};

	}
}
