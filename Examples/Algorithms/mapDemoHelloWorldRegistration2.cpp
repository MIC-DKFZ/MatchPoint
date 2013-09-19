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

/*!@file
 * @ingroup Examples
 *********************************************************
 * Demo: demoHelloWorldRegistration2
 * Topics:
 * - How to establish boxed algorithm with special
 *   settings?
 *
 * In the first hello world example some algorithm
 * settings were set explicit. This could be a tideous
 * task, espacially if a algorithm is needed often.
 * This example gives a first glance on the posibilities
 * to "rebox" algorithms and e.g. hard code special
 * parameter settings.
 *********************************************************/

#undef MAP_SEAL_ALGORITHMS

#include "mapDemoHelloWorldRegistration1Helper.h"
#include "mapImageMappingTask.h"

//This header file includes the new reboxed algorithm
//for further information see include file.
#include "mapDemoRegistrationAlgorithmTemplate.h"

int main(int argc, char* argv[])
{
	AppGlobals globals;
	int result = EXIT_FAILURE;

	//parse command line arguments
	if (parseArguments(argc, argv, globals) == EXIT_FAILURE)
	{
		std::cerr << "Missing Parameters " << std::endl;
		std::cerr << "Usage: " << argv[0];
		std::cerr << " <targetImage> <movingImage>";
		std::cerr << " [[<resultImage>]";
		std::cerr << " |[-test <referenceImage> <imageCheckThreshold> ";
		std::cerr << " <lmCheckThreshold> <testFilePattern>]]" << std::endl;
		return EXIT_FAILURE;
	}

	//load image and landmark files
	std::cout << "Load images and landmarks..." << std::endl;

	if (loadData(globals) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}


	/***************************************************************
	 * Establish a fixed registration algorithm
	 ***************************************************************/

	std::cout << "Establish registration algorithm..." << std::endl;

	//use one of the prepared and already "boxed" algorithms of MatchPoint.
	//this shows one of the key ideas of MatchPoint:
	//Offering a framework to build registration algorithms and delivering
	//them as boxed in such a way that makes it easy to use
	//
	//In this case it is an itk based algorithm formed by a rigid transform,
	//a mean squares metric and a regular step gradient decent algorithm.
	typedef map::algorithm::boxed::DemoRegistrationAlgorithm<ImageType> AlgorithmType;

	AlgorithmType::Pointer spAlgorithm = AlgorithmType::New();

	//Finally we set moving and target image for that should be
	//used by the image based registration algorithm
	spAlgorithm->setMovingImage(globals.spMovingImage);
	spAlgorithm->setTargetImage(globals.spTargetImage);

	//The algorithm is set up and ready to run...


	/***************************************************************
	 * Determine registration
	 ***************************************************************/

	std::cout << "Starting to determine the registration..." << std::endl;

	AlgorithmType::RegistrationType::Pointer spRegistration = spAlgorithm->getRegistration();

	std::cout << std::endl << "Registration determined..." << std::endl;
	//Thats all. Now we have a registration that map the moving image into the target image
	//space. But the algorithm only delivers the registration as a mapping function between
	//moving and target image space. So the moving image must be mapped...


	/***************************************************************
	 * Map the data by tasks
	 ***************************************************************/

	//define mapping tasks
	std::cout << "Define registration task..." << std::endl;

	typedef map::core::ImageMappingTask<AlgorithmType::RegistrationType, ImageType, ImageType>
	ImageMappingTaskType;

	ImageMappingTaskType::Pointer spImageTask = ImageMappingTaskType::New();
	spImageTask->setInputImage(globals.spMovingImage);
	spImageTask->setRegistration(spRegistration);

	//Process the task
	std::cout << "Process mapping task..." << std::endl;
	spImageTask->execute();


	/***************************************************************
	 * Save or test the results
	 ***************************************************************/

	globals.spResultImage = spImageTask->getResultImage();

	if (globals.doTest)
	{
		result = testResults(globals);
	}
	else
	{
		result = saveResults(globals);
	}


	return result;
}