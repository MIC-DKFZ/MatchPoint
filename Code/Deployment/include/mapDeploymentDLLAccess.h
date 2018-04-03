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


#ifndef __MAP_DEPLOYMENT_DLL_ACCESS_H
#define __MAP_DEPLOYMENT_DLL_ACCESS_H

#include "mapDeploymentDLLHandle.h"
#include "mapRegistrationAlgorithmBase.h"
#include "mapDeploymentExceptions.h"
#include "mapDeploymentSync.h"

namespace map
{
	namespace deployment
	{

		/**
		 * Function pointer for the mapGetDLLInterfaceVersion symbol in a deployment DLL.
		 * @sa mapGetDLLInterfaceVersion
		 * @ingroup DeployHost
		 */
		typedef void (* MAP_GET_DLL_INTERFACE_VERSION_FUNCTION_POINTER)(unsigned int& major,
				unsigned int& minor);

		/**
		 * Function pointer for the mapGetRegistrationAlgorithmUID symbol in a deployment DLL.
		 * @sa mapGetRegistrationAlgorithmUID
		 * @ingroup DeployHost
		 */
		typedef void (* MAP_GET_REGISTRATION_ALGORITHM_UID_FUNCTION_POINTER)(map::algorithm::UID::Pointer&
				spUID);

		/**
		 * Function pointer for the mapGetRegistrationAlgorithmUID symbol in a deployment DLL.
		 * @sa mapGetRegistrationAlgorithmUID
		 * @ingroup DeployHost
		 */
		typedef void (* MAP_GET_REGISTRATION_ALGORITHM_PROFILE_FUNCTION_POINTER)(
			const map::core::String& profile);

		/**
			 * Function pointer for the mapGetRegistrationAlgorithmInstance symbol in a deployment DLL.
			 * @sa mapGetRegistrationAlgorithmInstance
			 * @ingroup DeployHost
			 */
		typedef void (* MAP_GET_REGISTRATION_ALGORITHM_INSTANCE_FUNCTION_POINTER)(
			map::algorithm::RegistrationAlgorithmBase::Pointer& spAlgorithmBase,
			map::deployment::SyncObject* pSyncObject);

		typedef map::algorithm::RegistrationAlgorithmBase RegistrationAlgorithmBase;
		typedef RegistrationAlgorithmBase::Pointer RegistrationAlgorithmBasePointer;

		/*! Method tries to open the passed file as dll, checks for the interface version and
		 * compiles all information needed for a representing DLL information instance.
		 * @ingroup DeployHost
		 * @pre libraryFile must not be NULL
		 * @eguarantee strong
		 * @exception InvalidDLLException Thrown if file was not found, file is not a DLL or cannot be loaded.
		 * @exception MissingSymbolException Thrown if DLL misses any symbols.
		 * @exception InvalidInterfaceVersionException Thrown if the DLL has not a supported interface version.
		 * @exception InvalidUIDException Thrown if the DLL returns no (valid) UID instance.
		*/
		MAPDeployment_EXPORT DLLHandle::Pointer openDeploymentDLL(const char* libraryFile);
		MAPDeployment_EXPORT DLLHandle::Pointer openDeploymentDLL(const core::String& libraryFile);

		/*! Method tries to close the DLL specified by the passed info instance.
		  * @ingroup DeployHost
		 * @pre pDLLHandle must not be NULL
		 * @eguarantee strong
		 * @exception InvalidDLLException Thrown if DLL cannot be closed.
		*/
		MAPDeployment_EXPORT void closeDeploymentDLL(const DLLHandle* pDLLHandle);

		/*! Method tries to open the passed file (using openDeploymentDLL()), retrieves the UID of
		 * the algorithm stored in the DLL and closes the DLL again (using closeDeploymentDLL()).
		 * @ingroup DeployHost
		 * @pre libraryFile must not be NULL
		 * @eguarantee strong
		 * @exception InvalidDLLException Thrown if file was not found, file is not a DLL, cannot be loaded or closed.
		 * @exception MissingSymbolException Thrown if DLL misses any symbols.
		 * @exception InvalidInterfaceVersionException Thrown if the DLL has not a supported interface version.
		 * @exception InvalidUIDException Thrown if the DLL returns no (valid) UID instance.
		*/
		MAPDeployment_EXPORT algorithm::UID::ConstPointer peekDeploymentDLL(const char* libraryFile);
		MAPDeployment_EXPORT algorithm::UID::ConstPointer peekDeploymentDLL(const core::String&
				libraryFile);
		MAPDeployment_EXPORT void peekDeploymentDLL(const char* libraryFile,
				::map::algorithm::UID::ConstPointer& spUID, ::map::core::String& algProfile);
		MAPDeployment_EXPORT void peekDeploymentDLL(const core::String& libraryFile,
				::map::algorithm::UID::ConstPointer& spUID, ::map::core::String& algProfile);


		/*! Method requests an algorithm instance of the DLL specified by the passed DLL info.
		 * The pointer to the registration algorithm will be returned as result.
		 * @ingroup DeployHost
		 * @pre pDLLHandle must not be NULL
		 * @eguarantee strong
		 * @exception MissingSymbolException Thrown if DLL misses the mapGetRegistrationAlgorithmInstance symbol.
		 * @exception InvalidUIDException Thrown if the UID of the returned algorithm doesn't fit the UID of the DLL info instance.
		 * @exception InvalidAlgorithmException Thrown if the returned algorithm pointer is not valid.
		*/
		MAPDeployment_EXPORT RegistrationAlgorithmBasePointer getRegistrationAlgorithm(
			const DLLHandle* pDLLHandle);

		/**
		 * A function to determine if a passed filename is compliant to the the naming conventions
		 * for MatchPoint deployed algorithms: \n
		 * mdra[verioning]_[name].[dll|so|dylib]\n\n
		 * Example: mdra-D-0-9_FancyNewElasitc.dll
		 * @pre fileName pointer must not be NULL.
		 * @return Indicates if the file is compliant to the naming conventions.
		 */
		MAPDeployment_EXPORT bool checkFileNameIsMDRACompliant(const char* fileName);

    /**
		 * A function to determine if a file has the shared library extension in its name,
		 * this converts name to lower
		 * case before the compare, DynamicLoader always uses
		 * lower case for LibExtension values.
		 * @pre name pointer must not be NULL.
		 * @return Indicates if the file can be assumed to be a DLL by its (OS specific) extension
		 */
		MAPDeployment_EXPORT bool checkNameIsSharedLibrary(const char* name);

		/**
		 * function returns the os specific extension for deployed algorithms (Windows: .dll; Linux: .so; Mac OS: .dylib).
		 */
		MAPDeployment_EXPORT map::core::String getDeploymentDLLExtension();

    /**
    * function returns the os specific MDRA prefix for MDRA compliant file names:\n
    * mdra[verioning]\n\n
    * Example: mdra-D-0-12.
    */
    MAPDeployment_EXPORT map::core::String getDeploymentDLLMDRAPrefix();

	} //end of namespace deployment;

} //end of namespace map;

#endif
