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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapMultiResRegistrationAlgorithmSetterInterface.h $
*/




#ifndef __MULTI_RES_SCHEDULE_SETTER_INTERFACE_H
#define __MULTI_RES_SCHEDULE_SETTER_INTERFACE_H

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
			This is the interface for multi resolution/ multi scale algorithms that allow the setting of their resolution schedule.
			@ingroup AlgorithmFacets
			@see map::algorithm::facet::MultiResRegistrationAlgorithmInterface
			*/
			class MultiResScheduleSetterInterface
			{
			public:
				typedef MultiResScheduleSetterInterface Self;

				typedef MultiResRegistrationAlgorithmInterface::ScheduleType ScheduleType;

				/*! @brief sets the moving and the target schedule as copies of the
				passed schedule.
				@pre the 2nd Dimension of the passed schedule must equal the
				resolution dimension of moving and target information space.
				@pre the 1st Dimension of the schedule must be >1 (hence it must have
				at least one resolution level).
				@eguarantee strong
				*/
				virtual void setSchedule(const ScheduleType& schedule) = 0;

				/*! @brief sets the moving and the target schedule as copies of the
				passed schedules.
				@pre the 2nd Dimension of the passed schedules must equal the
				resolution dimension of their information spaces.
				@pre the 1st Dimension of the passed schedules must be equal
				@pre the 1st Dimension of the schedule must be >1 (hence it must have
				at least one resolution level).
				@eguarantee strong
				*/
				virtual void setSchedule(const ScheduleType& movingSchedule,
										 const ScheduleType& targetSchedule) = 0;

			protected:
				MultiResScheduleSetterInterface() {};
				virtual ~MultiResScheduleSetterInterface() {};

			private:
				//No copy constructor allowed
				MultiResScheduleSetterInterface(const Self& source); //purposely not implemented
				void operator=(const Self&);  //purposely not implemented

			};
		}
	}
}

#endif
