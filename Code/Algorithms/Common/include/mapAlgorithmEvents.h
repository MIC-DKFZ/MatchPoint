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


#ifndef __MAP_ALGORITHM_EVENTS_H
#define __MAP_ALGORITHM_EVENTS_H

#include "mapEvents.h"
#include "mapMAPAlgorithmsExports.h"

namespace map
{
	namespace events
	{


		/*! @def mapEventMacro
		* Helper macro that creates events objects for map.
		*/
#define mapAlgorithmEventMacro( classname , super ) \
	/*! @ingroup Events */  \
	class MAPAlgorithms_EXPORT classname : public super { \
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

		/*!@class AlgorithmEvent
		 * @brief General/base event concering an algorithm or its processing.
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(AlgorithmEvent, AnyMatchPointEvent);

		/*!@class AlgorithmIterationEvent
		 * @brief Event is invoked when an algorithm iterates
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(AlgorithmIterationEvent, AlgorithmEvent);

		/*!@class AlgorithmResolutionLevelEvent
		 * @brief Event is invoked when an algorithm  starts a new resolution level
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(AlgorithmResolutionLevelEvent, AlgorithmEvent);

		/*!@class InitializingAlgorithmEvent
		 * @brief Event is invoked when an algorithm initializes
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(InitializingAlgorithmEvent, AlgorithmEvent);

		/*!@class StartingAlgorithmEvent
		 * @brief Event is invoked when an algorithm starting to determin its results (e.g. finding a proper registration)
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(StartingAlgorithmEvent, AlgorithmEvent);

		/*!@class StoppingAlgorithmEvent
		 * @brief Event is invoked when an algorithm is about to being stopped (e.g. by user interaction)
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(StoppingAlgorithmEvent, AlgorithmEvent);

		/*!@class StoppedAlgorithmEvent
		 * @brief Event is invoked when an algorithm is stopped but has no final results
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(StoppedAlgorithmEvent, AlgorithmEvent);

		/*!@class FinalizingAlgorithmEvent
		 * @brief Event is invoked when an algorithm finalizes its results (e.g. calculating the transformatino field)
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(FinalizingAlgorithmEvent, AlgorithmEvent);

		/*!@class FinalizedAlgorithmEvent
		 * @brief Event is invoked when an algorithm is finalized and has results
		 * @ingroup Events
		 */
		mapAlgorithmEventMacro(FinalizedAlgorithmEvent, AlgorithmEvent);

		/*!@class RegisterAlgorithmComponentEvent
		 * @brief Event is invoked by algorithms policy, if the policy registers a new component
		 * (e.g. ArbitraryTransformPolicy sets a new transform model, then the policy will invoke this event
		 * to inform the class that uses the policy about the now model.)
		 * @remark this event is normaly used internally and is not propergated outside of an algorithm.
		 * @ingroup InternalEvents
		 */
		mapAlgorithmEventMacro(RegisterAlgorithmComponentEvent, AlgorithmEvent);

		/*!@class UnregisterAlgorithmComponentEvent
		 * @brief Event is invoked by algorithms policy, if the policy unregisters the its current component
		 * (e.g. ArbitraryTransformPolicy sets a new transform model, then the policy will invoke this event
		 * to inform the class, that uses the policy about, that the current component will be outdated.)
		 * @remark this event is normaly used internally and is not propergated outside of an algorithm.
		 * @ingroup InternalEvents
		 */
		mapAlgorithmEventMacro(UnregisterAlgorithmComponentEvent, AlgorithmEvent);

	}
}

#endif
