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


#ifndef __MAP_FAST_LOCKED_THREADING_STATIC_POLICY_H
#define __MAP_FAST_LOCKED_THREADING_STATIC_POLICY_H

#include "itkSimpleFastMutexLock.h"

#include "mapFastMutexLockSentinel.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		namespace services
		{
			/*! @class FastLockedThreadingStaticPolicy
			* @brief Policy is used to handle critical code via a mutex lock.
			*
			* It is used as normally used by StaticServiceStack
			* @ingroup ThreadingPolicies
			*/
			class MAPCore_EXPORT FastLockedThreadingStaticPolicy
			{
			protected:
				typedef itk::SimpleFastMutexLock  MutexType;
				typedef FastMutexLockSentinel SentinelType;

				/*! Initialize a sentinel and implicitly lock the mutex.
				 * @eguarantee strong
				 */
				static void activateSentinel(SentinelType& sentinel);

				/*! Used by the policy owner to lock part of its code.
				 * @eguarantee strong
				 */
				static void lock();

				/*! Used by the policy owner to unlock critical code.
				 * @eguarantee strong
				 */
				static void unlock();

				FastLockedThreadingStaticPolicy();
				~FastLockedThreadingStaticPolicy();

			private:
				/*! This policy uses this mutex to lock critical code by the policy user.*/
				static MutexType _mutex;

				FastLockedThreadingStaticPolicy(const
												FastLockedThreadingStaticPolicy&);  //purposely not implemented
				void operator=(const FastLockedThreadingStaticPolicy&);  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
