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




#ifndef __MASKED_REGISTRATION_ALGORITHM_INTERFACE_H
#define __MASKED_REGISTRATION_ALGORITHM_INTERFACE_H

#include "mapModificationTimeValidator.h"

#include "itkIndent.h"
#include "itkSpatialObject.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class MaskedRegistrationAlgorithmInterface
			*@brief This is the interface for registration algorithms that support
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
			class MaskedRegistrationAlgorithmInterface
			{
			public:
				typedef MaskedRegistrationAlgorithmInterface<VMovingDimension, VTargetDimension> Self;

				typedef ::itk::SpatialObject<VMovingDimension> MovingMaskBaseType;
				typedef ::itk::SpatialObject<VTargetDimension> TargetMaskBaseType;

				typedef typename MovingMaskBaseType::ConstPointer MovingMaskBaseConstPointer;
				typedef typename TargetMaskBaseType::ConstPointer TargetMaskBaseConstPointer;

				/*! @brief gets a const pointer to the moving mask
				@eguarantee strong
				@return a const pointer to the moving mask
				*/
				virtual MovingMaskBaseConstPointer getMovingMask() const = 0;

				/*! @brief gets a const pointer to the target mask
				@eguarantee strong
				@return a const pointer to the target mask
				*/
				virtual TargetMaskBaseConstPointer getTargetMask() const = 0;

				/*! @brief sets the moving mask
				@eguarantee strong
				@param pMovingMask a pointer to the moving mask
				*/
				virtual void setMovingMask(const MovingMaskBaseType* pMovingMask) = 0;

				/*! @brief sets the target mask
				@eguarantee strong
				@param pTargetMask a pointer to the moving mask
				*/
				virtual void setTargetMask(const TargetMaskBaseType* pTargetMask) = 0;

			protected:
				/*! @brief virtual destructor
				*/
				virtual ~MaskedRegistrationAlgorithmInterface() {};

				MaskedRegistrationAlgorithmInterface() {};

			private:
				//No copy constructor allowed
				MaskedRegistrationAlgorithmInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};
		}
	}
}

#endif
