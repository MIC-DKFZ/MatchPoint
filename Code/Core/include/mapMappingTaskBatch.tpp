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


#ifndef __MAP_MAPPING_TASK_BATCH_TPP
#define __MAP_MAPPING_TASK_BATCH_TPP

#include "mapMappingTaskBatch.h"
#include "mapThreadEvents.h"
#include "mapServiceException.h"

#include "itkCommand.h"
#include "itkNumericTraits.h"

#include <algorithm>

namespace map
{
	namespace core
	{

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		populatePendingTasks()
		{
			this->_pendingTasks.clear();

			for (typename TaskVectorType::iterator pos = this->_tasks.begin(); pos != this->_tasks.end(); ++pos)
			{
				this->_pendingTasks.push_back((*pos).GetPointer());
			}
		};

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		clear(void)
		{
			this->_failedTasks.clear();
			this->_tasks.clear();
			this->_pendingTasks.clear();
			this->_processedTasks.clear();
			this->_assignedTasks.clear();
			this->_threads.clear();
			this->Modified();
		}

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		addTask(MappingTaskBaseType* pTask)
		{
			if (!pTask)
			{
				mapExceptionMacro(ServiceException,
								  << "Error. Cannot add invalid task to task batch. Task pointer is NULL.");
			}

			this->_tasks.push_back(pTask);
			this->Modified();
		}

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		setRegistration(const RegistrationType* pRegistration)
		{
			if (!pRegistration)
			{
				mapExceptionMacro(ServiceException,
								  << "Error. Cannot set invalid registration to task batch. Registration pointer is NULL.");
			}

			for (typename TaskVectorType::iterator pos = this->_tasks.begin(); pos != this->_tasks.end(); ++pos)
			{
				(*pos)->setRegistration(pRegistration);
			}
		}

		template <class TRegistration>
		bool
		MappingTaskBatch<TRegistration>::
		process(const RegistrationType* pRegistration)
		{
			setRegistration(pRegistration);
			return process();
		}

		template <class TRegistration>
		bool
		MappingTaskBatch<TRegistration>::
		process()
		{
			this->_pTerminatingException = NULL;
			this->_failedTasks.clear();
			this->_processedTasks.clear();
			this->_assignedTasks.clear();
			this->_threads.clear();

			populatePendingTasks();

			itk::MultiThreader::Pointer smpThreader = itk::MultiThreader::New();

			ThreadCountType currentThreadCount = this->_maxThreadCount;

			if (currentThreadCount < 1)
			{
				if (_tasks.size() > (typename ThreadVectorType::size_type)(
						::itk::NumericTraits<ThreadCountType>::max()))
				{
					currentThreadCount = ::itk::NumericTraits<ThreadCountType>::max();
				}
				else
				{
					currentThreadCount = _tasks.size();
				}
			}

			smpThreader->SetNumberOfThreads(currentThreadCount);

			try
			{
				for (ThreadCountType index = 0; index < currentThreadCount; index++)
				{
					//create the threads, the id will be set via threadExecution
					//and the thread info structure passed by the threader
					typename ThreadType::Pointer smpThread = ThreadType::New();

					//add observer for the communication with the thread
					typename ::itk::MemberCommand<Self>::Pointer spNewTaskCommand = ::itk::MemberCommand<Self>::New();
					spNewTaskCommand->SetCallbackFunction(this, &Self::onNextTaskThreadEvent);
					smpThread->AddObserver(::map::events::NextTaskThreadEvent(::map::events::NextTaskThreadEvent::anyThreadID),
										   spNewTaskCommand);

					typename ::itk::MemberCommand<Self>::Pointer spProcessedTaskCommand =
						::itk::MemberCommand<Self>::New();
					spProcessedTaskCommand->SetCallbackFunction(this, &Self::onProcessedTaskThreadEvent);
					smpThread->AddObserver(::map::events::ProcessedTaskThreadEvent(
											   events::ProcessedTaskThreadEvent::anyThreadID), spProcessedTaskCommand);

					typename ::itk::MemberCommand<Self>::Pointer spFailedTaskCommand =
						::itk::MemberCommand<Self>::New();
					spFailedTaskCommand->SetCallbackFunction(this, &Self::onFailedTaskThreadEvent);
					smpThread->AddObserver(::map::events::FailedTaskThreadEvent(::map::events::FailedTaskThreadEvent::anyThreadID),
										   spFailedTaskCommand);

					_threads.push_back(smpThread);
					smpThreader->SetMultipleMethod(index, Self::threadExecution, smpThread.GetPointer());
				}
			}
			catch (...)
			{
				std::cout << "Test stop TODO";
			}

			try
			{
				//Start with the work
				smpThreader->MultipleMethodExecute();
			}
			catch (...)
			{
				std::cout << "Test execute TODO";
			}

			if (_pTerminatingException)
			{
				//one process task was exception neutral and threw an exception, pass it on now,
				//after al threads have terminated
				throw* _pTerminatingException;
			}

			return _failedTasks.size() == 0;
		}

		template <class TRegistration>
		ITK_THREAD_RETURN_TYPE
		MappingTaskBatch<TRegistration>::
		threadExecution(void* arg)
		{
			ThreadType* pThread;
			int threadID;

			threadID = ((itk::MultiThreader::ThreadInfoStruct*)(arg))->ThreadID;

			pThread = (ThreadType*)(((itk::MultiThreader::ThreadInfoStruct*)(arg))->UserData);

			if (!pThread)
			{
				mapDefaultExceptionStaticMacro( << "Error; user data for thread execution is missing");
			}

			pThread->setThreadID(threadID);
			pThread->execute();

			return ITK_THREAD_RETURN_VALUE;
		};

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		onNextTaskThreadEvent(::itk::Object* pCaller, const ::itk::EventObject& eventObject)
		{
			MutexHolderType holder(_threadMutex);

			if ((!_pendingTasks.empty()) && _pTerminatingException == NULL)
			{
				ThreadType* pThread = dynamic_cast<ThreadType*>(pCaller);

				if (pThread)
				{
					MappingTaskBaseType* pTask = _pendingTasks.front();
					pThread->setNewTask(pTask);
					_assignedTasks.push_back(pTask);
					_pendingTasks.pop_front();
					this->InvokeEvent(::map::events::NextTaskThreadEvent(pThread->getThreadID(), pTask, "Next assigned task"));
				}
			}
		}

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		onProcessedTaskThreadEvent(::itk::Object* pCaller, const ::itk::EventObject& eventObject)
		{
			MutexHolderType holder(_threadMutex);

			ThreadType* pThread = dynamic_cast<ThreadType*>(pCaller);

			if (pThread)
			{
				MappingTaskBaseType* pTask = pThread->getCurrentTask();
				std::remove(_assignedTasks.begin(), _assignedTasks.end(), pTask);
				_processedTasks.push_back(pTask);
				this->InvokeEvent(::map::events::ProcessedTaskThreadEvent(pThread->getThreadID(), pTask,
								  "Task processed successfully"));
			}
			else
			{
				mapDefaultExceptionMacro( <<
										  "Error. onProcessedTaskThreadEvent was called but pCaller doesnt point to a threas. pCaller: " <<
										  pCaller);
			}
		}

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		onFailedTaskThreadEvent(::itk::Object* pCaller, const ::itk::EventObject& eventObject)
		{
			MutexHolderType holder(_threadMutex);

			ThreadType* pThread = dynamic_cast<ThreadType*>(pCaller);

			if (pThread)
			{
				MappingTaskBaseType* pTask = pThread->getCurrentTask();
				std::remove(_assignedTasks.begin(), _assignedTasks.end(), pTask);
				_failedTasks.push_back(pTask);

				if (pThread->hasUnhandledExceptionOccured())
				{
					if ((pTask->getIsExceptionNeutral()) &&
						(pTask->getRegistrationException() != NULL))
					{
						_pTerminatingException = pTask->getRegistrationException();
					}

					this->InvokeEvent(::map::events::ThreadTerminatingErrorEvent(pThread->getThreadID(), pThread,
									  "Thread loop terminated with exception"));
				}

				this->InvokeEvent(::map::events::FailedTaskThreadEvent(pThread->getThreadID(), pTask, "Task failed"));
			}
			else
			{
				mapDefaultExceptionMacro( <<
										  "Error. onFailedTaskThreadEvent was called but pCaller doesnt point to a threas. pCaller: " <<
										  pCaller);
			}
		}

		template <class TRegistration>
		const typename MappingTaskBatch<TRegistration>::TaskSelectionType&
		MappingTaskBatch<TRegistration>::
		getFailedTasks(void) const
		{
			return this->_failedTasks;
		}

		template <class TRegistration>
		const typename MappingTaskBatch<TRegistration>::TaskVectorType&
		MappingTaskBatch<TRegistration>::
		getTasks(void) const
		{
			return this->_tasks;
		}

		template <class TRegistration>
		MappingTaskBatch<TRegistration>::
		MappingTaskBatch()
		{
			this->_failedTasks.clear();
			this->_tasks.clear();
			this->_pendingTasks.clear();
			this->_processedTasks.clear();
			this->_assignedTasks.clear();
			this->_threads.clear();
			_maxThreadCount = 0;
			_pTerminatingException = NULL;
		}

		template <class TRegistration>
		MappingTaskBatch<TRegistration>::
		~MappingTaskBatch()
		{
			this->clear();
		}

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "Max thread count : " << _maxThreadCount << std::endl;
			os << indent << "Thread count : " << _threads.size() << std::endl;
			os << indent << "Tasks : " << _tasks.size() << "tasks" << std::endl;
			os << indent << "Pending tasks : " << _pendingTasks.size() << "tasks" << std::endl;
			os << indent << "Assigned tasks : " << _assignedTasks.size() << "tasks" << std::endl;
			os << indent << "processed tasks : " << _processedTasks.size() << "tasks" << std::endl;
			os << indent << "Failed tasks : " << _failedTasks.size() << "tasks" << std::endl;
		}

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		setMaxThreadCount(ThreadCountType count)
		{
			if (count != _maxThreadCount)
			{
				_maxThreadCount = count;
				this->Modified();
			}
		};

		template <class TRegistration>
		typename MappingTaskBatch<TRegistration>::ThreadCountType
		MappingTaskBatch<TRegistration>::
		getMaxThreadCount() const
		{
			return _maxThreadCount;
		};

		template <class TRegistration>
		bool
		MappingTaskBatch<TRegistration>::
		getOneThreadPerTask() const
		{
			return _maxThreadCount == 0;
		};

		template <class TRegistration>
		void
		MappingTaskBatch<TRegistration>::
		activateOneThreadPerTask()
		{
			if (_maxThreadCount != 0)
			{
				_maxThreadCount = 0;
				this->Modified();
			}
		};

	} // end namespace core
} // end namespace map

#endif
