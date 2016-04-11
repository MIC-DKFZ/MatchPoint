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

#include "mapNullRegistrationKernel.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapLazyRegistrationKernel.h"
#include "mapExpandingFieldKernelWriter.h"
#include "mapSDXMLStrWriter.h"
#include "test/mapTestFieldGenerationFunctor.h"
#include "mapFileDispatch.h"
#include "mapFieldDecomposer.h"

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
      FieldFunctorType::TransformPointer spPreCachedTransform = spFunctor->generateTransform();

      //////////////////////////////////////
      //Kernel setup
      typedef core::LazyRegistrationKernel<2, 2> LazyKernelType;
      typedef core::PreCachedRegistrationKernel<2, 2> PreCachedKernelType;
      typedef core::NullRegistrationKernel<2, 2> IllegalKernelType;

      typedef io::ExpandingFieldKernelWriter<2, 2> WriterType;
      typedef io::ExpandingFieldKernelWriter<2, 3> Writer23Type;

      IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();
      LazyKernelType::Pointer spLazyKernel = LazyKernelType::New();
      PreCachedKernelType::Pointer spCachedKernel = PreCachedKernelType::New();

      spLazyKernel->setTransformFunctor(spFunctor.GetPointer());
      LazyKernelType::OutputPointType nullPoint;
      nullPoint[0] = -1;
      nullPoint[1] = -2;
      spFunctor->setNullPointUsage(true);
      spFunctor->setNullPoint(nullPoint);

      ////////////////////////////////////////////
      //Writer setup
      WriterType::Pointer spWriter = WriterType::New();

      WriterType::RequestType illegalRequest1(spIllegalKernel, "", "", false);
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
      spCachedKernel->setTransformModel(spPreCachedTransform);
      structuredData::Element::Pointer spDataCached;
      CHECK_NO_THROW(spDataCached = spWriter->storeKernel(requestCached));

      //test content
      structuredData::XMLStrWriter::Pointer spStrWriter = structuredData::XMLStrWriter::New();

      core::String data = spStrWriter->write(spDataLazy);
      core::String ref =
        "<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>ExpandingFieldKernelWriterTest_lazy_field.nrrd</FieldPath><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";

      CHECK_EQUAL(ref, data);

      //test the fields
      map::core::FieldDecomposer<2, 2>::FieldConstPointer actualField;
      map::core::String refFieldPath = map::core::FileDispatch::createFullPath(refPath,
                                       "expandingFieldKernelWriterTest_ref.mhd");
      typedef ::itk::ImageFileReader<map::core::FieldDecomposer<2, 2>::FieldType> ReaderType;
      ReaderType::Pointer spReader = ReaderType::New();
      spReader->SetFileName(refFieldPath);
      map::core::FieldDecomposer<2, 2>::FieldPointer spRefField = spReader->GetOutput();
      spReader->Update();

      map::core::FieldDecomposer<2, 2>::decomposeKernel(spLazyKernel, actualField);

      lit::FieldTester<map::core::FieldDecomposer<2, 2>::FieldType> tester;
      double checkThreshold = 0.1;
      tester.setCheckThreshold(checkThreshold);
      tester.setExpectedField(spRefField);

      map::core::FieldDecomposer<2, 2>::decomposeKernel(spLazyKernel, actualField);
      tester.setActualField(actualField);
      CHECK_TESTER(tester);

      map::core::FieldDecomposer<2, 2>::decomposeKernel(spCachedKernel, actualField);
      tester.setActualField(actualField);
      CHECK_TESTER(tester);

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace map
