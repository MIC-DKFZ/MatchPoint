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
// @version $Revision: 4910 $ (last changed revision)
// @date    $Date: 2013-07-30 14:08:21 +0200 (Di, 30 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/ITK/include/mapIterativeInverseTransformToDisplacementFieldSource.txx $
*/

#ifndef __MAP_ITERATIVE_INVERSE_DEFORMATION_FIELD_SOURCE_TXX
#define __MAP_ITERATIVE_INVERSE_DEFORMATION_FIELD_SOURCE_TXX

#include "mapIterativeInverseTransformToDisplacementFieldSource.h"
#include "itkProgressReporter.h"


namespace itk
{
  namespace map
  {

    //----------------------------------------------------------------------------
    // Constructor
    template <class TOutputImage, typename TTransformScalarType  >
    IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::IterativeInverseTransformToDisplacementFieldSource(){
        m_NumberOfIterations = 5;
        m_StopValue = 0;
        m_Time = 0;
        m_Transform = NULL;

        //Initial image is 64 wide in each direction.
        m_Size.Fill(64);
        m_Spacing.Fill(1.0);
        m_Origin.Fill(0.0);
        m_Direction.SetIdentity();
    }


    //----------------------------------------------------------------------------
     template <class TOutputImage, typename TTransformScalarType  >
    void 
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::SetTransform(const TransformType* transform)
    {
      if (transform != m_Transform.GetPointer())
      {
        m_Transform = transform;
        this->Modified();
      }
    };

    template <class TOutputImage, typename TTransformScalarType  >
    const typename IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>::TransformType*  
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::GetTransform(void) const
    {
      return m_Transform;
    };

    template <class TOutputImage, typename TTransformScalarType  >
    void 
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::SetOrigin(const OutputImagePointType& origin)
    {
      unsigned int i; 
      for (i=0; i<TOutputImage::ImageDimension; i++)
      {
        if ( (double)origin[i] != m_Origin[i] )
        {
          break;
        }
      } 
      if ( i < TOutputImage::ImageDimension ) 
      { 
        for (i=0; i<TOutputImage::ImageDimension; i++)
        {
          m_Origin[i] = origin[i];
        }
        this->Modified();
      }
    }

    template <class TOutputImage, typename TTransformScalarType  >
    void 
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::SetSpacing(const OutputImageSpacingType& spacing )
    {
      unsigned int i; 
      for (i=0; i<TOutputImage::ImageDimension; i++)
      {
        if ( (double)spacing[i] != m_Spacing[i] )
        {
          break;
        }
      } 
      if ( i < TOutputImage::ImageDimension ) 
      { 
        for (i=0; i<TOutputImage::ImageDimension; i++)
        {
          m_Spacing[i] = spacing[i];
        }
        this->Modified();
      }
    }

    template <class TOutputImage, typename TTransformScalarType  >
    void 
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::SetSize(const OutputImageSizeType& size)
    {
      unsigned int i; 
      for (i=0; i<TOutputImage::ImageDimension; i++)
      {
        if ( size[i] != m_Size[i] )
        {
          break;
        }
      } 
      if ( i < TOutputImage::ImageDimension ) 
      { 
        for (i=0; i<TOutputImage::ImageDimension; i++)
        {
          m_Size[i] = size[i];
        }
        this->Modified();
      }
    }

    template <class TOutputImage, typename TTransformScalarType  >
    void 
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::SetDirection(const OutputImageDirectionType& direction)
    {
      if ( direction != m_Direction ) 
      { 
        m_Direction = direction;
        this->Modified();
      }
    }

    //----------------------------------------------------------------------------
    template <class TOutputImage, typename TTransformScalarType  >
    void
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::GenerateData(){

        const unsigned int ImageDimension = OutputImageType::ImageDimension;
        TimeType time;
        time.Start(); //time measurement

        OutputImagePointer outputPtr = this->GetOutput(0);

        // some checks
        if (m_Transform.IsNull())
        {
          itkExceptionMacro("\n Transform is missing.");
        }

        OutputImageRegionType outputRegion(m_Size);

        // calculate a first guess
        // (calculate negative deformation field and apply it to itself)
        OutputImagePointer negField = OutputImageType::New();
        negField->SetRegions(outputRegion);
        negField->SetSpacing(m_Spacing);
        negField->SetOrigin(m_Origin);
        negField->SetDirection(m_Direction);
        negField->Allocate();

        OutputIterator negImageIt = OutputIterator(negField, outputRegion);

        for (negImageIt.GoToBegin(); !negImageIt.IsAtEnd(); ++negImageIt)
        {
          OutputImagePointType point;
          outputPtr->TransformIndexToPhysicalPoint(negImageIt.GetIndex(),point);
          OutputImagePointType transformedPoint = m_Transform->TransformPoint(point);
          OutputImagePixelType vector = transformedPoint - point;

          negImageIt.Set( vector*-1 );
        }

        outputPtr->SetRegions(outputRegion);
        outputPtr->SetSpacing(m_Spacing);
        outputPtr->SetOrigin(m_Origin);
        outputPtr->SetDirection(m_Direction);
        outputPtr->Allocate();

        typename VectorWarperType::Pointer vectorWarper = VectorWarperType::New();
        typename FieldInterpolatorType::Pointer VectorInterpolator = FieldInterpolatorType::New();
        vectorWarper->SetInput(negField);
        vectorWarper->SetInterpolator(VectorInterpolator);
        vectorWarper->SetOutputSpacing(m_Spacing);
        vectorWarper->SetOutputOrigin(m_Origin);
        vectorWarper->SetOutputDirection(m_Direction);
        vectorWarper->SetDisplacementField(negField);
        vectorWarper->GraftOutput(outputPtr);
        vectorWarper->UpdateLargestPossibleRegion();

        // If the number of iterations is zero, just output the first guess
        // (negative deformable field applied to itself)
        if(m_NumberOfIterations == 0)
        {
          this->GraftOutput( vectorWarper->GetOutput() );
        }
        else
        {

          // calculate the inverted field
          OutputImagePointType mappedPoint, newPoint;
          OutputImagePointType point, originalPoint, backMappedPoint;
          OutputImageIndexType index;
          OutputImagePixelType displacement, outputValue;
          double spacing = m_Spacing[0];
          double smallestError = 0;
          int stillSamePoint;
          unsigned int numberOfPoints = 1;
          for ( unsigned int i=0; i<ImageDimension; i++ )
          {
            numberOfPoints *= outputRegion.GetSize()[i];
          }

          ProgressReporter progress(this, 0,
            m_NumberOfIterations *
            outputRegion.GetNumberOfPixels());
          OutputIterator OutputIt = OutputIterator(outputPtr, outputPtr->GetRequestedRegion());

          OutputIt.GoToBegin();
          while( !OutputIt.IsAtEnd() )
          {
            // get the output image index
            index = OutputIt.GetIndex();
            outputPtr->TransformIndexToPhysicalPoint( index, originalPoint );

            stillSamePoint = 0;
            double step = spacing;

            // get the required displacement
            displacement = OutputIt.Get();

            // compute the required input image point
            for(unsigned int j = 0; j < ImageDimension; j++ )
            {
              mappedPoint[j] = originalPoint[j] + displacement[j];
              newPoint[j] = mappedPoint[j];
            }

            // calculate the error of the last iteration
            backMappedPoint =  m_Transform->TransformPoint( mappedPoint );

            smallestError = 0;
            for(unsigned int j = 0; j < ImageDimension; j++ )
            {
              smallestError += vcl_pow(backMappedPoint[j]-originalPoint[j],2);
            }
            smallestError = vcl_sqrt(smallestError);

            // iteration loop
            for (unsigned int i=0; i<m_NumberOfIterations; i++)
            {
              double tmp;

              if( stillSamePoint )
              {
                step = step/2;
              }

              for(unsigned int k=0; k<ImageDimension; k++)
              {
                mappedPoint[k] += step;

                backMappedPoint =  m_Transform->TransformPoint( mappedPoint );
                //forwardVector = inputFieldInterpolator->Evaluate( mappedPoint );
                tmp = 0;
                for (unsigned int l=0; l<ImageDimension; l++)
                {
                  tmp += vcl_pow(backMappedPoint[l] - originalPoint[l], 2);
                }
                tmp = vcl_sqrt(tmp);
                if(tmp < smallestError)
                {
                  smallestError = tmp;
                  for(unsigned int l=0; l<ImageDimension; l++)
                  {
                    newPoint[l] = mappedPoint[l];
                  }
                }

                mappedPoint[k] -= 2*step;

                backMappedPoint =  m_Transform->TransformPoint( mappedPoint );
                //forwardVector = inputFieldInterpolator->Evaluate( mappedPoint );
                tmp = 0;
                for (unsigned int l=0; l<ImageDimension; l++)
                {
                  tmp += vcl_pow(backMappedPoint[l] - originalPoint[l], 2);
                }
                tmp = vcl_sqrt(tmp);
                if(tmp < smallestError)
                {
                  smallestError = tmp;
                  for(unsigned int l=0; l<ImageDimension; l++)
                  {
                    newPoint[l] = mappedPoint[l];
                  }
                }

                mappedPoint[k] += step;
              }//end for loop over image dimension


              stillSamePoint = 1;
              for(unsigned int j = 0; j < ImageDimension; j++ )
              {
                if(newPoint[j] != mappedPoint[j])
                {
                  stillSamePoint = 0;
                }
                mappedPoint[j] = newPoint[j];
              }

              if(smallestError < m_StopValue)
              {
                break;
              }

            } //end iteration loop


            for( unsigned int k = 0; k < ImageDimension; k++ )
            {
              outputValue[k] = static_cast<OutputImageValueType>( mappedPoint[k]-originalPoint[k] );
            }

            OutputIt.Set( outputValue );

            ++OutputIt;

            progress.CompletedPixel();
          } //end while loop
        }//end else

        time.Stop();
        m_Time = time.GetMean();

    }

    //----------------------------------------------------------------------------
    template <class TOutputImage, typename TTransformScalarType  >
    void
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::GenerateOutputInformation()
    {
      TOutputImage *output;
      output = this->GetOutput(0);

      typename TOutputImage::RegionType largestPossibleRegion(m_Size);
      output->SetLargestPossibleRegion( largestPossibleRegion );

      output->SetSpacing(m_Spacing);
      output->SetOrigin(m_Origin);
      output->SetDirection(m_Direction);
    }

    //----------------------------------------------------------------------------
    template <class TOutputImage, typename TTransformScalarType  >
    void
      IterativeInverseTransformToDisplacementFieldSource<TOutputImage, TTransformScalarType>
      ::PrintSelf(std::ostream& os, Indent indent) const {

        Superclass::PrintSelf(os,indent);

        os << indent << "Number of iterations: " << m_NumberOfIterations << std::endl;
        os << indent << "Stop value:           " << m_StopValue << " mm" << std::endl;
        os << indent << "Elapsed time:         " << m_Time << " sec" << std::endl;
        os << indent << "Output spacing:       " << m_Spacing << std::endl;
        os << indent << "Output size:          " << m_Size << std::endl;
        os << indent << "Output origin:        " << m_Origin << std::endl;
        os << indent << "Output direction:     " << m_Direction << std::endl;
        os << indent << "Transform:            " << m_Transform << std::endl;
        os << std::endl;
    }

  } // end namespace map 
} // end namespace itk

#endif
