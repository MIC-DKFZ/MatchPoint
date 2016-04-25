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


#ifndef __MAP_REGISTRATION_COMBINATOR_TPP
#define __MAP_REGISTRATION_COMBINATOR_TPP

#include "mapRegistrationCombinator.h"
#include "mapRegistrationManipulator.h"
#include "mapMissingProviderException.h"

namespace map
{
	namespace core
	{
		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		typename RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::CombinedRegistrationPointer
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		process(const PreRegistrationType& preRegistration, const RegistrationType& registration,
				InitialisationStyleType initStyle) const
		{
			return process(preRegistration, registration,
						   preRegistration.getDirectFieldRepresentation().GetPointer(),
						   registration.getInverseFieldRepresentation().GetPointer(), initStyle);
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		typename RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::CombinedRegistrationPointer
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		process(const PreRegistrationType& preRegistration, const RegistrationType& registration,
				const CombinedDirectFieldRepresentationType* pDirectRepresentation,
				const CombinedInverseFieldRepresentationType* pInverseRepresentation,
				InitialisationStyleType initStyle) const
		{
			typename DirectKernelCombinatorBaseType::RequestType directRequest(
				preRegistration.getDirectMapping(), registration.getDirectMapping());
			typename InverseKernelCombinatorBaseType::RequestType inverseRequest(
				registration.getInverseMapping(), preRegistration.getInverseMapping());

			DirectKernelCombinatorBaseType* pDirectCombinator = DirectKernelCombinatorStackType::getProvider(
						directRequest);
			InverseKernelCombinatorBaseType* pInverseCombinator = InverseKernelCombinatorStackType::getProvider(
						inverseRequest);

			mapLogInfoMacro( << "Combine registrations. Registration 1: " << preRegistration << std::endl <<
							 " Registration 2:" << registration);

			if (!pDirectCombinator)
			{
				mapExceptionMacro(MissingProviderException,
								  << "No responsible combinator available for given direct request. Request:" << directRequest);
			}

			if (!pInverseCombinator)
			{
				mapExceptionMacro(MissingProviderException,
								  << "No responsible combinator available for given inverse request. Request:" << inverseRequest);
			}

			CombinedRegistrationPointer spCombinedRegistration = CombinedRegistrationType::New();

			typename CombinedRegistrationType::DirectMappingType::Pointer spDirectKernel =
				pDirectCombinator->combineKernels(directRequest, pDirectRepresentation, _useDirectPadding,
												  _directPaddingVector);
			typename CombinedRegistrationType::InverseMappingType::Pointer spInverseKernel =
				pInverseCombinator->combineKernels(inverseRequest, pInverseRepresentation, _useInversePadding,
												   _inversePaddingVector);

			assert(spDirectKernel.IsNotNull());
			assert(spInverseKernel.IsNotNull());

			RegistrationManipulator<CombinedRegistrationType> manipulator(spCombinedRegistration.GetPointer());
			manipulator.setDirectMapping(spDirectKernel);
			manipulator.setInverseMapping(spInverseKernel);

			if (initStyle == InitialisationStyle::DirectMapping
				|| initStyle == InitialisationStyle::CompleteRegistration)
			{
				mapLogInfoMacro( << "precompute direct kernel of combined registration");
				spDirectKernel->precomputeKernel();
			}

			if (initStyle == InitialisationStyle::InverseMapping
				|| initStyle == InitialisationStyle::CompleteRegistration)
			{
				mapLogInfoMacro( << "precompute inverse kernel of combined registration");
				spInverseKernel->precomputeKernel();
			}

			return spCombinedRegistration;
		}


		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		bool
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		getUseDirectPadding() const
		{
			return _useDirectPadding;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		void
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		setUseDirectPadding(bool directPadding)
		{
			_useDirectPadding = directPadding;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		bool
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		getUseInversePadding() const
		{
			return _useInversePadding;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		void
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		setUseInversePadding(bool inversePadding)
		{
			_useInversePadding = inversePadding;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy>
		const typename
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::DirectMappingVectorType&
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		getDirectPaddingVector() const
		{
			return _directPaddingVector;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy>
		void
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		setDirectPaddingVector(const DirectMappingVectorType& vector)
		{
			_directPaddingVector = vector;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy>
		const typename
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::InverseMappingVectorType&
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		getInversePaddingVector() const
		{
			return _inversePaddingVector;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		void
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		setInversePaddingVector(const InverseMappingVectorType& vector)
		{
			_inversePaddingVector = vector;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		void
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "Use direct padding     :" << _useDirectPadding << std::endl;
			os << indent << "Direct padding vector  :" << _directPaddingVector << std::endl;
			os << indent << "Use inverse padding    :" << _useInversePadding << std::endl;
			os << indent << "Inverse padding vector :" << _inversePaddingVector << std::endl;
		}

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		RegistrationCombinator(): _useDirectPadding(false), _useInversePadding(false)
		{
        _directPaddingVector.Fill(itk::NumericTraits<map::core::continuous::ScalarType>::NonpositiveMin());
        _inversePaddingVector.Fill(itk::NumericTraits<map::core::continuous::ScalarType>::NonpositiveMin());
    }

		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy >
		RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>::
		~RegistrationCombinator()
		{}



	} // end namespace core
} // end namespace map

#endif
