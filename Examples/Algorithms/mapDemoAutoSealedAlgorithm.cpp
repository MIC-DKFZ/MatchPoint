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

/*!@file
 * @ingroup Examples
 *********************************************************
 *This example shows you the effect of the MAP_SEAL_ALGORITHM
 *in conjunction with SealFixed policy macros.
 */

//You may choose the behavior of the demo
#define MAP_SEAL_ALGORITHMS  //now all algorithm using the policy macros are sealed
//#undef MAP_SEAL_ALGORITHMS  //now the algorithm allow the access to their internals

#include "mapITKImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMeanSquaresImageToImageMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"

#include "mapFixedImageToImageMetricPolicy.h"
#include "mapFixedInterpolatorPolicy.h"
#include "mapFixedSVNLOptimizerPolicy.h"
#include "mapFixedTransformPolicy.h"

#include <stdlib.h>

typedef map::core::discrete::Elements<2>::InternalImageType ImageType;
typedef map::algorithm::RegistrationAlgorithm<2, 2> AlgorithmBaseType;
typedef map::algorithm::itk::ITKImageRegistrationAlgorithmInterface<ImageType, ImageType, map::core::continuous::ScalarType, map::core::continuous::ScalarType>
ITKRegistrationAlgorithmInterface;

/*! function used to test the accessibility of an algorithm*/
int testAccess(AlgorithmBaseType* pAlgorithm, bool accessExpected)
{
	//we just get the algorithm as a base type, now we try to get access to the internal components
	//of the algorithm by casting to the according interface...
	typedef ITKRegistrationAlgorithmInterface::OptimizerGetterInterfaceType
	OptimizerGetterInterfaceType;
	typedef ITKRegistrationAlgorithmInterface::TransformGetterInterfaceType
	TransformGetterInterfaceType;
	typedef ITKRegistrationAlgorithmInterface::InterpolatorGetterInterfaceType
	InterpolatorGetterInterfaceType;
	typedef ITKRegistrationAlgorithmInterface::MetricGetterInterfaceType MetricGetterInterfaceType;

	int result = EXIT_SUCCESS;

	//test access to the optimizer
	OptimizerGetterInterfaceType* pOGetter = dynamic_cast<OptimizerGetterInterfaceType*>(pAlgorithm);

	if (pOGetter)
	{
		std::cout << "You have access to the optimizer: " << std::endl;
		pOGetter->getITKOptimizerControl()->getOptimizer()->Print(std::cout);
		std::cout << std::endl << std::endl;

		if (!accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}
	else
	{
		std::cout << "No access to the optimizer..." << std::endl;

		if (accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}

	//test access to the transform
	TransformGetterInterfaceType* pTGetter = dynamic_cast<TransformGetterInterfaceType*>(pAlgorithm);

	if (pTGetter)
	{
		std::cout << "You have access to the transform model: " << std::endl;
        pTGetter->getTransformModel()->Print(std::cout);
        std::cout << std::endl << std::endl;

		if (!accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}
	else
	{
		std::cout << "No access to the transform model..." << std::endl;

		if (accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}

	//test access to the interpolator
	InterpolatorGetterInterfaceType* pIGetter = dynamic_cast<InterpolatorGetterInterfaceType*>
			(pAlgorithm);

	if (pIGetter)
	{
		std::cout << "You have access to the interpolator: " << std::endl;
		pIGetter->getInterpolator()->Print(std::cout);
		std::cout << std::endl << std::endl;

		if (!accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}
	else
	{
		std::cout << "No access to the interpolator..." << std::endl;

		if (accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}

	//test access to the metric
	MetricGetterInterfaceType* pMGetter = dynamic_cast<MetricGetterInterfaceType*>(pAlgorithm);

	if (pMGetter)
	{
		std::cout << "You have access to the metric: " << std::endl;
		pMGetter->getMetricControl()->getMetric()->Print(std::cout);
		std::cout << std::endl << std::endl;

		if (!accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}
	else
	{
		std::cout << "No access to the metric..." << std::endl;

		if (accessExpected)
		{
			result = EXIT_FAILURE;
		}
	}

	return result;
}

mapGenerateAlgorithmUIDPolicyMacro(DemoAutoSealedRegistrationAlgorithmUIDPolicy,
								   "de.dkfz.matchpoint.test", "DemoAutoSealedRegistrationAlgorithm", "1.0.0", "");

int main(int argc, char* argv[])
{
	/***************************************************************
	 * Establish registration algorithm
	 ***************************************************************/

	std::cout << "Establish registration algorithm with auto seal policy macros..." << std::endl;

	//Ensure that MAP_SEAL_ALGORITHMS is not defined. Therefor all "SealedFixed" policy macros
	//will be fixed policies
	//Define MAP_SEAL_ALGORITHMS. Therefor all "SealedFixed" policy macros
	//will be sealed policies. Mark that the typedef code is the same
	//the define changes the whole behaviour. Now the algorithm is realy a
	//black box

	typedef ::itk::MeanSquaresImageToImageMetric<ImageType, ImageType> MetricType;
	typedef ::itk::RegularStepGradientDescentOptimizer OptimizerType;
	typedef ::itk::LinearInterpolateImageFunction<ImageType, map::core::continuous::ScalarType>
	InterpolatorType;
	typedef ::itk::TranslationTransform<map::core::continuous::ScalarType, 2> TranformType;

	typedef SealedFixedImageToImageMetricPolicyMacro<MetricType> MetricPolicyType;
	typedef SealedFixedSVNLOptimizerPolicyMacro<OptimizerType> OptimizerPolicyType;
	typedef SealedFixedInterpolatorPolicyMacro<InterpolatorType> InterpolatorPolicyType;
	typedef SealedFixedTransformPolicyMacro<TranformType> TransformPolicyType;

	typedef map::algorithm::itk::ITKImageRegistrationAlgorithm < ImageType, ImageType,
			DemoAutoSealedRegistrationAlgorithmUIDPolicy,
			InterpolatorPolicyType,
			MetricPolicyType,
			OptimizerPolicyType,
			TransformPolicyType > ITKImageRegistrationAlgorithmType;

	AlgorithmBaseType::Pointer spAlgorithm = ITKImageRegistrationAlgorithmType::New().GetPointer();

	/***************************************************************
	 * Check the accessibility of the algorithm instances
	 ***************************************************************/

	int result = EXIT_FAILURE;

#ifdef MAP_SEAL_ALGORITHMS
	std::cout << "Check algorithm (created with MAP_SEAL_ALGORITHMS defined)..." << std::endl <<
			  std::endl;
	std::cout << "This algorithm should NOT be accessible..." << std::endl << std::endl;

	result = testAccess(spAlgorithm, false);

#else
	std::cout << "Check the accessibility..." << std::endl;
	std::cout << "Check algorithm (created without MAP_SEAL_ALGORITHMS defined)..." << std::endl;
	std::cout << "This algorithm should be accessible..." << std::endl << std::endl;

	result = testAccess(spAlgorithm, true);
#endif

	std::cout <<
			  "Algorithm are identical on the algorithmical level (s.a. demoFixedITKImageRegistration)." <<
			  std::endl;
	std::cout <<
			  "but they differ in the accessibility they offer to their internals, depending on MAP_SEAL_ALGORITHMS."
			  << std::endl;

	return result;
}
