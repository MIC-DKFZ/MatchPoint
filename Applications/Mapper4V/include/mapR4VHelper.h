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
// @version $Revision: 536 $ (last changed revision)
// @date    $Date: 2014-05-19 16:45:05 +0200 (Mo, 19 Mai 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue1251/Applications/Mapper/include/mapRHelper.h $
*/


#ifndef __MAP_R4V_HELPER_H
#define __MAP_R4V_HELPER_H

#include "mapExceptionObjectMacros.h"
#include "mapRApplicationData.h"
#include "mapRHelper.h"

#include "vioitkCTXImageWriter.h"

namespace map
{
  namespace apps
  {
    namespace mapR4V
    {

      bool isVirtuosFile(const map::core::String& filePath);

      /** Helper class that contains the logic that handles the data loading according to the settings in appData.
      * the loaded data will be stored in app data. */
      class LoadingLogic
      {
      public:
        LoadingLogic(map::apps::mapR::ApplicationData& appData);
        void loadRegistration();
        void loadInputImage();
        void loadReferenceImage();
      protected:
        map::apps::mapR::ApplicationData& _appData;
        map::apps::mapR::LoadingLogic _legacyLogic;
      };


      template <typename TPixelType, unsigned int IDim>
      class ProcessingLogic
      {
      private:
        typedef map::apps::mapR::ProcessingLogic<TPixelType, IDim> LegacyLogicType;
      public:
        typedef ::itk::Image<TPixelType, IDim> ImageType;

        /**write the image data according to the settings in appData.
        * @pre pImage must point to a valid instance.*/
        static void doWriting(ImageType* pImage, const map::apps::mapR::ApplicationData& appData)
        {
          if (!pImage)
          {
            mapDefaultExceptionStaticMacro(<< "Cannot write data. Passed image pointer is invalid (NULL).");
          }

          if (isVirtuosFile(appData._outputFileName))
          {
            std::cout << std::endl << "save output file as Virtuos CTX... ";

            std::string metaValue;
            if (itk::ExposeMetaData<std::string>(appData._spInputImage->GetMetaDataDictionary(),"Virtuos.PatientName",metaValue))
            {
              itk::EncapsulateMetaData<std::string>(pImage->GetMetaDataDictionary(),"Virtuos.PatientName",metaValue);
            };
            if (itk::ExposeMetaData<std::string>(appData._spInputImage->GetMetaDataDictionary(),"Virtuos.CreatedBy",metaValue))
            {
              itk::EncapsulateMetaData<std::string>(pImage->GetMetaDataDictionary(),"Virtuos.CreatedBy",metaValue);
            };
            if (!itk::ExposeMetaData<std::string>(appData._spInputImage->GetMetaDataDictionary(),"Virtuos.CreationInfo",metaValue))
            {
              metaValue = "";
            };
            metaValue += "Mapped by MatchPoint. Used "+ appData._regFileName;
            itk::EncapsulateMetaData<std::string>(pImage->GetMetaDataDictionary(),"Virtuos.CreatedBy",metaValue);

            int metaIntValue;

            if (itk::ExposeMetaData<int>(appData._spInputImage->GetMetaDataDictionary(),"Virtuos.ModalityID",metaIntValue))
            {
              itk::EncapsulateMetaData<int>(pImage->GetMetaDataDictionary(),"Virtuos.ModalityID",metaIntValue);
            };

            vioitk::CTXImageWriter::ImageIntType* intImage = dynamic_cast<vioitk::CTXImageWriter::ImageIntType*>(pImage);
            vioitk::CTXImageWriter::ImageFloatType* floatImage = dynamic_cast<vioitk::CTXImageWriter::ImageFloatType*>(pImage);
            vioitk::CTXImageWriter::Pointer writer = vioitk::CTXImageWriter::New();
            writer->setFileName(appData._outputFileName);

            if (intImage)
            {
              writer->setImage(intImage);
            }
            else if (floatImage)
            {
              writer->setImage(floatImage);
            }
            else
            {
              mapDefaultExceptionStaticMacro(<< "Cannot write data. Passed image type is not supported by Virtuos (only 3D and int16/float pixel type).");
            }

            writer->writeData();

            std::cout << "done." << std::endl;
          }
          else
          {
            LegacyLogicType::doWriting(pImage, appData);
          };
        };

        static typename ImageType::Pointer doMapping(const map::apps::mapR::ApplicationData& appData)
        {
          return LegacyLogicType::doMapping(appData);
        };

        static void processData(const map::apps::mapR::ApplicationData& appData)
        {
          ImageType::Pointer mappedImage = doMapping(appData);
          doWriting(mappedImage,appData);
        }

      };


    }
  }
}


#endif
