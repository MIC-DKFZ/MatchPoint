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

#define mapCatchAppMacro(rcode, x) \
  catch (::itk::ExceptionObject& e) \
  { \
    std::cerr << "Error!!!" << std::endl; \
    std::cerr << e << std::endl; \
    return rcode; \
  } \
  catch (std::exception& e) \
  { \
    std::cerr << "Error!!!" << std::endl; \
    std::cerr << e.what() << std::endl; \
    return rcode; \
  } \
  catch (...) \
  { \
    std::cerr << x << std::endl; \
    return rcode; \
  }

/** Main entry point for the application.
 * @retval 0 normal exit.
 * @retval 1 showed help or version info.
 * @retval 2 Invalid usage. Missing parameters.
 * @retval 3 Invalid usage. Wrong option usage.
 * @retval 4 Error while loading moving image.
 * @retval 5 Error while loading target image.
 * @retval 6 Error while loading algorithm.
 * @retval 7 Error while loading meta parameter.
 * @retval 8 Error while registering and storing registration.
 * @retval 9 Error while loading moving point set.
 * @retval 10 Error while loading target point set.
 * @retval 11 Error while loading moving mask image.
 * @retval 12 Error while loading target mask image.
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
  std::cout << "Target mask file:   ";
  if (appData._targetMaskFileName.empty())
  {
    std::cout << "disabled" << std::endl;
  }
  else
  {
    std::cout << appData._targetMaskFileName << std::endl;
  }
  std::cout << "Moving point set file:   ";
  if (appData._movingPointSetFileName.empty())
  {
    std::cout << "disabled" << std::endl;
  }
  else
  {
    std::cout << appData._movingPointSetFileName << std::endl;
  }
  std::cout << "Target point set file:   ";
  if (appData._targetPointSetFileName.empty())
  {
    std::cout << "disabled" << std::endl;
  }
  else
  {
    std::cout << appData._targetPointSetFileName << std::endl;
  }

  std::cout << "Series read style: " << appData._seriesReadStyleStr << std::endl;

 
  try
  {
    map::apps::matchR::loadMovingImage(appData);
  }
  mapCatchAppMacro(4, "Error!!! unknown error while reading moving image.")

  try
  {
    map::apps::matchR::loadTargetImage(appData);
  }
  mapCatchAppMacro(5, "Error!!! unknown error while reading target image.")

  try
  {
    map::apps::matchR::loadAlgorithm(appData);
  }
  mapCatchAppMacro(6, "Error!!! unknown error while reading registration file.")

  try
  {
    map::apps::matchR::loadTargetPointSet(appData);
  }
  mapCatchAppMacro(9, "Error!!! unknown error while reading target point set.")
    
  try
  {
    map::apps::matchR::loadMovingPointSet(appData);
  }
  mapCatchAppMacro(10, "Error!!! unknown error while reading moving point set.")

    try
  {
    map::apps::matchR::loadMovingMask(appData);
  }
  mapCatchAppMacro(11, "Error!!! unknown error while reading moving mask.")

    try
  {
    map::apps::matchR::loadTargetMask(appData);
  }
  mapCatchAppMacro(12, "Error!!! unknown error while reading target mask.")

  try
  {
    map::apps::matchR::loadParameterMap(appData);
  }
  mapCatchAppMacro(7, "Error!!! unknown error while parsing the meta parameters.")
    
  try
  {
    if (appData._loadedDimensions == 2)
    {
      map::apps::matchR::ProcessingLogic<2> logic(appData);
      logic.processData();
    }
    else if (appData._loadedDimensions == 3)
    {
      map::apps::matchR::ProcessingLogic<3> logic(appData);
      logic.processData();
    }
  }
  mapCatchAppMacro(8, "Error!!! unknown error while mapping and writing image.")

  std::cout << std::endl;

  return result;
}
