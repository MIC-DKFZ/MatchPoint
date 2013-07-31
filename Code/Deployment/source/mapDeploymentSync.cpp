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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/source/mapDeploymentSync.cpp $
*/


#include "mapDeploymentSync.h"
#include "mapExceptionObject.h"
#include "mapLogbook.h"

#ifndef _MSC_VER
#include <auto_ptr.h>
#endif

namespace map
{
	namespace deployment
	{

		class CleanUpSyncHelper
		{
		public:
			inline void Use()
			{
			}

			~CleanUpSyncHelper()
			{
				delete Synchronizer::_SyncObject;
			}
		};

		static CleanUpSyncHelper CleanUpSyncHelperGlobal;
		SyncObject *Synchronizer::_SyncObject = NULL;
		SyncObject *Synchronizer::_SyncedObject = NULL;

		void
		Synchronizer::
		synchronizeDeployment(SyncObject *pSync)
		{
			if (pSync)
			{
				_SyncedObject = pSync;
				core::Logbook::setSynchronization(*pSync);
			}
		};

		SyncObject *
		Synchronizer::
		getSyncObject()
		{
			::std::auto_ptr<deployment::SyncObject> pNewSync(new SyncObject());

			core::Logbook::getSynchronization(*pNewSync);

			if (!_SyncObject)
			{
				delete _SyncObject;
			}

			_SyncObject = pNewSync.release();

			return _SyncObject;
		};

	} // end namespace deployment
} // end namespace map