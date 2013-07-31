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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapNullRegistrationKernelInverter.tpp $
*/

#ifndef __MAP_NULL_REGISTRATION_KERNEL_INVERTER_TPP
#define __MAP_NULL_REGISTRATION_KERNEL_INVERTER_TPP

#include "mapNullRegistrationKernelInverter.h"
#include "mapServiceException.h"

namespace map
{
	namespace core
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType &request) const
		{
			// if the kernel "request" is a null kernel, then we can handle it.
			const KernelType *pKernel = dynamic_cast<const KernelType *>(&request);
			return (pKernel != NULL);
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "NullRegistrationKernelInverter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			OStringStream os;
			os << "NullRegistrationKernelInverter, InputDimension: " << VInputDimensions << ", OutputDimension: " << VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>::InverseKernelBasePointer
		NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>::
		invertKernel(const KernelBaseType &kernel,
		             const FieldRepresentationType *pFieldRepresentation,
		             const InverseFieldRepresentationType *pInverseFieldRepresentation) const
		{
			const KernelType *pKernel = dynamic_cast<const KernelType *>(&kernel);

			if (pKernel == NULL)
			{
				mapExceptionMacro(ServiceException, << "Error: cannot invert kernel. Reason: cannot cast to NullRegistrationKernel: " << pKernel);
			}

			//inversion of a null kernel is always a null kernel
			InverseKernelBasePointer spResultKernel = KernelType::New().GetPointer();
			assert(spResultKernel.IsNotNull());
			return spResultKernel;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>::
		NullRegistrationKernelInverter()
		{};


	} // end namespace core
} // end namespace map

#endif
