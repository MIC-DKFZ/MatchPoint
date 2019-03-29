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


#include "mapCombineRApplicationData.h"
#include "mapConfigure.h"

#include "itksys/SystemTools.hxx"

namespace map
{
  namespace apps
  {
    namespace combineR
    {

      int unknown_argument(const char* argument, void* call_data)
      {
        std::cout << "Got unknown argument: \"" << argument << "\"" << std::endl;
        return 0;
      }

      ApplicationData::
        ApplicationData()
      {
        this->Reset();
      }

      void
        ApplicationData::
        Reset()
      {
        _spRegList.clear();
        _regFileList.clear();
        _inversionList.clear();

        _outputFileName = "";
        _logFileName = "";

        _showVersion = false;
        _showHelp = false;
        _detailedOutput = false;
      }

      bool containsHelpTag(int argc, char** argv)
      {
        while(argc != 0)
        {
          map::core::String value = argv[0];

          if (value == "--help" || value == "-h" || value == "-?")
          {
            return true;
          }

          ++argv;
          --argc;
        }
        return false;
      }

      bool containsVersionTag(int argc, char** argv)
      {
        while(argc != 0)
        {
          map::core::String value = argv[0];

          if (value == "--version" || value == "-v")
          {
            return true;
          }

          ++argv;
          --argc;
        }
        return false;
      }

      unsigned int
        ParseArguments(int argc, char** argv, ApplicationData& appData)
      {
        appData.Reset();

        appData._showHelp = containsHelpTag(argc,argv);
        appData._showVersion = containsVersionTag(argc,argv);

        if (appData._showHelp)
        {
          std::cout << std::endl << "Usage: " << std::endl << std::endl;
          std::cout << " combineR <Output> [-] <Reg1> [ [+|-] <Reg2> [... [+|-] <RegN>]]" << std::endl << std::endl;
          std::cout << "     Output: File path to the output registration file that will" << std::endl;
          std::cout << "             be generated." << std::endl;
          std::cout << "     RegN: File path to the n-th registration file that should" << std::endl;
          std::cout << "           be combined. You may invert the registration by" << std::endl;
          std::cout << "           putting \" - \" in front of the reg file. " << std::endl;
          std::cout << "           Putting \" + \" in front of the reg file, is the" << std::endl;
          std::cout << "           same then using no sign at all: the registration" << std::endl;
          std::cout << "           will be combined as it is" << std::endl << std::endl;
          std::cout << " Command-Line Options:" << std::endl << std::endl;
          std::cout << "    -h:        Display this help" << std::endl;
          std::cout << "    --help:    Display this help" << std::endl;
          std::cout << "    -?:        Display this help" << std::endl;
          std::cout << "    -v:        Show version information" << std::endl;
          std::cout << "    --version: Show version information" << std::endl<< std::endl;
          std::cout << " Example:" << std::endl << std::endl;
          std::cout << " combineR ouput.mapr input1.mapr input2.mapr - input3.mapr" << std::endl << std::endl;
          std::cout << R"( This will combine "input1.mapr", "input2.mapr" and the inverted "input3.mapr". The output file name will be "output.mapr".)"
            << std::endl;
          return 1;
        }
        if (appData._showVersion)
        {
          std::cout << std::endl << "Version: " << MAP_FULL_VERSION_STRING << std::endl;
          return 1;
        }

        --argc; //skip executable argument;
        ++argv;

        if (argc == 0)
        {
          std::cerr << "Wrong command line: insufficient number of arguments." << std::endl;
          std::cerr << "Use one of the following flags for more information:" << std::endl;
          std::cerr << "-? or --help" << std::endl;
          return 2;
        }

        appData._outputFileName = argv[0];
        --argc;
        ++argv;
        bool invertReg = false;

        while(argc != 0)
        {
          map::core::String value = argv[0];

          if (value == "-")
          {
            invertReg = true;
          }
          else if (value != "+") //per default it is always plus, so ignore "+"
          {         
            appData._regFileList.push_back(value);
            appData._inversionList.push_back(invertReg);
            invertReg = false;
          }
          --argc;
          ++argv;
        }

        if (appData._regFileList.empty())
        {
          std::cerr << "Wrong command line option or insufficient number of arguments." << std::endl;
          std::cerr << "Use one of the following flags for more information:" << std::endl;
          std::cerr << "-? or --help" << std::endl;
          return 3;
        }

        return 0;
      };

    }  // namespace combineR
  }  // namespace apps
}  // namespace map
