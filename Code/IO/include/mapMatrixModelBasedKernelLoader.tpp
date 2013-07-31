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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/include/mapMatrixModelBasedKernelLoader.tpp $
*/

#ifndef __MAP_MATRIX_MODEL_BASED_KERNEL_LOADER_TPP
#define __MAP_MATRIX_MODEL_BASED_KERNEL_LOADER_TPP

#include "mapMatrixModelBasedKernelLoader.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapRegistrationManipulator.h"
#include "mapITKAffineTransform.h"
#include "mapConvert.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions>
		bool
		MatrixModelBasedKernelLoader<VInputDimensions>::
		canHandleRequest(const RequestType &request) const
		{
			structuredData::Element::ConstSubElementIteratorType typePos = structuredData::findNextSubElement(request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(), tags::KernelType);

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
				canHandle = ((*typePos)->getValue() == "MatrixModelKernel") && (iDim == VInputDimensions) && (oDim == VInputDimensions);
			}

			return canHandle;
		}


		template <unsigned int VInputDimensions>
		core::String
		MatrixModelBasedKernelLoader<VInputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions>
		core::String
		MatrixModelBasedKernelLoader<VInputDimensions>::
		getStaticProviderName()
		{
			core::OStringStream os;
			os << "MatrixModelBasedKernelLoader<" << VInputDimensions << "," << VInputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions>
		core::String
		MatrixModelBasedKernelLoader<VInputDimensions>::
		getDescription() const
		{
			core::OStringStream os;
			os << "MatrixModelBasedKernelLoader, InputDimension: " << VInputDimensions << ", OutputDimension: " << VInputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions>
		typename MatrixModelBasedKernelLoader<VInputDimensions>::GenericKernelPointer
		MatrixModelBasedKernelLoader<VInputDimensions>::
		loadKernel(const RequestType &request) const
		{
			if (!canHandleRequest(request))
			{
				mapExceptionMacro(core::ServiceException, << "Error: cannot load kernel. Reason: cannot handle request.");
			}

			//establish matrix;
			structuredData::Element::ConstSubElementIteratorType matrixPos = structuredData::findNextSubElement(request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(), tags::Matrix);

			if (matrixPos == request._spKernelDescriptor->getSubElementEnd())
			{
				mapExceptionMacro(core::ServiceException, << "Error: cannot load kernel. Reason: no matrix found.");
			}

			if ((*matrixPos)->getSubElementsCount() != VInputDimensions * VInputDimensions)
			{
				mapExceptionMacro(core::ServiceException, << "Error: cannot load kernel. Reason: matrix has wrong number of elements. Expexted: " << VInputDimensions * VInputDimensions << "; found: " << (*matrixPos)->getSubElementsCount());
			}

			typename KernelType::TransformType::MatrixType matrix;

			for (structuredData::Element::ConstSubElementIteratorType pos = (*matrixPos)->getSubElementBegin(); pos != (*matrixPos)->getSubElementEnd(); ++pos)
			{
				unsigned int rowID = core::convert::toUInt((*pos)->getAttribute(tags::Row));
				unsigned int colID = core::convert::toUInt((*pos)->getAttribute(tags::Column));

				matrix(rowID, colID) = core::convert::toDouble((*pos)->getValue());
			}

			//establish offset;

			structuredData::Element::ConstSubElementIteratorType offsetPos = structuredData::findNextSubElement(request._spKernelDescriptor->getSubElementBegin(), request._spKernelDescriptor->getSubElementEnd(), tags::Offset);

			if (offsetPos == request._spKernelDescriptor->getSubElementEnd())
			{
				mapExceptionMacro(core::ServiceException, << "Error: cannot load kernel. Reason: no offset found.");
			}

			if ((*offsetPos)->getSubElementsCount() != VInputDimensions)
			{
				mapExceptionMacro(core::ServiceException, << "Error: cannot load kernel. Reason: offset has wrong number of elements. Expexted: " << VInputDimensions << "; found: " << (*offsetPos)->getSubElementsCount());
			}

			typename KernelType::TransformType::OutputVectorType offset;

			for (structuredData::Element::ConstSubElementIteratorType pos = (*offsetPos)->getSubElementBegin(); pos != (*offsetPos)->getSubElementEnd(); ++pos)
			{
				unsigned int rowID = core::convert::toUInt((*pos)->getAttribute(tags::Row));

				offset[rowID] = core::convert::toDouble((*pos)->getValue());
			}

			typename KernelType::Pointer spKernel = KernelType::New();

			typedef ::itk::AffineTransform<core::continuous::ScalarType, VInputDimensions> TransformType;
			typedef algorithm::itk::ITKTransformModel<TransformType> ModelType;
			typename ModelType::Pointer spModel = ModelType::New();

			spModel->getConcreteTransform()->SetMatrix(matrix);
			spModel->getConcreteTransform()->SetOffset(offset);

			spKernel->setTransformModel(spModel);

			GenericKernelPointer spResult = spKernel.GetPointer();
			return spResult;
		}

		template <unsigned int VInputDimensions>
		void
		MatrixModelBasedKernelLoader<VInputDimensions>::
		addAsInverseKernel(GenericKernelType *pKernel,  core::RegistrationBase::Pointer &spRegistration) const
		{
			typedef core::RegistrationKernelBase<VInputDimensions, VInputDimensions> KernelType;
			typedef core::Registration<VInputDimensions, VInputDimensions> RegistrationType;

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

		template <unsigned int VInputDimensions>
		void
		MatrixModelBasedKernelLoader<VInputDimensions>::
		addAsDirectKernel(GenericKernelType *pKernel,  core::RegistrationBase::Pointer &spRegistration) const
		{
			typedef core::RegistrationKernelBase<VInputDimensions, VInputDimensions> KernelType;
			typedef core::Registration<VInputDimensions, VInputDimensions> RegistrationType;

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

		template <unsigned int VInputDimensions>
		MatrixModelBasedKernelLoader<VInputDimensions>::
		MatrixModelBasedKernelLoader()
		{};


	} // end namespace io
} // end namespace map

#endif
