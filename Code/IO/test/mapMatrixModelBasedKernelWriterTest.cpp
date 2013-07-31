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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/test/mapMatrixModelBasedKernelWriterTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapModelBasedRegistrationKernel.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapITKEuler2DTransform.h"
#include "mapITKDimensionedTransformModel.h"
#include "mapMatrixModelBasedKernelWriter.h"
#include "mapSDXMLStrWriter.h"

#include "litCheckMacros.h"
#include "litTransformFieldTester.h"


namespace map
{
	namespace testing
	{

		template< template <typename> class TTransform, class TScalarType>
		class TestNumericTransformModel : public core::ITKDimensionedTransformModel<TTransform, TScalarType>
		{
		public:
			/*! Standard class typedefs. */
			typedef TestNumericTransformModel<TTransform, TScalarType>  Self;
			typedef core::ITKDimensionedTransformModel<TTransform, TScalarType>  Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(TestNumericTransformModel, ITKDimensionedTransformModel);
			itkNewMacro(Self);

			typedef typename Superclass::ScalarType                       ScalarType;
			typedef typename Superclass::InverseTransformModelPointer     InverseTransformModelPointer;
			typedef typename Superclass::InverseTransformModelBasePointer InverseTransformModelBasePointer;
			typedef typename Superclass::TransformModelBasePointer        TransformModelBasePointer;
			typedef typename Superclass::MatrixType                       MatrixType;
			typedef typename Superclass::OutputVectorType                 OutputVectorType;

			virtual bool getInverse(InverseTransformModelBasePointer &spInverseModel) const
			{
				return false;
			};

			virtual bool getAffineMatrixDecomposition(MatrixType &matrix, OutputVectorType &offset) const
			{
				return false;
			};

		protected:

			virtual InverseTransformModelPointer createInverse() const
			{
				InverseTransformModelPointer spNew;
				return spNew;
			};

			virtual TransformModelBasePointer createAnotherInstance() const
			{
				TransformModelBasePointer spNew = New().GetPointer();
				return spNew;
			};

		};

		int mapMatrixModelBasedKernelWriterTest(int argc, char *argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::ModelBasedRegistrationKernel<2, 2> KernelType;

			typedef core::FieldKernels<2, 2>::PreCachedFieldBasedRegistrationKernel IllegalKernelType;
			typedef algorithm::itk::ITKTransformModel< itk::Euler2DTransform<core::continuous::ScalarType> > TransformType;
			typedef TestNumericTransformModel<itk::Euler2DTransform, core::continuous::ScalarType> NumericTransformType;

			typedef io::MatrixModelBasedKernelWriter<2, 2> WriterType;
			typedef io::MatrixModelBasedKernelWriter<2, 3> Writer23Type;

			KernelType::Pointer spKernel = KernelType::New();
			TransformType::Pointer spTransform = TransformType::New();
			TransformType::ParametersType params(3);
			params[0] = 1.5708;
			params[1] = 5;
			params[2] = 2;
			spTransform->getTransform()->SetParameters(params);
			spKernel->setTransformModel(spTransform);

			KernelType::Pointer spNumericKernel = KernelType::New();
			NumericTransformType::Pointer spNumericTransform = NumericTransformType::New();
			spNumericTransform->getTransform()->SetParameters(params);
			spNumericKernel->setTransformModel(spNumericTransform);

			IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();

			WriterType::Pointer spWriter = WriterType::New();

			WriterType::RequestType illegalRequest1(spIllegalKernel, "", "", false);
			WriterType::RequestType illegalRequest2(spNumericKernel, "", "", false);
			WriterType::RequestType request(spKernel, "", "MatrixModelBasedWriterTest", false);

			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest1));
			CHECK_EQUAL(false, spWriter->canHandleRequest(illegalRequest2));
			CHECK_EQUAL(true, spWriter->canHandleRequest(request));

			CHECK_EQUAL("MatrixModelBasedKernelWriter<2,2>", spWriter->getProviderName());
			CHECK_EQUAL("MatrixModelBasedKernelWriter<2,3>", Writer23Type::getStaticProviderName());

			//test processing of illegal requests

			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest1), core::ServiceException);
			CHECK_THROW_EXPLICIT(spWriter->storeKernel(illegalRequest2), core::ServiceException);

			//test valid request
			structuredData::Element::Pointer spData;
			CHECK_NO_THROW(spData = spWriter->storeKernel(request));

			//test content
			structuredData::XMLStrWriter::Pointer spStrWriter = structuredData::XMLStrWriter::New();

			core::String data = spStrWriter->write(spData);
			core::String ref = "<Kernel InputDimensions='2' OutputDimensions='2'><StreamProvider>MatrixModelBasedKernelWriter&lt;2,2&gt;</StreamProvider><KernelType>MatrixModelKernel</KernelType><Matrix><Value Column='0' Row='0'>-3.673205103e-006</Value><Value Column='1' Row='0'>-1.000000000</Value><Value Column='0' Row='1'>1.000000000</Value><Value Column='1' Row='1'>-3.673205103e-006</Value></Matrix><MatrixStr>-3.67321e-006 -1 1 -3.67321e-006 </MatrixStr><Offset><Value Row='0'>5.000000000</Value><Value Row='1'>2.000000000</Value></Offset><OffsetStr>5 2 </OffsetStr></Kernel>";

			CHECK_EQUAL(ref, data);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
