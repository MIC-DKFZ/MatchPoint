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

#include "mapDeploymentDLLInterface.h"
#include "mapDeploymentDLLHelper.h"
#include "mapDiscreteElements.h"
#include "mapConfigure.h"

#include "mapElxParameterFileRegistrationAlgorithm.h"
#include "ElxParameterFileCLI2DRegistration_ProfileResource.h"

typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
typedef map::algorithm::elastix::ParameterFileRegistrationAlgorithm<ImageType, ImageType, map::algorithm::ElxParameterFileCLI2DRegistrationUIDPolicy>
AlgorithmType;

mapDeployAlgorithmMacro(AlgorithmType);