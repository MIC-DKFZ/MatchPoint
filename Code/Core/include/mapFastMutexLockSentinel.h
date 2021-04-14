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

#ifndef __MAP_FAST_MUTEX_LOCK_SENTINEL_H
#define __MAP_FAST_MUTEX_LOCK_SENTINEL_H

#include <mutex>

#include "mapMacros.h"
#include "mapMAPCoreExports.h"


namespace map
{
	namespace core
	{
		namespace services
		{
			/*! @class FastMutexLockSentinel
			* @brief Helper class for fast locked threadding policies.
			* Used as their sentinel class. Locks the mutex when calling InitializeSentinel()
			* unlocks the mutex when the destructor of the sentinel is called.
			*
			* @ingroup ThreadingPolicies
			*/
			class MAPCore_EXPORT FastMutexLockSentinel
			{
			public:
				using MutexType = std::mutex;

				void initializeSentinel(MutexType* pMutex);

				FastMutexLockSentinel();

				~FastMutexLockSentinel();

			private:
				/*! This policy uses this mutex to lock critical code by the policy user.*/
				MutexType* _pMutex{nullptr};

				FastMutexLockSentinel(const FastMutexLockSentinel&) = delete;  //purposely not implemented
				void operator=(const FastMutexLockSentinel&) = delete;  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#endif