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
#include "mapConfigure.h"

#include "itksys/SystemTools.hxx"

namespace map
{
	namespace apps
	{
		namespace mapR
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
				_inputFileName = "";
				_outputFileName = "";
				_regFileName = "";
				_refFileName = "";
        _logFileName = "";

				_showVersion = false;
				_showHelp = false;
				_detailedOutput = false;
				_paddingValue = 0.0;
        _noFailOnErrors = false;

				_upperSeriesLimit = 0;
				_loadedPixelType = ::itk::ImageIOBase::SCALAR;
				_loadedComponentType = ::itk::ImageIOBase::UCHAR;
				_loadedDimensions = 1;
        _inputIsImage = true;
				_seriesReadStyle = io::ImageSeriesReadStyle::Default;
				_seriesWriteStyle = io::ImageSeriesReadStyle::Default;
				_seriesReadStyleStr = "default";
				_seriesWriteStyleStr = "";

				_interpolatorType = ImageMappingInterpolator::Linear;
				_interpolatorTypeStr = "linear";

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
						//argument is the input file. Store the argument and move to next position.
						_inputFileName = dummyArg;
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

				cmdParser.AddArgument("--padding", itksys::CommandLineArguments::SPACE_ARGUMENT, &_paddingValue,
				                      "Specifies the value that should be used for pixels of the result image that are not covered by the mapped input image. Default value is '0.0'.");
				cmdParser.AddArgument("-p", itksys::CommandLineArguments::SPACE_ARGUMENT, &_paddingValue,
				                      "Specifies the value that should be used for pixels of the result image that are not covered by the mapped input image. Default value is '0.0'.");

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
				cmdParser.AddArgument("-w", itksys::CommandLineArguments::SPACE_ARGUMENT, &_seriesWriteStyleStr,
				                      "Defines the write style for the result image by overwriting the settings implied by the read style. Valid values are: 'default': output depends on the specified file format; 'dicom': uses the dicom series file names reader and forces an output as series of 2D images; 'gdcm': forces an output as series of 2D images; 'none': see default; 'numeric': forces an output as series of 2D images.");
				cmdParser.AddArgument("--seriesWriter", itksys::CommandLineArguments::SPACE_ARGUMENT,
				                      &_seriesWriteStyleStr,
				                      "Defines the write style for the result image by overwriting the settings implied by the read style. Valid values are: 'default': output depends on the specified file format; 'dicom': uses the dicom series file names reader and forces an output as series of 2D images; 'gdcm': further forces an output as series of 2D images; 'none': see default; 'numeric': forces an output as series of 2D images.");

				cmdParser.AddArgument("-i", itksys::CommandLineArguments::SPACE_ARGUMENT, &_interpolatorTypeStr,
				                      "Defines the interpolator that should be used for mapping the image. Default value is 'linear'. Valid values are: 'nn': uses a nearest neighbor interpolator; 'linear': uses a simple linear interpolator; 'bspline_3': uses a 3rd order B spline interpolator; 'hamming': uses a wsinc with hamming window as interpolator; 'welch': uses a wsinc with welch window as interpolator.");
				cmdParser.AddArgument("--interpolator", itksys::CommandLineArguments::SPACE_ARGUMENT,
				                      &_interpolatorTypeStr,
				                      "Defines the interpolator that should be used for mapping the image. Default value is 'linear'. Valid values are: 'nn': uses a nearest neighbor interpolator; 'linear': uses a simple linear interpolator; 'bspline_3': uses a 3rd order B spline interpolator; 'hamming': uses a wsinc with hamming window as interpolator; 'welch': uses a wsinc with welch window as interpolator.");

        cmdParser.AddArgument("--handleMappingFailure", itksys::CommandLineArguments::NO_ARGUMENT, &_noFailOnErrors,
            "If this flag is activated the mapping process will not faile if the registration is not sufficiently defined. Instead it will use the padding value (-p) to mark any voxel that could not be map due to the insufficent registration with the padding value.");

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
					std::cout << "  mapR <Input> [<Reg>] [options]" << std::endl << std::endl;
					std::cout << "     Input: File path to the image that should be mapped." << std::endl;
					std::cout << "     Reg: File path to the registration file that specifies" << std::endl;
					std::cout << "          the registration that should be used for mapping." << std::endl;
					std::cout << "          Optional: If no reg file is specified, an identity" << std::endl;
					std::cout << "          transform will be used for mapping." << std::endl << std::endl;
					std::cout << "Command-Line Options:" << std::endl << std::endl;
					std::cout << cmdParser.GetHelp() << std::endl << std::endl;
					std::cout << " Example:" << std::endl << std::endl;
					std::cout << " mapR input.dcm reg.mapr -t target.dcm" << std::endl << std::endl;
					std::cout <<
					          " This will map \"input.png\" by using \"reg.mapr\". The field of view of the output image is defined by \"target.dcm\". The output will be in the directory of the input. The output file name will be \"input_reg.dcm\"."
					          << std::endl;
					return 1;
				}

				if (_showVersion)
				{
					std::cout << std::endl << "Version: " << MAP_FULL_VERSION_STRING << std::endl;
					return 1;
				}

				if (_fileCount < 1)
				{
					return 2;
				}

				if (_outputFileName.empty())
				{
					::map::core::String path = core::FileDispatch::getPath(_inputFileName);
					::map::core::String inputName = core::FileDispatch::getName(_inputFileName);
					::map::core::String inputExt = core::FileDispatch::getExtension(_inputFileName);
					::map::core::String regName = core::FileDispatch::getName(_regFileName);

					_outputFileName = core::FileDispatch::createFullPath(path, inputName + "_" + regName + inputExt);
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

				if (!_seriesWriteStyleStr.empty())
				{
					if (_seriesWriteStyleStr == "none")
					{
						_seriesWriteStyle =  io::ImageSeriesReadStyle::None;
					}
					else if (_seriesWriteStyleStr == "dicom")
					{
						_seriesWriteStyle =  io::ImageSeriesReadStyle::Dicom;
					}
					else if (_seriesWriteStyleStr == "numeric")
					{
						_seriesWriteStyle =  io::ImageSeriesReadStyle::Numeric;
					}
					else if (_seriesWriteStyleStr == "gdcm")
					{
						_seriesWriteStyle =  io::ImageSeriesReadStyle::GDCM;
					}
				}
				else
				{
					_seriesWriteStyle = _seriesReadStyle;
					_seriesWriteStyleStr = _seriesReadStyleStr;
				}

				if (_interpolatorTypeStr == "nn")
				{
					_interpolatorType = ImageMappingInterpolator::NearestNeighbor;
				}
				else if (_interpolatorTypeStr == "linear")
				{
					_interpolatorType = ImageMappingInterpolator::Linear;
				}
				else if (_interpolatorTypeStr == "bspline_3")
				{
					_interpolatorType = ImageMappingInterpolator::BSpline_3;
				}
				else if (_interpolatorTypeStr == "hamming")
				{
					_interpolatorType = ImageMappingInterpolator::WSinc_Hamming;
				}
				else if (_interpolatorTypeStr == "welch")
				{
					_interpolatorType = ImageMappingInterpolator::WSinc_Welch;
				}
				else
				{
					_interpolatorType = ImageMappingInterpolator::Unkown;
				}

				return 0;
			};

		}
	}
}
