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
#include "mapOptimizerControlInterface.h"

#include "itkObject.h"

namespace map
{
	namespace testing
	{
		namespace
		{
			class TestOptimizerControl: public ::itk::Object, public map::algorithm::OptimizerControlInterface
			{
			public:
				typedef TestOptimizerControl Self;
				typedef algorithm::OptimizerControlInterface Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(TestOptimizerControl, OptimizerControlInterface);
				itkFactorylessNewMacro(Self);

				virtual bool isStoppable() const
				{
					return _isStoppable;
				};

				virtual bool hasIterationCount() const
				{
					return _hasIterationCount;
				};

				virtual bool hasMaxIterationCount() const
				{
					return _hasMaxIterationCount;
				};

				virtual bool canMinimize() const
				{
					return false; /*DUMMY*/
				};

				virtual bool canMaximize() const
				{
					return false; /*DUMMY*/
				};

				virtual bool getMinimize() const
				{
					return false; /*DUMMY*/
				};

				virtual bool getMaximize() const
				{
					return false; /*DUMMY*/
				};

				virtual void setMinimize(bool minimize)
				{
					/*DUMMY*/
				};

				virtual void setMaximize(bool maximize)
				{
					/*DUMMY*/
				};

				virtual bool hasCurrentValue() const
				{
					return _hasCurrentValue;
				};
				virtual bool hasCurrentPosition() const
				{
					return _hasCurrentPosition;
				};
				virtual bool hasScales() const
				{
					return _hasScale;
				};

				virtual const core::String getStopConditionDescription() const
				{
					return "stop dummy";
				}

				mutable unsigned int _doStopCount;
				mutable unsigned int _doGetCurrentIterationCount;
				mutable unsigned int _doGetMaxIteration;
				mutable unsigned int _doGetCurrentValue;
				mutable unsigned int _doGetCurrentPostion;
				mutable unsigned int _doGetScale;

				bool _isStoppable;
				bool _hasIterationCount;
				bool _hasMaxIterationCount;
				bool _stopResult;
				bool _hasCurrentValue;
				bool _hasCurrentPosition;
				bool _hasScale;

			protected:
				virtual bool doStop()
				{
					++_doStopCount;
					return _stopResult;
				};

				virtual IterationCountType doGetCurrentIteration() const
				{
					++_doGetCurrentIterationCount;
					return 42;
				};

				virtual IterationCountType doGetMaxIterations() const
				{
					++_doGetMaxIteration;
					return 84;
				};

				virtual OptimizerMeasureType doGetCurrentValue() const
				{
					OptimizerMeasureType result;
					result.push_back(42);

					++_doGetCurrentValue;
					return result;
				};

				virtual OptimizerPositionType doGetCurrentPosition() const
				{
					OptimizerPositionType result(1);
					result[0] = 21;

					++_doGetCurrentPostion;
					return result;
				};

				virtual OptimizerScalesType doGetScales() const
				{
					OptimizerScalesType result(1);
					result[0] = 105;

					++_doGetScale;
					return result;
				};

				TestOptimizerControl()
				{
					_isStoppable = false;
					_hasIterationCount = false;
					_hasMaxIterationCount = false;
					_stopResult = true;
					_hasCurrentValue = false;
					_hasCurrentPosition = false;
					_hasScale = false;
					_doStopCount = 0;
					_doGetCurrentIterationCount = 0;
					_doGetMaxIteration = 0;
					_doGetCurrentValue = 0;
					_doGetCurrentPostion = 0;
					_doGetScale = 0;
				};

				virtual ~TestOptimizerControl()
				{};
			};
		}

		int mapOptimizerControlInterfaceTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			TestOptimizerControl::Pointer testInterface = TestOptimizerControl::New();

			CHECK_EQUAL(false, testInterface->stop());
			CHECK_EQUAL(0, testInterface->getCurrentIteration());
			CHECK_EQUAL(0, testInterface->getMaxIterations());
			CHECK(testInterface->getCurrentValue().empty());
			CHECK(testInterface->getCurrentPosition().empty());
			CHECK(testInterface->getScales().empty());
			CHECK_EQUAL(0, testInterface->_doStopCount);
			CHECK_EQUAL(0, testInterface->_doGetCurrentIterationCount);
			CHECK_EQUAL(0, testInterface->_doGetMaxIteration);
			CHECK_EQUAL(0, testInterface->_doGetCurrentValue);
			CHECK_EQUAL(0, testInterface->_doGetCurrentPostion);
			CHECK_EQUAL(0, testInterface->_doGetScale);

			testInterface->_isStoppable = true;

			CHECK_EQUAL(true, testInterface->stop());
			CHECK_EQUAL(0, testInterface->getCurrentIteration());
			CHECK_EQUAL(0, testInterface->getMaxIterations());
			CHECK(testInterface->getCurrentValue().empty());
			CHECK(testInterface->getCurrentPosition().empty());
			CHECK(testInterface->getScales().empty());
			CHECK_EQUAL(1, testInterface->_doStopCount);
			CHECK_EQUAL(0, testInterface->_doGetCurrentIterationCount);
			CHECK_EQUAL(0, testInterface->_doGetMaxIteration);
			CHECK_EQUAL(0, testInterface->_doGetCurrentValue);
			CHECK_EQUAL(0, testInterface->_doGetCurrentPostion);
			CHECK_EQUAL(0, testInterface->_doGetScale);

			testInterface->_isStoppable = false;
			testInterface->_hasIterationCount = true;

			CHECK_EQUAL(false, testInterface->stop());
			CHECK_EQUAL(42, testInterface->getCurrentIteration());
			CHECK_EQUAL(0, testInterface->getMaxIterations());
			CHECK(testInterface->getCurrentValue().empty());
			CHECK(testInterface->getCurrentPosition().empty());
			CHECK(testInterface->getScales().empty());
			CHECK_EQUAL(1, testInterface->_doStopCount);
			CHECK_EQUAL(1, testInterface->_doGetCurrentIterationCount);
			CHECK_EQUAL(0, testInterface->_doGetMaxIteration);
			CHECK_EQUAL(0, testInterface->_doGetCurrentValue);
			CHECK_EQUAL(0, testInterface->_doGetCurrentPostion);
			CHECK_EQUAL(0, testInterface->_doGetScale);

			testInterface->_hasIterationCount = false;
			testInterface->_hasMaxIterationCount = true;

			CHECK_EQUAL(false, testInterface->stop());
			CHECK_EQUAL(0, testInterface->getCurrentIteration());
			CHECK_EQUAL(84, testInterface->getMaxIterations());
			CHECK(testInterface->getCurrentValue().empty());
			CHECK(testInterface->getCurrentPosition().empty());
			CHECK(testInterface->getScales().empty());
			CHECK_EQUAL(1, testInterface->_doStopCount);
			CHECK_EQUAL(1, testInterface->_doGetCurrentIterationCount);
			CHECK_EQUAL(1, testInterface->_doGetMaxIteration);
			CHECK_EQUAL(0, testInterface->_doGetCurrentValue);
			CHECK_EQUAL(0, testInterface->_doGetCurrentPostion);
			CHECK_EQUAL(0, testInterface->_doGetScale);

			testInterface->_hasMaxIterationCount = false;
			testInterface->_hasCurrentValue = true;

			CHECK_EQUAL(false, testInterface->stop());
			CHECK_EQUAL(0, testInterface->getCurrentIteration());
			CHECK_EQUAL(0, testInterface->getMaxIterations());
			CHECK(testInterface->getCurrentValue().at(0) = 42);
			CHECK(testInterface->getCurrentPosition().empty());
			CHECK(testInterface->getScales().empty());
			CHECK_EQUAL(1, testInterface->_doStopCount);
			CHECK_EQUAL(1, testInterface->_doGetCurrentIterationCount);
			CHECK_EQUAL(1, testInterface->_doGetMaxIteration);
			CHECK_EQUAL(1, testInterface->_doGetCurrentValue);
			CHECK_EQUAL(0, testInterface->_doGetCurrentPostion);
			CHECK_EQUAL(0, testInterface->_doGetScale);

			testInterface->_hasCurrentValue = false;
			testInterface->_hasCurrentPosition = true;

			CHECK_EQUAL(false, testInterface->stop());
			CHECK_EQUAL(0, testInterface->getCurrentIteration());
			CHECK_EQUAL(0, testInterface->getMaxIterations());
			CHECK(testInterface->getCurrentValue().empty());
			CHECK(testInterface->getCurrentPosition()[0] = 21);
			CHECK(testInterface->getScales().empty());
			CHECK_EQUAL(1, testInterface->_doStopCount);
			CHECK_EQUAL(1, testInterface->_doGetCurrentIterationCount);
			CHECK_EQUAL(1, testInterface->_doGetMaxIteration);
			CHECK_EQUAL(1, testInterface->_doGetCurrentValue);
			CHECK_EQUAL(1, testInterface->_doGetCurrentPostion);
			CHECK_EQUAL(0, testInterface->_doGetScale);

			testInterface->_hasCurrentPosition = false;
			testInterface->_hasScale = true;

			CHECK_EQUAL(false, testInterface->stop());
			CHECK_EQUAL(0, testInterface->getCurrentIteration());
			CHECK_EQUAL(0, testInterface->getMaxIterations());
			CHECK(testInterface->getCurrentValue().empty());
			CHECK(testInterface->getCurrentPosition().empty());
			CHECK(testInterface->getScales()[0] == 105);
			CHECK_EQUAL(1, testInterface->_doStopCount);
			CHECK_EQUAL(1, testInterface->_doGetCurrentIterationCount);
			CHECK_EQUAL(1, testInterface->_doGetMaxIteration);
			CHECK_EQUAL(1, testInterface->_doGetCurrentValue);
			CHECK_EQUAL(1, testInterface->_doGetCurrentPostion);
			CHECK_EQUAL(1, testInterface->_doGetScale);

			testInterface->_hasScale = false;
			testInterface->_isStoppable = true;
			testInterface->_stopResult = false;

			CHECK_EQUAL(false, testInterface->stop());
			CHECK_EQUAL(2, testInterface->_doStopCount);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
