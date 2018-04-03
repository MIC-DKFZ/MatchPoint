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




#ifndef __SEALED_OPTIMIZER_POLICY_H
#define __SEALED_OPTIMIZER_POLICY_H

#include "mapITKOptimizerControl.h"

#include "itkOptimizer.h"
#include "itkCommand.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{
			/*! @class SealedOptimizerPolicy
			@brief class for SealedOptimizerPolicy.

			This class is a SealedOptimizerPolicy. It is used if an ITKImageRegistrationAlgorithm
			should have one specific optimizer type. With this policy the optimizer is never
			to be changed and sealed, so that the instance and its setting aren't public.
			@sa FixedSVNLOptimizerPolicy
			@sa ArbitrarySVNLOptimizerPolicy
			@sa FixedMVNLOptimizerPolicy
			@sa ArbitraryMVNLOptimizerPolicy
			@ingroup ITKPolicies
			*/
			template<class TConcreteOptimizer>
			class SealedOptimizerPolicy
			{
			public:
				typedef SealedOptimizerPolicy<TConcreteOptimizer>      Self;

				typedef TConcreteOptimizer ConcreteOptimizerType;
				typedef typename ConcreteOptimizerType::Pointer ConcreteOptimizerPointer;
				typedef ::itk::Optimizer OptimizerType;
				typedef ITKOptimizerControl<TConcreteOptimizer> ConcreteOptimizerControlType;
				typedef typename ConcreteOptimizerControlType::Pointer ConcreteOptimizerControlPointer;
				typedef typename ConcreteOptimizerControlType::BaseInterfaceType InternalOptimizerControlType;

			protected:
				SealedOptimizerPolicy();
				~SealedOptimizerPolicy();

				/*! This is a command slot that can be used by any class deriving from this policy
				 * to get informed if the component instances is changed.
				 * @remark In the case of fixed policy (they don't allow the change of the instance, like this policy)
				 * the command will invoke no event. The command is present because it is part of a general policy API that
				 * allows policy using classes to interact in the same way with fixed and arbitrary policies.
				 */
				::itk::Command::Pointer _spOnChange;

				/*! gets the internal optimizer
				@eguarantee strong
				@return a pointer to an OptimizerType object
				*/
				InternalOptimizerControlType* getOptimizerInternal();
				const InternalOptimizerControlType* getOptimizerInternal() const;

				/*! gets the concrete optimizer control
				* @eguarantee strong
				* @return a pointer to a ConcreteOptimizerControlType object
				*/
				ConcreteOptimizerControlType* getConcreteOptimizerControl();
				/*! gets the concrete optimizer control
				* @eguarantee strong
				* @return a pointer to a ConcreteOptimizerControlType object
				*/
				const ConcreteOptimizerControlType* getConcreteOptimizerControl() const;

				/*! gets the concrete wrapped optimizer
				* @eguarantee strong
				* @return a pointer to a ConcreteOptimizerType object
				*/
				ConcreteOptimizerType* getConcreteITKOptimizer();
				/*! gets a concrete optimizer
				@eguarantee strong
				@return a pointer to a ConcreteOptimizerType object
				*/
				const ConcreteOptimizerType* getConcreteITKOptimizer() const;

				/*! initializes the optimizer
				Reimplement if you want to change the initialization of the optimizer
				in an algorithm. The default implementation does nothing.
				@eguarantee strong
				*/
				virtual void prepareOptimizer();

				/*! initializes the optimizer
				* after it was integrated in a controlling structure (e.g. registration algorithm)
				@eguarantee strong
				*/
				virtual void prepareOptimizerAfterAssembly(bool minimizeToOptimize);

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
				* because the initialization is going to change the intern object (e.g. prepareOptimizer() will change the settings of the optimizer)*/
				mutable ::itk::TimeStamp _mTime;

				ConcreteOptimizerControlPointer _spOptimizerControl;

				//No copy constructor allowed
				SealedOptimizerPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapSealedOptimizerPolicy.tpp"
#endif

#endif
