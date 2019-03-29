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
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/source/matchRApplicationData.cpp $
*/


#include "matchRApplicationData.h"
#include "mapConfigure.h"

#include "itksys/SystemTools.hxx"

namespace map
{
	namespace apps
	{
		namespace matchR
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
        _algorithmFileName = "";
				_movingFileName = "";
        _movingMaskFileName = "";
				_targetFileName = "";
        _targetMaskFileName = "";
        _outputFileName = "";
        _logFileName = "";
        _targetPointSetFileName = "";
        _movingPointSetFileName = "";

        _parameterStrs.clear();
        _parameterMap.clear();

				_showVersion = false;
				_showHelp = false;
				_detailedOutput = false;

				_upperSeriesLimit = 0;
				_loadedDimensions = 1;
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
						//argument is the moving file. Store the argument and move to next position.
						_movingFileName = dummyArg;
						++_fileCount;
						--argc;
						++argv;
					}
				}

        if (argc > 1)
        {
          ::map::core::String dummyArg = argv[1];

          if (dummyArg.substr(0, 1) != "-")
          {
            //argument is the target file. Store the argument and move to next position.
            _targetFileName = dummyArg;
            ++_fileCount;
            --argc;
            ++argv;
          }
        }

				if (argc > 1)
				{
					::map::core::String dummyArg = argv[1];

					if (dummyArg.substr(0, 1) != "-")
					{
						//argument is the algorithm. Store the argument and move to next position before parsing starts.
            _algorithmFileName = dummyArg;
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
				cmdParser.AddArgument("--target-mask", itksys::CommandLineArguments::SPACE_ARGUMENT, &_targetMaskFileName,
				                      "Specifies name and location of the file that specifies a target mask image.");
        cmdParser.AddArgument("-t", itksys::CommandLineArguments::SPACE_ARGUMENT, &_targetMaskFileName,
          "Specifies name and location of the file that specifies a target mask image.");
        cmdParser.AddArgument("--moving-mask", itksys::CommandLineArguments::SPACE_ARGUMENT, &_movingMaskFileName,
          "Specifies name and location of the file that specifies a moving mask image.");
        cmdParser.AddArgument("-m", itksys::CommandLineArguments::SPACE_ARGUMENT, &_movingMaskFileName,
          "Specifies name and location of the file that specifies a moving mask image.");

        cmdParser.AddArgument("--target-pointset", itksys::CommandLineArguments::SPACE_ARGUMENT, &_targetPointSetFileName,
          "Specifies name and location of the file that specifies the optional target point set.");
        cmdParser.AddArgument("--moving-pointset", itksys::CommandLineArguments::SPACE_ARGUMENT, &_movingPointSetFileName,
          "Specifies name and location of the file that specifies the optional moving point set.");

        cmdParser.AddArgument("--parameters", itksys::CommandLineArguments::MULTI_ARGUMENT, &_parameterStrs,
          R"(Allows to define meta properties that are passed to the algorithm. Each value defines a meta property and its value(s). The structure of the value string must be <PropertyName>=<Value>; e.g. -p "myProp=10". If you want to pass vector values (e.g. algorithm scales) seperate the value by space; e.g. -p "Scales= 1 2 3 10".)");
        cmdParser.AddArgument("-p", itksys::CommandLineArguments::MULTI_ARGUMENT, &_parameterStrs,
          R"(Allows to define meta properties that are passed to the algorithm. Each value defines a meta property and its value(s). The structure of the value string must be <PropertyName>=<Value>; e.g. -p "myProp=10". If you want to pass vector values (e.g. algorithm scales) seperate the value by space; e.g. -p "Scales= 1 2 3 10".)");

				cmdParser.AddArgument("-v", itksys::CommandLineArguments::NO_ARGUMENT, &_showVersion,
				                      "Shows the version of the program.");

				cmdParser.AddArgument("-d", itksys::CommandLineArguments::NO_ARGUMENT, &_detailedOutput,
				                      "Program has a more detailed (debug) output.");
				cmdParser.AddArgument("--details", itksys::CommandLineArguments::NO_ARGUMENT, &_detailedOutput,
				                      "Program has a more detailed (debug) output.");

				cmdParser.AddArgument("-h", itksys::CommandLineArguments::NO_ARGUMENT, &_showHelp,
				                      "Shows this help information for the program.");
				cmdParser.AddArgument("--help", itksys::CommandLineArguments::NO_ARGUMENT, &_showHelp,
				                      "Shows this help information for the program.");
				cmdParser.AddArgument("-?", itksys::CommandLineArguments::NO_ARGUMENT, &_showHelp,
				                      "Shows this help information for the program.");

				cmdParser.AddArgument("-u", itksys::CommandLineArguments::SPACE_ARGUMENT, &_upperSeriesLimit,
				                      "Only relevant in combination with numeric read style. Defines the upper index of the numeric image stack.");
				cmdParser.AddArgument("--upperSeriesLimit", itksys::CommandLineArguments::SPACE_ARGUMENT,
				                      &_upperSeriesLimit,
				                      "Only relevant in combination with numeric read style. Defines the upper index of the numeric image stack.");

				cmdParser.AddArgument("-r", itksys::CommandLineArguments::SPACE_ARGUMENT, &_seriesReadStyleStr,
				                      "Defines the read style for input and template image. Valid values are: 'default': like dicom but does not force series output; 'dicom': in current version it is equal to use 'gdcm'; 'gdcm': uses the dicom series file names reader and GDCM to load the images; 'none': only the specified file will be read; 'numeric': uses the numeric series file names reader and forces an output as series of 2D images.");
				cmdParser.AddArgument("--seriesReader", itksys::CommandLineArguments::SPACE_ARGUMENT,
				                      &_seriesReadStyleStr,
				                      "Defines the read style for input and template image. Valid values are: 'default': like dicom but does not force series output; 'dicom': in current version it is equal to use 'gdcm'; 'gdcm': uses the dicom series file names reader and GDCM to load the images; 'none': only the specified file will be read; 'numeric': uses the numeric series file names reader and forces an output as series of 2D images.");

        cmdParser.AddArgument("--log", itksys::CommandLineArguments::SPACE_ARGUMENT, &_logFileName,
            "Specifies name and location of the log file. Default (flag not set) is that no log file is written.");
        cmdParser.AddArgument("-l", itksys::CommandLineArguments::SPACE_ARGUMENT, &_logFileName,
            "Specifies name and location of the log file. Default (flag not set) is that no log file is written.");

        if (cmdParser.Parse() == 0)
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
					std::cout << "  matchR <Moving> <Target> <Alg> [options]" << std::endl << std::endl;
					std::cout << "     Moving: File path to the image that is the moving image." << std::endl;
          std::cout << "     Target: File path to the image that is the target image." << std::endl;
          std::cout << "     Alg: File path to the registration algorithm that should be used." << std::endl;
					std::cout << "Command-Line Options:" << std::endl << std::endl;
					std::cout << cmdParser.GetHelp() << std::endl << std::endl;
					std::cout << " Example:" << std::endl << std::endl;
					std::cout << " matchR moving.dcm target.dcm myFancyAlgorithm.dll" << std::endl << std::endl;
					std::cout <<
					          R"( This will match "moving.dcm" onto "target.dcm" by using the algorithm "myFancyAlgorithm.dcm". The output will be in the directory of the input. The output file name will be "moving_to_taget.reg".)"
					          << std::endl;
					return 1;
				}

				if (_showVersion)
				{
					std::cout << std::endl << "Version: " << MAP_FULL_VERSION_STRING << std::endl;
					return 1;
				}

				if (_fileCount < 3)
				{
					return 2;
				}

				if (_outputFileName.empty())
				{
					::map::core::String path = core::FileDispatch::getPath(_movingFileName);
					::map::core::String movingName = core::FileDispatch::getName(_movingFileName);
					::map::core::String targetName = core::FileDispatch::getName(_targetFileName);

          _outputFileName = core::FileDispatch::createFullPath(path, movingName + "_TO_" + targetName + ".mapr");
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

		}  // namespace matchR
	}  // namespace apps
}  // namespace map
