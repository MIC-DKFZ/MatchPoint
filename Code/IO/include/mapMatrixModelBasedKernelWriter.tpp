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
#include "mapSDITKStreamingHelper.h"

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
				typename KernelType::MatrixType matrix;
				typename KernelType::OutputVectorType offset;

				if (pKernel->getAffineMatrixDecomposition(matrix, offset))
				{
					canHandle = true;
				}
			};

			return canHandle;
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		getProviderName() const
		{
			return Self::getStaticProviderName();
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		getStaticProviderName()
		{
			::map::core::OStringStream os;
			os << "MatrixModelBasedKernelWriter<" << VInputDimensions << "," << VOutputDimensions << ">";
			return os.str();
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		::map::core::String
		MatrixModelBasedKernelWriter<VInputDimensions, VOutputDimensions>::
		getDescription() const
		{
			::map::core::OStringStream os;
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
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error: cannot store kernel. Reason: cannot cast to ModelBasedKernel: " << pKernel);
			}

			typename KernelType::TransformType::MatrixType matrix;
			typename KernelType::TransformType::OutputVectorType offset;

			typename KernelType::TransformType::ConstPointer spModel = pKernel->getTransformModel();

			if (spModel.IsNull())
			{
				mapExceptionMacro(::map::core::ServiceException,
								  << "Error: cannot store kernel. Reason: Kernel seems to have no valid transform model instance. Kernel: "
								  << pKernel);
			}

			if (!pKernel->getAffineMatrixDecomposition(matrix, offset))
			{
				mapExceptionMacro(::map::core::ServiceException,
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
			structuredData::Element::Pointer spMatrixElement = structuredData::streamITKMatrixToSD(matrix);

			spMatrixElement->setTag(tags::Matrix);

			//set matrix as string
			structuredData::Element::Pointer spMatrixStrElement = structuredData::Element::New();

			spMatrixStrElement->setTag(tags::MatrixStr);

			::map::core::OStringStream matrixOS;

			for (unsigned int rowID = 0; rowID < KernelType::TransformType::MatrixType::RowDimensions; ++rowID)
			{
				for (unsigned int colID = 0; colID < KernelType::TransformType::MatrixType::ColumnDimensions;
					 ++colID)
				{
					matrixOS << matrix(rowID, colID) << " ";
				}
			}

			spMatrixStrElement->setValue(matrixOS.str());

			spKernelElement->addSubElement(spMatrixElement);
			spKernelElement->addSubElement(spMatrixStrElement);

			//add offset
			structuredData::Element::Pointer spOffsetElement = structuredData::streamITKFixedArrayToSD(offset);
			spOffsetElement->setTag(tags::Offset);
			structuredData::Element::Pointer spOffsetStrElement = structuredData::Element::New();
			spOffsetStrElement->setTag(tags::OffsetStr);
			::map::core::OStringStream offsetOS;

			for (unsigned int rowID = 0; rowID < KernelType::TransformType::MatrixType::RowDimensions; ++rowID)
			{
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
