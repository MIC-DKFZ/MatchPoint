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

  //TODO
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

  // Set up the parameters in the transform
  this->m_Transform->SetParameters(parameters);
  throw "not implemented yet";
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

  MeasureType value;
  // call the combined version
  this->GetValueAndDerivative(parameters, value, derivative);
}

} // end namespace itk

#endif
