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




#ifndef __ARBITRARY_IMAGE_PYRAMIDE_POLICY_H
#define __ARBITRARY_IMAGE_PYRAMIDE_POLICY_H

#include "mapContinuous.h"
#include "mapImagePyramidesSetterInterface.h"
#include "mapImagePyramidesGetterInterface.h"
#include "mapModificationTimeValidator.h"

#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{

		/*! @class ArbitraryImagePyramidesPolicy
		@brief class for ArbitraryImagePyramidesPolicy.

		This class is a ArbitraryImagePyramidesPolicy. It is used if an algorithm implements
		a MultiResImageRegistrationAlgorithmBase and you want to allow that the pyramide
		can be set and get arbitrarily by the user (in contrary to FixedImagePyramidePolicy).
		@sa FixedImagePyramidePolicy
		@ingroup ITKPolicies
		*/

		template<class TMovingImage, class TTargetImage>
		class ArbitraryImagePyramidesPolicy : public
			facet::ImagePyramidesSetterInterface<TMovingImage, TTargetImage>,
		public facet::ImagePyramidesGetterInterface<TMovingImage, TTargetImage>
		{
		public:
			typedef ArbitraryImagePyramidesPolicy<TMovingImage, TTargetImage>      Self;
			typedef facet::ImagePyramidesSetterInterface<TMovingImage, TTargetImage>   Superclass;

			typedef TMovingImage MovingImageType;
			typedef TTargetImage TargetImageType;

            itkTypeMacroNoParent(ArbitraryImagePyramidesPolicy);

			/** Type of the image multiresolution pyramids. */
			typedef typename Superclass::TargetImagePyramideBaseType TargetImagePyramideBaseType;
			typedef typename Superclass::TargetImagePyramideBasePointer TargetImagePyramideBasePointer;
			typedef typename Superclass::MovingImagePyramideBaseType MovingImagePyramideBaseType;
			typedef typename Superclass::MovingImagePyramideBasePointer MovingImagePyramideBasePointer;

			/*! @brief sets the moving image pyramide
			@eguarantee strong
			@param pMovingMask a pointer to the moving image pyramide
			*/
			virtual void setMovingImagePyramide(MovingImagePyramideBaseType* pMovingPyramide);

			/*! @brief sets the target image pyramide
			@eguarantee strong
			@param pTargetMask a pointer to the moving image pyramide
			*/
			virtual void setTargetImagePyramide(TargetImagePyramideBaseType* pTargetPyramide);

			/*! @brief gets a  pointer to the moving image pyramide
			@eguarantee strong
			@return a pointer to the moving image pyramide
			*/
			virtual MovingImagePyramideBaseType* getMovingImagePyramide();

			/*! @brief gets a const pointer to the moving image pyramide
			@eguarantee strong
			@return a const pointer to the moving image pyramide
			*/
			virtual const MovingImagePyramideBaseType* getMovingImagePyramide() const;


			/*! @brief gets a  pointer to the target image pyramide
			@eguarantee strong
			@return a pointer to the target image pyramide
			*/
			virtual TargetImagePyramideBaseType* getTargetImagePyramide();

			/*! @brief gets a const pointer to the target image pyramide
			@eguarantee strong
			@return a const pointer to the target image pyramide
			*/
			virtual const TargetImagePyramideBaseType* getTargetImagePyramide() const;

		protected:
			ArbitraryImagePyramidesPolicy();
			~ArbitraryImagePyramidesPolicy();

			/*! This is a command slot that can be used by any class derivering from this policy
			* to get informed if the moving pyramide instances is changed. \n
			* Two events will be invoked with this command: \n
			* - UnregisterAlgorithmComponentEvent
			* - RegisterAlgorithmComponentEvent
			* .
			* The first one is used when the current pyramide is going to be replaced (by setMovingImagePyramide). The event data in this case
			* is a void pointer to the current (soon outdated) object. The second event will be called when the new image pyramide was set
			* (by setMovingImagePyramide). In this case the event data is a pointer to the new pyramide.*/
			::itk::Command::Pointer _spOnChangeMoving;

			/*! This is a command slot that can be used by any class derivering from this policy
			* to get informed if the target pyramide instances is changed. \n
			* Two events will be invoked with this command: \n
			* - UnregisterAlgorithmComponentEvent
			* - RegisterAlgorithmComponentEvent
			* .
			* The first one is used when the current pyramide is going to be replaced (by setTargetImagePyramide). The event data in this case
			* is a void pointer to the current (soon outdated) object. The second event will be called when the new image pyramide was set
			* (by setTargetImagePyramide). In this case the event data is a pointer to the new pyramide.*/
			::itk::Command::Pointer _spOnChangeTarget;

			/*! gets the internal pyramides
			@eguarantee strong
			@return a pointer to an pyramide type
			*/
			virtual MovingImagePyramideBaseType* getMovingPyramideInternal();
			virtual const MovingImagePyramideBaseType* getMovingPyramideInternal() const;
			virtual TargetImagePyramideBaseType* getTargetPyramideInternal();
			virtual const TargetImagePyramideBaseType* getTargetPyramideInternal() const;

			/*! initializes the pyramides
			@eguarantee strong
			*/
			void preparePyramides();

			/*! initializes the pyramides
			* after it was integrated in a controlling structur (e.g. registration algorithm)
			@eguarantee strong
			*/
			void preparePyramidesAfterAssembly();

			/** Return this modified time of the target pyramide.  */
			unsigned long getTargetPyramideMTime() const;

			/** Return this modified time of the moving pyramide.  */
			unsigned long getMovingPyramideMTime() const;

		private:
			::map::core::ModificationTimeValidator _movingPyramideMTime;

			::map::core::ModificationTimeValidator _targetPyramideMTime;

			/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
			* because the controlled object has changed.*/
			MovingImagePyramideBasePointer _spMovingPyramide;

			/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
			* because the controlled object has changed.*/
			TargetImagePyramideBasePointer _spTargetPyramide;

			//No copy constructor allowed
			ArbitraryImagePyramidesPolicy(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapArbitraryImagePyramidesPolicy.tpp"
#endif

#endif
