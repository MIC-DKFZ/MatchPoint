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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Examples/Algorithms/mapDemoHelper.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapDemoHelper.h"
#include "mapSimpleLandMarkFileReader.h"

#include "litTestImageIO.h"
#include "litCheckMacros.h"
#include "litImageTester.h"
#include "litPointSetTester.h"

#include <fstream>

int parseArguments(int argc, char *argv[], AppGlobals &globals)
{
	if ((argc < 8) || (argc < 12 && argc > 8))
	{
		return EXIT_FAILURE;
	}

	//Get standard parameters
	globals.targetImageFileName = argv[1];
	globals.movingImageFileName = argv[2];
	globals.movingImage2FileName = argv[3];
	globals.movingLandmarksFileName = argv[4];

	if (strcmp(argv[5], "-test") != 0)
	{
		globals.doTest = false;
		globals.resultImageFileName = argv[5];
		globals.resultImage2FileName = argv[6];
		globals.resultLandmarksFileName = argv[7];
	}
	else
	{
		globals.doTest = true;
		globals.referenceImageFileName = argv[6];
		globals.referenceImage2FileName = argv[7];
		globals.referenceLandmarksFileName = argv[8];

		std::istringstream istream;
		istream.str(argv[9]);
		istream >> globals.imageCheckThreshold;

		istream.clear();
		istream.str(argv[10]);
		istream >> globals.lmCheckThreshold;

		globals.testFilePattern = argv[11];
	}

	return EXIT_SUCCESS;
}

int loadData(AppGlobals &globals)
{
	globals.spTargetImage = lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(globals.targetImageFileName);

	if (globals.spTargetImage.IsNull())
	{
		std::cerr << "Error. Cannot load target image: " << globals.targetImageFileName << std::endl;
		return EXIT_FAILURE;
	}

	globals.spMovingImage = lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(globals.movingImageFileName);

	if (globals.spMovingImage.IsNull())
	{
		std::cerr << "Error. Cannot load moving image: " << globals.movingImageFileName << std::endl;
		return EXIT_FAILURE;
	}

	globals.spMovingImage2 = lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(globals.movingImage2FileName);

	if (globals.spMovingImage2.IsNull())
	{
		std::cerr << "Error. Cannot load moving image 2: " << globals.movingImage2FileName << std::endl;
		return EXIT_FAILURE;
	}

	//load landmark files
	globals.spMovingLandmarks = map::utilities::loadLandMarksFromFile<LandmarksType>(globals.movingLandmarksFileName);

	if (globals.spMovingLandmarks.IsNull())
	{
		std::cerr << "Error. Cannot load moving landmarks: " << globals.movingLandmarksFileName << std::endl;
		return EXIT_FAILURE;
	}

	if (globals.doTest)
	{
		globals.spReferenceImage = lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(globals.referenceImageFileName);

		if (globals.spReferenceImage.IsNull())
		{
			std::cerr << "Error. Cannot load moving image: " << globals.referenceImageFileName << std::endl;
			return EXIT_FAILURE;
		}

		globals.spReferenceImage2 = lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(globals.referenceImage2FileName);

		if (globals.spReferenceImage2.IsNull())
		{
			std::cerr << "Error. Cannot load moving image 2: " << globals.referenceImage2FileName << std::endl;
			return EXIT_FAILURE;
		}

		//load landmark files
		globals.spReferenceLandmarks = map::utilities::loadLandMarksFromFile<LandmarksType>(globals.referenceLandmarksFileName);

		if (globals.spReferenceLandmarks.IsNull())
		{
			std::cerr << "Error. Cannot load reference landmarks: " << globals.referenceLandmarksFileName << std::endl;
			return EXIT_FAILURE;
		}

	}

	return EXIT_SUCCESS;
}

int saveResults(AppGlobals &globals)
{
	//save result data
	std::cout << std::endl << "Save result data..." << std::endl;

	lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::writeImage(globals.spResultImage, globals.resultImageFileName);
	lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::writeImage(globals.spResultImage2, globals.resultImage2FileName);

	std::ofstream resultPointsFile;
	resultPointsFile.open(globals.resultLandmarksFileName.c_str());

	for (LandmarksType::PointsContainer::Iterator it = globals.spResultLandmarks->GetPoints()->Begin(); it != globals.spResultLandmarks->GetPoints()->End(); ++it)
	{
		resultPointsFile << it.Value();
	}

	resultPointsFile.close();

	std::cout << std::endl << "Registered data sucessfully saved!" << std::endl;
	return EXIT_SUCCESS;
}

int testResults(AppGlobals &globals)
{
	PREPARE_DEFAULT_TEST_REPORTING;

	//check the first result image
	CHECK(globals.spResultImage.IsNotNull());

	lit::ImageTester<ImageType, itk::Image<unsigned char, 2> > tester;
	tester.setExpectedImage(globals.spReferenceImage);
	tester.setActualImage(globals.spResultImage);
	tester.setCheckThreshold(globals.imageCheckThreshold);
	tester.setTestFileName(globals.testFilePattern + "_Image1");
	tester.setSaveTestFiles(true);

	CHECK_TESTER(tester);

	CHECK(globals.spResultImage2.IsNotNull());

	tester.setExpectedImage(globals.spReferenceImage2);
	tester.setActualImage(globals.spResultImage2);
	tester.setTestFileName(globals.testFilePattern + "_Image2");

	CHECK_TESTER(tester);

	CHECK(globals.spResultLandmarks.IsNotNull());

	lit::PointSetTester<LandmarksType> lmTester;
	lmTester.setExpectedPointSet(globals.spReferenceLandmarks);
	lmTester.setActualPointSet(globals.spResultLandmarks);
	lmTester.setCheckThreshold(globals.lmCheckThreshold);

	CHECK_TESTER(lmTester);

	RETURN_AND_REPORT_TEST_SUCCESS;
}