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
#include "litTestCommand.h"

#include "mapITKLandmarkKernelRegistrationAlgorithm.h"
#include "mapSimpleLandMarkFileReader.h"
#include "mapITKVolumeSplineKernelTransform.h"

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

			mapGenerateAlgorithmUIDPolicyMacro(ITKLandmarkKernelRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "ITKLandmarkKernelRegistrationAlgorithm.test", "1.0.0", "");
		}

		typedef core::continuous::Elements<3>::InternalPointSetType LandmarksType;

		int mapITKLandmarkKernelRegistrationAlgorithmTest(int argc, char* argv[])
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
			LandmarksType::Pointer spMovingLMs = utilities::loadLandMarksFromFile<LandmarksType>
												 (movingLMFileName);
			LandmarksType::Pointer spTargetLMs = utilities::loadLandMarksFromFile<LandmarksType>
												 (targetLMFileName);
			LandmarksType::Pointer spMovingLMs2 = utilities::loadLandMarksFromFile<LandmarksType>
												  (movingLMFileName);
			LandmarksType::Pointer spTargetLMs2 = utilities::loadLandMarksFromFile<LandmarksType>
												  (targetLMFileName);


			typedef algorithm::itk::ITKLandmarkKernelRegistrationAlgorithm<LandmarksType, ::itk::VolumeSplineKernelTransform<core::continuous::ScalarType, 3>, ITKLandmarkKernelRegistrationAlgorithmUIDPolicy>
			RegistrationAlgorithmType;

			RegistrationAlgorithmType::Pointer spAlgorithm = RegistrationAlgorithmType::New();

			//Add observer for algorithm events.
			RegTestCommand::Pointer spTestCommand = RegTestCommand::New();

			spAlgorithm->AddObserver(events::AlgorithmEvent(), spTestCommand);
			spAlgorithm->AddObserver(::itk::AnyEvent(), spTestCommand);

			//Set land marks
			spAlgorithm->setMovingPointSet(spMovingLMs);
			spAlgorithm->setTargetPointSet(spTargetLMs);

			RegistrationAlgorithmType::RegistrationPointer spRegistration;

			CHECK_NO_THROW(spRegistration = spAlgorithm->getRegistration());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
