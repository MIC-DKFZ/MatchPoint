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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/test/mapArbitraryInterpolatorPolicyTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litCheckMacros.h"
#include "mapDiscreteElements.h"
#include "mapArbitraryInterpolatorPolicy.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkNearestNeighborInterpolateImageFunction.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TInputImage>
			class TestPolicy : public algorithm::itk::ArbitraryInterpolatorPolicy<TInputImage>
			{
				//derivered a test class to generate public constructors (The policy itsself cannot
				//be instantiated directly), to set the visibility of getInterpolatorInternal to
				//public and to include internal event checks.
			public:
				using algorithm::itk::ArbitraryInterpolatorPolicy<TInputImage>::getInterpolatorInternal;

				typedef typename algorithm::itk::ArbitraryInterpolatorPolicy<TInputImage> Superclass;


				unsigned int _regEventCount;
				unsigned int _unregEventCount;

				TestPolicy()
				{
					typedef ::itk::ReceptorMemberCommand< TestPolicy<TInputImage> > AlgorithmCommandType;

					typename AlgorithmCommandType::Pointer spCmd = AlgorithmCommandType::New();
					spCmd->SetCallbackFunction(this, & TestPolicy<TInputImage>::onChange);
					this->_spOnChange = spCmd;

					_regEventCount = 0;
					_unregEventCount = 0;

				};

				void
				onChange(const ::itk::EventObject &eventObject)
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

		int mapArbitraryInterpolatorPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestPolicy<core::discrete::Elements<3>::InternalImageType> policy;
			const TestPolicy<core::discrete::Elements<3>::InternalImageType> &constPolicy = policy;

			typedef itk::LinearInterpolateImageFunction<core::discrete::Elements<3>::InternalImageType, core::continuous::ScalarType> Interpolator1Type;
			typedef itk::NearestNeighborInterpolateImageFunction<core::discrete::Elements<3>::InternalImageType, core::continuous::ScalarType> Interpolator2Type;

			Interpolator1Type::Pointer spInterpolator1 = Interpolator1Type::New();
			Interpolator2Type::Pointer spInterpolator2 = Interpolator2Type::New();

			itk::InterpolateImageFunction<core::discrete::Elements<3>::InternalImageType, core::continuous::ScalarType> *pInterpolator = NULL;
			const itk::InterpolateImageFunction<core::discrete::Elements<3>::InternalImageType, core::continuous::ScalarType> *pConstInterpolator = NULL;

			CHECK_NO_THROW(pInterpolator = policy.getInterpolatorInternal());
			CHECK_NO_THROW(pConstInterpolator = constPolicy.getInterpolatorInternal());

			CHECK(NULL == pInterpolator);
			CHECK(NULL == pConstInterpolator);

			CHECK_NO_THROW(policy.setInterpolator(spInterpolator1));

			CHECK_NO_THROW(pInterpolator = policy.getInterpolatorInternal());
			CHECK_EQUAL(1, policy._unregEventCount);
			CHECK_EQUAL(1, policy._regEventCount);

			CHECK_EQUAL(spInterpolator1.GetPointer(), pInterpolator);

			CHECK_NO_THROW(policy.setInterpolator(spInterpolator2));

			CHECK_NO_THROW(pInterpolator = policy.getInterpolatorInternal());
			CHECK_NO_THROW(pConstInterpolator = constPolicy.getInterpolatorInternal());
			CHECK_EQUAL(2, policy._unregEventCount);
			CHECK_EQUAL(2, policy._regEventCount);

			CHECK_EQUAL(spInterpolator2.GetPointer(), pInterpolator);
			CHECK_EQUAL(spInterpolator2.GetPointer(), pConstInterpolator);

			CHECK_NO_THROW(pInterpolator = policy.getInterpolator());
			CHECK_NO_THROW(pConstInterpolator = constPolicy.getInterpolator());

			CHECK(NULL != pInterpolator);
			CHECK_EQUAL(pInterpolator, pConstInterpolator);
			CHECK_EQUAL(pInterpolator, policy.getInterpolatorInternal());


			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
