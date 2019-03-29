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


#ifndef __MAP_RAPPLICATION_DATA_H
#define __MAP_RAPPLICATION_DATA_H

#include "mapString.h"
#include "mapGenericImageReader.h"
#include "mapRegistrationFileReader.h"

#include "itksys/CommandLineArguments.hxx"

namespace map
{
	namespace apps
	{
		namespace mapR
		{
			struct ImageMappingInterpolator
			{
				enum Type
				{
					Unkown = 0, //< undefined/unknown
					NearestNeighbor = 1, //< use nearest neighbor
					Linear = 2, //< use linear
					BSpline_3 = 3, //< use a 3rd order spline
					WSinc_Hamming = 4, //< use a wsinc with hamming window
					WSinc_Welch = 5 //< use a wsinc with welch window
				};
			};

			class ApplicationData
			{
			public:

				/** Loaded Image.*/
				::itk::DataObject::Pointer _input;
				::map::core::String  _inputFileName;
				::map::io::GenericImageReader::GenericOutputImageType::Pointer _spRefImage;
				::map::core::String  _refFileName;
				::map::io::RegistrationFileReader::LoadedRegistrationPointer _spReg;
				::map::core::String  _regFileName;

				::map::core::String  _outputFileName;

        ::map::core::String  _logFileName;

				int _upperSeriesLimit;
				::map::io::ImageSeriesReadStyle::Type _seriesReadStyle;
				::map::core::String _seriesReadStyleStr;
				::map::io::ImageSeriesReadStyle::Type _seriesWriteStyle;
				::map::core::String _seriesWriteStyleStr;
        bool _inputIsImage;

				ImageMappingInterpolator::Type _interpolatorType;
				::map::core::String _interpolatorTypeStr;

				bool _showVersion;
				bool _detailedOutput;
				bool _showHelp;
				double _paddingValue;
        bool _noFailOnErrors;

				int _fileCount;

				::map::io::GenericImageReader::LoadedPixelType _loadedPixelType;
				::map::io::GenericImageReader::LoadedComponentType _loadedComponentType;
				unsigned int _loadedDimensions;

				::map::io::GenericImageReader::MetaDataDictionaryArrayType _loadedMetaDataDictArray;
				::map::io::GenericImageReader::MetaDataDictionaryArrayType _loadedRefMetaDataDictArray;

				/** Parse the application argument passed when starting the application.
				* If no error or special request occurred the return is 0. Otherwise the return values
				* have the following meaning: \n
				* 1: incorrect use of flag -ex. -ex is last argument, but parameter name is missing.\n
				* 2: incorrect use of flag -m. -m is last argument, but media id is missing.\n
				* 3: incorrect use of flag -p. -p is last argument, but parameter name is missing.\n
				* 4: incorrect use of flag -l, -m and -p. Only one of them can be set.\n
				* 5: incorrect use of flag -m or -p. ControllerID must be specified.\n
				* 6: help flag was set.\n
				* 7: version flag was set.\n
				* @param argc Number of parameter arguments
				* @param argv Pointer to the passed arguments
				* @return Result code of the parsing (see above).**/
				unsigned int ParseArguments(int argc, char** argv);

				void Reset();

				ApplicationData();

			protected:
				itksys::CommandLineArguments cmdParser;
			};

		}  // namespace mapR
	}  // namespace apps
}  // namespace map
#endif
