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


#include "mapDeploymentSync.h"
#include "mapExceptionObject.h"
#include "mapLogbook.h"

#if !defined(_MSC_VER) && !defined(__APPLE__) && !defined(__linux__)
#include <auto_ptr.h>
#endif

#include <memory>


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
		SyncObject* Synchronizer::_SyncObject = nullptr;
		SyncObject* Synchronizer::_SyncedObject = nullptr;

		void
		Synchronizer::
		synchronizeDeployment(SyncObject* pSync)
		{
			if (pSync != nullptr)
			{
				_SyncedObject = pSync;
				::map::core::Logbook::setSynchronization(*pSync);
			}
		};

		SyncObject*
		Synchronizer::
		getSyncObject()
		{
			::std::unique_ptr<deployment::SyncObject> pNewSync(new SyncObject());

			::map::core::Logbook::getSynchronization(*pNewSync);

			if (_SyncObject == nullptr)
			{
				delete _SyncObject;
			}

			_SyncObject = pNewSync.release();

			return _SyncObject;
		};

	} // end namespace deployment
} // end namespace map
