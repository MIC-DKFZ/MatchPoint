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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapRegistrationCombinatorTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litCheckMacros.h"
#include "mapTestKernelBase.h"
#include "mapRegistrationCombinator.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapCombinedFieldBasedRegistrationKernel.h"
#include "mapRegistrationManipulator.h"
#include "mapFieldCombinationFunctorInterface.h"

namespace map
{
	namespace testing
	{


		typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel KernelType;


		KernelType::Pointer generateKernel()
		{
			KernelType::Pointer spKernel = KernelType::New();

			// create field
			KernelType::FieldType::Pointer spField = KernelType::FieldType::New();

			typedef itk::ImageRegionIterator< KernelType::FieldType > IteratorType;

			KernelType::FieldType::RegionType::SizeType size = {10, 10};
			KernelType::FieldType::RegionType region(size);
			KernelType::FieldType::SpacingType spacing(0.5);
			//Generate imagegrid
			spField->SetRegions(region);
			spField->SetSpacing(spacing);
			spField->Allocate();

			IteratorType iterator(spField, spField->GetLargestPossibleRegion());

			for (iterator.GoToBegin(); !(iterator.IsAtEnd()); ++iterator)
			{
				KernelType::FieldType::IndexType index = iterator.GetIndex();
				KernelType::FieldType::ValueType value;
				value.Fill(index[0] + index[1]);

				iterator.Set(value);
			}

			// creating field done, set field to kernel.
			spKernel->setField(*(spField.GetPointer()));

			return spKernel;
		}


		bool fieldExists(const core::RegistrationKernelBase<2, 2> &kernel)
		{
			typedef core::CombinedFieldBasedRegistrationKernel<2, 2, 2> CombinedKernelType;

			const CombinedKernelType *pCombinedKernel = dynamic_cast<const CombinedKernelType *>(&kernel);
			return pCombinedKernel->fieldExists();
		}

		bool isKernelCorrectlyComposed(const core::RegistrationKernelBase<2, 2> &kernelToCheck,
		                               const core::RegistrationKernelBase<2, 2> &kernel1,
		                               const core::RegistrationKernelBase<2, 2> &kernel2)
		{
			typedef core::CombinedFieldBasedRegistrationKernel<2, 2, 2> CombinedKernelType;

			const CombinedKernelType *pCombinedKernel = dynamic_cast<const CombinedKernelType *>(&kernelToCheck);

			bool result = false;

			if (pCombinedKernel)
			{
				typedef core::functors::FieldCombinationFunctorInterface<2, 2, 2> FunctorInterfaceType;
				const FunctorInterfaceType *pFunctor = dynamic_cast<const FunctorInterfaceType *>(pCombinedKernel->getFieldFunctor());

				if (pFunctor)
				{
					result = true;

					if (pFunctor->get1stSourceKernelBase() != &kernel1)
					{
						result = false;
					}

					if (pFunctor->get2ndSourceKernelBase() != &kernel2)
					{
						result = false;
					}
				}
			}

			return result;
		}



		int mapRegistrationCombinatorTest(int argc, char *argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::RegistrationCombinator< core::Registration<2, 2>, core::Registration<2, 2> > CombinatorType;
			typedef CombinatorType::PreRegistrationType PreRegistrationType;
			typedef CombinatorType::RegistrationType RegistrationType;


			typedef TestKernelBase<2, 2> IllegalKernelType;

			// create the registrations
			PreRegistrationType::Pointer spValidPreRegistration = PreRegistrationType::New();
			core::RegistrationManipulator<PreRegistrationType> manipulator(spValidPreRegistration.GetPointer());
			manipulator.setDirectMapping(generateKernel());
			manipulator.setInverseMapping(generateKernel());

			RegistrationType::Pointer spValidRegistration = RegistrationType::New();
			core::RegistrationManipulator<RegistrationType> manipulator2(spValidRegistration.GetPointer());
			manipulator2.setDirectMapping(generateKernel());
			manipulator2.setInverseMapping(generateKernel());


			PreRegistrationType::Pointer spInvalidDirectKernelPreRegistration = PreRegistrationType::New();
			core::RegistrationManipulator<PreRegistrationType> manipulator3(spInvalidDirectKernelPreRegistration.GetPointer());
			manipulator3.setDirectMapping(IllegalKernelType::New());
			manipulator3.setInverseMapping(generateKernel());

			PreRegistrationType::Pointer spInvalidInverseKernelPreRegistration = PreRegistrationType::New();
			core::RegistrationManipulator<PreRegistrationType> manipulator4(spInvalidInverseKernelPreRegistration.GetPointer());
			manipulator4.setDirectMapping(generateKernel());
			manipulator4.setInverseMapping(IllegalKernelType::New());


			RegistrationType::Pointer spInvalidDirectKernelRegistration = RegistrationType::New();
			core::RegistrationManipulator<RegistrationType> manipulator5(spInvalidDirectKernelRegistration.GetPointer());
			manipulator5.setDirectMapping(IllegalKernelType::New());
			manipulator5.setInverseMapping(generateKernel());

			RegistrationType::Pointer spInvalidInverseKernelRegistration = RegistrationType::New();
			core::RegistrationManipulator<RegistrationType> manipulator6(spInvalidInverseKernelRegistration.GetPointer());
			manipulator6.setDirectMapping(generateKernel());
			manipulator6.setInverseMapping(IllegalKernelType::New());


			// create the RegistrationCombinator
			CombinatorType::Pointer spCombinator = CombinatorType::New();

			// test the getters and setters


			CHECK_EQUAL(false, spCombinator->getUseDirectPadding());
			CHECK_NO_THROW(spCombinator->setUseDirectPadding(true));
			CHECK_EQUAL(true, spCombinator->getUseDirectPadding());

			CHECK_EQUAL(false, spCombinator->getUseInversePadding());
			CHECK_NO_THROW(spCombinator->setUseInversePadding(true));
			CHECK_EQUAL(true, spCombinator->getUseInversePadding());


			CombinatorType::DirectMappingVectorType emptyVector(0.0);
			CombinatorType::DirectMappingVectorType filledVector1(1.1);
			CombinatorType::DirectMappingVectorType filledVector2(2.2);

			CHECK_EQUAL(emptyVector, spCombinator->getDirectPaddingVector());
			CHECK_NO_THROW(spCombinator->setDirectPaddingVector(filledVector1));
			CHECK_EQUAL(filledVector1, spCombinator->getDirectPaddingVector());

			CHECK_EQUAL(emptyVector, spCombinator->getInversePaddingVector());
			CHECK_NO_THROW(spCombinator->setInversePaddingVector(filledVector2));
			CHECK_EQUAL(filledVector2, spCombinator->getInversePaddingVector());


			// test process()
			// our result should be a registration<2,2>
			CombinatorType::CombinedRegistrationPointer spResult;

			// both kernels must not be initialized
			CHECK_NO_THROW(spResult = spCombinator->process(*(spValidPreRegistration.GetPointer()), *(spValidRegistration.GetPointer()), CombinatorType::InitialisationStyle::None));
			CHECK(spResult.IsNotNull());
			CHECK(!fieldExists(spResult->getDirectMapping()));
			CHECK(!fieldExists(spResult->getInverseMapping()));

			// both kernels must not be initialized
			CHECK_NO_THROW(spResult = spCombinator->process(*(spValidPreRegistration.GetPointer()), *(spValidRegistration.GetPointer()), CombinatorType::InitialisationStyle::DirectMapping));
			CHECK(spResult.IsNotNull());
			CHECK(fieldExists(spResult->getDirectMapping()));
			CHECK(!fieldExists(spResult->getInverseMapping()));

			// both kernels must not be initialized
			CHECK_NO_THROW(spResult = spCombinator->process(*(spValidPreRegistration.GetPointer()), *(spValidRegistration.GetPointer()), CombinatorType::InitialisationStyle::InverseMapping));
			CHECK(spResult.IsNotNull());
			CHECK(!fieldExists(spResult->getDirectMapping()));
			CHECK(fieldExists(spResult->getInverseMapping()));

			// both kernels must not be initialized
			CHECK_NO_THROW(spResult = spCombinator->process(*(spValidPreRegistration.GetPointer()), *(spValidRegistration.GetPointer()), CombinatorType::InitialisationStyle::CompleteRegistration));
			CHECK(spResult.IsNotNull());
			CHECK(fieldExists(spResult->getDirectMapping()));
			CHECK(fieldExists(spResult->getInverseMapping()));

			// check if the kernels are at the right position:
			CHECK(isKernelCorrectlyComposed(spResult->getDirectMapping(), spValidPreRegistration->getDirectMapping(), spValidRegistration->getDirectMapping()));
			CHECK(isKernelCorrectlyComposed(spResult->getInverseMapping(), spValidRegistration->getInverseMapping(), spValidPreRegistration->getInverseMapping()));

			// test for exceptions: call process() with a registration that has a kernel
			// for which there is no appropriate combinator on the combinator stack
			CHECK_THROW_EXPLICIT(spCombinator->process(*(spInvalidDirectKernelPreRegistration.GetPointer()), *(spValidRegistration.GetPointer())), core::MissingProviderException);
			CHECK_THROW_EXPLICIT(spCombinator->process(*(spInvalidInverseKernelPreRegistration.GetPointer()), *(spValidRegistration.GetPointer())), core::MissingProviderException);
			CHECK_THROW_EXPLICIT(spCombinator->process(*(spValidPreRegistration.GetPointer()), *(spInvalidDirectKernelRegistration.GetPointer())), core::MissingProviderException);
			CHECK_THROW_EXPLICIT(spCombinator->process(*(spValidPreRegistration.GetPointer()), *(spInvalidInverseKernelRegistration.GetPointer())), core::MissingProviderException);
			CHECK_THROW_EXPLICIT(spCombinator->process(*(spInvalidDirectKernelPreRegistration.GetPointer()), *(spInvalidInverseKernelRegistration.GetPointer())), core::MissingProviderException);


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
