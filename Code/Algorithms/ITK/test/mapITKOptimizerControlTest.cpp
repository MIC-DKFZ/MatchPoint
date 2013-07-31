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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/test/mapITKOptimizerControlTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litCheckMacros.h"
#include "mapITKAmoebaOptimizer.h"

namespace map
{
	namespace testing
	{

		int mapITKOptimizerControlTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef algorithm::itk::ITKOptimizerControl< ::itk::AmoebaOptimizer> ControlType;

			::itk::AmoebaOptimizer *pConcreteOptimizer;
			::itk::Optimizer *pOptimizerBase;
			const ::itk::AmoebaOptimizer *pConstConcreteOptimizer;
			const ::itk::Optimizer *pConstOptimizerBase;

			ControlType::Pointer spControl = ControlType::New();
			::itk::AmoebaOptimizer::Pointer spAmoeba = ::itk::AmoebaOptimizer::New();

			CHECK_NO_THROW(pConcreteOptimizer = spControl->getConcreteOptimizer());
			CHECK_NO_THROW(pConstConcreteOptimizer = spControl->getConcreteOptimizer());
			CHECK_NO_THROW(pOptimizerBase = spControl->getOptimizer());
			CHECK_NO_THROW(pConstOptimizerBase = spControl->getOptimizer());

			CHECK(NULL != pConcreteOptimizer);
			CHECK_EQUAL(pConcreteOptimizer, pConstConcreteOptimizer);
			CHECK_EQUAL(pConcreteOptimizer, pOptimizerBase);
			CHECK_EQUAL(pConcreteOptimizer, pConstOptimizerBase);

			CHECK_NO_THROW(spControl->setOptimizer(spAmoeba));

			CHECK_NO_THROW(pConcreteOptimizer = spControl->getConcreteOptimizer());
			CHECK_NO_THROW(pConstConcreteOptimizer = spControl->getConcreteOptimizer());
			CHECK_NO_THROW(pOptimizerBase = spControl->getOptimizer());
			CHECK_NO_THROW(pConstOptimizerBase = spControl->getOptimizer());

			CHECK_EQUAL(spAmoeba.GetPointer(), pConcreteOptimizer);
			CHECK_EQUAL(pConcreteOptimizer, pConstConcreteOptimizer);
			CHECK_EQUAL(pConcreteOptimizer, pOptimizerBase);
			CHECK_EQUAL(pConcreteOptimizer, pConstOptimizerBase);

			CHECK_THROW_EXPLICIT(spControl->setOptimizer(NULL), ::map::core::ExceptionObject);

			CHECK_EQUAL(false, spControl->isStoppable());
			CHECK_EQUAL(false, spControl->stop());
			CHECK_EQUAL(false, spControl->hasIterationCount());
			CHECK_EQUAL(0, spControl->getCurrentIteration());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
