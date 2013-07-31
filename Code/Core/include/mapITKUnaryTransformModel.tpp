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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapITKUnaryTransformModel.tpp $
*/




#ifndef __ITK_UNARY_TRANSFORM_MODEL_TPP
#define __ITK_UNARY_TRANSFORM_MODEL_TPP

#include "mapITKUnaryTransformModel.h"
#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace core
	{

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		const typename ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::TransformBaseType *
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		getTransform() const
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		typename ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::TransformBaseType *
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		getTransform()
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		const typename ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::TransformType *
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		getConcreteTransform() const
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		typename ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::TransformType *
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		getConcreteTransform()
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		bool
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		getInverse(InverseTransformModelBasePointer &spInverseModel) const
		{
			assert(_spInternalTransform.IsNotNull());

			InverseTransformModelPointer spInternalInverse = this->createInverse();

			InverseTransformType *pInverse = spInternalInverse->getConcreteTransform();
			bool result = _spInternalTransform->GetInverse(pInverse);

			spInverseModel = spInternalInverse.GetPointer();

			return result;
		};


		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		typename ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::TransformModelBasePointer
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		clone() const
		{
			::itk::LightObject::Pointer spClone = this->createAnotherInstance().GetPointer();
			TransformModelBasePointer spClonedModel = dynamic_cast<TransformModelBaseType *>(spClone.GetPointer());

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

			spClonedModel->getTransform()->SetParameters(this->getTransform()->GetParameters());

			return spClonedModel;
		};



		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		ITKUnaryTransformModel()
		{
			_spInternalTransform = TransformType::New();
		};

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		~ITKUnaryTransformModel()
		{
		};

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		unsigned long
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		GetMTime() const
		{
			return _spInternalTransform->GetMTime();
		};

		template< template <typename, unsigned int> class TTransform, class TScalarType, unsigned int VDimensions>
		void
		ITKUnaryTransformModel<TTransform, TScalarType, VDimensions>::
		Modified() const
		{
			_spInternalTransform->Modified();
		};


	}
}

#endif
