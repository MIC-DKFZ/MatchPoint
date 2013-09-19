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
#include "litTestImageIO.h"

#include "mapDiscreteElements.h"
#include "mapFSLRegistrationAlgorithm.h"
#include "mapAlgorithmEvents.h"


namespace map
{
	namespace testing
	{

		mapGenerateAlgorithmUIDPolicyMacro(TestFSL3DRegistrationUIDPolicy, "de.dkfz.matchpoint.test",
										   "FSL.3D.default", "1.0.0", "");

		typedef std::map<core::String, core::String> ArgumentMapType;

		ArgumentMapType getLoggedArguments()
		{
			std::ifstream logFile;
			logFile.open("flirtDummyCall.log");

			if (logFile.fail())
			{
				mapDefaultExceptionStaticMacro( << "Error cannot find or access flirtDummyCall.log");
			}

			core::String item;
			std::vector<core::String> list;

			while (std::getline(logFile, item))
			{
				list.push_back(item);
			}

			ArgumentMapType result;

			for (std::vector<core::String>::const_iterator pos = list.begin(); pos != list.end(); ++pos)
			{
				if (pos->find("-") == 0)
				{
					if (pos + 1 != list.end())
					{
						result.insert(std::make_pair(*pos, *(pos + 1)));
						++pos;
					}
					else
					{
						result.insert(std::make_pair(*pos, ""));
					}
				}
			}

			return result;
		}

		core::String extractArg(const ArgumentMapType& args, const core::String& name)
		{
			ArgumentMapType::const_iterator finding = args.find(name);

			if (finding != args.end())
			{
				return finding->second;
			}
			else
			{
				return "";
			}
		}

		void onRegistrationEvent(itk::Object* pCaller, const itk::EventObject& e, void*)
		{
			const map::events::AlgorithmEvent* pEvent = dynamic_cast<const map::events::AlgorithmEvent*>(&e);

			if (pEvent)
			{
				std::cout << std::endl << pEvent->GetEventName() << " (@" << pCaller << "): " <<
						  pEvent->getComment() << std::endl;
			}
		}

		int mapFSL3DRegistrationAlgorithmTest(int argc, char* argv[])
		{

			//ARGUMENTS: 1: moving image
			//           2: target image

			PREPARE_DEFAULT_TEST_REPORTING;

			core::String movingImageFileName = "";
			core::String targetImageFileName = "";

			if (argc > 1)
			{
				movingImageFileName = argv[1];
			}

			if (argc > 2)
			{
				targetImageFileName = argv[2];
			}

			//load input data
			typedef map::core::discrete::Elements<3>::InternalImageType ImageType;

			typedef algorithm::fsl::FSLRegistrationAlgorithm<ImageType, ImageType, TestFSL3DRegistrationUIDPolicy>
			FSL3DRegistrationAlgorithmType;

			ImageType::Pointer spMovingImage = lit::TestImageIO<unsigned char, ImageType>::readImage(
												   movingImageFileName);
			ImageType::Pointer spTargetImage = lit::TestImageIO<unsigned char, ImageType>::readImage(
												   targetImageFileName);

			FSL3DRegistrationAlgorithmType::Pointer spAlgorithm = FSL3DRegistrationAlgorithmType::New();

			//Add observer for algorithm events.
			itk::CStyleCommand::Pointer spRegCommand = itk::CStyleCommand::New();
			spRegCommand->SetCallback(&onRegistrationEvent);

			spAlgorithm->AddObserver(map::events::AlgorithmIterationEvent(), spRegCommand);

			///////////////////////////////////////////////////////
			//Test algorithm execution without images
			CHECK_THROW_EXPLICIT(spAlgorithm->determineRegistration(), algorithm::AlgorithmException);
			CHECK_THROW_EXPLICIT(spAlgorithm->getRegistration(), algorithm::AlgorithmException);

			spAlgorithm->setMovingImage(spMovingImage);
			spAlgorithm->setTargetImage(spTargetImage);

			///////////////////////////////////////////////////////
			//Test legal algorithm execution and registration result
			FSL3DRegistrationAlgorithmType::RegistrationPointer spRegistration;
			CHECK_NO_THROW(spRegistration = spAlgorithm->getRegistration());
			CHECK_EQUAL(FSL3DRegistrationAlgorithmType::AlgorithmState::Finalized,
						spAlgorithm->getCurrentState());

			const core::ModelBasedRegistrationKernel<3, 3>* pInverseKernel =
				dynamic_cast<const core::ModelBasedRegistrationKernel<3, 3>* >(&
						(spRegistration->getInverseMapping()));
			core::ModelBasedRegistrationKernel<3, 3>::ParametersType parameters =
				pInverseKernel->getParameters();

			CHECK_CLOSE(1.0574, parameters[0], 0.0001);
			CHECK_CLOSE(0.0110152, parameters[1], 0.0001);
			CHECK_CLOSE(0.120938, parameters[2], 0.0001);
			CHECK_CLOSE(-0.0184141, parameters[3], 0.0001);
			CHECK_CLOSE(0.99621, parameters[4], 0.0001);
			CHECK_CLOSE(-0.0121487, parameters[5], 0.0001);
			CHECK_CLOSE(-0.126757, parameters[6], 0.0001);
			CHECK_CLOSE(-0.0109658, parameters[7], 0.0001);
			CHECK_CLOSE(1.10909, parameters[8], 0.0001);
			CHECK_CLOSE(-53.8016, parameters[9], 0.0001);
			CHECK_CLOSE(-1.44441, parameters[10], 0.0001);
			CHECK_CLOSE(30.7287, parameters[11], 0.0001);

			///////////////////////////////////////////////////////
			//Test correct generation of command line parameter

			//check default arguments
			ArgumentMapType cmdArg = getLoggedArguments();
			CHECK(extractArg(cmdArg, "-dof") == "12");
			CHECK(extractArg(cmdArg, "-cost") == "corratio");

			// check other params
			spAlgorithm->setCostFunction(algorithm::fsl::CostFunction::LeastSquares);
			spAlgorithm->setDegreesOfFreedom(algorithm::fsl::DegreesOfFreedom::DoF6);
			CHECK_NO_THROW(spAlgorithm->determineRegistration());
			cmdArg = getLoggedArguments();
			CHECK(extractArg(cmdArg, "-dof") == "6");
			CHECK(extractArg(cmdArg, "-cost") == "leastsq");

			spAlgorithm->setCostFunction(algorithm::fsl::CostFunction::MutualInformation);
			spAlgorithm->setDegreesOfFreedom(algorithm::fsl::DegreesOfFreedom::DoF7);
			CHECK_NO_THROW(spAlgorithm->determineRegistration());
			cmdArg = getLoggedArguments();
			CHECK(extractArg(cmdArg, "-dof") == "7");
			CHECK(extractArg(cmdArg, "-cost") == "mutualinfo");

			spAlgorithm->setCostFunction(algorithm::fsl::CostFunction::NormalisedCorrelation);
			spAlgorithm->setDegreesOfFreedom(algorithm::fsl::DegreesOfFreedom::DoF9);
			CHECK_NO_THROW(spAlgorithm->determineRegistration());
			cmdArg = getLoggedArguments();
			CHECK(extractArg(cmdArg, "-dof") == "9");
			CHECK(extractArg(cmdArg, "-cost") == "normcorr");

			spAlgorithm->setCostFunction(algorithm::fsl::CostFunction::NormalisedMutualInformation);
			spAlgorithm->setDegreesOfFreedom(algorithm::fsl::DegreesOfFreedom::DoF12);
			CHECK_NO_THROW(spAlgorithm->determineRegistration());
			cmdArg = getLoggedArguments();
			CHECK(extractArg(cmdArg, "-dof") == "12");
			CHECK(extractArg(cmdArg, "-cost") == "normmi");

			///////////////////////////////////////////////////////
			//Check other public methods

			CHECK_EQUAL(false, spAlgorithm->hasCurrentOptimizerValue());
			CHECK_EQUAL(false, spAlgorithm->hasMaxIterationCount());
			CHECK_EQUAL(false, spAlgorithm->hasIterationCount());
			CHECK_EQUAL(false, spAlgorithm->isStoppable());

			core::String envFlirtPath = "";

			if (!itksys::SystemTools::GetEnv("MAPElastixPath", envFlirtPath))
			{
				itksys::SystemTools::GetEnv("FSLDIR", envFlirtPath);
			};

			core::String dir;

			CHECK(spAlgorithm->getWorkingDirectory(dir));

			CHECK_EQUAL(itksys::SystemTools::GetCurrentWorkingDirectory(), dir);

			CHECK(spAlgorithm->getFlirtDirectory(dir));

			CHECK_EQUAL(envFlirtPath, dir);

			bool delDir;

			CHECK(spAlgorithm->getDeleteTempDirectory(delDir));

			CHECK_EQUAL(true, delDir);

			spAlgorithm->setWorkingDirectory("../newWorkingDir");

			spAlgorithm->setFlirtDirectory("../newFlirtDir");

			spAlgorithm->setDeleteTempDirectory(false);

			CHECK(spAlgorithm->getWorkingDirectory(dir));

			CHECK_EQUAL("../newWorkingDir", dir);

			CHECK(spAlgorithm->getFlirtDirectory(dir));

			CHECK_EQUAL("../newFlirtDir", dir);

			CHECK(spAlgorithm->getDeleteTempDirectory(delDir));

			CHECK_EQUAL(false, delDir);

			//////////////////////////////////////////////////////////
			//Check of correct temporal image storage
			//* @TODO

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
