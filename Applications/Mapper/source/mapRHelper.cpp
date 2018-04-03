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
#include "mapDummyRegistrationAlgorithm.h"
#include "mapSimpleLandMarkFileReader.h"

map::apps::mapR::LoadingLogic::LoadingLogic(ApplicationData& appData): _appData(appData)
{
};


template <unsigned int VDimension>
map::core::RegistrationBase::Pointer GenerateDummyReg()
{
  typedef map::algorithm::DummyRegistrationAlgorithm<VDimension>	DummyRegType;
  typename DummyRegType::Pointer regAlg = DummyRegType::New();

  map::core::RegistrationBase::Pointer dummyReg = regAlg->getRegistration().GetPointer();

  return dummyReg;
}

void
map::apps::mapR::LoadingLogic::
loadRegistration()
{
  map::io::RegistrationFileReader::LoadedRegistrationPointer spReg;

  if (_appData._regFileName.empty())
  {
    std::cout << std::endl << "generate identity transform... ";

    if (_appData._loadedDimensions == 2)
    {
      spReg = GenerateDummyReg<2>();
    }
    else if (_appData._loadedDimensions == 3)
    {
      spReg = GenerateDummyReg<3>();
    }
    else
    {
      mapDefaultExceptionStaticMacro( <<
                                      "Cannot generate identity transform. Dimensionality of loaded input image is not supported. LoadedDimensions: "
                                      << _appData._loadedDimensions);
    }

    std::cout << "done." << std::endl;
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

    if (spReg->getMovingDimensions() != spReg->getTargetDimensions()
        || spReg->getMovingDimensions() != _appData._loadedDimensions)
    {
      mapDefaultExceptionStaticMacro( <<
                                      "Loaded registration and loaded image have no equal dimensionality. Registration cannot be used to map the image.");
    }
  }

  _appData._spReg = spReg;
};

::itk::DataObject::Pointer
loadGenericPointSet(const ::map::core::String& filename, unsigned int& loadedDimensions)
{
  ::itk::DataObject::Pointer result;

  if (!(filename.empty()))
  {
    try
    {
      typedef ::map::core::continuous::Elements<2>::InternalPointSetType PointSetType;
      result = ::map::utilities::loadLandMarksFromFile<PointSetType>(filename).GetPointer();
      loadedDimensions = 2;
    }
    catch (...)
    {

    }
    try
    {
      typedef ::map::core::continuous::Elements<3>::InternalPointSetType PointSetType;
      result = ::map::utilities::loadLandMarksFromFile<PointSetType>(filename).GetPointer();
      loadedDimensions = 3;
    }
    catch (...)
    {

    }
  }
  return result;
};


void
map::apps::mapR::LoadingLogic::
loadInput()
{
  map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;
  unsigned int loadedDimensions = 0;
  map::io::GenericImageReader::LoadedPixelType loadedPixelType = ::itk::ImageIOBase::UNKNOWNPIXELTYPE;
  map::io::GenericImageReader::LoadedComponentType loadedComponentType = ::itk::ImageIOBase::UNKNOWNCOMPONENTTYPE;
  map::io::GenericImageReader::MetaDataDictionaryArrayType loadedMetaDataDictArray;

  map::io::GenericImageReader::Pointer spReader = map::io::GenericImageReader::New();
  spReader->setSeriesReadStyle(_appData._seriesReadStyle);
  spReader->setFileName(_appData._inputFileName);
  spReader->setUpperSeriesLimit(_appData._upperSeriesLimit);

  std::cout << std::endl << "read input file... ";

  ::map::core::String loadErrorString;
  try
  {
    loadedImage = spReader->GetOutput(loadedDimensions, loadedPixelType,
      loadedComponentType);
    loadedMetaDataDictArray = spReader->getMetaDictionaryArray();
  }
  catch (const std::exception& e)
  {
    loadErrorString = e.what();
  }
  
  if (loadedImage.IsNotNull())
  {
    std::cout << "done." << std::endl;

    if (_appData._detailedOutput)
    {
      std::cout << "Input image info:" << std::endl;
      loadedImage->Print(std::cout);
      std::cout << std::endl;
    }

    if (loadedPixelType != ::itk::ImageIOBase::SCALAR)
    {
      mapDefaultExceptionStaticMacro(<<
        "Unsupported input image. Only simple scalar images are supported in this version.");
    }

    if (loadedDimensions < 2 || loadedDimensions > 3)
    {
      mapDefaultExceptionStaticMacro(<<
        "Unsupported input image. Only 2D and 3D images are supported in this version.");
    }

    _appData._input = loadedImage;
    _appData._inputIsImage = true;

    _appData._loadedDimensions = loadedDimensions;
    _appData._loadedPixelType = loadedPixelType;
    _appData._loadedComponentType = loadedComponentType;
    _appData._loadedMetaDataDictArray = loadedMetaDataDictArray;
  }
  else //*try to load simple point set
  {
    _appData._input = loadGenericPointSet(_appData._inputFileName, loadedDimensions);
    if (_appData._input.IsNotNull())
    {
      std::cout << "Input point set info:" << std::endl;
      _appData._input->Print(std::cout);
    }
    _appData._loadedDimensions = loadedDimensions;
    _appData._inputIsImage = false;
  }

  if (_appData._input.IsNull())
  {
    mapDefaultExceptionStaticMacro(<<
      " Unable to load input. File is not existing or has an unsupported format." << std::endl << "Error details: " << loadErrorString);
  }

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
      mapDefaultExceptionStaticMacro( <<
                                      " Unable to load template image. File is not existing or has an unsupported format.");
    }


    if (loadedDimensions != _appData._spReg->getTargetDimensions())
    {
      mapDefaultExceptionStaticMacro( <<
                                      " Unsupported template image. Template image dimensions does not match registration.");
    }

    _appData._spRefImage = loadedImage;
    _appData._loadedRefMetaDataDictArray = loadedMetaDataDictArray;
  }
};
