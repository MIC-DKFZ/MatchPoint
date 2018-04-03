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

#ifndef __MAP_INVERTING_FIELD_KERNEL_LOADER_TPP
#define __MAP_INVERTING_FIELD_KERNEL_LOADER_TPP

#include "mapInvertingKernelLoader.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapRegistrationManipulator.h"
#include "mapConvert.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapSDTags.h"
#include "mapFileDispatch.h"
#include "mapLazyRegistrationKernel.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		InvertingKernelLoader<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			structuredData::Element::ConstSubElementIteratorType typePos = structuredData::findNextSubElement(
						request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(),
						tags::KernelType);

			bool canHandle = false;

			if (typePos != request._spKernelDescriptor->getSubElementEnd())
			{
          //The check "InvertingFieldKernel" is for backwards compatibility in order to be able to load files
          //of MatchPoint versions <0.12 (Naming changed with Issue #1505)
          canHandle = ((*typePos)->getValue() == "InvertingKernel") || ((*typePos)->getValue() == "InvertingFieldKernel");
          
          canHandle = canHandle && Superclass::canHandleRequest(request) && request._spComplementaryKernel.IsNotNull();
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		InvertingKernelLoader<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		InvertingKernelLoader<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			::map::core::OStringStream os;
			os << "InvertingKernelLoader<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		InvertingKernelLoader<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			::map::core::OStringStream os;
			os << "InvertingKernelLoader, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
			   VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename InvertingKernelLoader<VInputDimensions, VOutputDimensions>::GenericKernelPointer
		InvertingKernelLoader<VInputDimensions, VOutputDimensions>::
		loadKernel(const RequestType& request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error: cannot load kernel. Reason: cannot handle request.");
			}

			/*! Kernel base type of kernels that should be inverted to get the requested field kernel.*/
			typedef  core::RegistrationKernelBase<VOutputDimensions, VInputDimensions>	SourceKernelBaseType;
			const SourceKernelBaseType* sourceKernel = dynamic_cast<const SourceKernelBaseType*>
					(request._spComplementaryKernel.GetPointer());

			if (!sourceKernel)
			{
				mapExceptionMacro(::map::core::ServiceException,
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

			//determin null vector (support)
      typename KernelBaseType::OutputPointType nullPoint;
            bool usesNullPoint = this->hasNullPoint(request, nullPoint);

			typedef core::InverseRegistrationKernelGenerator<VOutputDimensions, VInputDimensions>
			InversionGeneratorType;

			typename InversionGeneratorType::Pointer generator = InversionGeneratorType::New();
      generator->setNullPointUsage(usesNullPoint);
      generator->setNullPoint(nullPoint);
      
      typename core::RegistrationKernelBase<VInputDimensions, VOutputDimensions>::Pointer spResult =
				generator->generateInverse(*sourceKernel, spInverseFieldRep);

			if (!request._preferLazyLoading)
			{
				spResult->precomputeKernel();
			}

			return spResult.GetPointer();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		InvertingKernelLoader<VInputDimensions, VOutputDimensions>::
		InvertingKernelLoader()
		{};


	} // end namespace io
} // end namespace map

#endif
