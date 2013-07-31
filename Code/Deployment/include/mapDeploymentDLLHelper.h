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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/include/mapDeploymentDLLHelper.h $
*/




#ifndef __MAP_DEPLOYMENT_DLL_HELPER_H
#define __MAP_DEPLOYMENT_DLL_HELPER_H

#include "mapRegistrationAlgorithmBase.h"
#include "mapUID.h"
#include "mapDeploymentSync.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
    mark code as components of this project
 */
namespace map
{
	namespace deployment
	{

		/*! @class DeploymentDLLHelper
		    @brief This is a helper class for developers who want to deploy an algorithm via DLL/shared objects.
		    See the dll test projects (e.g. mapTestAlgorithm) for examples how to use this helper class.
		    @ingroup DeployAlgorithm
		 */
		template<typename TAlgorithmType>
		class DeploymentDLLHelper
		{
		public:
			typedef DeploymentDLLHelper<TAlgorithmType> Self;

			typedef TAlgorithmType                            AlgorithmType;
			typedef typename AlgorithmType::Pointer           AlgorithmPointer;
			typedef map::algorithm::RegistrationAlgorithmBase AlgorithmBaseType;
			typedef typename AlgorithmBaseType::Pointer       AlgorithmBasePointer;

			static map::algorithm::UID::Pointer mapGetRegistrationAlgorithmUID();

			static AlgorithmBasePointer mapGetRegistrationAlgorithmInstance(SyncObject *pSyncObj);

		private:
			DeploymentDLLHelper();  //purposely not implemented
			~DeploymentDLLHelper();  //purposely not implemented
			//No copy constructor allowed
			DeploymentDLLHelper(const Self &source);   //purposely not implemented
			void operator=(const Self &); //purposely not implemented

		};

	}

}

#ifndef MatchPoint_MANUAL_TPP
#include "mapDeploymentDLLHelper.tpp"
#endif


#endif
