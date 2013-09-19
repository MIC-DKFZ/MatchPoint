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


#ifndef __MAP_FILE_DISPATCH_H
#define __MAP_FILE_DISPATCH_H

#include "mapString.h"
#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{

		class MAPCore_EXPORT FileDispatch
		{
		public:
			/** Returns the name of the file (without extension).*/
			static String getName(const String& sFilePath);
			/** Returns the extansion of the file (dot included).*/
			static String getExtension(const String& sFilePath);
			/** Returns name of the file plus extension.*/
			static String getFullName(const String& sFilePath);
			/** Returns the directory the file is located in (without trailing slash).
			* @remark this function always removes the last element of the path. Thus
			* if you pass a path without a file, it will return the parent directory.*/
			static String getPath(const String& sFilePath);

			/** Helper function to concat path and file into
			* a full path */
			static String createFullPath(const char* path, const char* file);
			static String createFullPath(const String& path, const String& file);

			/** Convertes all path seperators in the seperators used in the current OS.*/
			static String ensureCorrectOSPathSeparator(const String& path);

			String getName();
			String getExtension();
			String getFullName();
			String getPath();

			FileDispatch(const String& filePath);

		private:
			String _fileName;
		};

	}
}

#endif
