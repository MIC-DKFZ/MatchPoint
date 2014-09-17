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

			typedef typename
			core::FieldKernels<VInputDimensions, VOutputDimensions>::PreCachedFieldBasedRegistrationKernel
			CachedKernelType;
			typedef typename
			core::FieldKernels<VInputDimensions, VOutputDimensions>::LazyFieldBasedRegistrationKernel
			LazyKernelType;

			const CachedKernelType* pCachedKernel = dynamic_cast<const CachedKernelType*>
													(request._spKernel.GetPointer());
			const LazyKernelType* pLazyKernel = dynamic_cast<const LazyKernelType*>
												(request._spKernel.GetPointer());

			bool canHandle = false;

			if (pCachedKernel)
			{
				canHandle = true;
			}
			else if (pLazyKernel && request._expandLazyKernels)
			{
				canHandle = true;
			};

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
								  << "Error: cannot store kernel. Reason: cannot cast to FieldBasedKernel: " <<
								  request._spKernel.GetPointer());
			}


			const typename KernelType::FieldType::ConstPointer spField = pKernel->getField();

			if (spField.IsNull())
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot store kernel. Reason: Kernel seems to have no valid field. Kernel: " << pKernel);
			}

			structuredData::Element::Pointer spKernelElement = structuredData::Element::New();

			spKernelElement->setTag(tags::Kernel);

			spKernelElement->setAttribute(tags::InputDimensions, core::convert::toStr(VInputDimensions));
			spKernelElement->setAttribute(tags::OutputDimensions, core::convert::toStr(VOutputDimensions));

			spKernelElement->addSubElement(structuredData::Element::createElement(tags::StreamProvider,
										   this->getProviderName()));
			spKernelElement->addSubElement(structuredData::Element::createElement(tags::KernelType,
										   "ExpandedFieldKernel"));

			//generate file name and save field to file
			if (request._path.empty())
			{
				core::Logbook::warning("No request path set for field storing. Will be stored to current directory.");
			}

			if (request._name.empty())
			{
				core::Logbook::warning("No request name specified. Field will be stored to unspecified file '_field.mhd'.");
			}

			core::String fieldPath =  request._name + "_field.mhd";
			core::String absoluteFieldPath = core::FileDispatch::createFullPath(request._path, fieldPath);

			typedef ::itk::ImageFileWriter< typename KernelType::FieldType  > FieldWriterType;
			typename FieldWriterType::Pointer  spFieldWriter  = FieldWriterType::New();

			spFieldWriter->SetFileName(absoluteFieldPath.c_str());
			spFieldWriter->SetInput(spField);
			spFieldWriter->Update();

			//add field file
			structuredData::Element::Pointer spFieldPathElement = structuredData::Element::New();
			spFieldPathElement->setTag(tags::FieldPath);

			spFieldPathElement->setValue(fieldPath);

			spKernelElement->addSubElement(spFieldPathElement);

			//add null vector
			structuredData::Element::Pointer spNullVectorElement = structuredData::Element::New();
			spNullVectorElement->setTag(tags::NullVector);
			structuredData::Element::Pointer spUseNullVectorElement = structuredData::Element::New();
			spUseNullVectorElement->setTag(tags::UseNullVector);
			spUseNullVectorElement->setValue(core::convert::toStr(pKernel->usesNullVector()));
			spKernelElement->addSubElement(spUseNullVectorElement);

			if (pKernel->usesNullVector())
			{
				typename KernelType::MappingVectorType nullVector = pKernel->getNullVector();

				for (unsigned int rowID = 0; rowID < KernelType::MappingVectorType::Dimension; ++rowID)
				{
					structuredData::Element::Pointer spValueElement = structuredData::Element::New();
					spValueElement->setTag(tags::Value);
					spValueElement->setValue(core::convert::toStr(nullVector[rowID]));
					spValueElement->setAttribute(tags::Row, core::convert::toStr(rowID));
					spNullVectorElement->addSubElement(spValueElement);

				}

				spKernelElement->addSubElement(spNullVectorElement);
			}

			return spKernelElement;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InvertingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
		InvertingFieldKernelWriter()
		{};


	} // end namespace io
} // end namespace map

#endif
