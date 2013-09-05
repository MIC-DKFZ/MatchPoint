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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/test/mapTestAlgorithmInvalid3DLL.cpp $
*/

/*! @file
 * invalid test dll that misses the mapGetRegistrationAlgorithmInstance symbol.
 */

#include "mapDeploymentDLLHelper.h"
#include "mapDiscreteElements.h"
#include "mapDummyImageRegistrationAlgorithm.h"
#include "mapConfigure.h"

mapGenerateAlgorithmUIDPolicyMacro(InvalidTestAlgUIDPolicy,"de.dkfz.matchpoint.test", "InvalidAlgorithm7_missingSymbol", "1.0", "InvalidAlgorithm7_missingSymbol");

typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
typedef map::algorithm::DummyImageRegistrationAlgorithm<ImageType, ImageType,InvalidTestAlgUIDPolicy> AlgorithmType;

typedef map::deployment::DeploymentDLLHelper<AlgorithmType> DLLHelperType;

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetDLLInterfaceVersion(unsigned int &major, unsigned int &minor)
{
	major = MAP_DLL_INTERFACE_VERSION_MAJOR;
	minor = MAP_DLL_INTERFACE_VERSION_MINOR;
};

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetRegistrationAlgorithmUID(map::algorithm::UID::Pointer &spUID)
{
	spUID = map::algorithm::UID::New("de.dkfz.matchpoint.test", "InvalidAlgorithm7_missingSymbol", "1.0", "");
};

//extern "C"
//#ifdef _WIN32
//  __declspec(dllexport)
//#endif
//  void mapGetRegistrationAlgorithmProfile(map::core::String& profile)
//{
//  profile = "InvalidAlgorithm7_missingSymbol";
//};

extern "C"
#ifdef _WIN32
__declspec( dllexport )
#endif
void mapGetRegistrationAlgorithmInstance(map::algorithm::RegistrationAlgorithmBase::Pointer& spAlgorithm, map::deployment::SyncObject* pSyncObject)
{
  spAlgorithm = DLLHelperType::mapGetRegistrationAlgorithmInstance(pSyncObject);
};