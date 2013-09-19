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
#include "mapStateTestCommand.h"

#include "mapRegistrationAlgorithmBase.h"
#include "mapAlgorithmStateChangeEvent.h"

namespace map
{
	namespace testing
	{
		namespace
		{

			mapGenerateAlgorithmUIDPolicyMacro(TestRegistrationAlgorithmBaseUIDPolicy,
											   "de.dkfz.matchpoint.test", "TestRegistrationAlgorithmBase", "1", "");

			class TestRegistrationAlgorithmBase: public algorithm::RegistrationAlgorithmBase,
				public TestRegistrationAlgorithmBaseUIDPolicy
			{
			public:
				typedef TestRegistrationAlgorithmBase Self;
				typedef algorithm::RegistrationAlgorithmBase  Superclass;
				typedef itk::SmartPointer<Self>        Pointer;
				typedef itk::SmartPointer<const Self>  ConstPointer;

				typedef Superclass::AlgorithmType AlgorithmType;

				itkTypeMacro(TestRegistrationAlgorithmBase, RegistrationAlgorithmBase);
				mapNewAlgorithmMacro(Self);

				mapDefineAlgorithmIdentificationByPolicyMacro;

				virtual AlgorithmType getAlgorithmType() const
				{
					return Superclass::ATAnalytic;
				};

				mutable unsigned int _doDeterminRegistrationCall;

				unsigned int getMovingDimensions() const
				{
					return 3;
				};

				unsigned int getTargetDimensions() const
				{
					return 2;
				};

				bool isReusable() const
				{
					return true;
				};

				mutable unsigned int _onStateChange;
				mutable unsigned int _onConfigureAlgorithm;

				mutable AlgorithmState::Type _onStateChangeOldState;
				mutable AlgorithmState::Type _onStateChangeNewState;

				using Superclass::setCurrentState;

			protected:

				virtual bool doDetermineRegistration()
				{
					++_doDeterminRegistrationCall;
					return true;
				};

				TestRegistrationAlgorithmBase()
				{
					_doDeterminRegistrationCall = 0;
					_onStateChangeOldState = AlgorithmState::Pending;
					_onStateChangeNewState = AlgorithmState::Pending;
					_onStateChange = 0;
					_onConfigureAlgorithm = 0;
				};

				virtual ~TestRegistrationAlgorithmBase()
				{
				};

				virtual void onStateChange(AlgorithmState::Type oldState, AlgorithmState::Type newState) const
				{
					++_onStateChange;
					_onStateChangeOldState = oldState;
					_onStateChangeNewState = newState;
				}

				virtual void configureAlgorithm()
				{
					++_onConfigureAlgorithm;
				}

			private:
				TestRegistrationAlgorithmBase(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};
		}

		int mapRegistrationAlgorithmBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef TestRegistrationAlgorithmBase AlgorithmType;

			AlgorithmType::Pointer spRegAlg = AlgorithmType::New();

			//set event tester;
			StateTestCommand::Pointer spStateEventTest = StateTestCommand::New();

			spRegAlg->AddObserver(map::events::AlgorithmStateChangeEvent(), spStateEventTest);

			//test configureAlgorithmCall
			CHECK_EQUAL(1, spRegAlg->_onConfigureAlgorithm);

			//test determination interface
			spRegAlg->determineRegistration();
			CHECK_EQUAL(1, spRegAlg->_doDeterminRegistrationCall);
			CHECK_EQUAL(0, spStateEventTest->getEventCount());

			//test basic state interface (set and get)
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Pending,
						spRegAlg->getCurrentState());

			CHECK_NO_THROW(spRegAlg->setCurrentState(
							   algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing));
			CHECK_EQUAL(1, spRegAlg->_onStateChange);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Pending,
						spRegAlg->_onStateChangeOldState);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spRegAlg->_onStateChangeNewState);
			CHECK_EQUAL(1, spStateEventTest->getEventCount());
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Pending,
						spStateEventTest->_oldStates[0]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spStateEventTest->_newStates[0]);

			CHECK_NO_THROW(spRegAlg->setCurrentState(
							   algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping));
			CHECK_EQUAL(2, spRegAlg->_onStateChange);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spRegAlg->_onStateChangeOldState);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping,
						spRegAlg->_onStateChangeNewState);
			CHECK_EQUAL(2, spStateEventTest->getEventCount());
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spStateEventTest->_oldStates[1]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping,
						spStateEventTest->_newStates[1]);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
