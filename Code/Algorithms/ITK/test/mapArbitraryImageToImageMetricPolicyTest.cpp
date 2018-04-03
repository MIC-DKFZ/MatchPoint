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
#include "mapDiscreteElements.h"
#include "mapArbitraryImageToImageMetricPolicy.h"
#include "mapITKMeanSquaresImageToImageMetric.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TTargetImage, class TMovingImage>
			class TestPolicy : public
				::map::algorithm::itk::ArbitraryImageToImageMetricPolicy<TTargetImage, TMovingImage>
			{
				//derivered a test class to generate public constructors (The policy itsself cannot
				//be instantiated directly), to set the visibility of getMetricInternal to
				//public and to include internal event checks.
			public:
				using algorithm::itk::ArbitraryImageToImageMetricPolicy<TTargetImage, TMovingImage>::getMetricInternal;//get internals visible

				unsigned int _regEventCount;
				unsigned int _unregEventCount;

				TestPolicy()
				{
					typedef ::itk::ReceptorMemberCommand< TestPolicy<TTargetImage, TMovingImage> > AlgorithmCommandType;

					typename AlgorithmCommandType::Pointer spCmd = AlgorithmCommandType::New();
					spCmd->SetCallbackFunction(this, & TestPolicy<TTargetImage, TMovingImage>::onChange);
					this->_spOnChange = spCmd;

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

		int mapArbitraryImageToImageMetricPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestPolicy< ::map::core::discrete::Elements<3>::InternalImageType, core::discrete::Elements<3>::InternalImageType>
			policy;
			const TestPolicy< ::map::core::discrete::Elements<3>::InternalImageType, core::discrete::Elements<3>::InternalImageType>
			& constPolicy = policy;

			typedef algorithm::itk::ITKMetricControl< ::itk::MeanSquaresImageToImageMetric< ::map::core::discrete::Elements<3>::InternalImageType, core::discrete::Elements<3>::InternalImageType> >
			MetricType;

			MetricType::Pointer spMetricControl1 = MetricType::New();
			MetricType::Pointer spMetricControl2 = MetricType::New();

			::map::algorithm::itk::ITKImageToImageMetricControlInterface< ::map::core::discrete::Elements<3>::InternalImageType, core::discrete::Elements<3>::InternalImageType>
			* pMetricControl = NULL;
			const algorithm::itk::ITKImageToImageMetricControlInterface< ::map::core::discrete::Elements<3>::InternalImageType, core::discrete::Elements<3>::InternalImageType>
			* pConstMetricControl = NULL;

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
