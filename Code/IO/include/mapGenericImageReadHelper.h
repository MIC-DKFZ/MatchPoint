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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapGenericImageReader.h $
*/

#ifndef __MAP_GENERIC_IMAGE_READ_HELPER_H
#define __MAP_GENERIC_IMAGE_READ_HELPER_H

#include "mapGenericImageReader.h"

namespace map
{
    namespace io
    {

    template <typename TOutputImageType, typename TInputPixelType>
    typename TOutputImageType::Pointer
        castGenericImageHelper(map::io::GenericImageReader::GenericOutputImageType::Pointer genericImage)
    {
        typedef itk::Image<TInputPixelType, TOutputImageType::ImageDimension> InputImageType;
        typedef itk::CastImageFilter<InputImageType, TOutputImageType> CastFilterType;
        typename CastFilterType::Pointer filter = CastFilterType::New();
        typename InputImageType::ConstPointer input = dynamic_cast<InputImageType*>(genericImage.GetPointer());
        filter->SetInput(input);
        filter->Update();
        typename TOutputImageType::Pointer result = filter->GetOutput();
        return result;
    }

        /**
        * @brief Helper function for the use of GenericImageReader in on statement and directly casts the result image.
        *
        * The helper method uses the generic image reader to read the image and casts it into
        * the specified output image type. If the image cannot be casted the return will be a null Pointer.
        * For specific informations please see the documentation of GenericImageReader.
        * @param pLoadedDictArray Pass a pointer to valid array to receive the meta dictionaries
        * loaded with the image. If the pointer is null, no dictionaries will be transfered. The array
        * will be reseted before the loaded dictionaries will be added.
        * @sa ImageReader
        * @ingroup Utils
        */
        template <typename TOutputImageType>
        typename TOutputImageType::Pointer
            readGenericImageAndCast(const core::String& fileName,
            ImageSeriesReadStyle::Type readStyle = ImageSeriesReadStyle::Default,
            unsigned int upperNumericSeriesLimit = 100,
            GenericImageReader::MetaDataDictionaryArrayType*
            pLoadedDictArray = NULL)
        {
            typename TOutputImageType::Pointer result;

            map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;
            unsigned int loadedDimensions;
            map::io::GenericImageReader::LoadedPixelType loadedPixelType;
            map::io::GenericImageReader::LoadedComponentType loadedComponentType;
            map::io::GenericImageReader::MetaDataDictionaryArrayType loadedMetaDataDictArray;

            map::io::GenericImageReader::Pointer spReader = map::io::GenericImageReader::New();
            spReader->setSeriesReadStyle(readStyle);
            spReader->setUpperSeriesLimit(upperNumericSeriesLimit);
            spReader->setFileName(fileName);

            loadedImage = spReader->GetOutput(loadedDimensions, loadedPixelType,
                loadedComponentType);

            if (loadedDimensions != TOutputImageType::ImageDimension)
            {
                mapDefaultExceptionStaticMacro(<<
                    "Loaded image has not the requested/excepted image dimension. Loaded dimension: " << loadedDimensions << "; Excepted dimension: " << TOutputImageType::ImageDimension);
            }

            switch (loadedComponentType)
            {
            case ::itk::ImageIOBase::UCHAR:
            {
                result = castGenericImageHelper<TOutputImageType, unsigned char>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::CHAR:
            {
                result = castGenericImageHelper<TOutputImageType, char>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::USHORT:
            {
                result = castGenericImageHelper<TOutputImageType, unsigned short>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::SHORT:
            {
                result = castGenericImageHelper<TOutputImageType, short>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::UINT:
            {
                result = castGenericImageHelper<TOutputImageType, unsigned int>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::INT:
            {
                result = castGenericImageHelper<TOutputImageType, int>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::ULONG:
            {
                result = castGenericImageHelper<TOutputImageType, unsigned long>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::LONG:
            {
                result = castGenericImageHelper<TOutputImageType, long>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::FLOAT:
            {
                result = castGenericImageHelper<TOutputImageType, float>(loadedImage);
                break;
            }

            case ::itk::ImageIOBase::DOUBLE:
            {
                result = castGenericImageHelper<TOutputImageType, double>(loadedImage);
                break;
            }

            default:
            {
                mapDefaultExceptionStaticMacro(<<
                    "The file uses a pixel component type that is not supported in this application.");
            }
            }

            return result;
        }


    }
}

#endif
