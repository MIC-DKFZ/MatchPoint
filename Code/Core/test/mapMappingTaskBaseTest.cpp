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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapMappingTaskBaseTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapMappingTaskBase.h"
#include "mapTestMappingTask.h"
#include "mapRegistration.h"
#include "litCheckMacros.h"

namespace map
{
	namespace testing
	{

		int mapMappingTaskBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			typedef TestMappingTask<RegistrationType> MappingTaskType;

			MappingTaskType::Pointer spTask1 = MappingTaskType::New();
			MappingTaskType::Pointer spTask2 = MappingTaskType::New();
			RegistrationType::Pointer spRegistration = RegistrationType::New();

			spTask1->setIsExceptionNeutral(true);
			CHECK_EQUAL(true, spTask1->getIsExceptionNeutral());
			spTask2->setIsExceptionNeutral(false);
			CHECK_EQUAL(false, spTask2->getIsExceptionNeutral());

			spTask1->setRegistration(spRegistration);
			CHECK_EQUAL(1, spTask1->_clearResultsCount);
			spTask1->setRegistration(spRegistration);
			CHECK_EQUAL(1, spTask1->_clearResultsCount);

			CHECK_EQUAL(spRegistration.GetPointer(), spTask1->getRegistration());
			CHECK(spTask2->getRegistration() == NULL);

			CHECK(spTask1->getRegistrationException() == NULL);
			CHECK(spTask2->getRegistrationException() == NULL);

			spTask2->setRegistration(spRegistration);

			CHECK_EQUAL(true, spTask1->execute());
			CHECK_EQUAL(1, spTask1->_executionCount);
			CHECK_EQUAL(true, spTask2->execute());
			CHECK_EQUAL(1, spTask2->_executionCount);

			spTask1->_failExecution = true;
			spTask2->_failExecution = true;

			CHECK_THROW_EXPLICIT(spTask1->execute(), core::ExceptionObject);
			CHECK_EQUAL(2, spTask1->_executionCount);
			CHECK_EQUAL(false, spTask2->execute());
			CHECK_EQUAL(2, spTask2->_executionCount);
			CHECK(spTask2->getRegistrationException() != NULL);

			spTask2->reset();
			CHECK_EQUAL(2, spTask2->_clearResultsCount);
			CHECK_EQUAL(1, spTask2->_clearInputsCount);
			CHECK(spTask2->getRegistrationException() == NULL);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
