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
#include "mapFixedMVNLOptimizerPolicy.h"
#include "mapITKLevenbergMarquardtOptimizer.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TConcreteOptimizer>
			class TestPolicy : public algorithm::itk::FixedMVNLOptimizerPolicy<TConcreteOptimizer>
			{
				//derivered a test class to generate public constructors. The policy itsself cannot
				//be instantiated directly.
			public:
				using algorithm::itk::FixedMVNLOptimizerPolicy<TConcreteOptimizer>::getOptimizerInternal; //get internals visible
				using algorithm::itk::FixedMVNLOptimizerPolicy<TConcreteOptimizer>::getConcreteITKOptimizer; //get internals visible
				using algorithm::itk::FixedMVNLOptimizerPolicy<TConcreteOptimizer>::getConcreteOptimizerControl; //get internals visible
			};

		}

		int mapFixedMVNLOptimizerPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef TestPolicy< ::itk::LevenbergMarquardtOptimizer> PolicyType;

			PolicyType policy;
			const PolicyType& constPolicy = policy;

			::itk::LevenbergMarquardtOptimizer* pConcreteOptimizer = NULL;
			const ::itk::LevenbergMarquardtOptimizer* pConstConcreteOptimizer = NULL;

			::map::algorithm::itk::ITKOptimizerControl< ::itk::LevenbergMarquardtOptimizer>* pConcreteController =
				NULL;
			const algorithm::itk::ITKOptimizerControl< ::itk::LevenbergMarquardtOptimizer>*
			pConstConcreteController = NULL;

			const algorithm::itk::ITKOptimizerControlInterface* pConstController = NULL;
			const algorithm::OptimizerControlInterface* pConstControllerBase = NULL;

			::map::algorithm::itk::ITKOptimizerControlInterface* pController = NULL;
			::map::algorithm::OptimizerControlInterface* pControllerBase = NULL;

			CHECK_NO_THROW(pConcreteOptimizer = policy.getConcreteITKOptimizer());
			CHECK_NO_THROW(pConstConcreteOptimizer = constPolicy.getConcreteITKOptimizer());
			CHECK_NO_THROW(pConcreteController = policy.getConcreteOptimizerControl());
			CHECK_NO_THROW(pConstConcreteController = constPolicy.getConcreteOptimizerControl());
			CHECK_NO_THROW(pConstController = constPolicy.getITKOptimizerControl());
			CHECK_NO_THROW(pConstControllerBase = constPolicy.getOptimizerControl());
			CHECK_NO_THROW(pController = policy.getITKOptimizerControl());
			CHECK_NO_THROW(pControllerBase = policy.getOptimizerControl());

			CHECK(NULL != pConcreteOptimizer);
			CHECK_EQUAL(pConcreteOptimizer, pConstConcreteOptimizer);
			CHECK(NULL != pConcreteController);
			CHECK_EQUAL(pConcreteController, pConstConcreteController);
			CHECK_EQUAL(pConcreteController, pConstController);
			CHECK_EQUAL(pConcreteController, pConstControllerBase);
			CHECK_EQUAL(pConcreteController, pController);
			CHECK_EQUAL(pConcreteController, pControllerBase);

			CHECK(NULL != policy.getOptimizerInternal());
			CHECK(NULL != constPolicy.getOptimizerInternal());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
