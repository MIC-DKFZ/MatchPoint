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

#include "mapPointSetMappingTask.h"
#include "mapRegistration.h"
#include "mapTestMappingPerformer.h"
#include "litCheckMacros.h"
#include "mapNoneMappingPerformerLoadPolicy.h"

namespace map
{
	namespace testing
	{

		int mapPointSetMappingTaskTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			typedef core::continuous::Elements<2>::InternalPointSetType InputDataType;
			typedef core::continuous::Elements<2>::InternalPointSetType OutputDataType;
			typedef core::PointSetMappingTask<RegistrationType, InputDataType, OutputDataType, core::NoneMappingPerformerLoadPolicy>
			MappingTaskType;
			typedef TestMappingPerformer<MappingTaskType::PerformerRequestType> TestPerformerType;

			MappingTaskType::Pointer spTask = MappingTaskType::New();
			TestPerformerType::Pointer spPerformer = TestPerformerType::New();
			InputDataType::Pointer spInput = InputDataType::New();
			OutputDataType::Pointer spReference = OutputDataType::New();
			RegistrationType::Pointer spRegistration = RegistrationType::New();

			MappingTaskType::ErrorPointValueType errorPointReference =
				itk::NumericTraits<MappingTaskType::ErrorPointValueType>::Zero;

			//Setting up test performer and adding to stack
			spPerformer->_spCurrentResult = spReference;
			MappingTaskType::TaskPerformerStackType::unregisterAll();
			MappingTaskType::TaskPerformerStackType::registerProvider(spPerformer);
			spTask->setRegistration(spRegistration);

			//check default values and setter/getter
			CHECK_EQUAL(true, spTask->getThrowOnMappingError());
			CHECK_EQUAL(errorPointReference, spTask->getErrorPointValue());

			CHECK_NO_THROW(spTask->setThrowOnMappingError(false));
			errorPointReference = 42.0;
			CHECK_NO_THROW(spTask->setErrorPointValue(errorPointReference));

			CHECK_EQUAL(false, spTask->getThrowOnMappingError());
			CHECK_EQUAL(errorPointReference, spTask->getErrorPointValue());


			//check for exception if called getResultPointSet without setting input
			CHECK_THROW_EXPLICIT(spTask->getResultPointSet(), core::ServiceException);

			//check for exception if no performer is available
			CHECK_NO_THROW(spTask->setInputPointSet(spInput));
			CHECK_THROW_EXPLICIT(spTask->getResultPointSet(), core::MissingProviderException);

			//check for right setting of the request and caching of the result (getResultPointSet)
			spPerformer->_handleRequest = true;
			OutputDataType::Pointer spResult;

			CHECK_NO_THROW(spResult = spTask->getResultPointSet());
			CHECK_EQUAL(spReference.GetPointer(), spResult.GetPointer());
			CHECK_EQUAL(false, spPerformer->_pCurrentRequest->_throwOnMappingError);
			CHECK_EQUAL(errorPointReference, spPerformer->_pCurrentRequest->_errorValue);
			CHECK_EQUAL(spRegistration.GetPointer(),
						spPerformer->_pCurrentRequest->_spRegistration.GetPointer());
			CHECK_EQUAL(spInput.GetPointer(), spPerformer->_pCurrentRequest->_spInputData.GetPointer());

			//check if registration is reperformed when input is unchanged
			spResult = NULL;
			CHECK_NO_THROW(spResult = spTask->getResultPointSet());
			CHECK_EQUAL(spReference.GetPointer(), spResult.GetPointer());
			CHECK_EQUAL(1, spPerformer->_performanceCount);
			//if this is correct the performer was never asked,
			//thus the task correctly never reperformed the mapping

			spTask->setInputPointSet(spInput);
			CHECK_NO_THROW(spResult = spTask->getResultPointSet());
			CHECK_EQUAL(1, spPerformer->_performanceCount);
			//if this is correct the performer was never asked,
			//thus setting the same input again will not force reperforming of the mapping

			spTask->setInputPointSet(InputDataType::New());
			CHECK_NO_THROW(spResult = spTask->getResultPointSet());
			CHECK_EQUAL(2, spPerformer->_performanceCount);
			//if this is correct the performer was never asked,
			//thus setting the same input again will not force reperforming of the mapping

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
