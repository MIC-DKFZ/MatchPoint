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

#include "itksys/SystemTools.hxx"

#include "litCheckMacros.h"
#include "litTestImageIO.h"
#include "litTransformFieldTester.h"
#include "litImageTester.h"

#include "mapDiscreteElements.h"
#include "mapPlmParameterFileRegistrationAlgorithm.h"
#include "mapITKTranslationTransform.h"

namespace map
{
    namespace testing
    {

        mapGenerateAlgorithmUIDPolicyMacro(TestPlm3DRegistrationUIDPolicy,
            "de.dkfz.matchpoint.plastimatch.test", "ProgramFileRegistration.3D.default", "1.0.0", "");

        typedef std::vector<::map::core::String> ArgumentsType;

        ArgumentsType getLoggedArguments(const core::String& logFilePath)
        {
            std::ifstream logFile;
            logFile.open(logFilePath.c_str());

            if (logFile.fail())
            {
                mapDefaultExceptionStaticMacro(<< "Error cannot find or access plastimatchDummyCall.log");
            }

            ::map::core::String item;
            ArgumentsType list;

            while (std::getline(logFile, item))
            {
                list.push_back(item);
            }

            return list;
        }

        ::map::core::String getLoggedTempDir(const ArgumentsType& loggedArguments)
        {
            //the temp dir should be deduced by the 3rd line (plastimatch configuration file)

            if (loggedArguments.size() < 3)
            {
                mapDefaultExceptionStaticMacro(<<
                    "Error. PlastimatchDummyCall.log seems to be invalid, line with configuration file is missing.");
            }

            ::map::core::String dir = loggedArguments[2];
            dir = core::FileDispatch::getPath(dir);

            return dir;
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

        typedef itk::TranslationTransform<map::core::continuous::ScalarType, 3> TransformModelType;

        TransformModelType::Pointer generateInverseReferenceTransformModel()
        {
            TransformModelType::Pointer spModel = TransformModelType::New();
            TransformModelType::ParametersType params(3);
            params[0] = 10.0;
            params[1] = -16.0;
            params[2] = -5.0;
            spModel->SetParameters(params);
            return spModel;
        }

        TransformModelType::InverseTransformBaseType::Pointer generateDirectReferenceTransformModel()
        {
            TransformModelType::Pointer spModel = generateInverseReferenceTransformModel();
            TransformModelType::InverseTransformBaseType::Pointer spInvModel;
            spInvModel = spModel->GetInverseTransform();
            return spInvModel;
        }

        int mapPlmParameterFileRegistrationAlgorithmTest(int argc, char* argv[])
        {

            //ARGUMENTS: 1: moving image
            //           2: target image
            //           3: parameter file

            PREPARE_DEFAULT_TEST_REPORTING;

            ::map::core::String movingImageFileName = "";
            ::map::core::String targetImageFileName = "";
            ::map::core::String paramFileName = "";

            if (argc > 1)
            {
                movingImageFileName = argv[1];
            }

            if (argc > 2)
            {
                targetImageFileName = argv[2];
            }

            if (argc > 3)
            {
                paramFileName = argv[3];
            }

            //load input data
            typedef map::core::discrete::Elements<3>::InternalImageType ImageType;

            typedef algorithm::plastimatch::ParameterFileRegistrationAlgorithm < ImageType, ImageType, TestPlm3DRegistrationUIDPolicy >
                Plm3DRegistrationAlgorithmType;

            ImageType::Pointer spMovingImage = lit::TestImageIO<unsigned char, ImageType>::readImage(
                movingImageFileName);
            ImageType::Pointer spTargetImage = lit::TestImageIO<unsigned char, ImageType>::readImage(
                targetImageFileName);

            Plm3DRegistrationAlgorithmType::Pointer spAlgorithm = Plm3DRegistrationAlgorithmType::New();

            //Add observer for algorithm events.
            itk::CStyleCommand::Pointer spRegCommand = itk::CStyleCommand::New();
            spRegCommand->SetCallback(&onRegistrationEvent);

            spAlgorithm->AddObserver(map::events::AlgorithmIterationEvent(), spRegCommand);

            ///////////////////////////////////////////////////////
            //Test algorithm execution without images
            CHECK_THROW_EXPLICIT(spAlgorithm->determineRegistration(), algorithm::AlgorithmException);
            CHECK_THROW_EXPLICIT(spAlgorithm->getRegistration(), algorithm::AlgorithmException);

            ::map::core::String testString;
            CHECK(spAlgorithm->getParameterFilePath(testString));
            CHECK_EQUAL("", testString);
            bool delDir;
            CHECK(spAlgorithm->getDeleteTempDirectory(delDir));
            CHECK_EQUAL(true, delDir);
            CHECK(spAlgorithm->getMovingImage().IsNull());
            CHECK(spAlgorithm->getTargetImage().IsNull());

            spAlgorithm->setMovingImage(spMovingImage);
            spAlgorithm->setTargetImage(spTargetImage);
            spAlgorithm->setParameterFilePath(paramFileName);

            ///////////////////////////////////////////////////////
            //Test legal algorithm execution and registration result
            Plm3DRegistrationAlgorithmType::RegistrationPointer spRegistration;
            CHECK_NO_THROW(spRegistration = spAlgorithm->getRegistration());
            CHECK_EQUAL(Plm3DRegistrationAlgorithmType::AlgorithmState::Finalized,
                spAlgorithm->getCurrentState());

            // test result
            typedef lit::TransformFieldTester < map::core::discrete::Elements<3>::VectorFieldType, TransformModelType >
                TesterType;
            TesterType tester;
            typedef map::core::RegistrationKernel<3, 3> KernelBaseType;
            const KernelBaseType* pKernel = dynamic_cast<const KernelBaseType*>(&
                (spRegistration->getInverseMapping()));
            CHECK(pKernel != NULL);

            tester.setReferenceTransform(generateInverseReferenceTransformModel());
            tester.setActualField(testing::unwra pKernel->getTransformModel());
            tester.setCheckThreshold(0.01);
            CHECK_TESTER(tester);

            ///////////////////////////////////////////////////////
            //Test the correct implementation of DeleteTempDirectory.

            //DeleteTempDirectory is true (see above) -> temp dir must be deleted after algorithm execution
            CHECK(spAlgorithm->getDeleteTempDirectory(delDir));
            CHECK_EQUAL(true, delDir);
            CHECK_NO_THROW(spAlgorithm->determineRegistration());
            ArgumentsType cmdArg = getLoggedArguments("plastimatchDummyCall.log");
            ::map::core::String tempDir = getLoggedTempDir(cmdArg);

            CHECK(!(itksys::SystemTools::FileExists(tempDir.c_str(), false)));

            //DeleteTempDirectory is false -> temp dir must still exists after algorithm execution
            spAlgorithm->setDeleteTempDirectory(false);
            CHECK(spAlgorithm->getDeleteTempDirectory(delDir));
            CHECK_EQUAL(false, delDir);
            CHECK_NO_THROW(spAlgorithm->determineRegistration());
            cmdArg = getLoggedArguments("plastimatchDummyCall.log");
            tempDir = getLoggedTempDir(cmdArg);

            CHECK(itksys::SystemTools::FileExists(tempDir.c_str(), false));

            ///////////////////////////////////////////////////////
            //Test the correct temp storage of target and moving image
            //use date of the last run (where the temp dir was not deleted).

            ImageType::Pointer spStoredMovingImage =
                lit::TestImageIO<::map::core::discrete::InternalPixelType, ImageType>::readImage(
                ::map::core::FileDispatch::createFullPath(tempDir, "moving.mhd"));
            ImageType::Pointer spStoredTargetImage =
                lit::TestImageIO<::map::core::discrete::InternalPixelType, ImageType>::readImage(
                ::map::core::FileDispatch::createFullPath(tempDir, "target.mhd"));

            lit::ImageTester<ImageType, ImageType> imageTester;

            imageTester.setExpectedImage(spMovingImage);
            imageTester.setActualImage(spStoredMovingImage);
            CHECK_TESTER(imageTester);

            imageTester.setExpectedImage(spTargetImage);
            imageTester.setActualImage(spStoredTargetImage);
            CHECK_TESTER(imageTester);

            itksys::SystemTools::RemoveADirectory(tempDir.c_str());

            ///////////////////////////////////////////////////////
            //Check other public methods

            CHECK_EQUAL(false, spAlgorithm->hasCurrentOptimizerValue());
            CHECK_EQUAL(false, spAlgorithm->hasMaxIterationCount());
            CHECK_EQUAL(false, spAlgorithm->hasIterationCount());
            CHECK_EQUAL(false, spAlgorithm->isStoppable());

            ::map::core::String envPlastimatchPath = "";
            itksys::SystemTools::GetEnv("MAPPlastimatchPath", envPlastimatchPath);

            ::map::core::String dir;
            CHECK(spAlgorithm->getWorkingDirectory(dir));
            CHECK_EQUAL(itksys::SystemTools::GetCurrentWorkingDirectory(), dir);
            CHECK(spAlgorithm->getPlastimatchDirectory(dir));
            CHECK_EQUAL(envPlastimatchPath, dir);

            spAlgorithm->setWorkingDirectory("../newWorkingDir");
            spAlgorithm->setPlastimatchDirectory("../newPlastimatchDir");
            CHECK(spAlgorithm->getWorkingDirectory(dir));
            CHECK_EQUAL("../newWorkingDir", dir);
            CHECK(spAlgorithm->getPlastimatchDirectory(dir));
            CHECK_EQUAL("../newPlastimatchDir", dir);

            //////////////////////////////////////////////////////////
            //Check of correct temporal mask storage
            //* @TODO Check of correct temporal mask storage

            RETURN_AND_REPORT_TEST_SUCCESS;
        }
    } //namespace testing
} //namespace map
