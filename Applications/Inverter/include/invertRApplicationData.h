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
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/include/invertRApplicationData.h $
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
		namespace invertR
		{

			class ApplicationData
			{
			public:

				/** Loaded Image.*/
				::map::io::GenericImageReader::GenericOutputImageType::Pointer _spRefImage;
				::map::core::String  _refFileName;
				::map::io::RegistrationFileReader::LoadedRegistrationPointer _spReg;
				::map::core::String  _regFileName;

				::map::core::String  _outputFileName;

        ::map::core::String  _logFileName;

				::map::io::ImageSeriesReadStyle::Type _seriesReadStyle;
				::map::core::String _seriesReadStyleStr;

        bool _ensureDirectMapping;
        bool _ensureInverseMapping;

				bool _showVersion;
				bool _detailedOutput;
				bool _showHelp;

				int _fileCount;

				/** Parse the application argument passed when starting the application.
				* If no error or special request occurred the return is 0. Otherwise the return values
				* have the following meaning: \n
				* 1: version flag was set.\n
				* 2: Error with the required parameters.\n
				* 3: incorrect use of flags\n
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
