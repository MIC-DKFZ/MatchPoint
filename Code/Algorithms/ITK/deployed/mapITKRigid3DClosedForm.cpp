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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/deployed/mapITKRigid3DClosedForm.cpp $
*/

#include "mapDeploymentDLLInterface.h"
#include "mapDeploymentDLLHelper.h"
#include "mapContinuousElements.h"
#include "mapITKRigid3DClosedFormRegistrationAlgorithmTemplate.h"
#include "mapConfigure.h"


/*! UID policy for the new reboxed algorithm. This policy gives the reboxed version of the algorithm a new
 * unique identifer to track the usage of the algorithm within any application.*/
mapGenerateAlgorithmUIDPolicyMacro(DefaultCommonRigidClosedFormAlgorithm3DUIDPolicy, "de.dkfz.matchpoint.common", "RigidClosedForm.3D.default", "1.0.0");

typedef map::core::continuous::Elements<3>::InternalPointSetType PointSetType;
typedef map::algorithm::boxed::ITKRigid3DClosedFormRegistrationAlgorithmTemplate<PointSetType, DefaultCommonRigidClosedFormAlgorithm3DUIDPolicy>::Type AlgorithmType;

typedef map::deployment::DeploymentDLLHelper<AlgorithmType> DLLHelperType;

/** @class ITKRigid3DClosedForm_default
 * @ingroup Data_point Model_rigid Det_comp_analytic Det_deterministic Det_res_single Dim_3D_3D Mod_multi
 */
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
	spUID = DLLHelperType::mapGetRegistrationAlgorithmUID();
};

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void mapGetRegistrationAlgorithmInstance(map::algorithm::RegistrationAlgorithmBase::Pointer &spAlgorithm, map::deployment::SyncObject *syncObject)
{
	spAlgorithm = DLLHelperType::mapGetRegistrationAlgorithmInstance(syncObject);
};