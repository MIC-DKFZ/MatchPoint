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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/boxed/mapDummyImageRegistrationAlgorithm.tpp $
*/


#ifndef __DUMMY_IMAGE_REGISTRATION_ALGORITHM_TPP
#define __DUMMY_IMAGE_REGISTRATION_ALGORITHM_TPP

#include "mapAlgorithmException.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapRegistrationManipulator.h"
#include "../ITK/include/mapITKAffineTransform.h"

namespace map
{
	namespace algorithm
	{

    template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		typename DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::FieldRepRequirement::Type
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		isMovingRepresentationRequired() const
		{
			return FieldRepRequirement::No;
		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		typename DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::FieldRepRequirement::Type
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		isTargetRepresentationRequired() const
		{
			return FieldRepRequirement::No;
		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		typename DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::AlgorithmType
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		getAlgorithmType() const
		{
			return Superclass::ATAnalytic;
		};


		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		DummyImageRegistrationAlgorithm()
		{

		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		~DummyImageRegistrationAlgorithm()
		{
		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		bool
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		isReusable() const
		{
			return true;
		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		void
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		configureAlgorithm()
		{
		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		typename DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::RegistrationPointer
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		doGetRegistration() const
		{
			return _spFinalizedRegistration;
		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		bool
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		doDetermineRegistration()
		{
			RegistrationPointer spResult = NULL;

			typedef map::algorithm::itk::ITKTransformModel< ::itk::AffineTransform<core::continuous::ScalarType, RegistrationType::MovingDimensions> > TransformModelType;

			typename TransformModelType::Pointer spFinalTransformModel = TransformModelType::New();

			spFinalTransformModel->getConcreteTransform()->SetIdentity();

			//now build the inverse kernel (main kernel of a image based registration algorithm)
			typedef core::ModelBasedRegistrationKernel<RegistrationType::TargetDimensions, RegistrationType::MovingDimensions> InverseKernelType;
			typedef core::ModelBasedRegistrationKernel<RegistrationType::MovingDimensions, RegistrationType::TargetDimensions> DirectKernelType;

			typename InverseKernelType::Pointer spIKernel = InverseKernelType::New();
			spIKernel->setTransformModel(spFinalTransformModel);

			typename DirectKernelType::Pointer spDKernel = DirectKernelType::New();
			spDKernel->setTransformModel(spFinalTransformModel);

			//now create the registration an set the kernels
			spResult = RegistrationType::New();
			core::RegistrationManipulator<RegistrationType> manipulator(spResult);

			manipulator.setDirectMapping(spDKernel);
			manipulator.setInverseMapping(spIKernel);
			manipulator.getTagValues()[tags::AlgorithmUID] = this->getUID()->toStr();

			_spFinalizedRegistration = spResult;

			return true;
		};


		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		bool
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		registrationIsOutdated() const
		{
			bool outdated = _spFinalizedRegistration.IsNull();

			return outdated;
		};

		template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
		void
		DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy>::
		PrintSelf(std::ostream &os, ::itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>::PrintSelf(os, indent);
		};


	} // end namespace algorithm
} // end namespace map

#endif
