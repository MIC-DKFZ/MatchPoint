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
#include "mapArbitraryMVNLOptimizerPolicy.h"
#include "mapITKLevenbergMarquardtOptimizer.h"
#include "mapAlgorithmEvents.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			class TestPolicy : public algorithm::itk::ArbitraryMVNLOptimizerPolicy
			{
				//derivered a test class to generate public constructors (The policy itsself cannot
				//be instantiated directly), to set the visibility of getOptimizerInternal to
				//public and to include internal event checks.
			public:
				using algorithm::itk::ArbitraryMVNLOptimizerPolicy::getOptimizerInternal;

				unsigned int _regEventCount;
				unsigned int _unregEventCount;

				TestPolicy()
				{
					typedef ::itk::ReceptorMemberCommand< TestPolicy > AlgorithmCommandType;

					AlgorithmCommandType::Pointer spCmd = AlgorithmCommandType::New();
					spCmd->SetCallbackFunction(this, & TestPolicy::onChange);
					_spOnChange = spCmd;

					_regEventCount = 0;
					_unregEventCount = 0;

				};

				void
				onChange(const ::itk::EventObject& eventObject)
				{
					map::events::UnregisterAlgorithmComponentEvent unregEvent;
					map::events::RegisterAlgorithmComponentEvent regEvent;

					if (unregEvent.CheckEvent(&eventObject))
					{
						++_unregEventCount;
					}

					if (regEvent.CheckEvent(&eventObject))
					{
						++_regEventCount;
					}
				};
			};

		}

		int mapArbitraryMVNLOptimizerPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestPolicy policy;
			const TestPolicy& constPolicy = policy;

			typedef algorithm::itk::ITKOptimizerControl< ::itk::LevenbergMarquardtOptimizer> AControlType;

			AControlType::Pointer spAControl = AControlType::New();
			AControlType::Pointer spBControl = AControlType::New();

			::map::algorithm::itk::ITKMVNLOptimizerControlInterface* pController = NULL;
			const algorithm::itk::ITKMVNLOptimizerControlInterface* pConstController = NULL;

			::map::algorithm::OptimizerControlInterface* pControllerBase = NULL;
			const algorithm::OptimizerControlInterface* pConstControllerBase = NULL;

			CHECK_NO_THROW(pController = policy.getITKOptimizerControl());
			CHECK_NO_THROW(pConstController = constPolicy.getITKOptimizerControl());

			CHECK_NO_THROW(pControllerBase = policy.getOptimizerControl());
			CHECK_NO_THROW(pConstControllerBase = constPolicy.getOptimizerControl());


			CHECK(NULL == pController);
			CHECK(NULL == pConstController);

			CHECK_NO_THROW(policy.setITKOptimizerControl(spAControl));

			CHECK_EQUAL(1, policy._unregEventCount);
			CHECK_EQUAL(1, policy._regEventCount);

			CHECK_NO_THROW(pController = policy.getITKOptimizerControl());
			CHECK_NO_THROW(pConstController = constPolicy.getITKOptimizerControl());

			CHECK_NO_THROW(pControllerBase = policy.getOptimizerControl());
			CHECK_NO_THROW(pConstControllerBase = constPolicy.getOptimizerControl());

			CHECK_EQUAL(spAControl.GetPointer(), pController);
			CHECK_EQUAL(spAControl.GetPointer(), pConstController);
			CHECK_EQUAL(spAControl.GetPointer(), pControllerBase);
			CHECK_EQUAL(spAControl.GetPointer(), pConstControllerBase);
			CHECK_EQUAL(spAControl.GetPointer(), policy.getOptimizerInternal());
			CHECK_EQUAL(spAControl.GetPointer(), constPolicy.getOptimizerInternal());

			CHECK_NO_THROW(policy.setITKOptimizerControl(spBControl));

			CHECK_EQUAL(2, policy._unregEventCount);
			CHECK_EQUAL(2, policy._regEventCount);

			CHECK_NO_THROW(pController = policy.getITKOptimizerControl());
			CHECK_NO_THROW(pConstController = constPolicy.getITKOptimizerControl());
			CHECK_NO_THROW(pControllerBase = policy.getOptimizerControl());
			CHECK_NO_THROW(pConstControllerBase = constPolicy.getOptimizerControl());

			CHECK_EQUAL(spBControl.GetPointer(), pController);
			CHECK_EQUAL(spBControl.GetPointer(), pConstController);
			CHECK_EQUAL(spBControl.GetPointer(), pControllerBase);
			CHECK_EQUAL(spBControl.GetPointer(), pConstControllerBase);
			CHECK_EQUAL(spBControl.GetPointer(), policy.getOptimizerInternal());
			CHECK_EQUAL(spBControl.GetPointer(), constPolicy.getOptimizerInternal());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
