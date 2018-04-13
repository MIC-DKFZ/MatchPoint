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

#include "itksys/SystemTools.hxx"

#include "mapRegistrationFileReader.h"
#include "mapRegistration.h"
#include "mapNullRegistrationKernel.h"
#include "mapRegistrationKernel.h"
#include "mapLazyFieldFileKernelWriter.h"
#include "mapFileDispatch.h"
#include "mapSDXMLStrWriter.h"

#include "litCheckMacros.h"
#include "litFieldTester.h"


namespace map
{
  namespace testing
  {

    ::map::core::RegistrationKernel<2,2>::ConstPointer LoadLazyKernel(const std::string& refPath)
    {
      typedef ::map::io::RegistrationFileReader ReaderType;
      ReaderType::Pointer spReader = ReaderType::New();
      spReader->setPreferLazyLoading(true);

      auto fullpath = ::map::core::FileDispatch::createFullPath(refPath, "registrationFileWriterReader_Ref7.mapr");
      ::map::core::Registration<2,2>::Pointer spRegistration = dynamic_cast<::map::core::Registration<2, 2> *>( spReader->read(fullpath).GetPointer());

      return dynamic_cast<const ::map::core::RegistrationKernel<2, 2> *>(&(spRegistration->getInverseMapping()));
    };

    ::map::core::RegistrationKernel<2, 2>::ConstPointer LoadExpandedKernel(const std::string& refPath)
    {
      typedef ::map::io::RegistrationFileReader ReaderType;
      ReaderType::Pointer spReader = ReaderType::New();
      spReader->setPreferLazyLoading(false);

      auto fullpath = ::map::core::FileDispatch::createFullPath(refPath, "registrationFileWriterReader_Ref7.mapr");
      ::map::core::Registration<2, 2>::Pointer spRegistration = dynamic_cast<::map::core::Registration<2, 2> *>(spReader->read(fullpath).GetPointer());

      return dynamic_cast<const ::map::core::RegistrationKernel<2, 2> *>(&(spRegistration->getInverseMapping()));
    };

    int mapLazyFieldFileKernelWriterTest(int argc, char* argv[])
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
      typedef core::RegistrationKernel<2, 2> KernelType;

      KernelType::ConstPointer lazyKernel = LoadLazyKernel(refPath);
      KernelType::ConstPointer unLazyKernel = LoadLazyKernel(refPath);
      unLazyKernel->precomputeKernel();
      KernelType::ConstPointer expandedKernel = LoadExpandedKernel(refPath);

      typedef core::NullRegistrationKernel<2, 2> IllegalKernelType;

      IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();

      typedef io::LazyFieldFileKernelWriter<2, 2> WriterType;
      typedef io::LazyFieldFileKernelWriter<2, 3> Writer23Type;


      ////////////////////////////////////////////
      //Writer setup
      WriterType::Pointer spWriter = WriterType::New();

      WriterType::RequestType illegalRequest1(spIllegalKernel, "", "", false);
      WriterType::RequestType illegalRequest2(expandedKernel, "", "", false);
      WriterType::RequestType illegalRequest3(lazyKernel, testPath, "LazyFieldFileKernelWriterTest", true);
      WriterType::RequestType request(lazyKernel, testPath, "LazyFieldFileKernelWriterTest",false);
      WriterType::RequestType unlazyRequest(unLazyKernel, testPath, "UnLazyFieldFileKernelWriterTest", false);

      //////////////////////////////////////
      //Tests

      CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest1));
      CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest2));
      CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest3));
      CHECK_EQUAL(true, spWriter->canHandleRequest(request));

      CHECK_EQUAL("LazyFieldFileKernelWriter<2,2>", spWriter->getProviderName());
      CHECK_EQUAL("LazyFieldFileKernelWriter<2,3>", Writer23Type::getStaticProviderName());

      //test processing of illegal requests
      CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest1), core::ServiceException);
      CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest2), core::ServiceException);
      CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest3), core::ServiceException);

      //test valid request
      structuredData::Element::Pointer spDataLazy;
      CHECK_NO_THROW(spDataLazy = spWriter->storeKernel(request));

      //test content
      structuredData::XMLStrWriter::Pointer spStrWriter = structuredData::XMLStrWriter::New();

      core::String data = spStrWriter->write(spDataLazy);
      core::String ref =
        "<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>LazyFieldFileKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>LazyFieldFileKernelWriterTest_field.nrrd</FieldPath><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";
      CHECK_EQUAL(ref, data);

      auto refFieldPath = ::map::core::FileDispatch::createFullPath(refPath, "expandingFieldKernelWriterTest_ref.nrrd");
      auto testFieldPath = ::map::core::FileDispatch::createFullPath(testPath, "LazyFieldFileKernelWriterTest_field.nrrd");

      CHECK(!itksys::SystemTools::FilesDiffer(refFieldPath, testFieldPath));

      //write again. Now the data is not lazy any more and should be passed to the ExpandingFieldWriter
      CHECK_NO_THROW(spDataLazy = spWriter->storeKernel(unlazyRequest));

      data = spStrWriter->write(spDataLazy);
      ref =
        "<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>ExpandingFieldKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>ExpandedFieldKernel</KernelType><FieldPath>UnLazyFieldFileKernelWriterTest_field.nrrd</FieldPath><UseNullPoint>1</UseNullPoint><NullPoint><Value Row='0'>-1.000000000</Value><Value Row='1'>-2.000000000</Value></NullPoint></Kernel>";
      CHECK_EQUAL(ref, data);

      refFieldPath = ::map::core::FileDispatch::createFullPath(refPath, "expandingFieldKernelWriterTest_ref.nrrd");
      testFieldPath = ::map::core::FileDispatch::createFullPath(testPath, "UnLazyFieldFileKernelWriterTest_field.nrrd");

      CHECK(!itksys::SystemTools::FilesDiffer(refFieldPath, testFieldPath));

      RETURN_AND_REPORT_TEST_SUCCESS;
    }
  } //namespace testing
} //namespace map
