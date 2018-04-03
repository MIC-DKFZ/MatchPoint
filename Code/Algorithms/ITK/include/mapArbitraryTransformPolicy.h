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




#ifndef __ARBITRARY_TRANSFORM_POLICY_H
#define __ARBITRARY_TRANSFORM_POLICY_H

#include "mapITKTransformSetterInterface.h"
#include "mapITKTransformGetterInterface.h"
#include "mapModificationTimeValidator.h"

#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ArbitraryTransformPolicy
			@brief class for ArbitraryTransformPolicy.

			This class is a ArbitraryTransformPolicy. It is used if an ITKImageRegistrationAlgorithm
			should use an arbitrary transform model that is to be set by the user (in contrary to FixedTransformPolicy).
			@sa FixedTransformPolicy
			@ingroup ITKPolicies
			*/

			template<class TScalar, unsigned int VInputDimensions, unsigned int VOutputDimensions>
			class ArbitraryTransformPolicy: public
				facet::ITKTransformSetterInterface<TScalar, VInputDimensions, VOutputDimensions>,
			public facet::ITKTransformGetterInterface<TScalar, VInputDimensions, VOutputDimensions>
			{
			public:
				typedef ArbitraryTransformPolicy<TScalar, VInputDimensions, VOutputDimensions>      Self;
				typedef facet::ITKTransformSetterInterface<TScalar, VInputDimensions, VOutputDimensions>
				Superclass;
                itkTypeMacroNoParent(ArbitraryTransformPolicy);

				typedef typename Superclass::TransformType TransformType;
				typedef TScalar TransformScalarType;

				/*! sets the transfrom model
				@eguarantee strong
				@param pTransform the tranform model
				*/
				virtual void setTransformModel(TransformType* pTransform);

				/*! gets the transformation
				  @eguarantee strong
				  @return a pointer to the transform
				*/
				virtual TransformType* getTransformModel();
				virtual const TransformType* getTransformModel() const;

				/*! Returns the modification time of the policy (and its controlled component).
				 * In this case the modification time is a pass through of the internal component.
				@eguarantee strong
				@return the modification time
				*/
				virtual unsigned long GetMTime() const;

			protected:
				ArbitraryTransformPolicy();
				~ArbitraryTransformPolicy();

				/*! This is a command slot that can be used by any class derivering from this policy
				 * to get informed if the component instances is changed. \n
				 * Two events will be invoked with this command: \n
				 * - UnregisterAlgorithmComponentEvent
				 * - RegisterAlgorithmComponentEvent
				 * .
				 * The first one is used when the current transform is going to be replaced (by setTransformModel). The event data in this case
				 * is a void pointer to the current (soon outdated) object. The second event will be called when the new transform was set
				 * (by setTransformModel). In this case the event data is a pointer to the new transform.*/
				::itk::Command::Pointer _spOnChange;

				/*! gets the internal transformation
				  @eguarantee strong
				  @return a pointer to a transform type
				*/
				virtual TransformType* getTransformInternal();
				virtual const TransformType* getTransformInternal() const;

				/*! initializes the transform
				  @eguarantee strong
				*/
				void prepareTransform();

				/*! initializes the transform
				 * after it was integrated in a controlling structur (e.g. registration algorithm)
				@eguarantee strong
				*/
				void prepareTransformAfterAssembly();

			private:
				typename TransformType::Pointer _spTransformModel;

				/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
				 * because the controlled object has changed.*/
				mutable core::ModificationTimeValidator _mTime;

				//No copy constructor allowed
				ArbitraryTransformPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapArbitraryTransformPolicy.tpp"
#endif

#endif
