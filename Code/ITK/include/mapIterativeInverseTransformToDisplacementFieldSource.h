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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/ITK/include/mapIterativeInverseTransformToDisplacementFieldSource.h $
*/


#ifndef __MAP_ITERATIVE_INVERSE_DEFORMATION_FIELD_SOURCE_H
#define __MAP_ITERATIVE_INVERSE_DEFORMATION_FIELD_SOURCE_H

#include "itkImageSource.h"

#include "itkTransform.h"
#include "itkWarpVectorImageFilter.h"
#include "itkVectorLinearInterpolateImageFunction.h"
#include "itkImageRegionIterator.h"
#include "itkTimeProbe.h"



namespace itk
{
	namespace map
	{


		/** \class IterativeInverseTransformToDisplacementFieldSource
		* \brief Computes the inverse of an transform numerically as deformation field.
		*
		* IterativeInverseTransformToDisplacementFieldSource generates a deformation field
		* like itk::IterativeInverseDisplacementFieldImageFilter (based on the same algorithmic
		* code). In difference to the later a itk::Transform will be used instead
		* of an input information field.
		* @TODO Test if the directions where correct incooperated. Add directional tests to the unit test
		*/
		template < class TOutputImage, typename TTransformScalarType >
		class ITK_EXPORT IterativeInverseTransformToDisplacementFieldSource :
			public itk::ImageSource<TOutputImage>
		{
		public:
			/** Standard class typedefs. */
			typedef IterativeInverseTransformToDisplacementFieldSource  Self;
			typedef itk::ImageSource<TOutputImage>   Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			/** Method for creation through the object factory. */
			itkNewMacro(Self);

			/** Run-time type information (and related methods). */
			itkTypeMacro(IterativeInverseTransformToDisplacementFieldSource, ImageSource);

			/** Some typedefs. */
			typedef TOutputImage OutputImageType;
			typedef typename OutputImageType::Pointer        OutputImagePointer;
			typedef typename OutputImageType::PixelType      OutputImagePixelType;
			typedef typename OutputImageType::PointType      OutputImagePointType;
			typedef typename OutputImageType::IndexType      OutputImageIndexType;
			typedef typename OutputImagePixelType::ValueType OutputImageValueType;
			typedef typename OutputImageType::RegionType     OutputImageRegionType;
			typedef typename OutputImageType::SpacingType    OutputImageSpacingType;
			typedef typename OutputImageType::SizeType       OutputImageSizeType;
			typedef typename OutputImageType::DirectionType  OutputImageDirectionType;

			typedef itk::Transform < TTransformScalarType,
			        OutputImageType::ImageDimension,
			        OutputImageType::ImageDimension > TransformType;
			typedef typename TransformType::Pointer        TransformPointer;
			typedef typename TransformType::ConstPointer   TransformConstPointer;

			typedef itk::TimeProbe TimeType;

			typedef itk::ImageRegionIterator<OutputImageType> OutputIterator;

			typedef itk::WarpVectorImageFilter<TOutputImage, TOutputImage, TOutputImage> VectorWarperType;

			typedef itk::VectorLinearInterpolateImageFunction<TOutputImage, double> FieldInterpolatorType;
			typedef typename FieldInterpolatorType::Pointer     FieldInterpolatorPointer;
			typedef typename FieldInterpolatorType::OutputType  FieldInterpolatorOutputType;

			itkSetMacro(NumberOfIterations, unsigned int);
			itkGetMacro(NumberOfIterations, unsigned int);

			// If the error (in mm) between forward and backward mapping is smaller than the StopValue,
			// the algorithm stops.
			// This value can be used to speed up the calculation.
			itkSetMacro(StopValue, double);
			itkGetMacro(StopValue, double);

			char *GetReport()
			{
				return this->m_Report;
			}

			virtual void SetTransform(const TransformType *transform);
			virtual const TransformType *GetTransform(void) const;

			/** Specify the size of the output image. */
			virtual void SetSize(const OutputImageSizeType &size);
			/** Get the size of the output image. */
			itkGetMacro(Size, const OutputImageSizeType);

			/** Specify the spacing of the output image. */
			virtual void SetSpacing(const OutputImageSpacingType &spacing);
			/** Get the spacing of the output image. */
			itkGetMacro(Spacing, const OutputImageSpacingType);

			/** Specify the origin of the output image. */
			virtual void SetOrigin(const OutputImagePointType &origin);
			/** Get the origin of the output image. */
			itkGetMacro(Origin, OutputImagePointType);

			/** Specify the origin of the output image. */
			virtual void SetDirection(const OutputImageDirectionType &direction);
			/** Get the origin of the output image. */
			itkGetMacro(Direction, OutputImageDirectionType);

#ifdef ITK_USE_CONCEPT_CHECKING
			/** Begin concept checking */
			itkConceptMacro(OutputHasNumericTraitsCheck,
			                (Concept::HasNumericTraits<OutputImageValueType>));
			/** End concept checking */
#endif

		protected:
			IterativeInverseTransformToDisplacementFieldSource();
			~IterativeInverseTransformToDisplacementFieldSource() {}

			void PrintSelf(std::ostream &os, Indent indent) const;
			void MakeReport();

			void GenerateData();

			virtual void GenerateOutputInformation();

			unsigned int m_NumberOfIterations;
			double m_StopValue;
			double m_Time;

		private:
			TransformConstPointer m_Transform;

			OutputImageSizeType       m_Size;    //size of the output image
			OutputImageSpacingType    m_Spacing; //spacing of the output image
			OutputImagePointType      m_Origin;  //origin of the output image
			OutputImageDirectionType  m_Direction;//direction of the output image

			IterativeInverseTransformToDisplacementFieldSource(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	} // end namespace map
} // end namespace itk

#include "mapIterativeInverseTransformToDisplacementFieldSource.txx"

#endif

