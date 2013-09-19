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


#ifndef __MAP_EVENTS_H
#define __MAP_EVENTS_H

#include "itkEventObject.h"

#include "mapConfigure.h"
#include "mapMacros.h"
#include "mapMAPCoreExports.h"


namespace map
{
	namespace core
	{

		/** @class EventObject
		 * @brief Base object for all MatchPoint events
		 * @ingroup Events
		 * */
		class MAPCore_EXPORT EventObject : public itk::AnyEvent
		{
		public:
			typedef EventObject Self;
			typedef itk::AnyEvent Superclass;
			EventObject(void* pData = NULL, const std::string& comment = "");

			virtual ~EventObject();

			void* getData() const;

			const std::string& getComment() const;

			virtual const char* GetEventName() const;

			virtual bool CheckEvent(const ::itk::EventObject* e) const;

			virtual ::itk::EventObject* MakeObject() const;

			EventObject(const Self& s);

			virtual void Print(std::ostream& os) const;

		private:
			void* _pData;
			std::string _comment;
			void operator=(const Self&);
		};

		/*! @def mapEventMacro
		* Helper macro that creates events objects for map.
		*/
#define mapEventMacro( classname , super, export_tag ) \
	/*! @ingroup Events */  \
	class export_tag classname : public super { \
	public: \
		typedef classname Self; \
		typedef super Superclass; \
		classname(void* pData = NULL, const std::string& comment = ""): Superclass(pData, comment) {}\
		virtual ~classname() {} \
		virtual const char * GetEventName() const { return #classname; } \
		virtual bool CheckEvent(const ::itk::EventObject* e) const \
		{ return dynamic_cast<const Self*>(e); } \
		virtual ::itk::EventObject* MakeObject() const \
		{ return new Self(*this); } \
		classname(const Self& s) : Superclass(s) {}; \
	private: \
		void operator=(const Self&); \
	}
	}

	namespace events
	{
		/*!@class AnyMatchPointEvent
		 * @brief General event that can be used if you want to observe any event defined by MatchPoint.
		 * @ingroup Events
		 */
		typedef core::EventObject AnyMatchPointEvent;

		/*!@class ServiceEvent
		 * @brief General/base event concering a service strukture (e.g. ServiceStacks) or its processing.
		 * @ingroup Events
		 */
		mapEventMacro(ServiceEvent, AnyMatchPointEvent, MAPCore_EXPORT);

		/*!@class KernelEvent
		 * @brief General/base event concering a registration kernel.
		 * @ingroup Events
		 */
		mapEventMacro(KernelEvent, AnyMatchPointEvent, MAPCore_EXPORT);

		/*!@class KernelFieldComputationEvent
		 * @brief Event concering the processing of a registration kernel.
		 * @ingroup Events
		 */
		mapEventMacro(KernelFieldComputationEvent, KernelEvent, MAPCore_EXPORT);

		/*!@class RegistrationEvent
		 * @brief Event concering the registration of data.
		 * @ingroup Events
		 */
		mapEventMacro(RegistrationEvent, AnyMatchPointEvent, MAPCore_EXPORT);

		/*!@class TaskBatchEvent
		 * @brief General/base event concering a task batch (e.g. MappingTaskBatch) or its processing.
		 * @ingroup Events
		 */
		mapEventMacro(TaskBatchEvent, AnyMatchPointEvent, MAPCore_EXPORT);
	}
}

#endif
