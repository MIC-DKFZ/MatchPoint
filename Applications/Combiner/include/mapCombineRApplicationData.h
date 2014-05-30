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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Applications/Mapper/include/mapRApplicationData.h $
*/


#ifndef __MAP_COMBINER_PLICATION_DATA_H
#define __MAP_COMBINER_PLICATION_DATA_H

#include "mapString.h"
#include "mapGenericImageReader.h"
#include "mapCombineRegistrationFileReader.h"

#include "itksys/CommandLineArguments.hxx"

namespace map
{
	namespace apps
	{
		namespace combineR
		{

			class ApplicationData
			{
			public:

				/** Loaded Registrations.*/
				typedef std::vector<io::RegistrationFileReader::LoadedRegistrationPointer> RegistrationListType;
        RegistrationListType _spRegList;
				std::vector<core::String>  _regFileList;
        std::vector<bool> _inversionList;

				core::String  _outputFileName;

				bool _showVersion;
				bool _detailedOutput;
				bool _showHelp;

        int _fileCount;

				void Reset();

				ApplicationData();
			};

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

		}
	}
}
#endif
