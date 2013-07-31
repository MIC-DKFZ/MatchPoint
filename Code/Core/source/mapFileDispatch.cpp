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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/source/mapFileDispatch.cpp $
*/



#include "mapFileDispatch.h"

#include "itksys/SystemTools.hxx"

namespace map
{
	namespace core
	{
		String
		FileDispatch::
		getName(const String &sFilePath)
		{
			String result = itksys::SystemTools::GetFilenameWithoutLastExtension(sFilePath);
			return result;
		};

		String
		FileDispatch::
		getExtension(const String &sFilePath)
		{
			String result = itksys::SystemTools::GetFilenameLastExtension(sFilePath);
			return result;
		};

		String
		FileDispatch::
		getFullName(const String &sFilePath)
		{
			String result = itksys::SystemTools::GetFilenameName(sFilePath);
			return result;
		};

		String
		FileDispatch::
		getPath(const String &sFilePath)
		{
			String result = itksys::SystemTools::GetFilenamePath(sFilePath);
			return ensureCorrectOSPathSeparator(result);

		};

		String
		FileDispatch::
		getName()
		{
			return getName(_fileName);
		};

		String
		FileDispatch::
		getExtension()
		{
			return getExtension(_fileName);
		};

		String
		FileDispatch::
		getFullName()
		{
			return getFullName(_fileName);
		};

		String
		FileDispatch::
		getPath()
		{
			return getPath(_fileName);
		};

		FileDispatch::
		FileDispatch(const String &filePath)
		{
			_fileName = filePath;
		};

		/**
		 * A file scope helper function to concat path and file into
		 * a full path
		 */
		String
		FileDispatch::
		createFullPath(const char *path, const char *file)
		{
			String ret;

#ifdef _WIN32
			const char sep = '\\';
#else
			const char sep = '/';
#endif
			/**
			 * make sure the end of path is a separator
			 */
			ret = path;
			ret = ensureCorrectOSPathSeparator(ret);

			if (ret.size())
			{
				if (ret[ret.size() - 1] != sep)
				{
					ret.append(1, sep);
				}
			}

			ret.append(file);
			return ret;
		}

		String
		FileDispatch::
		createFullPath(const String &path, const String &file)
		{
			String ret = createFullPath(path.c_str(), file.c_str());
			return ret;
		}

		/** Convertes all path seperators in the seperators used in the current OS.*/
		String
		FileDispatch::
		ensureCorrectOSPathSeparator(const String &path)
		{
			String ret = path;

#ifdef _WIN32
			const String curSep = "\\";
			const char wrongSep = '/';
#else
			const String curSep = "/";
			const char wrongSep = '\\';
#endif

			String::size_type pos = ret.find_first_of(wrongSep);

			while (pos != String::npos)
			{
				ret.replace(pos, 1, curSep);

				pos = ret.find_first_of(wrongSep);
			}

			return ret;
		}


	}
}