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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapModelBasedRegistrationKernel.tpp $
*/

#ifndef __MODEL_BASED_REGISTRATION_KERNEL_TPP
#define __MODEL_BASED_REGISTRATION_KERNEL_TPP

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
			return _spTransformModel->getTransform()->GetParameters();
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::OutputPointType
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		transformPoint(const InputPointType &inPoint) const
		{
			assert(_spTransformModel.IsNotNull());
			return _spTransformModel->getTransform()->TransformPoint(inPoint);
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::OutputVectorType
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		transformVector(const InputVectorType &inVector) const
		{
			assert(_spTransformModel.IsNotNull());
			return _spTransformModel->getTransform()->TransformVector(inVector);
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		doMapPoint(const InputPointType &inPoint, OutputPointType &outPoint) const
		{
			assert(_spTransformModel.IsNotNull());
			outPoint = _spTransformModel->getTransform()->TransformPoint(inPoint);
			return true;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		const typename ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::TransformType *
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		getTransformModel() const
		{
			return _spTransformModel;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		setTransformModel(TransformType *pTransform)
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


		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		ModelBasedRegistrationKernel<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream &os, itk::Indent indent) const
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
