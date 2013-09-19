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




#ifndef __TRANSFORM_MODEL_BASE_H
#define __TRANSFORM_MODEL_BASE_H

#include "itkTransform.h"
#include "itkMatrix.h"
namespace map
{
	namespace core
	{

		/*! @brief Base class for the transform model representation in MatchPoint.
		 * It serves as a wrapper arround itk:Transform to extend the transform interface
		 * by special features needed by MatchPoint. E.g.: the GetInverse() method of itk:Transform
		 * is non virutal and only suitable for symmetric transforms (input and output space have the
		 * same dimensions).
		 *
		 * @ingroup TransformModel
		 */
		template<class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class TransformModelBase : public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			typedef TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>  Self;
			typedef itk::Object  Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(TransformModelBase, itk::Object);

			itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
			itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);
			itkStaticConstMacro(MatrixInputDimensions, unsigned int, VInputDimensions + 1);
			itkStaticConstMacro(MatrixOutputDimensions, unsigned int, VOutputDimensions + 1);

			typedef TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>
			TransformModelBaseType;
			typedef typename TransformModelBaseType::Pointer TransformModelBasePointer;

			typedef TScalarType ScalarType;
			typedef itk::Transform<TScalarType, VInputDimensions, VOutputDimensions>      TransformBaseType;
			typedef typename TransformBaseType::Pointer                                 TransformBasePointer;
			typedef itk::Transform<TScalarType, VOutputDimensions, VInputDimensions>
			InverseTransformBaseType;
			typedef typename InverseTransformBaseType::Pointer
			InverseTransformBasePointer;
			typedef TransformModelBase<TScalarType, VOutputDimensions, VInputDimensions>
			InverseTransformModelBaseType;
			typedef typename InverseTransformModelBaseType::Pointer
			InverseTransformModelBasePointer;

			typedef typename TransformBaseType::InputVectorType       InputVectorType;
			typedef typename TransformBaseType::OutputVectorType      OutputVectorType;
			typedef typename TransformBaseType::InputPointType        InputPointType;
			typedef typename TransformBaseType::OutputPointType       OutputPointType;
			typedef typename TransformBaseType::ParametersType        ParametersType;

			typedef itk::Matrix<TScalarType, VOutputDimensions, VInputDimensions> MatrixType;


			virtual const TransformBaseType* getTransform() const = 0;
			virtual TransformBaseType* getTransform() = 0;

			/*! Inverts the transform model and returns the inverse transform model via the parameter
			 * spInverseModel.
			 * @eguarantee strong
			 * @remark Implement the function for special transform model classes.
			 * @param [out] spInverseModel Referenz to a smart pointer that should store the inverted model
			 * any value referenced by the smart pointer before the function call will be overwritten.
			 * @return Indicates if the transform could be inverted. If returns false, spInverseModel was
			 * not changed and thus is likely to be and should assumed as incorrect.*/
			virtual bool getInverse(InverseTransformModelBasePointer& spInverseModel) const = 0;

			/*! clones the transform model and copies all parameters.
			 * spInverseModel.
			 * @eguarantee strong
			 * @remark Implement the function for special transform model classes.
			 * @return Smartpointer to the cloned transform model.*/
			virtual TransformModelBasePointer clone() const = 0;

			/*! Tries to decompose the transform model into an affine matrix and an offset. It is indecated by the return value if
			 * the actual modell can be decomposed.\n
			 * Usage of the return values: Point_trans = Matrix*Point + Offset
			 *
			 * @eguarantee strong
			 * @remark Implement the function for special transform model classes.
			 * @param [out] matrix Referenz to the matrix that define the affine non-translation part (e.g. rotation and scaling).
			 * @param [out] offset Referenz to a vector that defines the translation offset.
			 * @return Indicates if the transform model can be decomposed in a affine transformation matrix plus offset. If it returns false, it cannot be decomposed
			 * and the referenced output parameters are invalid.*/
			virtual bool getAffineMatrixDecomposition(MatrixType& matrix, OutputVectorType& offset) const = 0;

		protected:
			operator const TransformBaseType& () const
			{
				return getTransform();
			}
			operator TransformBaseType& ()
			{
				return getTransform();
			}

			TransformModelBase();

			virtual ~TransformModelBase();

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:
			TransformModelBase(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

		template<class TScalarType, unsigned int VInputDimensions, unsigned int VOutputDimensions>
		std::ostream& operator<<(std::ostream& os,
								 const TransformModelBase<TScalarType, VInputDimensions, VOutputDimensions>& model);

	}
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapTransformModelBase.tpp"
#endif

#endif
