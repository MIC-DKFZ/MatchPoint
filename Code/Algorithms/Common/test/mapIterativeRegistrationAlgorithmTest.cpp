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
#include "litTestCommand.h"
#include "mapIterativeRegistrationAlgorithm.h"
#include "mapStateTestCommand.h"

namespace map
{
	namespace testing
	{
		namespace
		{

			mapGenerateAlgorithmUIDPolicyMacro(IterativeTestUIDPolicy, "de.dkfz.matchpoint.test",
											   "TestIterativeRegistrationAlgorithm", "1", "");

			template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
			class TestIterativeRegistrationAlgorithm: public
				algorithm::IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions>,
			public IterativeTestUIDPolicy
			{
			public:
				typedef TestIterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions> Self;
				typedef algorithm::IterativeRegistrationAlgorithm<VMovingDimensions, VTargetDimensions> Superclass;
				typedef itk::SmartPointer<Self>     Pointer;

				typedef typename Superclass::AlgorithmType AlgorithmType;
				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;
				typedef typename Superclass::IterationCountType IterationCountType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

				mapNewAlgorithmMacro(Self);

				mapDefineAlgorithmIdentificationByPolicyMacro;

				mutable unsigned int _prepareAlgorithm;
				mutable unsigned int _runAlgorithm;
				mutable unsigned int _finalizeAlgorithm;
				mutable unsigned int _determineInterimRegistration;
				mutable unsigned int _doGetCurrentOptimizerValue;
				mutable unsigned int _doStopAlgorithm;

				bool _iterationSuccess;

				bool _hasCurrentValue;

				bool _stopResult;
				bool _isStoppable;

				RegistrationPointer _spRefRegistration;

				mutable typename MovingRepresentationDescriptorType::ConstPointer smpInterimMovingRep;
				mutable typename TargetRepresentationDescriptorType::ConstPointer smpInterimTargetRep;

				virtual bool isStoppable() const
				{
					return _isStoppable;
				}

				virtual IterationCountType doGetCurrentIteration() const
				{
					return 0;
				}

				virtual bool hasIterationCount() const
				{
					return false;
				}

				virtual bool hasMaxIterationCount() const
				{
					return false;
				}

				virtual IterationCountType doGetMaxIterations() const
				{
					return 0;
				}

				virtual bool hasCurrentOptimizerValue() const
				{
					return _hasCurrentValue;
				};

				typename FieldRepRequirement::Type isMovingRepresentationRequired() const
				{
					return FieldRepRequirement::No;
				};

				typename FieldRepRequirement::Type isTargetRepresentationRequired() const
				{
					return FieldRepRequirement::No;
				};

				using Superclass::setCurrentState;

				bool isReusable() const
				{
					return true;
				}

			protected:
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;
				typedef typename Superclass::OptimizerMeasureType OptimizerMeasureType;

				virtual InterimRegistrationPointer determineInterimRegistration(const
						MovingRepresentationDescriptorType* pMovingRepresentation,
						const TargetRepresentationDescriptorType* pTargetRepresentation) const
				{
					smpInterimMovingRep = pMovingRepresentation;
					smpInterimTargetRep = pTargetRepresentation;
					InterimRegistrationPointer dummy;
					++_determineInterimRegistration;

					return dummy;
				};

				virtual void prepareAlgorithm()
				{
					++_prepareAlgorithm;
				};

				virtual bool runAlgorithm()
				{
					++_runAlgorithm;
					return _iterationSuccess;
				}

				virtual void finalizeAlgorithm()
				{
					++_finalizeAlgorithm;
				};

				virtual bool doStopAlgorithm()
				{
					++_doStopAlgorithm;
					return _stopResult;
				}

				TestIterativeRegistrationAlgorithm() : _prepareAlgorithm(0), _runAlgorithm(0),
					_finalizeAlgorithm(0), _determineInterimRegistration(0), _doGetCurrentOptimizerValue(0),
					_doStopAlgorithm(0)
				{
					_iterationSuccess = true;
					_hasCurrentValue = true;
					_stopResult = true;
					_isStoppable = true;
				};

				virtual ~TestIterativeRegistrationAlgorithm() {};

				virtual void configureAlgorithm()
				{
				};

				virtual RegistrationPointer doGetRegistration() const
				{
					return _spRefRegistration;
				};

				virtual OptimizerMeasureType doGetCurrentOptimizerValue() const
				{
					++_doGetCurrentOptimizerValue;
					OptimizerMeasureType result;
					result.push_back(42);
					return result;
				};

			private:
				//No copy constructor allowed
				Self& IterativeRegistrationAlgorithmInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};


		}

		int mapIterativeRegistrationAlgorithmTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef TestIterativeRegistrationAlgorithm<2, 3> AlgorithmType;

			AlgorithmType::Pointer spRegAlg = AlgorithmType::New();
			AlgorithmType::RegistrationPointer spReg = AlgorithmType::RegistrationType::New();
			AlgorithmType::MovingRepresentationDescriptorType::Pointer spMovingRep =
				AlgorithmType::MovingRepresentationDescriptorType::New();
			AlgorithmType::TargetRepresentationDescriptorType::Pointer spTargetRep =
				AlgorithmType::TargetRepresentationDescriptorType::New();
			AlgorithmType::MovingRepresentationDescriptorType::Pointer spMovingRepRef =
				AlgorithmType::MovingRepresentationDescriptorType::New();
			AlgorithmType::TargetRepresentationDescriptorType::Pointer spTargetRepRef =
				AlgorithmType::TargetRepresentationDescriptorType::New();

			spRegAlg->_spRefRegistration = spReg;
			spRegAlg->setMovingRepresentation(spMovingRepRef);
			spRegAlg->setTargetRepresentation(spTargetRepRef);

			//set event tester;
			lit::TestCommand::Pointer spInitEventTest = lit::TestCommand::New();
			lit::TestCommand::Pointer spStartingEventTest = lit::TestCommand::New();
			lit::TestCommand::Pointer spStoppedEventTest = lit::TestCommand::New();
			lit::TestCommand::Pointer spFinalizingEventTest = lit::TestCommand::New();
			lit::TestCommand::Pointer spFinalizedEventTest = lit::TestCommand::New();
			StateTestCommand::Pointer spStateEventTest = StateTestCommand::New();

			spRegAlg->AddObserver(events::InitializingAlgorithmEvent(), spInitEventTest);
			spRegAlg->AddObserver(events::StartingAlgorithmEvent(), spStartingEventTest);
			spRegAlg->AddObserver(events::StoppedAlgorithmEvent(), spStoppedEventTest);
			spRegAlg->AddObserver(events::FinalizingAlgorithmEvent(), spFinalizingEventTest);
			spRegAlg->AddObserver(events::FinalizedAlgorithmEvent(), spFinalizedEventTest);
			spRegAlg->AddObserver(events::AlgorithmStateChangeEvent(), spStateEventTest);

			//check algorithm type
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::ATIterative, spRegAlg->getAlgorithmType());

			//Interim results
			CHECK_NO_THROW(spRegAlg->getInterimRegistration());
			CHECK_EQUAL(spMovingRepRef.GetPointer(), spRegAlg->smpInterimMovingRep.GetPointer());
			CHECK_EQUAL(spTargetRepRef.GetPointer(), spRegAlg->smpInterimTargetRep.GetPointer());
			CHECK_EQUAL(1, spRegAlg->_determineInterimRegistration);

			CHECK_NO_THROW(spRegAlg->getInterimRegistration(spMovingRep, spTargetRep));
			CHECK_EQUAL(spMovingRep.GetPointer(), spRegAlg->smpInterimMovingRep.GetPointer());
			CHECK_EQUAL(spTargetRep.GetPointer(), spRegAlg->smpInterimTargetRep.GetPointer());
			CHECK_EQUAL(2, spRegAlg->_determineInterimRegistration);

			//determination with iteration success
			CHECK_NO_THROW(spRegAlg->determineRegistration());
			CHECK_EQUAL(1, spRegAlg->_prepareAlgorithm);
			CHECK_EQUAL(1, spRegAlg->_runAlgorithm);
			CHECK_EQUAL(1, spRegAlg->_finalizeAlgorithm);

			CHECK_EQUAL(9, spStateEventTest->getLastCallOrder());
			CHECK_EQUAL(2, spInitEventTest->getLastCallOrder());
			CHECK_EQUAL(4, spStartingEventTest->getLastCallOrder());
			CHECK_EQUAL(6, spStoppedEventTest->getLastCallOrder());
			CHECK_EQUAL(8, spFinalizingEventTest->getLastCallOrder());
			CHECK_EQUAL(10, spFinalizedEventTest->getLastCallOrder());

			CHECK_EQUAL(5, spStateEventTest->getEventCount());

			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Pending,
						spStateEventTest->_oldStates[0]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spStateEventTest->_newStates[0]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spStateEventTest->_oldStates[1]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Running,
						spStateEventTest->_newStates[1]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Running,
						spStateEventTest->_oldStates[2]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopped,
						spStateEventTest->_newStates[2]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopped,
						spStateEventTest->_oldStates[3]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalizing,
						spStateEventTest->_newStates[3]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalizing,
						spStateEventTest->_oldStates[4]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalized,
						spStateEventTest->_newStates[4]);

			//determination with iteration failure
			lit::TestCommand::resetCallOrder();
			spStateEventTest->_oldStates.clear();
			spStateEventTest->_newStates.clear();
			spRegAlg->_iterationSuccess = false;

			CHECK_NO_THROW(spRegAlg->determineRegistration());
			CHECK_EQUAL(2, spRegAlg->_prepareAlgorithm);
			CHECK_EQUAL(2, spRegAlg->_runAlgorithm);
			CHECK_EQUAL(1, spRegAlg->_finalizeAlgorithm);

			CHECK_EQUAL(5, spStateEventTest->getLastCallOrder());
			CHECK_EQUAL(2, spInitEventTest->getLastCallOrder());
			CHECK_EQUAL(4, spStartingEventTest->getLastCallOrder());
			CHECK_EQUAL(6, spStoppedEventTest->getLastCallOrder());

			CHECK_EQUAL(8, spStateEventTest->getEventCount());

			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalized,
						spStateEventTest->_oldStates[0]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spStateEventTest->_newStates[0]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spStateEventTest->_oldStates[1]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Running,
						spStateEventTest->_newStates[1]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Running,
						spStateEventTest->_oldStates[2]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopped,
						spStateEventTest->_newStates[2]);

			//test getCurrentOptimizerValue
			CHECK(spRegAlg->hasCurrentOptimizerValue());
			CHECK_EQUAL(0, spRegAlg->_doGetCurrentOptimizerValue);
			CHECK_EQUAL(42, (spRegAlg->getCurrentOptimizerValue())[0]);
			CHECK_EQUAL(1, spRegAlg->_doGetCurrentOptimizerValue);

			spRegAlg->_hasCurrentValue = false;
			CHECK(!spRegAlg->hasCurrentOptimizerValue());
			CHECK_EQUAL(0, (spRegAlg->getCurrentOptimizerValue()).size());
			CHECK_EQUAL(1, spRegAlg->_doGetCurrentOptimizerValue); //function wasn't called at all

			//////////////////////////////////////////////
			//test implementation of the stop interface
			AlgorithmType::Pointer spRegAlg2 = AlgorithmType::New();
			StateTestCommand::Pointer spStateEventTest2 = StateTestCommand::New();
			spRegAlg2->AddObserver(events::AlgorithmStateChangeEvent(), spStateEventTest2);

			spRegAlg2->_stopResult = false;

			//test if algorithm is not stopped because it is still pending
			CHECK_EQUAL(false, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(0, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Pending,
						spRegAlg2->getCurrentState());

			spRegAlg2->setCurrentState(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing);
			CHECK_EQUAL(1, spStateEventTest2->getEventCount());

			//test if algorithm tries to stop, but didnt, because doStopAlgorithm returns false;
			CHECK_EQUAL(false, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(1, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spRegAlg2->getCurrentState());
			CHECK_EQUAL(1, spStateEventTest2->getEventCount());

			//test if algorithm tries to stop, but didnt, because doStopAlgorithm returns false;
			spRegAlg2->setCurrentState(algorithm::RegistrationAlgorithmBase::AlgorithmState::Running);
			CHECK_EQUAL(2, spStateEventTest2->getEventCount());

			CHECK_EQUAL(false, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(2, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Running,
						spRegAlg2->getCurrentState());

			//test if algorithm stops, if running
			spRegAlg2->_stopResult = true;

			CHECK_EQUAL(true, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(3, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(3, spStateEventTest2->getEventCount());
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping,
						spRegAlg2->getCurrentState());
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Running,
						spStateEventTest2->_oldStates[2]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping,
						spStateEventTest2->_newStates[2]);

			//test if algorithm stops, if initializing
			spRegAlg2->setCurrentState(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing);

			CHECK_EQUAL(true, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(4, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(5, spStateEventTest2->getEventCount());
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping,
						spRegAlg2->getCurrentState());
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Initializing,
						spStateEventTest2->_oldStates[4]);
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping,
						spStateEventTest2->_newStates[4]);

			//test if algorithm does nothing if he is already stopping and should be stopped again.
			CHECK_EQUAL(true, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(4, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(5, spStateEventTest2->getEventCount());
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopping,
						spRegAlg2->getCurrentState());

			//test if algorithm does nothing if he is already stopped and should be stopped again.
			spRegAlg2->setCurrentState(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopped);
			CHECK_EQUAL(true, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(4, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(6, spStateEventTest2->getEventCount()); //changed because of setCurrentState()
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Stopped,
						spRegAlg2->getCurrentState());

			//test if algorithm does nothing if he is already finalizing and should be stopped again.
			spRegAlg2->setCurrentState(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalizing);
			CHECK_EQUAL(true, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(4, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(7, spStateEventTest2->getEventCount()); //changed because of setCurrentState()
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalizing,
						spRegAlg2->getCurrentState());

			//test if algorithm does nothing if he is already finalized and should be stopped again.
			spRegAlg2->setCurrentState(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalized);
			CHECK_EQUAL(true, spRegAlg2->stopAlgorithm());
			CHECK_EQUAL(4, spRegAlg2->_doStopAlgorithm);
			CHECK_EQUAL(8, spStateEventTest2->getEventCount()); //changed because of setCurrentState()
			CHECK_EQUAL(algorithm::RegistrationAlgorithmBase::AlgorithmState::Finalized,
						spRegAlg2->getCurrentState());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
