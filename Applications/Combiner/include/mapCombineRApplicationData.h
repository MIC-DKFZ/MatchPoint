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


#ifndef __MAP_COMBINER_PLICATION_DATA_H
#define __MAP_COMBINER_PLICATION_DATA_H

#include "mapString.h"
#include "mapRegistrationBase.h"

#include "itksys/CommandLineArguments.hxx"

namespace map
{
	namespace apps
	{
		namespace combineR
		{

			struct ApplicationData
			{
				/** Loaded Registrations.*/
				using RegistrationListType = std::vector< ::map::core::RegistrationBase::Pointer>;
        RegistrationListType _spRegList;
				std::vector< ::map::core::String>  _regFileList;
        std::vector<bool> _inversionList;

				::map::core::String  _outputFileName;

        ::map::core::String  _logFileName;

				bool _showVersion;
				bool _detailedOutput;
				bool _showHelp;

				void Reset();

				ApplicationData();
			};

			/** Parse the application argument passed when starting the application.**/
			unsigned int ParseArguments(int argc, char** argv, ApplicationData& appData);

		}  // namespace combineR
	}  // namespace apps
}  // namespace map
#endif
