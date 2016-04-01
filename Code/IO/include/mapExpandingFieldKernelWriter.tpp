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

#ifndef __MAP_EXPANDING_FIELD_KERNEL_WRITER_TPP
#define __MAP_EXPANDING_FIELD_KERNEL_WRITER_TPP

#include "mapExpandingFieldKernelWriter.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapLazyRegistrationKernel.h"
#include "mapPreCachedRegistrationKernel.h"
#include "mapConvert.h"
#include "mapLogbook.h"
#include "mapFileDispatch.h"
#include "mapFieldByModelFunctor.h"

#include "itkImageFileWriter.h"

namespace map
{
  namespace io
  {

    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    bool
    ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
    canHandleRequest(const RequestType& request) const
    {
      // if the kernel "request" is a field-based kernel, then we can maybe handle it.

      typedef typename
      core::PreCachedRegistrationKernel<VInputDimensions, VOutputDimensions> CachedKernelType;
      typedef typename
      core::LazyRegistrationKernel<VInputDimensions, VOutputDimensions> LazyKernelType;

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
    ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
    getProviderName() const
    {
      return Self::getStaticProviderName();
    }

    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    core::String
    ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
    getStaticProviderName()
    {
      core::OStringStream os;
      os << "ExpandingFieldKernelWriter<" << VInputDimensions << "," << VOutputDimensions << ">";
      return os.str();
    }


    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    core::String
    ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
    getDescription() const
    {
      core::OStringStream os;
      os << "ExpandingFieldKernelWriter, InputDimension: " << VInputDimensions << ", OutputDimension: " <<
         VOutputDimensions << ".";
      return os.str();
    }


    template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
    structuredData::Element::Pointer
    ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
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
                          << "Error: cannot store kernel. Reason: cannot cast to FieldBasedKernel: " <<
                          request._spKernel.GetPointer());
      }

      const typename KernelType::TransformType::ConstPointer spTransform = pKernel->getTransformModel();

      if (spTransform.IsNull())
      {
        mapExceptionMacro(::map::core::ServiceException,
                          << "Error: cannot store kernel. Reason: Kernel seems to have no valid transform model. Kernel: " << pKernel);
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
        core::Logbook::warning("No request name specified. Field will be stored to unspecified file '_field.nrrd'.");
      }

      typedef typename ::map::core::RegistrationTopology < VInputDimensions, VOutputDimensions >::DirectFieldType FieldType;

      typename FieldType::ConstPointer spField;

      //check if the transformation alread containes the vectorfield
      typedef typename ::itk::DisplacementFieldTransform<::map::core::continuous::ScalarType, VOutputDimensions> FieldTransformType;
      const FieldTransformType* castedFieldTransform= dynamic_cast<const FieldTransformType*>(spTransform.GetPointer());
      if (castedFieldTransform)
      { //try to directly use the field
          spField = dynamic_cast<const FieldType*>(castedFieldTransform->GetDisplacementField());
      }
      if (spField.IsNull())
      {
          spField = ::map::core::generateFieldFromTransform<VInputDimensions, VOutputDimensions>(spTransform, pKernel->getLargestPossibleRepresentation());
      }

      core::String fieldPath =  request._name + "_field.nrrd";
      core::String absoluteFieldPath = core::FileDispatch::createFullPath(request._path, fieldPath);

      typedef ::itk::ImageFileWriter< typename FieldType  > FieldWriterType;
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
    ExpandingFieldKernelWriter<VInputDimensions, VOutputDimensions>::
    ExpandingFieldKernelWriter()
    {};


  } // end namespace io
} // end namespace map

#endif
