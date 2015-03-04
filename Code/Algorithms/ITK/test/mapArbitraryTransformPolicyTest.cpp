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

#include <itkScaleTransform.h>

#include "litCheckMacros.h"
#include "mapContinuous.h"
#include "mapArbitraryTransformPolicy.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			class TestPolicy : public
				algorithm::itk::ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>
			{
				//derivered a test class to generate public constructors (The policy itsself cannot
				//be instantiated directly), to set the visibility of getTransformInternal to
				//public and to include internal event checks.
			public:
				using algorithm::itk::ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>::getTransformInternal;//get internals visible

				unsigned int _regEventCount;
				unsigned int _unregEventCount;

				TestPolicy()
				{
					typedef ::itk::ReceptorMemberCommand< TestPolicy<TScalar, VInputDimensions, VOutputDimensions> >
					AlgorithmCommandType;

					typename AlgorithmCommandType::Pointer spCmd = AlgorithmCommandType::New();
					spCmd->SetCallbackFunction(this,
											   & TestPolicy<TScalar, VInputDimensions, VOutputDimensions>::onChange);
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

		int mapArbitraryTransformPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestPolicy<core::continuous::ScalarType, 3, 3> policy;
			const TestPolicy<core::continuous::ScalarType, 3, 3>& constPolicy = policy;

			typedef ::itk::ScaleTransform<core::continuous::ScalarType, 3> ModelType;

			ModelType::Pointer spModel1 = ModelType::New();
			ModelType::Pointer spModel2 = ModelType::New();

			itk::Transform<core::continuous::ScalarType, 3, 3>* pModel = NULL;
			const itk::Transform<core::continuous::ScalarType, 3, 3>* pConstModel = NULL;

			CHECK_NO_THROW(pModel = policy.getTransformInternal());
			CHECK_NO_THROW(pConstModel = constPolicy.getTransformInternal());

			CHECK(NULL == pModel);
			CHECK(NULL == pConstModel);

			CHECK_NO_THROW(policy.setTransformModel(spModel1));

			CHECK_EQUAL(1, policy._unregEventCount);
			CHECK_EQUAL(1, policy._regEventCount);

			CHECK_NO_THROW(pModel = policy.getTransformInternal());

			CHECK_EQUAL(spModel1.GetPointer(), pModel);

			CHECK_NO_THROW(policy.setTransformModel(spModel2));

			CHECK_EQUAL(2, policy._unregEventCount);
			CHECK_EQUAL(2, policy._regEventCount);

			CHECK_NO_THROW(pModel = policy.getTransformInternal());
			CHECK_NO_THROW(pConstModel = constPolicy.getTransformInternal());

			CHECK_EQUAL(spModel2.GetPointer(), pModel);
			CHECK_EQUAL(spModel2.GetPointer(), pConstModel);

			CHECK_NO_THROW(pModel = policy.getTransformModel());
			CHECK_NO_THROW(pConstModel = constPolicy.getTransformModel());

			CHECK_EQUAL(spModel2.GetPointer(), pModel);
			CHECK_EQUAL(spModel2.GetPointer(), pConstModel);


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
