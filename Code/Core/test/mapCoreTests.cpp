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

// this file defines the mapCoreTests for the test driver
// and all it expects is that you have a function called RegisterTests
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapExceptionObject.h"

#include "litMultiTestsMain.h"

namespace map
{
	namespace testing
	{
		void registerTests()
		{
			LIT_REGISTER_TEST(mapLogbookTest);
			LIT_REGISTER_TEST(mapExceptionObjectMacrosTest);
			LIT_REGISTER_TEST(mapPMVolumeTest);
			LIT_REGISTER_TEST(mapVolumeSizeTest);
			LIT_REGISTER_TEST(mapFileDispatchTest);
			LIT_REGISTER_TEST(mapFieldRepresentationDescriptorTest);
			LIT_REGISTER_TEST(mapRegistrationBaseTest);
			LIT_REGISTER_TEST(mapRegistrationTest);
			LIT_REGISTER_TEST(mapAffineMatrixDecomposerTest);
			LIT_REGISTER_TEST(mapPreCachedRegistrationKernelTest);
			LIT_REGISTER_TEST(mapServiceStackTest);
			LIT_REGISTER_TEST(mapGenericStaticLoadPolicyTest);
			LIT_REGISTER_TEST(mapStaticServiceStackTest);
			LIT_REGISTER_TEST(mapFieldGenerationFunctorTest);
			LIT_REGISTER_TEST(mapLazyRegistrationKernelTest);
			LIT_REGISTER_TEST(mapFieldByModelFunctorTest);
			LIT_REGISTER_TEST(mapFieldByModelInversionFunctorTest);
			LIT_REGISTER_TEST(mapFieldByFieldInversionFunctorTest);
			LIT_REGISTER_TEST(mapPointVectorCombinationPolicyTest);
			LIT_REGISTER_TEST(mapCombinationFunctorInterfaceTest);
			LIT_REGISTER_TEST(mapFieldByFileLoadFunctorTest);
      LIT_REGISTER_TEST(mapGenericFieldGeneratingCombinationFunctorTest);
      LIT_REGISTER_TEST(mapGenericKernelCombiningFieldSourceTest);
      LIT_REGISTER_TEST(mapCombinedRegistrationKernelTest);
			LIT_REGISTER_TEST(mapRegistrationKernelTest);
			LIT_REGISTER_TEST(mapDefaultKernelInverterTest);
			LIT_REGISTER_TEST(mapInverseRegistrationKernelGeneratorTest);
			LIT_REGISTER_TEST(mapInvertingRegistrationKernelTest);
			LIT_REGISTER_TEST(mapRegistrationCombinationRequestTest);
			LIT_REGISTER_TEST(mapRegistrationKernelCombinatorBaseTest);
			LIT_REGISTER_TEST(mapLazyFieldKernelCombinatorTest);
			LIT_REGISTER_TEST(mapPreCachedKernelCombinatorTest);
			LIT_REGISTER_TEST(mapRegistrationCombinatorTest);
			LIT_REGISTER_TEST(mapImageMappingPerformerRequestTest);
			LIT_REGISTER_TEST(mapPointSetMappingPerformerRequestTest);
			LIT_REGISTER_TEST(mapPointSetByModelPerformerTest);
			LIT_REGISTER_TEST(mapImageByModelPerformerTest);
			LIT_REGISTER_TEST(mapMappingTaskBaseTest);
			LIT_REGISTER_TEST(mapPointSetMappingTaskTest);
			LIT_REGISTER_TEST(mapImageMappingTaskTest);
			LIT_REGISTER_TEST(mapMappingTaskBatchTest);
			LIT_REGISTER_TEST(mapSmartMetaPropertyTest);
			LIT_REGISTER_TEST(mapMetaPropertyTest);
			LIT_REGISTER_TEST(mapMetaPropertyAccessInterfaceTest);
			LIT_REGISTER_TEST(mapMetaPropertyAccessorTest);
			LIT_REGISTER_TEST(mapSDElementTest);
			LIT_REGISTER_TEST(mapSDXMLStrReaderTest);
			LIT_REGISTER_TEST(mapSDXMLStrWriterTest);
			LIT_REGISTER_TEST(mapSDXMLFileReaderTest);
			LIT_REGISTER_TEST(mapSDXMLFileWriterTest);
			LIT_REGISTER_TEST(mapModificationTimeValidatorTest);
		}
	}
}

int main(int argc, char* argv[])
{
	int result = 0;

	map::testing::registerTests();

	try
	{
		result = lit::multiTestsMain(argc, argv);
	}
	catch (const map::core::ExceptionObject& e)
	{
		std::cerr << "MatchPoint test driver caught an MatchPoint exception:\n";
		e.Print(std::cerr);
		std::cerr << "\n";
		result = -1;
	}
	catch (const itk::ExceptionObject& e)
	{
		std::cerr << "MatchPoint test driver caught an ITK exception:\n";
		std::cerr << e.GetFile() << ":" << e.GetLine() << ":\n"
				  << e.GetDescription() << "\n";
		result = -1;
	}
	catch (const std::exception& e)
	{
		std::cerr << "MatchPoint test driver caught an exception:\n";
		std::cerr << e.what() << "\n";
		result = -1;
	}
	catch (...)
	{
		std::cerr << "MatchPoint test driver caught an unknown exception!!!\n";
		result = -1;
	}

	return result;
}
