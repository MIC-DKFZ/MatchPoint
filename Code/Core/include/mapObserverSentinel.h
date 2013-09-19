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




#ifndef __MAP_OBSERVER_SENTINEL_H
#define __MAP_OBSERVER_SENTINEL_H

#include "itkObject.h"
#include "itkCommand.h"

#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{

		/*! @class ObserverSentinel
		@brief Adds an observer to a given object and removes the observer when the sentinel is deleted.
		*/
		class MAPCore_EXPORT ObserverSentinel : public ::itk::Object
		{
		public:
			typedef ObserverSentinel Self;
			typedef ::itk::Object Superclass;
			typedef ::itk::SmartPointer<Self>         Pointer;
			typedef ::itk::SmartPointer<const Self>   ConstPointer;

			itkTypeMacro(ObserverSentinel, ::itk::Object);

			static Pointer New(::itk::Object* pObserverOwner, const ::itk::EventObject& event,
							   itk::Command* pCmd);

			virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			typedef unsigned long ObserverTagType;

			ObserverTagType getObserverTage() const;

		protected:
			/*! @pre pObserverOwner and pCmd must not be NULL.*/
			ObserverSentinel(::itk::Object* pObserverOwner, const ::itk::EventObject& event,
							 itk::Command* pCmd);
			virtual ~ObserverSentinel();

		private:
			ObserverTagType _tag;
			::itk::Object::Pointer _spObject;

			//No copy constructor allowed
			ObserverSentinel(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#endif
