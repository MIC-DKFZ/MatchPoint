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


#ifndef __MAP_ALGORITHM_WRAPPER_EVENT_H
#define __MAP_ALGORITHM_WRAPPER_EVENT_H

#include "mapAlgorithmEvents.h"

#include "itkObject.h"

namespace map
{
	namespace events
	{

		/*! @class AlgorithmWrapperEvent
		 * @ingroup Events*/
		class MAPAlgorithms_EXPORT AlgorithmWrapperEvent : public AlgorithmEvent
		{
		public:
			typedef AlgorithmWrapperEvent Self;
			typedef AlgorithmEvent Superclass;

			AlgorithmWrapperEvent(const ::itk::EventObject& wrappedEvent, ::itk::Object* wrappedCaller = NULL,
								  const std::string& comment = "");

			virtual ~AlgorithmWrapperEvent();

			virtual const char* GetEventName() const;

			virtual bool CheckEvent(const ::itk::EventObject* e) const;

			virtual ::itk::EventObject* MakeObject() const;

			AlgorithmWrapperEvent(const Self& s);

			::itk::EventObject& getWrappedEvent() const;
			::itk::Object* getWrappedCaller() const;

			virtual void Print(std::ostream& os) const;

		private:
			::itk::Object* _pWrappedCaller;
			::itk::EventObject* _pWrappedEvent;

			std::string _cachedEventName;

			void operator=(const Self&);
		};
	}
}

#endif
