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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/test/mapDeploymentDLLBrowserTest.cpp $
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itksys/SystemTools.hxx"
#include "itkDirectory.h"
#include "itkDynamicLoader.h"
#include "litCheckMacros.h"
#include "litTesterBase.h"

#include "mapDeploymentDLLDirectoryBrowser.h"
#include "mapDeploymentDLLAccess.h"
#include "mapFileDispatch.h"

#include "mapString.h"

namespace map
{
	namespace testing
	{
		deployment::DLLDirectoryBrowser::PathListType
		getFilesInPath(const core::String &libraryPath)
		{
			deployment::DLLDirectoryBrowser::PathListType result;

			itk::Directory::Pointer dir = itk::Directory::New();

			if (dir->Load(libraryPath.c_str()))
			{
				/*
				* check each file in the directory
				*/
				for (unsigned int i = 0; i < dir->GetNumberOfFiles(); i++)
				{
					const char *file = dir->GetFile(i);
					core::String fullpath = core::FileDispatch::createFullPath(libraryPath.c_str(), file);
					result.push_back(fullpath);
				}
			}

			return result;
		};

		bool
		checkLocationInInfos(const deployment::DLLDirectoryBrowser::DLLInfoListType &infos, const core::String &libraryPath)
		{
			bool result = false;

			map::deployment::DLLDirectoryBrowser::DLLInfoListType::const_iterator pos;

			for (pos = infos.begin(); pos != infos.end(); ++pos)
			{
				if ((*pos)->getLibraryFilePath().find(libraryPath) != core::String::npos)
				{
					return true;
				}
			}

			return result;
		};

		class DirBrowserTester: public lit::TesterBase
		{
		public:
			typedef DirBrowserTester Self;
			typedef TesterBase Superclass;

			virtual lit::StringType getTestDescription(void) const
			{
				return "Check valid dll directory browser results";
			};

			virtual lit::StringType getTestName(void) const
			{
				return "DirDeploymentDLLBroserTester";
			};

			void setResult(const deployment::DLLDirectoryBrowser::DLLInfoListType &infos)
			{
				_infos = infos;
			};

			void setActualFileList(const deployment::DLLDirectoryBrowser::PathListType &candidates)
			{
				_candidates = candidates;
			};

			DirBrowserTester()
			{};
			virtual ~DirBrowserTester()
			{};

		protected:
			deployment::DLLDirectoryBrowser::DLLInfoListType _infos;
			deployment::DLLDirectoryBrowser::PathListType _candidates;

			mutable deployment::DLLDirectoryBrowser::PathListType _falsePositives;
			mutable deployment::DLLDirectoryBrowser::PathListType _falseNegatives;

			virtual bool doCheck(void) const
			{
				_falseNegatives.clear();
				_falsePositives.clear();

				_pResults->onTestStart(getCurrentTestLabel());
				
				for (deployment::DLLDirectoryBrowser::PathListType::const_iterator pos = _candidates.begin(); pos != _candidates.end(); ++pos)
				{
					bool foundByBrowser = checkLocationInInfos(_infos, *pos);
					bool validCandidate = deployment::checkFileNameIsMDRACompliant(pos->c_str());

					if (foundByBrowser && !validCandidate)
					{
						_falsePositives.push_back(*pos);
					}

					if (!foundByBrowser && validCandidate)
					{
						_falseNegatives.push_back(*pos);
					}
				}

				return _falseNegatives.empty() && _falsePositives.empty();
			};

			virtual void handleSuccess(void) const
			{
				_pResults->onTestSuccess(getCurrentTestLabel(), "Directory browser identified the deployed algorithms correctly.");
			};

			/*! Function will be called be check() if test was a failure.
			* Implement to realize special tester behaviour.
			*/
			virtual void handleFailure(void) const
			{
				core::OStringStream stream;
				stream << "Directory browser misidentified the deployed algorithms." << std::endl;
				stream << "False positives (wrongly assumed to be deployed algorithms)" << std::endl;

				for (deployment::DLLDirectoryBrowser::PathListType::const_iterator pos = _falsePositives.begin(); pos != _falsePositives.end(); ++pos)
				{
					stream << " - " << *pos << std::endl;
				}

				stream << "False negatives (wrongly assumed to be no deployed algorithms)" << std::endl;

				for (deployment::DLLDirectoryBrowser::PathListType::const_iterator pos = _falseNegatives.begin(); pos != _falseNegatives.end(); ++pos)
				{
					stream << " - " << *pos << std::endl;
				}

				_pResults->onTestFailure(getCurrentTestLabel(), stream.str());
			};

		private:
			DirBrowserTester(Self &source); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

		//defined by mapDeploymentTests.cpp. It is the path to the current running executable.
		//It is needed to bypass the problem that when using MS Visual Studio the actual binary
		//path depends of the compile mode (release/debug) and is not the CMake binary path.
		extern const char *_callingAppPath;

		int mapDeploymentDLLBrowserTest(int argc, char *argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			map::core::String searchPath = itksys::SystemTools::GetProgramPath(_callingAppPath);

			//check basic api
			deployment::DLLDirectoryBrowser::Pointer spBrowser = deployment::DLLDirectoryBrowser::New();

			deployment::DLLDirectoryBrowser::PathListType paths;
			CHECK_NO_THROW(paths = spBrowser->getDLLSearchLocations());
			CHECK(paths.empty());
			CHECK_EQUAL(itksys::SystemTools::GetCurrentWorkingDirectory(), spBrowser->getSearchBase());

			deployment::DLLInfoListType infos;
			CHECK_NO_THROW(infos = spBrowser->getLibraryInfos());
			CHECK(infos.empty());

			CHECK_NO_THROW(spBrowser->setSearchBase("base"));
			CHECK(spBrowser->getDLLSearchLocations().empty());
			CHECK_EQUAL("base", spBrowser->getSearchBase());

			CHECK_NO_THROW(spBrowser->addDLLSearchLocation("aPath"));
			CHECK_NO_THROW(spBrowser->addDLLSearchLocation("bPath"));
			CHECK_NO_THROW(paths = spBrowser->getDLLSearchLocations());
			core::String refAPath = core::FileDispatch::createFullPath("base", "aPath");
			core::String refBPath = core::FileDispatch::createFullPath("base", "bPath");
			CHECK_EQUAL(refAPath, paths[0]);
			CHECK_EQUAL(refBPath, paths[1]);
			CHECK_EQUAL(2, paths.size());
			CHECK_NO_THROW(spBrowser->clearDLLSearchLocations());
			CHECK_NO_THROW(paths = spBrowser->getDLLSearchLocations());
			CHECK(paths.empty());

			//check the search results
			//basic check is that only deployed algorithms are found an no other files.
			spBrowser->setSearchBase(itksys::SystemTools::GetCurrentWorkingDirectory());
			spBrowser->addDLLSearchLocation(searchPath);

			CHECK_NO_THROW(spBrowser->update());
			CHECK_NO_THROW(infos = spBrowser->getLibraryInfos());

			deployment::DLLDirectoryBrowser::PathListType candidates = getFilesInPath(spBrowser->getDLLSearchLocations()[0]);

			DirBrowserTester tester;
			tester.setActualFileList(candidates);
			tester.setResult(infos);

			CHECK_TESTER(tester);

			core::String wrongFile = core::FileDispatch::createFullPath(searchPath, itksys::DynamicLoader::LibPrefix() + core::String("mapTestAlgorithm") + itksys::DynamicLoader::LibExtension());
			spBrowser->addDLLSearchLocation(wrongFile);
			CHECK_NO_THROW(spBrowser->update());
			CHECK_NO_THROW(infos = spBrowser->getLibraryInfos());
			tester.setResult(infos);
			tester.invertCheckOn();

			// this test should succeed because it is inverted. The uninverted test fails because,
			// we have forced the browser to find a algorithm by explicitly adding it to the search locations
			// and bypassing the naming check; but the tester complaines about the disregarded naming convention.
			// This behaviour of the browser is wanted, useres should be able to force a file be defining
			// it explicitly.
			CHECK_TESTER(tester);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
