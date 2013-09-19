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




#ifndef __ITK_DIMENSIONED_TRANSFORM_MODEL_TPP
#define __ITK_DIMENSIONED_TRANSFORM_MODEL_TPP

#include "mapITKDimensionedTransformModel.h"
#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace core
	{

		template< template <typename> class TTransform, class TScalarType>
		const typename ITKDimensionedTransformModel<TTransform, TScalarType>::TransformBaseType*
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		getTransform() const
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename> class TTransform, class TScalarType>
		typename ITKDimensionedTransformModel<TTransform, TScalarType>::TransformBaseType*
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		getTransform()
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename> class TTransform, class TScalarType>
		const typename ITKDimensionedTransformModel<TTransform, TScalarType>::TransformType*
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		getConcreteTransform() const
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename> class TTransform, class TScalarType>
		typename ITKDimensionedTransformModel<TTransform, TScalarType>::TransformType*
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		getConcreteTransform()
		{
			assert(_spInternalTransform.IsNotNull());
			return _spInternalTransform.GetPointer();
		};

		template< template <typename> class TTransform, class TScalarType>
		bool
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		getInverse(InverseTransformModelBasePointer& spInverseModel) const
		{
			assert(_spInternalTransform.IsNotNull());

			InverseTransformModelPointer spInternalInverse = this->createInverse();

			InverseTransformType* pInverse = spInternalInverse->getConcreteTransform();
			bool result = _spInternalTransform->GetInverse(pInverse);

			spInverseModel = spInternalInverse.GetPointer();

			return result;
		};


		template< template <typename> class TTransform, class TScalarType>
		typename ITKDimensionedTransformModel<TTransform, TScalarType>::TransformModelBasePointer
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		clone() const
		{
			::itk::LightObject::Pointer spClone = this->createAnotherInstance().GetPointer();
			TransformModelBasePointer spClonedModel = dynamic_cast<TransformModelBaseType*>
					(spClone.GetPointer());

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



		template< template <typename> class TTransform, class TScalarType>
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		ITKDimensionedTransformModel()
		{
			_spInternalTransform = TransformType::New();
		};

		template< template <typename> class TTransform, class TScalarType>
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		~ITKDimensionedTransformModel()
		{
		};

		template< template <typename> class TTransform, class TScalarType>
		unsigned long
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		GetMTime() const
		{
			return _spInternalTransform->GetMTime();
		};

		template< template <typename> class TTransform, class TScalarType>
		void
		ITKDimensionedTransformModel<TTransform, TScalarType>::
		Modified() const
		{
			_spInternalTransform->Modified();
		};


	}
}

#endif
