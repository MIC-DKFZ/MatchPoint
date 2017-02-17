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
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/source/matchRHelper.cpp $
*/


#include "matchRHelper.h"
#include "mapGenericImageReader.h"
#include "mapDeploymentDLLAccess.h"
#include "mapDeploymentDLLHandle.h"
#include "mapMetaProperty.h"
#include "mapContinuousElements.h"
#include "mapSimpleLandMarkFileReader.h"

#include "itkDataObject.h"
#include "itkCastImageFilter.h"



template <typename TPixelType, unsigned int IDimension>
void handleImageCast(const ::map::io::GenericImageReader::GenericOutputImageType* inputImage, ::map::io::GenericImageReader::GenericOutputImageType::Pointer& castedImage)
{
  typedef ::itk::Image<TPixelType, IDimension> InputImageType;
  typedef typename ::map::core::discrete::Elements<IDimension>::InternalImageType CastedImageType;
  typedef ::itk::CastImageFilter<InputImageType, CastedImageType> FilterType;

  const InputImageType* input = dynamic_cast<const InputImageType*>(inputImage);

  typename FilterType::Pointer caster = FilterType::New();

  caster->SetInput(input);
  caster->Update();
  typename CastedImageType::Pointer casted = caster->GetOutput();

  castedImage = casted.GetPointer();
}


template <unsigned int IDimension>
void handleGenericImageCast(map::io::GenericImageReader::LoadedComponentType loadedComponentType, const ::map::io::GenericImageReader::GenericOutputImageType* inputImage, ::map::io::GenericImageReader::GenericOutputImageType::Pointer& castedImage)
{
  switch (loadedComponentType)
  {
  case ::itk::ImageIOBase::UCHAR:
  {
    handleImageCast<unsigned char, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::CHAR:
  {
    handleImageCast<char, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::USHORT:
  {
    handleImageCast<unsigned short, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::SHORT:
  {
    handleImageCast<short, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::UINT:
  {
    handleImageCast<unsigned int, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::INT:
  {
    handleImageCast<int, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::ULONG:
  {
    handleImageCast<unsigned long, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::LONG:
  {
    handleImageCast<long, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::FLOAT:
  {
    handleImageCast<float, IDimension>(inputImage, castedImage);
    break;
  }

  case ::itk::ImageIOBase::DOUBLE:
  {
    handleImageCast<double, IDimension>(inputImage, castedImage);
    break;
  }

  default:
  {
    mapDefaultExceptionStaticMacro(<<
      "The file uses a pixel component type that is not supported in this application.");
  }
  }
}


void
::map::apps::matchR::loadAlgorithm(::map::apps::matchR::ApplicationData& appData)
{
  map::deployment::RegistrationAlgorithmBasePointer spAlgorithmBase = NULL;

  std::cout << std::endl << "Load registration algorithm..." << std::endl;

  map::deployment::DLLHandle::Pointer spHandle = NULL;

  spHandle = map::deployment::openDeploymentDLL(appData._algorithmFileName);

  if (spHandle.IsNull())
  {
    mapDefaultExceptionStaticMacro(<<
      "Cannot open deployed registration algorithm file.");
  }

  std::cout << "... libary opened..." << std::endl;

  if (appData._detailedOutput)
  {
    std::cout << "Algorithm information: " << std::endl;
    spHandle->getAlgorithmUID().Print(std::cout, 2);
    std::cout << std::endl;
  }

  //Now load the algorthm from DLL
  spAlgorithmBase = map::deployment::getRegistrationAlgorithm(spHandle);


  if (spAlgorithmBase.IsNotNull())
  {
    std::cout << "... done" << std::endl << std::endl;

    if (spAlgorithmBase->getMovingDimensions() != spAlgorithmBase->getTargetDimensions()
      || spAlgorithmBase->getMovingDimensions() != appData._loadedDimensions)
    {
      mapDefaultExceptionStaticMacro(<<
        "Loaded algorithm and loaded imagey have no equal dimensionality. Algorithm cannot be used to register the image.");
    }
    appData._algorithm = spAlgorithmBase;
  }
  else
  {
    mapDefaultExceptionStaticMacro(<< "Cannot create algorithm instance");
  }
};

void
::map::apps::matchR::loadMovingImage(::map::apps::matchR::ApplicationData& appData)
{
  map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;
  unsigned int loadedDimensions;
  map::io::GenericImageReader::LoadedPixelType loadedPixelType;
  map::io::GenericImageReader::LoadedComponentType loadedComponentType;
  map::io::GenericImageReader::MetaDataDictionaryArrayType loadedMetaDataDictArray;

  map::io::GenericImageReader::Pointer spReader = map::io::GenericImageReader::New();
  spReader->setSeriesReadStyle(appData._seriesReadStyle);
  spReader->setFileName(appData._movingFileName);
  spReader->setUpperSeriesLimit(appData._upperSeriesLimit);

  std::cout << std::endl << "Read moving image file... ";
  loadedImage = spReader->GetOutput(loadedDimensions, loadedPixelType,
    loadedComponentType);
  loadedMetaDataDictArray = spReader->getMetaDictionaryArray();

  if (loadedImage.IsNotNull())
  {
    std::cout << "done." << std::endl;

    if (appData._detailedOutput)
    {
      std::cout << "Moving image info:" << std::endl;
      loadedImage->Print(std::cout);
      std::cout << std::endl;
    }
  }
  else
  {
    mapDefaultExceptionStaticMacro(<<
      " Unable to load moving image. File is not existing or has an unsupported format.");
  }


  if (loadedPixelType != ::itk::ImageIOBase::SCALAR)
  {
    mapDefaultExceptionStaticMacro(<<
      "Unsupported moving image. Only simple scalar images are supported in this version.");
  }

  if (loadedDimensions < 2 || loadedDimensions > 3)
  {
    mapDefaultExceptionStaticMacro(<<
      "Unsupported moving image. Only 2D and 3D images are supported in this version.");
  }
  else if(loadedComponentType == 2)
  {
    handleGenericImageCast<2>(loadedComponentType, loadedImage, loadedImage);
  }
  else
  {
    handleGenericImageCast<3>(loadedComponentType, loadedImage, loadedImage);
  }

  appData._spMovingImage = loadedImage;

  appData._loadedDimensions = loadedDimensions;
};

void
::map::apps::matchR::loadTargetImage(::map::apps::matchR::ApplicationData& appData)
{
  if (!(appData._targetFileName.empty()))
  {
    map::io::GenericImageReader::GenericOutputImageType::Pointer loadedImage;
    unsigned int loadedDimensions;
    map::io::GenericImageReader::LoadedPixelType loadedPixelType;
    map::io::GenericImageReader::LoadedComponentType loadedComponentType;
    map::io::GenericImageReader::MetaDataDictionaryArrayType loadedMetaDataDictArray;

    map::io::GenericImageReader::Pointer spReader = map::io::GenericImageReader::New();
    spReader->setSeriesReadStyle(appData._seriesReadStyle);
    spReader->setFileName(appData._targetFileName);
    spReader->setUpperSeriesLimit(appData._upperSeriesLimit);

    std::cout << std::endl << "Read target file... ";
    loadedImage = spReader->GetOutput(loadedDimensions, loadedPixelType,
      loadedComponentType);
    loadedMetaDataDictArray = spReader->getMetaDictionaryArray();

    if (loadedImage.IsNotNull())
    {
      std::cout << "done." << std::endl;

      if (appData._detailedOutput)
      {
        std::cout << "Target image info:" << std::endl;
        loadedImage->Print(std::cout);
        std::cout << std::endl;
      }
    }
    else
    {
      mapDefaultExceptionStaticMacro(<<
        " Unable to load target image. File is not existing or has an unsupported format.");
    }


    if (loadedDimensions != appData._loadedDimensions)
    {
      mapDefaultExceptionStaticMacro(<<
        " Unsupported target image. target image dimensions does not match moving image.");
    }

    if (loadedComponentType == 2)
    {
      handleGenericImageCast<2>(loadedComponentType, loadedImage, loadedImage);
    }
    else
    {
      handleGenericImageCast<3>(loadedComponentType, loadedImage, loadedImage);
    }

    appData._spTargetImage = loadedImage;
  }
};

::itk::DataObject::Pointer
loadGenericPointSet(const ::map::core::String& filename, unsigned int dim)
{
  ::itk::DataObject::Pointer result;

  if (!(filename.empty()))
  {
    if (dim == 2)
    {
      typedef ::map::core::continuous::Elements<2>::InternalPointSetType PointSetType;
      result = ::map::utilities::loadLandMarksFromFile<PointSetType>(filename).GetPointer();
    }
    else
    {
      typedef ::map::core::continuous::Elements<2>::InternalPointSetType PointSetType;
      result = ::map::utilities::loadLandMarksFromFile<PointSetType>(filename).GetPointer();
    }
  }

  return result;
};

void
::map::apps::matchR::loadTargetPointSet(::map::apps::matchR::ApplicationData& appData)
{
  if (!(appData._targetPointSetFileName.empty()))
  {
    std::cout << std::endl << "Read target point set file... ";

    appData._genericTargetPointSet = loadGenericPointSet(appData._targetPointSetFileName, appData._loadedDimensions);

    if (appData._genericTargetPointSet.IsNotNull())
    {
      std::cout << "done." << std::endl;
    }
    else
    {
      mapDefaultExceptionStaticMacro(<<
        " Unable to load target point set. File is not existing or has an unsupported format.");
    }
  }
};

void
::map::apps::matchR::loadMovingPointSet(::map::apps::matchR::ApplicationData& appData)
{
  if (!(appData._movingPointSetFileName.empty()))
  {
    std::cout << std::endl << "Read moving point set file... ";

    appData._genericMovingPointSet = loadGenericPointSet(appData._movingPointSetFileName, appData._loadedDimensions);

    if (appData._genericMovingPointSet.IsNotNull())
    {
      std::cout << "done." << std::endl;
    }
    else
    {
      mapDefaultExceptionStaticMacro(<<
        " Unable to load moving point set. File is not existing or has an unsupported format.");
    }
  }
};

void
::map::apps::matchR::loadParameterMap(::map::apps::matchR::ApplicationData& appData)
{
  for (const auto& iter : appData._parameterStrs)
  {
    auto pos = iter.find_first_of("=");
    ::map::core::String name = iter.substr(0, pos);
    ::map::core::String value;

    if (pos != ::map::core::String::npos)
    {
      value = iter.substr(pos + 1);
    }

    appData._parameterMap.insert(std::make_pair(name, value));
  }
};

/**Helper function that converts, if possible */
template <typename TElement>
bool checkNConvert(const ::map::core::String& valueStr, TElement& value)
{
  try
  {
    value = map::core::convert::toValueGeneric<TElement>(valueStr);
    return true;
  }
  catch (...)
  { }

  return false;
};

template <typename TValueType>
map::core::MetaPropertyBase::Pointer
checkCastAndSetProp(const ::map::core::String& valueStr)
{
  bool result = false;
  TValueType value;
  map::core::MetaPropertyBase::Pointer prop;

  if (checkNConvert(valueStr, value))
  {
    prop = map::core::MetaProperty<TValueType>::New(value).GetPointer();
  }
  return prop;
};

::map::core::MetaPropertyBase::Pointer
map::apps::matchR::wrapMetaProperty(const ::map::algorithm::MetaPropertyInfo* pInfo, const ::map::core::String& valueStr)
{
  map::core::MetaPropertyBase::Pointer metaProp;

  if (!pInfo)
  {
    return metaProp;
  }

  if (pInfo->getTypeInfo() == typeid(int)) metaProp = checkCastAndSetProp<int>(valueStr);
  else if (pInfo->getTypeInfo() == typeid(unsigned int)) metaProp = checkCastAndSetProp<unsigned int>(valueStr);
  else if (pInfo->getTypeInfo() == typeid(long)) metaProp = checkCastAndSetProp<long>(valueStr);
  else if (pInfo->getTypeInfo() == typeid(unsigned long)) metaProp = checkCastAndSetProp<unsigned long>(valueStr);
  else if (pInfo->getTypeInfo() == typeid(float)) metaProp = checkCastAndSetProp<float>(valueStr);
  else if (pInfo->getTypeInfo() == typeid(double)) metaProp = checkCastAndSetProp<double>(valueStr);
  else if (pInfo->getTypeInfo() == typeid(::map::core::String))
  {
    metaProp = map::core::MetaProperty<map::core::String>::New(valueStr).GetPointer();
  }

  return metaProp;
};