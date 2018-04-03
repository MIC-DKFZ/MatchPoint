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


#ifndef __MAP_THREAD_EVENTS_H
#define __MAP_THREAD_EVENTS_H

#include "mapEvents.h"

namespace map
{
	namespace core
	{

		/** @class EventObject
		 * @brief Base object for all MatchPoint events
		 * @ingroup Events
		 * */
		class MAPCore_EXPORT ThreadEventObject : public EventObject
		{
		public:
			typedef ThreadEventObject Self;
			typedef EventObject Superclass;
			typedef int ThreadIDType;

			static const ThreadIDType anyThreadID;

			ThreadEventObject(ThreadIDType threadID, void* pData = NULL, const std::string& comment = "");

			virtual ~ThreadEventObject();

			ThreadIDType getThreadID() const;

			virtual const char* GetEventName() const;

			/*! In addition to the normal event check the thread IDs will also be compared.
			 * If the IDs are equal or one of the IDs equals anyThreadID the return of the check will be
			 * true*/
			virtual bool CheckEvent(const ::itk::EventObject* e) const;

			virtual ::itk::EventObject* MakeObject() const;

			ThreadEventObject(const Self& s);

			virtual void Print(std::ostream& os) const;

		private:
			/*! The ID of the thread that called the event or, if this object is part of an observer,
			 * the ID that should trigger the observer. In the later case use anyThreadID (value: -1)
			 * to allow the CheckEvent() method to trigger without regarding the ID.*/
			ThreadIDType _threadID;
			void operator=(const Self&);
		};

		/*! @def mapThreadEventMacro
		* Helper macro that creates thread event objects for MatchPoint.
		*/
#define mapThreadEventMacro( classname , super ) \
	/*! @ingroup Events */  \
	class MAPCore_EXPORT classname : public super { \
	public: \
		typedef classname Self; \
		typedef super Superclass; \
		classname(ThreadIDType threadID, void* pData = NULL, const std::string& comment = ""):super(threadID, pData, comment) {}\
		virtual ~classname() {} \
		virtual const char * GetEventName() const { return #classname; } \
		virtual bool CheckEvent(const ::itk::EventObject* e) const \
		{ \
			const Self* pE = dynamic_cast<const Self*>(e); \
			bool result = false; \
			if (pE) result = (this->getThreadID()==anyThreadID) || (pE->getThreadID()==this->getThreadID()); \
			return result; \
		} \
		virtual ::itk::EventObject* MakeObject() const \
		{ return new Self(*this); } \
		classname(const Self& s) :super(s) {}; \
	private: \
		void operator=(const Self&); \
	}

	}

	namespace events
	{
		/*!@class AnyMatchPointThreadEvent
		 * @brief General event that can be used if you want to observe any thread event defined by MatchPoint.
		 * @ingroup Events
		 */
		typedef core::ThreadEventObject AnyMatchPointThreadEvent;

		/*!@class TaskBatchThreadEvent
		 * @brief General/base event concering task batch threads.
		 * @ingroup Events
		 */
		mapThreadEventMacro(TaskBatchThreadEvent, AnyMatchPointThreadEvent);

		/*!@class NextTaskThreadEvent
		 * @brief Event that is invoked if a task processing thread needs a now task.
		 * @ingroup Events
		 */
		mapThreadEventMacro(NextTaskThreadEvent, TaskBatchThreadEvent);

		/*!@class ProcessedTaskThreadEvent
		 * @brief Event that is invoked if a task processing thread has successfully processed a task.
		 * @ingroup Events
		 */
		mapThreadEventMacro(ProcessedTaskThreadEvent, TaskBatchThreadEvent);

		/*!@class FailedTaskThreadEvent
		 * @brief Event that is invoked if a task processing thread faild to process the task (e.g. an exception was raised).
		 * @ingroup Events
		 */
		mapThreadEventMacro(FailedTaskThreadEvent, TaskBatchThreadEvent);

		/*!@class ThreadTerminatingErrorEvent
		 * @brief Event that is invoked if a thread terminates because of an error.
		 * @ingroup Events
		 */
		mapThreadEventMacro(ThreadTerminatingErrorEvent, AnyMatchPointThreadEvent);
	}
}

#endif
