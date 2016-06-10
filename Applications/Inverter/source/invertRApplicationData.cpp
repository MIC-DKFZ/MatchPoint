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
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/source/invertRApplicationData.cpp $
*/


#include "invertRApplicationData.h"
#include "mapConfigure.h"

#include "itksys/SystemTools.hxx"

namespace map
{
	namespace apps
	{
		namespace invertR
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
				_outputFileName = "";
				_regFileName = "";
				_refFileName = "";
        _logFileName = "";

				_showVersion = false;
				_showHelp = false;
				_detailedOutput = false;
        _ensureDirectMapping = false;
        _ensureInverseMapping = false;

				_seriesReadStyle = io::ImageSeriesReadStyle::Default;
				_seriesReadStyleStr = "default";

				_fileCount = 0;
			}

			unsigned int
			ApplicationData::
			ParseArguments(int argc, char** argv)
			{
				this->Reset();

				if (argc > 1)
				{
					::map::core::String dummyArg = argv[1];

					if (dummyArg.substr(0, 1) != "-")
					{
						//argument is the reg file. Store the argument and move to next position before parsing starts.
						_regFileName = dummyArg;
						++_fileCount;
						--argc;
						++argv;
					}
				}

				cmdParser.Initialize(argc, argv);

				cmdParser.SetUnknownArgumentCallback(unknown_argument);

				cmdParser.AddArgument("--output", itksys::CommandLineArguments::SPACE_ARGUMENT, &_outputFileName,
				                      "Specifies name and location of the output file. Default is the location of the input file and a name constructed from the name of the input file and the registration file.");
				cmdParser.AddArgument("-o", itksys::CommandLineArguments::SPACE_ARGUMENT, &_outputFileName,
				                      "Specifies name and location of the output file. Default is the location of the input file and a name constructed from the name of the input file and the registration file.");
				cmdParser.AddArgument("--FOVtemplate", itksys::CommandLineArguments::SPACE_ARGUMENT, &_refFileName,
				                      "Specifies name and location of the file that serves as template for the target field of view. Thus this file defines spacing, size, origin and orientation of the output image. Default is that the input image is used as template.");
				cmdParser.AddArgument("-t", itksys::CommandLineArguments::SPACE_ARGUMENT, &_refFileName,
				                      "Specifies name and location of the file that serves as template for the target field of view. Thus this file defines spacing, size, origin and orientation of the output image. Default is that the input image is used as template.");

				cmdParser.AddArgument("-v", itksys::CommandLineArguments::NO_ARGUMENT, &_showVersion,
				                      "Shows the version of the program.");

				cmdParser.AddArgument("-d", itksys::CommandLineArguments::NO_ARGUMENT, &_ensureDirectMapping,
				                      "Ensure that direct mapping is possible with the inverted new registration. This might cause the inverse kernel to be inverted numerically.");
        cmdParser.AddArgument("-directMapping", itksys::CommandLineArguments::NO_ARGUMENT, &_ensureDirectMapping,
          "Ensure that direct mapping is possible with the inverted new registration. This might cause the inverse kernel to be inverted numerically.");

        cmdParser.AddArgument("-i", itksys::CommandLineArguments::NO_ARGUMENT, &_ensureInverseMapping,
          "Ensure that inverse mapping is possible with the inverted new registration. This might cause the direct kernel to be inverted numerically.");
        cmdParser.AddArgument("-inverseMapping", itksys::CommandLineArguments::NO_ARGUMENT, &_ensureInverseMapping,
          "Ensure that inverse mapping is possible with the inverted new registration. This might cause the direct kernel to be inverted numerically.");

        cmdParser.AddArgument("--details", itksys::CommandLineArguments::NO_ARGUMENT, &_detailedOutput,
				                      "Program has a more detailed (debug) output.");

				cmdParser.AddArgument("-h", itksys::CommandLineArguments::NO_ARGUMENT, &_showHelp,
				                      "Shows this help information for the program.");
				cmdParser.AddArgument("--help", itksys::CommandLineArguments::NO_ARGUMENT, &_showHelp,
				                      "Shows this help information for the program.");
				cmdParser.AddArgument("-?", itksys::CommandLineArguments::NO_ARGUMENT, &_showHelp,
				                      "Shows this help information for the program.");

				cmdParser.AddArgument("-r", itksys::CommandLineArguments::SPACE_ARGUMENT, &_seriesReadStyleStr,
				                      "Defines the read style for input and template image. Valid values are: 'default': like dicom but does not force series output; 'dicom': in current version it is equal to use 'gdcm'; 'gdcm': uses the dicom series file names reader and GDCM to load the images; 'none': only the specified file will be read; 'numeric': uses the numeric series file names reader and forces an output as series of 2D images.");
				cmdParser.AddArgument("--seriesReader", itksys::CommandLineArguments::SPACE_ARGUMENT,
				                      &_seriesReadStyleStr,
				                      "Defines the read style for input and template image. Valid values are: 'default': like dicom but does not force series output; 'dicom': in current version it is equal to use 'gdcm'; 'gdcm': uses the dicom series file names reader and GDCM to load the images; 'none': only the specified file will be read; 'numeric': uses the numeric series file names reader and forces an output as series of 2D images.");

        cmdParser.AddArgument("--log", itksys::CommandLineArguments::SPACE_ARGUMENT, &_logFileName,
            "Specifies name and location of the log file. Default (flag not set) is that no log file is written.");
        cmdParser.AddArgument("-l", itksys::CommandLineArguments::SPACE_ARGUMENT, &_logFileName,
            "Specifies name and location of the log file. Default (flag not set) is that no log file is written.");


        if (!cmdParser.Parse())
				{
					std::cerr << "Wrong command line option or insufficient number of arguments." << std::endl;
					std::cerr << "The last correct argument was: " << argv[cmdParser.GetLastArgument()] << std::endl <<
					          "Use one of the following flags for more information:" << std::endl;
					std::cerr << "-? or --help" << std::endl;
					return 3;
				};

				if (_showHelp)
				{
					std::cout << std::endl << "Usage: " << std::endl << std::endl;
					std::cout << "  invertR <Reg> [options]" << std::endl << std::endl;
					std::cout << "     Reg: File path to the registration file that specifies" << std::endl;
					std::cout << "          the registration that should be inverted." << std::endl;
					std::cout << "Command-Line Options:" << std::endl << std::endl;
					std::cout << cmdParser.GetHelp() << std::endl << std::endl;
					std::cout << " Example:" << std::endl << std::endl;
					std::cout << " invertR reg.mapr" << std::endl << std::endl;
					std::cout <<
					          " This will invert \"reg.mapr\". The output will be in the directory of the input. The output file name will be \"reg_inverted.mapr\"."
					          << std::endl;
					return 1;
				}

				if (_showVersion)
				{
					std::cout << std::endl << "Version: " << MAP_FULL_VERSION_STRING;
					return 1;
				}

				if (_fileCount < 1)
				{
					return 2;
				}

				if (_outputFileName.empty())
				{
          ::map::core::String path = core::FileDispatch::getPath(_regFileName);
					::map::core::String regName = core::FileDispatch::getName(_regFileName);

					_outputFileName = core::FileDispatch::createFullPath(path, regName + "_inverted.mapr");
				}

				if (_seriesReadStyleStr == "none")
				{
					_seriesReadStyle =  io::ImageSeriesReadStyle::None;
				}
				else if (_seriesReadStyleStr == "dicom")
				{
					_seriesReadStyle =  io::ImageSeriesReadStyle::Dicom;
				}
				else if (_seriesReadStyleStr == "numeric")
				{
					_seriesReadStyle =  io::ImageSeriesReadStyle::Numeric;
				}
				else if (_seriesReadStyleStr == "gdcm")
				{
					_seriesReadStyle =  io::ImageSeriesReadStyle::GDCM;
				}

				return 0;
			};

		}
	}
}
