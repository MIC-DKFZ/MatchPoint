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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapModifiableMultiResImageRegistrationAlgorithmBase.tpp $
*/


#ifndef __MODIFIABLE_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_TPP
#define __MODIFIABLE_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_TPP

namespace map
{
	namespace algorithm
	{

		// **** public methods ****
		// ************************

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		void
		ModifiableMultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		setSchedule(const ScheduleType& schedule)
		{
			setSchedule(schedule, schedule);
		};

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		void
		ModifiableMultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		setResolutionLevels(ResolutionLevelCountType levels)
		{
			Superclass::setResolutionLevels(levels);
		};

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		void
		ModifiableMultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		setSchedule(const ScheduleType& movingSchedule, const ScheduleType& targetSchedule)
		{
			Superclass::setSchedule(movingSchedule, targetSchedule);
		};


		// **** protected methods ****
		// ***************************

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		ModifiableMultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		~ModifiableMultiResImageRegistrationAlgorithmBase() {}

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		ModifiableMultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		ModifiableMultiResImageRegistrationAlgorithmBase()
		{
		}

	} // end namespace algorithms
} // end namespace map

#endif
