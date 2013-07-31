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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/test/mapArbitraryPointSetToPointSetMetricPolicyTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litCheckMacros.h"
#include "mapDiscreteElements.h"
#include "mapArbitraryPointSetToPointSetMetricPolicy.h"
#include "mapITKEuclideanDistancePointMetric.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TTargetPointSet, class TMovingPointSet>
			class TestPolicy : public algorithm::itk::ArbitraryPointSetToPointSetMetricPolicy<TTargetPointSet, TMovingPointSet>
			{
				//derivered a test class to generate public constructors (The policy itsself cannot
				//be instantiated directly), to set the visibility of getMetricInternal to
				//public and to include internal event checks.
			public:
				using algorithm::itk::ArbitraryPointSetToPointSetMetricPolicy<TTargetPointSet, TMovingPointSet>::getMetricInternal;//get internals visible

				unsigned int _regEventCount;
				unsigned int _unregEventCount;

				TestPolicy()
				{
					typedef ::itk::ReceptorMemberCommand< TestPolicy<TTargetPointSet, TMovingPointSet> > AlgorithmCommandType;

					typename AlgorithmCommandType::Pointer spCmd = AlgorithmCommandType::New();
					spCmd->SetCallbackFunction(this, & TestPolicy<TTargetPointSet, TMovingPointSet>::onChange);
					this->_spOnChange = spCmd;

					_regEventCount = 0;
					_unregEventCount = 0;

				};

				void
				onChange(const ::itk::EventObject &eventObject)
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

		int mapArbitraryPointSetToPointSetMetricPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestPolicy<core::continuous::Elements<3>::InternalPointSetType, core::continuous::Elements<3>::InternalPointSetType> policy;
			const TestPolicy<core::continuous::Elements<3>::InternalPointSetType, core::continuous::Elements<3>::InternalPointSetType> &constPolicy = policy;

			typedef algorithm::itk::ITKMetricControl< ::itk::EuclideanDistancePointMetric<core::continuous::Elements<3>::InternalPointSetType, core::continuous::Elements<3>::InternalPointSetType> > MetricType;

			MetricType::Pointer spMetricControl1 = MetricType::New();
			MetricType::Pointer spMetricControl2 = MetricType::New();

			algorithm::itk::ITKPointSetToPointSetMetricControlInterface<core::continuous::Elements<3>::InternalPointSetType, core::continuous::Elements<3>::InternalPointSetType> *pMetricControl = NULL;
			const algorithm::itk::ITKPointSetToPointSetMetricControlInterface<core::continuous::Elements<3>::InternalPointSetType, core::continuous::Elements<3>::InternalPointSetType> *pConstMetricControl = NULL;

			CHECK_NO_THROW(pMetricControl = policy.getMetricInternal());
			CHECK_NO_THROW(pConstMetricControl = policy.getMetricInternal());

			CHECK(NULL == pMetricControl);
			CHECK(NULL == pConstMetricControl);

			CHECK_NO_THROW(policy.setMetricControl(spMetricControl1));

			CHECK_EQUAL(1, policy._unregEventCount);
			CHECK_EQUAL(1, policy._regEventCount);

			CHECK_NO_THROW(pMetricControl = policy.getMetricInternal());

			CHECK_EQUAL(spMetricControl1.GetPointer(), pMetricControl);

			CHECK_NO_THROW(policy.setMetricControl(spMetricControl2));

			CHECK_EQUAL(2, policy._unregEventCount);
			CHECK_EQUAL(2, policy._regEventCount);

			CHECK_NO_THROW(pMetricControl = policy.getMetricInternal());
			CHECK_NO_THROW(pConstMetricControl = constPolicy.getMetricInternal());

			CHECK_EQUAL(spMetricControl2.GetPointer(), pMetricControl);
			CHECK_EQUAL(spMetricControl2.GetPointer(), pConstMetricControl);

			CHECK_NO_THROW(pMetricControl = policy.getMetricControl());
			CHECK_NO_THROW(pConstMetricControl = constPolicy.getMetricControl());

			CHECK_EQUAL(spMetricControl2.GetPointer(), pMetricControl);
			CHECK_EQUAL(spMetricControl2.GetPointer(), pConstMetricControl);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
