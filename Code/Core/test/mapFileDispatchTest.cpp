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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapFileDispatch.h"
#include "mapString.h"
#include "litCheckMacros.h"
namespace map
{
	namespace testing
	{

		int mapFileDispatchTest(int argc, char* argv[])
		{
#ifdef _WIN32
			const core::String sep = "\\";
			const core::String wSep = "/";
#else
			const core::String sep = "/";
			const core::String wSep = "\\";
#endif

			PREPARE_DEFAULT_TEST_REPORTING;

			core::String filePath = "dir1" + sep + "subdir" + sep + "fileName.fileExt";
			core::String path = "dir1" + sep + "subdir" + sep;
			core::String path2 = "dir1" + sep + "subdir";
			core::String path2_wrong = "dir1" + wSep + "subdir";
			core::String emptyPath = "";
			core::String wrongPath = "dir1" + sep + "subdir" + wSep + "subsubdir" + wSep + "fileName.fileExt";
			core::String correctPath = "dir1" + sep + "subdir" + sep + "subsubdir" + sep + "fileName.fileExt";

			//check static member
			CHECK(map::core::FileDispatch::getName(filePath) == "fileName");
			CHECK(map::core::FileDispatch::getName(path) == "");
			CHECK(map::core::FileDispatch::getName(emptyPath) == "");

			CHECK(map::core::FileDispatch::getExtension(filePath) == ".fileExt");
			CHECK(map::core::FileDispatch::getExtension(path) == "");
			CHECK(map::core::FileDispatch::getExtension(emptyPath) == "");

			CHECK(map::core::FileDispatch::getFullName(filePath) == "fileName.fileExt");
			CHECK(map::core::FileDispatch::getFullName(path) == "");
			CHECK(map::core::FileDispatch::getFullName(emptyPath) == "");

			CHECK(map::core::FileDispatch::getPath(filePath) == "dir1" + sep + "subdir");
			CHECK(map::core::FileDispatch::getPath(path) == "dir1");
			CHECK(map::core::FileDispatch::getPath(emptyPath) == "");

			CHECK(map::core::FileDispatch::createFullPath(path.c_str(), "file.ext") == path + "file.ext");
			CHECK(map::core::FileDispatch::createFullPath(path2.c_str(), "file.ext") == path + "file.ext");
			CHECK(map::core::FileDispatch::createFullPath("", "file.ext") == "file.ext");
			CHECK(map::core::FileDispatch::createFullPath(path.c_str(), "") == path);

			CHECK(map::core::FileDispatch::createFullPath(path2_wrong.c_str(),
					"file.ext") == map::core::FileDispatch::createFullPath(path2.c_str(), "file.ext"));

			CHECK(map::core::FileDispatch::ensureCorrectOSPathSeparator(wrongPath) == correctPath);
			CHECK(map::core::FileDispatch::ensureCorrectOSPathSeparator(correctPath) == correctPath);
			CHECK(map::core::FileDispatch::ensureCorrectOSPathSeparator(emptyPath) == emptyPath);

			//check member

			map::core::FileDispatch disp1(filePath);
			map::core::FileDispatch disp2(path);
			map::core::FileDispatch disp3(emptyPath);

			CHECK(disp1.getName() == "fileName");
			CHECK(disp2.getName() == "");
			CHECK(disp3.getName() == "");

			CHECK(disp1.getExtension() == ".fileExt");
			CHECK(disp2.getExtension() == "");
			CHECK(disp3.getExtension() == "");

			CHECK(disp1.getFullName() == "fileName.fileExt");
			CHECK(disp2.getFullName() == "");
			CHECK(disp3.getFullName() == "");

			CHECK(disp1.getPath() == "dir1" + sep + "subdir");
			CHECK(disp2.getPath() == "dir1");
			CHECK(disp3.getPath() == "");

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
