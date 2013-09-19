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


#include "mapThreadEvents.h"

namespace map
{
	namespace core
	{

		const ThreadEventObject::ThreadIDType ThreadEventObject::anyThreadID = -1;

		ThreadEventObject::
		ThreadEventObject(ThreadIDType threadID, void* pData, const std::string& comment): Superclass(pData,
					comment), _threadID(threadID)
		{};

		ThreadEventObject::
		~ThreadEventObject() {};

		ThreadEventObject::ThreadIDType
		ThreadEventObject::
		getThreadID() const
		{
			return _threadID;
		};

		const char*
		ThreadEventObject::
		GetEventName() const
		{
			return "map::ThreadEventObject";
		};

		bool
		ThreadEventObject::
		CheckEvent(const ::itk::EventObject* e) const
		{
			const Self* pE = dynamic_cast<const Self*>(e);
			bool result = false;

			if (pE)
			{
				result = (this->_threadID == anyThreadID) || (pE->getThreadID() == this->_threadID);
			}

			return result;
		}

		::itk::EventObject*
		ThreadEventObject::
		MakeObject() const
		{
			return new ThreadEventObject(*this);
		}

		ThreadEventObject::
		ThreadEventObject(const Self& s) : Superclass(s)
		{
			_threadID = s.getThreadID();
		};

		void
		ThreadEventObject::
		Print(std::ostream& os) const
		{
			Superclass::Print(os);
			os << "Thread ID: " << _threadID << std::endl;
		};


	}
}