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

#ifndef __MODEL_BASED_REGISTRATION_KERNEL_TPP
#define __MODEL_BASED_REGISTRATION_KERNEL_TPP

#include "mapAffineMatrixOffsetDecompositionPolicy.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		String
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		getModelName() const
		{
			assert(_spTransformModel.IsNotNull());
			return _spTransformModel->GetNameOfClass();
		};


		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::ParametersType
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		getParameters() const
		{
			assert(_spTransformModel.IsNotNull());
			return _spTransformModel->GetParameters();
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::OutputPointType
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		transformPoint(const InputPointType& inPoint) const
		{
			assert(_spTransformModel.IsNotNull());
			return _spTransformModel->TransformPoint(inPoint);
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::OutputVectorType
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		transformVector(const InputVectorType& inVector) const
		{
			assert(_spTransformModel.IsNotNull());
			return _spTransformModel->TransformVector(inVector);
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const
		{
			assert(_spTransformModel.IsNotNull());
			outPoint = _spTransformModel->TransformPoint(inPoint);
			return true;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		const typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::TransformType*
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		getTransformModel() const
		{
			return _spTransformModel;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		setTransformModel(TransformType* pTransform)
		{
			_spTransformModel = pTransform;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		getLargestPossibleRepresentation() const
		{
			RepresentationDescriptorConstPointer spDummy = NULL;
			return spDummy;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		ModelBasedRegistrationKernel() : _spTransformModel(NULL)
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		~ModelBasedRegistrationKernel()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		precomputeKernel()
		{
			//nothing to precompute
		};

			/*! Tries to decompose the transform model into an affine matrix and an offset. It is indecated by the return value if
			 * the actual modell can be decomposed.\n
			 * Usage of the return values: Point_trans = Matrix*Point + Offset
			 *
			 * @eguarantee strong
			 * @remark Implement the function for special transform model classes.
			 * @param [out] matrix Reference to the matrix that define the affine non-translation part (e.g. rotation and scaling).
			 * @param [out] offset Reference to a vector that defines the translation offset.
			 * @return Indicates if the transform model can be decomposed in a affine transformation matrix plus offset. If it returns false, it cannot be decomposed
			 * and the referenced output parameters are invalid.*/
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
      ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
      getAffineMatrixDecomposition(MatrixType& matrix, OutputVectorType& offset) const
    {
      return AffineMatrixOffsetDecompositionPolicy<typename TransformType::ScalarType, VInputDimensions, VOutputDimensions>::getAffineMatrixDecomposition(_spTransformModel.GetPointer(), matrix,offset);
    };



		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "Transform model: ";

			if (_spTransformModel.IsNull())
			{
				os << "NULL" << std::endl;
			}
			else
			{
				os << std::endl;
				_spTransformModel->Print(os);
				os << std::endl;
			}
		};

	} // end namespace core
} // end namespace map

#endif
