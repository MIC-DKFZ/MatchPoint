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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/test/mapIterativeAlgorithmBaseTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litCheckMacros.h"
#include "mapIterativeAlgorithmBase.h"

namespace map
{
	namespace testing
	{
		namespace
		{
			class TestIterativeAlgorithmBase : public algorithm::IterativeAlgorithmBase
			{
			public:
				mutable unsigned int _doGetCurrentIterationCount;
				mutable unsigned int _doGetMaxIteration;

				bool _hasIterationCount;
				bool _hasMaxIterationCount;

				virtual bool hasIterationCount() const
				{
					return _hasIterationCount;
				}

				virtual bool hasMaxIterationCount() const
				{
					return _hasMaxIterationCount;
				}

				virtual IterationCountType doGetMaxIterations() const
				{
					++_doGetMaxIteration;
					return 84;
				}

				virtual IterationCountType doGetCurrentIteration() const
				{
					++_doGetCurrentIterationCount;
					return 42;
				}

				TestIterativeAlgorithmBase()
				{
					_doGetCurrentIterationCount = 0;
					_doGetMaxIteration = 0;
					_hasMaxIterationCount = false;
					_hasIterationCount = false;
				}

			};
		}

		int mapIterativeAlgorithmBaseTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestIterativeAlgorithmBase testInterface;

			CHECK_EQUAL(0, testInterface.getCurrentIteration());
			CHECK_EQUAL(0, testInterface.getMaxIterations());
			CHECK_EQUAL(0, testInterface._doGetCurrentIterationCount);
			CHECK_EQUAL(0, testInterface._doGetMaxIteration);

			testInterface._hasIterationCount = true;

			CHECK_EQUAL(42, testInterface.getCurrentIteration());
			CHECK_EQUAL(0, testInterface.getMaxIterations());
			CHECK_EQUAL(1, testInterface._doGetCurrentIterationCount);
			CHECK_EQUAL(0, testInterface._doGetMaxIteration);

			testInterface._hasIterationCount = false;
			testInterface._hasMaxIterationCount = true;

			CHECK_EQUAL(0, testInterface.getCurrentIteration());
			CHECK_EQUAL(84, testInterface.getMaxIterations());
			CHECK_EQUAL(1, testInterface._doGetCurrentIterationCount);
			CHECK_EQUAL(1, testInterface._doGetMaxIteration);

			testInterface._hasIterationCount = true;
			testInterface._hasMaxIterationCount = true;

			CHECK_EQUAL(42, testInterface.getCurrentIteration());
			CHECK_EQUAL(84, testInterface.getMaxIterations());
			CHECK_EQUAL(2, testInterface._doGetCurrentIterationCount);
			CHECK_EQUAL(2, testInterface._doGetMaxIteration);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
