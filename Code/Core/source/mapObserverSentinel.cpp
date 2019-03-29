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



#include "mapObserverSentinel.h"
#include "mapExceptionObjectMacros.h"

#include <cassert>


namespace map
{
	namespace core
	{

		ObserverSentinel::Pointer
		ObserverSentinel::
		New(::itk::Object* pObserverOwner, const ::itk::EventObject& event, itk::Command* pCmd)
		{
			Pointer smartPtr;
			Self* rawPtr = new Self(pObserverOwner, event, pCmd);
			smartPtr = rawPtr;
			rawPtr->UnRegister();
			return smartPtr;
		}

		::itk::LightObject::Pointer
		ObserverSentinel::
		CreateAnother() const
		{
			mapDefaultExceptionMacro( << "CreateAnother not implemented for ObserverSentinel");
		}

		ObserverSentinel::ObserverTagType
		ObserverSentinel::
		getObserverTage() const
		{
			return _tag;
		};

		ObserverSentinel::
		ObserverSentinel(::itk::Object* pObserverOwner, const ::itk::EventObject& event, itk::Command* pCmd)
		{
			assert(pObserverOwner);
			assert(pCmd);
			_spObject = pObserverOwner;
			_tag = _spObject->AddObserver(event, pCmd);
		};

		ObserverSentinel::
		~ObserverSentinel()
		{
			_spObject->RemoveObserver(_tag);
		};

	}  // namespace core
}  // namespace map
