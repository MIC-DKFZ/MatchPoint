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




#ifndef __ITK_DIMENSIONED_TRANSFORM_MODEL_H
#define __ITK_DIMENSIONED_TRANSFORM_MODEL_H

#include "mapTransformModelBase.h"

namespace map
{
	namespace core
	{
		/*! @brief Base classe for transform model representation containing an concrete internal itk::Transform with
		* a fixed dimension (e.g. Rigid2DTransform) and just the skalar type as template variable.
		* In difference to TransformModelBase this class defines the interface parts to directly access the concrete transform
		* instance.
		*
		* @ingroup TransformModel
		*/
		template< template <typename> class TTransform, class TScalarType>
		class ITKDimensionedTransformModel : public
			TransformModelBase<TScalarType, TTransform<TScalarType>::InputSpaceDimension, TTransform<TScalarType>::OutputSpaceDimension>
		{
		public:
			/*! Standard class typedefs. */
			typedef ITKDimensionedTransformModel<TTransform, TScalarType>  Self;
			typedef TransformModelBase<TScalarType, TTransform<TScalarType>::InputSpaceDimension, TTransform<TScalarType>::OutputSpaceDimension>
			Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(ITKDimensionedTransformModel, TransformModelBase);

			typedef typename Superclass::TransformModelBaseType           TransformModelBaseType;
			typedef typename Superclass::TransformModelBasePointer        TransformModelBasePointer;

			typedef typename Superclass::ScalarType                       ScalarType;

			typedef typename Superclass::InverseTransformModelBaseType    InverseTransformModelBaseType;
			typedef typename Superclass::InverseTransformModelBasePointer InverseTransformModelBasePointer;

			typedef ITKDimensionedTransformModel < TTransform,
					TScalarType >          InverseTransformModelType;
			typedef typename InverseTransformModelType::Pointer           InverseTransformModelPointer;

			typedef typename Superclass::TransformBaseType                TransformBaseType;
			typedef typename Superclass::TransformBasePointer             TransformBasePointer;
			typedef typename Superclass::InverseTransformBaseType         InverseTransformBaseType;
			typedef typename Superclass::InverseTransformBasePointer      InverseTransformBasePointer;

			typedef TTransform<TScalarType>                               TransformType;
			typedef typename TransformType::Pointer                       TransformPointer;
			typedef typename InverseTransformModelType::TransformType     InverseTransformType;
			typedef typename InverseTransformModelType::TransformPointer  InverseTransformPointer;

			virtual const TransformBaseType* getTransform() const;
			virtual TransformBaseType* getTransform();

			virtual const TransformType* getConcreteTransform() const;
			virtual TransformType* getConcreteTransform();

			virtual bool getInverse(InverseTransformModelBasePointer& spInverseModel) const;

			virtual TransformModelBasePointer clone() const;

			/*! The transform model is just a management wrapper arround the itk transform.
			 * Thus the modification time of the transform model is the modification time of the transfrom.  */
			virtual unsigned long GetMTime() const;

			/*! The transform model is just a management wrapper arround the itk transform.
			 * Thus the modification of the model must be passed through to the transform.  */
			virtual void Modified() const;

		protected:
			operator const TransformType& () const
			{
				return getConcreteTransform();
			}
			operator TransformType& ()
			{
				return getConcreteTransform();
			}

			/*! Internal helper method that returns an instance of the real inverse transform model that is derived from this class.
			 * Must be implemented in the concrete model class.
			 * see mapITKTranslationTransform.h as an example.*/
			virtual InverseTransformModelPointer createInverse() const = 0;
			/*! Internal helper method that returns another instance of the real transform model that is derived from this class.
			 * Must be implemented in the concrete model class.
			 * see mapITKTranslationTransform.h as an example.*/
			virtual TransformModelBasePointer createAnotherInstance() const = 0;

			TransformPointer _spInternalTransform;

			ITKDimensionedTransformModel();

			virtual ~ITKDimensionedTransformModel();

		private:
			ITKDimensionedTransformModel(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapITKDimensionedTransformModel.tpp"
#endif

#endif
