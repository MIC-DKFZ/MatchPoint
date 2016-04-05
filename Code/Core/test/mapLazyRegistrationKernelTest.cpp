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

#include "mapLazyRegistrationKernel.h"
#include "mapTestFieldGenerationFunctor.h"

#include "litCheckMacros.h"

#include "itkImage.h"
#include "itkImageRegionIterator.h"

namespace map
{
	namespace testing
	{
    typedef core::LazyRegistrationKernel<2, 2> KernelType;
		typedef TestFieldGenerationFunctor<2, 2> FieldFunctorType;

    void generateKernel(KernelType::Pointer& spKernel, FieldFunctorType::Pointer& spFunctor)
		{
			spKernel = KernelType::New();

      KernelType::RepresentationDescriptorPointer spInRep = testing::createSimpleDescriptor<2>(10, 0.5);

			spFunctor = FieldFunctorType::New(spInRep);

			spKernel->setTransformFunctor(spFunctor.GetPointer());
		}

		int mapLazyRegistrationKernelTest(int, char* [])
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

      KernelType::MappingVectorType nullVectorRef;
      nullVectorRef.Fill(99);
      KernelType::MappingVectorType defaultNullVector(
          ::itk::NumericTraits< KernelType::MappingVectorType::ValueType >::NonpositiveMin());

			//TESTS basic api /behavior of uninitialized kernel
      KernelType::Pointer emptyKernel = KernelType::New();

      CHECK_EQUAL(false, emptyKernel->transformExists());
      CHECK_EQUAL(false, emptyKernel->hasLimitedRepresentation());
      CHECK_EQUAL(true, emptyKernel->getLargestPossibleRepresentation().IsNull());
      CHECK_EQUAL("Unkown", emptyKernel->getModelName().c_str());

      CHECK(NULL == emptyKernel->getTransformFunctor());
      CHECK_NO_THROW(emptyKernel->setTransformFunctor(spFunctor));
      CHECK_EQUAL(spFunctor.GetPointer(), emptyKernel->getTransformFunctor());

      CHECK_EQUAL(false, emptyKernel->usesNullVector());
      CHECK_NO_THROW(emptyKernel->setNullVectorUsage(true));
      CHECK_EQUAL(true, emptyKernel->usesNullVector());

      CHECK_EQUAL(defaultNullVector, emptyKernel->getNullVector());
      CHECK_NO_THROW(emptyKernel->setNullVector(nullVectorRef));
      CHECK_EQUAL(nullVectorRef, emptyKernel->getNullVector());

      /// configured kernel
      const KernelType::TransformType* pKernelGeneratedField = spKernel->getTransformModel();
      const KernelType::TransformType* pReferenceField = spFunctor->_spCurrentTransform.GetPointer();

			CHECK(NULL != pKernelGeneratedField);
			CHECK_EQUAL(pReferenceField, pKernelGeneratedField);

			/// #2
			generateKernel(spKernel, spFunctor);
      CHECK_EQUAL(false, spKernel->transformExists());
      CHECK(spFunctor->_spCurrentTransform.IsNull()); //triggered by precompute
      CHECK_NO_THROW(spKernel->precomputeKernel());
      CHECK(spFunctor->_spCurrentTransform.IsNotNull()); //triggered by precompute
      CHECK_EQUAL(spFunctor->_spCurrentTransform, spKernel->getTransformModel());
      CHECK_EQUAL(true, spKernel->transformExists());

			/// #3
			generateKernel(spKernel, spFunctor);

			KernelType::RepresentationDescriptorConstPointer spKernelRep =
				spKernel->getLargestPossibleRepresentation();
			CHECK(NULL ==
          spFunctor->_spCurrentTransform.GetPointer()); //if not null, the kernel has illegally created the field
			//instead of just passing through the representation
			CHECK_EQUAL(spFunctor->getInFieldRepresentation(), spKernelRep.GetPointer());
      CHECK_EQUAL(false, spKernel->transformExists());

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
      CHECK_EQUAL(true, spKernel->transformExists());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
