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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapMaskedRegistrationAlgorithmBase.h $
*/




#ifndef __MASKED_REGISTRATION_ALGORITHM_BASE_H
#define __MASKED_REGISTRATION_ALGORITHM_BASE_H

#include "mapModificationTimeValidator.h"
#include "mapMaskedRegistrationAlgorithmInterface.h"

#include "itkIndent.h"
#include "itkSpatialObject.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{

		/*! @class MaskedRegistrationAlgorithmBase
		 *@brief This is the default implementation for the MaskedRegistrationAlgorithmInterface for registration algorithms that support
		 *the definition of masks.
		 *
		 * The masks are composed via itk:SpatialObjects (e.g. images or geometric
		 * primitives). The masks define which part of the moving and target space/image will be regarded
		 * for the registration purpose.
		 * This interface requires/assumes that the axis of the masks (top level spatial object) are aligned
		 * with the according information space (e.g. in a image registration algorithm the axis of the target image
		 * should be aligned with the axis of the target mask).
		 *
		 *@ingroup AlgorithmFacets
		 *@template VMovingDimension Dimension of the moving space
		 *@template VTargetDimension Dimension of the target space
		 */
		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		class MaskedRegistrationAlgorithmBase : public facet::MaskedRegistrationAlgorithmInterface<VMovingDimension, VTargetDimension>
		{
		public:
			typedef MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension> Self;

			typedef ::itk::SpatialObject<VMovingDimension> MovingMaskBaseType;
			typedef ::itk::SpatialObject<VTargetDimension> TargetMaskBaseType;

			typedef typename MovingMaskBaseType::ConstPointer MovingMaskBaseConstPointer;
			typedef typename TargetMaskBaseType::ConstPointer TargetMaskBaseConstPointer;

			/*! @brief gets a const pointer to the moving mask
			@eguarantee strong
			@return a const pointer to the moving mask
			*/
			virtual MovingMaskBaseConstPointer getMovingMask() const;

			/*! @brief gets a const pointer to the target mask
			@eguarantee strong
			@return a const pointer to the target mask
			*/
			virtual TargetMaskBaseConstPointer getTargetMask() const;

			/*! @brief sets the moving mask
			@eguarantee strong
			@param pMovingMask a pointer to the moving mask
			*/
			virtual void setMovingMask(const MovingMaskBaseType *pMovingMask);

			/*! @brief sets the target mask
			@eguarantee strong
			@param pTargetMask a pointer to the moving mask
			*/
			virtual void setTargetMask(const TargetMaskBaseType *pTargetMask);

		protected:
			/*! @brief virtual destructor
			*/
			virtual ~MaskedRegistrationAlgorithmBase();

			MaskedRegistrationAlgorithmBase();

			/*! Methods invoked by derivated classes.  */
			virtual void PrintSelf(std::ostream &os, ::itk::Indent indent) const;

			/** Return this modified time of the target mask.  */
			unsigned long getTargetMaskMTime() const;

			/** Return this modified time of the moving mask.  */
			unsigned long getMovingMaskMTime() const;

		private:

			core::ModificationTimeValidator _movingMaskMTime;

			core::ModificationTimeValidator _targetMaskMTime;

			MovingMaskBaseConstPointer _spMovingMask;

			TargetMaskBaseConstPointer _spTargetMask;

			//No copy constructor allowed
			MaskedRegistrationAlgorithmBase(const Self &source);
			void operator=(const Self &); //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapMaskedRegistrationAlgorithmBase.tpp"
#endif


#endif
