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
// @version $Revision: 1371 $ (last changed revision)
// @date    $Date: 2016-05-23 17:56:37 +0200 (Mo, 23 Mai 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/source/matchR.cpp $
*/

#include "matchRApplicationData.h"
#include "matchRHelper.h"

#ifdef MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER
/* The matchR needs the IO factories to be registered in cases where
MatchPoint is built without auto registration (e.g. for use in MITK)
matchR has to add the registration helper manually.*/
#include "itkImageIOFactoryRegisterManager.h"
#endif //MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER

map::apps::matchR::ApplicationData appData;

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

  std::cout << "matchR - Generic light weight image registration tool for MatchPoint." << std::endl;

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

  map::core::Logbook::setDefaultLogFileName(appData._logFileName);
  ::itk::StdStreamLogOutput::Pointer spStreamLogOutput = ::itk::StdStreamLogOutput::New();
  spStreamLogOutput->SetStream(std::cout);
  map::core::Logbook::addAdditionalLogOutput(spStreamLogOutput);

  if (appData._detailedOutput)
  {
    map::core::Logbook::setLogbookToDebugMode();
  }

  std::cout << std::endl << "*******************************************" << std::endl;
  std::cout << "Moving file:        " << appData._movingFileName << std::endl;
  std::cout << "Target file:        " << appData._targetFileName << std::endl;
  std::cout << "Algorithm location: " << appData._algorithmFileName << std::endl;
  std::cout << "Moving mask file:   ";
  if (appData._movingMaskFileName.empty())
  {
    std::cout << "disabled" << std::endl;
  }
  else
  {
    std::cout << appData._movingMaskFileName << std::endl;
  }
  if (appData._targetMaskFileName.empty())
  {
    std::cout << "disabled" << std::endl;
  }
  else
  {
    std::cout << appData._targetMaskFileName << std::endl;
  }

  std::cout << "Series read style: " << appData._seriesReadStyleStr << std::endl;

 
  try
  {
    map::apps::matchR::loadMovingImage(appData);
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
    std::cerr << "Error!!! unknown error while reading moving image." << std::endl;
    return 4;
  }

  try
  {
    map::apps::matchR::loadTargetImage(appData);
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
    std::cerr << "Error!!! unknown error while reading target image." << std::endl;
    return 6;
  }

  try
  {
    map::apps::matchR::loadAlgorithm(appData);
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
    if (appData._loadedDimensions == 2)
    {
      map::apps::matchR::handleGenericImage<2, map::apps::matchR::ProcessingLogic>(appData);
    }
    else if (appData._loadedDimensions == 3)
    {
      map::apps::matchR::handleGenericImage<3, map::apps::matchR::ProcessingLogic>(appData);
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
