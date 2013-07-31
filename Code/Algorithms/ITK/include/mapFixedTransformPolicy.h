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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapFixedTransformPolicy.h $
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
				typedef FixedTransformPolicy<TConcreteITKTransform>     Self;
				typedef SealedTransformPolicy<TConcreteITKTransform>    Superclass;

				typedef typename Superclass::ConcreteTransformType     ConcreteTransformType;
				typedef typename Superclass::ConcreteTransformPointer  ConcreteTransformPointer;
				typedef typename Superclass::TransformType             TransformType;
				typedef typename Superclass::TransformScalarType       TransformScalarType;

				/*! gets the transformation
				  @eguarantee strong
				  @return a pointer to the transform
				*/
				virtual TransformType *getTransformModel();
				virtual const TransformType *getTransformModel() const;

				using Superclass::getConcreteTransformModel;

			protected:


				FixedTransformPolicy();
				~FixedTransformPolicy();

			private:
				//No copy constructor allowed
				FixedTransformPolicy(const Self &source);
				void operator=(const Self &); //purposely not implemented

			};


		}
	}
}

#ifdef MAP_SEAL_ALGORITHMS
#define SealedFixedTransformPolicyMacro ::map::algorithm::itk::SealedTransformPolicy
#else
#define SealedFixedTransformPolicyMacro ::map::algorithm::itk::FixedTransformPolicy
#endif

#ifndef MatchPoint_MANUAL_TPP
#include "mapFixedTransformPolicy.tpp"
#endif

#endif
