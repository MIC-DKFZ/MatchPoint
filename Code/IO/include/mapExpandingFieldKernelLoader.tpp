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

#ifndef __MAP_EXPANDING_FIELD_KERNEL_LOADER_TPP
#define __MAP_EXPANDING_FIELD_KERNEL_LOADER_TPP

#include "mapExpandingFieldKernelLoader.h"
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
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
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

			bool canHandle = false;

			if (typePos != request._spKernelDescriptor->getSubElementEnd())
			{
				canHandle = ((*typePos)->getValue() == "ExpandedFieldKernel") && (iDim == VInputDimensions)
							&& (oDim == VOutputDimensions);
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			core::OStringStream os;
			os << "ExpandingFieldKernelLoader<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			core::OStringStream os;
			os << "ExpandingFieldKernelLoader, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
			   VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::GenericKernelPointer
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		loadKernel(const RequestType& request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot load kernel. Reason: cannot handle request.");
			}

			typename KernelBaseType::Pointer spKernel;

			//get file path
			core::String filePath = "";
			structuredData::Element::ConstSubElementIteratorType pathPos = structuredData::findNextSubElement(
						request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(),
						tags::FieldPath);

			if (pathPos != request._spKernelDescriptor->getSubElementEnd())
			{
				filePath = (*pathPos)->getValue();
			}
			else
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error. Cannot load kernel. Description as no file path element.")
			}

			//check if kernel descriptor is loaded from file and get its path (needed if file path is relative
			if (request._spKernelDescriptor->attributeExists(map::tags::SDInternalSourceReader)
				&& request._spKernelDescriptor->attributeExists(map::tags::SDInternalSourceURI))
			{
				if ((request._spKernelDescriptor->getAttribute(map::tags::SDInternalSourceReader) ==
					 map::tags::SDInternalSourceReader_file))
				{
					core::String basePath = request._spKernelDescriptor->getAttribute(map::tags::SDInternalSourceURI);
					basePath = map::core::FileDispatch::getPath(basePath);

					filePath = itksys::SystemTools::CollapseFullPath(filePath.c_str(), basePath.c_str());
				}
			}

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
				mapExceptionMacro(core::ServiceException,
								  << "Error. Cannot load kernel. Field kernel description as no null vector usage information.")
			}

			typename KernelBaseType::MappingVectorType nullVector;
			nullVector.Fill(0);

			structuredData::Element::ConstSubElementIteratorType nullVecPos =
				structuredData::findNextSubElement(request._spKernelDescriptor->getSubElementBegin(),
												   request._spKernelDescriptor->getSubElementEnd(), tags::NullVector);

			if (nullVecPos != request._spKernelDescriptor->getSubElementEnd())
			{
				try
				{
					nullVector = structuredData::streamSDToITKFixedArray<typename KernelBaseType::MappingVectorType>
								 (*nullVecPos);
				}
				catch (core::ExceptionObject& ex)
				{
					mapExceptionMacro(core::ServiceException, << ex.GetDescription());
				}
			}

			if (request._preferLazyLoading)
			{
				typedef typename
				core::FieldKernels<VInputDimensions, VOutputDimensions>::LazyFieldBasedRegistrationKernel
				KernelType;
				typename KernelType::Pointer spLazyKernel = KernelType::New();

				typedef core::functors::FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions> FunctorsType;

				typename KernelBaseType::RepresentationDescriptorType::Pointer spFieldDescriptor =
					core::createFieldRepresentationOfMetaImageFile<VInputDimensions>(filePath);

				typename FunctorsType::Pointer spFunctor = FunctorsType::New(filePath, spFieldDescriptor);

				spLazyKernel->setFieldFunctor(*(spFunctor.GetPointer()));
				spLazyKernel->setNullVectorUsage(usesNullVector);
				spLazyKernel->setNullVector(nullVector);

				spKernel = spLazyKernel;
			}
			else
			{
				typedef typename
				core::FieldKernels<VInputDimensions, VOutputDimensions>::PreCachedFieldBasedRegistrationKernel
				KernelType;
				typename KernelType::Pointer spCachedKernel = KernelType::New();

				typedef core::functors::FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions> FunctorsType;
				typename FunctorsType::Pointer spFunctor = FunctorsType::New(filePath);

				typename KernelType::FieldType::Pointer spField = spFunctor->generateField();

				spCachedKernel->setField(*(spField.GetPointer()));
				spCachedKernel->setNullVectorUsage(usesNullVector);
				spCachedKernel->setNullVector(nullVector);
				spKernel = spCachedKernel;
			}

			GenericKernelPointer spResult = spKernel.GetPointer();
			return spResult;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
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

			core::RegistrationManipulator<RegistrationType> man(pCastedReg);
			man.setInverseMapping(pCastedKernel);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
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

			core::RegistrationManipulator<RegistrationType> man(pCastedReg);
			man.setDirectMapping(pCastedKernel);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		ExpandingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		ExpandingFieldKernelLoader()
		{};


	} // end namespace io
} // end namespace map

#endif
