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

#include "itkEuler2DTransform.h"
#include "itkImageFileReader.h"

#include "litCheckMacros.h"
#include "litFieldTester.h"

#include "mapPreCachedRegistrationKernel.h"
#include "mapInvertingRegistrationKernel.h"
#include "mapInvertingKernelWriter.h"
#include "mapFieldByModelInversionFunctor.h"
#include "mapSDXMLStrWriter.h"
#include "mapFileDispatch.h"


namespace map
{
	namespace testing
	{

		int mapInvertingKernelWriterTest(int argc, char* argv[])
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
			typedef core::PreCachedRegistrationKernel<2, 2> KernelType;
			typedef itk::Euler2DTransform<::map::core::continuous::ScalarType> TransformType;

			KernelType::Pointer spSourceKernel = KernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(3);
			params[0] = 1.5708;
			params[1] = 5;
			params[2] = 2;
			spTransform->SetParameters(params);
			spSourceKernel->setTransformModel(spTransform);


			typedef core::functors::FieldByModelInversionFunctor<2, 2> FieldFunctorType;
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

			typedef core::InvertingRegistrationKernel<2, 2> InvertingKernelType;
			InvertingKernelType::Pointer spInvertingKernel = InvertingKernelType::New();
			spInvertingKernel->setSourceKernel(spSourceKernel);
			spInvertingKernel->setTransformFunctor(spFunctor);

			InvertingKernelType::Pointer spInvertingKernel_missingSource = InvertingKernelType::New();
			spInvertingKernel_missingSource->setTransformFunctor(spFunctor);

			typedef io::InvertingKernelWriter<2, 2> WriterType;
			typedef io::InvertingKernelWriter<2, 3> Writer23Type;

			////////////////////////////////////////////
			//Writer setup
			WriterType::Pointer spWriter = WriterType::New();

			WriterType::RequestType illegalRequest_invalidKernelType(spSourceKernel, "", "", false);
			WriterType::RequestType illegalRequest_invalidKernelConfig(spInvertingKernel_missingSource, "", "",
					false, spSourceKernel);
			WriterType::RequestType illegalRequest_missingSource1(spInvertingKernel, "", "", false);
			WriterType::RequestType illegalRequest_missingSource2(spInvertingKernel, "", "", false, NULL);
			WriterType::RequestType illegalRequest_expandLazy(spInvertingKernel, "", "", true, spSourceKernel);
			WriterType::RequestType request(spInvertingKernel, testPath, "InvertingKernelWriterTest",
											false, spSourceKernel);

			//////////////////////////////////////
			//Tests

			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest_invalidKernelType));
			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest_invalidKernelConfig));
			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest_missingSource1));
			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest_missingSource2));
			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest_expandLazy));
			CHECK_EQUAL(true, spWriter->canHandleRequest(request));

			CHECK_EQUAL("InvertingKernelWriter<2,2>", spWriter->getProviderName());
			CHECK_EQUAL("InvertingKernelWriter<2,3>", Writer23Type::getStaticProviderName());

			//test processing of illegal requests
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest_invalidKernelType),
								 core::ServiceException);
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest_invalidKernelConfig),
								 core::ServiceException);
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest_missingSource1), core::ServiceException);
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest_missingSource2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest_expandLazy), core::ServiceException);

			//test valid request
			structuredData::Element::Pointer spData;
			CHECK_NO_THROW(spData = spWriter->storeKernel(request));

			//test content
			structuredData::XMLStrWriter::Pointer spStrWriter = structuredData::XMLStrWriter::New();

			::map::core::String data = spStrWriter->write(spData);
			::map::core::String ref =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>InvertingKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>InvertingKernel</KernelType><InverseFieldRepresentation Dimensions='2'><Size><Value Row='0'>10.00000000</Value><Value Row='1'>10.00000000</Value></Size><Origin><Value Row='0'>0.0000000000</Value><Value Row='1'>0.0000000000</Value></Origin><Spacing><Value Row='0'>0.5000000000</Value><Value Row='1'>0.5000000000</Value></Spacing><Direction><Value Column='0' Row='0'>1.000000000</Value><Value Column='1' Row='0'>0.0000000000</Value><Value Column='0' Row='1'>0.0000000000</Value><Value Column='1' Row='1'>1.000000000</Value></Direction></InverseFieldRepresentation><UseNullVector>1</UseNullVector><NullVector><Value Row='0'>-1.797693135e+308</Value><Value Row='1'>-1.797693135e+308</Value></NullVector></Kernel>";

			CHECK_EQUAL(ref, data);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
