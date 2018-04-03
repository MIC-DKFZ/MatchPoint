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
#include "mapFixedImageToImageMetricPolicy.h"
#include "mapDiscreteElements.h"
#include "mapITKMeanSquaresImageToImageMetric.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TConcreteMetric>
			class TestPolicy : public algorithm::itk::FixedImageToImageMetricPolicy<TConcreteMetric>
			{
				//derivered a test class to generate public constructors. The policy itsself cannot
				//be instantiated directly.
			public:
				using algorithm::itk::FixedImageToImageMetricPolicy<TConcreteMetric>::getMetricInternal; //get internals visible
				using algorithm::itk::FixedImageToImageMetricPolicy<TConcreteMetric>::getConcreteMetricControl; //get internals visible
			};

		}

		int mapFixedImageToImageMetricPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef ::itk::MeanSquaresImageToImageMetric< ::map::core::discrete::Elements<3>::InternalImageType, core::discrete::Elements<3>::InternalImageType>
			MetricType;
			typedef algorithm::itk::ITKMetricControl<MetricType> MetricControlType;
			typedef TestPolicy< MetricType > PolicyType;

			PolicyType policy;
			const PolicyType& constPolicy = policy;

			MetricControlType* pConcreteMetricControl = NULL;
			const MetricControlType* pConstConcreteMetricControl = NULL;

			PolicyType::MetricType* pMetricControl = NULL;
			const PolicyType::MetricType* pConstMetricControl = NULL;

			CHECK_NO_THROW(pConcreteMetricControl = policy.getConcreteMetricControl());
			CHECK_NO_THROW(pConstConcreteMetricControl = constPolicy.getConcreteMetricControl());

			CHECK(NULL != pConcreteMetricControl);
			CHECK_EQUAL(pConcreteMetricControl, pConstConcreteMetricControl);
			CHECK_EQUAL(pConcreteMetricControl, policy.getMetricInternal());
			CHECK_EQUAL(pConstConcreteMetricControl, constPolicy.getMetricInternal());

			CHECK_NO_THROW(pMetricControl = policy.getMetricControl());
			CHECK_NO_THROW(pConstMetricControl = constPolicy.getMetricControl());

			CHECK(NULL != pMetricControl);
			CHECK_EQUAL(pMetricControl, pConstMetricControl);
			CHECK_EQUAL(pMetricControl, pConcreteMetricControl);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
