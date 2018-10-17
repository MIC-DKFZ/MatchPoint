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

#include "mapDeploymentDLLHelper.h"
#include "mapDiscreteElements.h"
#include "mapContinuousElements.h"
#include "mapConfigure.h"

#include "mapJOMPlmBSplineCLIRegistrationAlgorithm.h"

#include "PlmJOMBSplineCLI3DRegistration_ProfileResource.h"

typedef map::core::discrete::Elements<3>::InternalImageType ImageType;
typedef map::core::continuous::Elements<3>::InternalPointSetType PointSetType;
typedef map::algorithm::boxed::JOMPlmBSplineCLIRegistrationAlgorithm<ImageType, ImageType, PointSetType, PointSetType, map::algorithm::PlmJOMBSplineCLI3DRegistrationUIDPolicy>
AlgorithmType;

mapDeployAlgorithmMacro(AlgorithmType);