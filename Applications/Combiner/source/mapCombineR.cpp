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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/source/mapR.cpp $
*/


#include "mapCombineRApplicationData.h"
#include "mapCombineRHelper.h"
#include "mapRegistrationFileReader.h"
#include "mapRegistrationFileWriter.h"
#include "mapConvert.h"

#include "itkStdStreamLogOutput.h"
#include "itkVersion.h"

#ifdef MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER
/* The mapR needs the IO factories to be registered in cases where
   MatchPoint is built without auto registration (e.g. for use in MITK)
   mapR has to add the registration helper manually.*/
#include "itkImageIOFactoryRegisterManager.h"
#endif //MAP_DISABLE_ITK_IO_FACTORY_AUTO_REGISTER

map::apps::combineR::ApplicationData appData;

/** Main function/entry point of the program. When execute use "-?" to get the usage instructions.
 * See CombineRApplicationData::ParseArguments for the codes segement that specifies the instructions.
 * @retval 0 normal exit.
 * @retval 1 showed version info or help.
 * @retval 2 Invalid usage. No arguments given.
 * @retval 3 Invalid usage. Wrong arguments given.
 * @retval 5 Error while loading (or inverting) registrations.
 * @retval 6 Error while combining registrations.
 * @retval 7 Error while saving combined registration.
 */
int main(int argc, char** argv)
{
	int result = 0;

	std::cout << "combineR - Generic registration combination tool for MatchPoint." << std::endl;

	switch (map::apps::combineR::ParseArguments(argc, argv, appData))
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

	::itk::StdStreamLogOutput::Pointer spStreamLogOutput = ::itk::StdStreamLogOutput::New();
	spStreamLogOutput->SetStream(std::cout);
	map::core::Logbook::addAdditionalLogOutput(spStreamLogOutput);

	if (appData._detailedOutput)
	{
		map::core::Logbook::setLogbookToDebugMode();
	}

	std::cout << std::endl << "*******************************************" << std::endl;
  std::vector<map::core::String>::const_iterator fileListPos;
  std::vector<bool>::const_iterator invListPos = appData._inversionList.begin();
  for (fileListPos = appData._regFileList.begin(); fileListPos != appData._regFileList.end(); ++fileListPos, ++invListPos)
  {
    std::cout << "Reg file 1:      " << *fileListPos;
    if (*invListPos)
    {
        std::cout << "(inverted)";
    }
    std::cout << std::endl;
  }
	std::cout << "Output reg file:        " << appData._outputFileName << std::endl;

  //load registrations
  appData._spRegList.clear();
	try
	{
    for (fileListPos = appData._regFileList.begin(); fileListPos != appData._regFileList.end(); ++fileListPos)
    {
      std::cout << std::endl << "read registration file "<< fileListPos - appData._regFileList.begin() +1 << "... ";
      map::io::RegistrationFileReader::Pointer spRegReader = map::io::RegistrationFileReader::New();
      map::io::RegistrationFileReader::LoadedRegistrationPointer spReg = spRegReader->read(*fileListPos);
      appData._spRegList.push_back(spReg);
      std::cout << "done." << std::endl;
    }

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

  //invert registrations
  try
  {
    invListPos = appData._inversionList.begin();

    for (map::apps::combineR::ApplicationData::RegistrationListType::iterator regPos = appData._spRegList.begin(); regPos != appData._spRegList.end(); ++regPos, ++invListPos)
    {
      if (*invListPos)
      {
        std::cout << std::endl << "invert registration #"<< regPos - appData._spRegList.begin() + 1 << "... ";
        map::core::RegistrationBase::Pointer invertedReg = map::apps::combineR::invertRegistration(regPos->GetPointer());
        if (invertedReg.IsNotNull())
        {
          *regPos = invertedReg;
          std::cout << "done." << std::endl;
        }
        else
        {
          std::cerr << "Error!!! Unable to invert registration.unknown Unsupported dimensionality." << std::endl;
          return 5;
        }
      }
    }
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
    std::cerr << "Error!!! unknown error while inverting registration." << std::endl;
    return 5;
  }

  //combine registrations

  map::core::RegistrationBase::Pointer combinedReg = appData._spRegList.front();

  try
  {
     for (map::apps::combineR::ApplicationData::RegistrationListType::iterator regPos = appData._spRegList.begin()+1; regPos != appData._spRegList.end(); ++regPos)
    {
        std::cout << std::endl << "combine registration #"<< regPos - appData._spRegList.begin() + 1 << "... ";

        map::core::RegistrationBase::Pointer interimReg = map::apps::combineR::combineRegistration(combinedReg, regPos->GetPointer());
        if (interimReg.IsNotNull())
        {
          combinedReg = interimReg;
          std::cout << "done." << std::endl;
        }
        else
        {
          std::cerr << "Error!!! Unable to combine registration." << std::endl;
          return 6;
        }
    }
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
    std::cerr << "Error!!! unknown error while inverting registration." << std::endl;
    return 6;
  }


  try
  {
    std::cout << std::endl << "write final combine registration... ";

    if (!map::apps::combineR::writeRegistration(combinedReg, appData._outputFileName))
    {
      std::cerr << "Error!!! Unable to write combined registration." << std::endl;
      return 7;
    }
    else
    {
      std::cout << "done." << std::endl;
    }

  }
  catch (::itk::ExceptionObject& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e << std::endl;
    return 7;
  }
  catch (std::exception& e)
  {
    std::cerr << "Error!!!" << std::endl;
    std::cerr << e.what() << std::endl;
    return 7;
  }
  catch (...)
  {
    std::cerr << "Error!!! unknown error while inverting registration." << std::endl;
    return 7;
  }

	std::cout << std::endl;

	return result;
}
