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




#ifndef __IMAGE_PYRAMIDES_SETTER_INTERFACE_H
#define __IMAGE_PYRAMIDES_SETTER_INTERFACE_H

#include "itkMultiResolutionPyramidImageFilter.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class ImagePyramidesSetterInterface
			* Interface inherited by every algorithm that is able to set and change (by none const getter) image pyramides
			@ingroup AlgorithmFacets
			*/

			template<class TMovingImage, class TTargetImage>
			class ImagePyramidesSetterInterface
			{
			public:
				typedef ImagePyramidesSetterInterface<TMovingImage, TTargetImage> Self;

				typedef TMovingImage MovingImageType;
				typedef TTargetImage TargetImageType;

				/** Type of the Fixed image multiresolution pyramid. */
				typedef ::itk::MultiResolutionPyramidImageFilter < TargetImageType,
						TargetImageType >
						TargetImagePyramideBaseType;
				typedef typename TargetImagePyramideBaseType::Pointer  TargetImagePyramideBasePointer;
				typedef typename TargetImagePyramideBaseType::ConstPointer  TargetImagePyramidConstPointer;

				/** Type of the moving image multiresolution pyramid. */
				typedef ::itk::MultiResolutionPyramidImageFilter< MovingImageType, MovingImageType >
				MovingImagePyramideBaseType;
				typedef typename MovingImagePyramideBaseType::Pointer MovingImagePyramideBasePointer;
				typedef typename MovingImagePyramideBaseType::ConstPointer MovingImagePyramidConstPointer;

				/*! @brief sets the moving image pyramide
				@eguarantee strong
				@param pMovingMask a pointer to the moving image pyramide
				*/
				virtual void setMovingImagePyramide(MovingImagePyramideBaseType* pMovingPyramide) = 0;

				/*! @brief sets the target image pyramide
				@eguarantee strong
				@param pTargetMask a pointer to the moving image pyramide
				*/
				virtual void setTargetImagePyramide(TargetImagePyramideBaseType* pTargetPyramide) = 0;

			protected:
				ImagePyramidesSetterInterface() {};
				virtual ~ImagePyramidesSetterInterface() {};

			private:
				//No copy constructor allowed
				ImagePyramidesSetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};
		}
	}
}

#endif
