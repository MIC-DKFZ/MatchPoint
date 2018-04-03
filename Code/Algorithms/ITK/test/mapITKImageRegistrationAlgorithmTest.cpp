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

#include "litCheckMacros.h"
#include "mapITKImageRegistrationAlgorithm.h"
#include "litTestCommand.h"
#include "litTestImageIO.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMeanSquaresImageToImageMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"


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
				virtual void checkEvent(const ::itk::Object* caller, const ::itk::EventObject& e)
				{
					const events::AlgorithmEvent* pChangeEvent = dynamic_cast<const events::AlgorithmEvent*>(&e);

					if (pChangeEvent)
					{
						std::cout << std::endl << pChangeEvent->GetEventName() << " (@" << caller << "): " <<
								  pChangeEvent->getComment() << std::endl;
					}
					else
					{
						std::cout << std::endl << e.GetEventName() << " (@" << caller << ")" << std::endl;
					}
				};

				RegTestCommand() {};
				virtual ~RegTestCommand() {};

			private:
				RegTestCommand(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

			mapGenerateAlgorithmUIDPolicyMacro(ArbitraryITKImageRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "ArbitraryITKImageRegistrationAlgorithmTest", "1.0.0", "");
		}

		int mapITKImageRegistrationAlgorithmTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: moving image
			//           2: target image

			PREPARE_DEFAULT_TEST_REPORTING;

			map::core::String movingImageFileName = "";
			map::core::String targetImageFileName = "";

			if (argc > 1)
			{
				movingImageFileName = argv[1];
			}

			if (argc > 2)
			{
				targetImageFileName = argv[2];
			}

			//load input data
			typedef core::discrete::Elements<2>::InternalImageType TestImageType;

			TestImageType::Pointer spMovingImage =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					movingImageFileName);
			TestImageType::Pointer spTargetImage =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					targetImageFileName);
			TestImageType::Pointer spMovingImage2 =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					movingImageFileName);
			TestImageType::Pointer spTargetImage2 =
				lit::TestImageIO<unsigned char, core::discrete::Elements<2>::InternalImageType>::readImage(
					targetImageFileName);

			typedef algorithm::itk::ITKImageRegistrationAlgorithm<TestImageType, TestImageType, ArbitraryITKImageRegistrationAlgorithmUIDPolicy>
			ArbitraryITKImageRegistrationAlgorithmType;
			ArbitraryITKImageRegistrationAlgorithmType::Pointer spAlgorithm =
				ArbitraryITKImageRegistrationAlgorithmType::New();

			//Add observer for algorithm events.
			RegTestCommand::Pointer spTestCommand = RegTestCommand::New();

			spAlgorithm->AddObserver(::map::events::AlgorithmEvent(), spTestCommand);
			spAlgorithm->AddObserver(::itk::AnyEvent(), spTestCommand);

			//create registration algorithm components
			typedef algorithm::itk::ITKMetricControl< ::itk::MeanSquaresImageToImageMetric<TestImageType, TestImageType> >
			MetricControlType;
			typedef algorithm::itk::ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer>
			OptimizerControlType;
			typedef ::itk::LinearInterpolateImageFunction<TestImageType, core::continuous::ScalarType>
			InterpolatorType;
			typedef ::itk::TranslationTransform< ::map::core::continuous::ScalarType, 2> TranformModelType;

			OptimizerControlType::Pointer spOptimizer = OptimizerControlType::New();
			MetricControlType::Pointer spMetric = MetricControlType::New();
			InterpolatorType::Pointer spInterpolator = InterpolatorType::New();
			TranformModelType::Pointer spTransformModel = TranformModelType::New();

			CHECK_EQUAL(ArbitraryITKImageRegistrationAlgorithmType::AlgorithmState::Pending,
						spAlgorithm->getCurrentState());
			CHECK_THROW_EXPLICIT(spAlgorithm->determineRegistration(), algorithm::AlgorithmException);
			CHECK_THROW_EXPLICIT(spAlgorithm->getRegistration(), algorithm::AlgorithmException);
			CHECK_EQUAL(ArbitraryITKImageRegistrationAlgorithmType::AlgorithmState::Pending,
						spAlgorithm->getCurrentState());

			//Set optimizer values
			spOptimizer->getConcreteOptimizer()->SetMaximumStepLength(4.00);
			spOptimizer->getConcreteOptimizer()->SetMinimumStepLength(0.01);
			spOptimizer->getConcreteOptimizer()->SetNumberOfIterations(200);

			//Set all registration algorithm components
			spAlgorithm->setMetricControl(spMetric);
			spAlgorithm->setITKOptimizerControl(spOptimizer);
			spAlgorithm->setInterpolator(spInterpolator);
			spAlgorithm->setTransformModel(spTransformModel);
			CHECK_THROW_EXPLICIT(spAlgorithm->determineRegistration(), algorithm::AlgorithmException);
			CHECK_THROW_EXPLICIT(spAlgorithm->getRegistration(), algorithm::AlgorithmException);

			spAlgorithm->setMovingImage(spMovingImage);
			spAlgorithm->setTargetImage(spTargetImage);

			ArbitraryITKImageRegistrationAlgorithmType::RegistrationPointer spRegistration;
			CHECK_NO_THROW(spRegistration = spAlgorithm->getRegistration());
			CHECK_EQUAL(ArbitraryITKImageRegistrationAlgorithmType::AlgorithmState::Finalized,
						spAlgorithm->getCurrentState());

			const core::RegistrationKernel<2, 2>* pInverseKernel =
          dynamic_cast<const core::RegistrationKernel<2, 2>* >(&
						(spRegistration->getInverseMapping()));
      ::map::core::RegistrationKernel<2, 2>::TransformType::ParametersType parameters =
				pInverseKernel->getTransformModel()->GetParameters();

			CHECK_CLOSE(13.0, parameters[0], 0.01);
			CHECK_CLOSE(17.0, parameters[1], 0.01);

			//we don't need the output for the rest of the test
			spAlgorithm->RemoveAllObservers();

			ArbitraryITKImageRegistrationAlgorithmType::RegistrationPointer spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			//**************************************************
			//now check the current optimizer value API part
			CHECK_EQUAL(true, spAlgorithm->hasCurrentOptimizerValue());

			ArbitraryITKImageRegistrationAlgorithmType::OptimizerMeasureType measure;

			CHECK_NO_THROW(measure = spAlgorithm->getCurrentOptimizerValue());

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

			spInterpolator->Modified();
			spRegistration = spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//now there must be a new registration because interpolator was modified
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

			spAlgorithm->setMovingImage(spMovingImage2);
			spRegistration2 = spAlgorithm->getRegistration();
			//must be a new registration because the moving input was changed
			CHECK(spRegistration.GetPointer() != spRegistration2.GetPointer());

			spRegistration = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			spAlgorithm->setTargetImage(spTargetImage2);
			spRegistration2 = spAlgorithm->getRegistration();
			//must be a new registration because the moving input was changed
			CHECK(spRegistration.GetPointer() != spRegistration2.GetPointer());

			spRegistration = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

			//**************************************************
			//now check the observer sentinels of the algorithm

			CHECK_EQUAL(true, spInterpolator->HasObserver(::itk::AnyEvent()));
			spAlgorithm->setInterpolator(NULL);
			//now the observer set by the algorithm should be removed
			CHECK_EQUAL(false, spInterpolator->HasObserver(::itk::AnyEvent()));

			CHECK_EQUAL(true, spOptimizer->getOptimizer()->HasObserver(::itk::AnyEvent()));
			spAlgorithm->setITKOptimizerControl(NULL);
			//now the observer set by the algorithm should be removed
			CHECK_EQUAL(false, spOptimizer->getOptimizer()->HasObserver(::itk::AnyEvent()));

			CHECK_EQUAL(true, spMetric->getMetric()->HasObserver(::itk::AnyEvent()));
			spAlgorithm->setMetricControl(NULL);
			//now the observer set by the algorithm should be removed
			CHECK_EQUAL(false, spMetric->getMetric()->HasObserver(::itk::AnyEvent()));

			CHECK_EQUAL(true, spTransformModel->HasObserver(::itk::AnyEvent()));
			spAlgorithm->setTransformModel(NULL);
			//now the observer set by the algorithm should be removed
			CHECK_EQUAL(false, spTransformModel->HasObserver(::itk::AnyEvent()));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
