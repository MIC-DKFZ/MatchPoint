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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapTransformModel.tpp $
*/




#ifndef __TRANSFORM_MODEL_TPP
#define __TRANSFORM_MODEL_TPP

#include "mapTransformModel.h"

namespace map
{
	namespace core
	{

		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		const typename TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::TransformBaseType &
		TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::
		getTransform() const
		{
			assert(_spInternalTransform.IsNotNull());
			return *(_spInternalTransform.GetPointer());
		};

		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::TransformBaseType &
		TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::
		getTransform()
		{
			assert(_spInternalTransform.IsNotNull());
			return *(_spInternalTransform.GetPointer());
		};

		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		const typename TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::TransformType &
		TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::
		getConcreteTransform() const
		{
			assert(_spInternalTransform.IsNotNull());
			return *(_spInternalTransform.GetPointer());
		};

		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::TransformType &
		TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::
		getConcreteTransform()
		{
			assert(_spInternalTransform.IsNotNull());
			return *(_spInternalTransform.GetPointer());
		};

		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::
		getInverse(InverseTransformModelBasePointer &spInverseModel) const
		{
			assert(_spInternalTransform.IsNotNull());

			bool result = VInputDimensions == VOutputDimensions;

			spInverseModel = InverseTransformModel::New();
			InverseTransformType *pInverse = spInverseModel->getTransform();
			result = CreationPolicyType::createInverse(_spInternalTransform, pInverse);

			return result;
		};

		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::
		TransformModel()
		{
			_spInternalTransform = TransformType::New();
		};

		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>::
		~TransformModel()
		{
		};



	}
}

#endif
