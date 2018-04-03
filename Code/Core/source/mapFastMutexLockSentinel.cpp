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

#include "mapFastMutexLockSentinel.h"
#include <assert.h>

namespace map
{
	namespace core
	{
		namespace services
		{
			void
			FastMutexLockSentinel::
			initializeSentinel(MutexType* pMutex)
			{
				assert(_pMutex == NULL); //must not be used before!

				_pMutex = pMutex;
				_pMutex->Lock();
			}

			FastMutexLockSentinel::
			FastMutexLockSentinel() : _pMutex(NULL)
			{};

			FastMutexLockSentinel::
			~FastMutexLockSentinel()
			{
				if (_pMutex)
				{
					_pMutex->Unlock();
				}
			};

		} // end namespace services
	} // end namespace core
} // end namespace map
