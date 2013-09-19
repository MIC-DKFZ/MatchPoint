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

#include "mapModelBasedRegistrationKernel.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapExpandingFieldKernelLoader.h"
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

		int mapExpandingFieldKernelLoaderTest(int argc, char* argv[])
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

			//////////////////////////////////////////////
			//functor for reference field
			typedef TestFieldGenerationFunctor<2, 2> FieldFunctorType;
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
			FieldFunctorType::Pointer spRefFunctor = FieldFunctorType::New(spInRep);

			typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel LazyKernelType;
			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel PreCachedKernelType;

			typedef io::ExpandingFieldKernelLoader<2, 2> LoaderType;
			typedef io::ExpandingFieldKernelLoader<2, 3> Loader23Type;

			//////////////////////////////////////////////
			//Loader and request setup
			LoaderType::Pointer spLoader = LoaderType::New();

			map::core::String testFilePath = map::structuredData::encodeForXml(
												 map::core::FileDispatch::createFullPath(refPath, "expandingFieldKernelWriterTest_ref.mhd"));

			core::String validData =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>"
				+ testFilePath +
				"</FieldPath><UseNullVector>1</UseNullVector><NullVector><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullVector></Kernel>";
			core::String validData_noNullVector =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>"
				+ testFilePath + "</FieldPath><UseNullVector>1</UseNullVector></Kernel>";
			core::String invalidData_wrongDim =
				"<Kernel InputDimensions='3' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType></Kernel>";
			core::String invalidData_wrongDim2 =
				"<Kernel InputDimensions='2' OutputDimensions='3'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType></Kernel>";
			core::String invalidData_wrongType =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>WrongKernel</KernelType></Kernel>";
			core::String invalidData_noFile =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><UseNullVector>1</UseNullVector><NullVector><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullVector></Kernel>";
			core::String invalidData_noUseNullVector =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>expandingFieldKernelWriterTest_ref.mhd</FieldPath><NullVector><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullVector></Kernel>";
			core::String invalidData_wrongNullVector =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>expandingFieldKernelWriterTest_ref.mhd</FieldPath><UseNullVector>1</UseNullVector><NullVector><Value Row='0'>-1.000000000</Value></NullVector></Kernel>";
			core::String invalidData_wrongFile =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>inexistantDummyFile.error</FieldPath><UseNullVector>1</UseNullVector><NullVector><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullVector></Kernel>";
			core::String invalidData_wrongDimFile =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>"
				+ testFilePath +
				"</FieldPath><UseNullVector>1</UseNullVector><NullVector><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullVector></Kernel>";

			structuredData::XMLStrReader::Pointer spStrReader = structuredData::XMLStrReader::New();

			LoaderType::RequestType validRequest(spStrReader->readXMLContent(validData), false);
			LoaderType::RequestType validRequest_lazy(spStrReader->readXMLContent(validData), true);
			LoaderType::RequestType validRequest_noNull(spStrReader->readXMLContent(validData_noNullVector),
					false);
			LoaderType::RequestType validRequest_noNull_lazy(spStrReader->readXMLContent(
						validData_noNullVector), true);
			LoaderType::RequestType invalidRequest_wrongDim(spStrReader->readXMLContent(invalidData_wrongDim),
					false);
			LoaderType::RequestType invalidRequest_wrongDim2(spStrReader->readXMLContent(invalidData_wrongDim2),
					false);
			LoaderType::RequestType invalidRequest_wrongType(spStrReader->readXMLContent(invalidData_wrongType),
					false);
			LoaderType::RequestType invalidRequest_noFile(spStrReader->readXMLContent(invalidData_noFile),
					false);
			LoaderType::RequestType invalidRequest_noUseNullVector(spStrReader->readXMLContent(
						invalidData_noUseNullVector), false);
			LoaderType::RequestType invalidRequest_wrongNullVector(spStrReader->readXMLContent(
						invalidData_wrongNullVector), false);
			LoaderType::RequestType invalidRequest_wrongFile(spStrReader->readXMLContent(invalidData_wrongFile),
					false);
			LoaderType::RequestType invalidRequest_wrongFile_lazy(spStrReader->readXMLContent(
						invalidData_wrongFile), true);

			////////////////////////////////////////////
			// Start Tests
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim2));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongType));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest_lazy));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest_noNull));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest_noNull_lazy));

			CHECK_EQUAL("ExpandingFieldKernelLoader<2,2>", spLoader->getProviderName());
			CHECK_EQUAL("ExpandingFieldKernelLoader<2,3>", Loader23Type::getStaticProviderName());

			//test processing of illegal requests

			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongType), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_noFile), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_noUseNullVector), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongNullVector), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongFile),
								 ::itk::ImageFileReaderException);

			//test valid request
			LoaderType::GenericKernelPointer spKernel;
			CHECK_NO_THROW(spKernel = spLoader->loadKernel(validRequest));
			LoaderType::GenericKernelPointer spKernel_lazy;
			CHECK_NO_THROW(spKernel_lazy = spLoader->loadKernel(validRequest_lazy));
			LoaderType::GenericKernelPointer spKernel_noNull;
			CHECK_NO_THROW(spKernel_noNull = spLoader->loadKernel(validRequest_noNull));
			LoaderType::GenericKernelPointer spKernel_noNull_lazy;
			CHECK_NO_THROW(spKernel_noNull_lazy = spLoader->loadKernel(validRequest_noNull_lazy));

			//test the fields
			lit::FieldTester<FieldFunctorType::FieldType> tester;
			double checkThreshold = 0.1;
			tester.setCheckThreshold(checkThreshold);
			tester.setExpectedField(spRefFunctor->generateField());

			PreCachedKernelType* pKernel = dynamic_cast<PreCachedKernelType*>(spKernel.GetPointer());
			CHECK(pKernel != NULL);
			tester.setActualField(pKernel->getField());
			CHECK_TESTER(tester);
			CHECK(*(pKernel->getLargestPossibleRepresentation()) == *spInRep);

			LazyKernelType* pKernel_lazy = dynamic_cast<LazyKernelType*>(spKernel_lazy.GetPointer());
			CHECK(pKernel_lazy != NULL);
			tester.setActualField(pKernel_lazy->getField());
			CHECK_TESTER(tester);
			CHECK(*(pKernel_lazy->getLargestPossibleRepresentation()) == *spInRep);

			pKernel = dynamic_cast<PreCachedKernelType*>(spKernel_noNull.GetPointer());
			CHECK(pKernel != NULL);
			tester.setActualField(pKernel->getField());
			CHECK_TESTER(tester);
			CHECK(*(pKernel->getLargestPossibleRepresentation()) == *spInRep);

			pKernel_lazy = dynamic_cast<LazyKernelType*>(spKernel_noNull_lazy.GetPointer());
			CHECK(pKernel_lazy != NULL);
			tester.setActualField(pKernel_lazy->getField());
			CHECK_TESTER(tester);
			CHECK(*(pKernel_lazy->getLargestPossibleRepresentation()) == *spInRep);


			//*@TODO Noch Test für: wenn man ein meta file unterschiebt, dass die falsche Dimension hat, also .mapr noch richtige dimension und dann das meta image falsch.

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
