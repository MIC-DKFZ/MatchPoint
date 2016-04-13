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
// @version $Revision: 901 $ (last changed revision)
// @date    $Date: 2015-03-04 17:45:27 +0100 (Mi, 04 Mrz 2015) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/Common/boxed/mapDummyRegistrationAlgorithm.tpp $
*/


#ifndef __DUMMY_IMAGE_REGISTRATION_ALGORITHM_TPP
#define __DUMMY_IMAGE_REGISTRATION_ALGORITHM_TPP

#include <itkAffineTransform.h>

#include "mapAlgorithmException.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapRegistrationManipulator.h"

namespace map
{
	namespace algorithm
	{

		template<unsigned int VDimension, class TIdentificationPolicy>
		typename DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::FieldRepRequirement::Type
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		isMovingRepresentationRequired() const
		{
			return FieldRepRequirement::No;
		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		typename DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::FieldRepRequirement::Type
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		isTargetRepresentationRequired() const
		{
			return FieldRepRequirement::No;
		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		typename DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::AlgorithmType
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		getAlgorithmType() const
		{
			return Superclass::ATAnalytic;
		};


		template<unsigned int VDimension, class TIdentificationPolicy>
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		DummyRegistrationAlgorithm()
		{

		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		~DummyRegistrationAlgorithm()
		{
		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		bool
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		isReusable() const
		{
			return true;
		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		void
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		configureAlgorithm()
		{
		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		typename DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::RegistrationPointer
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		doGetRegistration() const
		{
			return _spFinalizedRegistration;
		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		bool
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		doDetermineRegistration()
		{
			RegistrationPointer spResult = NULL;

			typedef ::itk::AffineTransform< ::map::core::continuous::ScalarType, VDimension>  TransformModelType;

			typename TransformModelType::Pointer spFinalTransformModel = TransformModelType::New();

			spFinalTransformModel->SetIdentity();

			//now build the inverse kernel (main kernel of a image based registration algorithm)
      typedef core::PreCachedRegistrationKernel<VDimension, VDimension>
			InverseKernelType;
      typedef core::PreCachedRegistrationKernel<VDimension, VDimension>
			DirectKernelType;

			typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
			spIKernel->setTransformModel(spFinalTransformModel);

			typename DirectKernelType::Pointer spDKernel = DirectKernelType::New();
			spDKernel->setTransformModel(spFinalTransformModel);

			//now create the registration an set the kernels
			spResult = RegistrationType::New();
			::map::core::RegistrationManipulator<RegistrationType> manipulator(spResult);

			manipulator.setDirectMapping(spDKernel);
			manipulator.setInverseMapping(spIKernel);
			manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

			_spFinalizedRegistration = spResult;

			return true;
		};


		template<unsigned int VDimension, class TIdentificationPolicy>
		bool
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		registrationIsOutdated() const
		{
			bool outdated = _spFinalizedRegistration.IsNull();

			return outdated;
		};

		template<unsigned int VDimension, class TIdentificationPolicy>
		void
		DummyRegistrationAlgorithm<VDimension, TIdentificationPolicy>::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
		};


	} // end namespace algorithm
} // end namespace map

#endif
