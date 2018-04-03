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
#include "mapMultiResImageRegistrationAlgorithmBase.h"
#include "mapArbitraryImagePyramidesPolicy.h"

#include "itkBoxSpatialObject.h"

namespace map
{
	namespace testing
	{
		namespace
		{

			template<class TMovingImage, class TTargetImage>
			class TestMultiResRegistrationAlgorithmBase : public
				::map::algorithm::MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, algorithm::ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> >
			{
			public:
				TestMultiResRegistrationAlgorithmBase()
				{
					_hasLevelCount = false;
					_doGetCurrentLevelCount = 0;
				};

				using algorithm::MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, algorithm::ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> >::getTargetPyramideMTime;
				using algorithm::MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, algorithm::ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> >::getMovingPyramideMTime;

				typedef algorithm::MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, algorithm::ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage> >
				Superclass;

				bool _hasLevelCount;
				mutable unsigned int _doGetCurrentLevelCount;


				virtual bool hasLevelCount() const
				{
					return _hasLevelCount;
				};

				virtual typename Superclass::ResolutionLevelCountType doGetCurrentLevel() const
				{
					++_doGetCurrentLevelCount;
					return 42;
				};

				void onMovingImagePyramideChange(const itk::EventObject&)
				{};

				void onTargetImagePyramideChange(const itk::EventObject&)
				{};

			};
		}

		int mapMultiResImageRegistrationAlgorithmBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;


			typedef core::discrete::Elements<3>::InternalImageType ImageType;
			typedef core::discrete::Elements<2>::InternalImageType Image2Type;

			typedef ::itk::MultiResolutionPyramidImageFilter<ImageType, ImageType> Pyramide1Type;
			typedef ::itk::MultiResolutionPyramidImageFilter<Image2Type, Image2Type> Pyramide2Type;

			Pyramide1Type::Pointer spPyramide1 = Pyramide1Type::New();

			Pyramide2Type::Pointer spTargetPyramide1 = Pyramide2Type::New();

			TestMultiResRegistrationAlgorithmBase<ImageType, Image2Type> testInterface;

			CHECK(NULL == testInterface.getMovingImagePyramide());
			CHECK(NULL == testInterface.getTargetImagePyramide());

			unsigned long mmt = testInterface.getMovingPyramideMTime();
			unsigned long tmt = testInterface.getTargetPyramideMTime();

			testInterface.setMovingImagePyramide(spPyramide1);

			CHECK(mmt < testInterface.getMovingPyramideMTime());
			CHECK(tmt == testInterface.getTargetPyramideMTime());
			mmt = testInterface.getMovingPyramideMTime();

			testInterface.setTargetImagePyramide(spTargetPyramide1);

			CHECK(mmt == testInterface.getMovingPyramideMTime());
			CHECK(tmt < testInterface.getTargetPyramideMTime());

			tmt = testInterface.getTargetPyramideMTime();

			spPyramide1->Modified();

			CHECK(mmt < testInterface.getMovingPyramideMTime());
			CHECK(tmt == testInterface.getTargetPyramideMTime());
			mmt = testInterface.getMovingPyramideMTime();

			spTargetPyramide1->Modified();

			CHECK(mmt == testInterface.getMovingPyramideMTime());
			CHECK(tmt < testInterface.getTargetPyramideMTime());

			CHECK_EQUAL(spPyramide1.GetPointer(), testInterface.getMovingImagePyramide());
			CHECK_EQUAL(spTargetPyramide1.GetPointer(), testInterface.getTargetImagePyramide());

			testInterface._hasLevelCount = false;
			CHECK_EQUAL(0, testInterface.getCurrentLevel());
			CHECK_EQUAL(0, testInterface._doGetCurrentLevelCount);
			testInterface._hasLevelCount = true;
			CHECK_EQUAL(42, testInterface.getCurrentLevel());
			CHECK_EQUAL(1, testInterface._doGetCurrentLevelCount);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
