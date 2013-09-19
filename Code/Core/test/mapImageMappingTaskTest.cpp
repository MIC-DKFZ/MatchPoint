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

#include "mapImageMappingTask.h"
#include "mapRegistration.h"
#include "mapTestMappingPerformer.h"
#include "litCheckMacros.h"
#include "mapNoneMappingPerformerLoadPolicy.h"

namespace map
{
	namespace testing
	{

		int mapImageMappingTaskTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			typedef core::discrete::Elements<2>::InternalImageType InputDataType;
			typedef core::discrete::Elements<2>::InternalImageType OutputDataType;
			typedef core::ImageMappingTask<RegistrationType, InputDataType, OutputDataType, core::NoneMappingPerformerLoadPolicy>
			MappingTaskType;
			typedef TestMappingPerformer<MappingTaskType::PerformerRequestType, core::ImageMappingPerformerBase<RegistrationType, InputDataType, OutputDataType> >
			TestPerformerType;
			typedef itk::LinearInterpolateImageFunction<InputDataType, core::continuous::ScalarType>
			InterpolatorType;

			MappingTaskType::Pointer spTask = MappingTaskType::New();
			TestPerformerType::Pointer spPerformer = TestPerformerType::New();
			InputDataType::Pointer spInput = InputDataType::New();
			OutputDataType::Pointer spReference = OutputDataType::New();
			RegistrationType::Pointer spRegistration = RegistrationType::New();
			MappingTaskType::InterpolateBaseType::Pointer spInterpolator = InterpolatorType::New().GetPointer();
			MappingTaskType::ResultImageDescriptorType::Pointer spResultDescriptor =
				core::createFieldRepresentation(*spInput);

			MappingTaskType::ErrorValueType errorReference =
				itk::NumericTraits<MappingTaskType::ErrorValueType>::Zero;
			MappingTaskType::PaddingValueType paddingReference =
				itk::NumericTraits<MappingTaskType::PaddingValueType>::Zero;

			//Setting up test performer and adding to stack
			spPerformer->_spCurrentResult = spReference;
			MappingTaskType::TaskPerformerStackType::unregisterAll();
			MappingTaskType::TaskPerformerStackType::registerProvider(spPerformer.GetPointer());
			spTask->setRegistration(spRegistration);

			//check default values and setter/getter
			CHECK_EQUAL(true, spTask->getThrowOnMappingError());
			CHECK_EQUAL(errorReference, spTask->getErrorValue());
			CHECK_EQUAL(false, spTask->getThrowOnPaddingError());
			CHECK_EQUAL(paddingReference, spTask->getPaddingValue());
			CHECK(spTask->getImageInterpolator() != NULL);

			CHECK_NO_THROW(spTask->setThrowOnMappingError(false));
			errorReference = 42.0;
			CHECK_NO_THROW(spTask->setErrorValue(errorReference));
			CHECK_NO_THROW(spTask->setThrowOnPaddingError(true));
			paddingReference = 22.0;
			CHECK_NO_THROW(spTask->setPaddingValue(paddingReference));
			CHECK_NO_THROW(spTask->setImageInterpolator(spInterpolator));
			CHECK_NO_THROW(spTask->setResultImageDescriptor(spResultDescriptor));

			CHECK_EQUAL(false, spTask->getThrowOnMappingError());
			CHECK_EQUAL(errorReference, spTask->getErrorValue());
			CHECK_EQUAL(true, spTask->getThrowOnPaddingError());
			CHECK_EQUAL(paddingReference, spTask->getPaddingValue());
			CHECK_EQUAL(spInterpolator.GetPointer(), spTask->getImageInterpolator());

			//check for exception if called getResultImage without setting input
			CHECK_THROW_EXPLICIT(spTask->getResultImage(), core::ServiceException);

			//check for exception if called getResultImage without an interpolator
			spTask->setInputImage(spInput);
			spTask->setImageInterpolator(NULL);
			CHECK_THROW_EXPLICIT(spTask->getResultImage(), core::ServiceException);

			//check for exception if no performer is available
			spTask->setImageInterpolator(spInterpolator);
			CHECK_THROW_EXPLICIT(spTask->getResultImage(), core::MissingProviderException);

			//check for right setting of the request and caching of the result (getResultImage)
			spPerformer->_handleRequest = true;
			OutputDataType::Pointer spResult;

			CHECK_NO_THROW(spResult = spTask->getResultImage());
			CHECK_EQUAL(spReference.GetPointer(), spResult.GetPointer());
			CHECK_EQUAL(false, spPerformer->_pCurrentRequest->_throwOnMappingError);
			CHECK_EQUAL(errorReference, spPerformer->_pCurrentRequest->_errorValue);
			CHECK_EQUAL(true, spPerformer->_pCurrentRequest->_throwOnOutOfInputAreaError);
			CHECK_EQUAL(paddingReference, spPerformer->_pCurrentRequest->_paddingValue);
			CHECK_EQUAL(spRegistration.GetPointer(),
						spPerformer->_pCurrentRequest->_spRegistration.GetPointer());
			CHECK_EQUAL(spInput.GetPointer(), spPerformer->_pCurrentRequest->_spInputData.GetPointer());
			CHECK_EQUAL(spInterpolator.GetPointer(),
						spPerformer->_pCurrentRequest->_spInterpolateFunction.GetPointer());
			CHECK((*spResultDescriptor) == *(spPerformer->_pCurrentRequest->_spResultDescriptor.GetPointer()));

			//check if registration is reperformed when input, representation, and interpolator is unchanged
			spResult = NULL;
			CHECK_NO_THROW(spResult = spTask->getResultImage());
			CHECK_EQUAL(spReference.GetPointer(), spResult.GetPointer());
			CHECK_EQUAL(1, spPerformer->_performanceCount);
			//if this is correct the performer was never asked,
			//thus the task correctly never reperformed the mapping

			spTask->setInputImage(spInput);
			CHECK_NO_THROW(spResult = spTask->getResultImage());
			CHECK_EQUAL(1, spPerformer->_performanceCount);
			//if this is correct the performer was never asked,
			//thus setting the same input again will not force reperforming of the mapping

			spTask->setInputImage(InputDataType::New());
			CHECK_NO_THROW(spResult = spTask->getResultImage());
			CHECK_EQUAL(2, spPerformer->_performanceCount);

			spResult = spTask->getResultImage(); //no reperforming

			CHECK_EQUAL(2, spPerformer->_performanceCount);

			CHECK_NO_THROW(spTask->setResultImageDescriptor(NULL));
			CHECK_NO_THROW(spResult = spTask->getResultImage());

			CHECK_EQUAL(3, spPerformer->_performanceCount); //reperforming because result representation changed

			CHECK_NO_THROW(spTask->setResultImageDescriptor(NULL));
			CHECK_NO_THROW(spResult = spTask->getResultImage());

			CHECK_EQUAL(3,
						spPerformer->_performanceCount); // no reperforming because result representation was not realy changed


			MappingTaskType::InterpolateBaseType::Pointer spInterpolator2 =
				InterpolatorType::New().GetPointer();
			CHECK_NO_THROW(spTask->setImageInterpolator(spInterpolator2));
			CHECK_NO_THROW(spResult = spTask->getResultImage());

			CHECK_EQUAL(4, spPerformer->_performanceCount); //reperforming because result representation changed

			CHECK_NO_THROW(spTask->setImageInterpolator(spInterpolator2));
			CHECK_NO_THROW(spResult = spTask->getResultImage());

			CHECK_EQUAL(4,
						spPerformer->_performanceCount); // no reperforming because result representation was not realy changed

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
