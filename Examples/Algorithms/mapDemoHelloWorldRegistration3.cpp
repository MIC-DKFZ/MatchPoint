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
 * - How to process multiple data with on registration?
 * - Why have is the mapping seperated from the registration
 *   in explicit task objects?
 *
 * This example equals practically the second example. The only
 * real difference is in the data registration/mapping part. Now
 * we not only register one image (the common suspect: the moving
 * image) but an additional image and a set of landmarks. What
 * sounds like a trival task, needs from a technical point of
 * view a lot of registration domain knowledg. Now we have two
 * data types: continuous (landmarks/points) and discrete (images).
 * And we need two mapping directions: direct for points and
 * inverse mapping for images. Image registrations in itk e.g.
 * determin an inverse mapping to register image from moving to
 * target space. Thus the result of this "itk native"
 * registration algorithms can not be used directly on points.
 * Using MatchPoint you do not need to be aware of such issues.
 * You just have to determine a registration, thus a how a
 * moving space can be mapped onto an target space, by an
 * algorithm. This MatchPoint registration is then able to map
 * several data types. (Even new data types and there mapping rules
 * can be integrated dynamically).
 * Further explinations and benifits of the registration-task-schema
 * (like concurent task processing) are adressed with in this example.
 *****************************************************************/

#undef MAP_SEAL_ALGORITHMS

#include "mapDemoHelper.h"

//This header file includes the new reboxed algorithm
//for further information see include file.
#include "mapDemoRegistrationAlgorithmTemplate.h"

#include "mapImageMappingTask.h"
#include "mapPointSetMappingTask.h"
#include "mapMappingTaskBatch.h"

int main(int argc, char* argv[])
{
	//Parts of the code that are simelar to
	//demoHelloWorldRegistration2.cpp have
	//no comment. Please see demoHelloWorldRegistration2.cpp
	//for informations in these parts

	AppGlobals globals;
	int result = EXIT_FAILURE;

	if (parseArguments(argc, argv, globals) == EXIT_FAILURE)
	{
		std::cerr << "Missing Parameters " << std::endl;
		std::cerr << "Usage: " << argv[0];
		std::cerr << " <targetImage> <movingImage> <movingImage2>";
		std::cerr << " <movingLandmarksFile> [[<resultImage> <resultImage2>";
		std::cerr << " <resultLandmarksFile>]|[-test <referenceImage1>";
		std::cerr << " <referenceImage2> <referenceLandmarksFile>";
		std::cerr << " <imageCheckThreshold> <lmCheckThreshold> <testFilePattern>]]" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Load images and landmarks..." << std::endl;

	if (loadData(globals) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	/***************************************************************
	 * Establish a fixed registration algorithm
	 ***************************************************************/

	std::cout << "Establish registration algorithm..." << std::endl;

	typedef map::algorithm::boxed::DemoRegistrationAlgorithm<ImageType> AlgorithmType;

	AlgorithmType::Pointer spAlgorithm = AlgorithmType::New();

	spAlgorithm->setMovingImage(globals.spMovingImage);
	spAlgorithm->setTargetImage(globals.spTargetImage);

	/***************************************************************
	 * Determine registration
	 ***************************************************************/

	std::cout << "Starting to determine the registration..." << std::endl;

	AlgorithmType::RegistrationType::Pointer spRegistration = spAlgorithm->getRegistration();

	std::cout << std::endl << "Registration determined..." << std::endl;

	/***************************************************************
	 * Map the data by tasks
	 ***************************************************************/

	//define mapping tasks
	std::cout << "Define mapping tasks..." << std::endl;

	typedef map::core::ImageMappingTask<AlgorithmType::RegistrationType, ImageType, ImageType>
	ImageMappingTaskType;
	typedef map::core::PointSetMappingTask<AlgorithmType::RegistrationType, LandmarksType, LandmarksType>
	PointSetMappingTaskType;

	ImageMappingTaskType::Pointer spImageTask = ImageMappingTaskType::New();
	spImageTask->setInputImage(globals.spMovingImage);

	ImageMappingTaskType::Pointer spImage2Task = ImageMappingTaskType::New();
	spImage2Task->setInputImage(globals.spMovingImage2);

	PointSetMappingTaskType::Pointer spPointSetTask = PointSetMappingTaskType::New();
	spPointSetTask->setInputPointSet(globals.spMovingLandmarks);

	std::cout << "Setup mapping task batch..." << std::endl;
	typedef map::core::MappingTaskBatch<AlgorithmType::RegistrationType> MappingTaskBatchType;
	MappingTaskBatchType::Pointer spBatch = MappingTaskBatchType::New();

	//add tasks to batch
	spBatch->addTask(spImageTask);
	spBatch->addTask(spImage2Task);
	spBatch->addTask(spPointSetTask);

	//Process the batch
	std::cout << "Process mapping task batch..." << std::endl;
	spBatch->process(spRegistration);


	/***************************************************************
	 * Save or test the results
	 ***************************************************************/

	globals.spResultImage = spImageTask->getResultImage();
	globals.spResultImage2 = spImage2Task->getResultImage();
	globals.spResultLandmarks = spPointSetTask->getResultPointSet();

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