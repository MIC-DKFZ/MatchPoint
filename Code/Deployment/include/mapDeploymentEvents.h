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


#ifndef __MAP_DEPLOYMENT_EVENTS_H
#define __MAP_DEPLOYMENT_EVENTS_H

#include "mapEvents.h"

namespace map
{
	namespace events
	{

		/*! @def mapDeploymentEventMacro
		* Helper macro that creates events objects for map.
		*/
#define mapDeploymentEventMacro( classname , super ) \
	/*! @ingroup Events */  \
	class MAPDeployment_EXPORT classname : public super { \
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

		/*!@class ServiceEvent
		 * @brief General/base event concering deployment.
		 * @ingroup Events
		 * @ingroup DeploymentEvents
		 */
		mapDeploymentEventMacro(DeploymentEvent, AnyMatchPointEvent);

		/*!@class InvalidDLLEvent
		 * @brief Event concering the attempt to handle an invalid DLLs.
		 * @ingroup Events
		 */
		mapDeploymentEventMacro(InvalidDLLEvent, DeploymentEvent);

		/*!@class InvalidDLLEvent
		 * @brief Event is triggered in case of an access to an valid DLL.
		 *
		 * The data pointer passed with this event is a pointer to the corresponding
		 * map::deployment::DLLInfo structur.
		 * @ingroup Events
		 */
		mapDeploymentEventMacro(ValidDLLEvent, DeploymentEvent);

	}
}

#endif
