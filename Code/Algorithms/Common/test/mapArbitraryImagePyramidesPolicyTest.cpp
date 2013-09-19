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
#include "mapDiscreteElements.h"
#include "mapArbitraryImagePyramidesPolicy.h"
#include "itkRecursiveMultiResolutionPyramidImageFilter.h"

namespace map
{
	namespace testing
	{

		namespace
		{
			template<class TMovingImage, class TTargetImage>
			class TestPolicy : public algorithm::ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>
			{
				//derivered a test class to generate public constructors (The policy itsself cannot
				//be instantiated directly), to set the visibility of getMovingPyramideInternal &
				//getTargetPyramideInternalto public and to include internal event checks.
			public:
				using algorithm::ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>::getMovingPyramideInternal;
				using algorithm::ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>::getTargetPyramideInternal;

				unsigned int _regEventCountMoving;
				unsigned int _unregEventCountMoving;
				unsigned int _regEventCountTarget;
				unsigned int _unregEventCountTarget;

				TestPolicy()
				{
					typedef ::itk::ReceptorMemberCommand< TestPolicy<TMovingImage, TTargetImage> > AlgorithmCommandType;

					typename AlgorithmCommandType::Pointer spCmd = AlgorithmCommandType::New();
					spCmd->SetCallbackFunction(this, & TestPolicy<TMovingImage, TTargetImage>::onMChange);
					this->_spOnChangeMoving = spCmd;

					typename AlgorithmCommandType::Pointer spCmd2 = AlgorithmCommandType::New();
					spCmd2->SetCallbackFunction(this, & TestPolicy<TMovingImage, TTargetImage>::onTChange);
					this->_spOnChangeTarget = spCmd2;

					_regEventCountMoving = 0;
					_unregEventCountMoving = 0;
					_regEventCountTarget = 0;
					_unregEventCountTarget = 0;

				};

				void
				onMChange(const ::itk::EventObject& eventObject)
				{
					map::events::UnregisterAlgorithmComponentEvent unregEvent;
					map::events::RegisterAlgorithmComponentEvent regEvent;

					if (unregEvent.CheckEvent(&eventObject))
					{
						++_unregEventCountMoving;
					}

					if (regEvent.CheckEvent(&eventObject))
					{
						++_regEventCountMoving;
					}
				};

				void
				onTChange(const ::itk::EventObject& eventObject)
				{
					map::events::UnregisterAlgorithmComponentEvent unregEvent;
					map::events::RegisterAlgorithmComponentEvent regEvent;

					if (unregEvent.CheckEvent(&eventObject))
					{
						++_unregEventCountTarget;
					}

					if (regEvent.CheckEvent(&eventObject))
					{
						++_regEventCountTarget;
					}
				};

			};

		}

		int mapArbitraryImagePyramidesPolicyTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::discrete::Elements<3>::InternalImageType ImageType;
			typedef core::discrete::Elements<2>::InternalImageType Image2Type;
			TestPolicy<ImageType, Image2Type> policy;
			const TestPolicy<ImageType, Image2Type>& constPolicy = policy;

			typedef itk::MultiResolutionPyramidImageFilter<ImageType, ImageType> Pyramide1Type;
			typedef itk::RecursiveMultiResolutionPyramidImageFilter<Image2Type, Image2Type> Pyramide2Type;

			Pyramide1Type::Pointer spPyramide1 = Pyramide1Type::New();
			Pyramide1Type::Pointer spPyramide2 = Pyramide1Type::New();

			Pyramide2Type::Pointer spTargetPyramide1 = Pyramide2Type::New();
			Pyramide2Type::Pointer spTargetPyramide2 = Pyramide2Type::New();

			TestPolicy<ImageType, Image2Type>::MovingImagePyramideBaseType* pPyramide = NULL;
			const TestPolicy<ImageType, Image2Type>::MovingImagePyramideBaseType* pConstPyramide = NULL;
			TestPolicy<ImageType, Image2Type>::TargetImagePyramideBaseType* pTargetPyramide = NULL;
			const TestPolicy<ImageType, Image2Type>::TargetImagePyramideBaseType* pConstTargetPyramide = NULL;

			CHECK_NO_THROW(pPyramide = policy.getMovingPyramideInternal());
			CHECK_NO_THROW(pConstPyramide = constPolicy.getMovingPyramideInternal());
			CHECK_NO_THROW(pTargetPyramide = policy.getTargetPyramideInternal());
			CHECK_NO_THROW(pConstTargetPyramide = constPolicy.getTargetPyramideInternal());

			CHECK(NULL == pPyramide);
			CHECK(NULL == pConstPyramide);
			CHECK(NULL == pTargetPyramide);
			CHECK(NULL == pConstTargetPyramide);

			CHECK_NO_THROW(policy.setMovingImagePyramide(spPyramide1));
			CHECK_NO_THROW(pPyramide = policy.getMovingPyramideInternal());
			CHECK_EQUAL(1, policy._unregEventCountMoving);
			CHECK_EQUAL(1, policy._regEventCountMoving);
			CHECK_EQUAL(0, policy._unregEventCountTarget);
			CHECK_EQUAL(0, policy._regEventCountTarget);
			CHECK_EQUAL(spPyramide1.GetPointer(), pPyramide);
			CHECK(NULL == policy.getTargetPyramideInternal());

			CHECK_NO_THROW(policy.setTargetImagePyramide(spTargetPyramide1));
			CHECK_NO_THROW(pTargetPyramide = policy.getTargetPyramideInternal());
			CHECK_EQUAL(1, policy._unregEventCountMoving);
			CHECK_EQUAL(1, policy._regEventCountMoving);
			CHECK_EQUAL(1, policy._unregEventCountTarget);
			CHECK_EQUAL(1, policy._regEventCountTarget);
			CHECK_EQUAL(spTargetPyramide1.GetPointer(), pTargetPyramide);
			CHECK_EQUAL(spPyramide1.GetPointer(), policy.getMovingPyramideInternal());


			CHECK_NO_THROW(policy.setMovingImagePyramide(spPyramide2));
			CHECK_NO_THROW(pPyramide = policy.getMovingPyramideInternal());
			CHECK_NO_THROW(pConstPyramide = policy.getMovingPyramideInternal());
			CHECK_EQUAL(2, policy._unregEventCountMoving);
			CHECK_EQUAL(2, policy._regEventCountMoving);
			CHECK_EQUAL(1, policy._unregEventCountTarget);
			CHECK_EQUAL(1, policy._regEventCountTarget);
			CHECK_EQUAL(spPyramide2.GetPointer(), pPyramide);
			CHECK_EQUAL(spPyramide2.GetPointer(), pConstPyramide);
			CHECK_EQUAL(spTargetPyramide1.GetPointer(), policy.getTargetPyramideInternal());

			CHECK_EQUAL(pPyramide, pConstPyramide);

			CHECK_NO_THROW(policy.setTargetImagePyramide(spTargetPyramide2));
			CHECK_NO_THROW(pTargetPyramide = policy.getTargetPyramideInternal());
			CHECK_NO_THROW(pConstTargetPyramide = policy.getTargetPyramideInternal());
			CHECK_EQUAL(2, policy._unregEventCountMoving);
			CHECK_EQUAL(2, policy._regEventCountMoving);
			CHECK_EQUAL(2, policy._unregEventCountTarget);
			CHECK_EQUAL(2, policy._regEventCountTarget);
			CHECK_EQUAL(spTargetPyramide2.GetPointer(), pTargetPyramide);
			CHECK_EQUAL(spTargetPyramide2.GetPointer(), pConstTargetPyramide);

			CHECK_EQUAL(pTargetPyramide, pConstTargetPyramide);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
