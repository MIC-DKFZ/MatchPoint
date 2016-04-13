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

#include "itkTranslationTransform.h"

#include "mapDefaultKernelInverter.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapNullRegistrationKernel.h"
#include "mapInvertingRegistrationKernel.h"
#include "mapFieldByFieldInversionFunctor.h"

#include "litCheckMacros.h"
#include "litTransformFieldTester.h"


namespace map
{
    namespace testing
    {

        template<class TScalarType, unsigned int VDimensions>
        class TestNonInvertingTranslationTransform : public ::itk::TranslationTransform < TScalarType, VDimensions >
        {
        public:
            /*! Standard class typedefs. */
            typedef TestNonInvertingTranslationTransform<TScalarType, VDimensions>  Self;
            typedef ::itk::TranslationTransform<TScalarType, VDimensions>  Superclass;
            typedef itk::SmartPointer<Self>        Pointer;
            typedef itk::SmartPointer<const Self>  ConstPointer;

            itkTypeMacro(TestNonInvertingTranslationTransform, TranslationTransform);
            itkNewMacro(Self);

            typedef typename Superclass::ScalarType                       ScalarType;
            typedef typename Superclass::InverseTransformBasePointer      InverseTransformBasePointer;

            /** Return an inverse of this transform. */
            virtual InverseTransformBasePointer GetInverseTransform() const
            {
                InverseTransformBasePointer result;
                return result;
            };
        };

        int mapDefaultKernelInverterTest(int argc, char* argv[])
        {
            //ARGUMENTS: 1: Number of iterations
            //           2: Stop value
            //           3: Check threshold

            PREPARE_DEFAULT_TEST_REPORTING;

            unsigned int nrOfIterations = 40;
            double stopValue = 0.1;
            double checkThreshold = 0.1;

            if (argc > 1)
            {
                std::istringstream istream;
                istream.str(argv[1]);
                istream >> nrOfIterations;
            }

            if (argc > 2)
            {
                std::istringstream istream;
                istream.str(argv[2]);
                istream >> stopValue;
            }

            if (argc > 3)
            {
                std::istringstream istream;
                istream.str(argv[3]);
                istream >> checkThreshold;
            }

            typedef core::PreCachedRegistrationKernel<2, 2> KernelType;
            typedef core::PreCachedRegistrationKernel<2, 2> InverseKernelType;

            typedef core::NullRegistrationKernel<2, 2> IllegalKernelType;
            typedef itk::TranslationTransform< ::map::core::continuous::ScalarType, 2> TransformType;

            typedef TestNonInvertingTranslationTransform< ::map::core::continuous::ScalarType, 2>	NumericTransformType;

            typedef core::DefaultKernelInverter<2, 2> InverterType;
            typedef core::DefaultKernelInverter<2, 3> Inverter2Type;

            KernelType::Pointer spKernel = KernelType::New();
            TransformType::Pointer spTransform = TransformType::New();
            TransformType::ParametersType params(2);
            params[0] = 5;
            params[1] = 5;
            spTransform->SetParameters(params);
            spKernel->setTransformModel(spTransform);

            KernelType::Pointer spNumericKernel = KernelType::New();
            NumericTransformType::Pointer spNumericTransform = NumericTransformType::New();
            spNumericTransform->SetParameters(params);
            spNumericKernel->setTransformModel(spNumericTransform);

            InverseKernelType::RepresentationDescriptorType::SpacingType spacing(0.5);
            InverseKernelType::RepresentationDescriptorType::PointType origin;
            origin.Fill(0);
            InverseKernelType::RepresentationDescriptorType::SizeType size;
            size.fill(2);

            InverseKernelType::RepresentationDescriptorType::Pointer spInverseRep =
                InverseKernelType::RepresentationDescriptorType::New();
            spInverseRep->setSize(size);
            spInverseRep->setSpacing(spacing);
            spInverseRep->setOrigin(origin);


            IllegalKernelType::Pointer spIllegalKernel = IllegalKernelType::New();

            InverterType::Pointer spInverter = InverterType::New();
            Inverter2Type::Pointer spInverter2 = Inverter2Type::New();

            spInverter->setFunctorStopValue(stopValue);
            spInverter->setFunctorNumberOfIterations(nrOfIterations);

            CHECK_EQUAL(stopValue, spInverter->getFunctorStopValue());
            CHECK_EQUAL(nrOfIterations, spInverter->getFunctorNumberOfIterations());


            CHECK_EQUAL(false, spInverter->canHandleRequest(*(spIllegalKernel.GetPointer())));
            CHECK_EQUAL(true, spInverter->canHandleRequest(*(spKernel.GetPointer())));

            CHECK_EQUAL("DefaultKernelInverter<2,2>", spInverter->getProviderName());
            CHECK_EQUAL("DefaultKernelInverter<2,3>", spInverter2->getProviderName());

            CHECK_THROW_EXPLICIT(spInverter->invertKernel(*(spIllegalKernel.GetPointer()), NULL, NULL),
                core::ServiceException);

            InverterType::InverseKernelBasePointer spInverseKernel;
            CHECK_NO_THROW(spInverseKernel = spInverter->invertKernel(*(spKernel.GetPointer()), NULL, NULL));

            //test if the kernel was really inverted analytically

            CHECK(spInverseKernel.IsNotNull());
            InverseKernelType* pInverseConcreteKernel = dynamic_cast<InverseKernelType*>
                (spInverseKernel.GetPointer());
            CHECK(NULL != pInverseConcreteKernel);

            //check correct inversion by transform parameters
            CHECK_EQUAL(-5, pInverseConcreteKernel->getTransformModel()->GetParameters()[0]);
            CHECK_EQUAL(-5, pInverseConcreteKernel->getTransformModel()->GetParameters()[1]);


            //test if the kernel was really inverted numerically, thus a lazy field kernel was established

            InverterType::InverseKernelBasePointer spInverseNumericKernel;
            CHECK_THROW_EXPLICIT(spInverseNumericKernel = spInverter->invertKernel(*
                (spNumericKernel.GetPointer()), NULL, NULL), core::ServiceException);
            CHECK_NO_THROW(spInverseNumericKernel = spInverter->invertKernel(*(spNumericKernel.GetPointer()),
                NULL, spInverseRep));

            //test if the kernel was really inverted numerically

            CHECK(spInverseNumericKernel.IsNotNull());
            typedef core::InvertingRegistrationKernel<2, 2> FieldBasedRegistrationKernelType;
            FieldBasedRegistrationKernelType* pInverseConcreteNumericKernel =
                dynamic_cast<FieldBasedRegistrationKernelType*>(spInverseNumericKernel.GetPointer());
            CHECK(NULL != pInverseConcreteNumericKernel);

            ::map::core::FieldDecomposer<2, 2>::FieldConstPointer actualField;
            ::map::core::FieldDecomposer<2, 2>::decomposeKernel(pInverseConcreteNumericKernel, actualField);

            //check correct inversion
            lit::TransformFieldTester < ::map::core::FieldDecomposer<2, 2>::FieldType, NumericTransformType::InverseTransformBaseType >
                tester;
            tester.setReferenceTransform(pInverseConcreteKernel->getTransformModel());
            tester.setActualField(actualField);
            tester.setCheckThreshold(0.1);

            CHECK_TESTER(tester);


            RETURN_AND_REPORT_TEST_SUCCESS;
        }
    } //namespace testing
} //namespace map
