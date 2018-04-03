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




#ifndef __FIXED_MVNL_OPTIMIZER_POLICY_H
#define __FIXED_MVNL_OPTIMIZER_POLICY_H

#include "mapSealedOptimizerPolicy.h"
#include "mapITKMVNLOptimizerGetterInterface.h"
#include "mapOptimizerGetterInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{
			/*! @class FixedMVNLOptimizerPolicy
			@brief class for FixedMVNLOptimizerPolicy.

			This class is a FixedMVNLOptimizerPolicy. It is used if an ITK registration algorithm
			should have one specific optimizer type and this optimizer is never to be changed.
			@sa SealedOptimizerPolicy
			@sa ArbitraryMVNLOptimizerPolicy
			@ingroup ITKPolicies
			*/
			template<class TConcreteOptimizer>
			class FixedMVNLOptimizerPolicy : public SealedOptimizerPolicy<TConcreteOptimizer>,
				public facet::ITKMVNLOptimizerGetterInterface, public facet::OptimizerGetterInterface
			{
			public:
				typedef FixedMVNLOptimizerPolicy<TConcreteOptimizer>     Self;
				typedef SealedOptimizerPolicy<TConcreteOptimizer>    Superclass;

				typedef typename Superclass::ConcreteOptimizerType           ConcreteOptimizerType;
				typedef typename Superclass::ConcreteOptimizerPointer        ConcreteOptimizerPointer;
				typedef typename Superclass::ConcreteOptimizerControlType    ConcreteOptimizerControlType;
				typedef typename Superclass::ConcreteOptimizerControlPointer ConcreteOptimizerControlPointer;
				typedef typename Superclass::OptimizerType                   OptimizerType;
				typedef typename Superclass::InternalOptimizerControlType    ITKOptimizerControlType;
				typedef typename facet::OptimizerGetterInterface::OptimizerControlType    OptimizerControlType;

				/*! @brief gets the optimizer
				  @eguarantee no fail
				  @return pointer to an OptimizerControlType object
				 */
				virtual ITKOptimizerControlType* getITKOptimizerControl();
				/*! @brief gets the optimizer
				  @eguarantee no fail
				  @return pointer to an OptimizerControlType object
				 */
				virtual const ITKOptimizerControlType* getITKOptimizerControl() const;

				/*! @brief gets the optimizer
				  @eguarantee no fail
				  @return pointer to an OptimizerControlType object
				 */
				virtual OptimizerControlType* getOptimizerControl();
				/*! @brief gets the optimizer
				  @eguarantee no fail
				  @return pointer to an OptimizerControlType object
				 */
				virtual const OptimizerControlType* getOptimizerControl() const;

				using Superclass::getConcreteITKOptimizer;
				using Superclass::getConcreteOptimizerControl;

			protected:

				FixedMVNLOptimizerPolicy();
				~FixedMVNLOptimizerPolicy();

			private:
				//No copy constructor allowed
				FixedMVNLOptimizerPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifdef MAP_SEAL_ALGORITHMS
#define SealedFixedMVNLOptimizerPolicyMacro ::map::algorithm::itk::SealedOptimizerPolicy
#else
#define SealedFixedMVNLOptimizerPolicyMacro ::map::algorithm::itk::FixedMVNLOptimizerPolicy
#endif

#ifndef MatchPoint_MANUAL_TPP
#include "mapFixedMVNLOptimizerPolicy.tpp"
#endif

#endif
