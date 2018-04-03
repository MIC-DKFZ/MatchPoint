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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapFieldKernelLoader.tpp $
*/

#ifndef __MAP_EXPANDING_FIELD_KERNEL_LOADER_TPP
#define __MAP_EXPANDING_FIELD_KERNEL_LOADER_TPP

#include "mapFieldKernelLoader.h"
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
            FieldKernelLoader<VInputDimensions, VOutputDimensions>::
            canHandleRequest(const RequestType& request) const
        {
            structuredData::Element::ConstSubElementIteratorType typePos = structuredData::findNextSubElement(
                request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(),
                tags::KernelType);

            bool canHandle = false;

            if (typePos != request._spKernelDescriptor->getSubElementEnd())
            {
                canHandle = ((*typePos)->getValue() == "ExpandedFieldKernel")
                    && Superclass::canHandleRequest(request);
            }

            return canHandle;
        }


        template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
        ::map::core::String
            FieldKernelLoader<VInputDimensions, VOutputDimensions>::
            getProviderName() const
        {
            return Self::getStaticProviderName();
        }

        template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
        ::map::core::String
            FieldKernelLoader<VInputDimensions, VOutputDimensions>::
            getStaticProviderName()
        {
            ::map::core::OStringStream os;
            os << "FieldKernelLoader<" << VInputDimensions << "," << VOutputDimensions << ">";
            return os.str();
        }


        template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
        ::map::core::String
            FieldKernelLoader<VInputDimensions, VOutputDimensions>::
            getDescription() const
        {
            ::map::core::OStringStream os;
            os << "FieldKernelLoader, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
                VOutputDimensions << ".";
            return os.str();
        }


        template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
        typename FieldKernelLoader<VInputDimensions, VOutputDimensions>::GenericKernelPointer
            FieldKernelLoader<VInputDimensions, VOutputDimensions>::
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
            typename KernelBaseType::OutputPointType nullPoint;
            bool usesNullPoint = this->hasNullPoint(request, nullPoint);

            typedef typename
                ::map::core::PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions>	KernelType;
            typename KernelType::Pointer spCachedKernel = KernelType::New();

            typedef core::functors::FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions> FunctorsType;
            typename FunctorsType::Pointer spFunctor = FunctorsType::New(filePath);
            spFunctor->setNullPointUsage(usesNullPoint);
            spFunctor->setNullPoint(nullPoint);

            typename FunctorsType::TransformType::Pointer spFieldTransform = spFunctor->generateTransform();

            spCachedKernel->setTransformModel(spFieldTransform.GetPointer());
            spKernel = spCachedKernel;

            GenericKernelPointer spResult = spKernel.GetPointer();
            return spResult;
        }

        template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
        FieldKernelLoader<VInputDimensions, VOutputDimensions>::
            FieldKernelLoader()
        {};


    } // end namespace io
} // end namespace map

#endif
