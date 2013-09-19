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




#ifndef __SEALED_TRANSFORM_POLICY_H
#define __SEALED_TRANSFORM_POLICY_H

#include "mapTransformModelBase.h"
#include "mapITKTransformModel.h"

#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class SealedTransformPolicy
			@brief class for SealedTransformPolicy.

			This class is a SealedTransformPolicy. It is used if an ITKImageRegistrationAlgorithm
			should have one specific transform model type. With this policy the transform model is never
			to be changed and sealed, so that the instance and its setting aren't public.
			@sa ArbitraryTransformPolicy
			@sa FixedTransformPolicy
			@ingroup ITKPolicies
			*/

			template<class TConcreteITKTransform>
			class SealedTransformPolicy
			{
			public:
				typedef SealedTransformPolicy<TConcreteITKTransform>      Self;


				typedef ITKTransformModel<TConcreteITKTransform> ConcreteTransformType;
				typedef typename ConcreteTransformType::Pointer ConcreteTransformPointer;
				typedef core::TransformModelBase<typename ConcreteTransformType::ScalarType, ConcreteTransformType::InputDimensions, ConcreteTransformType::OutputDimensions>
				TransformType;
				typedef typename TransformType::ScalarType TransformScalarType;

			protected:
				SealedTransformPolicy();
				~SealedTransformPolicy();

				/*! This is a command slot that can be used by any class derivering from this policy
				 * to get informed if the component instances is changed.
				 * @remark In the case of fixed policy (they don't allow the change of the instance, like this policy)
				 * the command will invoke no event. The command is present because it is part of a general policy API that
				 * allows policy using classes to interact in the same way with fixed and arbitrary policies.
				 */
				::itk::Command::Pointer _spOnChange;

				/*! gets the internal transform
				  @eguarantee strong
				  @return a pointer to an transform type
				*/
				TransformType* getTransformInternal();
				const TransformType* getTransformInternal() const;

				/*! gets the concrete transform
				 * @eguarantee strong
				 * @return a pointer to a ConcreteTransformType object
				*/
				ConcreteTransformType* getConcreteTransformModel();
				/*! gets the concrete transform
				  @eguarantee strong
				  @return a pointer to a ConcreteTransformType object
				*/
				const ConcreteTransformType* getConcreteTransformModel() const;

				/*! initializes the transform
				  @eguarantee strong
				*/
				virtual void prepareTransform();

				/*! initializes the transform
				 * after it was integrated in a controlling structur (e.g. registration algorithm)
				@eguarantee strong
				*/
				virtual void prepareTransformAfterAssembly();

				/*! Returns the modification time of the policy (and its controlled component).
				 * In this case the modification time is a pass through of the internal component.
				@eguarantee strong
				@return the modification time
				*/
				virtual unsigned long GetMTime() const;


				/*! This method can be used to indicate modification of the policy.
				*/
				void indicateModification() const;

			private:
				/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
				 * because the controlled object has changed.*/
				mutable ::itk::TimeStamp _mTime;

				ConcreteTransformPointer _spTransformModel;

				//No copy constructor allowed
				SealedTransformPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};


		}
	}
}


#ifndef MatchPoint_MANUAL_TPP
#include "mapSealedTransformPolicy.tpp"
#endif

#endif
