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

#ifndef __MAP_GENERIC_IMAGE_READER_H
#define __MAP_GENERIC_IMAGE_READER_H

#include "mapImageReader.h"
#include "mapMAPIOExports.h"

namespace map
{
    namespace io
    {
        /** @class ImageReader
        * @brief Helper class manages the generic loading (unspecified dimension and pixel type) of 2D/3D images ...
        *
        * GenericImageReader uses the ImageReader class and dispatches the dimension and pixel type information from the specified image file.
        * GenericImageReader supports 2D and 3D images and the following pixel types:
        * - (unsigned) char
        * - (unsigned) short
        * - (unsigned) int
        * - (unsigned) long
        * - float
        * - double
        * .
        * Due to the fact that it builds upon the itk io infrastructure, all formats supported by ITK
        * can be read.
        * For further information regarding the usage see documentation of ImageReader.
        * @sa ImageReader
        * @ingroup Utils
        */
        class MAPIO_EXPORT GenericImageReader : public ::itk::Object
        {
        public:
            using Self = GenericImageReader;
            using Superclass = ::itk::Object;
            using Pointer = ::itk::SmartPointer<Self>;
            using ConstPointer = ::itk::SmartPointer<const Self>;

            itkTypeMacro(GenericImageReader, ::itk::Object);
            itkNewMacro(Self);

            using GenericOutputImageType = ::itk::DataObject;

            using LoadedPixelType = ::itk::IOPixelEnum;

            using LoadedComponentType = ::itk::IOComponentEnum;

            using MetaDataDictionaryArrayType = std::vector<itk::MetaDataDictionary>;

        private:
            /** Loaded Image.*/
            GenericOutputImageType::Pointer _spImage;
            /** The file name of the image. */
            core::String  _fileName;
            /** The upper limit for the searching of series files in the path.*/
            unsigned int _upperSeriesLimit;
            /** Indicates if the image data is up to date or should be read again.*/
            bool _upToDate;
            /** Defines if the specified image file is part of a series and the
            * whole series should be read into one image. Only relevant for 3D images.*/
            ImageSeriesReadStyle::Type _seriesReadStyle;

            unsigned int _loadedDimensions;
            LoadedPixelType _loadedPixelType;
            LoadedComponentType _loadedComponentType;
            core::String _loadedComponentTypeStr;
            core::String _loadedPixelTypeStr;

            MetaDataDictionaryArrayType _dictionaryArray;

            /** Loads the image. First identifies pixel type and dimension and then deligates according
             * to the pixel type.
             * @exception map::core::ExceptionObject If no ImageIO is found.
             * @exception map::core::ExceptionObject If dimension of the image is not supported. Only 2D/3D is supported.
             * @exception map::core::ExceptionObject If pixel type is not supported. Currently only scalar pixels are supported.
             */
            void load();

            /** Loads an scalar image.
              * @exception map::core::ExceptionObject If pixel component type is not supported.
              */
            template <unsigned int IDimension>
            void loadScalar();

            //template <unsigned int IDimension>
            //void loadRGB();

        public:
            /** Function to access the member variable _FileName. _FileName represents the filename of the
            * headerfile. The path must be included, the file extension may left away.
            * @return File name of the header file.*/
            const core::String&  getFileName() const;

            /** Function to access the member variable _FileName. _FileName represents the filename of the
            * headerfile. The path must be included, the file extension may left away.
            * @param [in] sFileName The file name of the header file.*/
            void setFileName(const core::String&  sFileName);

            /** Function to access the member variable _upperSeriesLimit. _upperSeriesLimit represents
            * the upper limit for the series file search.
            * @return The upper limit of the series search.*/
            unsigned int getUpperSeriesLimit() const;

            /** Function to access the member variable _upperSeriesLimit. _upperSeriesLimit represents
            * the upper limit for the series file search. Changing the series limit out dates the ImageReader.
            * @remark It is only relevant if series style is set to "Numeric".
            * @param [in] upperLimit The upper limit of the header file.*/
            void setUpperSeriesLimit(unsigned int upperLimit);

            /** Function to access the member variable _seriesReadStyle (see member description for more information).*/
            ImageSeriesReadStyle::Type getSeriesReadStyle() const;

            /** Function to access the member variable _seriesReadStyle (see member description for more information).
            * Changing the style out dates the ImageReader.*/
            void setSeriesReadStyle(ImageSeriesReadStyle::Type readStyle);

            /** Function loads the image if needed and returns the data.
            * @return Pointer to loaded image.
            * @exception map::core::ExceptionObject If no ImageIO is found.
            * @exception map::core::ExceptionObject If dimension of the image is not supported. Only 2D/3D is supported.
            * @exception map::core::ExceptionObject If pixel type is not supported. Currently only scalar pixels are supported.
            * @exception map::core::ExceptionObject If pixel component type is not supported.
            */
            GenericOutputImageType*  GetOutput(unsigned int& loadedDimensions, LoadedPixelType& loadedPixelType,
                LoadedComponentType& loadedComponentType);

            /** Function returns the reference to the meta data dictionary(ies) of the latest file(s) loaded by this class.
             * Array may be empty if no MetaDictionary exists.*/
            const MetaDataDictionaryArrayType& getMetaDictionaryArray();

        protected:
            GenericImageReader();

            ~GenericImageReader() override;
        };

    }  // namespace io
}  // namespace map

#endif
