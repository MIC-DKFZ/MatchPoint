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

#include <mapImageRegistrationAlgorithmInterface.h>
#include <mapRegistrationAlgorithmInterface.h>
#include <mapIterativeAlgorithmInterface.h>
#include <mapMultiResRegistrationAlgorithmInterface.h>
#include <mapAlgorithmEvents.h>
#include <mapAlgorithmWrapperEvent.h>

template <unsigned int IDimension, typename TPixelType>
void handleImageCast(const ::map::io::GenericImageReader::GenericOutputImageType* inputImage, ::map::io::GenericImageReader::GenericOutputImageType::Pointer& castedImage)
{
  typename ::itk::Image<TPixelType, IDimension> InputImageType;
  typename ::map::core::discrete::Elements<IDimension>::InternalImageType CastedImageType;
  typename ::itk::CastImageFilter<InputImageType, CastedImageType> FilterType;

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
loadAlgorithm(::map::apps::matchR::ApplicationData& appData)
{
  map::deployment::RegistrationAlgorithmBasePointer spAlgorithmBase = NULL;

  std::cout << "Load registration algorithm..." << std::endl;

  map::deployment::DLLHandle::Pointer spHandle = NULL;

  spHandle = map::deployment::openDeploymentDLL(appData._algorithmFileName);

  if (spHandle.IsNull())
  {
    mapDefaultExceptionStaticMacro(<<
      "Cannot open deployed registration algorithm file.");
  }

  std::cout << "Algorithm information: " << std::endl;
  spHandle->getAlgorithmUID().Print(std::cout, 2);

  //Now load the algorthm from DLL
  spAlgorithmBase = map::deployment::getRegistrationAlgorithm(spHandle);

  std::cout << "... algorithm is loaded" << std::endl;

  if (spAlgorithmBase.IsNotNull())
  {
    std::cout << "... done" << std::endl;

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
loadMovingImage(::map::apps::matchR::ApplicationData& appData)
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

  std::cout << std::endl << "read moving image file... ";
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
loadTargetImage(::map::apps::matchR::ApplicationData& appData)
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

    std::cout << std::endl << "read target file... ";
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

void ::map::apps::matchR::onMapAlgorithmEvent(::itk::Object*, const itk::EventObject& event)
{
  const map::events::AlgorithmEvent* pAlgEvent = dynamic_cast<const map::events::AlgorithmEvent*>
    (&event);
  const map::events::AlgorithmIterationEvent* pIterationEvent =
    dynamic_cast<const map::events::AlgorithmIterationEvent*>(&event);
  const map::events::AlgorithmWrapperEvent* pWrapEvent =
    dynamic_cast<const map::events::AlgorithmWrapperEvent*>(&event);
  const map::events::AlgorithmResolutionLevelEvent* pLevelEvent =
    dynamic_cast<const map::events::AlgorithmResolutionLevelEvent*>(&event);

  const map::events::InitializingAlgorithmEvent* pInitEvent =
    dynamic_cast<const map::events::InitializingAlgorithmEvent*>(&event);
  const map::events::StartingAlgorithmEvent* pStartEvent =
    dynamic_cast<const map::events::StartingAlgorithmEvent*>(&event);
  const map::events::StoppingAlgorithmEvent* pStoppingEvent =
    dynamic_cast<const map::events::StoppingAlgorithmEvent*>(&event);
  const map::events::StoppedAlgorithmEvent* pStoppedEvent =
    dynamic_cast<const map::events::StoppedAlgorithmEvent*>(&event);
  const map::events::FinalizingAlgorithmEvent* pFinalizingEvent =
    dynamic_cast<const map::events::FinalizingAlgorithmEvent*>(&event);
  const map::events::FinalizedAlgorithmEvent* pFinalizedEvent =
    dynamic_cast<const map::events::FinalizedAlgorithmEvent*>(&event);

  if (pInitEvent)
  {
    std::cout <<"Initializing algorithm ..."<< std::endl;
  }
  else if (pStartEvent)
  {
    std::cout <<"Starting algorithm ..."<< std::endl;
  }
  else if (pStoppingEvent)
  {
    std::cout <<"Stopping algorithm ..."<< std::endl;
  }
  else if (pStoppedEvent)
  {
    std::cout <<"Stopped algorithm ..."<< std::endl;

    if (!pStoppedEvent->getComment().empty())
    {
      std::cout << "Stopping condition: "<< pStoppedEvent->getComment() << std::endl;
    }
  }
  else if (pFinalizingEvent)
  {
    std::cout <<"Finalizing algorithm and results ..."<< std::endl;
  }
  else if (pFinalizedEvent)
  {
    std::cout <<"Finalized algorithm ..."<< std::endl;
  }
  else if (pIterationEvent)
  {
    typedef map::algorithm::facet::IterativeAlgorithmInterface IIterativeAlgorithm;

    const IIterativeAlgorithm* pIterative = dynamic_cast<const IIterativeAlgorithm*>
      (appDthis->m_spLoadedAlgorithm.GetPointer());

    IIterativeAlgorithm::IterationCountType count = 0;

    std::cout << "[";
    if (pIterative && pIterative->hasIterationCount())
    {
      std::cout << pIterative->getCurrentIteration();
    }
    std::cout << "] " << pIterationEvent->getComment() << std::endl;
  }
  else if (pLevelEvent)
  {
    typedef map::algorithm::facet::MultiResRegistrationAlgorithmInterface IMultiResAlgorithm;
    const IMultiResAlgorithm* pResAlg = dynamic_cast<const IMultiResAlgorithm*>
      (this->m_spLoadedAlgorithm.GetPointer());

    map::algorithm::facet::MultiResRegistrationAlgorithmInterface::ResolutionLevelCountType count = 0;

    std::cout << std::endl << "**************************************" << std::endl;
    std::cout << "New resolution level";
    if (pResAlg && pResAlg->hasLevelCount())
    {
      std::cout << "[# " <<pResAlg->getCurrentLevel() + 1 <<"]";
    }
    std::cout << std::endl << "**************************************" << std::endl << std::endl;
  }
  else if (pAlgEvent && !pWrapEvent)
  {
    std::cout << pAlgEvent->getComment() << std::endl;
  }
}
