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

#include "mapPreCachedRegistrationKernel.h"
#include "mapMatrixModelBasedKernelLoader.h"
#include "mapSDXMLStrReader.h"

#include "litCheckMacros.h"
#include "litTransformFieldTester.h"


namespace map
{
	namespace testing
	{

		int mapMatrixModelBasedKernelLoaderTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::PreCachedRegistrationKernel<2, 2> KernelType;

			typedef io::MatrixModelBasedKernelLoader<2> LoaderType;

			LoaderType::Pointer spLoader = LoaderType::New();

			::map::core::String validData =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType><Matrix><Value Column='0' Row='0'>0</Value><Value Column='1' Row='0'>-1.000000000</Value><Value Column='0' Row='1'>1.000000000</Value><Value Column='1' Row='1'>0</Value></Matrix><MatrixStr>0 -1 1 0 </MatrixStr><Offset><Value Row='0'>5.000000000</Value><Value Row='1'>2.000000000</Value></Offset><OffsetStr>5 2 </OffsetStr></Kernel>";
			::map::core::String invalidData_wrongDim =
				"<Kernel InputDimensions='2' OutputDimensions='3'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType></Kernel>";
			::map::core::String invalidData_wrongDim2 =
				"<Kernel InputDimensions='3' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType></Kernel>";
			::map::core::String invalidData_wrongType =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>WrongKernelType</KernelType></Kernel>";
			::map::core::String invalidData_noMatrix =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType></Kernel>";
			::map::core::String invalidData_wrongMatrix =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType><Matrix><Value Column='0' Row='0'>-3.673205103e-006</Value><Value Column='1' Row='0'>-1.000000000</Value></Matrix></Kernel>";
			::map::core::String invalidData_noOffset =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType><Matrix><Value Column='0' Row='0'>-3.673205103e-006</Value><Value Column='1' Row='0'>-1.000000000</Value><Value Column='0' Row='1'>1.000000000</Value><Value Column='1' Row='1'>-3.673205103e-006</Value></Matrix><MatrixStr>-3.67321e-006 -1 1 -3.67321e-006 </MatrixStr><OffsetStr>5 2 </OffsetStr></Kernel>";
			::map::core::String invalidData_wrongOffset =
				"<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType><Matrix><Value Column='0' Row='0'>-3.673205103e-006</Value><Value Column='1' Row='0'>-1.000000000</Value><Value Column='0' Row='1'>1.000000000</Value><Value Column='1' Row='1'>-3.673205103e-006</Value></Matrix><MatrixStr>-3.67321e-006 -1 1 -3.67321e-006 </MatrixStr><Offset><Value Row='0'>5.000000000</Value></Offset><OffsetStr>5 2 </OffsetStr></Kernel>";

			structuredData::XMLStrReader::Pointer spStrReader = structuredData::XMLStrReader::New();

			LoaderType::RequestType validRequest(spStrReader->readXMLContent(validData), false);
			LoaderType::RequestType invalidRequest_wrongDim(spStrReader->readXMLContent(invalidData_wrongDim),
					false);
			LoaderType::RequestType invalidRequest_wrongDim2(spStrReader->readXMLContent(invalidData_wrongDim2),
					false);
			LoaderType::RequestType invalidRequest_wrongType(spStrReader->readXMLContent(invalidData_wrongType),
					false);
			LoaderType::RequestType invalidRequest_noMatrix(spStrReader->readXMLContent(invalidData_noMatrix),
					false);
			LoaderType::RequestType invalidRequest_wrongMatrix(spStrReader->readXMLContent(
						invalidData_wrongMatrix), false);
			LoaderType::RequestType invalidRequest_noOffset(spStrReader->readXMLContent(invalidData_noOffset),
					false);
			LoaderType::RequestType invalidRequest_wrongOffset(spStrReader->readXMLContent(
						invalidData_wrongOffset), false);


			////////////////////////////////////////////
			// Start Tests
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongDim2));
			CHECK_EQUAL(false, spLoader->canHandleRequest(invalidRequest_wrongType));
			CHECK_EQUAL(true, spLoader->canHandleRequest(validRequest));

			CHECK_EQUAL("MatrixModelBasedKernelLoader<2,2>", spLoader->getProviderName());
			CHECK_EQUAL("MatrixModelBasedKernelLoader<2,2>", LoaderType::getStaticProviderName());

			//test processing of illegal requests

			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongDim2), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongType), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_noMatrix), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongMatrix), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_noOffset), core::ServiceException);
			CHECK_THROW_EXPLICIT(spLoader->loadKernel(invalidRequest_wrongOffset), core::ServiceException);

			//test valid request
			LoaderType::GenericKernelPointer spKernel;
			CHECK_NO_THROW(spKernel = spLoader->loadKernel(validRequest));
			KernelType* pMKernel = dynamic_cast<KernelType*>(spKernel.GetPointer());
			CHECK(pMKernel != NULL);

			KernelType::TransformType::MatrixType matrix;
			KernelType::TransformType::OutputVectorType offset;
			CHECK(pMKernel->getAffineMatrixDecomposition(matrix, offset));
			CHECK_EQUAL(5, offset[0]);
			CHECK_EQUAL(2, offset[1]);
			CHECK_EQUAL(0, matrix[0][0]);
			CHECK_EQUAL(-1, matrix[0][1]);
			CHECK_EQUAL(1, matrix[1][0]);
			CHECK_EQUAL(0, matrix[1][1]);

			//Test adding of kernels
			//*@TODO test for adding kernels

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
