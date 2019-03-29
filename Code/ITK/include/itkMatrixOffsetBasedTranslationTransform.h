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
#ifndef __itkMatrixOffsetBasedTranslationTransform_h
#define __itkMatrixOffsetBasedTranslationTransform_h

#include "itkMatrixOffsetTransformBase.h"
#include <iostream>


namespace itk
{
  /**
   * Translation transformation of a vector space (e.g. space coordinates)
   *
   * This class allows the definition and manipulation of translation
   * transformations of an n-dimensional affine space (and its
   * associated vector space) onto itself.  One common use is to define
   * and manipulate Euclidean coordinate transformations in two and
   * three dimensions, but other uses are possible as well.
   *
   * This class serves the same purpose then itk::TranslationTransform.
   * But it is derived from MatrixOffsetTransformBase and can therfore
   * used wherever derived classes are assumed (e.g. itk::CenteredTransformInitializer)
   *
   * \ingroup ITKTransform
   */

  template <
    typename TScalar = double,      // Data type for scalars
    //    (e.g. float or double)
    unsigned int NDimensions = 3 >
  // Number of dimensions in the input space
  class MatrixOffsetBasedTranslationTransform:
    public MatrixOffsetTransformBase< TScalar, NDimensions, NDimensions >
  {
  public:
    /** Standard typedefs   */
    using Self = MatrixOffsetBasedTranslationTransform<TScalar, NDimensions>;
    typedef MatrixOffsetTransformBase< TScalar,
            NDimensions,
            NDimensions >  Superclass;

    using Pointer = SmartPointer<Self>;
    using ConstPointer = SmartPointer<const Self>;

    /** Run-time type information (and related methods).   */
    itkTypeMacro(MatrixOffsetBasedTranslationTransform, MatrixOffsetTransformBase);

    /** New macro for creation of through a Smart Pointer   */
    itkNewMacro(Self);

    /** Dimension of the domain space. */
    itkStaticConstMacro(InputSpaceDimension, unsigned int, NDimensions);
    itkStaticConstMacro(OutputSpaceDimension, unsigned int, NDimensions);
    itkStaticConstMacro(SpaceDimension, unsigned int, NDimensions);
    itkStaticConstMacro(ParametersDimension, unsigned int, NDimensions);

    /** Parameters Type   */
    using ParametersType = typename Superclass::ParametersType;
    using JacobianType = typename Superclass::JacobianType;
    using ScalarType = typename Superclass::ScalarType;
    using InputPointType = typename Superclass::InputPointType;
    using OutputPointType = typename Superclass::OutputPointType;
    using InputVectorType = typename Superclass::InputVectorType;
    using OutputVectorType = typename Superclass::OutputVectorType;
    using InputVnlVectorType = typename Superclass::InputVnlVectorType;
    using OutputVnlVectorType = typename Superclass::OutputVnlVectorType;
    using InputCovariantVectorType = typename Superclass::InputCovariantVectorType;
    using OutputCovariantVectorType = typename Superclass::OutputCovariantVectorType;
    using MatrixType = typename Superclass::MatrixType;
    using InverseMatrixType = typename Superclass::InverseMatrixType;
    using CenterType = typename Superclass::CenterType;
    using OffsetType = typename Superclass::OffsetType;
    using TranslationType = typename Superclass::TranslationType;

    /** Base inverse transform type. This type should not be changed to the
     * concrete inverse transform type or inheritance would be lost.*/
    using InverseTransformBaseType = typename Superclass::InverseTransformBaseType;
    using InverseTransformBasePointer = typename InverseTransformBaseType::Pointer;

    /** Compose affine transformation with a translation
     *
     * This method modifies self to include a translation of the
     * origin.  The translation is precomposed with self if pre is
     * true, and postcomposed otherwise.
     * This updates Translation based on current center. */
    void Translate(const OutputVectorType& offset, bool pre = 0);

    /** Get an inverse of this transform. */
    bool GetInverse(Self* inverse) const;

    /** Return an inverse of this transform. */
    virtual InverseTransformBasePointer GetInverseTransform() const;

    /** Back transform by an affine transformation
     *
     * This method finds the point or vector that maps to a given
     * point or vector under the affine transformation defined by
     * self.  If no such point exists, an exception is thrown.
     *
     * \deprecated Please use GetInverseTransform and then call the
     *   forward transform function */
    itkLegacyMacro(InputPointType   BackTransform(const OutputPointType&   point) const);
    itkLegacyMacro(InputVectorType  BackTransform(const OutputVectorType& vector) const);
    itkLegacyMacro(InputVnlVectorType BackTransform(const OutputVnlVectorType& vector) const);
    itkLegacyMacro(InputCovariantVectorType BackTransform(const OutputCovariantVectorType& vector)
                   const);

    /** Back transform a point by an affine transform
     *
     * This method finds the point that maps to a given point under
     * the affine transformation defined by self.  If no such point
     * exists, an exception is thrown.  The returned value is (a
     * pointer to) a brand new point created with new.
     *
     * \deprecated Please use GetInverseTransform and then call the
     *   forward transform function */
    itkLegacyMacro(InputPointType BackTransformPoint(const OutputPointType&   point) const);

    virtual const ParametersType& GetParameters() const;
    virtual void SetParameters(const ParametersType& parameters);

    /** Set the fixed parameters and update internal
    * transformation. This transform has no fixed paramaters
    */
    virtual void SetFixedParameters(const ParametersType& /*unused*/)
    {
    }

    /** Get the fixed parameters */
    virtual const ParametersType& GetFixedParameters() const;

    /** Get the Jacobian matrix. */
    virtual void ComputeJacobianWithRespectToParameters(const InputPointType& point,
        JacobianType& j) const;

    /** Get the jacobian with respect to position, which simply is the
    *  matrix because the transform is position-invariant.
    *  jac will be resized as needed, but it will be more efficient if
    *  it is already properly sized. */
    virtual void ComputeJacobianWithRespectToPosition(const InputPointType&   x,
        JacobianType& jac) const;

  protected:
    /** Construct an MatrixOffsetBasedTranslationTransform object
     *
     * This method constructs a new MatrixOffsetBasedTranslationTransform object and
     * initializes the matrix and offset parts of the transformation
     * to values specified by the caller.  If the arguments are
     * omitted, then the MatrixOffsetBasedTranslationTransform is initialized to an identity
     * transformation in the appropriate number of dimensions.   */
    MatrixOffsetBasedTranslationTransform(const MatrixType& matrix,
                                          const OutputVectorType& offset);
    MatrixOffsetBasedTranslationTransform(unsigned int paramDims);
    MatrixOffsetBasedTranslationTransform();

    /** Destroy an MatrixOffsetBasedTranslationTransform object   */
    virtual ~MatrixOffsetBasedTranslationTransform();

    /** Print contents of an MatrixOffsetBasedTranslationTransform */
    void PrintSelf(std::ostream& s, Indent indent) const;

  private:
    JacobianType     m_IdentityJacobian;

    MatrixOffsetBasedTranslationTransform(const Self& other);
    const Self& operator=(const Self&);
  }; //class MatrixOffsetBasedTranslationTransform

  #if !defined(ITK_LEGACY_REMOVE)
  /** Back transform a vector */
  template< typename TScalar, unsigned int NDimensions >
  inline
  typename MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::InputVectorType
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::BackTransform(
    const OutputVectorType& vect) const
  {
    itkWarningMacro(
      << "BackTransform(): This method is slated to be removed "
      << "from ITK. Instead, please use GetInverse() to generate an inverse "
      << "transform and then perform the transform using that inverted transform.");
    return this->GetInverseMatrix() * vect;
  }

  /** Back transform a vnl_vector */
  template< typename TScalar, unsigned int NDimensions >
  inline
  typename MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::InputVnlVectorType
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::BackTransform(
    const OutputVnlVectorType& vect) const
  {
    itkWarningMacro(
      << "BackTransform(): This method is slated to be removed "
      << "from ITK. Instead, please use GetInverse() to generate an inverse "
      << "transform and then perform the transform using that inverted transform.");
    return this->GetInverseMatrix() * vect;
  }

  /** Back Transform a CovariantVector */
  template< typename TScalar, unsigned int NDimensions >
  inline
  typename MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::InputCovariantVectorType
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::BackTransform(
    const OutputCovariantVectorType& vec) const
  {
    itkWarningMacro(
      << "BackTransform(): This method is slated to be removed "
      << "from ITK. Instead, please use GetInverse() to generate an inverse "
      << "transform and then perform the transform using that inverted transform.");

    InputCovariantVectorType result;    // Converted vector

    for (unsigned int i = 0; i < NDimensions; i++)
    {
      result[i] = NumericTraits< ScalarType >::Zero;

      for (unsigned int j = 0; j < NDimensions; j++)
      {
        result[i] += this->GetMatrix()[j][i] * vec[j]; // Direct matrix transposed
      }
    }

    return result;
  }

  /** Back transform a given point which is represented as type PointType */
  template< typename TScalar, unsigned int NDimensions >
  inline
  typename MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::InputPointType
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::BackTransformPoint(
    const OutputPointType& point) const
  {
    return this->BackTransform(point);
  }

  /** Back transform a point */
  template< typename TScalar, unsigned int NDimensions >
  inline
  typename MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::InputPointType
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::BackTransform(
    const OutputPointType& point) const
  {
    itkWarningMacro(
      << "BackTransform(): This method is slated to be removed "
      << "from ITK.  Instead, please use GetInverse() to generate an inverse "
      << "transform and then perform the transform using that inverted transform.");
    InputPointType result;       // Converted point
    ScalarType     temp[NDimensions];
    unsigned int   i, j;

    for (j = 0; j < NDimensions; j++)
    {
      temp[j] = point[j] - this->GetOffset()[j];
    }

    for (i = 0; i < NDimensions; i++)
    {
      result[i] = 0.0;

      for (j = 0; j < NDimensions; j++)
      {
        result[i] += this->GetInverseMatrix()[i][j] * temp[j];
      }
    }

    return result;
  }
  #endif
}  // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMatrixOffsetBasedTranslationTransform.hxx"
#endif

#endif /* __itkMatrixOffsetBasedTranslationTransform_h */
