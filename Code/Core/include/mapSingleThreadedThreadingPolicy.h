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


#ifndef __MAP_SINGLE_THREADED_THREADING_POLICY_H
#define __MAP_SINGLE_THREADED_THREADING_POLICY_H

#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		namespace services
		{
			/*! @class SingleThreadedThreadingPolicy
			* @brief Policy is used in single threaded enviroments.
			*
			* This threading policiy assumes that the owner is only used in single
			* threaded envirmoments. Thus there is no locking at all with this policy.
			* lock() and unlock() are just empty stubs.
			* @ingroup ThreadingPolicies
			*/
			class MAPCore_EXPORT SingleThreadedThreadingPolicy
			{
			protected:

				/*! Used by the policy owner to lock part of its code.
				 * @eguarantee strong
				 */
				void lock() const;

				/*! Used by the policy owner to unlock critical code.
				 * @eguarantee strong
				 */
				void unlock() const;

				SingleThreadedThreadingPolicy();
				~SingleThreadedThreadingPolicy();

			private:
				SingleThreadedThreadingPolicy(const SingleThreadedThreadingPolicy&);  //purposely not implemented
				void operator=(const SingleThreadedThreadingPolicy&);  //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#endif
