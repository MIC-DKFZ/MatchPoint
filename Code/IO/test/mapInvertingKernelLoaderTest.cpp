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

#include "mapITKEuler2DTransform.h"
#include "mapFieldByModelFunctor.h"
#include "mapInvertingRegistrationKernel.h"
#include "mapLazyRegistrationKernel.h"
#include "mapInvertingKernelLoader.h"
#include "test/mapTestFieldGenerationFunctor.h"
#include "mapFileDispatch.h"
#include "mapSDXMLStrReader.h"
#include "mapSDXMLStrWriter.h"

#include "litCheckMacros.h"
#include "litFieldTester.h"

#include "itkImageFileReader.h"

namespace map
{
	namespace testing
	{

		int mapInvertingKernelLoaderTest(int argc, char* argv[])
		{
			//ARGUMENTS: 1: test storage path
			//           2: ref path

			PREPARE_DEFAULT_TEST_REPORTING;

			std::string testPath = "";
			std::string refPath = "";

			if (argc > 1)
			{
				testPath = argv[1];
			}

			if (argc > 2)
			{
				refPath = argv[2];
			}

			//////////////////////////////////////
			//Kernel setup
			typedef itk::Euler2DTransform< ::map::core::continuous::ScalarType> TransformType;

			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(3);
			params[0] = 1.5708;
			params[1] = 5;
			params[2] = 2;
			spTransform->SetParameters(params);

			typedef core::functors::FieldByModelFunctor<2, 2> FieldFunctorType;
			FieldFunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
			FieldFunctorType::InFieldRepresentationType::PointType origin;
			origin.Fill(0);
			FieldFunctorType::InFieldRepresentationType::SizeType size;
			size.fill(10);

			FieldFunctorType::InFieldRepresentationType::Pointer spInRep =
				FieldFunctorType::InFieldRepresentationType::New();
			spInRep->setSize(size);
			spInRep->setSpacing(spacing);
			spInRep->setOrigin(origin);
			FieldFunctorType::Pointer spFunctor = FieldFunctorType::New(spTransform, spInRep);

			typedef core::LazyRegistrationKernel<2, 2> SourceKernelType;
			SourceKernelType::Pointer spSourceKernel = SourceKernelType::New();
			spSourceKernel->setTransformFunctor(spFunctor);

			typedef core::InvertingRegistrationKernel<2, 2> InvertingKernelType;

			::map::core::InverseRegistrationKernelGenerator<2, 2>::Pointer inverter =
				::map::core::InverseRegistrationKernelGenerator<2, 2>::New();
			InvertingKernelType::Pointer spInvertingKernelRef = dynamic_cast<InvertingKernelType*>
					(inverter->generateInverse(*spSourceKernel, spInRep).GetPointer());

			typedef io::InvertingKernelLoader<2, 2> LoaderType;
			typedef io::InvertingKernelLoader<2, 3> Loader23Type;

			//////////////////////////////////////////////
			//Loader and request setup
			LoaderType::Pointer spLoader = LoaderType::New();

			::map::core::String validData =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>InvertingKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>InvertingKernel</KernelType><InverseFieldRepresentation Dimensions='2'><Size><Value Row='0'>10.00000000</Value><Value Row='1'>10.00000000</Value></Size><Origin><Value Row='0'>0.0000000000</Value><Value Row='1'>0.0000000000</Value></Origin><Spacing><Value Row='0'>0.5000000000</Value><Value Row='1'>0.5000000000</Value></Spacing><Direction><Value Column='0' Row='0'>1.000000000</Value><Value Column='1' Row='0'>0.0000000000</Value><Value Column='0' Row='1'>0.0000000000</Value><Value Column='1' Row='1'>1.000000000</Value></Direction></InverseFieldRepresentation><UseNullPoint>0</UseNullPoint></Kernel>";
			::map::core::String invalidData_wrongDim =
				"<Kernel InputDimensions='3' OutputDimensions='2'><StreamProvider>InvertingKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>InvertingKernel</KernelType><InverseFieldRepresentation Dimensions='2'><Size><Value Row='0'>10.00000000</Value><Value Row='1'>10.00000000</Value></Size><Origin><Value Row='0'>0.0000000000</Value><Value Row='1'>0.0000000000</Value></Origin><Spacing><Value Row='0'>0.5000000000</Value><Value Row='1'>0.5000000000</Value></Spacing><Direction><Value Column='0' Row='0'>1.000000000</Value><Value Column='1' Row='0'>0.0000000000</Value><Value Column='0' Row='1'>0.0000000000</Value><Value Column='1' Row='1'>1.000000000</Value></Direction></InverseFieldRepresentation><UseNullPoint>0</UseNullPoint></Kernel>";
			::map::core::String invalidData_wrongDim2 =
				"<Kernel InputDimensions='2' OutputDimensions='3'><StreamProvider>InvertingKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>InvertingKernel</KernelType><InverseFieldRepresentation Dimensions='2'><Size><Value Row='0'>10.00000000</Value><Value Row='1'>10.00000000</Value></Size><Origin><Value Row='0'>0.0000000000</Value><Value Row='1'>0.0000000000</Value></Origin><Spacing><Value Row='0'>0.5000000000</Value><Value Row='1'>0.5000000000</Value></Spacing><Direction><Value Column='0' Row='0'>1.000000000</Value><Value Column='1' Row='0'>0.0000000000</Value><Value Column='0' Row='1'>0.0000000000</Value><Value Column='1' Row='1'>1.000000000</Value></Direction></InverseFieldRepresentation><UseNullPoint>0</UseNullPoint></Kernel>";
			::map::core::String invalidData_wrongType =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>InvertingKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>WrongType</KernelType><InverseFieldRepresentation Dimensions='2'><Size><Value Row='0'>10.00000000</Value><Value Row='1'>10.00000000</Value></Size><Origin><Value Row='0'>0.0000000000</Value><Value Row='1'>0.0000000000</Value></Origin><Spacing><Value Row='0'>0.5000000000</Value><Value Row='1'>0.5000000000</Value></Spacing><Direction><Value Column='0' Row='0'>1.000000000</Value><Value Column='1' Row='0'>0.0000000000</Value><Value Column='0' Row='1'>0.0000000000</Value><Value Column='1' Row='1'>1.000000000</Value></Direction></InverseFieldRepresentation><UseNullPoint>0</UseNullPoint></Kernel>";
			::map::core::String invalidData_wrongRepDim =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>InvertingKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>InvertingKernel</KernelType><InverseFieldRepresentation Dimensions='4'><Size><Value Row='0'>10.00000000</Value><Value Row='1'>10.00000000</Value></Size><Origin><Value Row='0'>0.0000000000</Value><Value Row='1'>0.0000000000</Value></Origin><Spacing><Value Row='0'>0.5000000000</Value><Value Row='1'>0.5000000000</Value></Spacing><Direction><Value Column='0' Row='0'>1.000000000</Value><Value Column='1' Row='0'>0.0000000000</Value><Value Column='0' Row='1'>0.0000000000</Value><Value Column='1' Row='1'>1.000000000</Value></Direction></InverseFieldRepresentation><UseNullPoint>0</UseNullPoint></Kernel>";
			::map::core::String invalidData_invalidRep =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>InvertingKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>InvertingKernel</KernelType><InverseFieldRepresentation Dimensions='2'></InverseFieldRepresentation></Kernel>";

			structuredData::XMLStrReader::Pointer spStrReader = structuredData::XMLStrReader::New();

			LoaderType::RequestType validRequest(spStrReader->readXMLContent(validData), false, spSourceKernel);
			LoaderType::RequestType validRequest_lazy(spStrReader->readXMLContent(validData), true,
					spSourceKernel);
			LoaderType::RequestType invalidRequest_missingSource(spStrReader->readXMLContent(validData), true,
					NULL);
			LoaderType::RequestType invalidRequest_wrongDim(spStrReader->readXMLContent(invalidData_wrongDim),
					false);
			LoaderType::RequestType invalidRequest_wrongDim2(spStrReader->readXMLContent(invalidData_wrongDim2),
					false);
			LoaderType::RequestType invalidRequest_wrongType(spStrReader->readXMLContent(invalidData_wrongType),
					false);
			LoaderType::RequestType invalidRequest_wrongRepDim(spStrReader->readXMLContent(
						invalidData_wrongRepDim), false);
			LoaderType::RequestType invalidRequest_invalidRep(spStrReader->readXMLContent(
						invalidData_invalidRep), false);

			////////////////////////////////////////////
			// Start Tests
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_missingSource));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim2));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongType));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongRepDim));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_invalidRep));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest_lazy));

			CHECK_EQUAL("InvertingKernelLoader<2,2>", spLoader->getProviderName());
			CHECK_EQUAL("InvertingKernelLoader<2,3>", Loader23Type::getStaticProviderName());

			//test processing of illegal requests

			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_missingSource), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongType), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongRepDim), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_invalidRep), core::ServiceException);

			//test valid request
			LoaderType::GenericKernelPointer spKernel;
			CHECK_NO_THROW(spKernel = spLoader->loadKernel(validRequest));
			LoaderType::GenericKernelPointer spKernel_lazy;
			CHECK_NO_THROW(spKernel_lazy = spLoader->loadKernel(validRequest_lazy));

			//test the fields
      ::map::core::FieldDecomposer<2, 2>::FieldConstPointer extractedField;
      bool validField = ::map::core::FieldDecomposer<2, 2>::decomposeKernel(spInvertingKernelRef, extractedField);
      CHECK(validField);

			lit::FieldTester<FieldFunctorType::FieldType> tester;
			double checkThreshold = 0.1;
			tester.setCheckThreshold(checkThreshold);
      tester.setExpectedField(extractedField);

			InvertingKernelType* pKernel = dynamic_cast<InvertingKernelType*>(spKernel.GetPointer());
			CHECK(pKernel != NULL);
      validField = ::map::core::FieldDecomposer<2, 2>::decomposeKernel(pKernel, extractedField);
      CHECK(validField);
      tester.setActualField(extractedField);
			CHECK_TESTER(tester);
			CHECK(*(pKernel->getLargestPossibleRepresentation()) == *spInRep);

			InvertingKernelType* pKernel_lazy = dynamic_cast<InvertingKernelType*>(spKernel_lazy.GetPointer());
			CHECK(pKernel_lazy != NULL);
      validField = ::map::core::FieldDecomposer<2, 2>::decomposeKernel(pKernel_lazy, extractedField);
      CHECK(validField);
      tester.setActualField(extractedField);
			CHECK_TESTER(tester);
			CHECK(*(pKernel_lazy->getLargestPossibleRepresentation()) == *spInRep);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
