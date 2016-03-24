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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapFieldKernelLoaderBase.tpp $
*/

#ifndef __MAP_FIELD_KERNEL_LOADER_BASE_TPP
#define __MAP_FIELD_KERNEL_LOADER_BASE_TPP

#include "mapFieldKernelLoaderBase.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapRegistrationManipulator.h"
#include "mapConvert.h"
#include "mapFieldByFileLoadFunctor.h"
#include "mapSDTags.h"
#include "mapFileDispatch.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			structuredData::Element::ConstSubElementIteratorType typePos = structuredData::findNextSubElement(
						request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(),
						tags::KernelType);

			if (!request._spKernelDescriptor->attributeExists(tags::InputDimensions))
			{
				return false;
			}

			if (!request._spKernelDescriptor->attributeExists(tags::OutputDimensions))
			{
				return false;
			}

			unsigned int iDim = core::convert::toUInt(request._spKernelDescriptor->getAttribute(
									tags::InputDimensions));
			unsigned int oDim = core::convert::toUInt(request._spKernelDescriptor->getAttribute(
									tags::OutputDimensions));

			bool canHandle =  (iDim == VInputDimensions) && (oDim == VOutputDimensions);

			return canHandle;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>::
		getFilePath(const RequestType& request) const
		{
			//get file path
			::map::core::String filePath = "";
			structuredData::Element::ConstSubElementIteratorType pathPos = structuredData::findNextSubElement(
						request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(),
						tags::FieldPath);

			if (pathPos != request._spKernelDescriptor->getSubElementEnd())
			{
				filePath = (*pathPos)->getValue();
			}
			else
			{
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error. Cannot load kernel. Description as no file path element.")
			}

			//check if kernel descriptor is loaded from file and get its path (needed if file path is relative
			if (request._spKernelDescriptor->attributeExists(map::tags::SDInternalSourceReader)
				&& request._spKernelDescriptor->attributeExists(map::tags::SDInternalSourceURI))
			{
				if ((request._spKernelDescriptor->getAttribute(map::tags::SDInternalSourceReader) ==
					 map::tags::SDInternalSourceReader_file))
				{
					::map::core::String basePath = request._spKernelDescriptor->getAttribute(map::tags::SDInternalSourceURI);
					basePath = map::core::FileDispatch::getPath(basePath);

					filePath = itksys::SystemTools::CollapseFullPath(filePath.c_str(), basePath.c_str());
				}
			}

			return filePath;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>::
		hasNullVector(const RequestType& request, typename KernelBaseType::MappingVectorType& nullVector) const
		{
			//determin null vector (support)
			bool usesNullVector = false;
			structuredData::Element::ConstSubElementIteratorType usesNullPos =
				structuredData::findNextSubElement(request._spKernelDescriptor->getSubElementBegin(),
												   request._spKernelDescriptor->getSubElementEnd(), tags::UseNullVector);

			if (usesNullPos != request._spKernelDescriptor->getSubElementEnd())
			{
				usesNullVector = core::convert::toBool((*usesNullPos)->getValue());
			}
			else
			{
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error. Cannot load kernel. Field kernel description as no null vector usage information.")
			}

			typename KernelBaseType::MappingVectorType newNullVector;
			newNullVector.Fill(0);

			structuredData::Element::ConstSubElementIteratorType nullVecPos =
				structuredData::findNextSubElement(request._spKernelDescriptor->getSubElementBegin(),
												   request._spKernelDescriptor->getSubElementEnd(), tags::NullVector);

			if (nullVecPos != request._spKernelDescriptor->getSubElementEnd())
			{
				try
				{
					newNullVector = structuredData::streamSDToITKFixedArray<typename KernelBaseType::MappingVectorType>
								 (*nullVecPos);
				}
				catch (::map::core::ExceptionObject& ex)
				{
					mapExceptionMacro(::map::core::ServiceException, << ex.GetDescription());
				}
			}

			nullVector = newNullVector;
			return usesNullVector;
		}		
		
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>::
		addAsInverseKernel(GenericKernelType* pKernel,
						   core::RegistrationBase::Pointer& spRegistration) const
		{
			typedef core::RegistrationKernelBase<VOutputDimensions, VInputDimensions> KernelType;
			typedef core::Registration<VInputDimensions, VOutputDimensions> RegistrationType;

			if (spRegistration.IsNull())
			{
				spRegistration = RegistrationType::New();
			}

			if (!pKernel)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add kernel. Kernel pointer is null.");
			}

			RegistrationType* pCastedReg = dynamic_cast<RegistrationType*>(spRegistration.GetPointer());
			KernelType* pCastedKernel = dynamic_cast<KernelType*>(pKernel);

			if (!pCastedReg)
			{
				mapDefaultExceptionMacro( <<
										  "Error. Cannot add kernel. Registration has not the correct dimension.");
			}

			if (!pCastedKernel)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add kernel. Kernel has not the correct dimension.");
			}

			::map::core::RegistrationManipulator<RegistrationType> man(pCastedReg);
			man.setInverseMapping(pCastedKernel);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>::
		addAsDirectKernel(GenericKernelType* pKernel,
						  core::RegistrationBase::Pointer& spRegistration) const
		{
			typedef core::RegistrationKernelBase<VInputDimensions, VOutputDimensions> KernelType;
			typedef core::Registration<VInputDimensions, VOutputDimensions> RegistrationType;

			if (spRegistration.IsNull())
			{
				spRegistration = RegistrationType::New();
			}

			if (!pKernel)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add kernel. Kernel pointer is null.");
			}

			RegistrationType* pCastedReg = dynamic_cast<RegistrationType*>(spRegistration.GetPointer());
			KernelType* pCastedKernel = dynamic_cast<KernelType*>(pKernel);

			if (!pCastedReg)
			{
				mapDefaultExceptionMacro( <<
										  "Error. Cannot add kernel. Registration has not the correct dimension.");
			}

			if (!pCastedKernel)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add kernel. Kernel has not the correct dimension.");
			}

			::map::core::RegistrationManipulator<RegistrationType> man(pCastedReg);
			man.setDirectMapping(pCastedKernel);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>::
		FieldKernelLoaderBase()
		{};


	} // end namespace io
} // end namespace map

#endif
