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

#include "mapDemoHelper.h"

#include "mapITKImageRegistrationAlgorithm.h"
#include "mapImageMappingTask.h"
#include "mapPointSetMappingTask.h"
#include "mapMappingTaskBatch.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMeanSquaresImageToImageMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"

void onRegistrationEvent(itk::Object* pCaller, const itk::EventObject& e, void*)
{
	const map::events::AlgorithmEvent* pChangeEvent = dynamic_cast<const map::events::AlgorithmEvent*>
			(&e);

	if (pChangeEvent)
	{
		std::cout << std::endl << pChangeEvent->GetEventName() << " (@" << pCaller << "): " <<
				  pChangeEvent->getComment() << std::endl;
	}
}

void onBatchEvent(itk::Object* pCaller, const itk::EventObject& e, void*)
{
	const map::events::AnyMatchPointThreadEvent* pMAPThreadEvent =
		dynamic_cast<const map::events::AnyMatchPointThreadEvent*>(&e);

	if (pMAPThreadEvent)
	{
		std::cout << std::endl << pMAPThreadEvent->GetEventName() << " (@" << pCaller << "; Thread # " <<
				  pMAPThreadEvent->getThreadID() << "): " << pMAPThreadEvent->getComment() << std::endl;
	}
}

mapGenerateAlgorithmUIDPolicyMacro(DemoArbitraryImageRegUIDPolicy, "de.dkfz.matchpoint.demo",
								   "ArbitraryITKImageReg", "1.0.0", "");

int main(int argc, char* argv[])
{
	AppGlobals globals;

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
	 * Establish registration algorithm
	 ***************************************************************/

	std::cout << "Establish registration algorithm..." << std::endl;

	typedef map::algorithm::itk::ITKImageRegistrationAlgorithm<ImageType, ImageType, DemoArbitraryImageRegUIDPolicy>
	ArbitraryITKImageRegistrationAlgorithmType;

	ArbitraryITKImageRegistrationAlgorithmType::Pointer spAlgorithm =
		ArbitraryITKImageRegistrationAlgorithmType::New();

	typedef ArbitraryITKImageRegistrationAlgorithmType::RegistrationType RegistrationType;

	//Add observer for algorithm events.
	itk::CStyleCommand::Pointer spRegCommand = itk::CStyleCommand::New();
	spRegCommand->SetCallback(&onRegistrationEvent);

	spAlgorithm->AddObserver(map::events::AlgorithmEvent(), spRegCommand);

	//create registration algorithm components
	typedef map::algorithm::itk::ITKMetricControl< ::itk::MeanSquaresImageToImageMetric<ImageType, ImageType> >
	MetricControlType;
	typedef map::algorithm::itk::ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer>
	OptimizerControlType;
	typedef ::itk::LinearInterpolateImageFunction<ImageType, map::core::continuous::ScalarType>
	InterpolatorType;
	typedef map::algorithm::itk::ITKTransformModel< ::itk::TranslationTransform<map::core::continuous::ScalarType, 2> >
	TranformModelType;

	OptimizerControlType::Pointer spOptimizer = OptimizerControlType::New();
	MetricControlType::Pointer spMetric = MetricControlType::New();
	InterpolatorType::Pointer spInterpolator = InterpolatorType::New();
	TranformModelType::Pointer spTransformModel = TranformModelType::New();

	//Set optimizer values
	spOptimizer->getConcreteOptimizer()->SetMaximumStepLength(4.00);
	spOptimizer->getConcreteOptimizer()->SetMinimumStepLength(0.01);
	spOptimizer->getConcreteOptimizer()->SetNumberOfIterations(200);

	//Set all registration algorithm components
	spAlgorithm->setMetricControl(spMetric);
	spAlgorithm->setITKOptimizerControl(spOptimizer);
	spAlgorithm->setInterpolator(spInterpolator);
	spAlgorithm->setTransformModel(spTransformModel);

	//Set input images
	spAlgorithm->setMovingImage(globals.spMovingImage);
	spAlgorithm->setTargetImage(globals.spTargetImage);


	/***************************************************************
	 * Determine registration
	 ***************************************************************/

	std::cout << "Starting to determine the registration..." << std::endl;

	RegistrationType::Pointer spRegistration = spAlgorithm->getRegistration();

	std::cout << std::endl << "Registration determined..." << std::endl;


	/***************************************************************
	 * Map the data by tasks
	 ***************************************************************/

	//define mapping tasks
	std::cout << "Define mapping tasks..." << std::endl;

	typedef map::core::ImageMappingTask<RegistrationType, ImageType, ImageType> ImageMappingTaskType;
	typedef map::core::PointSetMappingTask<RegistrationType, LandmarksType, LandmarksType>
	PointSetMappingTaskType;

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

	spBatch->AddObserver(map::events::AnyMatchPointThreadEvent(
							 map::events::NextTaskThreadEvent::anyThreadID), spBatchCommand);

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
		return testResults(globals);
	}

	return saveResults(globals);
}