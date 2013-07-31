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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKBSplineDeformableTransform.tpp $
*/



#include "mapITKBSplineDeformableTransform.h"
#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			const typename ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::TransformBaseType *
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			getTransform() const
			{
				assert(_spInternalTransform.IsNotNull());
				return _spInternalTransform.GetPointer();
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			typename ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::TransformBaseType *
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			getTransform()
			{
				assert(_spInternalTransform.IsNotNull());
				return _spInternalTransform.GetPointer();
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			const typename ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::TransformType *
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			getConcreteTransform() const
			{
				assert(_spInternalTransform.IsNotNull());
				return _spInternalTransform.GetPointer();
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			typename ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::TransformType *
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			getConcreteTransform()
			{
				assert(_spInternalTransform.IsNotNull());
				return _spInternalTransform.GetPointer();
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			bool
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			getInverse(InverseTransformModelBasePointer &spInverseModel) const
			{
				assert(_spInternalTransform.IsNotNull());

				InverseTransformModelPointer spInternalInverse = InverseTransformModelType::New();

				InverseTransformType *pInverse = spInternalInverse->getConcreteTransform();
				bool result = _spInternalTransform->GetInverse(pInverse);

				spInverseModel = spInternalInverse.GetPointer();

				return result;
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			bool
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			getAffineMatrixDecomposition(MatrixType &matrix, OutputVectorType &offset) const
			{
				return false;
			};
			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			typename ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::TransformModelBasePointer
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			clone() const
			{
				::itk::LightObject::Pointer spClone = CreateAnother();
				TransformModelBasePointer spClonedModel = dynamic_cast<typename Superclass::TransformModelBaseType *>(spClone.GetPointer());

				if (spClonedModel.IsNull())
				{
					mapDefaultExceptionMacro( << "Error. Transform model cannot clone itself. Model: " << *this);
				}

				try
				{
					//set the fixed befor the normal parameters because some itk transforms need the fixed parameters to properly handle the setting
					//of the normal parameters.
					spClonedModel->getTransform()->SetFixedParameters(this->getTransform()->GetFixedParameters());
				}
				catch (...)
				{
					//not every transform has fixed parameters and the default implementation of itk
					//throws an exception if you try to get or set exception in these cases.
					//catch the exception an go on, with just setting the normal parameters
				}

				spClonedModel->getTransform()->SetParametersByValue(this->getTransform()->GetParameters());

				return spClonedModel;
			};



			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			ITKTransformModel()
			{
				_spInternalTransform = TransformType::New();
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			~ITKTransformModel()
			{
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			unsigned long
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			GetMTime() const
			{
				return _spInternalTransform->GetMTime();
			};

			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			void
			ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >::
			Modified() const
			{
				_spInternalTransform->Modified();
			};

		}
	}
}
