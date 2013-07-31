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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/ITK/include/mapArbitraryWarpImageFilter.h $
*/


#ifndef __MAP_ARBITRARY_WARP_IMAGE_FILTER_H
#define __MAP_ARBITRARY_WARP_IMAGE_FILTER_H

#include "mapNULLVectorAwareLinearInterpolateImageFunction.h"
#include "itkWarpImageFilter.h"
#include "itkSize.h"

namespace itk
{

	namespace map
	{
		/** \class ArbitraryWarpImageFilter
		 * \brief Warps an image using an input deformation field.
		 *
		 * ArbitraryWarpImageFilter warps an existing image with respect to
		 * a given deformation field. In difference to the standard itk version
		 * the largest possible region, sample rate and index is not defined via
		 * the deformation field (thus in the standard itk version the result image always
		 * covers the whole deformation field and has the same resolution).
		 * Using ArbitraryWarpImageFilter the user can specify in the origin, size and
		 * spacing/resolution of the result image.
		 * If the wished start origin, size and spacing are equal to the deformation field
		 * (thus both sample grids are identically), the standard itk version will be used
		 * because of its better performance. In all other cases the inverse mapping vectors
		 * for each result pixel must first be interpolated given the deformation field.
		 *
		 * A deformation field is represented as a image whose pixel type is some
		 * vector type with at least N elements, where N is the dimension of
		 * the input image. The vector type must support element access via operator
		 * [].
		 *
		 * The output image is produced by inverse mapping: the output pixels
		 * are mapped back onto the input image. This scheme avoids the creation of
		 * any holes and overlaps in the output image.
		 *
		 * Each vector in the deformation field represent the distance between
		 * a geometric point in the input space and a point in the output space such
		 * that:
		 *
		 * \f[ p_{in} = p_{out} + d \f]
		 *
		 * Typically the mapped position does not correspond to an integer pixel
		 * position in the input image. Interpolation via an image function
		 * is used to compute values at non-integer positions. The default
		 * interpolation typed used is the LinearInterpolateImageFunction.
		 * The user can specify a particular interpolation function via
		 * SetInterpolator(). Note that the input interpolator must derive
		 * from base class InterpolateImageFunction.
		 *
		 * Position mapped to outside of the input image buffer are assigned
		 * a edge padding value.
		 *
		 * The input image is set via SetInput. The input deformation field
		 * is set via SetDisplacementField.
		 *
		 * This filter is implemented as a multithreaded filter.
		 *
		 * \warning This filter assumes that the input type, output type
		 * and deformation field type all have the same number of dimensions.
		 *
		 * \ingroup GeometricTransforms MultiThreaded
		 */
		template <
		class TInputImage,
		      class TOutputImage,
		      class TDisplacementField
		      >
		class ITK_EXPORT ArbitraryWarpImageFilter :
			public itk::WarpImageFilter<TInputImage, TOutputImage, TDisplacementField>
		{
		public:
			/** Standard class typedefs. */
			typedef ArbitraryWarpImageFilter      Self;
			typedef itk::WarpImageFilter<TInputImage, TOutputImage, TDisplacementField> Superclass;
			typedef itk::SmartPointer<Self>         Pointer;
			typedef itk::SmartPointer<const Self>   ConstPointer;

			/** Method for creation through the object factory. */
			itkNewMacro(Self);

			/** Run-time type information (and related methods) */
			itkTypeMacro(ArbitraryWarpImageFilter, WarpImageFilter);

			/** Inherit some types from the superclass. */
			typedef typename Superclass::OutputImageRegionType    OutputImageRegionType;
			typedef typename Superclass::InputImageType           InputImageType;
			typedef typename Superclass::InputImagePointer        InputImagePointer;
			typedef typename Superclass::OutputImageType          OutputImageType;
			typedef typename Superclass::OutputImagePointer       OutputImagePointer;
			typedef typename Superclass::InputImageConstPointer   InputImageConstPointer;
			typedef typename Superclass::IndexType                IndexType;
			typedef typename Superclass::SizeType                 SizeType;
			typedef typename Superclass::PixelType                PixelType;
			typedef typename Superclass::SpacingType              SpacingType;

			typedef typename Superclass::DisplacementFieldType     DisplacementFieldType;
			typedef typename Superclass::DisplacementFieldPointer  DisplacementFieldPointer;
			typedef typename Superclass::DisplacementType         DisplacementType;

			typedef typename Superclass::CoordRepType             CoordRepType;
			typedef typename Superclass::InterpolatorType         InterpolatorType;
			typedef typename Superclass::InterpolatorPointer      InterpolatorPointer;
			typedef typename Superclass::DefaultInterpolatorType  DefaultInterpolatorType;

			typedef typename Superclass::PointType                PointType;

			/** Set the size of the output image. */
			itkSetMacro(Size, SizeType);

			/** Get the size of the output image. */
			itkGetConstReferenceMacro(Size, SizeType);

			/** Set the edge padding value */
			itkSetMacro(MappingErrorValue, PixelType);

			/** Get the edge padding value */
			itkGetMacro(MappingErrorValue, PixelType);

			/** Set the edge padding value */
			itkSetMacro(ThrowExceptionOnMappingError, bool);

			/** Get the edge padding value */
			itkGetMacro(ThrowExceptionOnMappingError, bool);

			/** Set the null vector used in the deformation field. */
			itkSetMacro(NullVector, DisplacementType);

			/** Get the null vector used in the deformation field. */
			itkGetConstReferenceMacro(NullVector, DisplacementType);

			bool usesNullVector() const
			{
				return m_UseNullVector;
			};

			void setNullVectorUsage(bool use)
			{
				m_UseNullVector = use;
			};

			/** WarpImageFilter produces an image which is a different
			 * size than its input image. As such, it needs to provide an
			 * implemenation for GenerateOutputInformation() which set
			 * the output information according the OutputSpacing, OutputOrigin
			 * and the deformation field's LargestPossibleRegion. */
			virtual void GenerateOutputInformation();

			/** It is difficult to compute in advance the input image region
			 * required to compute the requested output region. Thus the safest
			 * thing to do is to request for the whole input image.
			 *
			 * For the deformation field, the input requested region
			 * set to be the same as that of the output requested region. */
			virtual void GenerateInputRequestedRegion();

			/** This method is used to set the state of the filter before
			 * multi-threading. */
			virtual void BeforeThreadedGenerateData();

			/** This method is used to set the state of the filter after
			 * multi-threading. */
			virtual void AfterThreadedGenerateData();

		protected:
			ArbitraryWarpImageFilter();
			~ArbitraryWarpImageFilter() {};
			void PrintSelf(std::ostream &os, Indent indent) const;

			/** WarpImageFilter is implemented as a multi-threaded filter.
			 * As such, it needs to provide and implementation for
			 * ThreadedGenerateData(). */
			void ThreadedGenerateData(const OutputImageRegionType &outputRegionForThread,
			                          ::itk::ThreadIdType threadId);

		private:
			ArbitraryWarpImageFilter(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented

			bool      m_UseStandardWarpFilter;
			SizeType  m_Size;              // Size of the output image
			PixelType m_MappingErrorValue;
			bool      m_ThrowExceptionOnMappingError;

			bool m_UseNullVector;
			DisplacementType m_NullVector;

			typedef NULLVectorAwareLinearInterpolateImageFunction<DisplacementFieldType, CoordRepType> FieldInterpolatorType;
			typedef typename FieldInterpolatorType::Pointer FieldInterpolatorPointer;

			FieldInterpolatorPointer        m_FieldInterpolator;
		};

	} // end namespace map
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "mapArbitraryWarpImageFilter.txx"
#endif

#endif
