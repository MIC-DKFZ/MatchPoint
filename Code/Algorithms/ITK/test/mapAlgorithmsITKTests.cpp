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

#include "mapExceptionObject.h"
#include "litMultiTestsMain.h"

namespace map
{
	namespace testing
	{

		void registerTests()
		{
			LIT_REGISTER_TEST(mapITKOptimizerControlInterfaceTest);
			LIT_REGISTER_TEST(mapITKOptimizerControlTest);
			LIT_REGISTER_TEST(mapFixedSVNLOptimizerPolicyTest);
			LIT_REGISTER_TEST(mapArbitrarySVNLOptimizerPolicyTest);
			LIT_REGISTER_TEST(mapFixedInterpolatorPolicyTest);
			LIT_REGISTER_TEST(mapArbitraryInterpolatorPolicyTest);
			LIT_REGISTER_TEST(mapFixedImageToImageMetricPolicyTest);
			LIT_REGISTER_TEST(mapArbitraryImageToImageMetricPolicyTest);
			LIT_REGISTER_TEST(mapFixedTransformPolicyTest);
			LIT_REGISTER_TEST(mapArbitraryTransformPolicyTest);
			LIT_REGISTER_TEST(mapArbitraryMVNLOptimizerPolicyTest);
			LIT_REGISTER_TEST(mapFixedMVNLOptimizerPolicyTest);
			LIT_REGISTER_TEST(mapArbitraryPointSetToPointSetMetricPolicyTest);
			LIT_REGISTER_TEST(mapFixedPointSetToPointSetMetricPolicyTest);
			LIT_REGISTER_TEST(mapITKImageRegistrationAlgorithmTest);
			LIT_REGISTER_TEST(mapFixedITKImageRegistrationAlgorithmTest);
			LIT_REGISTER_TEST(mapITKAffineTransformTest);
			LIT_REGISTER_TEST(mapITKCenteredRigid2DTransformTest);
			LIT_REGISTER_TEST(mapITKPointSetRegistrationAlgorithmTest);
			LIT_REGISTER_TEST(mapITKRigid2DICPRegistrationAlgorithmTemplateTest);
			LIT_REGISTER_TEST(mapITKEuler3DICPRegistrationAlgorithmTemplateTest);
			LIT_REGISTER_TEST(mapITKRigid2DClosedFormRegistrationAlgorithmTemplateTest);
			LIT_REGISTER_TEST(mapITKRigid3DClosedFormRegistrationAlgorithmTemplateTest);
			LIT_REGISTER_TEST(mapITKLandmarkKernelRegistrationAlgorithmTest);
      LIT_REGISTER_TEST(mapITKEuler3DMattesMIRegistrationAlgorithmTemplateTest);
		}

	} //namespace testing
} //namespace map

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
