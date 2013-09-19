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


#ifndef __MAP_MAPPING_TASK_BATCH_THREAD_H
#define __MAP_MAPPING_TASK_BATCH_THREAD_H

#include "mapMappingTaskBase.h"

#include "itkObject.h"
#include "itkMutexLockHolder.h"

namespace map
{

	namespace core
	{
		/*! @class MappingTaskBatchThread
		* @brief Class realizes a thread of a task batch, that process mapping tasks give by the batch.
		*
		* To request a new task this class will invoke an NextTaskThreadEvent.\n
		* To signal a sucessfully processed task it will invoke a ProcessedTaskThreadEvent.\n
		* To signal a failed task it will invoke a FailedTaskThreadEvent.
		* @ingroup MappingTask
		* @ingroup Registration
		* @tparam TMappingTaskBase the registration task base class, that should be processed.
		*/
		template <class TMappingTaskBase>
		class MappingTaskBatchThread: public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			typedef MappingTaskBatchThread<TMappingTaskBase>   Self;
			typedef itk::Object                       Superclass;
			typedef itk::SmartPointer<Self>           Pointer;
			typedef itk::SmartPointer<const Self>     ConstPointer;

			typedef TMappingTaskBase MappingTaskBaseType;
			typedef typename MappingTaskBaseType::Pointer  MappingTaskBasePointer;

			itkNewMacro(Self);
			itkTypeMacro(MappingTaskBatchThread, itk::Object);

			typedef unsigned long ThreadIDType;

			ThreadIDType getThreadID() const;
			void setThreadID(const ThreadIDType& id);

			/** Executes the thread. The default handling requests a task via
			* invoking an NextTaskThreadEvent. The thread assumes that the next task is set
			* if the event returns. If the _pNewTask is NULL the thread asumes,
			* that all work is done and execute returns. If there is a new task, it will be processed.
			* After the processing the next task will be requested (and so on).
			*/
			void execute();

			void setNewTask(MappingTaskBaseType* pTask);

			MappingTaskBaseType* getCurrentTask();

			bool hasUnhandledExceptionOccured() const;

		protected:

			MappingTaskBatchThread();

			virtual ~MappingTaskBatchThread();

		private:

			ThreadIDType _threadID;
			bool _unhandledExceptionOccured;

			MappingTaskBaseType* _pNewTask;
			MappingTaskBaseType* _pCurrentProcessedTask;

			/** Responsible for locking the processing, to ensure no change of values
			* while thread is in Execution.*/
			::itk::SimpleFastMutexLock _executionMutex;
			typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock > MutexHolderType;

			MappingTaskBatchThread(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapMappingTaskBatchThread.tpp"
#endif

#endif
