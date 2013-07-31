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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Examples/Algorithms/mapDemoFixedITKImageRegistration.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapDemoHelper.h"

#include "mapITKImageRegistrationAlgorithm.h"
#include "mapImageMappingTask.h"
#include "mapPointSetMappingTask.h"
#include "mapMappingTaskBatch.h"

#include "mapITKUnaryTransformModel.h"
#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMeanSquaresImageToImageMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"

#include "mapFixedImageToImageMetricPolicy.h"
#include "mapFixedInterpolatorPolicy.h"
#include "mapFixedSVNLOptimizerPolicy.h"
#include "mapFixedTransformPolicy.h"

void onRegistrationEvent(itk::Object *pCaller, const itk::EventObject &e, void *)
{
	const map::events::AlgorithmEvent *pChangeEvent = dynamic_cast<const map::events::AlgorithmEvent *>(&e);

	if (pChangeEvent)
	{
		std::cout << std::endl << pChangeEvent->GetEventName() << " (@" << pCaller << "): " << pChangeEvent->getComment() << std::endl;
	}
}

void onBatchEvent(itk::Object *pCaller, const itk::EventObject &e, void *)
{
	const map::events::AnyMatchPointThreadEvent *pMAPThreadEvent = dynamic_cast<const map::events::AnyMatchPointThreadEvent *>(&e);

	if (pMAPThreadEvent)
	{
		std::cout << std::endl << pMAPThreadEvent->GetEventName() << " (@" << pCaller << "; Thread # " << pMAPThreadEvent->getThreadID() << "): " << pMAPThreadEvent->getComment() << std::endl;
	}
}

mapGenerateAlgorithmUIDPolicyMacro(DemoFixedRegistrationAlgorithmUIDPolicy, "de.dkfz.matchpoint.test", "DemoFixedITKImageRegistrationAlgorithm", "1.0.0");

int main(int argc, char *argv[])
{
	AppGlobals globals;
	int result = EXIT_FAILURE;

	//parse command line arguments
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

	typedef ::itk::MeanSquaresImageToImageMetric<ImageType, ImageType> MetricType;
	typedef ::itk::RegularStepGradientDescentOptimizer OptimizerType;
	typedef ::itk::LinearInterpolateImageFunction<ImageType, map::core::continuous::ScalarType> InterpolatorType;
	typedef ::itk::TranslationTransform<map::core::continuous::ScalarType, 2> TransformType;

	typedef map::algorithm::itk::FixedImageToImageMetricPolicy<MetricType> MetricPolicyType;
	typedef map::algorithm::itk::FixedSVNLOptimizerPolicy<OptimizerType> OptimizerPolicyType;
	typedef map::algorithm::itk::FixedInterpolatorPolicy<InterpolatorType> InterpolatorPolicyType;
	typedef map::algorithm::itk::FixedTransformPolicy<TransformType> TransformPolicyType;

	typedef map::algorithm::itk::ITKImageRegistrationAlgorithm < ImageType, ImageType,
	        DemoFixedRegistrationAlgorithmUIDPolicy,
	        InterpolatorPolicyType,
	        MetricPolicyType,
	        OptimizerPolicyType,
	        TransformPolicyType > FixedITKImageRegistrationAlgorithmType;

	FixedITKImageRegistrationAlgorithmType::Pointer spAlgorithm = FixedITKImageRegistrationAlgorithmType::New();

	typedef FixedITKImageRegistrationAlgorithmType::RegistrationType RegistrationType;

	//Add observer for algorithm events.
	itk::CStyleCommand::Pointer spRegCommand = itk::CStyleCommand::New();
	spRegCommand->SetCallback(&onRegistrationEvent);

	spAlgorithm->AddObserver(map::events::AlgorithmEvent(), spRegCommand);

	//Set input images
	spAlgorithm->setMovingImage(globals.spMovingImage);
	spAlgorithm->setTargetImage(globals.spTargetImage);

	//Set optimizer values
	spAlgorithm->getConcreteITKOptimizer()->SetMaximumStepLength(4.00);
	spAlgorithm->getConcreteITKOptimizer()->SetMinimumStepLength(0.01);
	spAlgorithm->getConcreteITKOptimizer()->SetNumberOfIterations(200);

	/***************************************************************
	 * Determine registration
	 ***************************************************************/

	std::cout << "Starting to determine the registration..." << std::endl;

	RegistrationType::Pointer spRegistration = spAlgorithm->getRegistration();

	std::cout << std::endl << "Registration determined..." << std::endl;


	/***************************************************************
	 * Map the data by tasks
	 ***************************************************************/

	//define registration tasks
	std::cout << "Define mapping tasks..." << std::endl;

	typedef map::core::ImageMappingTask<RegistrationType, ImageType, ImageType> ImageMappingTaskType;
	typedef map::core::PointSetMappingTask<RegistrationType, LandmarksType, LandmarksType> PointSetMappingTaskType;

	ImageMappingTaskType::Pointer spImageTask = ImageMappingTaskType::New();
	spImageTask->setInputImage(globals.spMovingImage);

	ImageMappingTaskType::Pointer spImage2Task = ImageMappingTaskType::New();
	spImage2Task->setInputImage(globals.spMovingImage2);

	PointSetMappingTaskType::Pointer spPointSetTask = PointSetMappingTaskType::New();
	spPointSetTask->setInputPointSet(globals.spMovingLandmarks);

	std::cout << "Setup mapping task batch..." << std::endl;
	typedef map::core::MappingTaskBatch<RegistrationType> MappingTaskBatchType;
	MappingTaskBatchType::Pointer spBatch = MappingTaskBatchType::New();

	//Set observer
	itk::CStyleCommand::Pointer spBatchCommand = itk::CStyleCommand::New();
	spBatchCommand->SetCallback(&onBatchEvent);

	spBatch->AddObserver(map::events::AnyMatchPointThreadEvent(map::events::NextTaskThreadEvent::anyThreadID), spBatchCommand);

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