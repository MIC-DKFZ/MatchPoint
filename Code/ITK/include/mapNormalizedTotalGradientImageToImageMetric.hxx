/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkNormalizedTotalGradientImageToImageMetric_hxx
#define itkNormalizedTotalGradientImageToImageMetric_hxx

#include "itkCovariantVector.h"
#include "itkImageRegionIterator.h"
#include "itkImageIterator.h"
#include "itkMath.h"
#include "itkMakeUniqueForOverwrite.h"
#include "itkShapedNeighborhoodIterator.h"
#include "itkSubtractImageFilter.h"

namespace itk
{
/**
 * Constructor
 */
template <typename TFixedImage, typename TMovingImage>
NormalizedTotalGradientImageToImageMetric<TFixedImage, TMovingImage>::NormalizedTotalGradientImageToImageMetric()
{
  this->SetComputeGradient(true);

  this->m_WithinThreadPreProcess = false;
  this->m_WithinThreadPostProcess = false;

  //  For backward compatibility, the default behavior is to use all the pixels
  //  in the fixed image.
  //  This should be fixed in ITKv4 so that this metric behaves as the others.
  this->SetUseAllPixels(true);

  m_Delta = 0.00011;
}

/**
 * Print out internal information about this class
 */
template <typename TFixedImage, typename TMovingImage>
void
NormalizedTotalGradientImageToImageMetric<TFixedImage, TMovingImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

/**
 * Initialize
 */
template <typename TFixedImage, typename TMovingImage>
void
NormalizedTotalGradientImageToImageMetric<TFixedImage, TMovingImage>::Initialize()
{
  this->Superclass::Initialize();

}

template <typename TFixedImage, typename TMovingImage>
auto
NormalizedTotalGradientImageToImageMetric<TFixedImage, TMovingImage>::GetValue(const ParametersType & parameters) const
  -> MeasureType
{
  itkDebugMacro("GetValue( " << parameters << " ) ");

  if (!this->m_FixedImage)
  {
    itkExceptionMacro(<< "Fixed image has not been assigned");
  }

  if (!this->m_MovingImage)
  {
    itkExceptionMacro(<< "Moving image has not been assigned");
  }

  // Set up the parameters in the transform
  this->m_Transform->SetParameters(parameters);

  //do the computation based on Fixed and moving images
  //Mask support can be skipped for now I suppose, but should be statet if not implemented in the class docu.

  auto resampleFilter = itk::ResampleImageFilter<TMovingImage, TFixedImage>::New();
  resampleFilter->SetReferenceImage(this->m_FixedImage);
  resampleFilter->UseReferenceImageOn();
  resampleFilter->SetTransform(this->m_Transform);
  resampleFilter->SetInput(this->m_MovingImage);
  resampleFilter->Update();
  auto transformedImage = resampleFilter->GetOutput();

  using subtractFilterType = itk::SubtractImageFilter<TFixedImage, TMovingImage>;
  auto subtractFilter = subtractFilterType::New();
  subtractFilter->SetInput1(this->m_FixedImage.GetPointer());
  subtractFilter->SetInput2(transformedImage);
  subtractFilter->Update();
  auto diffImage = subtractFilter->GetOutput();

  auto dirDerTarget = CalculateDirectionalDerivativeSum(this->m_FixedImage.GetPointer());
  auto dirDerMoving = CalculateDirectionalDerivativeSum(transformedImage);
  auto dirDerDiff = CalculateDirectionalDerivativeSum(diffImage);

  return dirDerDiff / (dirDerTarget + dirDerMoving);
}


/**
 * Get the both Value and Derivative Measure
 */
template <typename TFixedImage, typename TMovingImage>
void
NormalizedTotalGradientImageToImageMetric<TFixedImage, TMovingImage>::GetValueAndDerivative(const ParametersType & parameters,
                                                                                MeasureType &          value,
                                                                                DerivativeType &       derivative) const
{
  if (!this->m_FixedImage)
  {
    itkExceptionMacro(<< "Fixed image has not been assigned");
  }

  value = this->GetValue(parameters);
  this->GetDerivative(parameters, derivative);
}

/**
 * Get the match measure derivative
 */
template <typename TFixedImage, typename TMovingImage>
void
NormalizedTotalGradientImageToImageMetric<TFixedImage, TMovingImage>::GetDerivative(const ParametersType & parameters,
                                                                        DerivativeType &       derivative) const
{
  if (!this->m_FixedImage)
  {
    itkExceptionMacro(<< "Fixed image has not been assigned");
  }

  ParametersType testPoint;

  testPoint = parameters;

  const unsigned int numberOfParameters = this->GetNumberOfParameters();
  derivative = DerivativeType(numberOfParameters);
  for (unsigned int i = 0; i < numberOfParameters; ++i)
  {
    testPoint[i] -= m_Delta;
    const MeasureType valuep0 = this->GetValue(testPoint);
    testPoint[i] += 2 * m_Delta;
    const MeasureType valuep1 = this->GetValue(testPoint);
    derivative[i] = (valuep1 - valuep0) / (2 * m_Delta);
    testPoint[i] = parameters[i];
  }
}

} // end namespace itk

template <typename TImage>
double CalculateDirectionalDerivativeSum(const TImage* image)
{
  using ImageType = TImage;
  using IteratorType = itk::ConstShapedNeighborhoodIterator<ImageType>;
  IteratorType::RadiusType radius;
  radius.Fill(1);
  IteratorType iterator(radius, image, image->GetLargestPossibleRegion());
  IteratorType::OffsetType top, bottom, left, right;
  top    = { { 0,-1} };
  bottom = { { 0, 1} };
  left   = { {-1, 0} };
  right  = { { 1, 0} };
  iterator.ActivateOffset(top);
  iterator.ActivateOffset(bottom);
  iterator.ActivateOffset(left);
  iterator.ActivateOffset(right);
  double sum = 0;
  auto regionSize = image->GetLargestPossibleRegion().GetSize();

  for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
  {
    auto centerIndex = iterator.GetIndex();
    if (centerIndex[0] > 0 && centerIndex[0] < regionSize[0] - 1 && centerIndex[1] > 0 && centerIndex[1] < regionSize[1] - 1)
    {
      auto centerVal = *(iterator.GetElement(0));
      IteratorType::ConstIterator localIterator = iterator.Begin();

      while (!localIterator.IsAtEnd())
      {
        sum += abs(centerVal - localIterator.Get());
        ++localIterator;
      }
    }
  }

  // iterate over diagonal neighbors separately to include /SQRT2 factor
  IteratorType::OffsetType topLeft, topRight, bottomLeft, bottomRight;
  topLeft     = { {-1,-1} };
  topRight    = { { 1, 1} };
  bottomLeft  = { {-1, 1} };
  bottomRight = { { 1, 1} };
  iterator.ActivateOffset(topLeft);
  iterator.ActivateOffset(topRight);
  iterator.ActivateOffset(bottomLeft);
  iterator.ActivateOffset(bottomRight);

  const double SQRT2 = sqrt(2);
  for (iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator)
  {
    auto centerIndex = iterator.GetIndex();
    if (centerIndex[0] > 0 && centerIndex[0] < regionSize[0] - 1 && centerIndex[1] > 0 && centerIndex[1] < regionSize[1] - 1)
    {
      auto centerVal = *(iterator.GetElement(0));
      IteratorType::ConstIterator localIterator = iterator.Begin();

      while (!localIterator.IsAtEnd())
      {
        sum += abs(centerVal - localIterator.Get()) / SQRT2;
        ++localIterator;
      }
    }
  }

  return sum;
}

#endif
