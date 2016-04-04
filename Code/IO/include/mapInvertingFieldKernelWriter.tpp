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
// @version $Revision: 1287 $ (last changed revision)
// @date    $Date: 2016-04-01 18:02:24 +0200 (Fr, 01 Apr 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/IO/include/mapInvertingKernelWriter.tpp $
*/

#ifndef __MAP_INVERTING_FIELD_KERNEL_WRITER_TPP
#define __MAP_INVERTING_FIELD_KERNEL_WRITER_TPP

#include "mapInvertingKernelWriter.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
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
		InvertingKernelWriter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			// if the kernel "request" is a field-based kernel, then we can maybe handle it.

			const KernelType* pKernel = dynamic_cast<const KernelType*>
										(request._spKernel.GetPointer());

			bool canHandle = false;

			if (pKernel && !request._expandLazyKernels)
			{
				if (pKernel->getSourceKernel() == request._spComplementaryKernel.GetPointer())
				{
					canHandle = true;
				}
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		InvertingKernelWriter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		InvertingKernelWriter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			::map::core::OStringStream os;
			os << "InvertingKernelWriter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		InvertingKernelWriter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			::map::core::OStringStream os;
			os << "InvertingKernelWriter, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
			   VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		structuredData::Element::Pointer
		InvertingKernelWriter<VInputDimensions, VOutputDimensions>::
		storeKernel(const RequestType& request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error: cannot store kernel. Reason: cannot handle request.");
			}

			const KernelType* pKernel = dynamic_cast<const KernelType*>(request._spKernel.GetPointer());

			if (pKernel == NULL)
			{
				mapExceptionMacro(::map::core::ServiceException,
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
										   "InvertingKernel"));

			typename KernelType::RepresentationDescriptorConstPointer spInverseFieldRepresentation =
				pKernel->getLargestPossibleRepresentation();

			if (spInverseFieldRepresentation.IsNotNull())
			{
				structuredData::Element::Pointer spRepElement =
					spInverseFieldRepresentation->streamToStructuredData();
				spRepElement->setTag(tags::InverseFieldRepresentation);
				spKernelElement->addSubElement(spRepElement);
			}

			structuredData::Element::Pointer spUseNullVectorElement = structuredData::Element::New();
			spUseNullVectorElement->setTag(tags::UseNullVector);
			spUseNullVectorElement->setValue(::map::core::convert::toStr(pKernel->usesNullVector()));
			spKernelElement->addSubElement(spUseNullVectorElement);

			if (pKernel->usesNullVector())
			{
				typename KernelType::MappingVectorType nullVector = pKernel->getNullVector();
				structuredData::Element::Pointer spNullVectorElement = structuredData::streamITKFixedArrayToSD(
							nullVector);
				spNullVectorElement->setTag(tags::NullVector);

				spKernelElement->addSubElement(spNullVectorElement);
			}

			return spKernelElement;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InvertingKernelWriter<VInputDimensions, VOutputDimensions>::
		InvertingKernelWriter()
		{};


	} // end namespace io
} // end namespace map

#endif
