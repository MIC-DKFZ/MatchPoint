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




#ifndef __IMAGE_PYRAMIDES_GETTER_INTERFACE_H
#define __IMAGE_PYRAMIDES_GETTER_INTERFACE_H

#include "itkMultiResolutionPyramidImageFilter.h"

namespace map
{
	namespace algorithm
	{
		namespace facet
		{
			/*! @class ImagePyramidesGetterInterface
			* Interface inherited by every algorithm that is able to get image pyramides
			@ingroup AlgorithmFacets
			*/

			template<class TMovingImage, class TTargetImage>
			class ImagePyramidesGetterInterface
			{
			public:
				typedef ImagePyramidesGetterInterface<TMovingImage, TTargetImage> Self;

				typedef TMovingImage MovingImageType;
				typedef TTargetImage TargetImageType;

				/** Type of the Fixed image multiresolution pyramid. */
				typedef ::itk::MultiResolutionPyramidImageFilter < TargetImageType,
						TargetImageType >
						TargetImagePyramideBaseType;
				typedef typename TargetImagePyramideBaseType::Pointer  TargetImagePyramideBasePointer;

				/** Type of the moving image multiresolution pyramid. */
				typedef ::itk::MultiResolutionPyramidImageFilter < MovingImageType,
						MovingImageType >
						MovingImagePyramideBaseType;
				typedef typename MovingImagePyramideBaseType::Pointer MovingImagePyramideBasePointer;

				/*! @brief gets a  pointer to the moving image pyramide
				@eguarantee strong
				@return a pointer to the moving image pyramide
				*/
				virtual MovingImagePyramideBaseType* getMovingImagePyramide() = 0;

				/*! @brief gets a const pointer to the moving image pyramide
				@eguarantee strong
				@return a const pointer to the moving image pyramide
				*/
				virtual const MovingImagePyramideBaseType* getMovingImagePyramide() const = 0;


				/*! @brief gets a  pointer to the target image pyramide
				@eguarantee strong
				@return a pointer to the target image pyramide
				*/
				virtual TargetImagePyramideBaseType* getTargetImagePyramide() = 0;

				/*! @brief gets a const pointer to the target image pyramide
				@eguarantee strong
				@return a const pointer to the target image pyramide
				*/
				virtual const TargetImagePyramideBaseType* getTargetImagePyramide() const = 0;

			protected:
				ImagePyramidesGetterInterface() {};
				virtual ~ImagePyramidesGetterInterface() {};

			private:
				//No copy constructor allowed
				ImagePyramidesGetterInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};
		}
	}
}


#endif
