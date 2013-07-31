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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapTransformModel.h $
*/




#ifndef __TRANSFORM_MODEL_H
#define __TRANSFORM_MODEL_H

#include "mapTransformModelCreationPolicy.h"
#include "mapTransformModelBase.h"

namespace map
{
	namespace core
	{
		/*! @brief Base classe for transform model representation containing an concrete internal itk::Transform as representation.
		* In difference to TransformModelBase this class defines the interface parts to directly access the concrete transform
		* instance.
		*
		* \ingroup TransformModel
		*/
		template< template <typename, unsigned int, unsigned int> class TTransform, class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class TransformModel : public TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>,
			public TransformModelCreationPolicy<TTransform, TScalarType, VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef TransformModel<TTransform, TScalarType, VInputDimensions, VOutputDimensions>  Self;
			typedef TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>  Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(TransformModel, TransformModelBase);

			typedef TransformModelCreationPolicy < TTransform, TScalarType,
			        VInputDimensions,
			        VOutputDimensions >       CreationPolicyType;
			typedef typename Superclass::ScalarType                       ScalarType;

			typedef typename Superclass::InverseTransformModelBaseType    InverseTransformModelBaseType;
			typedef typename Superclass::InverseTransformModelBasePointer InverseTransformModelBasePointer;

			typedef typename TransformModel < TTransform, TScalarType,
			        VOutputDimensions,
			        VInputDimensions >             InverseTransformModelType;
			typedef typename InverseTransformModelType::Pointer           InverseTransformModelPointer;

			typedef typename Superclass::TransformBaseType                TransformBaseType;
			typedef typename Superclass::TransformBasePointer             TransformBasePointer;
			typedef typename Superclass::InverseTransformBaseType         InverseTransformBaseType;
			typedef typename Superclass::InverseTransformBasePointer      InverseTransformBasePointer;

			typedef typename CreationPolicyType::TransformType                  TransformType;
			typedef typename TransformType::Pointer                             TransformPointer;
			typedef typename InverseTransformModelType::TransformType           InverseTransformType;
			typedef typename InverseTransformModelType::TransformPointer        InverseTransformPointer;

			virtual const TransformBaseType &getTransform() const;
			virtual TransformBaseType &getTransform();

			virtual const TransformType &getConcreteTransform() const;
			virtual TransformType &getConcreteTransform();

			operator const TransformType &() const
			{
				return getConcreteTransform();
			}
			operator TransformType &()
			{
				return getConcreteTransform();
			}

			virtual bool getInverse(InverseTransformModelBasePointer &spInverseModel) const;

		protected:

			TransformPointer _spInternalTransform;

			TransformModel();

			virtual ~TransformModel();

		private:
			TransformModel(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapTransformModel.tpp"
#endif

#endif
