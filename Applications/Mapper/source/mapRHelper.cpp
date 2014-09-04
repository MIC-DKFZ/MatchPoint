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


#include "mapRHelper.h"
#include "mapGenericImageReader.h"

map::apps::mapR::LoadingLogic::LoadingLogic(ApplicationData& appData): _appData(appData)
{
};

void
  map::apps::mapR::LoadingLogic::
  loadRegistration()
{
  map::io::RegistrationFileReader::Pointer spRegReader = map::io::RegistrationFileReader::New();

  map::io::RegistrationFileReader::LoadedRegistrationPointer spReg;

  std::cout << std::endl << "read registration file... ";
  spReg = spRegReader->read(_appData._regFileName);
  std::cout << "done." << std::endl;

  if (_appData._detailedOutput)
  {
    std::cout << std::endl << "Registration info:" << std::endl;
    _appData._spReg->Print(std::cout);
    std::cout << std::endl;
  }

  if (spReg->getMovingDimensions() != spReg->getTargetDimensions()
    || spReg->getMovingDimensions() != _appData._loadedDimensions)
  {
    mapDefaultExceptionStaticMacro(<< "oaded registration and loaded image have no equal dimensionality. Registration cannot be used to map the image.");
  }

  _appData._spReg = spReg;
};

void
  map::apps::mapR::LoadingLogic::
  loadInputImage()
{
  map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;
  unsigned int loadedDimensions;
  map::io::GenericImageReader::LoadedPixelType loadedPixelType;
  map::io::GenericImageReader::LoadedComponentType loadedComponentType;
  map::io::GenericImageReader::MetaDataDictionaryArrayType loadedMetaDataDictArray;

  map::io::GenericImageReader::Pointer spReader = map::io::GenericImageReader::New();
  spReader->setSeriesReadStyle(_appData._seriesReadStyle);
  spReader->setFileName(_appData._inputFileName);
  spReader->setUpperSeriesLimit(_appData._upperSeriesLimit);

  std::cout << std::endl << "read input file... ";
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
    mapDefaultExceptionStaticMacro(<< " Unable to load input image. File is not existing or has an unsupported format.");
  }


  if (loadedPixelType != ::itk::ImageIOBase::SCALAR)
  {
    mapDefaultExceptionStaticMacro(<< "Unsupported input image. Only simple scalar images are supported in this version.");
  }

  if (loadedDimensions < 2 || loadedDimensions > 3)
  {
    mapDefaultExceptionStaticMacro(<< "Unsupported input image. Only 2D and 3D images are supported in this version.");
  }

  _appData._spInputImage = loadedImage;

  _appData._loadedDimensions = loadedDimensions;
  _appData._loadedPixelType = loadedPixelType;
  _appData._loadedComponentType = loadedComponentType;
  _appData._loadedMetaDataDictArray = loadedMetaDataDictArray;
};

void
  map::apps::mapR::LoadingLogic::
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
    spReader->setUpperSeriesLimit(_appData._upperSeriesLimit);

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
      mapDefaultExceptionStaticMacro(<< " Unable to load templatet image. File is not existing or has an unsupported format.");
    }


    if (loadedDimensions != _appData._spReg->getTargetDimensions())
    {
      mapDefaultExceptionStaticMacro(<< " Unsupported template image. Template image dimension does not match registration.");
    }

    _appData._spRefImage = loadedImage;
    _appData._loadedRefMetaDataDictArray = loadedMetaDataDictArray;
  }
};