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

#ifndef __MAP_LAZY_FIELD_FILE_KERNEL_WRITER_TPP
#define __MAP_LAZY_FIELD_FILE_KERNEL_WRITER_TPP

#include <algorithm>
#include <utility>

#include "itksys/SystemTools.hxx"

#include "mapLazyFieldFileKernelWriter.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapFieldByFileLoadFunctor.h"
#include "mapConvert.h"
#include "mapLogbook.h"
#include "mapFileDispatch.h"
#include "mapExpandingFieldKernelWriter.h"

namespace map
{
  namespace io
  {

    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    bool
    LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions>::
    canHandleRequest(const RequestType& request) const
    {
      const KernelType* pLazyKernel = dynamic_cast<const KernelType*>
                                          (request._spKernel.GetPointer());

      bool canHandle = false;

      if (pLazyKernel && !request._expandLazyKernels)
      {
        auto fileLoadFunctor = dynamic_cast<const ::map::core::functors::FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions> *>(pLazyKernel->getTransformFunctor());

        canHandle = fileLoadFunctor != nullptr;
      };

      return canHandle;
    }


    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    core::String
    LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions>::
    getProviderName() const
    {
      return Self::getStaticProviderName();
    }

    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    core::String
    LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions>::
    getStaticProviderName()
    {
      core::OStringStream os;
      os << "LazyFieldFileKernelWriter<" << VInputDimensions << "," << VOutputDimensions << ">";
      return os.str();
    }


    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    core::String
    LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions>::
    getDescription() const
    {
      core::OStringStream os;
      os << "LazyFieldFileKernelWriter, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
         VOutputDimensions << ".";
      return os.str();
    }


    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    structuredData::Element::Pointer
    LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions>::
    storeKernel(const RequestType& request) const
    {
      if (!canHandleRequest(request))
      {
        mapExceptionMacro(::map::core::ServiceException,
                          << "Error: cannot store kernel. Reason: cannot handle request.");
      }

      const KernelType* pKernel = dynamic_cast<const KernelType*>(request._spKernel.GetPointer());

      if (pKernel == nullptr)
      {
        mapExceptionMacro(::map::core::ServiceException,
                          << "Error: cannot store kernel. Reason: cannot cast to LazyRegistrationKernel: " <<
                          request._spKernel.GetPointer());
      }

      structuredData::Element::Pointer spKernelElement;

      if (pKernel->transformExists())
      { //pKernel is not lazy anymore. So we can just save the transform back to a file.
        RequestType expandingRequest = request;
        expandingRequest._expandLazyKernels = true;
        typedef io::ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions> ExpandingWriterType;
        ExpandingWriterType::Pointer writer = ExpandingWriterType::New();
        spKernelElement = writer->storeKernel(expandingRequest);
      }
      else
      { 
        auto fileLoadFunctor = dynamic_cast<const ::map::core::functors::FieldByFileLoadFunctor<VInputDimensions, VOutputDimensions> *>(pKernel->getTransformFunctor());

        if (fileLoadFunctor == nullptr)
        {
          mapExceptionMacro(::map::core::ServiceException,
            << "Error: cannot store kernel. Reason: Lazy kernel seems to have no FieldByFileLoadFunctor. Kernel: " << pKernel);
        }

        core::String sourcePath = fileLoadFunctor->getFieldFilePath();

        spKernelElement = structuredData::Element::New();

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
          core::Logbook::warning("No request name specified. Field will be stored to unspecified file '_field.nrrd'.");
        }

        core::String fieldPath = request._name + "_field.nrrd";
        core::String destinationPath = core::FileDispatch::createFullPath(request._path, fieldPath);

        //copy field file
        auto extension = core::FileDispatch::getExtension(sourcePath);
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        if (extension == ".nrrd" || extension == ".mda")
        { //these format only consist of one file -> we can just copy it.
          itksys::SystemTools::CopyAFile(sourcePath, destinationPath);
        }
        else
        {
          mapExceptionMacro(::map::core::ServiceException,
            << "Error: cannot store kernel. Reason: Lazy kernel currently only support savely files in NRRD or MDA fromat. See https://phabricator.mitk.org/T24623 for more details. Kernel: " << pKernel);
        }

        //add field file
        structuredData::Element::Pointer spFieldPathElement = structuredData::Element::New();
        spFieldPathElement->setTag(tags::FieldPath);
        spFieldPathElement->setValue(fieldPath);

        spKernelElement->addSubElement(spFieldPathElement);

        //add null point
        structuredData::Element::Pointer spUseNullPointElement = structuredData::Element::New();
        spUseNullPointElement->setTag(tags::UseNullPoint);
        spUseNullPointElement->setValue(::map::core::convert::toStr(fileLoadFunctor->getNullPointUsage()));
        spKernelElement->addSubElement(spUseNullPointElement);

        if (fileLoadFunctor->getNullPointUsage())
        {
          typename KernelType::OutputPointType nullPoint = fileLoadFunctor->getNullPoint();
          structuredData::Element::Pointer spNullPointElement = structuredData::streamITKFixedArrayToSD(
            nullPoint);
          spNullPointElement->setTag(tags::NullPoint);

          spKernelElement->addSubElement(spNullPointElement);
        }
      }

      return spKernelElement;
    }


    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions>::
    LazyFieldFileKernelWriter()
    {};


  } // end namespace io
} // end namespace map

#endif
