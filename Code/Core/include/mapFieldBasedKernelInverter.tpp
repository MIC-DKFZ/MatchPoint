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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldBasedKernelInverter.tpp $
*/

#ifndef __MAP_FIELD_BASED_KERNEL_INVERTER_TPP
#define __MAP_FIELD_BASED_KERNEL_INVERTER_TPP

#include "mapFieldBasedKernelInverter.h"
#include "mapServiceException.h"
#include "mapFieldByFieldInversionFunctor.h"
#include "mapFieldBasedRegistrationKernels.h"

namespace map
{
	namespace core
	{
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		unsigned long
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getFunctorNumberOfIterations() const
		{
			return _functorNrOfIterations;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		setFunctorNumberOfIterations(unsigned long nrOfIterations)
		{
			_functorNrOfIterations = nrOfIterations;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		double
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getFunctorStopValue() const
		{
			return _functorStopValue;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		setFunctorStopValue(double stopValue)
		{
			_functorStopValue = stopValue;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType &request) const
		{
			// if the kernel "request" is a field-based kernel, then we can handle it.
			const KernelType *pKernel = dynamic_cast<const KernelType *>(&request);
			return (pKernel != NULL);
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "FieldBasedKernelInverter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			OStringStream os;
			os << "FieldBasedKernelInverter, InputDimension: " << VInputDimensions << ", OutputDimension: " << VOutputDimensions << ".";
			return os.str();
		}



		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::InverseKernelBasePointer
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		invertKernel(const KernelBaseType &kernel,
		             const FieldRepresentationType *pFieldRepresentation,
		             const InverseFieldRepresentationType *pInverseFieldRepresentation) const
		{
			const KernelType *pKernel = dynamic_cast<const KernelType *>(&kernel);

			if (pKernel == NULL)
			{
				mapExceptionMacro(ServiceException, << "Error: cannot invert kernel. Reason: cannot cast to FieldBasedKernel: " << pKernel);
			}

			if (pInverseFieldRepresentation == NULL)
			{
				mapExceptionMacro(ServiceException, << "Error: cannot invert kernel. Reason: pInverseFieldRepresentation not present.");
			}

			typedef typename FieldKernels<VOutputDimensions, VInputDimensions>::LazyFieldBasedRegistrationKernel LazyFieldKernelType;
			typename LazyFieldKernelType::Pointer spInverseKernel = LazyFieldKernelType::New();

			typedef functors::FieldByFieldInversionFunctor<VOutputDimensions, VInputDimensions> FunctorType;
			typename FunctorType::Pointer spFunctor = FunctorType::New(*pKernel, pInverseFieldRepresentation);
			spFunctor->setStopValue(_functorStopValue);
			spFunctor->setNumberOfIterations(_functorNrOfIterations);

			spInverseKernel->setFieldFunctor(*(spFunctor.GetPointer()));

			assert(spInverseKernel.IsNotNull());

			InverseKernelBasePointer spResult = spInverseKernel.GetPointer();
			return spResult;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>::
		FieldBasedKernelInverter(): _functorNrOfIterations(20), _functorStopValue(0.0)
		{};


	} // end namespace core
} // end namespace map

#endif
