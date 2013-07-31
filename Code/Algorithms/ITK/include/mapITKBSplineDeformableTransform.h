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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKBSplineDeformableTransform.h $
*/




#ifndef __MAP_ITK_BSplineDeformable_TRANSFORM_H
#define __MAP_ITK_BSplineDeformable_TRANSFORM_H

#include "mapITKTransformModel.h"
#include "mapTransformModelBase.h"
#include "mapITKDimensionedTransformModel.h"
#include "itkBSplineDeformableTransform.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::BSplineDeformableTransform.
			@ingroup ITK
			@ingroup ITKTransformModel
			*/
			template<class TScalarType, unsigned int VDimensions, unsigned int VSplineOrder>
			class ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >:
				public map::core::TransformModelBase<TScalarType, VDimensions, VDimensions>
			{
			public:
				/*! Standard class typedefs. */
				typedef ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> >  Self;
				typedef map::core::TransformModelBase<TScalarType, VDimensions, VDimensions>  Superclass;
				typedef ::itk::SmartPointer<Self>        Pointer;
				typedef ::itk::SmartPointer<const Self>  ConstPointer;

				itkTypeMacro(ITKTransformModel, TransformModelBase);
				itkNewMacro(Self);

				typedef typename Superclass::TransformModelBasePointer        TransformModelBasePointer;

				typedef typename Superclass::ScalarType                       ScalarType;
				typedef typename Superclass::MatrixType                       MatrixType;
				typedef typename Superclass::OutputVectorType                 OutputVectorType;

				typedef typename Superclass::InverseTransformModelBaseType    InverseTransformModelBaseType;
				typedef typename Superclass::InverseTransformModelBasePointer InverseTransformModelBasePointer;

				typedef ITKTransformModel< ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder> > InverseTransformModelType;
				typedef typename InverseTransformModelType::Pointer           InverseTransformModelPointer;

				typedef typename Superclass::TransformBaseType                TransformBaseType;
				typedef typename Superclass::TransformBasePointer             TransformBasePointer;
				typedef typename Superclass::InverseTransformBaseType         InverseTransformBaseType;
				typedef typename Superclass::InverseTransformBasePointer      InverseTransformBasePointer;

				typedef typename ::itk::BSplineDeformableTransform<TScalarType, VDimensions, VSplineOrder>          TransformType;
				typedef typename TransformType::Pointer                       TransformPointer;
				typedef typename InverseTransformModelType::TransformType     InverseTransformType;
				typedef typename InverseTransformModelType::TransformPointer  InverseTransformPointer;

				virtual const TransformBaseType *getTransform() const;
				virtual TransformBaseType *getTransform();

				virtual const TransformType *getConcreteTransform() const;
				virtual TransformType *getConcreteTransform();

				virtual bool getInverse(InverseTransformModelBasePointer &spInverseModel) const;

				virtual TransformModelBasePointer clone() const;

				/*! The transform model is just a management wrapper arround the itk transform.
				* Thus the modification time of the transform model is the modification time of the transfrom.  */
				virtual unsigned long GetMTime() const;

				/*! The transform model is just a management wrapper arround the itk transform.
				* Thus the modification of the model must be passed through to the transform.  */
				virtual void Modified() const;

				virtual bool getAffineMatrixDecomposition(MatrixType &matrix, OutputVectorType &offset) const;

			protected:
				operator const TransformType &() const
				{
					return getConcreteTransform();
				}
				operator TransformType &()
				{
					return getConcreteTransform();
				}

				TransformPointer _spInternalTransform;

				ITKTransformModel();

				virtual ~ITKTransformModel();

			private:
				ITKTransformModel(const Self &); //purposely not implemented
				void operator=(const Self &); //purposely not implemented
			};
		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapITKBSplineDeformableTransform.tpp"
#endif

#endif
