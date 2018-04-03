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


#include "mapDeploymentDLLHandle.h"
#include "mapExceptionObject.h"

namespace map
{
	namespace deployment
	{

		const DLLHandle::LibraryHandleType&
		DLLHandle::
		getLibraryHandle() const
		{
			return _libraryHandle;
		};

		DLLHandle::
		DLLHandle(const LibraryHandleType& libraryHandle,
				  const map::algorithm::UID* pUID,
				  const core::String& libraryFile,
				  const core::String& profileStr): DLLInfo(pUID, libraryFile, profileStr),
			_libraryHandle(libraryHandle)
		{
		};

		DLLHandle::
		~DLLHandle()
		{
		};

		DLLHandle::Pointer
		DLLHandle::
		New(const LibraryHandleType& libraryHandle,
			const map::algorithm::UID* pUID,
			const core::String& libraryFile,
			const core::String& profileStr)
		{
			if (!pUID)
			{
				mapDefaultExceptionStaticMacro( <<
												"Cannot create DLLHandle instance. Passed UID pointer is NULL. Library: " << libraryFile);
			}

			Pointer smartPtr;
			Self* rawPtr = new Self(libraryHandle, pUID, libraryFile, profileStr);
			smartPtr = rawPtr;
			rawPtr->UnRegister();
			return smartPtr;
		};

	} // end namespace deployment
} // end namespace map