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

#ifndef __NULL_VECTOR_AWARE_LINEAR_INTERPOLATE_IMAGE_FUNCTION_TPP
#define __NULL_VECTOR_AWARE_LINEAR_INTERPOLATE_IMAGE_FUNCTION_TPP

#include "mapNULLVectorAwareLinearInterpolateImageFunction.h"
#include "itkNumericTraits.h"

#include "vnl/vnl_math.h"

namespace itk
{
	namespace map
	{

		/**
		* Define the number of neighbors
		*/
		template<class TInputImage, class TCoordRep>
		const unsigned long
		NULLVectorAwareLinearInterpolateImageFunction< TInputImage, TCoordRep >
		::m_Neighbors = 1 << TInputImage::ImageDimension;


		/**
		* Constructor
		*/
		template<class TInputImage, class TCoordRep>
		NULLVectorAwareLinearInterpolateImageFunction< TInputImage, TCoordRep >
		::NULLVectorAwareLinearInterpolateImageFunction() : _useNullVector(true),
			 _nullVector(::itk::NumericTraits<typename OutputType::ValueType>::NonpositiveMin())
		{

		}


		/**
		* PrintSelf
		*/
		template<class TInputImage, class TCoordRep>
		void
		NULLVectorAwareLinearInterpolateImageFunction< TInputImage, TCoordRep >
		::PrintSelf(std::ostream& os, Indent indent) const
		{
			this->Superclass::PrintSelf(os, indent);
		}


		/**
		* Evaluate at image index position
		*/
		template<class TInputImage, class TCoordRep>
		typename NULLVectorAwareLinearInterpolateImageFunction< TInputImage, TCoordRep >
		::OutputType
		NULLVectorAwareLinearInterpolateImageFunction< TInputImage, TCoordRep >
		::EvaluateAtContinuousIndex(
			const ContinuousIndexType& index) const
		{
			unsigned int dim;  // index over dimension

			/**
			* Compute base index = closet index below point
			* Compute distance from point to base index
			*/
			IndexType baseIndex;
			double distance[Superclass::ImageDimension];

			for (dim = 0; dim < Superclass::ImageDimension; dim++)
			{
				baseIndex[dim] = Math::Floor<typename Superclass::IndexValueType >(index[dim]);
				distance[dim] = index[dim] - static_cast< double >(baseIndex[dim]);
			}

			/**
			* Interpolated value is the weighted sum of each of the surrounding
			* neighbors. The weight for each neighbor is the fraction overlap
			* of the neighbor pixel with respect to a pixel centered on point.
			*/
			OutputType output;
			output.Fill(0.0);

			typedef typename NumericTraits<PixelType>::ScalarRealType ScalarRealType;
			ScalarRealType totalOverlap = NumericTraits<ScalarRealType>::Zero;

			for (unsigned int counter = 0; counter < m_Neighbors; counter++)
			{

				double overlap = 1.0;          // fraction overlap
				unsigned int upper = counter;  // each bit indicates upper/lower neighbour
				IndexType neighIndex;

				// get neighbor index and overlap fraction
				for (dim = 0; dim < Superclass::ImageDimension; dim++)
				{

					if (upper & 1)
					{
						neighIndex[dim] = baseIndex[dim] + 1;

						// Take care of the case where the pixel is just
						// in the outer upper boundary of the image grid.
						if (neighIndex[dim] > this->m_EndIndex[dim])
						{
							neighIndex[dim] = this->m_EndIndex[dim];
						}

						overlap *= distance[dim];
					}
					else
					{
						neighIndex[dim] = baseIndex[dim];

						// Take care of the case where the pixel is just
						// in the outer lower boundary of the image grid.
						if (neighIndex[dim] < this->m_StartIndex[dim])
						{
							neighIndex[dim] = this->m_StartIndex[dim];
						}

						overlap *= 1.0 - distance[dim];
					}

					upper >>= 1;

				}

				// get neighbor value only if overlap is not zero
				if (overlap)
				{
					const PixelType input = this->GetInputImage()->GetPixel(neighIndex);

					if (_useNullVector && input == _nullVector)
					{
						//at least one of the overlapping vectors is a null vector,
						//hence stop the interpolation and pass the null vector
						output = _nullVector;
						break;
					}

					for (unsigned int k = 0; k < Superclass::Dimension; k++)
					{
						output[k] += overlap * static_cast<RealType>(input[k]);
					}

					totalOverlap += overlap;
				}

				if (totalOverlap == 1.0)
				{
					// finished
					break;
				}

			}

			return (output);
		}
	} // end namespace map
} // end namespace itk

#endif
