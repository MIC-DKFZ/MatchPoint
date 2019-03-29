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




#ifndef __FIXED_INTERPOLATOR_POLICY_H
#define __FIXED_INTERPOLATOR_POLICY_H

#include "mapSealedInterpolatorPolicy.h"
#include "mapITKInterpolatorGetterInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class FixedInterpolatorPolicy
			@brief class for FixedInterpolatorPolicy.

			This class is a FixedInterpolatorPolicy. It is used if an ITKImageRegistrationAlgorithm
			should have one specific interpolator type and it is never to be changed.
			@sa SealedInterpolatorPolicy
			@sa ArbitraryInterpolatorPolicy
			@ingroup ITKPolicies
			*/

			template<class TConcreteInterpolator>
			class FixedInterpolatorPolicy : public SealedInterpolatorPolicy<TConcreteInterpolator>,
				public facet::ITKInterpolatorGetterInterface < typename TConcreteInterpolator::InputImageType,
				typename TConcreteInterpolator::CoordRepType >
			{
			public:
				using Self = FixedInterpolatorPolicy<TConcreteInterpolator>;
				using Superclass = SealedInterpolatorPolicy<TConcreteInterpolator>;

				using ConcreteInterpolatorType = typename Superclass::ConcreteInterpolatorType;
				using ConcreteInterpolatorPointer = typename Superclass::ConcreteInterpolatorPointer;
				using InterpolatorType = typename Superclass::InterpolatorType;
				using CoordRepType = typename Superclass::CoordRepType;

				using Superclass::getConcreteInterpolator;

				virtual const InterpolatorType* getInterpolator() const;
				virtual InterpolatorType* getInterpolator();

			protected:
				FixedInterpolatorPolicy();
				~FixedInterpolatorPolicy();


			private:
				//No copy constructor allowed
				FixedInterpolatorPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};



		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#ifdef MAP_SEAL_ALGORITHMS
#define SealedFixedInterpolatorPolicyMacro ::map::algorithm::itk::SealedInterpolatorPolicy
#else
#define SealedFixedInterpolatorPolicyMacro ::map::algorithm::itk::FixedInterpolatorPolicy
#endif

#ifndef MatchPoint_MANUAL_TPP
#include "mapFixedInterpolatorPolicy.tpp"
#endif

#endif
