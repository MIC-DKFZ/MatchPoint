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


#ifndef __MAP_MAPPING_TASK_BATCH_THREAD_TPP
#define __MAP_MAPPING_TASK_BATCH_THREAD_TPP

#include "mapMappingTaskBatchThread.h"
#include "mapThreadEvents.h"

namespace map
{
	namespace core
	{

		template <class TMappingTaskBase>
		typename MappingTaskBatchThread<TMappingTaskBase>::ThreadIDType
		MappingTaskBatchThread<TMappingTaskBase>::
		getThreadID() const
		{
			return _threadID;
		};

		template <class TMappingTaskBase>
		void
		MappingTaskBatchThread<TMappingTaskBase>::
		setThreadID(const ThreadIDType& id)
		{
			MutexHolderType hold(_executionMutex);

			_threadID = id;
		};

		template <class TMappingTaskBase>
		void
		MappingTaskBatchThread<TMappingTaskBase>::
		execute()
		{
			MutexHolderType hold(_executionMutex);
			_unhandledExceptionOccured = false;

			bool stopThread = false;

			try
			{
				while (!stopThread)
				{
					//Reset task pointer to indicates the assignment of a new task
					_pNewTask = NULL;
					this->InvokeEvent(::map::events::NextTaskThreadEvent(_threadID));

					if (_pNewTask)
					{
						//a new task was assigned
						_pCurrentProcessedTask = _pNewTask;

						if (_pCurrentProcessedTask->execute())
						{
							this->InvokeEvent(::map::events::ProcessedTaskThreadEvent(_threadID, _pCurrentProcessedTask));
						}
						else
						{
							this->InvokeEvent(::map::events::FailedTaskThreadEvent(_threadID, _pCurrentProcessedTask));
						}
					}
					else
					{
						stopThread = true;
					}
				}
			}
			catch (...)
			{
				_unhandledExceptionOccured = true;
				this->InvokeEvent(::map::events::FailedTaskThreadEvent(_threadID, _pCurrentProcessedTask));
			}
		};

		template <class TMappingTaskBase>
		void
		MappingTaskBatchThread<TMappingTaskBase>::
		setNewTask(MappingTaskBaseType* pTask)
		{
			_pNewTask = pTask;
		};

		template <class TMappingTaskBase>
		typename MappingTaskBatchThread<TMappingTaskBase>::MappingTaskBaseType*
		MappingTaskBatchThread<TMappingTaskBase>::
		getCurrentTask()
		{
			return _pCurrentProcessedTask;
		};

		template <class TMappingTaskBase>
		bool
		MappingTaskBatchThread<TMappingTaskBase>::
		hasUnhandledExceptionOccured() const
		{
			return _unhandledExceptionOccured;
		};



		template <class TMappingTaskBase>
		MappingTaskBatchThread<TMappingTaskBase>::
		MappingTaskBatchThread()
		{
			_threadID = 0;
			_unhandledExceptionOccured = false;

			_pNewTask = NULL;
			_pCurrentProcessedTask = NULL;
		};

		template <class TMappingTaskBase>
		MappingTaskBatchThread<TMappingTaskBase>::
		~MappingTaskBatchThread()
		{
		};

	} // end namespace core
} // end namespace map

#endif
