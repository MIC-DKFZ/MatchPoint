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



#include <mapRegistrationAlgorithmBase.h>
#include "mapAlgorithmStateChangeEvent.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
    mark code as components of this project
 */
namespace map
{
	namespace algorithm
	{

		bool
		RegistrationAlgorithmBase::
		determineRegistration()
		{
			return doDetermineRegistration();
		};

		RegistrationAlgorithmBase::
		RegistrationAlgorithmBase() : _currentState(AlgorithmState::Pending), _firstConfiguration(true)
		{
		};

		RegistrationAlgorithmBase::
		~RegistrationAlgorithmBase()
		{
		};

		bool
		RegistrationAlgorithmBase::
		isFirstConfiguration() const
		{
			return _firstConfiguration;
		};

		void
		RegistrationAlgorithmBase::
		doneFirstConfiguration()
		{
			_firstConfiguration = false;
		};

		/*! Methods invoked by itk::LightObject::Print().  */
		void
		RegistrationAlgorithmBase::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "Algorithm type:    " << this->getAlgorithmType() << std::endl;
			os << indent << "Algorithm state:   " << _currentState << std::endl;
			os << indent << "Moving dimensions: " << this->getMovingDimensions() << std::endl;
			os << indent << "Target dimensions: " << this->getTargetDimensions() << std::endl;
		};

		RegistrationAlgorithmBase::AlgorithmState::Type
		RegistrationAlgorithmBase::
		getCurrentState() const
		{
			return _currentState;
		};

		void
		RegistrationAlgorithmBase::
		setCurrentState(const AlgorithmState::Type& state)
		{
			StateLockHolderType holder(_stateLock);

			this->onStateChange(_currentState, state);
			this->InvokeEvent(events::AlgorithmStateChangeEvent(_currentState, state));
			_currentState = state;
		};

		void
		RegistrationAlgorithmBase::
		onStateChange(AlgorithmState::Type oldState, AlgorithmState::Type newState) const
		{
			//default implementation does nothing
		};

	}
}
