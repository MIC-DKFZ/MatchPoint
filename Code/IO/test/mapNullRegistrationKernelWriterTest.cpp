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
#include "mapNullRegistrationKernel.h"
#include "mapNullRegistrationKernelWriter.h"
#include "mapSDXMLStrWriter.h"

#include "litCheckMacros.h"


namespace map
{
	namespace testing
	{

		int mapNullRegistrationKernelWriterTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::NullRegistrationKernel<2, 2> KernelType;

			typedef core::PreCachedRegistrationKernel<2, 2> IllegalKernelType;

			typedef io::NullRegistrationKernelWriter<2, 2> WriterType;
			typedef io::NullRegistrationKernelWriter<2, 3> Writer23Type;

			KernelType::Pointer spKernel = KernelType::New();
			IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();

			WriterType::Pointer spWriter = WriterType::New();

			WriterType::RequestType illegalRequest1(spIllegalKernel, "", "", false);
			WriterType::RequestType request(spKernel, "", "NullRegistrationKernelWriterTest", false);

			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(true, spWriter->canHandleRequest(request));

			CHECK_EQUAL("NullRegistrationKernelWriter<2,2>", spWriter->getProviderName());
			CHECK_EQUAL("NullRegistrationKernelWriter<2,3>", Writer23Type::getStaticProviderName());

			//test processing of illegal requests
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest1), core::ServiceException);

			//test valid request
			structuredData::Element::Pointer spData;
			CHECK_NO_THROW(spData = spWriter->storeKernel(request));

			//test content
			structuredData::XMLStrWriter::Pointer spStrWriter = structuredData::XMLStrWriter::New();

			::map::core::String data = spStrWriter->write(spData);
			::map::core::String ref =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>NullRegistrationKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>NullRegistrationKernel</KernelType></Kernel>";

			CHECK_EQUAL(ref, data);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
