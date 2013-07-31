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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Examples/Algorithms/mapDemoHelloWorldRegistration1.cpp $
*/

/*!@file
 * @ingroup Examples
 *********************************************************
 * Demo: demoHelloWorldRegistration1
 * Topics:
 * - First basic example demonstrating how to register
 *********************************************************/

#undef MAP_SEAL_ALGORITHMS

#include "mapDemoHelloWorldRegistration1Helper.h"

#include "mapRigidMSRegistrationAlgorithmTemplate.h"
#include "mapImageMappingTask.h"

int main(int argc, char *argv[])
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
	typedef map::algorithm::boxed::RigidMSRegistrationAlgorithmTemplate<ImageType>::Type AlgorithmType;

	AlgorithmType::Pointer spAlgorithm = AlgorithmType::New();

	//Now we setting some optimizer parameters.
	spAlgorithm->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(4.00);
	spAlgorithm->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(0.01);

	spAlgorithm->getConcreteOptimizerControl()->getConcreteOptimizer()->SetNumberOfIterations(200);

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
	 * Register the data by tasks
	 ***************************************************************/

	//define registration tasks
	std::cout << "Define registration task..." << std::endl;

	typedef map::core::ImageMappingTask<AlgorithmType::RegistrationType, ImageType, ImageType> ImageMappingTaskType;

	ImageMappingTaskType::Pointer spImageTask = ImageMappingTaskType::New();
	spImageTask->setInputImage(globals.spMovingImage);
	spImageTask->setRegistration(spRegistration);

	//Process the task
	std::cout << "Process registration task..." << std::endl;
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