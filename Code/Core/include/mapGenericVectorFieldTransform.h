/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __mapGenericVectorFieldTransform_h
#define __mapGenericVectorFieldTransform_h

#include "itkTransform.h"

#include "itkImage.h"
#include "itkMatrixOffsetTransformBase.h"
#include "itkImageVectorOptimizerParametersHelper.h"
#include "itkVectorInterpolateImageFunction.h"

namespace itk
{

/** \class GenericVectorFieldTransform
 * \brief Provides local/dense/high-dimensionaltiy transformation via a
 * a displacement field.
 *
 * The displacement field stores vectors of displacements, with
 * dimension \c NDimensions. Transformation is performed at a given
 * point by adding the displacement at that point to the input point.
 *
 * T(x, p), x is the position, p is the local parameter at position x.
 * For a 2D example:
 *
 *  x = (x0, x1), p = (p0, p1)
 *
 * then T(x, p) is defined as:
 *
 *    T(x, p) = (T0, T1) = (x0+p0, x1+p1)
 *
 *
 * The displacement field is defined using an itkImage, and must be set
 * before use by the user, using \c SetGenericVectorField. The image has
 * the same dimensionality as the input and output spaces, defined by
 * template parameter \c NDimensions, and is an image of vectors of
 * type \c OutputVectorType, with dimensionality NDimensions as well.
 *
 * An interpolator of type \c VectorInterpolateImageFunction is used with
 * the displacement field image. By default,
 * VectorLinearInterpolateImageFunction is used, and the user can override
 * using SetInterpolator.
 *
 * The displacement field data is stored using the common
 * \c OptimizerParameters type
 * in conjunction with the \c ImageVectorOptimizerParametersHelper class. This
 * allows access of the displacement field image as if it were an itkArray,
 * allowing transparent use with other classes.
 * \warning The \c SetParameters
 * method will copy the passed parameters, which can be costly since
 * displacement fields are dense and thus potentially very large.
 *
 * The \c UpdateTransformParameters method simply adds the provided
 * update array, applying the usual optional scaling factor. Derived
 * classes may provide different behavior.
 *
 * Because this is a local transform, methods that have a version that takes
 * a point must be used, such as \c TransformVector,
 * \c TransformCovariantVector, and \c TransformDiffusionTensor. Also,
 * \c ComputeJacobianWithRespectToParameters simply returns
 * an identity matrix (see method documentation),
 * and \c ComputeJacobianWithRespectToPosition should be used.
 *
 * The differences between this class and itk::DisplacementFieldTransform 
 * are the following two:
 * - The transform allows and handles unequal input and output dimensions
 * - The transform allows to decide how to handle transform requests that
 * are outside of the field's coverage. It either uses identity (like
 * itk::DisplacementFieldTransform) or it will map points (if NULL point
 * support is activated) to a user specified
 * value (the null point) that indicates that the mapping is not valid.
 *
 * \ingroup ITKTransform
 */
template
<class TScalar, unsigned int InDimensions, unsigned int OutDimensions>
class GenericVectorFieldTransform :
    public Transform<TScalar, InDimensions, OutDimensions>
{
public:
  /** Standard class typedefs. */
  using Self = GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>;
  typedef Transform<TScalar, InDimensions, OutDimensions> Superclass;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Run-time type information (and related methods). */
  itkTypeMacro( GenericVectorFieldTransform, Transform );

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro( Self );

  using InverseTransformBaseType = typename Superclass::InverseTransformBaseType;
  using InverseTransformBasePointer = typename Superclass::InverseTransformBasePointer;

  /** Scalar type. */
  using ScalarType = typename Superclass::ScalarType;

  /** Type of the input parameters. */
  using ParametersType = typename Superclass::ParametersType;
  using ParametersValueType = typename Superclass::ParametersValueType;

  /** Jacobian type. */
  using JacobianType = typename Superclass::JacobianType;

  /** Transform category type. */
  using TransformCategoryType = typename Superclass::TransformCategoryEnum;

  /** The number of parameters defininig this transform. */
  using NumberOfParametersType = typename Superclass::NumberOfParametersType;

  /** Standard coordinate point type for this class. */
  using InputPointType = typename Superclass::InputPointType;
  using OutputPointType = typename Superclass::OutputPointType;

  /** Standard vector type for this class. */
  using InputVectorType = typename Superclass::InputVectorType;
  using OutputVectorType = typename Superclass::OutputVectorType;

  using InputVectorPixelType = typename Superclass::InputVectorPixelType;
  using OutputVectorPixelType = typename Superclass::OutputVectorPixelType;

  /** Standard covariant vector type for this class */
  using InputCovariantVectorType = typename Superclass::InputCovariantVectorType;
  using OutputCovariantVectorType = typename Superclass::OutputCovariantVectorType;

  /** Standard vnl_vector type for this class. */
  using InputVnlVectorType = typename Superclass::InputVnlVectorType;
  using OutputVnlVectorType = typename Superclass::OutputVnlVectorType;

  /** Standard diffusion tensor type for this class */
  using InputDiffusionTensor3DType = typename Superclass::InputDiffusionTensor3DType;
  using OutputDiffusionTensor3DType = typename Superclass::OutputDiffusionTensor3DType;

  /** Standard tensor type for this class */
  typedef CovariantVector<ScalarType, InputDiffusionTensor3DType::Dimension>
  InputTensorEigenVectorType;
  typedef CovariantVector<ScalarType, OutputDiffusionTensor3DType::Dimension>
  OutputTensorEigenVectorType;
  /** Derivative type */
  using DerivativeType = typename Superclass::DerivativeType;

  /** Dimension of the domain spaces. */
  itkStaticConstMacro( InDimension, unsigned int, InDimensions );
  itkStaticConstMacro( OutDimension, unsigned int, OutDimensions);

  /** Define the displacement field type and corresponding interpolator type. */
  typedef Image<OutputVectorType,  InDimensions>        GenericVectorFieldType;
  using GenericVectorFieldPointer = typename GenericVectorFieldType::Pointer;
  using GenericVectorFieldConstPointer = typename GenericVectorFieldType::ConstPointer;

  typedef VectorInterpolateImageFunction
    <GenericVectorFieldType, ScalarType> InterpolatorType;

  /** Standard types for the displacement Field */
  using IndexType = typename GenericVectorFieldType::IndexType;
  using RegionType = typename GenericVectorFieldType::RegionType;
  using SizeType = typename GenericVectorFieldType::SizeType;
  using SpacingType = typename GenericVectorFieldType::SpacingType;
  using DirectionType = typename GenericVectorFieldType::DirectionType;
  using PointType = typename GenericVectorFieldType::PointType;
  using PixelType = typename GenericVectorFieldType::PixelType;

  /** Define the internal parameter helper used to access the field */
  typedef ImageVectorOptimizerParametersHelper<
    ScalarType,
    OutputVectorType::Dimension,
    InDimension>
  OptimizerParametersHelperType;

  /** Get/Set the displacement field.
   * Set the displacement field. Create special set accessor to update
   * interpolator and assign displacement field to transform parameters
   * container. */
  virtual void SetDisplacementField(GenericVectorFieldType* field);
  itkGetModifiableObjectMacro(DisplacementField, GenericVectorFieldType);

  /** Get/Set the interpolator.
   * Create out own set accessor that assigns the displacement field */
  virtual void SetInterpolator( InterpolatorType* interpolator );
  itkGetModifiableObjectMacro( Interpolator, InterpolatorType );

  /** Get the modification time of displacement field */
  itkGetConstReferenceMacro( DisplacementFieldSetTime, ModifiedTimeType );

  /**  Method to transform a point. Out-of-bounds points will
   * be returned with zero displacemnt. */
  virtual OutputPointType TransformPoint( const InputPointType& thisPoint )
  const;

  /**  Method to transform a vector. */
  using Superclass::TransformVector;
  virtual OutputVectorType TransformVector(const InputVectorType & /*unused*/) const
  {
    itkExceptionMacro( "TransformVector(Vector) unimplemented, use "
                       "TransformVector(Vector,Point)" );
  }

  virtual OutputVectorPixelType TransformVector(const InputVectorPixelType & /*unused*/)
  const
  {
    itkExceptionMacro( "TransformVector(Vector) unimplemented, use "
                       "TransformVector(Vector,Point)" );
  }

  virtual OutputVnlVectorType TransformVector(const InputVnlVectorType & /*unused*/) const
  {
    itkExceptionMacro( "TransformVector(Vector) unimplemented, use "
                       "TransformVector(Vector,Point)" );
  }

  /** Method to transform a tensor */
  using Superclass::TransformDiffusionTensor3D;
  OutputDiffusionTensor3DType TransformDiffusionTensor(
    const InputDiffusionTensor3DType &  /*unused*/) const
  {
    itkExceptionMacro( "TransformDiffusionTensor(Tensor) unimplemented, use "
                       "TransformDiffusionTensor(Tensor,Point)" );
  }

  OutputVectorPixelType TransformDiffusionTensor(const InputVectorPixelType &  /*unused*/)
  const
  {
    itkExceptionMacro( "TransformDiffusionTensor(Tensor) unimplemented, use "
                       "TransformDiffusionTensor(Tensor,Point)" );
  }

  /**  Method to transform a CovariantVector. */
  using Superclass::TransformCovariantVector;
  virtual OutputCovariantVectorType TransformCovariantVector(
    const InputCovariantVectorType & /*unused*/) const
  {
    itkExceptionMacro( "TransformCovariantVector(CovariantVector) "
                       "unimplemented, use TransformCovariantVector(CovariantVector,Point)" );
  }

  virtual OutputVectorPixelType TransformCovariantVector(
    const InputVectorPixelType & /*unused*/) const
  {
    itkExceptionMacro( "TransformCovariantVector(CovariantVector) "
                       "unimplemented, use TransformCovariantVector(CovariantVector,Point)" );
  }

  /** Set the transformation parameters. This sets the displacement
   * field image directly. */
  virtual void SetParameters(const ParametersType & params)
  {
    if( &(this->m_Parameters) != &params )
      {
      if( params.Size() != this->m_Parameters.Size() )
        {
        itkExceptionMacro("Input parameters size (" << params.Size()
                                                    << ") does not match internal size ("
                                                    << this->m_Parameters.Size() << ").");
        }
      /* copy into existing object */
      this->m_Parameters = params;
      this->Modified();
      }
  }

  /**
   * This method sets the fixed parameters of the transform.
   * For a displacement field transform, the fixed parameters are the
   * following: field size, field origin, field spacing, and field direction.
   *
   * Note:  If a displacement field already exists, this function
   * creates a new one with zero displacement (identity transform).
   */
  virtual void SetFixedParameters( const ParametersType &  /*fixedParameters*/);

  /**
   * Compute the jacobian with respect to the parameters at a point.
   * Simply returns identity matrix, sized [NDimensions, NDimensions].
   *
   * T(x, p), x is the position, p is the local parameter at position x.
   * Take a 2D example, x = (x0, x1), p = (p0, p1) and T(x, p) is defined as:
   *
   *    T(x, p) = (T0, T1) = (x0+p0, x1+p1)
   *
   * Each local deformation is defined as a translation transform.
   * So the Jacobian w.r.t parameters are
   *
   * dT/dp =
   *    [ dT0/dp0, dT0/dp1;
   *      dT1/dp0, dT1/dp1 ];
   *
   *    = [1, 0;
   *       0, 1];
   *
   * TODO: format the above for doxygen formula.
   */
  virtual void ComputeJacobianWithRespectToParameters(const InputPointType & /*unused*/,
                                                      JacobianType & j) const
  {
      itkExceptionMacro("ComputeJacobianWithRespectToParameters unimplemented");
  }

  /**
   * Compute the jacobian with respect to the parameters at an index.
   * Simply returns identity matrix, sized [NDimensions, NDimensions].
   * See \c ComputeJacobianWithRespectToParameters( InputPointType, ... )
   * for rationale.
   */
  virtual void ComputeJacobianWithRespectToParameters(const IndexType & /*unused*/,
                                                      JacobianType & j) const
  {
      itkExceptionMacro("ComputeJacobianWithRespectToParameters unimplemented");
  }

  /**
   * Compute the jacobian with respect to the position, by point.
   * \c j will be resized as needed.
   */
  virtual void ComputeJacobianWithRespectToPosition(const InputPointType  & x, JacobianType & j ) const;

  /**
   * Compute the jacobian with respect to the position, by point.
   * \c j will be resized as needed.
   */
  virtual void ComputeInverseJacobianWithRespectToPosition(const InputPointType  & x, JacobianType & j ) const;

  /**
   * Compute the jacobian with respect to the position, by index.
   * \c j will be resized as needed.
   */
  virtual void ComputeJacobianWithRespectToPosition(const IndexType  & x, JacobianType & j ) const;

  /**
   * Compute the inverse jacobian of the forward displacement field with
   * respect to the position, by point. Note that this is different than
   * the jacobian of the inverse displacement field. This takes advantage
   * of the ability to compute the inverse jacobian of a displacement field
   * by simply reversing the sign of the forward jacobian.
   * However, a more accurate method for computing the inverse
   * jacobian is to take the inverse of the jacobian matrix. This
   * method is more computationally expensive and may be used by
   * setting \c useSVD to true
   */
  virtual void GetInverseJacobianOfForwardFieldWithRespectToPosition(const InputPointType & point,
                                                                     JacobianType & jacobian,
                                                                     bool useSVD = false )
  const;

  /**
   * Compute the inverse jacobian of the forward displacement field with
   * respect to the position, by index.Note that this is different than
   * the jacobian of the inverse displacement field. This takes advantage
   * of the ability to compute the inverse jacobian of a displacement field
   * by simply reversing the sign of the forward jacobian.
   * However, a more accurate method for computing the inverse
   * jacobian is to take the inverse of the jacobian matrix. This
   * method is more computationally expensive and may be used by
   * setting \c useSVD to true
   */
  virtual void GetInverseJacobianOfForwardFieldWithRespectToPosition(const IndexType & index, JacobianType & jacobian,
                                                                     bool useSVD = false )
  const;

  virtual void UpdateTransformParameters( const DerivativeType & update, ScalarType factor = 1.0 );

  /** Return an inverse of this transform.
   * Note that the inverse displacement field must be set by the user. */
  bool GetInverse( Self *inverse ) const;

  /** Return an inverse of this transform.
   * Note that the inverse displacement field must be set by the user. */
  virtual InverseTransformBasePointer GetInverseTransform() const;

  /** This transform is not linear. */
  virtual TransformCategoryType GetTransformCategory() const
  {
    return TransformCategoryType::DisplacementField;
  }

  virtual NumberOfParametersType GetNumberOfLocalParameters() const
  {
    return InDimension;
  }

  itkSetMacro(NullPoint, OutputPointType);
  itkGetConstMacro(NullPoint, OutputPointType);
  itkSetMacro(UseNullPoint, bool);
  itkGetConstMacro(UseNullPoint, bool);
  itkBooleanMacro(UseNullPoint);

protected:

  GenericVectorFieldTransform();
  virtual ~GenericVectorFieldTransform();
  void PrintSelf( std::ostream& os, Indent indent ) const;

  /** The displacement field and its inverse (if it exists). */
  typename GenericVectorFieldType::Pointer      m_DisplacementField;

  /** The interpolator. */
  typename InterpolatorType::Pointer          m_Interpolator;

  /** Track when the displacement field was last set/assigned, as
   * distinct from when it may have had its contents modified. */
  ModifiedTimeType m_DisplacementFieldSetTime;

  OutputPointType m_NullPoint;
  bool m_UseNullPoint;

private:
  GenericVectorFieldTransform( const Self & ); // purposely not implemented
  void operator=( const Self & );             // purposely not implemented

  /**
   * Convenience method which reads the information from the current
   * displacement field into m_FixedParameters.
   */
  virtual void SetFixedParametersFromGenericVectorField() const;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "mapGenericVectorFieldTransform.tpp"
#endif

#endif // __itkGenericVectorFieldTransform_h
