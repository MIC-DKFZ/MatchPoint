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
#include <cassert>

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
				assert(_pMutex == nullptr); //must not be used before!

				_pMutex = pMutex;
				_pMutex->lock();
			}

			FastMutexLockSentinel::
			FastMutexLockSentinel()  
			{};

			FastMutexLockSentinel::
			~FastMutexLockSentinel()
			{
				if (_pMutex != nullptr)
				{
					_pMutex->unlock();
				}
			};

		} // end namespace services
	} // end namespace core
} // end namespace map
