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

#include "mapPreCachedRegistrationKernel.h"
#include "litCheckMacros.h"
#include "itkImage.h"
#include "itkImageRegionIterator.h"
#include "itkTranslationTransform.h"

#include "mapArtifactGenerator.h"

namespace map
{
	namespace testing
	{
		typedef core::PreCachedRegistrationKernel<2, 2> KernelType;
    typedef ::map::core::discrete::Elements<2>::VectorFieldType FieldType;

		int mapPreCachedRegistrationKernelTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

      //generat kernel with a field transform
      KernelType::Pointer spEmptyKernel = KernelType::New();

      KernelType::Pointer spFieldKernel = KernelType::New();

      KernelType::RepresentationDescriptorPointer spReferenceFieldRepresentation = testing::createSimpleDescriptor<2>(10, 0.5);
      ::itk::GenericVectorFieldTransform< ::map::core::continuous::ScalarType, 2, 2>::Pointer refFieldTransform = testing::wrapFieldInTransform<2>(testing::generate2DSumField(spReferenceFieldRepresentation)).GetPointer();
      spFieldKernel->setTransformModel(refFieldTransform);

      //generate kernel with model transform
      typedef itk::TranslationTransform< ::map::core::continuous::ScalarType, 2> TransformType;
      TransformType::Pointer spTransform = TransformType::New();
      TransformType::ParametersType params(2);
      params[0] = 5;
      params[1] = -5;
      spTransform->SetParameters(params);

      KernelType::Pointer spTransformKernel = KernelType::New();
      spTransformKernel->setTransformModel(spTransform);


			KernelType::InputPointType inPoint;
			inPoint.Fill(2);
			KernelType::OutputPointType referencePoint_field;
      referencePoint_field.Fill(10);
      KernelType::OutputPointType referencePoint_transform = spTransform->TransformPoint(inPoint);

			KernelType::InputPointType inPoint2;
			inPoint2.Fill(3.5);
      KernelType::OutputPointType referencePoint2_field;
      referencePoint2_field.Fill(17.5);
      KernelType::OutputPointType referencePoint2_transform = spTransform->TransformPoint(inPoint2);

			KernelType::InputPointType invalidInPoint;
			invalidInPoint.Fill(50);
      KernelType::OutputPointType invalidReferencePoint_field;
      invalidReferencePoint_field.Fill(0.0);

			KernelType::OutputPointType resultPoint;

      KernelType::OutputPointType nullPointRef;
      nullPointRef.Fill(99999);
      KernelType::OutputPointType defaultNullPoint(
          ::itk::NumericTraits< KernelType::MappingVectorType::ValueType >::NonpositiveMin());

      //////////////////////////////////////////////////
      //check kernel with field
      CHECK_EQUAL(refFieldTransform.GetPointer(), spFieldKernel->getTransformModel());
      CHECK_EQUAL(true, spFieldKernel->hasLimitedRepresentation());
      CHECK_EQUAL(true, spFieldKernel->transformExists());

			KernelType::RepresentationDescriptorConstPointer spFieldRepresentation =
          spFieldKernel->getLargestPossibleRepresentation();
			CHECK(*(spReferenceFieldRepresentation.GetPointer()) == *(spFieldRepresentation.GetPointer()));
      CHECK_EQUAL(refFieldTransform->GetNameOfClass(), spFieldKernel->getModelName());

      CHECK_EQUAL(false, spFieldKernel->usesNullPoint());
      CHECK_EQUAL(defaultNullPoint, spFieldKernel->getNullPoint());
      refFieldTransform->UseNullPointOn();
      refFieldTransform->SetNullPoint(nullPointRef);
      CHECK_EQUAL(true, spFieldKernel->usesNullPoint());
      CHECK_EQUAL(nullPointRef, spFieldKernel->getNullPoint());

      resultPoint.Fill(0);
      CHECK_EQUAL(true, spFieldKernel->mapPoint(inPoint, resultPoint));
      CHECK_EQUAL(referencePoint_field, resultPoint);
			resultPoint.Fill(0);
      CHECK_EQUAL(true, spFieldKernel->mapPoint(inPoint2, resultPoint));
      CHECK_EQUAL(referencePoint2_field, resultPoint);
			resultPoint.Fill(11);
      CHECK_EQUAL(false, spFieldKernel->mapPoint(invalidInPoint, resultPoint));
      CHECK_EQUAL(invalidReferencePoint_field, resultPoint);

      //////////////////////////////////////////////////
      //check kernel with transfrom
      CHECK_EQUAL(false, spTransformKernel->hasLimitedRepresentation());
      CHECK_EQUAL(true, spTransformKernel->getLargestPossibleRepresentation().IsNull());
      CHECK_EQUAL(spTransform.GetPointer(), spTransformKernel->getTransformModel());
      CHECK_EQUAL(spTransform->GetNameOfClass(), spTransformKernel->getModelName());
      CHECK_EQUAL(true, spTransformKernel->transformExists());

      //reset result
      resultPoint.Fill(0);
      CHECK_EQUAL(true, spTransformKernel->mapPoint(inPoint, resultPoint));
      CHECK_EQUAL(referencePoint_transform, resultPoint);
      resultPoint.Fill(0);
      CHECK_EQUAL(true, spTransformKernel->mapPoint(inPoint2, resultPoint));
      CHECK_EQUAL(referencePoint2_transform, resultPoint);

      //////////////////////////////////////////////////
      //check invalid empty kernel
      CHECK_EQUAL(false, spEmptyKernel->transformExists());
      CHECK_THROW_EXPLICIT(spEmptyKernel->hasLimitedRepresentation(), map::core::ExceptionObject);
      CHECK_THROW_EXPLICIT(spEmptyKernel->getLargestPossibleRepresentation(), map::core::ExceptionObject);
      CHECK(spEmptyKernel->getTransformModel() == NULL);
      CHECK_EQUAL("Unkown", spEmptyKernel->getModelName().c_str());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
