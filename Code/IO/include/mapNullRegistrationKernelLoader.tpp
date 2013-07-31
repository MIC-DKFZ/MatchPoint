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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/include/mapNullRegistrationKernelLoader.tpp $
*/

#ifndef __MAP_NULL_REGISTRATION_KERNEL_LOADER_TPP
#define __MAP_NULL_REGISTRATION_KERNEL_LOADER_TPP

#include "mapNullRegistrationKernelLoader.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapRegistrationManipulator.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType &request) const
		{
			structuredData::Element::ConstSubElementIteratorType  typePos = structuredData::findNextSubElement(request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(), tags::KernelType);

			if (!request._spKernelDescriptor->attributeExists(tags::InputDimensions))
			{
				return false;
			}

			if (!request._spKernelDescriptor->attributeExists(tags::OutputDimensions))
			{
				return false;
			}

			unsigned int iDim = core::convert::toUInt(request._spKernelDescriptor->getAttribute(tags::InputDimensions));
			unsigned int oDim = core::convert::toUInt(request._spKernelDescriptor->getAttribute(tags::OutputDimensions));

			bool canHandle = false;

			if (typePos != request._spKernelDescriptor->getSubElementEnd())
			{
				canHandle = ((*typePos)->getValue() == "NullRegistrationKernel") && (iDim == VInputDimensions) && (oDim == VOutputDimensions);
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			core::OStringStream os;
			os << "NullRegistrationKernelLoader<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			core::OStringStream os;
			os << "NullRegistrationKernelLoader, InputDimension: " << VInputDimensions << ", OutputDimension: " << VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::GenericKernelPointer
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		loadKernel(const RequestType &request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(core::ServiceException, << "Error: cannot load kernel. Reason: cannot handle request.");
			}

			GenericKernelPointer spResult = core::NullRegistrationKernel<VInputDimensions, VOutputDimensions>::New().GetPointer();
			return spResult;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		addAsInverseKernel(GenericKernelType *pKernel,  core::RegistrationBase::Pointer &spRegistration) const
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

			RegistrationType *pCastedReg = dynamic_cast<RegistrationType *>(spRegistration.GetPointer());
			KernelType *pCastedKernel = dynamic_cast<KernelType *>(pKernel);

			if (!pCastedReg)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add kernel. Registration has not the correct dimension.");
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
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		addAsDirectKernel(GenericKernelType *pKernel,  core::RegistrationBase::Pointer &spRegistration) const
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

			RegistrationType *pCastedReg = dynamic_cast<RegistrationType *>(spRegistration.GetPointer());
			KernelType *pCastedKernel = dynamic_cast<KernelType *>(pKernel);

			if (!pCastedReg)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add kernel. Registration has not the correct dimension.");
			}

			if (!pCastedKernel)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add kernel. Kernel has not the correct dimension.");
			}

			core::RegistrationManipulator<RegistrationType> man(pCastedReg);
			man.setDirectMapping(pCastedKernel);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>::
		NullRegistrationKernelLoader()
		{};


	} // end namespace io
} // end namespace map

#endif
