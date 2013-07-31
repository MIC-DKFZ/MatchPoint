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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Examples/Algorithms/mapDemoITKMultiResImageRegistration.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapDemoHelper.h"

#include "mapITKMultiResImageRegistrationAlgorithm.h"
#include "mapImageMappingTask.h"
#include "mapPointSetMappingTask.h"
#include "mapMappingTaskBatch.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMattesMutualInformationImageToImageMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"

typedef map::algorithm::itk::ITKMultiResImageRegistrationAlgorithm<ImageType, ImageType> ArbitraryITKMultiResImageRegistrationAlgorithmType;

void onRegistrationEvent(itk::Object *pCaller, const itk::EventObject &e, void *)
{
	const map::events::AlgorithmEvent *pChangeEvent = dynamic_cast<const map::events::AlgorithmEvent *>(&e);

	if (pChangeEvent)
	{
		std::cout << std::endl << pChangeEvent->GetEventName() << " (@" << pCaller << "): " << pChangeEvent->getComment() << std::endl;
	}

	const map::events::AlgorithmResolutionLevelEvent *pLevelEvent = dynamic_cast<const map::events::AlgorithmResolutionLevelEvent *>(&e);

	if (pLevelEvent)
	{
		ArbitraryITKMultiResImageRegistrationAlgorithmType *pAlg = dynamic_cast<ArbitraryITKMultiResImageRegistrationAlgorithmType *>(pCaller);

		if (pAlg)
		{
			typedef map::algorithm::itk::ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer> OptimizerControlType;
			OptimizerControlType *pOptimizerControl = dynamic_cast<OptimizerControlType *>(pAlg->getOptimizerControl());

			if (pAlg->getCurrentLevel() == 0)
			{
				pOptimizerControl->getConcreteOptimizer()->SetMaximumStepLength(16.00);
				pOptimizerControl->getConcreteOptimizer()->SetMinimumStepLength(2.5);
			}
			else
			{
				pOptimizerControl->getConcreteOptimizer()->SetMaximumStepLength(pOptimizerControl->getConcreteOptimizer()->GetMaximumStepLength() / 4.0);
				pOptimizerControl->getConcreteOptimizer()->SetMinimumStepLength(pOptimizerControl->getConcreteOptimizer()->GetMinimumStepLength() / 10.0);
			}
		}
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

int main(int argc, char *argv[])
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

	ArbitraryITKMultiResImageRegistrationAlgorithmType::Pointer spAlgorithm = ArbitraryITKMultiResImageRegistrationAlgorithmType::New();

	typedef ArbitraryITKMultiResImageRegistrationAlgorithmType::RegistrationType RegistrationType;

	//Add observer for algorithm events.
	itk::CStyleCommand::Pointer spRegCommand = itk::CStyleCommand::New();
	spRegCommand->SetCallback(&onRegistrationEvent);

	spAlgorithm->AddObserver(map::events::AlgorithmEvent(), spRegCommand);

	//create registration algorithm components
	//  typedef map::algorithm::itk::ITKMetricControl< ::itk::MeanSquaresImageToImageMetric<ImageType, ImageType> > MetricControlType;
	typedef map::algorithm::itk::ITKMetricControl< ::itk::MattesMutualInformationImageToImageMetric<ImageType, ImageType> > MetricControlType;
	typedef map::algorithm::itk::ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer> OptimizerControlType;
	typedef ::itk::LinearInterpolateImageFunction<ImageType, map::core::continuous::ScalarType> InterpolatorType;
	typedef map::algorithm::itk::ITKTransformModel< ::itk::TranslationTransform<map::core::continuous::ScalarType, 2> > TranformModelType;
	typedef ::itk::MultiResolutionPyramidImageFilter<ImageType, ImageType> PyramideType;

	OptimizerControlType::Pointer spOptimizer = OptimizerControlType::New();
	MetricControlType::Pointer spMetric = MetricControlType::New();
	InterpolatorType::Pointer spInterpolator = InterpolatorType::New();
	TranformModelType::Pointer spTransformModel = TranformModelType::New();
	PyramideType::Pointer spTargetPyramide = PyramideType::New();
	PyramideType::Pointer spMovingPyramide = PyramideType::New();

	//Set optimizer values
	spOptimizer->getConcreteOptimizer()->SetMaximumStepLength(16.00);
	spOptimizer->getConcreteOptimizer()->SetMinimumStepLength(2.5);
	spOptimizer->getConcreteOptimizer()->SetNumberOfIterations(200);
	spOptimizer->getConcreteOptimizer()->SetRelaxationFactor(0.9);

	//Set optimizer values
	spMetric->getConcreteMetric()->SetNumberOfHistogramBins(128);
	spMetric->getConcreteMetric()->SetNumberOfSpatialSamples(50000);

	//Set all registration algorithm components
	spAlgorithm->setMetricControl(spMetric);
	spAlgorithm->setITKOptimizerControl(spOptimizer);
	spAlgorithm->setInterpolator(spInterpolator);
	spAlgorithm->setTransformModel(spTransformModel);
	spAlgorithm->setMovingImagePyramide(spMovingPyramide);
	spAlgorithm->setTargetImagePyramide(spTargetPyramide);

	//Set input images
	spAlgorithm->setMovingImage(globals.spMovingImage);
	spAlgorithm->setTargetImage(globals.spTargetImage);

	//Set resolutions
	spAlgorithm->setResolutionLevels(3);

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
		return testResults(globals);
	}

	return saveResults(globals);
}