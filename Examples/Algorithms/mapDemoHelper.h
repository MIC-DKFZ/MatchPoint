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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#ifndef __MAP_DEMO_HELPER_H
#define __MAP_DEMO_HELPER_H

#include "mapContinuousElements.h"
#include "mapDiscreteElements.h"

typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
typedef map::core::continuous::Elements<2>::InternalPointSetType   LandmarksType;

struct AppGlobals
{
	bool doTest;
	std::string targetImageFileName;
	std::string movingImageFileName;
	std::string movingImage2FileName;
	std::string movingLandmarksFileName;
	std::string resultImageFileName;
	std::string resultImage2FileName;
	std::string resultLandmarksFileName;
	std::string referenceImageFileName;
	std::string referenceImage2FileName;
	std::string referenceLandmarksFileName;

	ImageType::Pointer spTargetImage;
	ImageType::Pointer spMovingImage;
	ImageType::Pointer spMovingImage2;
	LandmarksType::Pointer spMovingLandmarks;

	ImageType::Pointer spReferenceImage;
	ImageType::Pointer spReferenceImage2;
	LandmarksType::Pointer spReferenceLandmarks;

	ImageType::Pointer spResultImage;
	ImageType::Pointer spResultImage2;
	LandmarksType::Pointer spResultLandmarks;

	double imageCheckThreshold;
	double lmCheckThreshold;
	std::string testFilePattern;
};

int parseArguments(int argc, char* argv[], AppGlobals& globals);

LandmarksType::Pointer loadLM(const std::string& lmFileName);

int loadData(AppGlobals& globals);

int saveResults(AppGlobals& globals);

int testResults(AppGlobals& globals);

#endif