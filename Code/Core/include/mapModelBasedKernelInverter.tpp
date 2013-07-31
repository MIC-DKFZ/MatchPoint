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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapModelBasedKernelInverter.tpp $
*/

#ifndef __MAP_MODEL_BASED_KERNEL_INVERTER_TPP
#define __MAP_MODEL_BASED_KERNEL_INVERTER_TPP

#include "mapModelBasedKernelInverter.h"
#include "mapServiceException.h"
#include "mapFieldByModelInversionFunctor.h"
#include "mapFieldBasedRegistrationKernels.h"

namespace map
{
	namespace core
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		unsigned long
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getFunctorNumberOfIterations() const
		{
			return _functorNrOfIterations;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		setFunctorNumberOfIterations(unsigned long nrOfIterations)
		{
			_functorNrOfIterations = nrOfIterations;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		double
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getFunctorStopValue() const
		{
			return _functorStopValue;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		setFunctorStopValue(double stopValue)
		{
			_functorStopValue = stopValue;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType &request) const
		{
			// if the kernel "request" is a model-based kernel, then we can handle it.
			const KernelType *pKernel = dynamic_cast<const KernelType *>(&request);
			return (pKernel != NULL);
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "ModelBasedKernelInverter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			OStringStream os;
			os << "ModelBasedKernelInverter, InputDimension: " << VInputDimensions << ", OutputDimension: " << VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::InverseKernelBasePointer
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		invertKernel(const KernelBaseType &kernel,
		             const FieldRepresentationType *pFieldRepresentation,
		             const InverseFieldRepresentationType *pInverseFieldRepresentation) const
		{
			const KernelType *pKernel = dynamic_cast<const KernelType *>(&kernel);

			if (pKernel == NULL)
			{
				mapExceptionMacro(ServiceException, << "Error: cannot invert kernel. Reason: cannot cast to ModelBasedKernel: " << pKernel);
			}

			const typename KernelType::TransformType *pTransformModel = pKernel->getTransformModel();
			typename KernelType::TransformType::InverseTransformModelBasePointer spInverseTransformModel;

			InverseKernelBasePointer spResultKernel;

			if (pTransformModel->getInverse(spInverseTransformModel))
			{
				// analytic inversion worked, so we just have to create the kernel and return it
				typedef ModelBasedRegistrationKernel<VOutputDimensions, VInputDimensions> InverseKernelType;
				typename InverseKernelType::Pointer spInverseKernel = InverseKernelType::New();
				spInverseKernel->setTransformModel(spInverseTransformModel);
				spResultKernel = spInverseKernel;
			}
			else
			{
				// analytic inversion failed, do numeric inversion
				if (pInverseFieldRepresentation == NULL)
				{
					mapExceptionMacro(ServiceException, << "Error: cannot invert kernel. Reason: pInverseFieldRepresentation not present.");
				}

				typedef typename FieldKernels<VOutputDimensions, VInputDimensions>::LazyFieldBasedRegistrationKernel LazyFieldKernelType;
				typename LazyFieldKernelType::Pointer spInverseKernel = LazyFieldKernelType::New();

				typedef typename functors::FieldByModelInversionFunctor<VOutputDimensions, VInputDimensions> FunctorType;
				typename FunctorType::Pointer spFunctor = FunctorType::New(*pTransformModel, pInverseFieldRepresentation);
				spFunctor->setStopValue(_functorStopValue);
				spFunctor->setNumberOfIterations(_functorNrOfIterations);

				spInverseKernel->setFieldFunctor(*(spFunctor.GetPointer()));

				spResultKernel = spInverseKernel;
			}

			assert(spResultKernel.IsNotNull());
			return spResultKernel;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		ModelBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		ModelBasedKernelInverter(): _functorNrOfIterations(20), _functorStopValue(0.0)
		{};


	} // end namespace core
} // end namespace map

#endif
