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




#ifndef __FIXED_TRANSFORM_POLICY_H
#define __FIXED_TRANSFORM_POLICY_H

#include "mapSealedTransformPolicy.h"
#include "mapITKTransformGetterInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class FixedTransformPolicy
			@brief class for FixedTransformPolicy.

			This class is a FixedTransformPolicy. It is used if an ITKImageRegistrationAlgorithm
			should have one specific transform model type and it is never to be changed.
			@sa ArbitraryTransformPolicy
			@sa SealedTransformPolicy
			@ingroup ITKPolicies
			*/

			template<class TConcreteITKTransform>
			class FixedTransformPolicy : public SealedTransformPolicy<TConcreteITKTransform>,
				public facet::ITKTransformGetterInterface < typename TConcreteITKTransform::ScalarType,
				TConcreteITKTransform::InputSpaceDimension,
				TConcreteITKTransform::OutputSpaceDimension >
			{
			public:
				using Self = FixedTransformPolicy<TConcreteITKTransform>;
				using Superclass = SealedTransformPolicy<TConcreteITKTransform>;

				using ConcreteTransformType = typename Superclass::ConcreteTransformType;
				using ConcreteTransformPointer = typename Superclass::ConcreteTransformPointer;
				using TransformType = typename Superclass::TransformType;
				using TransformScalarType = typename Superclass::TransformScalarType;

				/*! gets the transformation
				  @eguarantee strong
				  @return a pointer to the transform
				*/
				virtual TransformType* getTransformModel();
				virtual const TransformType* getTransformModel() const;

				using Superclass::getConcreteTransformModel;

			protected:


				FixedTransformPolicy();
				~FixedTransformPolicy();

			private:
				//No copy constructor allowed
				FixedTransformPolicy(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};


		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#ifdef MAP_SEAL_ALGORITHMS
#define SealedFixedTransformPolicyMacro ::map::algorithm::itk::SealedTransformPolicy
#else
#define SealedFixedTransformPolicyMacro ::map::algorithm::itk::FixedTransformPolicy
#endif

#ifndef MatchPoint_MANUAL_TPP
#include "mapFixedTransformPolicy.tpp"
#endif

#endif
