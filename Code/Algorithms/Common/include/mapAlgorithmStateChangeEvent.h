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


#ifndef __MAP_ALGORITHM_STATE_CHANGE_EVENTS_H
#define __MAP_ALGORITHM_STATE_CHANGE_EVENTS_H

#include "mapAlgorithmEvents.h"
#include "mapRegistrationAlgorithmBase.h"
#include "mapMAPAlgorithmsExports.h"

namespace map
{
	namespace events
	{

		/*! @class AlgorithmStateChangeEvent
		 * @ingroup Events*/
		class MAPAlgorithms_EXPORT AlgorithmStateChangeEvent : public AlgorithmEvent
		{
		public:
			using Self = AlgorithmStateChangeEvent;
			using Superclass = AlgorithmEvent;
			using AlgorithmStateType = algorithm::RegistrationAlgorithmBase::AlgorithmState::Type;

			AlgorithmStateChangeEvent(const AlgorithmStateType& oldState =
										  algorithm::RegistrationAlgorithmBase::AlgorithmState::Pending,
									  const AlgorithmStateType& newState = algorithm::RegistrationAlgorithmBase::AlgorithmState::Pending);

			~AlgorithmStateChangeEvent() override;

			const char* GetEventName() const override;

			bool CheckEvent(const ::itk::EventObject* e) const override;

			::itk::EventObject* MakeObject() const override;

			AlgorithmStateChangeEvent(const Self& s);

			AlgorithmStateType getOldState() const;
			AlgorithmStateType getNewState() const;

			void Print(std::ostream& os) const override;

		private:
			AlgorithmStateType _oldState;
			AlgorithmStateType _newState;
			void operator=(const Self&) = delete;
		};
	}  // namespace events
}  // namespace map

#endif
