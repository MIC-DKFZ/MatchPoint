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




#ifndef __ARBITRARY_INTERPOLATOR_POLICY_H
#define __ARBITRARY_INTERPOLATOR_POLICY_H

#include "mapContinuous.h"
#include "mapITKInterpolatorSetterInterface.h"
#include "mapITKInterpolatorGetterInterface.h"
#include "mapModificationTimeValidator.h"

#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ArbitraryInterpolatorPolicy
			@brief class for ArbitraryInterpolatorPolicy.

			This class is a ArbitraryInterpolatorPolicy. It is used if an ITKImageRegistrationAlgorithm
			should use an arbitrary interpolator that is to be set by the user (in contrary to FixedInterpolatorPolicy).
			@sa FixedInterpolatorPolicy
			@ingroup ITKPolicies
			*/

			template<class TInputImage, class TCoordRep = core::continuous::ScalarType>
			class ArbitraryInterpolatorPolicy : public
				facet::ITKInterpolatorSetterInterface<TInputImage, TCoordRep>,
			public facet::ITKInterpolatorGetterInterface<TInputImage, TCoordRep>
			{
			public:
				typedef ArbitraryInterpolatorPolicy<TInputImage, TCoordRep>      Self;
				typedef facet::ITKInterpolatorSetterInterface<TInputImage, TCoordRep>   Superclass;

                itkTypeMacroNoParent(ArbitraryInterpolatorPolicy);

				typedef ::itk::InterpolateImageFunction<TInputImage, TCoordRep> InterpolatorType;
				using CoordRepType = TCoordRep;

				/*! sets the interpolator
				@eguarantee strong
				@param pInterpolator the interpolator
				*/
				virtual void setInterpolator(InterpolatorType* pInterpolator);

				/*! gets the interpolator
				@eguarantee strong
				@return a pointer to the interpolator
				*/
				virtual InterpolatorType* getInterpolator();
				virtual const InterpolatorType* getInterpolator() const;

				/*! Returns the modification time of the policy (and its controlled component).
				 * In this case the modification time is a pass through of the internal component.
				@eguarantee strong
				@return the modification time
				*/
				virtual ::itk::ModifiedTimeType GetMTime() const;

			protected:
				ArbitraryInterpolatorPolicy();
				~ArbitraryInterpolatorPolicy();

				/*! This is a command slot that can be used by any class derivering from this policy
				 * to get informed if the component instances is changed. \n
				 * Two events will be invoked with this command: \n
				 * - UnregisterAlgorithmComponentEvent
				 * - RegisterAlgorithmComponentEvent
				 * .
				 * The first one is used when the current interpolator is going to be replaced (by setInterpolator). The event data in this case
				 * is a void pointer to the current (soon outdated) object. The second event will be called when the new interpolator was set
				 * (by setInterpolator). In this case the event data is a pointer to the new interpolator.*/
				::itk::Command::Pointer _spOnChange;

				/*! gets the internal interpolator
				@eguarantee strong
				@return a pointer to an interpolator type
				*/
				virtual InterpolatorType* getInterpolatorInternal();
				virtual const InterpolatorType* getInterpolatorInternal() const;

				/*! initializes the interpolator
				@eguarantee strong
				*/
				void prepareInterpolator();

				/*! initializes the interpolator
				 * after it was integrated in a controlling structur (e.g. registration algorithm)
				@eguarantee strong
				*/
				void prepareInterpolatorAfterAssembly();

			private:
				typename InterpolatorType::Pointer _spInterpolator;

				/*! The time stamp is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
				 * because the controlled object has changed.*/
				mutable core::ModificationTimeValidator _mTime;

				//No copy constructor allowed
				ArbitraryInterpolatorPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapArbitraryInterpolatorPolicy.tpp"
#endif

#endif
