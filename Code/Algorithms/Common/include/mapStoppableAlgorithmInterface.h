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




#ifndef __STOPPABLE_ALGORITHM_INTERFACE_H
#define __STOPPABLE_ALGORITHM_INTERFACE_H

#include "mapMacros.h"
#include "mapMAPAlgorithmsExports.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class StoppableAlgorithmInterface
			@brief This is the interface for algorithms that can be stopped/aborted while they are determining the registration
			@ingroup AlgorithmFacets
			@remark Algorithms that allow to stop an ongoing registration process and
			implement this interface should use/emit StoppedAlgorithmEvent via the RegistrationAlgorithmBase to indicate
			when the algorithm really has stopped.
			@see map::events::StoppingAlgorithmEvent
			@see map::events::StoppedAlgorithmEvent
			*/
			class MAPAlgorithms_EXPORT StoppableAlgorithmInterface
			{
			public:
				using Self = StoppableAlgorithmInterface;

				/*! @brief stops the algorithm if it is stoppable.
				@remark A successful return of this function does not guarantee that the algorithm has already stopped. It only
				ensures that the algorithm will stop the current run as soon as possible. To be sure that the algorithm has stopped the current state
				should be checked via RegistrationAlgorithmBase or you should wait for the map::events::StoppedAlgorithmEvent.
				@eguarantee strong
				@retval true if the algorithm was successfully ordered to stop. This does not guarantee that the algorithm
				has already stopped when the function returns. But it ensures that the algorithm will be stopped as soon as possible.
				The algorithm should be observed for map::events::StoppedAlgorithmEvent.
				@retval false if the algorithm was not successfully ordered to stop.
				*/
				virtual bool stopAlgorithm() = 0;

				/*! @brief Returns if the algorithm is stoppable or not.
				@remark this function is needed because it is possible that algorithms are generally able to stop and therefore implement the interface,
				but the actual ability to stop depends on their current configuration.
				@eguarantee strong
				@retval true if the algorithm is stoppable
				@retval false if the algorithm is not stoppable
				*/
				virtual bool isStoppable() const = 0;

			protected:
				StoppableAlgorithmInterface();
				virtual ~StoppableAlgorithmInterface();

			private:
				//No copy constructor allowed
				StoppableAlgorithmInterface(const Self& source) = delete; //purposely not implemented
				void operator=(const Self&) = delete;  //purposely not implemented

			};
		}  // namespace facet
	}  // namespace algorithm
}  // namespace map

#endif
