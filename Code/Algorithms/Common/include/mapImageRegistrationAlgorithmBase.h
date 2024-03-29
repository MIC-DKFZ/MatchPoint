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




#ifndef __IMAGE_REGISTRATION_ALGORITHM_BASE_H
#define __IMAGE_REGISTRATION_ALGORITHM_BASE_H

#include "itkIndent.h"
#include "itkTimeStamp.h"

#include "mapImageRegistrationAlgorithmInterface.h"

namespace map
{
	namespace algorithm
	{

		/*! @class ImageRegistrationAlgorithmBase
		@brief This is the interface for image registration algorithms

		@ingroup AlgorithmFacets
		@template TMovingImage Type of the moving image
		@template TTargetImage Type of the target image
		*/
		template<class TMovingImage, class TTargetImage>
		class ImageRegistrationAlgorithmBase : public
			facet::ImageRegistrationAlgorithmInterface<TMovingImage, TTargetImage>
		{
		public:
			typedef ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage> Self;

			using MovingImageType = TMovingImage;
			using TargetImageType = TTargetImage;

			using MovingImageConstPointer = typename MovingImageType::ConstPointer;
			using TargetImageConstPointer = typename TargetImageType::ConstPointer;

			/*! @brief gets a const pointer to the moving image
			@eguarantee strong
			@return a const pointer to the moving image
			*/
			MovingImageConstPointer getMovingImage() const;

			/*! @brief gets a const pointer to the target image
			@eguarantee strong
			@return a const pointer to the target image
			*/
			TargetImageConstPointer getTargetImage() const;

			/*! @brief sets the moving image
			@eguarantee strong
			@param pMovingImage a pointer to the moving image
			*/
			void setMovingImage(const MovingImageType* pMovingImage);

			/*! @brief sets the target image
			@eguarantee strong
			@param pTargetImage a pointer to the moving image
			*/
			void setTargetImage(const TargetImageType* pTargetImage);

		protected:
			/*! @brief virtual destructor
			*/
			virtual ~ImageRegistrationAlgorithmBase();

			ImageRegistrationAlgorithmBase();

			/*! Methods invoked by derivated classes.  */
			virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

			/** Return this modified time of the target image.  */
			::itk::ModifiedTimeType getTargetImageMTime() const;

			/** Return this modified time of the moving image.  */
			::itk::ModifiedTimeType getMovingImageMTime() const;

		private:

			MovingImageConstPointer _spMovingImage;
			::itk::TimeStamp _movingImageMTime;

			TargetImageConstPointer _spTargetImage;
			::itk::TimeStamp _targetImageMTime;


			//No copy constructor allowed
			ImageRegistrationAlgorithmBase(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapImageRegistrationAlgorithmBase.tpp"
#endif


#endif
