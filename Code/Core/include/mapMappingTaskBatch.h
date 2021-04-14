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


#ifndef __MAP_MAPPING_TASK_BATCH_H
#define __MAP_MAPPING_TASK_BATCH_H

#include "mapMappingTaskBase.h"
#include "mapMappingTaskBatchThread.h"

#include "itkObject.h"
#include "itkMultiThreader.h"

#include <vector>
#include <deque>

namespace map
{

	namespace core
	{
		/*! @class MappingTaskBatch
		* @brief Class realizes a task batch, that performs mapping on different data in on run.
		*
		* You can add an arbitrarily number of tasks to the batch. by calling process(const RegistrationType*) all
		* tasks will be performed with the passed registration.
		* @ingroup MappingTask
		* @ingroup Registration
		* @tparam TRegistration the registration class, that should be used to perform the task.
		*/
		template <class TRegistration>
		class MappingTaskBatch: public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			typedef TRegistration					RegistrationType;
			typedef MappingTaskBase<RegistrationType> MappingTaskBaseType;
			typedef typename MappingTaskBaseType::Pointer  MappingTaskBasePointer;
			typedef std::deque<MappingTaskBaseType*>   TaskSelectionType;
			typedef std::vector<MappingTaskBasePointer> TaskVectorType;

			typedef MappingTaskBatch<TRegistration>  Self;
			typedef itk::Object					                  Superclass;
			typedef itk::SmartPointer<Self>								Pointer;
			typedef itk::SmartPointer<const Self>					ConstPointer;
			typedef typename TaskVectorType::size_type             ThreadCountType;

			itkTypeMacro(MappingTaskBatch, itk::Object);
			itkNewMacro(Self);

			/*! Removes all tasks from the batch.
			 * @eguarantee: strong
			 */
			void clear(void);

			/*! Adds a task to the batch.
			 * @param [in] Pointer to the task that should be added.
			 * @eguarantee: strong
			 * @pre pTask must not be NULL.
			 */
			void addTask(MappingTaskBaseType* pTask);

			/*! Adds the registration to every task in the batch and calls execute().
			 * @param [in] Pointer to the registration that should be used.
			 * @eguarantee: basic
			 * @pre pRegistration must not be NULL.
			 */
			bool process(const RegistrationType* pRegistration);

			/*! Calls execute() of every task.
			 * @eguarantee: basic
			 */
			bool process();

			const TaskSelectionType& getFailedTasks(void) const;

			const TaskVectorType& getTasks(void) const;

			/*! Sets the value of _maxThreadCount.
			 * @eguarantee: strong
			 */
			void setMaxThreadCount(ThreadCountType count);
			/*! Returns the value of _maxThreadCount.
			 * @eguarantee: strong
			 * @return The number of thread that will be used.
			 * @retval 0 Indicates that the thread count will equal the number of tasks.
			 */
			ThreadCountType getMaxThreadCount() const;

			/*! Checks if _maxThreadCount is 0.
			 * @eguarantee: strong
			 */
			bool getOneThreadPerTask() const;
			/*! Sets the value of _maxThreadCount to 0.
			 * @eguarantee: strong
			 */
			void activateOneThreadPerTask();

		protected:
			MappingTaskBatch();
			virtual ~MappingTaskBatch();

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:
			TaskVectorType _tasks;

			/*! all tasks that are waiting to be processed*/
			TaskSelectionType _pendingTasks;
			/*! all tasks that are assigned to threads*/
			TaskSelectionType _assignedTasks;
			/*! all tasks that were successfully processed*/
			TaskSelectionType _processedTasks;
			/*! all tasks that have failed*/
			TaskSelectionType _failedTasks;

			/*! copys all tasks from _tasks to _pendingTasks
			 * @eguarantee: strong
			 */
			void populatePendingTasks();

			/*! Adds the registration to every task in the batch.
			 * @param [in] Pointer to the registration that should be used.
			 * @eguarantee: strong
			 * @pre pRegistration must not be NULL.
			 */
			void setRegistration(const RegistrationType* pRegistration);

			typedef MappingTaskBatchThread<MappingTaskBaseType> ThreadType;
			typedef std::vector<typename ThreadType::Pointer> ThreadVectorType;

			/*! Indicate how many thread should be used to process the task.
			 * A value of 0 indicates that the thread number should equal the task number (one task per thread).*/
			ThreadCountType _maxThreadCount;

			ThreadVectorType _threads;

			/*! Indicates if a task has failed with an exception and was set exception neutral. Thus the batch won't processe
			 * any further tasks and will wait for the threads to return and throw the exception afterwards.*/
			const ExceptionObject* _pTerminatingException;

			static ITK_THREAD_RETURN_TYPE threadExecution(void* arg);

			void onNextTaskThreadEvent(::itk::Object* pCaller, const ::itk::EventObject& eventObject);
			void onProcessedTaskThreadEvent(::itk::Object* pCaller, const ::itk::EventObject& eventObject);
			void onFailedTaskThreadEvent(::itk::Object* pCaller, const ::itk::EventObject& eventObject);

			/** Responsible for locking the processing of thread callbacks.*/
			::std::mutex _threadMutex;
			typedef ::std::lock_guard< ::std::mutex > MutexHolderType;

			MappingTaskBatch(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapMappingTaskBatch.tpp"
#endif

#endif
