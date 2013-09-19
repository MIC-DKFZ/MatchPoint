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

#ifndef __NULL_VECTOR_AWARE_LINEAR_INTERPOLATE_IMAGE_FUNCTION_H
#define __NULL_VECTOR_AWARE_LINEAR_INTERPOLATE_IMAGE_FUNCTION_H

#include "itkVectorLinearInterpolateImageFunction.h"

namespace itk
{
	namespace map
	{

		/**
		* \class NULLVectorAwareLinearInterpolateImageFunction
		* \brief Linearly interpolate a vector image at specified positions and awares the null vector.
		*
		* NULLVectorAwareLinearInterpolateImageFunction extends the normal itk::VectorLinearInteroplateImageFunction
		* by support/awareness of null vectors. It is used e.g. to map the MatchPoint field kernels.
		*
		* This function works for N-dimensional images.
		*
		* \warning This function work only for Vector images. For
		* scalar images use LinearInterpolateImageFunction.
		*
		* \ingroup ImageFunctions ImageInterpolators
		*
		*/
		template <class TInputImage, class TCoordRep = double>
		class ITK_EXPORT NULLVectorAwareLinearInterpolateImageFunction :
			public VectorLinearInterpolateImageFunction<TInputImage, TCoordRep>
		{
		public:
			/** Standard class typedefs. */
			typedef NULLVectorAwareLinearInterpolateImageFunction                  Self;
			typedef VectorLinearInterpolateImageFunction<TInputImage, TCoordRep> Superclass;
			typedef SmartPointer<Self>                                    Pointer;
			typedef SmartPointer<const Self>                              ConstPointer;

			/** Method for creation through the object factory. */
			itkNewMacro(Self);

			/** Run-time type information (and related methods). */
			itkTypeMacro(NULLVectorAwareLinearInterpolateImageFunction,
						 VectorLinearInterpolateImageFunction);

			/** InputImageType typedef support. */
			typedef typename Superclass::InputImageType InputImageType;
			typedef typename Superclass::PixelType      PixelType;
			typedef typename Superclass::ValueType      ValueType;
			typedef typename Superclass::RealType       RealType;

			/** Index typedef support. */
			typedef typename Superclass::IndexType       IndexType;

			/** ContinuousIndex typedef support. */
			typedef typename Superclass::ContinuousIndexType ContinuousIndexType;

			/** Output type is Vector<double,Dimension> */
			typedef typename Superclass::OutputType OutputType;

			/** Evaluate the function at a ContinuousIndex position
			*
			* Returns the linearly interpolated vectors at a
			* specified point position. No bounds checking is done.
			* The point is assume to lie within the image buffer.
			* If one of the interplated vectors is the null vector
			* while null vector usage is activated, the null vector
			* will allways be returned.
			*
			* ImageFunction::IsInsideBuffer() can be used to check bounds before
			* calling the method. */
			virtual OutputType EvaluateAtContinuousIndex(
				const ContinuousIndexType& index) const;

			const OutputType& GetNullVector() const
			{
				return _nullVector;
			};

			void SetNullVector(const OutputType& nullVector)
			{
				_nullVector = nullVector;
			};

			bool UsesNullVector() const
			{
				return _useNullVector;
			};

			void SetNullVectorUsage(bool use)
			{
				_useNullVector = use;
			};


		protected:
			NULLVectorAwareLinearInterpolateImageFunction();
			~NULLVectorAwareLinearInterpolateImageFunction() {};
			void PrintSelf(std::ostream& os, Indent indent) const;

			bool _useNullVector;
			OutputType _nullVector;

			/** Number of neighbors used in the interpolation */
			static const unsigned long  m_Neighbors;

		private:
			NULLVectorAwareLinearInterpolateImageFunction(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented


		};
	} // end namespace map

} // end namespace itk

#ifndef MatchPoint_MANUAL_TPP
# include "mapNULLVectorAwareLinearInterpolateImageFunction.tpp"
#endif

#endif
