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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/include/mapDeploymentDLLDirectoryBrowser.h $
*/


#ifndef __MAP_DEPLOYMENT_DLL_DIRECTORY_BROWSER_H
#define __MAP_DEPLOYMENT_DLL_DIRECTORY_BROWSER_H

#include "itkObject.h"

#include "mapDeploymentDLLInfo.h"

namespace map
{
	namespace deployment
	{
		/** @class DLLDirectoryBrowser
		* @brief Helper class that searches in given directories for valid deployment algorithms (DA).
		*
		* For each found but invalid DA an InvalidDLLEvent will be triggered. For each valid
		* DA a ValidDLLEvent will be triggered, containing a pointer to the corresponding
		* DLLInfo structure. You can add observer to the browser to get a notification
		* for that events.\n
		* The browser only lists a certain DLL once. The DLL is uniquely identified by its file path.
		* Thus even if add the same path several times as a search location or a directory and a dll file path contained
		* in the directory, no multiple listing of an DLL will occur.\n
		* The browser collapses every added search path, when it is added. Thus it resolves any relative path components using the current search base.
		* The base is by default the current working directory.
		* @remark The browser will only check and find DAs which have filenames following the naming convention:\n
		* mdra[verioning]_[name].[dll|so]; Example: mdra-D-0-9_CorrectlyNamedAlgorithm.dll\n
		* You can force the browser to find other DA by not only specifying the directory but the concrete filepath
		* of the DA.
		*
		* @ingroup DeployHost
		*/
		class MAPDeployment_EXPORT DLLDirectoryBrowser: public itk::Object
		{
		public:
			/** Smart pointer typedef support. */
			typedef DLLDirectoryBrowser  Self;
			typedef itk::Object  Superclass;
			typedef ::itk::SmartPointer<Self>  Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;

			/** Run-time type information (and related methods). */
			itkTypeMacro(DLLDirectoryBrowser, itk::Object);

			itkFactorylessNewMacro(Self);

			typedef std::vector<DLLInfo::Pointer> DLLInfoListType;
			typedef std::vector<core::String> PathListType;

			/** Sets the base that is used to collapse relative search paths when added as search locations.
			* @eguarantee strong
			*/
			void setSearchBase(const core::String &base);

			/** Returns the base path that is used to collapse relative search paths when added as search locations.
			* @eguarantee strong
			*/
			const core::String &getSearchBase() const;

			/** Adds the passed location to the dll search path list, that is used for searching deployment DLLs.
			* @param [in] sLocation String to the search location. It may be a file path to the library that should be loaded
			* or a directory. If a directory location is added, all files in the directory will be scanned if they are dynamic libraries.
			* @eguarantee strong
			*/
			void addDLLSearchLocation(const core::String &location);
			/** Returns the current list of additional search locations.
			* @eguarantee strong
			*/
			const PathListType &getDLLSearchLocations() const;
			/** Clears the DLL search path list
			* @eguarantee strong
			*/
			void clearDLLSearchLocations();

			/** Clears the current list of DLL infos and starts a search for DLLs in the current search path list.
			* @eguarantee strong
			*/
			void update();

			/** Returns the current list of found deployment DLLs.
			* @eguarantee strong
			*/
			DLLInfoListType getLibraryInfos() const;

		protected:

			/** looks for potential deployed algorithm (complying naming conventions) in the passed path. Assumes that real directory is passed.
			 * Returns a list of file paths with all candidates in the path that should be "peeked".*/
			PathListType getCandidatesInPath(const core::String &libraryPath) const;
			/** looks for potential deployed algorithm in the current search locations. If the search location specifies a file, it must exist and be a valid
			 * shared object. If the location is a directory, the containing files must also following the naming conventions. Assumes that an existing directory is passed.
			 * Returns a list of file paths with all candidates that should be "peeked".*/
			PathListType getCandidates() const;

			/** looks for the specified DLL and add an DLLInfo to the parameter list if the file is a valid DLL.*/
			void peekLibrary(const core::String &libraryFilePath, DLLInfoListType &list, PathListType &touchedFiles) const;

			/** looks if the passed libraryFilePath is already contained in the list of touched files.*/
			bool libraryIsInList(const core::String &libraryFilePath, const PathListType &touchedFiles) const;

			DLLDirectoryBrowser();

			~DLLDirectoryBrowser();

			DLLInfoListType _dllInfoList;
			PathListType _pathList;

			/*! Base for collapsing of relative search paths. Default is the current working directory*/
			core::String _basePath;

		private:
			DLLDirectoryBrowser(const Self &);//purposely not implemented
			void operator=(const Self &); //purposely not implemented

		};

		typedef DLLDirectoryBrowser::DLLInfoListType DLLInfoListType;

		/*! Helper method if you just need quick information about deployment DLLs in an specific directory.
		 * The method uses a DLLDirectoryBrowser on the specified directory and passes back the result
		 * the algorithm stored in the DLL and closes the DLL again (using closeDeploymentDLL()).
		 * @ingroup DeployHost
		 * @pre directoryPath must not be NULL
		 * @eguarantee strong
		 * @param directoryPath the directory path as c-string.
		 * @result list with DLLInfo instances for all found, valid DLLs.
		*/
		MAPDeployment_EXPORT DLLInfoListType peekDeploymentDLLDirectory(const char *directoryPath);
		/*! @overload
		 * @param directoryPath the directory path as string.
		 * @eguarantee strong
		 * @result list with DLLInfo instances for all found, valid DLLs.
		*/
		MAPDeployment_EXPORT DLLInfoListType peekDeploymentDLLDirectory(const core::String &directoryPath);

		/** Helper function that selects all dll infos from a given list, that match
		 * with the passed uid (regarding the given wild cards, thus ignoring parts of the uid).
		 * @pre passed uid must point to a valid instance;
		 * @param [in] infoList The list that should be filtered.
		 * @param [in] uid The reference uid.
		 * @param [in] wcNamespace Indicates if the namespace is wild carded. (True: ignore).
		 * @param [in] wcName Indicates if the name is wild carded. (True: ignore).
		 * @param [in] wcVersion Indicates if the version is wild carded. (True: ignore).
		 * @param [in] wcBuild Indicates if the build is wild carded. (True: ignore).
		 * @return A dll info list that only contains dll infos, that match the given reference uid.
		 * @eguarantee strong
		 * @TODO add to unit test*/
		MAPDeployment_EXPORT DLLInfoListType selectDLLInfosByUID(const DLLInfoListType &infoList, const algorithm::UID *uid, bool wcNamespace = false, bool wcName = false, bool wcVersion = false, bool wcBuild = false);

	} // end namespace deployment
} // end namespace map

#endif
