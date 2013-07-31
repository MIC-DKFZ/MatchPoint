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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapTestMappingTask.h $
*/

#ifndef __MAP_TEST_MAPPING_TASK_H
#define __MAP_TEST_MAPPING_TASK_H

#include "mapMappingTaskBase.h"

namespace map
{
	namespace testing
	{
		template <class TRegistration>
		class TestMappingTask: public core::MappingTaskBase<TRegistration>
		{
		public:
			/*! Standard class typedefs. */
			typedef TestMappingTask<TRegistration>   Self;
			typedef core::MappingTaskBase<TRegistration> Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(TestMappingTask, MappingTaskBase);
			itkNewMacro(Self);

			bool _failExecution;
			mutable unsigned int _executionCount;
			mutable unsigned int _clearResultsCount;
			mutable unsigned int _clearInputsCount;

		protected:
			virtual void doExecution(void) const
			{
				++_executionCount;

				if (_failExecution)
				{
					mapDefaultExceptionMacro( << "TestException");
				}
			}

			virtual void clearResults(void) const
			{
				++_clearResultsCount;
			}

			virtual void clearInputs(void)
			{
				++_clearInputsCount;
			}

			TestMappingTask()
			{
				_executionCount = 0;
				_clearResultsCount = 0;
				_clearInputsCount = 0;
				_failExecution = false;
			};

			virtual ~TestMappingTask()
			{};

		private:
			TestMappingTask(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	} // end namespace testing
} // end namespace map

#endif
