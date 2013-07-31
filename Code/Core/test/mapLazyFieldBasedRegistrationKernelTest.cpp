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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapLazyFieldBasedRegistrationKernelTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapFieldBasedRegistrationKernels.h"
#include "mapTestFieldGenerationFunctor.h"

#include "litCheckMacros.h"

#include "itkImage.h"
#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{
		typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel KernelType;
		typedef TestFieldGenerationFunctor<2, 2> FieldFunctorType;

		void generateKernel(KernelType::Pointer &spKernel, FieldFunctorType::Pointer &spFunctor)
		{
			spKernel = KernelType::New();

			FieldFunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
			FieldFunctorType::InFieldRepresentationType::PointType origin;
			origin.Fill(0);
			FieldFunctorType::InFieldRepresentationType::SizeType size;
			size.fill(10);

			FieldFunctorType::InFieldRepresentationType::Pointer spInRep = FieldFunctorType::InFieldRepresentationType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);

			spFunctor = FieldFunctorType::New(spInRep);

			spKernel->setFieldFunctor(*(spFunctor.GetPointer()));
		}

		int mapLazyFieldBasedRegistrationKernelTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			KernelType::Pointer spKernel;
			FieldFunctorType::Pointer spFunctor;
			generateKernel(spKernel, spFunctor);

			KernelType::InputPointType inPoint;
			inPoint.Fill(2);
			KernelType::OutputPointType referencePoint;
			referencePoint.Fill(10);

			KernelType::InputPointType inPoint2;
			inPoint2.Fill(3.5);
			KernelType::OutputPointType referencePoint2;
			referencePoint2.Fill(17.5);

			KernelType::InputPointType invalidInPoint;
			invalidInPoint.Fill(50);
			KernelType::OutputPointType invalidReferencePoint;
			invalidReferencePoint.Fill(0.0);

			KernelType::OutputPointType resultPoint;

			//TESTS #1
			const KernelType::FieldType *pKernelGeneratedField = spKernel->getField();
			const KernelType::FieldType *pReferenceField = spFunctor->_spCurrentFieldPointer.GetPointer();

			CHECK(NULL != pKernelGeneratedField);
			CHECK_EQUAL(pReferenceField, pKernelGeneratedField);

			/// #2
			generateKernel(spKernel, spFunctor);

			CHECK_NO_THROW(spKernel->precomputeKernel());

			CHECK_EQUAL(spFunctor->_spCurrentFieldPointer, spKernel->getField());

			/// #3
			generateKernel(spKernel, spFunctor);

			KernelType::RepresentationDescriptorConstPointer spKernelRep = spKernel->getLargestPossibleRepresentation();
			CHECK(NULL == spFunctor->_spCurrentFieldPointer.GetPointer()); //if not null, the kernel has illegally created the field
			//instead of just passing through the representation
			CHECK_EQUAL(spFunctor->getInFieldRepresentation(), spKernelRep.GetPointer());

			/// #4


			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint, resultPoint));
			CHECK_EQUAL(referencePoint, resultPoint);
			resultPoint.Fill(0);
			CHECK_EQUAL(true, spKernel->mapPoint(inPoint2, resultPoint));
			CHECK_EQUAL(referencePoint2, resultPoint);
			resultPoint.Fill(11);
			CHECK_EQUAL(false, spKernel->mapPoint(invalidInPoint, resultPoint));
			CHECK_EQUAL(invalidReferencePoint, resultPoint);

			CHECK_EQUAL(spFunctor->_spCurrentFieldPointer, spKernel->getField());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
