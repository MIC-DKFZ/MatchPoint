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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/source/mapRApplicationData.cpp $
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
				
        _showVersion = false;
				_showHelp = false;
				_detailedOutput = false;
			}

			unsigned int
			ParseArguments(int argc, char** argv, ApplicationData& appData)
			{
				appData.Reset();

        if (appData._showHelp)
        {
          std::cout << std::endl << "Usage: " << std::endl << std::endl;
          std::cout << "  combiner <Output> [-] <Reg1> [ [+|-] <Reg2> [... [+|-] <RegN>]]" << std::endl << std::endl;
          std::cout << "     Output: File path to the output registration file that will" << std::endl;
          std::cout << "             be generated." << std::endl <<
          std::cout << "     RegN: File path to the n-th registration file that should" << std::endl;
          std::cout << "           be combined. You may invert the registration by" << std::endl;
          std::cout << "           putting \" - \" in front of the reg file. " << std::endl;
          std::cout << "           Putting \" + \" in front of the reg file, is the" << std::endl;
          std::cout << "           same then using no sign at all: the registration" << std::endl;
          std::cout << "           will be combined as it is" << std::endl << std::endl;
          std::cout << " Command-Line Options:" << std::endl << std::endl;
          std::cout << " Example:" << std::endl << std::endl;
          std::cout << " combineR ouput.mapr input1.mapr input2.mapr - input3.mapr" << std::endl << std::endl;
          std::cout <<
            " This will map \"input.png\" by using \"reg.mapr\". The field of view of the output image is defined by \"target.dcm\". The output will be in the directory of the input. The output file name will be \"input_reg.dcm\"."
            << std::endl;
          return 1;
        }
        if (appData._showVersion)
        {
          std::cout << std::endl << "Version: " << MAP_FULL_VERSION_STRING;
          return 1;
        }

        --argc; //skip executable argument;
        ++argv;

        if (!argc)
        {
          std::cerr << "Wrong command line option or insufficient number of arguments." << std::endl;
          std::cerr << "Use one of the following flags for more information:" << std::endl;
          std::cerr << "-? or --help" << std::endl;
          return 3;
        }

        appData._outputFileName = argv[0];
        --argc;
        ++argv;
        bool invertReg = false;

        while(argc)
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

				return 0;
			};

		}
	}
}
