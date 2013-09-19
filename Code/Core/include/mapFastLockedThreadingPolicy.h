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

#ifndef __MAP_FAST_LOCKED_THREADING_POLICY_H
#define __MAP_FAST_LOCKED_THREADING_POLICY_H

#include "itkSimpleFastMutexLock.h"

#include "mapFastMutexLockSentinel.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		namespace services
		{
			/*! @class FastLockedThreadingPolicy
			* @brief Policy is used to handle critical code via a mutex lock.
			*
			* @ingroup ThreadingPolicies
			*/
			class MAPCore_EXPORT FastLockedThreadingPolicy
			{
			protected:
				typedef itk::SimpleFastMutexLock  MutexType;
				typedef FastMutexLockSentinel SentinelType;

				/*! Initialize a sentinel and implicitly lock the mutex.
				 * @eguarantee strong
				 */
				void activateSentinel(SentinelType& sentinel) const;

				/*! Used by the policy owner to lock part of its code.
				 * @eguarantee strong
				 */
				void lock() const;

				/*! Used by the policy owner to unlock critical code.
				 * @eguarantee strong
				 */
				void unlock() const;

				FastLockedThreadingPolicy();
				~FastLockedThreadingPolicy();

			private:
				/*! This policy uses this mutex to lock critical code by the policy user.*/
				mutable MutexType _mutex;

				FastLockedThreadingPolicy(const FastLockedThreadingPolicy&);  //purposely not implemented
				void operator=(const FastLockedThreadingPolicy&);  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
