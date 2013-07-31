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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Deployment/source/mapDeploymentDLLInfo.cpp $
*/


#include "mapDeploymentDLLInfo.h"
#include "mapExceptionObject.h"

namespace map
{
	namespace deployment
	{

		const map::algorithm::UID &
		DLLInfo::
		getAlgorithmUID() const
		{
			return *_spAlgorithmUID;
		};

		const core::String &
		DLLInfo::
		getLibraryFilePath() const
		{
			return _libraryFilePath;
		};

		DLLInfo::
		DLLInfo(const map::algorithm::UID *pUID,
		        const core::String &libraryFilePath): _spAlgorithmUID(pUID), _libraryFilePath(libraryFilePath)
		{
			if (!pUID)
			{
				mapDefaultExceptionStaticMacro( << "Cannot create DLLInfo instance. Passed UID pointer is NULL. Library: " << libraryFilePath);
			}
		};

		DLLInfo::
		~DLLInfo()
		{
		};

		DLLInfo::Pointer
		DLLInfo::
		New(const map::algorithm::UID *pUID,
		    const core::String &libraryFile)
		{
			if (!pUID)
			{
				mapDefaultExceptionStaticMacro( << "Cannot create DLLInfo instance. Passed UID pointer is NULL. Library: " << libraryFile);
			}

			Pointer smartPtr;
			Self *rawPtr = new Self(pUID, libraryFile);
			smartPtr = rawPtr;
			rawPtr->UnRegister();
			return smartPtr;
		};

	} // end namespace deployment
} // end namespace map