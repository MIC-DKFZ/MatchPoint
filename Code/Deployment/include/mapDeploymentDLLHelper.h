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


#ifndef __MAP_DEPLOYMENT_DLL_HELPER_H
#define __MAP_DEPLOYMENT_DLL_HELPER_H

#include "mapRegistrationAlgorithmBase.h"
#include "mapUID.h"
#include "mapDeploymentSync.h"
#include "mapDeploymentDLLInterface.h"

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

			/*! Returns a smart pointer to the UID of the algorithm
			 */
			static map::algorithm::UID::Pointer mapGetRegistrationAlgorithmUID();

			/*! Returns a profile string containing the profile of the algorithm type.
			 * The profile is stored in xml format. String may be empty if no profile is specified.
			 */
			static map::core::String mapGetRegistrationAlgorithmProfile();

			/*! Returns a smart pointer to an instance of the algorithm (as RegistrationAlgorithmBase)
			 */
			static AlgorithmBasePointer mapGetRegistrationAlgorithmInstance(SyncObject* pSyncObj);

		private:
			DeploymentDLLHelper();  //purposely not implemented
			~DeploymentDLLHelper();  //purposely not implemented
			//No copy constructor allowed
			DeploymentDLLHelper(const Self& source);   //purposely not implemented
			void operator=(const Self&);  //purposely not implemented

		};

	}
}

#ifdef _WIN32
#define MAP_DEPLOYMENT_ALG_EXPORT extern "C" __declspec(dllexport)
#else
#define MAP_DEPLOYMENT_ALG_EXPORT extern "C"
#endif

/*!@def mapDeployAlgorithmMacro
 * This macro is used to throw a basic ExceptionObject within an object method.
 * The macro presumes that the object owns a method this->GetNameOfClass().\n
 * Use mapExceptionMacro() if you want to specifiy a arbitrary exception class that should be thrown.
 * @sa DeploymentDLLHelper
 * @sa DeploymentDLLInterface
 * @ingroup DeployAlgorithm
 */
#define mapDeployAlgorithmMacro(AlgorithmClass) \
	MAP_DEPLOYMENT_ALG_EXPORT void mapGetDLLInterfaceVersion(unsigned int &major, unsigned int &minor) \
	{ \
		major = MAP_DLL_INTERFACE_VERSION_MAJOR; \
		minor = MAP_DLL_INTERFACE_VERSION_MINOR; \
	}; \
	MAP_DEPLOYMENT_ALG_EXPORT void mapGetRegistrationAlgorithmUID(::map::algorithm::UID::Pointer &spUID) \
	{ \
		spUID = ::map::deployment::DeploymentDLLHelper<AlgorithmClass>::mapGetRegistrationAlgorithmUID(); \
	}; \
	MAP_DEPLOYMENT_ALG_EXPORT void mapGetRegistrationAlgorithmProfile(::map::core::String &profileString)\
	{\
		profileString = ::map::deployment::DeploymentDLLHelper<AlgorithmClass>::mapGetRegistrationAlgorithmProfile();\
	};\
	MAP_DEPLOYMENT_ALG_EXPORT void mapGetRegistrationAlgorithmInstance(::map::algorithm::RegistrationAlgorithmBase::Pointer &spAlgorithm, ::map::deployment::SyncObject *syncObject)\
	{\
		spAlgorithm = ::map::deployment::DeploymentDLLHelper<AlgorithmClass>::mapGetRegistrationAlgorithmInstance(syncObject);\
	}


#ifndef MatchPoint_MANUAL_TPP
#include "mapDeploymentDLLHelper.tpp"
#endif


#endif
