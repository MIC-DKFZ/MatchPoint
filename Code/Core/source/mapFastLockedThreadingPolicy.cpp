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

#include "mapFastLockedThreadingPolicy.h"

namespace map
{
	namespace core
	{
		namespace services
		{
			void
			FastLockedThreadingPolicy::
			lock() const
			{
				_mutex.lock();
			}

			void
			FastLockedThreadingPolicy::
			unlock() const
			{
				_mutex.unlock();
			};

			void
			FastLockedThreadingPolicy::
			activateSentinel(SentinelType& sentinel) const
			{
				sentinel.initializeSentinel(&_mutex);
				//lock will be done by initializeSentinel()
			};

			FastLockedThreadingPolicy::
			FastLockedThreadingPolicy()
			= default;

			FastLockedThreadingPolicy::
			~FastLockedThreadingPolicy()
			= default;

		} // end namespace services
	} // end namespace core
} // end namespace map
