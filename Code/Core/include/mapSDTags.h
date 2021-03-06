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


#ifndef __MAP_SD_TAGS_H
#define __MAP_SD_TAGS_H


namespace map
{
	namespace tags
	{
		/** Indicates which kind of reader was used to recieve the
		 data that was used to generate the structured data.
		 e.g.: file = for FileReader; string = string in memory...*/
		const char* const SDInternalSourceReader = "sdInternal:SourceReader";
		const char* const SDInternalSourceReader_file = "file";
		const char* const SDInternalSourceReader_string = "string";

		/** Indicates which kind of format the structured data was
		 stored in.
		 e.g.: xml...*/
		const char* const SDInternalSourceFormat = "sdInternal:SourceFormat";
		const char* const SDInternalSourceFormat_xml = "xml";

		/** Indicates the location of the data source.
		 e.g.: the file path...*/
		const char* const SDInternalSourceURI = "sdInternal:SourceURI";
	}  // namespace tags
}  // namespace map

#endif
