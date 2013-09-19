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




#ifndef __MULTI_RES_REGISTRATION_ALGORITHM_INTERFACE_H
#define __MULTI_RES_REGISTRATION_ALGORITHM_INTERFACE_H

#include "itkArray2D.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class MultiResRegistrationAlgorithmInterface
			This is the interface that should be implemented for algorithm that support multi resolution/ multi scale approaches.
			@ingroup AlgorithmFacets
			@remark Algorithms that want to support resolution events and
			implement this interface should use the ResolutionChangedEventt
			to indicate the beginning of the next resolution level usage
			@see map::events::AlgorithmIterationEvent
			@see map::algorithm::facet::MultiResRegistrationAlgorithmSetterInterface
			*/
			class MultiResRegistrationAlgorithmInterface
			{
			public:
				typedef MultiResRegistrationAlgorithmInterface Self;

				typedef unsigned int DimensionCountType;
				typedef unsigned int ScalingType;
				typedef unsigned int ResolutionLevelCountType;
				typedef ::itk::Array2D<ScalingType> ScheduleType;

				/*! @brief Returns the number of dimensions for the moving
				information space. Must be implemented by the algorithm
				that realizes the interface.
				@eguarantee strong
				*/
				virtual DimensionCountType getMovingResolutionDimensions() const = 0;

				/*! @brief Returns the number of dimensions for the target
				information space. Must be implemented by the algorithm
				that realizes the interface.
				@eguarantee strong
				*/
				virtual DimensionCountType getTargetResolutionDimensions() const = 0;

				/*! returns the current schedule for the moving information space
				@eguarantee strong*/
				virtual const ScheduleType& getMovingSchedule() const = 0;

				/*! returns the current schedule for the target information space
				@eguarantee strong*/
				virtual const ScheduleType& getTargetSchedule() const = 0;

				/*! returns the the resolution level count
				@eguarantee strong*/
				virtual ResolutionLevelCountType getResolutionLevels() const = 0;

				/*! Indicates if the current processed level can be deduced
				@eguarantee no fail
				*/
				virtual bool hasLevelCount() const = 0;

				/*! @brief gets the number of the algorithm's current resolution level
				@eguarantee strong
				@return returns the algorithm's current level. If the algorithm is not able to deduce (hasLevelCount()==false) this information, 0 will be returned.
				@retval an IterationCountType specifying the current iteration
				@eguarantee strong
				*/
				virtual ResolutionLevelCountType getCurrentLevel() const = 0;

			protected:
				MultiResRegistrationAlgorithmInterface() {};
				virtual ~MultiResRegistrationAlgorithmInterface() {};

			private:
				//No copy constructor allowed
				MultiResRegistrationAlgorithmInterface(const Self& source); //purposely not implemented
				void operator=(const Self&);  //purposely not implemented

			};
		}
	}
}

#endif
