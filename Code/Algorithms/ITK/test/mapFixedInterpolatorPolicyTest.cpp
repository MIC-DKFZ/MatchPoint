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
#include "mapFixedInterpolatorPolicy.h"
#include "mapDiscreteElements.h"
#include "itkLinearInterpolateImageFunction.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TConcreteInterpolator>
			class TestPolicy : public algorithm::itk::FixedInterpolatorPolicy<TConcreteInterpolator>
			{
				//derivered a test class to generate public constructors. The policy itsself cannot
				//be instantiated directly.
			public:
				using algorithm::itk::FixedInterpolatorPolicy<TConcreteInterpolator>::getInterpolatorInternal; //get internals visible
				using algorithm::itk::FixedInterpolatorPolicy<TConcreteInterpolator>::getConcreteInterpolator; //get internals visible
			};

		}

		int mapFixedInterpolatorPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef ::itk::LinearInterpolateImageFunction< ::map::core::discrete::Elements<3>::InternalImageType, core::continuous::ScalarType>
			InterpolatorType;
			typedef TestPolicy< InterpolatorType > PolicyType;

			PolicyType policy;
			const PolicyType& constPolicy = policy;

			InterpolatorType* pConcreteInterpolator = NULL;
			const InterpolatorType* pConstConcreteInterpolator = NULL;

			PolicyType::InterpolatorType* pInterpolator = NULL;
			const PolicyType::InterpolatorType* pConstInterpolator = NULL;

			CHECK_NO_THROW(pConcreteInterpolator = policy.getConcreteInterpolator());
			CHECK_NO_THROW(pConstConcreteInterpolator = constPolicy.getConcreteInterpolator());

			CHECK(NULL != pConcreteInterpolator);
			CHECK_EQUAL(pConcreteInterpolator, pConstConcreteInterpolator);
			CHECK_EQUAL(pConcreteInterpolator, policy.getInterpolatorInternal());
			CHECK_EQUAL(pConstConcreteInterpolator, constPolicy.getInterpolatorInternal());

			CHECK_NO_THROW(pInterpolator = policy.getInterpolator());
			CHECK_NO_THROW(pConstInterpolator = constPolicy.getInterpolator());

			CHECK(NULL != pInterpolator);
			CHECK_EQUAL(pInterpolator, pConstInterpolator);
			CHECK_EQUAL(pConcreteInterpolator, pInterpolator);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
