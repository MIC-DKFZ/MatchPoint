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



#include "mapMultiResScheduleRegistrationAlgorithmBase.h"
#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace algorithm
	{

		MultiResScheduleRegistrationAlgorithmBase::
		MultiResScheduleRegistrationAlgorithmBase()
		{
		};

		MultiResScheduleRegistrationAlgorithmBase::
		~MultiResScheduleRegistrationAlgorithmBase()
		{
		};

		void
		MultiResScheduleRegistrationAlgorithmBase::
		setSchedule(const ScheduleType& schedule)
		{
			setSchedule(schedule, schedule);
		};

		void
		MultiResScheduleRegistrationAlgorithmBase::
		setSchedule(const ScheduleType& movingSchedule, const ScheduleType& targetSchedule)
		{
			if (movingSchedule.columns() != this->getMovingResolutionDimensions())
			{
				mapDefaultExceptionStaticMacro( <<
												"Error. Schedule of moving information space has wrong dimension (column count). Dimension: " <<
												this->getMovingResolutionDimensions() << "; columns: " << movingSchedule.columns());
			}

			if (targetSchedule.columns() != this->getTargetResolutionDimensions())
			{
				mapDefaultExceptionStaticMacro( <<
												"Error. Schedule of target information space has wrong dimension (column count). Dimension: " <<
												this->getTargetResolutionDimensions() << "; columns: " << targetSchedule.columns());
			}

			if (targetSchedule.rows() != movingSchedule.rows())
			{
				mapDefaultExceptionStaticMacro( << "Error. Schedules have different level count (rows). moving: " <<
												movingSchedule.rows() << "; " << targetSchedule.rows());
			}

			ScheduleType tempMovingSchedule = movingSchedule;
			ScheduleType tempTargetSchedule = targetSchedule;

			this->onScheduleChange(this->_movingResSchedule, tempMovingSchedule, this->_targetResSchedule,
								   tempTargetSchedule);

			this->_movingResSchedule = tempMovingSchedule;
			this->_targetResSchedule = tempTargetSchedule;
		};

		const MultiResScheduleRegistrationAlgorithmBase::ScheduleType&
		MultiResScheduleRegistrationAlgorithmBase::
		getMovingSchedule() const
		{
			return this->_movingResSchedule;
		};

		const MultiResScheduleRegistrationAlgorithmBase::ScheduleType&
		MultiResScheduleRegistrationAlgorithmBase::
		getTargetSchedule() const
		{
			return this->_targetResSchedule;
		};

		MultiResScheduleRegistrationAlgorithmBase::ResolutionLevelCountType
		MultiResScheduleRegistrationAlgorithmBase::
		getResolutionLevels() const
		{
			return _movingResSchedule.rows(); //both schedules must have the same number of rows.
		};

		void
		MultiResScheduleRegistrationAlgorithmBase::
		setResolutionLevels(ResolutionLevelCountType levels)
		{
			if (!(levels > 0))
			{
				mapDefaultExceptionStaticMacro( << "Error. Cannot set resolution level; passed level is 0.");
			}

			ScheduleType newMSched(levels, this->getMovingResolutionDimensions());
			ScheduleType newTSched(levels, this->getTargetResolutionDimensions());

			ScalingType s = 1;

			for (ResolutionLevelCountType i = 1; i <= levels; ++i, s = s * 2)
			{
				newMSched.set_row(levels - i, s);
				newTSched.set_row(levels - i, s);
			}

			this->setSchedule(newMSched, newTSched);
		};

		MultiResScheduleRegistrationAlgorithmBase::ResolutionLevelCountType
		MultiResScheduleRegistrationAlgorithmBase::
		getCurrentLevel() const
		{
			ResolutionLevelCountType result = 0;

			if (this->hasLevelCount())
			{
				result = this->doGetCurrentLevel();
			}

			return result;
		};

		void
		MultiResScheduleRegistrationAlgorithmBase::
		onScheduleChange(const ScheduleType& oldMovingSchedule, ScheduleType& newMovingSchedule,
						 const ScheduleType& oldTargetSchedule, ScheduleType& newTargetMovingSchedule) const
		{
			//default implementation does nothing.
			//reimplement if you want to react on level changes
			//or want to modify the new schedules befor they are set
		};

	}
}


