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
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/include/matchRApplicationData.h $
*/


#ifndef __MAP_RAPPLICATION_DATA_H
#define __MAP_RAPPLICATION_DATA_H

#include "mapString.h"
#include "mapGenericImageReader.h"
#include "mapRegistrationFileReader.h"
#include "mapRegistrationAlgorithmBase.h"

#include "itksys/CommandLineArguments.hxx"

namespace map
{
	namespace apps
	{
		namespace matchR
		{

			class ApplicationData
			{
			public:

        ::map::algorithm::RegistrationAlgorithmBase::Pointer _algorithm;
        ::map::core::String  _algorithmFileName;

				/** Loaded Images.*/
				::map::io::GenericImageReader::GenericOutputImageType::Pointer _spMovingImage;
				::map::core::String  _movingFileName;
				::map::io::GenericImageReader::GenericOutputImageType::Pointer _spTargetImage;
				::map::core::String  _targetFileName;
        ::map::io::GenericImageReader::GenericOutputImageType::Pointer _spMovingMaskImage;
        ::map::core::String  _movingMaskFileName;
        ::map::io::GenericImageReader::GenericOutputImageType::Pointer _spTargetMaskImage;
        ::map::core::String  _targetMaskFileName;

				::map::core::String  _outputFileName;

        ::map::core::String  _logFileName;

				int _upperSeriesLimit;
				::map::io::ImageSeriesReadStyle::Type _seriesReadStyle;
        ::map::core::String _seriesReadStyleStr;

        std::vector<::map::core::String> _parameterStrs;
        typedef std::map<::map::core::String, ::map::core::String> ParameterMapType;
        ParameterMapType _parameterMap;

				bool _showVersion;
				bool _detailedOutput;
				bool _showHelp;

				int _fileCount;

				unsigned int _loadedDimensions;

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

		}
	}
}
#endif
