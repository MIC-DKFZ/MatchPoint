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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapInvertingFieldKernelLoader.tpp $
*/

#ifndef __MAP_INVERTING_FIELD_KERNEL_LOADER_TPP
#define __MAP_INVERTING_FIELD_KERNEL_LOADER_TPP

#include "mapInvertingFieldKernelLoader.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapRegistrationManipulator.h"
#include "mapConvert.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapSDTags.h"
#include "mapFileDispatch.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
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
				canHandle = ((*typePos)->getValue() == "InvertingFieldKernel") && (iDim == VInputDimensions)
							&& (oDim == VOutputDimensions) && request._spComplementaryKernel.IsNotNull();
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			core::OStringStream os;
			os << "InvertingFieldKernelLoader<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			core::OStringStream os;
			os << "InvertingFieldKernelLoader, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
			   VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::GenericKernelPointer
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		loadKernel(const RequestType& request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot load kernel. Reason: cannot handle request.");
			}

      /*! Kernel base type of kernels that should be inverted to get the requested field kernel.*/
      typedef  core::RegistrationKernelBase<VOutputDimensions, VInputDimensions>	SourceKernelBaseType;
      const SourceKernelBaseType* sourceKernel = dynamic_cast<const SourceKernelBaseType*>(request._spComplementaryKernel.GetPointer());

			if (!sourceKernel)
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot load kernel. Reason: complementary/source kernel has not the correct dimensionality.");
			}

			structuredData::Element::ConstSubElementIteratorType repPos = structuredData::findNextSubElement(
						request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(),
						tags::InverseFieldRepresentation);
      
      typename KernelBaseType::RepresentationDescriptorPointer spInverseFieldRep;

      if (repPos != request._spKernelDescriptor->getSubElementEnd())
      {
        spInverseFieldRep = KernelBaseType::RepresentationDescriptorType::New();
        spInverseFieldRep->streamFromStructuredData(*repPos);
      }

      typedef core::InverseRegistrationKernelGenerator<VOutputDimensions, VInputDimensions> InversionGeneratorType;

      InversionGeneratorType::Pointer generator = InversionGeneratorType::New();
      core::RegistrationKernelBase<VInputDimensions, VOutputDimensions>::Pointer spResult = generator->generateInverse(*sourceKernel, spInverseFieldRep);
            
      if (!request._preferLazyLoading)
			{
        spResult->precomputeKernel();
			}

			return spResult;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
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
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
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
		InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		InvertingFieldKernelLoader()
		{};


	} // end namespace io
} // end namespace map

#endif
