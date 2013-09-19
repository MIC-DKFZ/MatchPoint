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

#ifndef __MAP_MATRIX_MODEL_BASED_KERNEL_WRITER_TPP
#define __MAP_MATRIX_MODEL_BASED_KERNEL_WRITER_TPP

#include "mapMatrixModelBasedKernelWriter.h"
#include "mapServiceException.h"
#include "mapRegistrationFileTags.h"
#include "mapConvert.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		canHandleRequest(const RequestType& request) const
		{
			// if the kernel "request" is a model-based kernel, then we can handle it.
			const KernelType* pKernel = dynamic_cast<const KernelType*>(request._spKernel.GetPointer());

			bool canHandle = false;

			if (pKernel)
			{
				typename KernelType::TransformType::ConstPointer spModel = pKernel->getTransformModel();

				if (spModel.IsNotNull())
				{
					typename KernelType::TransformType::MatrixType matrix;
					typename KernelType::TransformType::OutputVectorType offset;

					if (spModel->getAffineMatrixDecomposition(matrix, offset))
					{
						canHandle = true;
					}
				}
			};

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			core::OStringStream os;
			os << "MatrixModelBasedKernelWriter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		core::String
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			core::OStringStream os;
			os << "MatrixModelBasedKernelWriter, InputDimension: " << VInputDimensions << ", OutputDimension: "
			   << VOutputDimensions << ".";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		structuredData::Element::Pointer
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		storeKernel(const RequestType& request) const
		{
			const KernelType* pKernel = dynamic_cast<const KernelType*>(request._spKernel.GetPointer());

			if (pKernel == NULL)
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot store kernel. Reason: cannot cast to ModelBasedKernel: " << pKernel);
			}

			typename KernelType::TransformType::MatrixType matrix;
			typename KernelType::TransformType::OutputVectorType offset;

			typename KernelType::TransformType::ConstPointer spModel = pKernel->getTransformModel();

			if (spModel.IsNull())
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot store kernel. Reason: Kernel seems to have no valid transform model instance. Kernel: "
								  << pKernel);
			}

			if (!spModel->getAffineMatrixDecomposition(matrix, offset))
			{
				mapExceptionMacro(core::ServiceException,
								  << "Error: cannot store kernel. Reason: Kernel has no valid matrix decompostion. Kernel: " <<
								  pKernel);
			};

			structuredData::Element::Pointer spKernelElement = structuredData::Element::New();

			spKernelElement->setTag(tags::Kernel);

			spKernelElement->setAttribute(tags::InputDimensions, core::convert::toStr(VInputDimensions));

			spKernelElement->setAttribute(tags::OutputDimensions, core::convert::toStr(VOutputDimensions));

			spKernelElement->addSubElement(structuredData::Element::createElement(tags::StreamProvider,
										   this->getProviderName()));

			spKernelElement->addSubElement(structuredData::Element::createElement(tags::KernelType,
										   "MatrixModelKernel"));

			//add matrix
			structuredData::Element::Pointer spMatrixElement = structuredData::Element::New();

			spMatrixElement->setTag(tags::Matrix);

			structuredData::Element::Pointer spMatrixStrElement = structuredData::Element::New();

			spMatrixStrElement->setTag(tags::MatrixStr);

			//set matrix as string
			core::OStringStream matrixOS;

			//set matrix as seperated elements
			for (unsigned int rowID = 0; rowID < KernelType::TransformType::MatrixType::RowDimensions; ++rowID)
			{
				for (unsigned int colID = 0; colID < KernelType::TransformType::MatrixType::ColumnDimensions;
					 ++colID)
				{
					structuredData::Element::Pointer spValueElement = structuredData::Element::New();
					spValueElement->setTag(tags::Value);
					spValueElement->setValue(core::convert::toStr(matrix(rowID, colID)));
					spValueElement->setAttribute(tags::Column, core::convert::toStr(colID));
					spValueElement->setAttribute(tags::Row, core::convert::toStr(rowID));
					spMatrixElement->addSubElement(spValueElement);

					matrixOS << matrix(rowID, colID) << " ";
				}
			}

			spMatrixStrElement->setValue(matrixOS.str());

			spKernelElement->addSubElement(spMatrixElement);
			spKernelElement->addSubElement(spMatrixStrElement);

			//add offset
			structuredData::Element::Pointer spOffsetElement = structuredData::Element::New();
			spOffsetElement->setTag(tags::Offset);
			structuredData::Element::Pointer spOffsetStrElement = structuredData::Element::New();
			spOffsetStrElement->setTag(tags::OffsetStr);
			core::OStringStream offsetOS;

			for (unsigned int rowID = 0; rowID < KernelType::TransformType::MatrixType::RowDimensions; ++rowID)
			{
				structuredData::Element::Pointer spValueElement = structuredData::Element::New();
				spValueElement->setTag(tags::Value);
				spValueElement->setValue(core::convert::toStr(offset[rowID]));
				spValueElement->setAttribute(tags::Row, core::convert::toStr(rowID));
				spOffsetElement->addSubElement(spValueElement);

				offsetOS << offset[rowID] << " ";
			}

			spOffsetStrElement->setValue(offsetOS.str());

			spKernelElement->addSubElement(spOffsetElement);
			spKernelElement->addSubElement(spOffsetStrElement);

			return spKernelElement;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		MatrixModelBasedKernelWriter()
		{};


	} // end namespace io
} // end namespace map

#endif
