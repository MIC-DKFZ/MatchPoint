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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapModifiableMultiResImageRegistrationAlgorithmBase.h $
*/




#ifndef __MODIFIABLE_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_H
#define __MODIFIABLE_MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_H

#include "itkIndent.h"
#include "itkMultiResolutionPyramidImageFilter.h"
#include "itkConceptChecking.h"

#include "mapMultiResImageRegistrationAlgorithmBase.h"
#include "mapMultiResRegistrationAlgorithmSetterInterface.h"
#include "mapMultiResScheduleSetterInterface.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{

		/*! @class ModifiableMultiResImageRegistrationAlgorithmBase
		 *@brief Extension of MultiResImageRegistrationAlgorithmBase that implements public
		 * facets for setting resolution level and schedule.
		 *
		 * Use this base class, if you want to allow the changing of resolution levels or
		 * schedules from the outside. If you need a "read only" implementation, please
		 * use MultiResImageRegistrationAlgorithmBase.
		 * This base class allows depending on the used pyramide policy to set the pyramide types. (see ImagePyramideSetterInterface and ImagePyramideSetterInterface
		 * added by TPyramidesPolicy; e.g. ArbitraryImagePyramidePolicy)
		 *
		 *@ingroup AlgorithmFacets
		 *@template TMovingImage the type of the moving image
		 *@template TTargetImage the type of the target image
		 *@template TPyramidesPolicy Policy that defines how the image pyramides can be changed an what interfaces are offered by the base class.
		 */
		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy >
		class ModifiableMultiResImageRegistrationAlgorithmBase: public
			MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>,
		public facet::MultiResScheduleSetterInterface,
		public facet::MultiResRegistrationAlgorithmSetterInterface
		{
		public:
			typedef TMovingImage MovingImageType;
			typedef TTargetImage TargetImageType;
			typedef TPyramidesPolicy PyramidesPolicyType;

			typedef ModifiableMultiResImageRegistrationAlgorithmBase<MovingImageType, TargetImageType, TPyramidesPolicy >
			Self;
			typedef MultiResImageRegistrationAlgorithmBase<MovingImageType, TargetImageType, TPyramidesPolicy >
			Superclass;

			/** Type of pyramid schedule type */
			typedef typename Superclass::ResolutionLevelCountType ResolutionLevelCountType;
			typedef typename Superclass::ScheduleType ScheduleType;

			typedef typename PyramidesPolicyType::TargetImagePyramideBaseType TargetImagePyramideBaseType;
			typedef typename PyramidesPolicyType::TargetImagePyramideBasePointer TargetImagePyramideBasePointer;
			typedef typename PyramidesPolicyType::MovingImagePyramideBaseType MovingImagePyramideBaseType;
			typedef typename PyramidesPolicyType::MovingImagePyramideBasePointer MovingImagePyramideBasePointer;

			/*! @brief sets the moving and the target schedule as copies of the
			passed schedule. Before the new schedule is set onScheduleChange will
			be called.
			@pre the 2nd Dimension of the passed schedule must equal the
			resolution dimension of moving and target information space.
			@pre the 1st Dimension of the schedule must be >=1 (hence it must have
			at least one resolution level).
			@eguarantee strong
			*/
			virtual void setSchedule(const ScheduleType& schedule);

			/*! resets the both schedules to the passed level count.
			The sub sampling rate of a level is 2^(levels - n). n is the
			current level (starting with 1).\n
			Passing 4 will therefore generate 8, 4, 2, 1.
			@pre "levels" must be >0.
			*/
			virtual void setResolutionLevels(ResolutionLevelCountType levels);

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
			virtual void setSchedule(const ScheduleType& movingSchedule, const ScheduleType& targetSchedule);

		protected:
			/*! @brief virtual destructor
			*/
			virtual ~ModifiableMultiResImageRegistrationAlgorithmBase();

			ModifiableMultiResImageRegistrationAlgorithmBase();

		private:
			//No copy constructor allowed
			ModifiableMultiResImageRegistrationAlgorithmBase(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapModifiableMultiResImageRegistrationAlgorithmBase.tpp"
#endif


#endif
