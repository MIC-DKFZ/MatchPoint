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


#ifndef __MAP_ARBITRARY_WARP_IMAGE_FILTER_TXX
#define __MAP_ARBITRARY_WARP_IMAGE_FILTER_TXX

#include "mapArbitraryWarpImageFilter.h"

#include "itkImageRegionIterator.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkNumericTraits.h"
#include "itkProgressReporter.h"

namespace itk
{

  namespace map
  {

    /**
    * Default constructor.
    */
    template <class TInputImage,class TOutputImage,class TDisplacementField>
    ArbitraryWarpImageFilter<TInputImage,TOutputImage,TDisplacementField>
      ::ArbitraryWarpImageFilter()
    {
      // Setup default values
      m_UseStandardWarpFilter = false;
      m_Size.Fill(NumericTraits<typename SizeType::SizeValueType>::Zero);
      m_FieldInterpolator = FieldInterpolatorType::New();
      m_MappingErrorValue = NumericTraits<PixelType>::Zero;
      m_ThrowExceptionOnMappingError = false;
    }

    /**
    * Standard PrintSelf method.
    */
    template <class TInputImage,class TOutputImage,class TDisplacementField>
    void
      ArbitraryWarpImageFilter<TInputImage,TOutputImage,TDisplacementField>
      ::PrintSelf(std::ostream& os, Indent indent) const
    {
      Superclass::PrintSelf(os, indent);

      os << indent << "Size: " << m_Size << std::endl;;
      os << indent << "UseStandardWarpFilter: " << m_UseStandardWarpFilter << std::endl;;
      os << indent << "FieldInterpolator: " << m_FieldInterpolator.GetPointer() << std::endl;;
      os << indent << "MappingErrorValue: " << m_MappingErrorValue << std::endl;;
      os << indent << "ThrowExceptionOnMappingError: " << m_ThrowExceptionOnMappingError << std::endl;;
    }

    /**
    * Setup state of filter before multi-threading.
    * InterpolatorType::SetInputImage is not thread-safe and hence
    * has to be setup before ThreadedGenerateData
    */
    template <class TInputImage,class TOutputImage,class TDisplacementField>
    void
      ArbitraryWarpImageFilter<TInputImage,TOutputImage,TDisplacementField>
      ::BeforeThreadedGenerateData()
    {
      Superclass::BeforeThreadedGenerateData();

      m_FieldInterpolator->SetNullVector(m_NullVector);
      m_FieldInterpolator->SetNullVectorUsage(m_UseNullVector);

      // Connect field to interpolator
      m_FieldInterpolator->SetInputImage( this->GetDisplacementField() );
    }

    /**
    * Setup state of filter after multi-threading.
    */
    template <class TInputImage,class TOutputImage,class TDisplacementField>
    void
      ArbitraryWarpImageFilter<TInputImage,TOutputImage,TDisplacementField>
      ::AfterThreadedGenerateData()
    {
      Superclass::AfterThreadedGenerateData();
      // Disconnect field from interpolator
      m_FieldInterpolator->SetInputImage( NULL );
    }


    /**
    * Compute the output for the region specified by outputRegionForThread.
    */
    template <class TInputImage,class TOutputImage,class TDisplacementField>
    void
      ArbitraryWarpImageFilter<TInputImage,TOutputImage,TDisplacementField>
      ::ThreadedGenerateData(
      const OutputImageRegionType& outputRegionForThread,
      ::itk::ThreadIdType threadId )
    {
      if (m_UseStandardWarpFilter && !m_UseNullVector)
      {
        Superclass::ThreadedGenerateData(outputRegionForThread,threadId);
      }
      else
      { //Arbitrary version
        InputImageConstPointer inputPtr = this->GetInput();
        OutputImagePointer outputPtr = this->GetOutput();
        DisplacementFieldPointer fieldPtr = this->GetDisplacementField();
        InterpolatorPointer interpolatorPtr = this->GetInterpolator();

        // support progress methods/callbacks
        ProgressReporter progress(this, threadId, outputRegionForThread.GetNumberOfPixels());

        // iterator for the output image
        ImageRegionIteratorWithIndex<OutputImageType> outputIt(
          outputPtr, outputRegionForThread );


        IndexType index;
        PointType point;
        DisplacementType displacement;

        while( !outputIt.IsAtEnd() )
        {
          // get the output image index
          index = outputIt.GetIndex();
          outputPtr->TransformIndexToPhysicalPoint( index, point );

          // get the required displacement by field interpolation
          if( m_FieldInterpolator->IsInsideBuffer( point ) )
          {
            displacement = static_cast<DisplacementType>( m_FieldInterpolator->Evaluate( point ) );
            if (m_UseNullVector && displacement == m_NullVector)
            {
              if (m_ThrowExceptionOnMappingError)
              {
                itkExceptionMacro("Cannot warp image. Result space is covered by NULL vectors in deformation field.");
              }
              else
              {
                outputIt.Set( m_MappingErrorValue );
              }
            }
            else
            {
              // compute the required input image point
              for(unsigned int j = 0; j < Superclass::ImageDimension; j++ )
              {
                point[j] += displacement[j];
              }

              // get the interpolated value
              if( interpolatorPtr->IsInsideBuffer( point ) )
              {
                PixelType value = static_cast<PixelType>( 
                  interpolatorPtr->Evaluate( point ) );
                outputIt.Set( value );
              }
              else
              {
                outputIt.Set( this->GetEdgePaddingValue() );
              }   
            }
          }
          else
          {
            if (m_ThrowExceptionOnMappingError)
            {
              itkExceptionMacro("Cannot warp image. Result space is not completely covered by deformation field.");
            }
            else
            {
              outputIt.Set( m_MappingErrorValue );
            }
          }   

          ++outputIt;
          progress.CompletedPixel();
        }
      }
    }

    template <class TInputImage,class TOutputImage,class TDisplacementField>
    void
      ArbitraryWarpImageFilter<TInputImage,TOutputImage,TDisplacementField>
      ::GenerateInputRequestedRegion()
    {

      // call the superclass's superclass implementation
      Superclass::Superclass::GenerateInputRequestedRegion();

      // request the largest possible region for the input image
      InputImagePointer inputPtr = 
        const_cast< InputImageType * >( this->GetInput() );

      if( inputPtr )
      {
        inputPtr->SetRequestedRegionToLargestPossibleRegion();
      }

      // just propagate up the output requested region for the 
      // deformation field.
      DisplacementFieldPointer fieldPtr = this->GetDisplacementField();
      OutputImagePointer outputPtr = this->GetOutput();

      typename DisplacementFieldType::RegionType region(outputPtr->GetRequestedRegion());
      typename DisplacementFieldType::RegionType::IndexType index;

      if (fieldPtr->TransformPhysicalPointToIndex(outputPtr->GetOrigin(),index))
      {
        region.SetIndex(index);
      }
      region.Crop(fieldPtr->GetLargestPossibleRegion());

      if( fieldPtr )
      {
        fieldPtr->SetRequestedRegion(region);
      }

    }

    template <class TInputImage,class TOutputImage,class TDisplacementField>
    void
      ArbitraryWarpImageFilter<TInputImage,TOutputImage,TDisplacementField>
      ::GenerateOutputInformation()
    {
      // call the superclass's implementation of this method
      Superclass::GenerateOutputInformation();

      typename OutputImageType::RegionType imageRegion(m_Size);

      OutputImagePointer outputPtr = this->GetOutput();
      outputPtr->SetLargestPossibleRegion(imageRegion);

      DisplacementFieldPointer fieldPtr = this->GetDisplacementField();

      if ((imageRegion == fieldPtr->GetLargestPossibleRegion()) &&
        (outputPtr->GetSpacing() == fieldPtr->GetSpacing()) &&
        (outputPtr->GetOrigin() == fieldPtr->GetOrigin()))
      { //grid of wanted result image and deformation field are equal, thus use standard warp filter (better performance)
        m_UseStandardWarpFilter = true;
      }
      else
      { //grid of wanted result image and deformation field are not equal
        m_UseStandardWarpFilter = false;
      }
    }


  } // end namespace map
} // end namespace itk

#endif

