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
#include "itkCastImageFilter.h"



template <typename TPixelType, unsigned int IDimension>
void handleImageCast(const ::map::io::GenericImageReader::GenericOutputImageType* inputImage, ::map::io::GenericImageReader::GenericOutputImageType::Pointer& castedImage)
{
  typedef ::itk::Image<TPixelType, IDimension> InputImageType;
  typedef ::map::core::discrete::Elements<IDimension>::InternalImageType CastedImageType;
  typedef ::itk::CastImageFilter<InputImageType, CastedImageType> FilterType;

  const InputImageType* input = dynamic_cast<const InputImageType*>(inputImage);

  FilterType::Pointer caster = FilterType::New();

  caster->SetInput(input);
  caster->Update();
  CastedImageType::Pointer casted = caster->GetOutput();

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

void
::map::apps::matchR::loadParameterMap(::map::apps::matchR::ApplicationData& appData)
{
};

//
//template <typename TValueType>
//bool
//QmitkMAPAlgorithmModel::
//CheckCastAndSetProp(const map::algorithm::MetaPropertyInfo* pInfo, const QVariant& value)
//{
//  bool result = false;
//  if (pInfo->getTypeInfo() == typeid(TValueType) && value.canConvert<TValueType>())
//  {
//    /**@TODO: Not save, because canConvert may say true but the actual value is not really convertible (e.g. string to int for the value "a")*/
//    TValueType val = value.value<TValueType>();
//    map::core::MetaPropertyBase::Pointer spMetaProp = map::core::MetaProperty<TValueType>::New(val).GetPointer();
//
//    result = m_pMetaInterface->setProperty(pInfo, spMetaProp);
//  }
//  return result;
//};
//
//bool
//QmitkMAPAlgorithmModel::
//SetPropertyValue(const map::algorithm::MetaPropertyInfo* pInfo, const QVariant& value)
//{
//  if (!m_pMetaInterface)
//  {
//    return false;
//  }
//
//  bool result = CheckCastAndSetProp<bool>(pInfo, value);
//
//  if (!result) result = CheckCastAndSetProp<int>(pInfo, value);
//  if (!result) result = CheckCastAndSetProp<unsigned int>(pInfo, value);
//  if (!result) result = CheckCastAndSetProp<long>(pInfo, value);
//  if (!result) result = CheckCastAndSetProp<unsigned long>(pInfo, value);
//  if (!result) result = CheckCastAndSetProp<float>(pInfo, value);
//  if (!result) result = CheckCastAndSetProp<double>(pInfo, value);
//  if (!result  && pInfo->getTypeInfo() == typeid(map::core::String))
//  {
//    map::core::String val = value.toString().toStdString();
//    map::core::MetaPropertyBase::Pointer spMetaProp = map::core::MetaProperty<map::core::String>::New(val).GetPointer();
//
//    result = m_pMetaInterface->setProperty(pInfo, spMetaProp);
//  };
//
//  return result;
//};