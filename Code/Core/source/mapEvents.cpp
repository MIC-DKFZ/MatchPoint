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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/source/mapEvents.cpp $
*/


#include "mapEvents.h"

namespace map
{
	namespace core
	{


		EventObject::
		EventObject(void *pData, const std::string &comment): _pData(pData), _comment(comment)
		{};

		EventObject::
		~EventObject() {};

		void *
		EventObject::
		getData() const
		{
			return _pData;
		};

		const std::string &
		EventObject::
		getComment() const
		{
			return _comment;
		};

		const char *
		EventObject::
		GetEventName() const
		{
			return "map::EventObject";
		};

		bool
		EventObject::
		CheckEvent(const ::itk::EventObject *e) const
		{
			return dynamic_cast<const Self *>(e);
		}

		::itk::EventObject *
		EventObject::
		MakeObject() const
		{
			return new EventObject(*this);
		}

		EventObject::
		EventObject(const Self &s) : Superclass(s)
		{
			_comment = s.getComment();
			_pData = s.getData();
		};

		void
		EventObject::
		Print(std::ostream &os) const
		{
			Superclass::Print(os);
			os << "Comment: " << _comment << std::endl;
			os << "Data pointer: " << _pData << std::endl;
		};


	}
}