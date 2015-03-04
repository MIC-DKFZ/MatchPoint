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

#include "mapModelBasedKernelInverter.h"
#include "mapFieldBasedKernelInverter.h"
#include "mapModelBasedRegistrationKernel.h"
#include "litCheckMacros.h"
#include "mapITKTranslationTransform.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapTestKernelBase.h"

namespace map
{
	namespace testing
	{


		int mapInverseRegistrationKernelGeneratorTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			// create the generator
			typedef core::InverseRegistrationKernelGenerator<2, 2> GeneratorType;
			GeneratorType::Pointer spGenerator = GeneratorType::New();

			// check whether the LoadPolicy worked
			typedef GeneratorType::InverterStackType InverterStackType;
			CHECK(NULL != InverterStackType::getProvider(
					  core::ModelBasedKernelInverter<2, 2>::getStaticProviderName()));
			CHECK(NULL != InverterStackType::getProvider(
					  core::FieldBasedKernelInverter<2, 2>::getStaticProviderName()));

			// create a ModelBasedKernel we can invert
			typedef core::ModelBasedRegistrationKernel<2, 2> KernelType;
			KernelType::Pointer spKernel = KernelType::New();

			typedef itk::TranslationTransform<core::continuous::ScalarType, 2> TransformType;
			TransformType::Pointer spTransform = TransformType::New();

			TransformType::ParametersType params(2);
			params[0] = 5;
			params[1] = 5;
			spTransform->SetParameters(params);
			spKernel->setTransformModel(spTransform);

			// let the generator invert the kernel

			typedef GeneratorType::InverseKernelBaseType InverseKernelType;
			typedef GeneratorType::InverseKernelBasePointer InverseKernelPointer;
			InverseKernelPointer spInverseKernel;

			CHECK_NO_THROW(spInverseKernel = spGenerator->generateInverse(*(spKernel.GetPointer()), NULL));
			CHECK(spInverseKernel.IsNotNull());

			// We did not check for correctness of the inversion because this is the job of the corresponding kernel inverter test.
			// We just check if the call chain has worked properly.


			// We also have to check if the generator throws an exception if he can't invert something we give to him
			TestKernelBase<2, 2>::Pointer spIllegalKernel = TestKernelBase<2, 2>::New();
			CHECK_THROW_EXPLICIT(spGenerator->generateInverse(*(spIllegalKernel.GetPointer()), NULL),
								 core::MissingProviderException);


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
