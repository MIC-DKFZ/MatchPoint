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

#include "mapDemoHelloWorldRegistration1Helper.h"

#include "litTestImageIO.h"
#include "litCheckMacros.h"
#include "litImageTester.h"
#include "litPointSetTester.h"

#include <fstream>

int parseArguments(int argc, char* argv[], AppGlobals& globals)
{
	if ((argc < 4) || (argc < 8 && argc > 4))
	{
		return EXIT_FAILURE;
	}

	//Get standard parameters
	globals.targetImageFileName = argv[1];
	globals.movingImageFileName = argv[2];

	if (strcmp(argv[3], "-test") != 0)
	{
		globals.doTest = false;
		globals.resultImageFileName = argv[3];
	}
	else
	{
		globals.doTest = true;
		globals.referenceImageFileName = argv[4];

		std::istringstream istream;
		istream.str(argv[5]);
		istream >> globals.imageCheckThreshold;

		istream.clear();
		istream.str(argv[6]);
		istream >> globals.lmCheckThreshold;

		globals.testFilePattern = argv[7];
	}

	return EXIT_SUCCESS;
}

int loadData(AppGlobals& globals)
{
	globals.spTargetImage =
		lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(
			globals.targetImageFileName);

	if (globals.spTargetImage.IsNull())
	{
		std::cerr << "Error. Cannot load target image: " << globals.targetImageFileName << std::endl;
		return EXIT_FAILURE;
	}

	globals.spMovingImage =
		lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(
			globals.movingImageFileName);

	if (globals.spMovingImage.IsNull())
	{
		std::cerr << "Error. Cannot load moving image: " << globals.movingImageFileName << std::endl;
		return EXIT_FAILURE;
	}

	if (globals.doTest)
	{
		globals.spReferenceImage =
			lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::readImage(
				globals.referenceImageFileName);

		if (globals.spReferenceImage.IsNull())
		{
			std::cerr << "Error. Cannot load moving image: " << globals.referenceImageFileName << std::endl;
			return EXIT_FAILURE;
		}

	}

	return EXIT_SUCCESS;
}

int saveResults(AppGlobals& globals)
{
	//save result data
	std::cout << std::endl << "Save result data..." << std::endl;

	lit::TestImageIO<unsigned char, map::core::discrete::Elements<2>::InternalImageType>::writeImage(
		globals.spResultImage, globals.resultImageFileName);

	return EXIT_SUCCESS;
}

int testResults(AppGlobals& globals)
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

	tester.setInvertCheck(globals.testShouldFail);

	CHECK_TESTER(tester);

	CHECK(globals.spResultImage.IsNotNull());

	RETURN_AND_REPORT_TEST_SUCCESS;
}

AppGlobals::AppGlobals()
{
	doTest = false;
	imageCheckThreshold = 0;
	lmCheckThreshold = 0;

	testShouldFail = false;
};