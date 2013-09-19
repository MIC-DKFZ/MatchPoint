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




#ifndef __MAP_ITK_Similarity2D_TRANSFORM_H
#define __MAP_ITK_Similarity2D_TRANSFORM_H

#include "mapITKTransformModel.h"
#include "mapITKDimensionedTransformModel.h"
#include "itkSimilarity2DTransform.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::Similarity2DTransform.
			@ingroup ITK
			@ingroup ITKTransformModel
			*/
			template<class TScalarType>
			class ITKTransformModel< ::itk::Similarity2DTransform<TScalarType> >:
				public map::core::ITKDimensionedTransformModel< ::itk::Similarity2DTransform, TScalarType>
			{
			public:
				typedef ITKTransformModel< ::itk::Similarity2DTransform<TScalarType> >  Self;
				typedef map::core::ITKDimensionedTransformModel< ::itk::Similarity2DTransform, TScalarType>
				Superclass;
				typedef ::itk::SmartPointer<Self>        Pointer;
				typedef ::itk::SmartPointer<const Self>  ConstPointer;

				itkTypeMacro(ITKTransformModel, ITKDimensionedTransformModel);
				itkNewMacro(Self);

				typedef typename Superclass::TransformModelBasePointer        TransformModelBasePointer;

				typedef typename Superclass::ScalarType                       ScalarType;
				typedef typename Superclass::MatrixType                       MatrixType;
				typedef typename Superclass::OutputVectorType                 OutputVectorType;

				typedef typename Superclass::InverseTransformModelBaseType    InverseTransformModelBaseType;
				typedef typename Superclass::InverseTransformModelBasePointer InverseTransformModelBasePointer;

				typedef typename Superclass::InverseTransformModelType        InverseTransformModelType;
				typedef typename Superclass::InverseTransformModelPointer     InverseTransformModelPointer;

				typedef typename Superclass::TransformBaseType                TransformBaseType;
				typedef typename Superclass::TransformBasePointer             TransformBasePointer;
				typedef typename Superclass::InverseTransformBaseType         InverseTransformBaseType;
				typedef typename Superclass::InverseTransformBasePointer      InverseTransformBasePointer;

				typedef typename Superclass::TransformType                    TransformType;
				typedef typename Superclass::TransformPointer                 TransformPointer;
				typedef typename Superclass::InverseTransformType             InverseTransformType;
				typedef typename Superclass::InverseTransformPointer          InverseTransformPointer;

				virtual bool getAffineMatrixDecomposition(MatrixType& matrix, OutputVectorType& offset) const
				{
					matrix = Superclass::getConcreteTransform()->GetMatrix();
					offset = Superclass::getConcreteTransform()->GetOffset();

					return true;
				};

			protected:

				virtual InverseTransformModelPointer createInverse() const
				{
					//cause translation is an unary transform model the inverse model is equivalent to the model.
					InverseTransformModelPointer spNew = New().GetPointer();
					return spNew;
				};

				virtual TransformModelBasePointer createAnotherInstance() const
				{
					TransformModelBasePointer spNew = New().GetPointer();
					return spNew;
				};

				ITKTransformModel() {};

				virtual ~ITKTransformModel() {};

			private:
				ITKTransformModel(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#endif
