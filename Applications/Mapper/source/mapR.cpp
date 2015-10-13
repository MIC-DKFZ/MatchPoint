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

#include "mapRApplicationData.h"
#include "mapRHelper.h"

#ifdef MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER
/* The mapR needs the IO factories to be registered in cases where
MatchPoint is built without auto registration (e.g. for use in MITK)
mapR has to add the registration helper manually.*/
#include "itkImageIOFactoryRegisterManager.h"
#endif //MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER

map::apps::mapR::ApplicationData appData;

void onMAPEvent(::itk::Object*, const itk::EventObject& event, void*)
{
  std::cout << " > > > ";
  event.Print(std::cout);
  std::cout << std::endl;
}

/** Main entry point for the application.
 * @retval 0 normal exit.
 * @retval 1 showed help or version info.
 * @retval 2 Invalid usage. Missing parameters.
 * @retval 3 Invalid usage. Wrong option usage.
 * @retval 4 Error while loading input image.
 * @retval 5 Error while loading registration.
 * @retval 6 Error while loading reference image.
 * @retval 9 Error while mapping or writing result image.
 */
int main(int argc, char** argv)
{
  int result = 0;

  std::cout << "mapR - Generic image mapping tool for MatchPoint." << std::endl;

  switch (appData.ParseArguments(argc, argv))
  {
    case 1:
    {
      //showed version or help info. Done.
      return 1;
    }

    case 2:
    {
      std::cerr << "Missing Parameters. Use one of the following flags for more information:" <<
                std::endl;
      std::cerr << "-? or --help" << std::endl;
      return 2;
    }

    case 3:
    {
      //wrong option usage.
      return 3;
    }
  }

  if (appData._fileCount < 1)
  {
    std::cerr << "Missing Parameters. Use one of the following flags for more information:" <<
              std::endl;
    std::cerr << "-? or --help" << std::endl;
    return 2;
  }

  ::itk::StdStreamLogOutput::Pointer spStreamLogOutput = ::itk::StdStreamLogOutput::New();
  spStreamLogOutput->SetStream(std::cout);
  map::core::Logbook::addAdditionalLogOutput(spStreamLogOutput);

  if (appData._detailedOutput)
  {
    map::core::Logbook::setLogbookToDebugMode();
  }

  std::cout << std::endl << "*******************************************" << std::endl;
  std::cout << "Input file:        " << appData._inputFileName << std::endl;
  std::cout << "Registration file: ";

  if (appData._regFileName.empty())
  {
    std::cout << "unspecified -> Identity transform will be used" << std::endl;
  }
  else
  {
    std::cout << appData._regFileName << std::endl;
  }

  std::cout << "Series read style: " << appData._seriesReadStyleStr << std::endl;
  std::cout << "Series write style: " << appData._seriesWriteStyleStr << std::endl;
  std::cout << "Interpolation style: ";
  std::cout << std::endl << "*******************************************" << std::endl;
  std::cout << "Input file:        " << appData._inputFileName << std::endl;
  std::cout << "Registration file: " << appData._regFileName << std::endl;
  std::cout << "Series read style: " << appData._seriesReadStyleStr << std::endl;
  std::cout << "Series write style: " << appData._seriesWriteStyleStr << std::endl;
  std::cout << "Interpolation style: ";

  if (appData._interpolatorType == map::apps::mapR::ImageMappingInterpolator::Unkown)
  {
    std::cout <<
              "unknown interpolator defined by user. Abort mapping. User defined interpolator string: " <<
              appData._interpolatorTypeStr << std::endl;
    return 3;
  }
  else
  {
    std::cout << appData._interpolatorType << "(" << appData._interpolatorTypeStr << ")" << std::endl;
  }

  if (!(appData._refFileName.empty()))
  {
    std::cout << "Template file:     " << appData._refFileName << std::endl;
  }

  map::apps::mapR::LoadingLogic loadingLogic(appData);

  try
  {
    loadingLogic.loadInputImage();
  }
  catch (::itk::ExceptionObject& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e << std::endl;
    return 4;
  }
  catch (std::exception& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e.what() << std::endl;
    return 4;
  }
  catch (...)
  {
    std::cerr << "Error!!! unknown error while reading input image." << std::endl;
    return 4;
  }

  try
  {
    loadingLogic.loadRegistration();
  }
  catch (::itk::ExceptionObject& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e << std::endl;
    return 5;
  }
  catch (std::exception& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e.what() << std::endl;
    return 5;
  }
  catch (...)
  {
    std::cerr << "Error!!! unknown error while reading registration file." << std::endl;
    return 5;
  }

  try
  {
    loadingLogic.loadReferenceImage();
  }
  catch (::itk::ExceptionObject& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e << std::endl;
    return 6;
  }
  catch (std::exception& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e.what() << std::endl;
    return 6;
  }
  catch (...)
  {
    std::cerr << "Error!!! unknown error while reading template image." << std::endl;
    return 6;
  }

  try
  {
    if (appData._loadedDimensions == 2)
    {
      map::apps::mapR::handleGenericImage<2, map::apps::mapR::ProcessingLogic>(appData);
    }
    else if (appData._loadedDimensions == 3)
    {
      map::apps::mapR::handleGenericImage<3, map::apps::mapR::ProcessingLogic>(appData);
    }
  }
  catch (::itk::ExceptionObject& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e << std::endl;
    return 9;
  }
  catch (std::exception& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e.what() << std::endl;
    return 9;
  }
  catch (...)
  {
    std::cerr << "Error!!! unknown error while mapping and writing image." << std::endl;
    return 9;
  }

  std::cout << std::endl;

  return result;
}
