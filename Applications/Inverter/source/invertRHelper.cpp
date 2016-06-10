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
// @version $Revision: 1083 $ (last changed revision)
// @date    $Date: 2015-09-08 11:18:31 +0200 (Di, 08 Sep 2015) $ (last change date)
// @author  $Author: debusc $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/source/invertRHelper.cpp $
*/


#include "invertRHelper.h"
#include "mapGenericImageReader.h"

map::apps::invertR::LoadingLogic::LoadingLogic(ApplicationData& appData): _appData(appData)
{
};

void
map::apps::invertR::LoadingLogic::
loadRegistration()
{
  map::io::RegistrationFileReader::LoadedRegistrationPointer spReg;

  if (_appData._regFileName.empty())
  {
    mapDefaultExceptionStaticMacro(<<
      "Unable to load registration for inverions. No registration file is specified.");
  }
  else
  {
    map::io::RegistrationFileReader::Pointer spRegReader = map::io::RegistrationFileReader::New();

    std::cout << std::endl << "read registration file... ";
    spReg = spRegReader->read(_appData._regFileName);
    std::cout << "done." << std::endl;

    if (_appData._detailedOutput)
    {
      std::cout << std::endl << "Registration info:" << std::endl;
      _appData._spReg->Print(std::cout);
      std::cout << std::endl;
    }

  }

  _appData._spReg = spReg;
};


void
map::apps::invertR::LoadingLogic::
loadReferenceImage()
{
  if (!(_appData._refFileName.empty()))
  {
    map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;
    unsigned int loadedDimensions;
    map::io::GenericImageReader::LoadedPixelType loadedPixelType;
    map::io::GenericImageReader::LoadedComponentType loadedComponentType;
    map::io::GenericImageReader::MetaDataDictionaryArrayType loadedMetaDataDictArray;

    map::io::GenericImageReader::Pointer spReader = map::io::GenericImageReader::New();
    spReader->setSeriesReadStyle(_appData._seriesReadStyle);
    spReader->setFileName(_appData._refFileName);

    std::cout << std::endl << "read template file... ";
    loadedImage = spReader->GetOutput(loadedDimensions, loadedPixelType,
                                      loadedComponentType);
    loadedMetaDataDictArray = spReader->getMetaDictionaryArray();

    if (loadedImage.IsNotNull())
    {
      std::cout << "done." << std::endl;

      if (_appData._detailedOutput)
      {
        std::cout << "Input image info:" << std::endl;
        loadedImage->Print(std::cout);
        std::cout << std::endl;
      }
    }
    else
    {
      mapDefaultExceptionStaticMacro( <<
                                      " Unable to load template image. File is not existing or has an unsupported format.");
    }


    if (loadedDimensions != _appData._spReg->getTargetDimensions() || loadedDimensions != _appData._spReg->getMovingDimensions())
    {
      mapDefaultExceptionStaticMacro( <<
                                      " Unsupported template image. Template image dimensions does not match registration.");
    }

    _appData._spRefImage = loadedImage;
  }
};
