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
#include "mapExpandingFieldKernelWriter.h"
#include "mapSDXMLStrWriter.h"
#include "test/mapTestFieldGenerationFunctor.h"
#include "mapFileDispatch.h"

#include "litCheckMacros.h"
#include "litFieldTester.h"

#include "itkImageFileReader.h"

namespace map
{
	namespace testing
	{

		int mapExpandingFieldKernelWriterTest(int argc, char* argv[])
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

			//functor for lazy field kernel
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
			FieldFunctorType::Pointer spFunctor = FieldFunctorType::New(spInRep);

			//////////////////////////////////////
			//Kernel setup
			typedef core::ModelBasedRegistrationKernel<2, 2> KernelType;

			typedef core::FieldKernels<2, 2>::LazyFieldBasedRegistrationKernel LazyKernelType;
			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel PreCachedKernelType;
			typedef core::ModelBasedRegistrationKernel<2, 2> ModelKernelType;

			typedef io::ExpandingFieldKernelWriter<2, 2> WriterType;
			typedef io::ExpandingFieldKernelWriter<2, 3> Writer23Type;

			ModelKernelType::Pointer spModelKernel = ModelKernelType::New();
			LazyKernelType::Pointer spLazyKernel = LazyKernelType::New();
			PreCachedKernelType::Pointer spCachedKernel = PreCachedKernelType::New();

			spLazyKernel->setFieldFunctor(*(spFunctor.GetPointer()));
			LazyKernelType::MappingVectorType nullVector;
			nullVector[0] = -1;
			nullVector[1] = -2;
			spLazyKernel->setNullVector(nullVector);
			//the cached kernel is not set by purpose now to check the behavior when the field is missing

			spCachedKernel->setNullVectorUsage(false);

			////////////////////////////////////////////
			//Writer setup
			WriterType::Pointer spWriter = WriterType::New();

			WriterType::RequestType illegalRequest1(spModelKernel, "", "", false);
			WriterType::RequestType illegalRequest2(spLazyKernel, "", "", false);
			WriterType::RequestType requestLazy(spLazyKernel, testPath, "ExpandingFieldKernelWriterTest_lazy",
												true);
			WriterType::RequestType requestCached(spCachedKernel, testPath,
												  "ExpandingFieldKernelWriterTest_cached", true);


			//////////////////////////////////////
			//Tests

			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest2));
			CHECK_EQUAL(true, spWriter->canHandleRequest(requestLazy));
			CHECK_EQUAL(true, spWriter->canHandleRequest(requestCached));

			CHECK_EQUAL("ExpandingFieldKernelWriter<2,2>", spWriter->getProviderName());
			CHECK_EQUAL("ExpandingFieldKernelWriter<2,3>", Writer23Type::getStaticProviderName());

			//test processing of illegal requests
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest1), core::ServiceException);
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest2), core::ServiceException);
			CHECK_THROW(spWriter->storeKernel(requestCached)); //illegal because field is not yet set

			//test valid request
			structuredData::Element::Pointer spDataLazy;
			CHECK_NO_THROW(spDataLazy = spWriter->storeKernel(requestLazy));

			//make the cached kernel legal
			spCachedKernel->setField(*(spLazyKernel->getField()));
			structuredData::Element::Pointer spDataCached;
			CHECK_NO_THROW(spDataCached = spWriter->storeKernel(requestCached));

			//test content
			structuredData::XMLStrWriter::Pointer spStrWriter = structuredData::XMLStrWriter::New();

			core::String data = spStrWriter->write(spDataLazy);
			core::String ref =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>ExpandingFieldKernelWriterTest_lazy_field.mhd</FieldPath><UseNullVector>1</UseNullVector><NullVector><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullVector></Kernel>";

			CHECK_EQUAL(ref, data);

			//test the fields
			map::core::String refFieldPath = map::core::FileDispatch::createFullPath(refPath,
											 "expandingFieldKernelWriterTest_ref.mhd");
			typedef ::itk::ImageFileReader<LazyKernelType::FieldType> ReaderType;
			ReaderType::Pointer spReader = ReaderType::New();
			spReader->SetFileName(refFieldPath);
			FieldFunctorType::FieldPointer spRefField = spReader->GetOutput();
			spReader->Update();

			lit::FieldTester<FieldFunctorType::FieldType> tester;
			double checkThreshold = 0.1;
			tester.setCheckThreshold(checkThreshold);
			tester.setExpectedField(spRefField);

			tester.setActualField(spLazyKernel->getField());
			CHECK_TESTER(tester);

			tester.setActualField(spCachedKernel->getField());
			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
