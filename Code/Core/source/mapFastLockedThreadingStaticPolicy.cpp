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


#include "mapFastLockedThreadingStaticPolicy.h"

namespace map
{
	namespace core
	{
		namespace services
		{

			void
			FastLockedThreadingStaticPolicy::
			activateSentinel(SentinelType& sentinel)
			{
				sentinel.initializeSentinel(&FastLockedThreadingStaticPolicy::_mutex);
				//lock will be done by initializeSentinel()
			};

			void
			FastLockedThreadingStaticPolicy::
			lock()
			{
				FastLockedThreadingStaticPolicy::_mutex.Lock();
			};

			void
			FastLockedThreadingStaticPolicy::
			unlock()
			{
				FastLockedThreadingStaticPolicy::_mutex.Unlock();
			};

			FastLockedThreadingStaticPolicy::
			FastLockedThreadingStaticPolicy()
			{
			};

			FastLockedThreadingStaticPolicy::
			~FastLockedThreadingStaticPolicy()
			{
			};

			FastLockedThreadingStaticPolicy::MutexType FastLockedThreadingStaticPolicy::_mutex;

		} // end namespace services
	} // end namespace core
} // end namespace map
