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


#ifndef __MAP_NULL_REGISTRATION_KERNEL_COMBINATOR_TPP
#define __MAP_NULL_REGISTRATION_KERNEL_COMBINATOR_TPP

#include "mapNullRegistrationKernelCombinator.h"
#include "mapServiceException.h"

namespace map
{
	namespace core
	{

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		typename NullRegistrationKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::CombinedKernelBasePointer
		NullRegistrationKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		combineKernels(const RequestType& request,
					   const InputFieldRepresentationType* pInputFieldRepresentation,
					   bool usePadding,
					   const PaddingVectorType& paddingVector) const
		{
			const Kernel1Type* pKernel1 = dynamic_cast<const Kernel1Type*>(request._spKernel1.GetPointer());
			const Kernel2Type* pKernel2 = dynamic_cast<const Kernel2Type*>(request._spKernel2.GetPointer());

			if ((pKernel1 == NULL) && (pKernel2 == NULL))
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot combine kernels. Reason: neither first nor second kernel is a NullRegeistrationKernel: Kernel 1: "
								  << pKernel1 << "; Kernel 2: " << pKernel2);
			}

			//As soon as there is a NullRegistrationKernel involved in the combination the result is always a NullRegistrationKernel.
			CombinedKernelBasePointer spResult = CombinedKernelType::New().GetPointer();
			return spResult;
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		bool
		NullRegistrationKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		canHandleRequest(const RequestType& request) const
		{
			// get the two kernels from the request (which is a RegistrationCombinationRequest object)
			// and check if at least on of them is a NullRegistrationKernel
			const Kernel1Type* pKernel1 = dynamic_cast<const Kernel1Type*>(request._spKernel1.GetPointer());
			const Kernel2Type* pKernel2 = dynamic_cast<const Kernel2Type*>(request._spKernel2.GetPointer());

			return ((pKernel1 != NULL) || (pKernel2 != NULL));
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		String
		NullRegistrationKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		String
		NullRegistrationKernelCombinator<VInputDimensions, VInterimDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "NullRegistrationKernelCombinator<" << VInputDimensions << "," << VInterimDimensions << "," <<
			   VOutputDimensions << ">";
			return os.str();
		}

		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		String
		NullRegistrationKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >::
		getDescription() const
		{
			OStringStream os;
			os << "NullRegistrationKernelCombinator, VInputDimensions: " << VInputDimensions <<
			   ", VInterimDimensions: " << VInterimDimensions << ", VOutputDimensions: " << VOutputDimensions <<
			   ".";
			return os.str();
		}


	} // end namespace core
} // end namespace map

#endif
