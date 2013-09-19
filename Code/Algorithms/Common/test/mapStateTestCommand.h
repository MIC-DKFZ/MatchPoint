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

#ifndef __MAP_STATE_TEST_COMMAND_H
#define __MAP_STATE_TEST_COMMAND_H

#include "litCheckMacros.h"
#include "mapRegistrationAlgorithmBase.h"
#include "litTestCommand.h"

namespace map
{
	namespace testing
	{

		class StateTestCommand : public lit::TestCommand
		{
		public:
			/** Standard class typedefs. */
			typedef StateTestCommand   Self;
			typedef itk::SmartPointer<Self>    Pointer;

			/** Run-time type information (and related methods). */
			itkTypeMacro(StateTestCommand, TestCommand);

			/** Method for creation through the object factory. */
			itkNewMacro(Self);

			typedef algorithm::RegistrationAlgorithmBase::AlgorithmState::Type AlgorithmStateType;

			std::vector<AlgorithmStateType> _oldStates;
			std::vector<AlgorithmStateType> _newStates;

		protected:
			virtual void checkEvent(const itk::Object* caller, const itk::EventObject& e);

			StateTestCommand();
			virtual ~StateTestCommand();

		private:
			StateTestCommand(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} //namespace testing
} //namespace map

#endif