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
#ifndef __itkMatrixOffsetBasedTranslationTransform_hxx
#define __itkMatrixOffsetBasedTranslationTransform_hxx

#include "itkNumericTraits.h"
#include "itkMatrixOffsetBasedTranslationTransform.h"
#include "vnl/algo/vnl_matrix_inverse.h"

namespace itk
{
  /** Constructor with default arguments */
  template< typename TScalar, unsigned int NDimensions >
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::MatrixOffsetBasedTranslationTransform()
    : Superclass(ParametersDimension), m_IdentityJacobian(NDimensions, NDimensions)
  {
    // The Jacobian of this transform is constant.
    // Therefore the m_IdentityJacobian variable can be
    // initialized here and be shared among all the threads.
    this->m_IdentityJacobian.Fill(0.0);

    for (unsigned int i = 0; i < NDimensions; i++)
    {
      this->m_IdentityJacobian(i, i) = 1.0;
    }
  }

  /** Constructor with default arguments */
  template< typename TScalar, unsigned int NDimensions >
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::MatrixOffsetBasedTranslationTransform(
    unsigned int parametersDimension):
    Superclass(parametersDimension), m_IdentityJacobian(NDimensions, NDimensions)
  {
    // The Jacobian of this transform is constant.
    // Therefore the m_IdentityJacobian variable can be
    // initialized here and be shared among all the threads.
    this->m_IdentityJacobian.Fill(0.0);

    for (unsigned int i = 0; i < NDimensions; i++)
    {
      this->m_IdentityJacobian(i, i) = 1.0;
    }
  }

  /** Constructor with explicit arguments */
  template< typename TScalar, unsigned int NDimensions >
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::MatrixOffsetBasedTranslationTransform(
    const MatrixType& matrix,
    const OutputVectorType& offset):
    Superclass(matrix, offset), m_IdentityJacobian(NDimensions, NDimensions)
  {
    // The Jacobian of this transform is constant.
    // Therefore the m_IdentityJacobian variable can be
    // initialized here and be shared among all the threads.
    this->m_IdentityJacobian.Fill(0.0);

    for (unsigned int i = 0; i < NDimensions; i++)
    {
      this->m_IdentityJacobian(i, i) = 1.0;
    }
  }

  /**  Destructor */
  template< typename TScalar, unsigned int NDimensions >
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::
  ~MatrixOffsetBasedTranslationTransform()
  {
  }

  /** Print self */
  template< typename TScalar, unsigned int NDimensions >
  void
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::PrintSelf(std::ostream& os,
      Indent indent) const
  {
    Superclass::PrintSelf(os, indent);
  }


  /** Get an inverse of this transform. */
  template< typename TScalar, unsigned int NDimensions >
  bool
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >
  ::GetInverse(Self* inverse) const
  {
    return this->Superclass::GetInverse(inverse);
  }

  /** Return an inverse of this transform. */
  template< typename TScalar, unsigned int NDimensions >
  typename MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::InverseTransformBasePointer
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >
  ::GetInverseTransform() const
  {
    Pointer inv = New();

    return this->GetInverse(inv) ? inv.GetPointer() : ITK_NULLPTR;
  }

  // Set parameters
  template< typename TScalar, unsigned int NDimensions >
  void
  MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >
  ::SetParameters(const ParametersType& parameters)
  {
    if (parameters.Size() < NDimensions)
    {
      itkExceptionMacro
      ( << "Error setting parameters: parameters array size ("
        << parameters.Size() << ") is less than expected "
        << " (NDimensions) "
        << " (" << NDimensions << ")"
      );
    }

    // Save parameters. Needed for proper operation of TransformUpdateParameters.
    if (&parameters != &(this->m_Parameters))
    {
      this->m_Parameters = parameters;
    }

    // Transfer the constant part
    OutputVectorType trans;

    for (unsigned int i = 0; i < NDimensions; i++)
    {
      trans[i] = this->m_Parameters[i];
    }

    this->SetVarTranslation(trans);

    this->ComputeOffset();

    // Modified is always called since we just have a pointer to the
    // parameters and cannot know if the parameters have changed.
    this->Modified();
  }

  // Get parameters
  template< typename TScalar, unsigned int NDimensions >
  const typename MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >::ParametersType
  & MatrixOffsetBasedTranslationTransform< TScalar, NDimensions >
  ::GetParameters() const
  {
    // Transfer the constant part

    OutputVectorType trans = this->GetTranslation();

    for (unsigned int i = 0; i < NDimensions; i++)
    {
      this->m_Parameters[i] = trans[i];
    }

    return this->m_Parameters;
  }

  template <typename ScalarType, unsigned int NDimensions>
  const typename MatrixOffsetBasedTranslationTransform<ScalarType, NDimensions>::ParametersType
  & MatrixOffsetBasedTranslationTransform<ScalarType, NDimensions>
  ::GetFixedParameters(void) const
  {
    this->m_FixedParameters.SetSize(0);
    return this->m_FixedParameters;
  }

  // Compute the Jacobian of the transformation
  // It follows the same order of Parameters vector
  template <typename ScalarType, unsigned int NDimensions>
  void
  MatrixOffsetBasedTranslationTransform<ScalarType, NDimensions>
  ::ComputeJacobianWithRespectToParameters(const InputPointType& p, JacobianType& j) const
  {
    // the Jacobian is constant for this transform, and it has already been
    // initialized in the constructor, so we just need to return it here.
    j = this->m_IdentityJacobian;
  }

  // Compute the Jacobian of the transformation with respect to position
  template <typename ScalarType, unsigned int NDimensions>
  void
  MatrixOffsetBasedTranslationTransform<ScalarType, NDimensions>
  ::ComputeJacobianWithRespectToPosition(const InputPointType&,
                                         JacobianType& jac) const
  {
    // the Jacobian is constant for this transform, and it has already been
    // initialized in the constructor, so we just need to return it here.
    jac = this->m_IdentityJacobian;
  }


} // namespace

#endif
