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

#ifndef __MAP_NULL_REGISTRATION_KERNEL_WRITER_TPP
#define __MAP_NULL_REGISTRATION_KERNEL_WRITER_TPP

#include "mapNullRegistrationKernelWriter.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		NullRegistrationKernelWriter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			// if the kernel "request" is a model-based kernel, then we can handle it.
			const KernelType* pKernel = dynamic_cast<const KernelType*>(request._spKernel.GetPointer());

			bool canHandle = false;

			if (pKernel)
			{
				canHandle = true;
			};

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		NullRegistrationKernelWriter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		NullRegistrationKernelWriter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			::map::core::OStringStream os;
			os << "NullRegistrationKernelWriter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		NullRegistrationKernelWriter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			::map::core::OStringStream os;
			os << "NullRegistrationKernelWriter, InputDimension: " << VInputDimensions << ", OutputDimension: "
			   << VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		structuredData::Element::Pointer
		NullRegistrationKernelWriter<VInputDimensions, VOutputDimensions>::
		storeKernel(const RequestType& request) const
		{
			const KernelType* pKernel = dynamic_cast<const KernelType*>(request._spKernel.GetPointer());

			if (pKernel == NULL)
			{
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error: cannot store kernel. Reason: cannot cast to NullRegistrationKernel: " << pKernel);
			}

			structuredData::Element::Pointer spKernelElement = structuredData::Element::New();

			spKernelElement->setTag(tags::Kernel);
			::map::core::OStringStream os;
			os << VInputDimensions;
			spKernelElement->setAttribute(tags::InputDimensions, os.str());
			::map::core::OStringStream os2;
			os2 << VOutputDimensions;
			spKernelElement->setAttribute(tags::OutputDimensions, os2.str());

			spKernelElement->addSubElement(structuredData::Element::createElement(tags::StreamProvider,
										   this->getProviderName()));
			spKernelElement->addSubElement(structuredData::Element::createElement(tags::KernelType,
										   "NullRegistrationKernel"));
			return spKernelElement;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		NullRegistrationKernelWriter<VInputDimensions, VOutputDimensions>::
		NullRegistrationKernelWriter()
		{};


	} // end namespace io
} // end namespace map

#endif
