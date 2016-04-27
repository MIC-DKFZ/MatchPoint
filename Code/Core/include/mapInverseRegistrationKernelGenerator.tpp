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


#ifndef __MAP_INVERSE_REGISTRATION_KERNEL_GENERATOR_TPP
#define __MAP_INVERSE_REGISTRATION_KERNEL_GENERATOR_TPP

#include "mapInverseRegistrationKernelGenerator.h"
#include "mapMissingProviderException.h"

namespace map
{
	namespace core
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::InverseKernelBasePointer
		InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::
		generateInverse(const KernelBaseType& kernel,
		                const InverseFieldRepresentationType* pInverseFieldRepresentation) const
		{
			return generateInverse(kernel, kernel.getLargestPossibleRepresentation(),
			                       pInverseFieldRepresentation);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::InverseKernelBasePointer
		InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::
		generateInverse(const KernelBaseType& kernel, const FieldRepresentationType* pFieldRepresentation,
		                const InverseFieldRepresentationType* pInverseFieldRepresentation) const
		{
			InverterBaseType* pInverter = InverterStackType::getProvider(kernel);

			if (!pInverter)
			{
				mapExceptionMacro(MissingProviderException,
				                  << "No responsible inverter available for given kernel. Kernel:" << kernel);
			}

			InverseKernelBasePointer spInverseKernel = pInverter->invertKernel(kernel, pFieldRepresentation,
			        pInverseFieldRepresentation, _useNullPoint, _nullPoint);

			assert(spInverseKernel.IsNotNull());

			return spInverseKernel;
		};


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::
		InverseRegistrationKernelGenerator() : _useNullPoint(false)
		{
			_nullPoint.Fill(itk::NumericTraits<::map::core::continuous::ScalarType>::NonpositiveMin());
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::
		~InverseRegistrationKernelGenerator()
		{
		};

	} // end namespace core
} // end namespace map

#endif
