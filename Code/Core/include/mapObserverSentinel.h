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
			using Self = ObserverSentinel;
			using Superclass = ::itk::Object;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;

			itkTypeMacro(ObserverSentinel, ::itk::Object);

			static Pointer New(::itk::Object* pObserverOwner, const ::itk::EventObject& event,
							   itk::Command* pCmd);

			::itk::LightObject::Pointer CreateAnother() const override;

			using ObserverTagType = unsigned long;

			ObserverTagType getObserverTage() const;

		protected:
			/*! @pre pObserverOwner and pCmd must not be NULL.*/
			ObserverSentinel(::itk::Object* pObserverOwner, const ::itk::EventObject& event,
							 itk::Command* pCmd);
			~ObserverSentinel() override;

		private:
			ObserverTagType _tag;
			::itk::Object::Pointer _spObject;

			//No copy constructor allowed
			ObserverSentinel(const Self& source) = delete;
			void operator=(const Self&) = delete;  //purposely not implemented
		};

	}  // namespace core
}  // namespace map

#endif
