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


#ifndef __MAP_IMAGE_WRITER_TPP
#define __MAP_IMAGE_WRITER_TPP

#include "mapImageWriter.h"

#include "mapFileDispatch.h"

#ifdef MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER
#undef ITK_IO_FACTORY_REGISTER_MANAGER
#endif //MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTE

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkImageSeriesReader.h"
#include "itkImageSeriesWriter.h"
#include "itkNumericSeriesFileNames.h"

#include "itkRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkFixedArray.h"

#include <iostream>
#include <locale>


namespace map
{
	namespace io
	{

		template <typename TInputPixel, typename TOutputPixel, unsigned int iDimension>
		void
		ImageWriter<TInputPixel, TOutputPixel, iDimension>::
		save2D()
		{
			typedef ::itk::ImageFileWriter< OutputImageType  > ImageWriterType;
			typedef ::itk::RescaleIntensityImageFilter< InputImageType, InputImageType > RescaleFilterType;
			typedef ::itk::CastImageFilter< InputImageType, OutputImageType > CastFilterType;

			typename CastFilterType::Pointer  imageCaster =  CastFilterType::New();
			typename ImageWriterType::Pointer  imageWriter  = ImageWriterType::New();
			typename RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();

			if (_rescaleImage)
			{
				rescaleFilter->SetOutputMinimum(_rescaleMin);
				rescaleFilter->SetOutputMaximum(_rescaleMax);
				rescaleFilter->SetInput(_spImage);
				imageCaster->SetInput(rescaleFilter->GetOutput());
			}
			else
			{
				imageCaster->SetInput(_spImage);
			}

			imageWriter->SetFileName(_filePath.c_str());
			imageWriter->SetInput(imageCaster->GetOutput());

			imageWriter->Update();
		};

		template <typename TInputPixel, typename TOutputPixel, unsigned int iDimension>
		void
		ImageWriter<TInputPixel, TOutputPixel, iDimension>::
		save3D()
		{
			core::FileDispatch dispatch(_filePath);
			core::String  sTemp = dispatch.getExtension();

			//Converts to lowercase, because itk:analyzeIO is bugged and only checks for lower case
			for (core::String::iterator spos = sTemp.begin(); spos != sTemp.end(); spos++)
			{
				(*spos) = std::tolower((*spos), std::locale("english"));
			}

			if ((_seriesWriteStyle == map::io::ImageSeriesWriteStyle::Numeric) ||
				(_seriesWriteStyle == map::io::ImageSeriesWriteStyle::Default &&
				 ((sTemp == ".png") || (sTemp == ".bmp") || (sTemp == ".jpg") || (sTemp == ".tif")
				  || (sTemp == ".dcm") || (sTemp == ".ima"))))
			{
				typedef ::itk::CastImageFilter< InputImageType, OutputImageType > CastFilterType;
				typedef ::itk::RescaleIntensityImageFilter< InputImageType, InputImageType > RescaleFilterType;
				typedef ::itk::Image < TOutputPixel, iDimension - 1 > OutputSeriesImageType;
				typedef ::itk::ImageSeriesWriter< OutputImageType, OutputSeriesImageType  > SeriesWriterType;

				typename SeriesWriterType::Pointer  seriesWriter  = SeriesWriterType::New();
				typename CastFilterType::Pointer  imageCaster =  CastFilterType::New();
				typename RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();

				seriesWriter->SetSeriesFormat(_filePath);

				if (_rescaleImage)
				{
					rescaleFilter->SetOutputMinimum(_rescaleMin);
					rescaleFilter->SetOutputMaximum(_rescaleMax);
					rescaleFilter->SetInput(_spImage);
					imageCaster->SetInput(rescaleFilter->GetOutput());
				}
				else
				{
					imageCaster->SetInput(_spImage);
				}

				seriesWriter->SetInput(imageCaster->GetOutput());

				seriesWriter->Update();
			}
			else
			{
				//others (e.g. Analyze, MetaImage) uses the direct itk IO like 2D images
				save2D();
			}
		};

		/** Function loads the image if needed and returns the data.
		 * \return Pointer to loaded image.*/
		template <typename TInputPixel, typename TOutputPixel, unsigned int iDimension>
		void
		ImageWriter<TInputPixel, TOutputPixel, iDimension>::
		setInput(const InputImageType* pImage)
		{
			_spImage = pImage;
		};

		/** Function saves the image. */
		template <typename TInputPixel, typename TOutputPixel, unsigned int iDimension>
		void
		ImageWriter<TInputPixel, TOutputPixel, iDimension>::
		update()
		{
			if (!_spImage)
			{
				mapDefaultExceptionMacro( << "No image specified to save.");
			}

			if (_filePath == "")
			{
				mapDefaultExceptionMacro( << "No filepath specified for file to save.");
			}

			switch (OutputImageType::GetImageDimension())
			{
				case 2:
					save2D();
					break;

				case 3:
					save3D();
					break;

				default:
					mapDefaultExceptionMacro( << "Image writer only accepts 2 or 3 dimensional images.")
			};
		};

		template <typename TInputPixel, typename TOutputPixel, unsigned int iDimension>
		ImageWriter<TInputPixel, TOutputPixel, iDimension>::
		ImageWriter()
		{
			_filePath = "";
			_spImage = NULL;
			_rescaleImage = false;
			_rescaleMax = 255;
			_rescaleMin = 0;
			_seriesWriteStyle = ImageSeriesWriteStyle::Default;
		};

		template <typename TInputPixel, typename TOutputPixel, unsigned int iDimension>
		ImageWriter<TInputPixel, TOutputPixel, iDimension>::
		~ImageWriter()
		{
		};

	}
}
#endif
