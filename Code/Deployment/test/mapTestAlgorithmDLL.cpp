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
 * correct test dll that deploys the default DemoRegistrationAlgorithm.
 * The DLL is used for several tests of some MatchPoint deployment class
 * and to implicitly test the mapDeployAlgorithmMacro.
 */

#include "mapDeploymentDLLHelper.h"
#include "mapDiscreteElements.h"
#include "mapDummyImageRegistrationAlgorithm.h"
#include "mapConfigure.h"

mapGenerateAlgorithmUIDPolicyMacro(TestAlgorithmDLLPolicy, "de.dkfz.matchpoint", "TestAlgorithm",
								   "1.0.0", "testprofile");

typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
typedef map::algorithm::DummyImageRegistrationAlgorithm<ImageType, ImageType, TestAlgorithmDLLPolicy>
AlgorithmType;

mapDeployAlgorithmMacro(AlgorithmType);