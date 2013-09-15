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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapMultiResRegistrationAlgorithmBase.h $
*/




#ifndef __MULTI_RES_REGISTRATION_ALGORITHM_BASE_H
#define __MULTI_RES_REGISTRATION_ALGORITHM_BASE_H

#include "mapMultiResRegistrationAlgorithmInterface.h"
#include "mapMultiResRegistrationAlgorithmSetterInterface.h"
#include "mapMacros.h"
#include "mapMAPAlgorithmsExports.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{

		/*! @class MultiResRegistrationAlgorithmBase
		This is the default implementation of the interface for multi resolution / multi scale algorithms that also support the setting of the resolution schedule.
		@ingroup AlgorithmFacets
		@remark Algorithms that want to support resolution events and
		implement this interface should use the ResolutionChangedEventt
		to indicate the beginning of the next resolution level usage
		@see map::events::AlgorithmIterationEvent
		*/
		class MAPAlgorithms_EXPORT MultiResRegistrationAlgorithmBase : public facet::MultiResRegistrationAlgorithmInterface, public facet::MultiResRegistrationAlgorithmSetterInterface, public facet::MultiResScheduleSetterInterface
		{
		public:
			typedef MultiResRegistrationAlgorithmBase Self;

			typedef unsigned int DimensionCountType;
			typedef unsigned int ScalingType;
			typedef unsigned int ResolutionLevelCountType;
			typedef ::itk::Array2D<ScalingType> ScheduleType;

			/*! @brief sets the moving and the target schedule as copies of the
			passed schedule. Before the new schedule is set onScheduleChange will
			be called.
			@pre the 2nd Dimension of the passed schedule must equal the
			resolution dimension of moving and target information space.
			@pre the 1st Dimension of the schedule must be >=1 (hence it must have
			at least one resolution level).
			@eguarantee strong
			*/
			virtual void setSchedule(const ScheduleType &schedule);

			/*! @brief sets the moving and the target schedule as copies of the
			passed schedules. Before the new schedule is set onScheduleChange will
			be called.
			@pre the 2nd Dimension of the passed schedules must equal the
			resolution dimension of their information spaces.
			@pre the 1st Dimension of the passed schedules must be equal
			@pre the 1st Dimension of the schedule must be >1 (hence it must have
			at least one resolution level).
			@eguarantee strong
			*/
			virtual void setSchedule(const ScheduleType &movingSchedule, const ScheduleType &targetSchedule);

			/*! returns the current schedule for the moving information space
			@eguarantee strong*/
			virtual const ScheduleType &getMovingSchedule() const;

			/*! returns the current schedule for the target information space
			@eguarantee strong*/
			virtual const ScheduleType &getTargetSchedule() const;

			/*! returns the the resolution level count
			@eguarantee strong*/
			virtual ResolutionLevelCountType getResolutionLevels() const;

			/*! resets the both schedules to the passed level count.
			The sub sampling rate of a level is 2^(levels - n). n is the
			current level (starting with 1).\n
			Passing 4 will therefore generate 8, 4, 2, 1.
			@pre "levels" must be >0.
			*/
			virtual void setResolutionLevels(ResolutionLevelCountType levels);

			/*! @brief gets the number of the algorithm's current resolution levekiteration
			@eguarantee strong
			@return returns the algorithm's current level. If the algorithm is not able to deduce (hasLevelCount()==false) this information, 0 will be returned.
			@retval an IterationCountType specifying the current iteration
			@eguarantee strong
			*/
			virtual ResolutionLevelCountType getCurrentLevel() const;

		protected:
			MultiResRegistrationAlgorithmBase();
			virtual ~MultiResRegistrationAlgorithmBase();

			/*! Method is called when the schedules are going to be changed.
			Overwrite this method to create special algorithmic behaviour.
			@post new moving and target schedule must be have still valid dimensions. 1st dimension must be equal vor both schedules
			2nd dimesion must be euqal to the dimension count of the according information space.
			@eguarantee strong
			*/
			virtual void onScheduleChange(const ScheduleType &oldMovingSchedule, ScheduleType &newMovingSchedule, const ScheduleType &oldTargetSchedule, ScheduleType &newTargetMovingSchedule) const;

			/*! return the current resolution level number.
			Will be called by getCurrentLevel() if hasLevelCount() returns true.
			@eguarantee strong
			@return level count
			*/
			virtual ResolutionLevelCountType doGetCurrentLevel() const = 0;

			ScheduleType _movingResSchedule;
			ScheduleType _targetResSchedule;

		private:
			//No copy constructor allowed
			MultiResRegistrationAlgorithmBase(const Self &source); //purposely not implemented
			void operator=(const Self &); //purposely not implemented

		};

	}
}

#endif
