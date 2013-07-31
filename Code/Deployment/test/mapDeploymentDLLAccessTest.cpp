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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/test/mapDeploymentDLLAccessTest.cpp $
*/


#include "mapDeploymentDLLAccess.h"
#include "litCheckMacros.h"

#include "itksys/SystemTools.hxx"
#include "itkDynamicLoader.h"

namespace map
{
	namespace testing
	{

		//defined by mapDeploymentTests.cpp. It is tha path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char *_callingAppPath;

		int mapDeploymentDLLAccessTest(int, char *argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string dllPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			//////////////////////////////////////////////////
			// Test: openDeploymentDLL + getRegistrationAlgorithm + closeDeploymentDLL

			//Test open with wrong path pointer
			CHECK_THROW(map::deployment::openDeploymentDLL(NULL));

			//Test open non existing file
			CHECK_THROW_EXPLICIT(map::deployment::openDeploymentDLL("nonExistingFile.???"), deployment::InvalidDLLException);

			//Test open file with wrong file extension
			CHECK_THROW_EXPLICIT(map::deployment::openDeploymentDLL("nonExistingFile.???"), deployment::InvalidDLLException);


			//Test open file regular DLL
			deployment::DLLHandle::Pointer spHandle1 = NULL;

			std::string validDLLPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "mapTestAlgorithm" + itksys::DynamicLoader::LibExtension();

			CHECK_NO_THROW(spHandle1 = map::deployment::openDeploymentDLL(validDLLPath));
			//now check the returned information
			CHECK(spHandle1.IsNotNull());
			CHECK_EQUAL(validDLLPath, spHandle1->getLibraryFilePath());
			CHECK_EQUAL("de.dkfz.matchpoint", spHandle1->getAlgorithmUID().getNamespace());
			CHECK_EQUAL("TestAlgorithm", spHandle1->getAlgorithmUID().getName());
			CHECK_EQUAL("1.0.0", spHandle1->getAlgorithmUID().getVersion());

			map::algorithm::RegistrationAlgorithmBase::Pointer spInstance = NULL;
			CHECK_NO_THROW(spInstance = map::deployment::getRegistrationAlgorithm(spHandle1));
			CHECK(spInstance.IsNotNull());

			spInstance = NULL; //Enforce the destruction of the instance before the DLL is closed!

			CHECK_NO_THROW(map::deployment::closeDeploymentDLL(spHandle1));

			//Test open file invalid DLL (missing mapGetDLLInterfaceVersion symbol)
			std::string invalidDLLPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "mapTestAlgorithmInvalid1" + itksys::DynamicLoader::LibExtension();
			CHECK_THROW_EXPLICIT(map::deployment::openDeploymentDLL(invalidDLLPath), deployment::MissingSymbolException);

			//Test open file invalid DLL (missing mapGetRegistrationAlgorithmUID symbol)
			invalidDLLPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "mapTestAlgorithmInvalid2" + itksys::DynamicLoader::LibExtension();
			CHECK_THROW_EXPLICIT(map::deployment::openDeploymentDLL(invalidDLLPath), deployment::MissingSymbolException);

			//Test open file invalid DLL (missing mapGetRegistrationAlgorithmInstance symbol)
			invalidDLLPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "mapTestAlgorithmInvalid3" + itksys::DynamicLoader::LibExtension();
			CHECK_THROW_EXPLICIT(map::deployment::openDeploymentDLL(invalidDLLPath), deployment::MissingSymbolException);

			//Test open file invalid DLL (wrong version)
			invalidDLLPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "mapTestAlgorithmInvalid4" + itksys::DynamicLoader::LibExtension();
			CHECK_THROW_EXPLICIT(map::deployment::openDeploymentDLL(invalidDLLPath), deployment::InvalidInterfaceVersionException);

			//Test open file invalid DLL (invalid UID when calling mapGetRegistrationAlgorithmUID)
			invalidDLLPath = dllPath + "/" + itksys::DynamicLoader::LibPrefix() + "mapTestAlgorithmInvalid5" + itksys::DynamicLoader::LibExtension();
			CHECK_THROW_EXPLICIT(map::deployment::openDeploymentDLL(invalidDLLPath), deployment::InvalidUIDException);

			//////////////////////////////////////////////////
			// Test: getRegistrationAlgorithm errors
			CHECK_THROW(map::deployment::getRegistrationAlgorithm(NULL));


			//////////////////////////////////////////////////
			// Test: peekDeploymentDLL

			map::algorithm::UID::ConstPointer spUID;

			//Test peek with wrong path pointer
			CHECK_THROW(map::deployment::peekDeploymentDLL(NULL));

			//Test peek non existing file
			CHECK_THROW_EXPLICIT(map::deployment::peekDeploymentDLL("nonExistingFile.???"), deployment::InvalidDLLException);

			//Test peek file with wrong file extension
			CHECK_THROW_EXPLICIT(map::deployment::peekDeploymentDLL("nonExistingFile.???"), deployment::InvalidDLLException);

			//Test peek with valid DLL
			CHECK_NO_THROW(spUID = map::deployment::peekDeploymentDLL(validDLLPath));
			CHECK(spUID.IsNotNull());
			CHECK_EQUAL("de.dkfz.matchpoint", spUID->getNamespace());
			CHECK_EQUAL("TestAlgorithm", spUID->getName());
			CHECK_EQUAL("1.0.0", spUID->getVersion());

			//skipped testing other errors with peekDeploymentDLL because it just calls openDeploymentDLL and closeDeploymentDLL, which have been tested above

			//////////////////////////////////////////////////
			// Test: checkNameIsSharedLibrary
			core::String noLib = "iAmNoLib.other";
			core::String aLib = core::String("iAmALib.") + itksys::DynamicLoader::LibExtension();

			CHECK_THROW(map::deployment::checkNameIsSharedLibrary(NULL));
			CHECK(map::deployment::checkNameIsSharedLibrary(aLib.c_str()));
			CHECK(! map::deployment::checkNameIsSharedLibrary(noLib.c_str()));

			//////////////////////////////////////////////////
			// Test: checkFileNameIsMDRACompliant

			core::String validMDRA = core::String("mdra");
#if _DEBUG || (__linux__ && !defined(NDEBUG))
			validMDRA = validMDRA + "-D";
#endif

			core::OStringStream ostr;
			ostr << "-" << MAP_VERSION_MAJOR << "-" << MAP_VERSION_MINOR << "_";
			core::String versionPart = ostr.str();

			core::String invalidMDRA_DFlag = core::String("mdra-B") + versionPart + "MyInvalidDFlagAlgorithm" + itksys::DynamicLoader::LibExtension();
			core::String invalidMDRA_Version = validMDRA + "0-0_" + "MyInvalidVersionAlgorithm" + itksys::DynamicLoader::LibExtension();
			core::String invalidMDRA_Extension = validMDRA + "0-0_" + "MyInvalidExtensionAlgorithm.other";
			validMDRA = validMDRA + versionPart + "MyValidAlgorithm" + itksys::DynamicLoader::LibExtension();
			core::String validMDRA_withPath = core::String("./myPath/") + validMDRA;

			CHECK_THROW(map::deployment::checkFileNameIsMDRACompliant(NULL));
			CHECK(! map::deployment::checkFileNameIsMDRACompliant(aLib.c_str()));
			CHECK(! map::deployment::checkFileNameIsMDRACompliant(noLib.c_str()));
			CHECK(! map::deployment::checkFileNameIsMDRACompliant(invalidMDRA_DFlag.c_str()));
			CHECK(! map::deployment::checkFileNameIsMDRACompliant(invalidMDRA_Version.c_str()));
			CHECK(! map::deployment::checkFileNameIsMDRACompliant(invalidMDRA_Extension.c_str()));
			CHECK(map::deployment::checkFileNameIsMDRACompliant(validMDRA.c_str()));
			CHECK(map::deployment::checkFileNameIsMDRACompliant(validMDRA_withPath.c_str()));

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
