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


#include "mapDeploymentDLLHelper.h"

namespace map
{
	namespace deployment
	{

		template<typename TAlgorithmType>
		map::algorithm::UID::Pointer
		DeploymentDLLHelper<TAlgorithmType>::
		mapGetRegistrationAlgorithmUID()
		{
			return AlgorithmType::UID();
		};

		template<typename TAlgorithmType>
		map::core::String
		DeploymentDLLHelper<TAlgorithmType>::
		mapGetRegistrationAlgorithmProfile()
		{
			return map::core::String(AlgorithmType::AlgorithmProfile());
		};

		template<typename TAlgorithmType>
		typename DeploymentDLLHelper<TAlgorithmType>::AlgorithmBasePointer
		DeploymentDLLHelper<TAlgorithmType>::
		mapGetRegistrationAlgorithmInstance(SyncObject* pSyncObj)
		{
			Synchronizer::synchronizeDeployment(pSyncObj);
			AlgorithmBasePointer spBase = AlgorithmType::New().GetPointer();
			return spBase;
		};

	} // end namespace deployment
} // end namespace map
