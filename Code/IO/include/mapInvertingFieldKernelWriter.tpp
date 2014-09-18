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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapInvertingFieldKernelWriter.tpp $
*/

#ifndef __MAP_INVERTING_FIELD_KERNEL_WRITER_TPP
#define __MAP_INVERTING_FIELD_KERNEL_WRITER_TPP

#include "mapInvertingFieldKernelWriter.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapConvert.h"
#include "mapLogbook.h"
#include "mapFileDispatch.h"

#include "itkImageFileWriter.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		InvertingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			// if the kernel "request" is a field-based kernel, then we can maybe handle it.

			const KernelType* pKernel = dynamic_cast<const KernelType*>
													(request._spKernel.GetPointer());

			bool canHandle = false;

			if (pKernel)
			{
        if (pKernel->getSourceKernel() == request._spComplimentaryKernel.GetPointer())
        {
				  canHandle = true;
        }
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		InvertingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		InvertingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			core::OStringStream os;
			os << "InvertingFieldKernelWriter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		InvertingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			core::OStringStream os;
			os << "InvertingFieldKernelWriter, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
			   VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		structuredData::Element::Pointer
		InvertingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
		storeKernel(const RequestType& request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot store kernel. Reason: cannot handle request.");
			}

			const KernelType* pKernel = dynamic_cast<const KernelType*>(request._spKernel.GetPointer());

			if (pKernel == NULL)
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot store kernel. Reason: cannot cast to InvertingFieldBasedRegistrationKernel: " <<
								  request._spKernel.GetPointer());
			}

			structuredData::Element::Pointer spKernelElement = structuredData::Element::New();

			spKernelElement->setTag(tags::Kernel);

			spKernelElement->setAttribute(tags::InputDimensions, core::convert::toStr(VInputDimensions));
			spKernelElement->setAttribute(tags::OutputDimensions, core::convert::toStr(VOutputDimensions));

			spKernelElement->addSubElement(structuredData::Element::createElement(tags::StreamProvider,
										   this->getProviderName()));
			spKernelElement->addSubElement(structuredData::Element::createElement(tags::KernelType,
										   "InvertingFieldKernel"));

      typename KernelType::RepresentationDescriptorConstPointer spInverseFieldRepresentation = spKernel->getLargestPossibleRepresentation()
      
			if(spInverseFieldRepresentation.IsNotNull()
      {
			  structuredData::Element::Pointer spRepElement = spInverseFieldRepresentation->streamToSD();
			  spRepElement->setTag(tags::InverseFieldRepresentation);
      }

			spKernelElement->addSubElement(spFieldPathElement);

			return spKernelElement;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InvertingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
		InvertingFieldKernelWriter()
		{};


	} // end namespace io
} // end namespace map

#endif
