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




#ifndef __MULTI_RES_REGISTRATION_ALGORITHM_SETTER_INTERFACE_H
#define __MULTI_RES_REGISTRATION_ALGORITHM_SETTER_INTERFACE_H

#include "mapMultiResRegistrationAlgorithmInterface.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class MultiResRegistrationAlgorithmSetterInterface
			This is the interface for multi resolution/ multi scale algorithms that allow the setting of there resolution schedule.
			@ingroup AlgorithmFacets
			@see map::algorithm::facet::MultiResRegistrationAlgorithmInterface
			*/
			class MultiResRegistrationAlgorithmSetterInterface
			{
			public:
				typedef MultiResRegistrationAlgorithmSetterInterface Self;

				typedef MultiResRegistrationAlgorithmInterface::ResolutionLevelCountType ResolutionLevelCountType;

				/*! resets the both schedules to the passed level count.
				The sub sampling rate of a level is 2^(levels - n). n is the
				current level (starting with 1).\n
				Passing 4 will therefore generate 8, 4, 2, 1.
				@pre "levels" must be >0.
				*/
				virtual void setResolutionLevels(ResolutionLevelCountType levels) = 0;

			protected:
				MultiResRegistrationAlgorithmSetterInterface() {};
				virtual ~MultiResRegistrationAlgorithmSetterInterface() {};

			private:
				//No copy constructor allowed
				MultiResRegistrationAlgorithmSetterInterface(const Self& source); //purposely not implemented
				void operator=(const Self&);  //purposely not implemented

			};
		}
	}
}

#endif
