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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Examples/Algorithms/mapDemoHelloWorldRegistration1Helper.h $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#ifndef __MAP_DEMO_HELLO_WORLD_REGISTRATION1_HELPER_H
#define __MAP_DEMO_HELLO_WORLD_REGISTRATION1_HELPER_H

#include "mapContinuousElements.h"
#include "mapDiscreteElements.h"

typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
typedef map::core::continuous::Elements<2>::InternalPointSetType   LandmarksType;

struct AppGlobals
{
	bool doTest;
	std::string targetImageFileName;
	std::string movingImageFileName;
	std::string resultImageFileName;
	std::string referenceImageFileName;

	ImageType::Pointer spTargetImage;
	ImageType::Pointer spMovingImage;

	ImageType::Pointer spReferenceImage;

	ImageType::Pointer spResultImage;

	double imageCheckThreshold;
	double lmCheckThreshold;
	std::string testFilePattern;

	bool testShouldFail;

	AppGlobals();
};

int parseArguments(int argc, char *argv[], AppGlobals &globals);

int loadData(AppGlobals &globals);

int saveResults(AppGlobals &globals);

int testResults(AppGlobals &globals);

#endif