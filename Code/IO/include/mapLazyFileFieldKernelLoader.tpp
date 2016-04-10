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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapLazyFileFieldKernelLoader.tpp $
*/

#ifndef __MAP_LAZY_FILE_FIELD_KERNEL_LOADER_TPP
#define __MAP_LAZY_FILE_FIELD_KERNEL_LOADER_TPP

#include "mapLazyFileFieldKernelLoader.h"
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
		LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			structuredData::Element::ConstSubElementIteratorType typePos = structuredData::findNextSubElement(
						request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(),
						tags::KernelType);

			bool canHandle = false;

			if (typePos != request._spKernelDescriptor->getSubElementEnd())
			{
				canHandle = ((*typePos)->getValue() == "ExpandedFieldKernel") && request._preferLazyLoading
							&& Superclass::canHandleRequest(request);
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			::map::core::OStringStream os;
			os << "LazyFileFieldKernelLoader<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			::map::core::OStringStream os;
			os << "LazyFileFieldKernelLoader, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
			   VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>::GenericKernelPointer
		LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		loadKernel(const RequestType& request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error: cannot load kernel. Reason: cannot handle request.");
			}

			typename KernelBaseType::Pointer spKernel;

			//get file path
			::map::core::String filePath = Superclass::getFilePath(request);
			
			//determin null vector (support)
			typename KernelBaseType::MappingVectorType nullVector;
            bool usesNullVector = this->hasNullVector(request, nullVector);

			typedef typename
			::map::core::LazyRegistrationKernel<VInputDimensions, VOutputDimensions> KernelType;
			typename KernelType::Pointer spLazyKernel = KernelType::New();

			typedef core::functors::FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions> FunctorsType;

			typename KernelBaseType::RepresentationDescriptorType::Pointer spFieldDescriptor =
				::map::core::createFieldRepresentationOfMetaImageFile<VInputDimensions>(filePath);

			typename FunctorsType::Pointer spFunctor = FunctorsType::New(filePath, spFieldDescriptor);
            spFunctor->setNullVectorUsage(usesNullVector);
            spFunctor->setNullVector(nullVector);

			spLazyKernel->setTransformFunctor(spFunctor.GetPointer());

			spKernel = spLazyKernel;

			GenericKernelPointer spResult = spKernel.GetPointer();
			return spResult;
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>::
		LazyFileFieldKernelLoader()
		{};


	} // end namespace io
} // end namespace map

#endif
