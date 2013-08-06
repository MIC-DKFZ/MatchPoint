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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/test/mapITKPointSetRegistrationAlgorithmTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litCheckMacros.h"
#include "mapITKPointSetRegistrationAlgorithm.h"
#include "litTestCommand.h"

#include "mapITKLevenbergMarquardtOptimizer.h"
#include "mapITKEuclideanDistancePointMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapSimpleLandMarkFileReader.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			class RegTestCommand : public lit::TestCommand
			{
			public:
				/** Standard class typedefs. */
				typedef RegTestCommand   Self;
				typedef itk::SmartPointer<Self>    Pointer;

				/** Run-time type information (and related methods). */
				itkTypeMacro(RegTestCommand, TestCommand);

				/** Method for creation through the object factory. */
				itkNewMacro(Self);

			protected:
				virtual void checkEvent(const ::itk::Object *caller, const ::itk::EventObject &e)
				{
					const events::AlgorithmEvent *pChangeEvent = dynamic_cast<const events::AlgorithmEvent *>(&e);

					if (pChangeEvent)
					{
						std::cout << std::endl << pChangeEvent->GetEventName() << " (@" << caller << "): " << pChangeEvent->getComment() << std::endl;
					}
					else
					{
						std::cout << std::endl << e.GetEventName() << " (@" << caller << ")" << std::endl;
					}
				};

				RegTestCommand() {};
				virtual ~RegTestCommand() {};

			private:
				RegTestCommand(const Self &); //purposely not implemented
				void operator=(const Self &); //purposely not implemented
			};

      mapGenerateAlgorithmUIDPolicyMacro(ArbitraryITKPointSetRegistrationAlgorithmUIDPolicy, "de.dkfz.matchpoint.test", "ArbitraryITKPointSetRegistrationAlgorithm.Test", "1.0.0","");

		}

		typedef core::continuous::Elements<2>::InternalPointSetType LandmarksType;

		int mapITKPointSetRegistrationAlgorithmTest(int argc, char *argv[])
		{
			//ARGUMENTS: 1: moving land marks
			//           2: target land marks

			PREPARE_DEFAULT_TEST_REPORTING;

			std::string movingLMFileName = "";
			std::string targetLMFileName = "";

			if (argc > 1)
			{
				movingLMFileName = argv[1];
			}

			if (argc > 2)
			{
				targetLMFileName = argv[2];
			}

			//load input data
			LandmarksType::Pointer spMovingLMs = utilities::loadLandMarksFromFile<LandmarksType>(movingLMFileName);
			LandmarksType::Pointer spTargetLMs = utilities::loadLandMarksFromFile<LandmarksType>(targetLMFileName);
			LandmarksType::Pointer spMovingLMs2 = utilities::loadLandMarksFromFile<LandmarksType>(movingLMFileName);
			LandmarksType::Pointer spTargetLMs2 = utilities::loadLandMarksFromFile<LandmarksType>(targetLMFileName);

			typedef algorithm::itk::ITKPointSetRegistrationAlgorithm<LandmarksType, LandmarksType, ArbitraryITKPointSetRegistrationAlgorithmUIDPolicy> ArbitraryITKPointSetRegistrationAlgorithmType;
			ArbitraryITKPointSetRegistrationAlgorithmType::Pointer spAlgorithm = ArbitraryITKPointSetRegistrationAlgorithmType::New();

			//Add observer for algorithm events.
			RegTestCommand::Pointer spTestCommand = RegTestCommand::New();

			spAlgorithm->AddObserver(events::AlgorithmEvent(), spTestCommand);
			spAlgorithm->AddObserver(::itk::AnyEvent(), spTestCommand);

			//create registration algorithm components
			typedef algorithm::itk::ITKMetricControl< ::itk::EuclideanDistancePointMetric<LandmarksType, LandmarksType> > MetricControlType;
			typedef algorithm::itk::ITKOptimizerControl< ::itk::LevenbergMarquardtOptimizer> OptimizerControlType;
			typedef algorithm::itk::ITKTransformModel< itk::TranslationTransform<core::continuous::ScalarType, 2> > TranformModelType;

			OptimizerControlType::Pointer spOptimizer = OptimizerControlType::New();
			MetricControlType::Pointer spMetric = MetricControlType::New();
			TranformModelType::Pointer spTransformModel = TranformModelType::New();

			CHECK_EQUAL(ArbitraryITKPointSetRegistrationAlgorithmType::AlgorithmState::Pending, spAlgorithm->getCurrentState());
			CHECK_THROW_EXPLICIT(spAlgorithm->determineRegistration(), algorithm::AlgorithmException);
			CHECK_THROW_EXPLICIT(spAlgorithm->getRegistration(), algorithm::AlgorithmException);
			CHECK_EQUAL(ArbitraryITKPointSetRegistrationAlgorithmType::AlgorithmState::Pending, spAlgorithm->getCurrentState());

			//Set optimizer values
			spOptimizer->getConcreteOptimizer()->SetValueTolerance(1e-5);
			spOptimizer->getConcreteOptimizer()->SetGradientTolerance(1e-5);
			spOptimizer->getConcreteOptimizer()->SetEpsilonFunction(1e-6);
			spOptimizer->getConcreteOptimizer()->SetNumberOfIterations(100);
			spOptimizer->getConcreteOptimizer()->SetUseCostFunctionGradient(false);

			//Set all registration algorithm components
			spAlgorithm->setMetricControl(spMetric);
			spAlgorithm->setITKOptimizerControl(spOptimizer);
			spAlgorithm->setTransformModel(spTransformModel);
			CHECK_THROW_EXPLICIT(spAlgorithm->determineRegistration(), algorithm::AlgorithmException);
			CHECK_THROW_EXPLICIT(spAlgorithm->getRegistration(), algorithm::AlgorithmException);

			spAlgorithm->setMovingPointSet(spMovingLMs);
			spAlgorithm->setTargetPointSet(spTargetLMs);

			ArbitraryITKPointSetRegistrationAlgorithmType::RegistrationPointer spRegistration;
			CHECK_NO_THROW(spRegistration = spAlgorithm->getRegistration());
			CHECK_EQUAL(ArbitraryITKPointSetRegistrationAlgorithmType::AlgorithmState::Finalized, spAlgorithm->getCurrentState());

			const core::ModelBasedRegistrationKernel<2, 2> *pInverseKernel = dynamic_cast<const core::ModelBasedRegistrationKernel<2, 2>* >(&(spRegistration->getInverseMapping()));
			core::ModelBasedRegistrationKernel<2, 2>::ParametersType parameters = pInverseKernel->getParameters();

			CHECK_CLOSE(13.0, parameters[0], 0.01);
			CHECK_CLOSE(17.0, parameters[1], 0.01);

			//we don't need the output for the rest of the test
			spAlgorithm->RemoveAllObservers();

			ArbitraryITKPointSetRegistrationAlgorithmType::RegistrationPointer spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			//**************************************************
			//now check if modification (and only modification) of the components forces the
			//algorithm to redetermin the registration

			spOptimizer->Modified();
			spRegistration = spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//now there must be a new registration because optimizer was modified
			CHECK(spRegistration.GetPointer() != spRegistration2.GetPointer());

			spRegistration = spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			spMetric->Modified();
			spRegistration = spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//now there must be a new registration because metric was modified
			CHECK(spRegistration.GetPointer() != spRegistration2.GetPointer());

			spRegistration = spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			spTransformModel->Modified();
			spRegistration = spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//now there must be a new registration because interpolator was modified
			CHECK(spRegistration.GetPointer() != spRegistration2.GetPointer());

			spRegistration = spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			//**************************************************
			//now check if modification (and only modification) of the inputs forces the
			//algorithm to redetermin the registration

			spAlgorithm->setMovingPointSet(spMovingLMs2);
			spRegistration2 = spAlgorithm->getRegistration();
			//must be a new registration because the moving input was changed
			CHECK(spRegistration.GetPointer() != spRegistration2.GetPointer());

			spRegistration = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			spAlgorithm->setTargetPointSet(spTargetLMs2);
			spRegistration2 = spAlgorithm->getRegistration();
			//must be a new registration because the moving input was changed
			CHECK(spRegistration.GetPointer() != spRegistration2.GetPointer());

			spRegistration = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			//**************************************************
			//now check the observer sentinels of the algorithm

			CHECK_EQUAL(true, spOptimizer->getOptimizer()->HasObserver(::itk::AnyEvent()));
			spAlgorithm->setITKOptimizerControl(NULL);
			//now the observer set by the algorithm should be removed
			CHECK_EQUAL(false, spOptimizer->getOptimizer()->HasObserver(::itk::AnyEvent()));

			CHECK_EQUAL(true, spMetric->getMetric()->HasObserver(::itk::AnyEvent()));
			spAlgorithm->setMetricControl(NULL);
			//now the observer set by the algorithm should be removed
			CHECK_EQUAL(false, spMetric->getMetric()->HasObserver(::itk::AnyEvent()));

			CHECK_EQUAL(true, spTransformModel->getTransform()->HasObserver(::itk::AnyEvent()));
			spAlgorithm->setTransformModel(NULL);
			//now the observer set by the algorithm should be removed
			CHECK_EQUAL(false, spTransformModel->getTransform()->HasObserver(::itk::AnyEvent()));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
