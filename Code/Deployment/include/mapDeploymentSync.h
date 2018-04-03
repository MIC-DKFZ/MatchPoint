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


#ifndef __MAP_DEPLOYMENT_SYNC_H
#define __MAP_DEPLOYMENT_SYNC_H

#include "mapSyncObject.h"
#include "mapMAPDeploymentExports.h"

namespace map
{
	namespace deployment
	{

		/** @class Synchronizer
		* @brief Synchronizes deployment dlls with the host application.
		*
		* This class is used in deployment DLLs/SOs (by DeploymentDLLHelper) to synchronize
		* the dll with global settings of the host.\n
		* E.g. that the same map::core::Logbook implementation and settings are used.
		*
		* @ingroup DeployAlgorithm
		*/
		class MAPDeployment_EXPORT Synchronizer
		{
		public:
			/** Standard class typedefs. */
			typedef Synchronizer Self;

			/** This function is used in deployment DLLs/SOs (by DeploymentDLLHelper) to synchronize
			* the dll with global settings of the host.
			* @param [in] pSync Pointer to the sync object that will be used by the function to realize the synchronization.
			*/
			static void synchronizeDeployment(SyncObject* pSync);

			static SyncObject* getSyncObject();

			Synchronizer();
			~Synchronizer();

		private:
			friend class CleanUpSyncHelper;

			/** Pointer is null if the synchronizer is used in the deployment dll. If used in the host (getSyncObject()) it will point
			* to the SyncObject of the host.
			* */
			static SyncObject* _SyncObject;

			/** Pointer is null if the synchronizer is used in the host. If used in the deployment dll (synchronizeDeployment()) it will point
			* to the SyncObject of the host.
			* */
			static SyncObject* _SyncedObject;
		};

	} // end namespace deployment
} // end namespace map

#endif
