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


#ifndef __MAP_IMAGE_WRITER_H
#define __MAP_IMAGE_WRITER_H

#include "mapString.h"
#include "mapImageReader.h"
#include "mapClassMacros.h"

#include "itkImage.h"
#include "itkImageSource.h"

namespace map
{
	namespace io
	{

		struct ImageSeriesWriteStyle
		{
			enum Type
			{
				Default = 0, //* - Depending on the file extension (meta images (*.mhd, *.mha): None; others: Numeric)
				None = 1, //* - No series writing, only the specified file
				Numeric = 3 //* - Use series writer and NumericSeriesFileNames
			};
		};

		/** @class ImageWriter
		 * @brief Class manages the writing of 2D/3D images typically used in f.r.e.e. ...
		 *
		 * ImageWriter is used to save 2D or 3D images in an itk like style, but also takes
		 * the needs of f.r.e.e. and the specialties of different formats into account.\n
		 * 2D images will be saved directly by the IO classes of itk, so in this case the
		 * ImageWriter is only a layer of abstraction.\n
		 * 3D images will be handled different, depending on the type of files:\n
		 *  - 2D-Formats: (*.png, *.bmp, *.jpg, *.tif) Will be considered as series of images. The list of files will be
		 *			  created by ::itk::NumericSeriesFileNames, so in this case the given
		 *			  file name is already masked by %d for the increasing index within
		 *			  the file name.
		 *	- others: directly by the itk io
		 * .
		 * @ingroup Utils
		 */
		template <typename TInputPixel, typename TOutputPixel, unsigned int iDimension = 2>
		class ImageWriter : public ::itk::Object
		{
		public:
			typedef ::itk::Image<TInputPixel, iDimension>  InputImageType;
			typedef ::itk::Image<TOutputPixel, iDimension> OutputImageType;

			typedef ImageWriter<TInputPixel, TOutputPixel, iDimension> Self;
			typedef ::itk::Object  Superclass;

			typedef ::itk::SmartPointer<Self>                                     Pointer;
			typedef ::itk::SmartPointer<const Self>                               ConstPointer;
			itkTypeMacro(ImageWriter, itk::Object);
			itkNewMacro(Self);

		private:
			/** Pointer to the image volume to be saved.*/
			typename InputImageType::ConstPointer _spImage;
			/** The file name and path for the saved image. */
			::map::core::String  _filePath;
			/** Indicates if the output image intensity should be rescaled.*/
			bool _rescaleImage;
			/** Indicates the minimum of the output.*/
			double _rescaleMin;
			/** Indicates the maximum of the output.*/
			double _rescaleMax;
			/** Defines if the specified image should be stored as one file or a series of files.
			 * Only relevant for 3D images.*/
			typename ImageSeriesWriteStyle::Type _seriesWriteStyle;

			void save2D();

			void save3D();

		public:
			mapGetConstReferenceVarMacro(FilePath, core::String, _filePath);
			mapSetVarMacro(FilePath, core::String, _filePath);

			mapGetConstReferenceVarMacro(RescaleMinimum, double, _rescaleMin);
			mapSetVarMacro(RescaleMinimum, double, _rescaleMin);

			mapGetConstReferenceVarMacro(RescaleMaximum, double, _rescaleMax);
			mapSetVarMacro(RescaleMaximum, double, _rescaleMax);

			mapGetConstReferenceVarMacro(RescaleImage, bool, _rescaleImage);
			mapSetVarMacro(RescaleImage, bool, _rescaleImage);

			/** Function loads the image if needed and returns the data.
			 * @return Pointer to loaded image.*/
			void setInput(const InputImageType* pImage);

			/** Function saves the image. */
			void update();

			ImageWriter();

		protected:
			virtual ~ImageWriter();

		private:
			ImageWriter(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapImageWriter.tpp"
#endif

#endif
