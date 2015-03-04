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

#include "itkScaleTransform.h"

#include "litCheckMacros.h"
#include "mapFixedTransformPolicy.h"
#include "mapDiscrete.h"
#include "mapContinuousElements.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TConcreteTransform>
			class TestPolicy : public algorithm::itk::FixedTransformPolicy<TConcreteTransform>
			{
				//derivered a test class to generate public constructors. The policy itsself cannot
				//be instantiated directly.
			public:
				using algorithm::itk::FixedTransformPolicy<TConcreteTransform>::getTransformInternal; //get internals visible
				using algorithm::itk::FixedTransformPolicy<TConcreteTransform>::getConcreteTransformModel; //get internals visible
			};

		}

		int mapFixedTransformPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef ::itk::ScaleTransform<core::continuous::ScalarType, 2> TransformType;
			typedef TestPolicy< TransformType > PolicyType;
			typedef PolicyType::ConcreteTransformType ModelType;

			PolicyType policy;
			const PolicyType& constPolicy = policy;

			ModelType* pConcreteModel = NULL;
			const ModelType* pConstConcreteModel = NULL;

			PolicyType::TransformType* pTransform = NULL;
			const PolicyType::TransformType* pConstTransform = NULL;

			CHECK_NO_THROW(pConcreteModel = policy.getConcreteTransformModel());
			CHECK_NO_THROW(pConstConcreteModel = constPolicy.getConcreteTransformModel());

			CHECK(NULL != pConcreteModel);
			CHECK_EQUAL(pConcreteModel, pConstConcreteModel);
			CHECK_EQUAL(pConcreteModel, policy.getTransformInternal());
			CHECK_EQUAL(pConstConcreteModel, constPolicy.getTransformInternal());

			CHECK_NO_THROW(pTransform = policy.getTransformModel());
			CHECK_NO_THROW(pConstTransform = constPolicy.getTransformModel());

			CHECK(NULL != pTransform);
			CHECK_EQUAL(pTransform, pConstTransform);
			CHECK_EQUAL(pTransform, pConcreteModel);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
