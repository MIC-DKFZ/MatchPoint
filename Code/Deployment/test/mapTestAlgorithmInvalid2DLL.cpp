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

/*! @file
 * invalid test dll that misses the mapGetRegistrationAlgorithmUID symbol.
 */

#include "mapDeploymentDLLInterface.h"
#include "mapDeploymentDLLHelper.h"
#include "mapDiscreteElements.h"
#include "mapDummyImageRegistrationAlgorithm.h"
#include "mapConfigure.h"

mapGenerateAlgorithmUIDPolicyMacro(InvalidTestAlgUIDPolicy, "de.dkfz.matchpoint.test",
								   "InvalidAlgorithm2_missingSymbol", "1.0", "InvalidAlgorithm2_missingSymbol");

typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
typedef map::algorithm::DummyImageRegistrationAlgorithm<ImageType, ImageType, InvalidTestAlgUIDPolicy>
AlgorithmType;

typedef map::deployment::DeploymentDLLHelper<AlgorithmType> DLLHelperType;

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetDLLInterfaceVersion(unsigned int& major, unsigned int& minor)
{
	major = MAP_DLL_INTERFACE_VERSION_MAJOR;
	minor = MAP_DLL_INTERFACE_VERSION_MINOR;
};

//purposely not implemented
//extern "C"
//#ifdef _WIN32
//__declspec( dllexport )
//#endif
//void mapGetRegistrationAlgorithmUID(map::algorithm::UID::Pointer& spUID)
//{
//  spUID = DLLHelperType::mapGetRegistrationAlgorithmUID();
//};

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetRegistrationAlgorithmProfile(map::core::String& profile)
{
	profile = "InvalidAlgorithm2_missingSymbol";
};


extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetRegistrationAlgorithmInstance(map::algorithm::RegistrationAlgorithmBase::Pointer&
		spAlgorithm, map::deployment::SyncObject* syncObject)
{
	spAlgorithm = DLLHelperType::mapGetRegistrationAlgorithmInstance(syncObject);
};