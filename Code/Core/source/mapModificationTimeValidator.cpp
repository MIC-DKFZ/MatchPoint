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


#include "mapModificationTimeValidator.h"

namespace map
{
	namespace core
	{

		ModificationTimeValidator::ModificationTimeValidator(const WatchedObjectType* obj)
		{
			_spObj = NULL;
			setWatchedObject(obj);
		}

		ModificationTimeValidator::ModificationTimeValidator()
		{
			_spObj = NULL;
		}

		ModificationTimeValidator::~ModificationTimeValidator()
		{
		}

		void ModificationTimeValidator::setWatchedObject(const WatchedObjectType* obj)
		{
			if (_spObj != obj)
			{
				_spObj = obj;

				if (obj)
				{
					_objTimeStamp = obj->GetMTime();
				}

				_ownTimeStamp.Modified();
			}
		}

		ModificationTimeValidator::MTimeType ModificationTimeValidator::getMTime() const
		{
			if (_spObj.IsNotNull())
			{
				if (_objTimeStamp < _spObj->GetMTime())
				{
					_objTimeStamp = _spObj->GetMTime();
					_ownTimeStamp.Modified();
				}
			}

			MTimeType result = _ownTimeStamp.GetMTime();

			return result;
		}

	} // end namespace core
} // end namespace map