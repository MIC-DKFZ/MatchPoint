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


#include "mapR4VHelper.h"

#include "vioitkCTXImageLoader.h"


bool
  map::apps::mapR4V::isVirtuosFile(const map::core::String& filePath)
{
  bool result = false;

  if (filePath.find(".ctx") != map::core::String::npos)
  {
    result = true;
  };

  if (filePath.find(".ctx.gz") != map::core::String::npos)
  {
    result = true;
  };

  return result;
}

map::apps::mapR4V::LoadingLogic::LoadingLogic(map::apps::mapR::ApplicationData& appData): _appData(appData), _legacyLogic(appData)
{
};

void
  map::apps::mapR4V::LoadingLogic::
  loadRegistration()
{
  _legacyLogic.loadRegistration();
};

void
  map::apps::mapR4V::LoadingLogic::
  loadInputImage()
{
  if(isVirtuosFile(_appData._inputFileName))
  {
    map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;
    unsigned int loadedDimensions;
    map::io::GenericImageReader::LoadedPixelType loadedPixelType;
    map::io::GenericImageReader::LoadedComponentType loadedComponentType;

    std::cout << std::endl << "read input file (Virtuos CTX)... ";

    vioitk::CTXImageLoader::Pointer loader = vioitk::CTXImageLoader::New();
    loader->setFileName(_appData._inputFileName);
    loader->importData();

    loadedImage = loader->getITKImage();
    loadedDimensions = 3;
    loadedPixelType = ::itk::ImageIOBase::SCALAR;

    if (loadedImage.IsNotNull())
    {
      if (loader->getPixelType() == "float")
      {
        loadedComponentType = ::itk::ImageIOBase::FLOAT;
      }
      else
      {
        loadedComponentType = ::itk::ImageIOBase::SHORT;
      }
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
      mapDefaultExceptionStaticMacro(<< " Unable to load input image. File is not existing or has an unsupported format.");
    }

    _appData._spInputImage = loadedImage;
    _appData._loadedDimensions = loadedDimensions;
    _appData._loadedPixelType = loadedPixelType;
    _appData._loadedComponentType = loadedComponentType;

  }
  else
  {
    _legacyLogic.loadInputImage();
  }
};

void
  map::apps::mapR4V::LoadingLogic::
  loadReferenceImage()
{

  if (!(_appData._refFileName.empty()))
  {
    if(isVirtuosFile(_appData._refFileName))
    {
      if (_appData._spReg->getTargetDimensions() != 3)
      {
        mapDefaultExceptionStaticMacro(<< "Template image dimension does not match registration target dimension. Virtuos CTX loading only for 3D images.");
      }

      map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;

      std::cout << std::endl << "read template file (Virtuos CTX)... ";

      vioitk::CTXImageLoader::Pointer loader = vioitk::CTXImageLoader::New();
      loader->setFileName(_appData._inputFileName);
      loader->importData();

      loadedImage = loader->getITKImage();

      if (loadedImage.IsNull())
      {
        mapDefaultExceptionStaticMacro(<< " Unable to load input image. File is not existing or has an unsupported format.");
      }

      _appData._spRefImage = loadedImage;

    }
    else
    {
      _legacyLogic.loadReferenceImage();
    }
  }
};