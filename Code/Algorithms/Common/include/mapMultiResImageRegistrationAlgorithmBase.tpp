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


#ifndef __MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_TPP
#define __MULTI_RES_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_TPP

namespace map
{
	namespace algorithm
	{

		// **** public methods ****
		// ************************
		/*! @brief Returns the number of dimensions for the moving
		 information space.
		  @eguarantee strong
		 */
		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		typename MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::DimensionCountType
		MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		getMovingResolutionDimensions() const
		{
			return TMovingImage::ImageDimension;
		};

		/*! @brief Returns the number of dimensions for the target
		 information space.
		  @eguarantee strong
		 */
		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		typename MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::DimensionCountType
		MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		getTargetResolutionDimensions() const
		{
			return TTargetImage::ImageDimension;
		};

		// **** protected methods ****
		// ***************************

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		~MultiResImageRegistrationAlgorithmBase() {}

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		MultiResImageRegistrationAlgorithmBase()
		{
			//now set the policy event slots
			typedef ::itk::ReceptorMemberCommand<Self> AlgorithmCommandType;

			typename AlgorithmCommandType::Pointer spMovingPyramideCmd = AlgorithmCommandType::New();
			spMovingPyramideCmd->SetCallbackFunction(this, &Self::onMovingImagePyramideChangeHelper);
			PyramidesPolicyType::_spOnChangeMoving = spMovingPyramideCmd;

			typename AlgorithmCommandType::Pointer spTargetPyramideCmd = AlgorithmCommandType::New();
			spTargetPyramideCmd->SetCallbackFunction(this, &Self::onTargetImagePyramideChangeHelper);
			PyramidesPolicyType::_spOnChangeTarget = spTargetPyramideCmd;
		}

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		void
		MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			os << indent << "Moving pyramide: " << this->getMovingPyramideInternal() << std::endl;
			os << indent << "Target pyramide: " << this->getTargetPyramideInternal() << std::endl;
		}

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		void
		MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		onMovingImagePyramideChangeHelper(const ::itk::EventObject& eventObject)
		{
			onMovingImagePyramideChange(eventObject);
		}

		template<class TMovingImage, class TTargetImage, class TPyramidesPolicy>
		void
		MultiResImageRegistrationAlgorithmBase<TMovingImage, TTargetImage, TPyramidesPolicy>::
		onTargetImagePyramideChangeHelper(const ::itk::EventObject& eventObject)
		{
			onTargetImagePyramideChange(eventObject);
		}

	}  // namespace algorithm
} // end namespace map

#endif
