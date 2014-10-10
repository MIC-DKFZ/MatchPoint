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

#include "mapFieldBasedKernelInverter.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapFieldByModelFunctor.h"
#include "litCheckMacros.h"
#include "litTransformFieldTester.h"

#include "mapITKTranslationTransform.h"

namespace map
{
	namespace testing
	{

		int mapFieldBasedKernelInverterTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: Number of iterations
			//           2: Stop value
			//           3: Check threshold

			PREPARE_DEFAULT_TEST_REPORTING;

			unsigned int nrOfIterations = 40;
			double stopValue = 0.1;
			double checkThreshold = 0.1;

			if (argc > 1)
			{
				std::istringstream istream;
				istream.str(argv[1]);
				istream >> nrOfIterations;
			}

			if (argc > 2)
			{
				std::istringstream istream;
				istream.str(argv[2]);
				istream >> stopValue;
			}

			if (argc > 3)
			{
				std::istringstream istream;
				istream.str(argv[3]);
				istream >> checkThreshold;
			}

			typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel KernelType;
			typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel InverseKernelType;

			typedef core::ModelBasedRegistrationKernel<2, 2> IllegalKernelType;

			typedef algorithm::itk::ITKTransformModel< itk::TranslationTransform<core::continuous::ScalarType, 2> >
			TransformType;

			typedef core::FieldBasedKernelInverter<2, 2> InverterType;
			typedef core::FieldBasedKernelInverter<2, 3> Inverter2Type;


			// We need a field kernel, so we build a lazy one here using the FieldByModelFunctor
			typedef core::functors::FieldByModelFunctor<2, 2> ModelFunctorType;

			TransformType::Pointer spModel = TransformType::New();

			ModelFunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
			ModelFunctorType::InFieldRepresentationType::PointType origin;
			origin.Fill(0);
			ModelFunctorType::InFieldRepresentationType::SizeType size;
			size.fill(20);
			ModelFunctorType::TransformModelType::ParametersType params(2);
			params.fill(0.3);
			spModel->getTransform()->SetParameters(params);

			ModelFunctorType::InFieldRepresentationType::Pointer spInRep =
				ModelFunctorType::InFieldRepresentationType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			ModelFunctorType::Pointer spFunc = ModelFunctorType::New(*spModel, spInRep);

			TransformType::InverseTransformModelBasePointer spInverseModel;
			spModel->getInverse(spInverseModel);

			//Now we create the kernel
			KernelType::Pointer spKernel = KernelType::New();
			spKernel->setFieldFunctor(*(spFunc.GetPointer()));


			//Now we create the illegal kernel
			IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();

			//creating the inverters
			InverterType::Pointer spInverter = InverterType::New();
			Inverter2Type::Pointer spInverter2 = Inverter2Type::New();


			//TEST
			spInverter->setFunctorStopValue(stopValue);
			spInverter->setFunctorNumberOfIterations(nrOfIterations);

			CHECK_EQUAL(stopValue, spInverter->getFunctorStopValue());
			CHECK_EQUAL(nrOfIterations, spInverter->getFunctorNumberOfIterations());


			CHECK_EQUAL(false, spInverter->canHandleRequest(*(spIllegalKernel.GetPointer())));
			CHECK_EQUAL(true, spInverter->canHandleRequest(*(spKernel.GetPointer())));

			CHECK_EQUAL("FieldBasedKernelInverter<2,2>", spInverter->getProviderName());
			CHECK_EQUAL("FieldBasedKernelInverter<2,3>", spInverter2->getProviderName());

			CHECK_THROW_EXPLICIT(spInverter->invertKernel(*(spIllegalKernel.GetPointer()), NULL, NULL),
								 core::ServiceException);

			InverterType::InverseKernelBasePointer spInverseKernel;
			CHECK_THROW_EXPLICIT(spInverter->invertKernel(*(spKernel.GetPointer()), NULL, NULL),
								 core::ServiceException);
			CHECK_NO_THROW(spInverseKernel = spInverter->invertKernel(*(spKernel.GetPointer()), NULL, spInRep));

			//check correct inversion
			typedef core::InvertingFieldBasedRegistrationKernel<2, 2> FieldBasedRegistrationKernelType;
			typedef FieldBasedRegistrationKernelType::FieldType::RegionType TestRegionType;

			FieldBasedRegistrationKernelType* pInverseConcreteKernel =
				dynamic_cast<FieldBasedRegistrationKernelType*>(spInverseKernel.GetPointer());
			CHECK(pInverseConcreteKernel != NULL);
			CHECK(pInverseConcreteKernel->getSourceKernel() == spKernel.GetPointer());

			//define test region
			TestRegionType::IndexType testIndex;
			TestRegionType::SizeType testSize;
			testIndex.Fill(1);
			testSize.Fill(38);
			TestRegionType testRegion(testIndex, testSize);

			lit::TransformFieldTester<FieldBasedRegistrationKernelType::FieldType, TransformType::InverseTransformBaseType>
			tester;
			tester.setReferenceTransform(spInverseModel->getTransform());
			tester.setActualField(pInverseConcreteKernel->getField());
			tester.setTestRegion(testRegion);
			tester.setCheckThreshold(0.1);

			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
