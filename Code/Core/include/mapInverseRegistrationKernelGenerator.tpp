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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapInverseRegistrationKernelGenerator.tpp $
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
		generateInverse(const KernelBaseType &kernel, const InverseFieldRepresentationType *pInverseFieldRepresentation) const
		{
			return generateInverse(kernel, kernel.getLargestPossibleRepresentation(), pInverseFieldRepresentation);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::InverseKernelBasePointer
		InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::
		generateInverse(const KernelBaseType &kernel, const FieldRepresentationType *pFieldRepresentation,
		                const InverseFieldRepresentationType *pInverseFieldRepresentation) const
		{
			InverterBaseType *pInverter = InverterStackType::getProvider(kernel);

			if (!pInverter)
			{
				mapExceptionMacro(MissingProviderException, << "No responsible inverter available for given kernel. Kernel:" << kernel);
			}

			InverseKernelBasePointer spInverseKernel = pInverter->invertKernel(kernel, pFieldRepresentation, pInverseFieldRepresentation);

			assert(spInverseKernel.IsNotNull());

			return spInverseKernel;
		};


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::
		InverseRegistrationKernelGenerator()
		{
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>::
		~InverseRegistrationKernelGenerator()
		{
		};

	} // end namespace core
} // end namespace map

#endif
