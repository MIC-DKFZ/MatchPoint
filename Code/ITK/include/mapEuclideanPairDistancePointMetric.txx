/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkEuclideanPairDistancePointMetric.txx,v $
  Language:  C++
  Date:      $Date: 2013-07-30 14:08:21 +0200 (Di, 30 Jul 2013) $
  Version:   $Revision: 4910 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkEuclideanPairDistancePointMetric_txx
#define __itkEuclideanPairDistancePointMetric_txx

#include "mapEuclideanPairDistancePointMetric.h"
#include "itkImageRegionConstIteratorWithIndex.h"

namespace itk
{

/** Constructor */
template <class TFixedPointSet, class TMovingPointSet, class TDistanceMap> 
EuclideanPairDistancePointMetric<TFixedPointSet,TMovingPointSet,TDistanceMap>
::EuclideanPairDistancePointMetric()
{
  m_DistanceMap = 0;
  
  // when set to true it will be a bit faster, but it will result in minimizing
  // the sum of distances^4 instead of the sum of distances^2
  m_ComputeSquaredDistance = false; 
}

/** Return the number of values, i.e the number of points in the moving set */
template <class TFixedPointSet, class TMovingPointSet, class TDistanceMap>  
unsigned int
EuclideanPairDistancePointMetric<TFixedPointSet,TMovingPointSet,TDistanceMap>  
::GetNumberOfValues() const
{
  MovingPointSetConstPointer movingPointSet = this->GetMovingPointSet();

  if( !movingPointSet ) 
    {
    itkExceptionMacro( << "Moving point set has not been assigned" );
    }

  return  movingPointSet->GetPoints()->Size();
}


/** Get the match Measure */
template <class TFixedPointSet, class TMovingPointSet, class TDistanceMap>  
typename EuclideanPairDistancePointMetric<TFixedPointSet,TMovingPointSet,TDistanceMap>::MeasureType
EuclideanPairDistancePointMetric<TFixedPointSet,TMovingPointSet,TDistanceMap>
::GetValue( const TransformParametersType & parameters ) const
{
  FixedPointSetConstPointer fixedPointSet = this->GetFixedPointSet();

  if( !fixedPointSet ) 
    {
    itkExceptionMacro( << "Fixed point set has not been assigned" );
    }

  
  MovingPointSetConstPointer movingPointSet = this->GetMovingPointSet();

  if( !movingPointSet ) 
    {
    itkExceptionMacro( << "Moving point set has not been assigned" );
    }

  PointIterator pointItr = movingPointSet->GetPoints()->Begin();
  PointIterator pointEnd = movingPointSet->GetPoints()->End();

  PointIterator pointItr2 = fixedPointSet->GetPoints()->Begin();
  PointIterator pointEnd2 = fixedPointSet->GetPoints()->End();

  MeasureType measure;
  measure.set_size(movingPointSet->GetPoints()->Size());

  this->SetTransformParameters( parameters );

  unsigned int identifier = 0;
  while( pointItr != pointEnd && pointItr2 != pointEnd2)
    {
    
    typename Superclass::InputPointType  inputPoint;
    inputPoint.CastFrom( pointItr.Value() );
    typename Superclass::OutputPointType transformedPoint = this->m_Transform->TransformPoint( inputPoint );

    double dist = pointItr2.Value().SquaredEuclideanDistanceTo(transformedPoint);

        if(!m_ComputeSquaredDistance)
          {
          dist = vcl_sqrt(dist);
          }

    ++pointItr2;

    measure.put(identifier,dist);

    ++pointItr;
    identifier++;
    }

  return measure;

}

/** Get the Derivative Measure */
template <class TFixedPointSet, class TMovingPointSet, class TDistanceMap>
void
EuclideanPairDistancePointMetric<TFixedPointSet,TMovingPointSet,TDistanceMap>
::GetDerivative( const TransformParametersType & itkNotUsed(parameters),
                 DerivativeType & itkNotUsed(derivative) ) const
{

}

/** Get both the match Measure and theDerivative Measure  */
template <class TFixedPointSet, class TMovingPointSet, class TDistanceMap>  
void
EuclideanPairDistancePointMetric<TFixedPointSet,TMovingPointSet,TDistanceMap>
::GetValueAndDerivative(const TransformParametersType & parameters, 
                        MeasureType & value, DerivativeType  & derivative) const
{
  value = this->GetValue(parameters);
  this->GetDerivative(parameters,derivative);
}

/** PrintSelf method */
template <class TFixedPointSet, class TMovingPointSet, class TDistanceMap>  
void
EuclideanPairDistancePointMetric<TFixedPointSet,TMovingPointSet,TDistanceMap>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
  os << indent << "DistanceMap: " << m_DistanceMap << std::endl;
  if(m_ComputeSquaredDistance)
    {
    os << indent << "m_ComputeSquaredDistance: True"<< std::endl;
    }
  else
    {
    os << indent << "m_ComputeSquaredDistance: False"<< std::endl;
    }
}

} // end namespace itk


#endif
