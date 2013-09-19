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


#include "mapDeploymentDLLDirectoryBrowser.h"
#include "mapDeploymentDLLAccess.h"
#include "mapDeploymentEvents.h"
#include "mapLogbook.h"
#include "mapFileDispatch.h"
#include "mapExceptionObjectMacros.h"

#include "itkDirectory.h"
#include "itksys/SystemTools.hxx"

namespace map
{
	namespace deployment
	{
		//implemented in mapDeploymentDLLAccess.cpp
		extern bool checkNameIsSharedLibrary(const char* name);

		void
		DLLDirectoryBrowser::
		addDLLSearchLocation(const core::String& location)
		{
			core::String fullPath = core::FileDispatch::ensureCorrectOSPathSeparator(
										itksys::SystemTools::CollapseFullPath(location.c_str(), _basePath.c_str()));

			_pathList.push_back(fullPath);
		};

		const DLLDirectoryBrowser::PathListType&
		DLLDirectoryBrowser::
		getDLLSearchLocations() const
		{
			return _pathList;

		};

		void
		DLLDirectoryBrowser::
		clearDLLSearchLocations()
		{
			_pathList.clear();
		};

		void
		DLLDirectoryBrowser::
		setSearchBase(const core::String& base)
		{
			_basePath = base;
		};

		const core::String&
		DLLDirectoryBrowser::
		getSearchBase() const
		{
			return _basePath;
		};

		bool
		DLLDirectoryBrowser::
		libraryIsInList(const core::String& libraryFilePath, const PathListType& touchedFiles) const
		{
			bool result = false;
			PathListType::const_iterator pos;

			for (pos = touchedFiles.begin(); pos != touchedFiles.end(); ++pos)
			{
				if ((*pos) == libraryFilePath)
				{
					result = true;
					break;
				}
			}

			return result;
		};


		DLLDirectoryBrowser::PathListType
		DLLDirectoryBrowser::
		getCandidatesInPath(const core::String& libraryPath) const
		{
			PathListType result;

			itk::Directory::Pointer dir = itk::Directory::New();

			if (dir->Load(libraryPath.c_str()))
			{
				/*
				* check each file in the directory
				*/
				for (unsigned int i = 0; i < dir->GetNumberOfFiles(); i++)
				{
					const char* file = dir->GetFile(i);

					if (checkFileNameIsMDRACompliant(file))
					{
						core::String fullpath = core::FileDispatch::createFullPath(libraryPath.c_str(), file);
						result.push_back(fullpath);
					}
				}
			}

			return result;
		};

		DLLDirectoryBrowser::PathListType
		DLLDirectoryBrowser::
		getCandidates() const
		{
			PathListType result;

			for (PathListType::const_iterator pos = _pathList.begin(); pos != _pathList.end(); ++pos)
			{

				if (itksys::SystemTools::FileExists(pos->c_str()))
				{
					//directory or file exists
					if (itksys::SystemTools::FileExists(pos->c_str(), true))
					{
						//its directly defined file, so only check if it is a shared library; naming convention is irrelevant.
						if (checkNameIsSharedLibrary(pos->c_str()))
						{
							result.push_back(*pos);
						}
					}
					else
					{
						//its a directory
						PathListType subresult = this->getCandidatesInPath(*pos);
						result.insert(result.end(), subresult.begin(), subresult.end());
					}
				}
				else
				{
					core::OStringStream stream;
					stream << "Specified dll search location does not exist. Location: " << *pos;
					mapLogWarningMacro( << stream.str());
					this->InvokeEvent(map::events::InvalidDLLEvent(NULL, stream.str()));
				}
			}

			return result;
		};


		void
		DLLDirectoryBrowser::
		peekLibrary(const core::String& libraryFilePath, DLLInfoListType& list,
					PathListType& touchedFiles) const
		{
			if (!libraryIsInList(libraryFilePath, touchedFiles))
			{
				try
				{
					algorithm::UID::ConstPointer spUID;
					core::String profileStr;
					map::deployment::peekDeploymentDLL(libraryFilePath, spUID, profileStr);
					DLLInfo::Pointer spInfo = DLLInfo::New(spUID, libraryFilePath, profileStr);
					list.push_back(spInfo);
					core::String sComment = "Valid DLL: " + libraryFilePath;
					this->InvokeEvent(map::events::ValidDLLEvent(spInfo.GetPointer(), sComment));
				}
				catch (const map::core::ExceptionObject& e)
				{
					core::String sComment = e.GetDescription();
					this->InvokeEvent(map::events::InvalidDLLEvent(NULL, sComment));
				}
				catch (...)
				{
					core::String sComment = "Unkown error while try to peek DLL. File path: " + libraryFilePath;
					this->InvokeEvent(map::events::InvalidDLLEvent(NULL, sComment));
				}
			}

			touchedFiles.push_back(libraryFilePath);
		};


		void
		DLLDirectoryBrowser::
		update()
		{
			DLLInfoListType result;

			PathListType touchedFiles;

			PathListType candidates = this->getCandidates();

			for (PathListType::const_iterator pos = candidates.begin(); pos != candidates.end(); ++pos)
			{
				this->peekLibrary(*pos, result, touchedFiles);
			}

			//every thing worked just fine so exchange
			_dllInfoList.swap(result);
		};

		DLLDirectoryBrowser::DLLInfoListType
		DLLDirectoryBrowser::
		getLibraryInfos() const
		{
			return _dllInfoList;
		};

		DLLDirectoryBrowser::
		DLLDirectoryBrowser()
		{
			_basePath = itksys::SystemTools::GetCurrentWorkingDirectory();
		};

		DLLDirectoryBrowser::
		~DLLDirectoryBrowser()
		{
		};

		DLLInfoListType peekDeploymentDLLDirectory(const char* directoryPath)
		{
			return peekDeploymentDLLDirectory(core::String(directoryPath));
		};

		DLLInfoListType peekDeploymentDLLDirectory(const core::String& directoryPath)
		{
			DLLDirectoryBrowser::Pointer spBrowser = DLLDirectoryBrowser::New();
			spBrowser->addDLLSearchLocation(directoryPath);
			spBrowser->update();
			return spBrowser->getLibraryInfos();
		};

		DLLInfoListType selectDLLInfosByUID(const DLLInfoListType& infoList, const algorithm::UID* uid,
											bool wcNamespace, bool wcName, bool wcVersion, bool wcBuild)
		{
			if (!uid)
			{
				mapDefaultExceptionStaticMacro( << "Cannot select dll info list. Passed uid object is NULL.");
			}

			DLLInfoListType result;

			for (DLLInfoListType::const_iterator pos = infoList.begin(); pos != infoList.end(); ++pos)
			{
				if (compareUIDs(*uid, (*pos)->getAlgorithmUID(), wcNamespace, wcName, wcVersion, wcBuild))
				{
					result.push_back(*pos);
				}
			}

			return result;
		};


	} // end namespace deployment
} // end namespace map