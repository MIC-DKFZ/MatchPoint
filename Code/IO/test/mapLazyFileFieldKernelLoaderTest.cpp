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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/test/mapLazyFileFieldKernelLoaderTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapLazyRegistrationKernel.h"
#include "mapLazyFileFieldKernelLoader.h"
#include "test/mapTestFieldGenerationFunctor.h"
#include "mapFileDispatch.h"
#include "mapSDXMLStrReader.h"
#include "mapSDXMLStrWriter.h"
#include "mapFieldDecomposer.h"

#include "litCheckMacros.h"
#include "litFieldTester.h"

#include "itkImageFileReader.h"

namespace map
{
	namespace testing
	{

		int mapLazyFileFieldKernelLoaderTest(int argc, char* argv[])
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

			typedef core::LazyRegistrationKernel<2, 2> LazyKernelType;

			typedef io::LazyFileFieldKernelLoader<2, 2> LoaderType;
			typedef io::LazyFileFieldKernelLoader<2, 3> Loader23Type;

			//////////////////////////////////////////////
			//Loader and request setup
			LoaderType::Pointer spLoader = LoaderType::New();

			map::core::String testFilePath = map::structuredData::encodeForXml(
												 map::core::FileDispatch::createFullPath(refPath, "expandingFieldKernelWriterTest_ref.nrrd"));

			::map::core::String validData =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>"
				+ testFilePath +
				"</FieldPath><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";
			::map::core::String validData_noNullPoint =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>"
				+ testFilePath + "</FieldPath><UseNullPoint>1</UseNullPoint></Kernel>";
			::map::core::String invalidData_wrongDim =
				"<Kernel InputDimensions='3' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType></Kernel>";
			::map::core::String invalidData_wrongDim2 =
				"<Kernel InputDimensions='2' OutputDimensions='3'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType></Kernel>";
			::map::core::String invalidData_wrongType =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>WrongKernel</KernelType></Kernel>";
			::map::core::String invalidData_noFile =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";
			::map::core::String invalidData_noUseNullPoint =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>expandingFieldKernelWriterTest_ref.mhd</FieldPath><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";
			::map::core::String invalidData_wrongNullPoint =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>expandingFieldKernelWriterTest_ref.mhd</FieldPath><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value></NullPoint></Kernel>";
			::map::core::String invalidData_wrongFile =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>inexistantDummyFile.error</FieldPath><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";
			::map::core::String invalidData_wrongDimFile =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>"
				+ testFilePath +
				"</FieldPath><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";

			structuredData::XMLStrReader::Pointer spStrReader = structuredData::XMLStrReader::New();

			LoaderType::RequestType validRequest(spStrReader->readXMLContent(validData), false);
			LoaderType::RequestType validRequest_lazy(spStrReader->readXMLContent(validData), true);
			LoaderType::RequestType validRequest_noNull(spStrReader->readXMLContent(validData_noNullPoint),
					false);
			LoaderType::RequestType validRequest_noNull_lazy(spStrReader->readXMLContent(
						validData_noNullPoint), true);
			LoaderType::RequestType invalidRequest_wrongDim(spStrReader->readXMLContent(invalidData_wrongDim),
					false);
			LoaderType::RequestType invalidRequest_wrongDim2(spStrReader->readXMLContent(invalidData_wrongDim2),
					false);
			LoaderType::RequestType invalidRequest_wrongType(spStrReader->readXMLContent(invalidData_wrongType),
					false);
			LoaderType::RequestType invalidRequest_noFile(spStrReader->readXMLContent(invalidData_noFile),
					false);
			LoaderType::RequestType invalidRequest_noUseNullPoint(spStrReader->readXMLContent(
						invalidData_noUseNullPoint), false);
			LoaderType::RequestType invalidRequest_wrongNullPoint(spStrReader->readXMLContent(
						invalidData_wrongNullPoint), false);
			LoaderType::RequestType invalidRequest_wrongFile(spStrReader->readXMLContent(invalidData_wrongFile),
					false);
			LoaderType::RequestType invalidRequest_wrongFile_lazy(spStrReader->readXMLContent(
						invalidData_wrongFile), true);

			////////////////////////////////////////////
			// Start Tests
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim2));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongType));
			CHECK_EQUAL(false, spLoader->canHandleRequest(validRequest));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest_lazy));
			CHECK_EQUAL(false, spLoader->canHandleRequest(validRequest_noNull));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest_noNull_lazy));

			CHECK_EQUAL("LazyFileFieldKernelLoader<2,2>", spLoader->getProviderName());
			CHECK_EQUAL("LazyFileFieldKernelLoader<2,3>", Loader23Type::getStaticProviderName());

			//test processing of illegal requests

			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongType), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_noFile), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_noUseNullPoint), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongNullPoint), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongFile), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(validRequest), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(validRequest_noNull), core::ServiceException);

			//test valid request
			LoaderType::GenericKernelPointer spKernel;
			CHECK_NO_THROW(spKernel = spLoader->loadKernel(validRequest_lazy));
			LoaderType::GenericKernelPointer spKernel_noNull;
			CHECK_NO_THROW(spKernel_noNull = spLoader->loadKernel(validRequest_noNull_lazy));

      
			//test the fields
      ::map::core::FieldDecomposer<2, 2>::FieldConstPointer actualField;
      ::map::core::FieldDecomposer<2, 2>::decomposeTransform(spRefFunctor->generateTransform(),actualField);

      lit::FieldTester< ::map::core::FieldDecomposer<2, 2>::FieldType> tester;
			double checkThreshold = 0.1;
			tester.setCheckThreshold(checkThreshold);
      tester.setExpectedField(actualField);

			LazyKernelType* pKernel = dynamic_cast<LazyKernelType*>(spKernel.GetPointer());
			CHECK(pKernel != NULL);
      bool validField = ::map::core::FieldDecomposer<2, 2>::decomposeKernel(pKernel, actualField);
      CHECK(validField);
      tester.setActualField(actualField);
			CHECK_TESTER(tester);
			CHECK(*(pKernel->getLargestPossibleRepresentation()) == *spInRep);

			pKernel = dynamic_cast<LazyKernelType*>(spKernel_noNull.GetPointer());
			CHECK(pKernel != NULL);
      validField = ::map::core::FieldDecomposer<2, 2>::decomposeKernel(pKernel, actualField);
      CHECK(validField);
      tester.setActualField(actualField);
			CHECK_TESTER(tester);
			CHECK(*(pKernel->getLargestPossibleRepresentation()) == *spInRep);

			//*@TODO Noch Test fuer: wenn man ein meta file unterschiebt, dass die falsche Dimension hat, also .mapr noch richtige dimension und dann das meta image falsch.

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
