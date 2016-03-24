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

#include "litCheckMacros.h"
#include "mapRegistrationAlgorithm.h"

namespace map
{
	namespace testing
	{
		namespace
		{
			mapGenerateAlgorithmUIDPolicyMacro(TestRegistrationAlgorithmUIDPolicy, "de.dkfz.matchpoint.test",
											   "TestRegistrationAlgorithm", "1", "");

			template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
			class TestRegistrationAlgorithm: public
				::map::algorithm::RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>,
			public TestRegistrationAlgorithmUIDPolicy
			{
			public:
				typedef TestRegistrationAlgorithm<VMovingDimensions, VTargetDimensions> Self;
				typedef algorithm::RegistrationAlgorithm<VMovingDimensions, VTargetDimensions>      Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;

				typedef typename Superclass::AlgorithmType AlgorithmType;
				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

				itkTypeMacro(TestRegistrationAlgorithm, RegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				mapDefineAlgorithmIdentificationByPolicyMacro;

				virtual AlgorithmType getAlgorithmType() const
				{
					return Superclass::ATAnalytic;
				};

				mutable unsigned int _doGetRegistration;
				mutable unsigned int _doDeterminRegistrationCall;
				RegistrationPointer _spRefRegistration;
				RegistrationPointer _spRegistration;

				typename FieldRepRequirement::Type isMovingRepresentationRequired() const
				{
					return FieldRepRequirement::No;
				};

				typename FieldRepRequirement::Type isTargetRepresentationRequired() const
				{
					return FieldRepRequirement::No;
				};

				bool isReusable() const
				{
					return true;
				};

			protected:

				virtual bool doDetermineRegistration()
				{
					_spRegistration = _spRefRegistration;
					++_doDeterminRegistrationCall;
					return true;
				};

				virtual RegistrationPointer doGetRegistration() const
				{
					++_doGetRegistration;
					return _spRegistration;
				};

				TestRegistrationAlgorithm()
				{
					_doDeterminRegistrationCall = 0;
					_doGetRegistration = 0;
					_spRegistration = NULL;
					_spRefRegistration = NULL;
				};

				virtual ~TestRegistrationAlgorithm()
				{
				};

				virtual void configureAlgorithm()
				{

				};

			private:
				TestRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};
		}

		int mapRegistrationAlgorithmTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef TestRegistrationAlgorithm<2, 3> AlgorithmType;

			AlgorithmType::Pointer spRegAlg = AlgorithmType::New();
			AlgorithmType::RegistrationPointer spReg = AlgorithmType::RegistrationType::New();
			AlgorithmType::MovingRepresentationDescriptorType::Pointer spMovingRep =
				AlgorithmType::MovingRepresentationDescriptorType::New();
			AlgorithmType::TargetRepresentationDescriptorType::Pointer spTargetRep =
				AlgorithmType::TargetRepresentationDescriptorType::New();

			CHECK_EQUAL(2, spRegAlg->getMovingDimensions());
			CHECK_EQUAL(3, spRegAlg->getTargetDimensions());

			spRegAlg->_spRefRegistration = spReg;

			CHECK_EQUAL(spReg.GetPointer(), spRegAlg->getRegistration().GetPointer());
			CHECK_EQUAL(1, spRegAlg->_doDeterminRegistrationCall);
			CHECK_EQUAL(2, spRegAlg->_doGetRegistration);

			CHECK_EQUAL(spReg.GetPointer(), spRegAlg->getRegistration().GetPointer());
			CHECK_EQUAL(1, spRegAlg->_doDeterminRegistrationCall);
			CHECK_EQUAL(4, spRegAlg->_doGetRegistration);

			spRegAlg->determineRegistration();
			CHECK_EQUAL(2, spRegAlg->_doDeterminRegistrationCall);

			CHECK(NULL == spRegAlg->getMovingRepresentation());
			CHECK(NULL == spRegAlg->getTargetRepresentation());

			spRegAlg->setMovingRepresentation(spMovingRep);
			spRegAlg->setTargetRepresentation(spTargetRep);

			CHECK_EQUAL(spMovingRep.GetPointer(), spRegAlg->getMovingRepresentation());
			CHECK_EQUAL(spTargetRep.GetPointer(), spRegAlg->getTargetRepresentation());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
