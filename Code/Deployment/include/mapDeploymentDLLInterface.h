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


#ifndef __MAP_DEPLOYMENT_DLL_INTERFACE_H
#define __MAP_DEPLOYMENT_DLL_INTERFACE_H

#include "mapRegistrationAlgorithmBase.h"
#include "mapUID.h"
#include "mapString.h"
#include "mapDeploymentSync.h"

/*!@file
 * This file declares the available function symbols for default MatchPoint deployment DLLs.
 * If you want to deploy a algorithm via DLL, add this file to your project and define/implement
 * the functions declared in this file.\n
 * For a default implementation of mapGetDLLInterfaceVersion() just link
 * your project to the MAPDeployment library which already contains that function. For the other functions see
 * mapDeploymentDLLHelper.h
 * @ingroup DeployAlgorithm
 */

/*! @brief Offers information of the used interface version. This function is guaranteed, thus it
 * can be used to detect changes in the rest of the interface or its semantic by checking on the
 * major and/or minor version.
 * @remark Normaly you just have to include mapGetDLLInterfaceVersion.cpp to your project for adding
 * a proper implemtation of this function for your DLL.
 * @ingroup DeployAlgorithm
 */
extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetDLLInterfaceVersion(unsigned int& major, unsigned int& minor);

/*! @brief Returns a smart pointer to the UID of the algorithm offered by the deployment DLL.
 * @ingroup DeployAlgorithm
 */
extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetRegistrationAlgorithmUID(map::algorithm::UID::Pointer& spUID);

/*! @brief Returns a profile string containing the profile of the algorithm offered by the deployment DLL.
 * The profile is stored in xml format. String may be empty if no profile is specified.
 * @ingroup DeployAlgorithm
 */
extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetRegistrationAlgorithmProfile(map::core::String& profileString);

/*! @brief Returns a smart pointer to an instance of the algorithm (as RegistrationAlgorithmBase) offered by the DLL.
 * @ingroup DeployAlgorithm
 */
extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetRegistrationAlgorithmInstance(map::algorithm::RegistrationAlgorithmBase::Pointer&
		spAlgorithmBase, map::deployment::SyncObject* pSyncObject);

#endif
