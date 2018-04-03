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




#ifndef __SEALED_IMAGE_PYRAMIDES_POLICY_H
#define __SEALED_IMAGE_PYRAMIDES_POLICY_H

#include "itkMultiResolutionPyramidImageFilter.h"
#include "itkCommand.h"

#include "mapNoComponentInitializationPolicy.h"

#include "mapModificationTimeValidator.h"


namespace map
{
	namespace algorithm
	{

		/*! @class SealedImagePyramidesPolicy
		@brief class for SealedImagePyramidesPolicy.

		This class is a SealedImagePyramidesPolicy. It is used if an ITKImageRegistrationAlgorithm
		should have one specific pyramide type. With this policy the pyramide is never to be changed and sealed, so
		that the instance and its setting aren't public.
		@sa FixedImagePyramidesPolicy
		@sa ArbitraryImagePyramidesPolicy
		@ingroup ITKPolicies
		*/

		template<class TConcreteMovingImagePyramide, class TConcreteTargetImagePyramide, class TInitializationPolicy = itk::NoComponentInitializationPolicy>
		class SealedImagePyramidesPolicy
		{
		public:
			typedef SealedImagePyramidesPolicy<TConcreteMovingImagePyramide, TConcreteTargetImagePyramide, TInitializationPolicy>
			Self;

			typedef TConcreteMovingImagePyramide ConcreteMovingImagePyramideType;
			typedef typename ConcreteMovingImagePyramideType::Pointer ConcreteMovingImagePyramidePointer;
			typedef ::itk::MultiResolutionPyramidImageFilter<typename ConcreteMovingImagePyramideType::InputImageType, typename ConcreteMovingImagePyramideType::InputImageType>
			MovingImagePyramideBaseType;
			typedef TConcreteTargetImagePyramide ConcreteTargetImagePyramideType;
			typedef typename ConcreteTargetImagePyramideType::Pointer ConcreteTargetImagePyramidePointer;
			typedef ::itk::MultiResolutionPyramidImageFilter<typename ConcreteTargetImagePyramideType::InputImageType, typename ConcreteTargetImagePyramideType::InputImageType>
			TargetImagePyramideBaseType;

			typedef typename TargetImagePyramideBaseType::Pointer  TargetImagePyramideBasePointer;
			typedef typename TargetImagePyramideBaseType::ConstPointer  TargetImagePyramidConstPointer;
			typedef typename MovingImagePyramideBaseType::Pointer MovingImagePyramideBasePointer;
			typedef typename MovingImagePyramideBaseType::ConstPointer MovingImagePyramidConstPointer;


			typedef typename TConcreteMovingImagePyramide::InputImageType MovingImageType;
			typedef typename TConcreteTargetImagePyramide::InputImageType TargetImageType;

			typedef TInitializationPolicy InitializationPolicy;

		protected:
			SealedImagePyramidesPolicy();
			~SealedImagePyramidesPolicy();

			/*! Returns the modification time of the policy (and its controlled component).
			* In this case the modification time is a pass through of the internal component.
			@eguarantee strong
			@return the modification time
			*/
			virtual unsigned long getMovingPyramideMTime() const;

			/*! Returns the modification time of the policy (and its controlled component).
			* In this case the modification time is a pass through of the internal component.
			@eguarantee strong
			@return the modification time
			*/
			virtual unsigned long getTargetPyramideMTime() const;

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
			MovingImagePyramideBaseType* getMovingPyramideInternal();
			const MovingImagePyramideBaseType* getMovingPyramideInternal() const;
			TargetImagePyramideBaseType* getTargetPyramideInternal();
			const TargetImagePyramideBaseType* getTargetPyramideInternal() const;

			/*! gets the concrete moving pyramide
			@eguarantee strong
			@return a pointer to a ConcreteMovingImagePyramideType object
			*/
			const ConcreteMovingImagePyramideType* getConcreteMovingPyramide() const;
			/*! gets the concrete target pyramide
			@eguarantee strong
			@return a pointer to a ConcreteTargetImagePyramideType object
			*/
			const ConcreteTargetImagePyramideType* getConcreteTargetPyramide() const;

			/*! gets the concrete moving pyramide
			@eguarantee strong
			@return a pointer to a ConcreteMovingImagePyramideType object
			*/
			ConcreteMovingImagePyramideType* getConcreteMovingPyramide();
			/*! gets the concrete target pyramide
			@eguarantee strong
			@return a pointer to a ConcreteTargetImagePyramideType object
			*/
			ConcreteTargetImagePyramideType* getConcreteTargetPyramide();

			/*! initializes the pyramides
			@eguarantee strong
			*/
			virtual void preparePyramides();

			/*! initializes the pyramides
			* after it was integrated in a controlling structur (e.g. registration algorithm)
			@eguarantee strong
			*/
			virtual void preparePyramidesAfterAssembly();

		private:
			::map::core::ModificationTimeValidator _movingPyramideMTime;

			::map::core::ModificationTimeValidator _targetPyramideMTime;

			/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
			* because the controlled object has changed.*/
			ConcreteMovingImagePyramidePointer _spMovingPyramide;

			/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
			* because the controlled object has changed.*/
			ConcreteMovingImagePyramidePointer _spTargetPyramide;

			//No copy constructor allowed
			SealedImagePyramidesPolicy(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

	}
}


#ifndef MatchPoint_MANUAL_TPP
#include "mapSealedImagePyramidesPolicy.tpp"
#endif

#endif
