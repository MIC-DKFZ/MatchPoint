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


#ifndef __IMAGE_REGISTRATION_ALGORITHM_INTERFACE_TPP
#define __IMAGE_REGISTRATION_ALGORITHM_INTERFACE_TPP

namespace map
{
	namespace algorithm
	{

		// **** public methods ****
		// ************************
		template<class TMovingImage, class TTargetImage>
		typename ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::MovingImageConstPointer
		ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::
		getMovingImage() const
		{
			return _spMovingImage;
		}

		template<class TMovingImage, class TTargetImage>
		typename ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::TargetImageConstPointer
		ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::
		getTargetImage() const
		{
			return _spTargetImage;
		}


		template<class TMovingImage, class TTargetImage>
		void
		ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::
		setMovingImage(const MovingImageType* pMovingImage)
		{
			_spMovingImage = pMovingImage;
		}

		template<class TMovingImage, class TTargetImage>
		void
		ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::
		setTargetImage(const TargetImageType* pTargetImage)
		{
			_spTargetImage = pTargetImage;
		}


		// **** protected methods ****
		// ***************************

		template<class TMovingImage, class TTargetImage>
		ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::
		~ImageRegistrationAlgorithmBase() {}

		template<class TMovingImage, class TTargetImage>
		ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::
		ImageRegistrationAlgorithmBase() {}

		template<class TMovingImage, class TTargetImage>
		void
		ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			os << indent << "Moving image: " << _spMovingImage.GetPointer() << std::endl;
			os << indent << "Target image: " << _spTargetImage.GetPointer() << std::endl;
		}

	} // end namespace algorithms
} // end namespace map

#endif
