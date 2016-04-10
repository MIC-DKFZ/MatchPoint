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
#ifndef __mapGenericVectorFieldTransform_tpp
#define __mapGenericVectorFieldTransform_tpp

#include "mapGenericVectorFieldTransform.h"
#include "itkVectorLinearInterpolateImageFunction.h"

#include "itkImageRegionIteratorWithIndex.h"
#include "vnl/algo/vnl_symmetric_eigensystem.h"
#include "vnl/algo/vnl_matrix_inverse.h"
#include "mapPointVectorCombinationPolicy.h"

namespace itk
{

/**
 * Constructor
 */
template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>::GenericVectorFieldTransform()
: Superclass( 0 )
{
  this->m_DisplacementField = ITK_NULLPTR;

  this->m_FixedParameters.SetSize( InDimensions * ( InDimensions + 3 ) );
  this->m_FixedParameters.Fill( 0.0 );

  // Setup and assign default interpolator
  typedef VectorLinearInterpolateImageFunction< GenericVectorFieldType, ScalarType> DefaultInterpolatorType;
  typename DefaultInterpolatorType::Pointer interpolator = DefaultInterpolatorType::New();
  this->m_Interpolator = interpolator;

  // Setup and assign parameter helper. This will hold the displacement field
  // for access through the common OptimizerParameters interface.
  OptimizerParametersHelperType* helper = new OptimizerParametersHelperType;
  // After assigning this, m_Parametes will manage this,
  // deleting when appropriate.
  this->m_Parameters.SetHelper( helper );

  m_DisplacementFieldSetTime = 0;

  m_UseNullPoint = false;
  m_NullPoint.Fill(::itk::NumericTraits<ScalarType>::NonpositiveMin());
}

/**
 * Destructor
 */
template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>::
~GenericVectorFieldTransform()
{
}

/**
 * Transform point
 */
template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
typename GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>::OutputPointType
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::TransformPoint( const InputPointType& inputPoint ) const
{
  if( !this->m_DisplacementField )
    {
    itkExceptionMacro( "No displacement field is specified." );
    }
  if( !this->m_Interpolator )
    {
    itkExceptionMacro( "No interpolator is specified." );
    }

  typename InterpolatorType::ContinuousIndexType cidx;
  typename InterpolatorType::PointType point;
  point.CastFrom( inputPoint );

  OutputPointType outputPoint;

  if( this->m_Interpolator->IsInsideBuffer( point ) )
    {
    this->m_DisplacementField->TransformPhysicalPointToContinuousIndex( point, cidx );
    typename InterpolatorType::OutputType displacement = this->m_Interpolator->EvaluateAtContinuousIndex( cidx );

    ::map::core::PointVectorCombinationPolicy<InDimensions, OutDimensions>::mapPoint(inputPoint, displacement, outputPoint);

    }
  else
  {
      if (this->m_UseNullPoint)
      {
          outputPoint = m_NullPoint;
      }
      else
      {
          ::map::core::PointVectorCombinationPolicy<InDimensions, OutDimensions>::mapPoint(inputPoint, outputPoint);
      }

  }

  return outputPoint;
}

/**
 * return an inverse transformation
 */
template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
bool GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::GetInverse( Self *itkNotUsed(inverse) ) const
{
    return false;
}


// Return an inverse of this transform
template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
typename GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>::InverseTransformBasePointer
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::GetInverseTransform() const
{
  return ITK_NULLPTR;
}

/*
 * ComputeJacobianWithRespectToParameters methods
 */

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::ComputeJacobianWithRespectToPosition( const InputPointType & point,
                                        JacobianType & jacobian )
const
{
    itkExceptionMacro("ComputeJacobianWithRespectToPosition unimplemented");
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::ComputeJacobianWithRespectToPosition( const IndexType & index,
                                        JacobianType & jacobian )
const
{
    itkExceptionMacro("ComputeJacobianWithRespectToPosition unimplemented");
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::ComputeInverseJacobianWithRespectToPosition( const InputPointType & point,
                                        JacobianType & jacobian )
const
{
    itkExceptionMacro("ComputeInverseJacobianWithRespectToPosition unimplemented");
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::GetInverseJacobianOfForwardFieldWithRespectToPosition(
  const InputPointType & point,
  JacobianType & jacobian,
  bool useSVD )
const
{
    itkExceptionMacro("GetInverseJacobianOfForwardFieldWithRespectToPosition unimplemented");
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::GetInverseJacobianOfForwardFieldWithRespectToPosition(
  const IndexType & index,
  JacobianType & jacobian,
  bool useSVD )
const
{
    itkExceptionMacro("GetInverseJacobianOfForwardFieldWithRespectToPosition unimplemented");
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::UpdateTransformParameters( const DerivativeType & update, ScalarType factor)
{
  // This simply adds the values.
  // TODO: This should be multi-threaded probably, via image add filter.
  Superclass::UpdateTransformParameters( update, factor );
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::SetDisplacementField( GenericVectorFieldType* field )
{
  itkDebugMacro("setting GenericVectorField to " << field);
  if( this->m_DisplacementField != field )
    {
    this->m_DisplacementField = field;

    this->Modified();
    /* Store this separately for use in smoothing because we only want
     * to know when the displacement field object has changed, not just
     * its contents. */
    this->m_DisplacementFieldSetTime = this->GetMTime();
    if( !this->m_Interpolator.IsNull() )
      {
      this->m_Interpolator->SetInputImage( this->m_DisplacementField );
      }
    // Assign to parameters object
    this->m_Parameters.SetParametersObject( this->m_DisplacementField );
    }
  this->SetFixedParametersFromGenericVectorField();
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::SetInterpolator( InterpolatorType* interpolator )
{
  itkDebugMacro("setting Interpolator to " << interpolator);
  if( this->m_Interpolator != interpolator )
    {
    this->m_Interpolator = interpolator;
    this->Modified();
    if( !this->m_DisplacementField.IsNull() )
      {
      this->m_Interpolator->SetInputImage( this->m_DisplacementField );
      }
    }
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::SetFixedParameters( const ParametersType & fixedParameters )
{
    if (fixedParameters.Size() != InDimensions * (InDimensions + 3))
    {
    itkExceptionMacro( "The fixed parameters are not the right size." );
    }

  SizeType size;
  for( unsigned int d = 0; d < InDimensions; d++ )
    {
    size[d] = static_cast<SizeValueType>( fixedParameters[d] );
    }

  PointType origin;
  for( unsigned int d = 0; d < InDimensions; d++ )
    {
    origin[d] = fixedParameters[d + InDimensions];
    }

  SpacingType spacing;
  for( unsigned int d = 0; d < InDimensions; d++ )
    {
    spacing[d] = fixedParameters[d + 2 * InDimensions];
    }

  DirectionType direction;
  for( unsigned int di = 0; di < InDimensions; di++ )
    {
    for( unsigned int dj = 0; dj < InDimensions; dj++ )
      {
      direction[di][dj] = fixedParameters[3 * InDimensions + ( di * InDimensions + dj )];
      }
    }

  PixelType zeroDisplacement;
  zeroDisplacement.Fill( 0.0 );

  typename GenericVectorFieldType::Pointer GenericVectorField = GenericVectorFieldType::New();
  GenericVectorField->SetSpacing( spacing );
  GenericVectorField->SetOrigin( origin );
  GenericVectorField->SetDirection( direction );
  GenericVectorField->SetRegions( size );
  GenericVectorField->Allocate();
  GenericVectorField->FillBuffer( zeroDisplacement );

  this->SetDisplacementField( GenericVectorField );
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::SetFixedParametersFromGenericVectorField() const
  {
  this->m_FixedParameters.SetSize( InDimensions * ( InDimensions + 3 ) );

  const typename GenericVectorFieldType::RegionType & fieldRegion =
    this->m_DisplacementField->GetLargestPossibleRegion();

  // Set the field size parameters
  SizeType fieldSize = fieldRegion.GetSize();
  for( unsigned int i = 0; i < InDimensions; i++ )
    {
    this->m_FixedParameters[i] = static_cast<ParametersValueType>( fieldSize[i] );
    }

  // Set the origin parameters
  PointType fieldOrigin = this->m_DisplacementField->GetOrigin();
  for( unsigned int i = 0; i < InDimensions; i++ )
    {
    this->m_FixedParameters[InDimensions + i] = fieldOrigin[i];
    }

  // Set the spacing parameters
  SpacingType fieldSpacing = this->m_DisplacementField->GetSpacing();
  for( unsigned int i = 0; i < InDimensions; i++ )
    {
    this->m_FixedParameters[2 * InDimensions + i] = static_cast<ParametersValueType>( fieldSpacing[i] );
    }

  // Set the direction parameters
  DirectionType fieldDirection = this->m_DisplacementField->GetDirection();
  for( unsigned int di = 0; di < InDimensions; di++ )
    {
    for( unsigned int dj = 0; dj < InDimensions; dj++ )
      {
      this->m_FixedParameters[3 * InDimensions + ( di * InDimensions + dj )] =
        static_cast<ParametersValueType>( fieldDirection[di][dj] );
      }
    }
}

template <typename TScalar, unsigned int InDimensions, unsigned int OutDimensions>
void
GenericVectorFieldTransform<TScalar, InDimensions, OutDimensions>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf( os, indent );

  std::cout << indent << "Interpolator: " << std::endl;
  std::cout << indent << indent << this->m_Interpolator << std::endl;
  std::cout << indent << "UseNullPoint: " << this->m_UseNullPoint << std::endl;
  std::cout << indent << "NullPoint: " << this->m_NullPoint << std::endl;

  if( this->m_DisplacementField )
    {
    std::cout << indent << "Displacement Field: " << std::endl;
    std::cout << indent << indent << this->m_DisplacementField << std::endl;
    }
  else
    {
    std::cout << "Displacement field not set." << std::endl;
    }
}

} // namespace itk

#endif
