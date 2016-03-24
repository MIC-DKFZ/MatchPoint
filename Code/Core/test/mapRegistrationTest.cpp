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

#include "mapRegistration.h"
#include "mapRegistrationManipulator.h"
#include "litCheckMacros.h"
#include "mapRegistrationKernelBase.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class TestRegistrationKernel : public
			::map::core::RegistrationKernelBase<VInputDimensions, VOutputDimensions>
		{
		public:
			typedef TestRegistrationKernel<VInputDimensions, VOutputDimensions> Self;
			typedef core::RegistrationKernelBase<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;
			typedef typename Superclass::InputPointType InputPointType;
			typedef typename Superclass::OutputPointType OutputPointType;
			typedef typename Superclass::RepresentationDescriptorConstPointer
			RepresentationDescriptorConstPointer;
			typedef typename Superclass::RepresentationDescriptorPointer RepresentationDescriptorPointer;

			itkTypeMacro(TestRegistrationKernel, RegistrationKernelBase);

			itkNewMacro(Self);

			virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const
			{
				//dummy mapping not important for this test level
				_hasMappedPoint = true;
				return true;
			};


			virtual bool hasLimitedRepresentation()
			{
				return false;
			};

			virtual RepresentationDescriptorConstPointer getLargestPossibleRepresentation() const
			{
				RepresentationDescriptorConstPointer _spDummy = _spFieldRepresentation.GetPointer();
				return _spDummy;
			};

			virtual void precomputeKernel()
			{
				_isPreComputed = true;
			};


			bool _isPreComputed;
			mutable bool _hasMappedPoint;

			RepresentationDescriptorPointer _spFieldRepresentation;

		protected:
			TestRegistrationKernel()
			{
				_isPreComputed = false;
				_hasMappedPoint = false;
			};

			virtual ~TestRegistrationKernel() {};

		private:
			//No copy constructor allowed
			TestRegistrationKernel(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

		class TestRegistrationGenerator1
		{
		public:
			typedef core::Registration<2, 2> Registration1Type;
			typedef core::RegistrationManipulator<Registration1Type> ManipulatorType;
			typedef Registration1Type::Pointer Registration1Pointer;

			typedef core::FieldRepresentationDescriptor<2> FRD2DType;
			typedef FRD2DType::Pointer FRD2DPointer;

			FRD2DPointer _spField2D;

			std::string _tag1;
			std::string _value1;

			TestRegistrationKernel<2, 2>::Pointer _spDirectKernel;
			TestRegistrationKernel<2, 2>::Pointer _spInverseKernel;

			Registration1Pointer generate()
			{
				Registration1Pointer spReg = Registration1Type::New();
				ManipulatorType manip(spReg);

				manip.setDirectMapping(_spDirectKernel);
				manip.setInverseMapping(_spInverseKernel);

				::map::core::RegistrationBase::TagMapType tags;
				std::pair<std::string, std::string> taggedValue(_tag1, _value1);
				tags.insert(taggedValue);

				manip.setTagValues(tags);

				return spReg;
			};

			TestRegistrationGenerator1()
			{
				_spField2D = FRD2DType::New();
				_spDirectKernel = TestRegistrationKernel<2, 2>::New();
				_spDirectKernel->_spFieldRepresentation = _spField2D;
				_spInverseKernel = TestRegistrationKernel<2, 2>::New();

				_tag1 = "param1";
				_value1 = "value1";
			}
		};

		class TestRegistrationGenerator2
		{
		public:
			typedef core::Registration<2, 3> Registration2Type;
			typedef core::RegistrationManipulator<Registration2Type> ManipulatorType;
			typedef Registration2Type::Pointer Registration2Pointer;

			typedef core::FieldRepresentationDescriptor<3> FRD3DType;
			typedef FRD3DType::Pointer FRD3DPointer;

			FRD3DPointer _spField3D;
			TestRegistrationKernel<2, 3>::Pointer _spDirectKernel;
			TestRegistrationKernel<3, 2>::Pointer _spInverseKernel;

			std::string _tag2;
			std::string _value2;

			Registration2Pointer generate()
			{
				Registration2Pointer spReg = Registration2Type::New();

				ManipulatorType manip(spReg);

				manip.setDirectMapping(_spDirectKernel);
				manip.setInverseMapping(_spInverseKernel);

				std::pair<std::string, std::string> taggedValue(_tag2, _value2);

				manip.getTagValues().insert(taggedValue);

				return spReg;
			};


			TestRegistrationGenerator2()
			{
				_spField3D = FRD3DType::New();
				_spDirectKernel = TestRegistrationKernel<2, 3>::New();
				_spInverseKernel = TestRegistrationKernel<3, 2>::New();
				_spInverseKernel->_spFieldRepresentation = _spField3D;

				_tag2 = "param2";
				_value2 = "value2";
			}

		};

		int mapRegistrationTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestRegistrationGenerator1 generator1;
			TestRegistrationGenerator2 generator2;
			TestRegistrationGenerator1::Registration1Pointer spReg1 = generator1.generate();
			TestRegistrationGenerator2::Registration2Pointer spReg2 = generator2.generate();

			CHECK_EQUAL(2, spReg1->getMovingDimensions());
			CHECK_EQUAL(2, spReg1->getTargetDimensions());
			CHECK_EQUAL(2, spReg2->getMovingDimensions());
			CHECK_EQUAL(3, spReg2->getTargetDimensions());

			CHECK_EQUAL(generator1._spField2D, spReg1->getDirectFieldRepresentation());
			CHECK(spReg1->getInverseFieldRepresentation().IsNull());
			CHECK(spReg2->getDirectFieldRepresentation().IsNull());
			CHECK_EQUAL(generator2._spField3D, spReg2->getInverseFieldRepresentation());

			CHECK_EQUAL(true, spReg1->hasLimitedMovingRepresentation());
			CHECK_EQUAL(false, spReg1->hasLimitedTargetRepresentation());
			CHECK_EQUAL(false, spReg2->hasLimitedMovingRepresentation());
			CHECK_EQUAL(true, spReg2->hasLimitedTargetRepresentation());

			std::string foundValue = "";
			CHECK_NO_THROW(spReg1->getTagValue(generator1._tag1, foundValue));
			CHECK_EQUAL(generator1._value1, foundValue);
			CHECK_NO_THROW(spReg2->getTagValue(generator2._tag2, foundValue));
			CHECK_EQUAL(generator2._value2, foundValue);
			CHECK_EQUAL(false, spReg2->getTagValue(generator1._tag1, foundValue));

			//Kernel function tests
			CHECK_EQUAL(generator1._spDirectKernel , &(spReg1->getDirectMapping()));
			CHECK_EQUAL(generator1._spInverseKernel , &(spReg1->getInverseMapping()));
			CHECK_EQUAL(generator2._spDirectKernel , &(spReg2->getDirectMapping()));
			CHECK_EQUAL(generator2._spInverseKernel , &(spReg2->getInverseMapping()));

			spReg1->precomputeInverseMapping();
			spReg2->precomputeDirectMapping();

			CHECK(!generator1._spDirectKernel->_isPreComputed);
			CHECK(generator1._spInverseKernel->_isPreComputed);
			CHECK(generator2._spDirectKernel->_isPreComputed);
			CHECK(!generator2._spInverseKernel->_isPreComputed);

			TestRegistrationGenerator1::Registration1Type::MovingPointType moving1;
			TestRegistrationGenerator1::Registration1Type::TargetPointType target1;

			moving1.Fill(1);

			TestRegistrationGenerator2::Registration2Type::MovingPointType moving2;
			TestRegistrationGenerator2::Registration2Type::TargetPointType target2;

			target2.Fill(3);

			spReg1->mapPoint(moving1, target1);
			spReg2->mapPointInverse(target2, moving2);

			CHECK(generator1._spDirectKernel->_hasMappedPoint);
			CHECK(!generator1._spInverseKernel->_hasMappedPoint);
			CHECK(!generator2._spDirectKernel->_hasMappedPoint);
			CHECK(generator2._spInverseKernel->_hasMappedPoint);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
