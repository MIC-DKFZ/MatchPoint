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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/include/mapImageRegistrationAlgorithmInterface.h $
*/




#ifndef __IMAGE_REGISTRATION_ALGORITHM_INTERFACE_H
#define __IMAGE_REGISTRATION_ALGORITHM_INTERFACE_H

#include "itkIndent.h"

/*! @namespace
*/
namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class ImageRegistrationAlgorithmInterface
			@brief This is the interface for image registration algorithms

			@ingroup AlgorithmFacets
			@template TMovingImage Type of the moving image
			@template TTargetImage Type of the target image
			*/
			template<class TMovingImage, class TTargetImage>
			class ImageRegistrationAlgorithmInterface

			{
			public:
				typedef ImageRegistrationAlgorithmInterface<TMovingImage, TTargetImage> Self;

				typedef TMovingImage MovingImageType;
				typedef TTargetImage TargetImageType;

				typedef typename MovingImageType::ConstPointer MovingImageConstPointer;
				typedef typename TargetImageType::ConstPointer TargetImageConstPointer;

				/*! @brief gets a const pointer to the moving image
				@eguarantee strong
				@return a const pointer to the moving image
				*/
				virtual MovingImageConstPointer getMovingImage() const = 0;

				/*! @brief gets a const pointer to the target image
				@eguarantee strong
				@return a const pointer to the target image
				*/
				virtual TargetImageConstPointer getTargetImage() const = 0;

				/*! @brief sets the moving image
				@eguarantee strong
				@param pMovingImage a pointer to the moving image
				*/
				virtual void setMovingImage(const MovingImageType *pMovingImage) = 0;

				/*! @brief sets the target image
				@eguarantee strong
				@param pTargetImage a pointer to the moving image
				*/
				virtual void setTargetImage(const TargetImageType *pTargetImage) = 0;

			protected:
				/*! @brief virtual destructor
				*/
				virtual ~ImageRegistrationAlgorithmInterface() {};

				ImageRegistrationAlgorithmInterface() {};

			private:
				//No copy constructor allowed
				ImageRegistrationAlgorithmInterface(const Self &source);
				void operator=(const Self &); //purposely not implemented
			};
		}
	}
}

#endif
