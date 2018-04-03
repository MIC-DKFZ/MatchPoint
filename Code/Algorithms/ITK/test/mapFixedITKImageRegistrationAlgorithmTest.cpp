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
#include "mapFixedImageToImageMetricPolicy.h"
#include "mapFixedInterpolatorPolicy.h"
#include "mapFixedSVNLOptimizerPolicy.h"
#include "mapFixedTransformPolicy.h"

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


			mapGenerateAlgorithmUIDPolicyMacro(TestAlgorithmUIDPolicy, "de.dkfz.matchpoint.test",
											   "ITKImageRegistrationAlgorithm.fixedTest", "1.0.0", "");
		}

		int mapFixedITKImageRegistrationAlgorithmTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: moving image
			//           2: target image

			PREPARE_DEFAULT_TEST_REPORTING;

			std::string movingImageFileName = "";
			std::string targetImageFileName = "";

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

			typedef algorithm::itk::ITKMetricControl< ::itk::MeanSquaresImageToImageMetric<TestImageType, TestImageType> >
			MetricControlType;
			typedef algorithm::itk::ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer>
			OptimizerControlType;
			typedef ::itk::LinearInterpolateImageFunction<TestImageType, core::continuous::ScalarType>
			InterpolatorType;
			typedef ::itk::TranslationTransform< core::continuous::ScalarType, 2> TransformType;

			typedef algorithm::itk::FixedImageToImageMetricPolicy< ::itk::MeanSquaresImageToImageMetric<TestImageType, TestImageType> >
			MetricPolicyType;
			typedef algorithm::itk::FixedSVNLOptimizerPolicy< ::itk::RegularStepGradientDescentOptimizer>
			OptimizerPolicyType;
			typedef algorithm::itk::FixedInterpolatorPolicy<InterpolatorType> InterpolatorPolicyType;
			typedef algorithm::itk::FixedTransformPolicy<TransformType> TransformPolicyType;

			typedef algorithm::itk::ITKImageRegistrationAlgorithm<TestImageType, TestImageType, TestAlgorithmUIDPolicy, InterpolatorPolicyType, MetricPolicyType, OptimizerPolicyType, TransformPolicyType>
			FixedITKImageRegistrationAlgorithmType;
			FixedITKImageRegistrationAlgorithmType::Pointer spAlgorithm =
				FixedITKImageRegistrationAlgorithmType::New();

			spAlgorithm->getConcreteITKOptimizer()->SetMaximumStepLength(4.00);
			spAlgorithm->getConcreteITKOptimizer()->SetMinimumStepLength(0.01);
			spAlgorithm->getConcreteITKOptimizer()->SetNumberOfIterations(200);
			//Voilá it's done the algorithm is ready to run.

			//Add observer for algorithm events.
			RegTestCommand::Pointer spTestCommand = RegTestCommand::New();

			spAlgorithm->AddObserver(::map::events::AlgorithmEvent(), spTestCommand);
			spAlgorithm->AddObserver(::itk::AnyEvent(), spTestCommand);

			//Test algorithm execution without images
			CHECK_THROW_EXPLICIT(spAlgorithm->determineRegistration(), algorithm::AlgorithmException);
			CHECK_THROW_EXPLICIT(spAlgorithm->getRegistration(), algorithm::AlgorithmException);

			spAlgorithm->setMovingImage(spMovingImage);
			spAlgorithm->setTargetImage(spTargetImage);

			//Test legal algorithm execution
			FixedITKImageRegistrationAlgorithmType::RegistrationPointer spRegistration;
			CHECK_NO_THROW(spRegistration = spAlgorithm->getRegistration());
			CHECK_EQUAL(FixedITKImageRegistrationAlgorithmType::AlgorithmState::Finalized,
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

			FixedITKImageRegistrationAlgorithmType::RegistrationPointer spRegistration2;
			spRegistration2 = spAlgorithm->getRegistration();
			//must be equal, because there is no reason to determin a new registration
			CHECK_EQUAL(spRegistration.GetPointer(), spRegistration2.GetPointer());

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

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
