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


#include <assert.h>

#include "itksys/SystemTools.hxx"
#include "itkDynamicLoader.h"

#include "mapConfigure.h"
#include "mapDeploymentDLLAccess.h"
#include "mapCheckDLLInterfaceVersion.h"
#include "mapDeploymentSync.h"
#include "mapFileDispatch.h"

namespace map
{
	namespace deployment
	{

		map::core::String
    getDeploymentDLLExtension()
    {
      map::core::String result = itksys::DynamicLoader::LibExtension();
#ifdef __APPLE_CC__
      result = ".dylib";
#endif
      return result;
    };

    map::core::String getDeploymentDLLMDRAPrefix()
    {
      ::map::core::String prefix = core::String("mdra");

#if _DEBUG || (__linux__ && !defined(NDEBUG)) || (__APPLE__ && !defined(NDEBUG))
      prefix = prefix + "-D";
#endif

      ::map::core::OStringStream ostr;
      ostr << "-" << MAP_VERSION_MAJOR << "-" << MAP_VERSION_MINOR;

      prefix = prefix + ostr.str();

      return prefix;
    };

		bool
		checkNameIsSharedLibrary(const char* name)
		{
			if (!name)
			{
				mapDefaultExceptionStaticMacro("Error. File name pointer to check is NULL. Cannot determine if its an library.");
			}

			::map::core::String sname = name;

			if (sname.find(getDeploymentDLLExtension()) != core::String::npos)
			{
				return true;
			}

			return false;
		}

		bool
		checkFileNameIsMDRACompliant(const char* name)
		{
			if (!name)
			{
				mapDefaultExceptionStaticMacro("Error. File name pointer to check is NULL. Cannot determine if its name is compliant to the naming style for deployed algorithms.");
			}

			::map::core::String sname = name;

			sname = core::FileDispatch::getFullName(sname);

			::map::core::String suffix = core::String(getDeploymentDLLExtension());
			::map::core::String prefix = getDeploymentDLLMDRAPrefix()+"_";

			if (sname.find(prefix) != 0)
			{
				return false;
			}

			if (sname.find(suffix) == core::String::npos)
			{
				return false;
			}

			return true;
		}

		/*! Helper class to properly close a DLL properly (e.g. in case of an exception)*/
		class DLLGuard
		{
		public:
			typedef itksys::DynamicLoader::LibraryHandle HandleType;

			void activate()
			{
				_active = true;
			}

			void deactivate()
			{
				_active = false;
			}

			bool isActive() const
			{
				return _active;
			}

			DLLGuard(HandleType handle) : _handle(handle), _active(true)
			{
			};

			~DLLGuard()
			{
				if (_active)
				{
					itksys::DynamicLoader::CloseLibrary(_handle);
				}
			}

		protected:
			HandleType _handle;
			bool _active;
		};

		DLLHandle::Pointer openDeploymentDLL(const char* libraryFile)
		{
			if (!libraryFile)
			{
				mapDefaultExceptionStaticMacro("Error. Passed pointer to the library file name is NULL.");
			}

			if (!itksys::SystemTools::FileExists(libraryFile, true))
			{
				mapExceptionStaticMacro(InvalidDLLException,
										"Error. Passed library file does not exist. File path: " << libraryFile);
			}

			if (! checkNameIsSharedLibrary(libraryFile))
			{
				mapExceptionStaticMacro(InvalidDLLException,
										"Error. Passed library file seems not to be a valid shared library (wrong file extension). File path: "
										<< libraryFile);
			}

			itksys::DynamicLoader::LibraryHandle libHandle = itksys::DynamicLoader::OpenLibrary(libraryFile);

			if (!libHandle)
			{
				mapExceptionStaticMacro(InvalidDLLException,
										"Error. Passed library cannot be loaded; seems not to be a valid DLL. File path:" << libraryFile <<
										". Error note: " << itksys::DynamicLoader::LastError());
			}

			DLLGuard dllGuard(libHandle);

			//DLL is not correctly loaded. Check for the InterfaceVersion Symbol
			MAP_GET_DLL_INTERFACE_VERSION_FUNCTION_POINTER pVersionFunction =
				(MAP_GET_DLL_INTERFACE_VERSION_FUNCTION_POINTER) itksys::DynamicLoader::GetSymbolAddress(libHandle,
						"mapGetDLLInterfaceVersion");

			if (pVersionFunction == NULL)
			{
				mapExceptionStaticMacro(MissingSymbolException,
										"Error. DLL seems to be invalid; mapGetDLLInterfaceVersion symbol is missing. File path: " <<
										libraryFile << ". Error note: " << itksys::DynamicLoader::LastError());
			}

			//now check the version of the dll
			unsigned int majorVersion = 0;
			unsigned int minorVersion = 0;
			(*pVersionFunction)(majorVersion, minorVersion);

			if (!checkDLLInterfaceVersion(majorVersion, minorVersion))
			{
				mapExceptionStaticMacro(InvalidInterfaceVersionException,
										"Error. DLL seems to have wrong deployment interface version. File path:" << libraryFile <<
										"; DLL version: " << majorVersion << "." << minorVersion << "; host version: " <<
										MAP_DLL_INTERFACE_VERSION_MAJOR << "." << MAP_DLL_INTERFACE_VERSION_MINOR);
			}

			//look for the other expected symbols
			MAP_GET_REGISTRATION_ALGORITHM_UID_FUNCTION_POINTER pUIDFunction =
				(MAP_GET_REGISTRATION_ALGORITHM_UID_FUNCTION_POINTER) itksys::DynamicLoader::GetSymbolAddress(
					libHandle, "mapGetRegistrationAlgorithmUID");
			MAP_GET_REGISTRATION_ALGORITHM_INSTANCE_FUNCTION_POINTER pInstanceFunction =
				(MAP_GET_REGISTRATION_ALGORITHM_INSTANCE_FUNCTION_POINTER) itksys::DynamicLoader::GetSymbolAddress(
					libHandle, "mapGetRegistrationAlgorithmInstance");
			MAP_GET_REGISTRATION_ALGORITHM_PROFILE_FUNCTION_POINTER pProfileFunction =
				(MAP_GET_REGISTRATION_ALGORITHM_PROFILE_FUNCTION_POINTER) itksys::DynamicLoader::GetSymbolAddress(
					libHandle, "mapGetRegistrationAlgorithmProfile");

			if (pUIDFunction == NULL)
			{
				mapExceptionStaticMacro(MissingSymbolException,
										"Error. DLL seems to be invalid; mapGetRegistrationAlgorithmUID symbol is missing. File path: " <<
										libraryFile << ". Error note: " << itksys::DynamicLoader::LastError());
			}

			if (pProfileFunction == NULL)
			{
				mapExceptionStaticMacro(MissingSymbolException,
										"Error. DLL seems to be invalid; mapGetRegistrationAlgorithmProfile symbol is missing. File path: "
										<< libraryFile << ". Error note: " << itksys::DynamicLoader::LastError());
			}

			if (pInstanceFunction == NULL)
			{
				mapExceptionStaticMacro(MissingSymbolException,
										"Error. DLL seems to be invalid; mapGetRegistrationAlgorithmInstance symbol is missing. File path: "
										<< libraryFile << ". Error note: " << itksys::DynamicLoader::LastError());
			}

			//DLL seems to be valid -> Get the UID and compile the DLL info

			::map::algorithm::UID::Pointer spUIDdll;
			(*pUIDFunction)(spUIDdll);

			if (spUIDdll.IsNull())
			{
				mapExceptionStaticMacro(InvalidUIDException,
										"Error. DLL returns NULL pointer as UID. File path: " << libraryFile);
			}

			map::core::String profileStr;
			(*pProfileFunction)(profileStr);

			//copy the UID information to a UID that is not instanciated within the DLL, thus the new UID does not depend on the DLL.
			::map::algorithm::UID::Pointer spUID = algorithm::UID::New(spUIDdll->getNamespace(), spUIDdll->getName(),
											spUIDdll->getVersion(), spUIDdll->getBuildTag());

			DLLHandle::Pointer spResult = DLLHandle::New(libHandle, spUID, libraryFile, profileStr);

			dllGuard.deactivate();

			return spResult;
		};


		DLLHandle::Pointer openDeploymentDLL(const core::String& libraryFile)
		{
			return openDeploymentDLL(libraryFile.c_str());
		};


		void closeDeploymentDLL(const DLLHandle* pDLLHandle)
		{
			if (!pDLLHandle)
			{
				mapDefaultExceptionStaticMacro("Error. Passed DLL info pointer is NULL.");
			}

			if (!(pDLLHandle->getLibraryHandle()))
			{
				mapExceptionStaticMacro(InvalidDLLException,
										"Error. Passed library handle is not valid. File path:" << (pDLLHandle->getLibraryFilePath()) <<
										"; handle: " << pDLLHandle->getLibraryHandle());
			}

			if (!itksys::DynamicLoader::CloseLibrary(pDLLHandle->getLibraryHandle()))
			{
				mapExceptionStaticMacro(InvalidDLLException,
										"Error. Passed library cannot be closed; seems not to be a valid DLL. File path:" <<
										pDLLHandle->getLibraryFilePath() << ". Error note: " << itksys::DynamicLoader::LastError());
			}
		};

		::map::algorithm::UID::ConstPointer peekDeploymentDLL(const char* libraryFile)
		{
			DLLHandle::Pointer spHandle = openDeploymentDLL(libraryFile);

			::map::algorithm::UID::ConstPointer spUID;
			::map::core::String tempProfile;

			peekDeploymentDLL(libraryFile, spUID, tempProfile);

			closeDeploymentDLL(spHandle);

			return spUID;
		};

		::map::algorithm::UID::ConstPointer peekDeploymentDLL(const core::String& libraryFile)
		{
			return peekDeploymentDLL(libraryFile.c_str());
		};

		void peekDeploymentDLL(const char* libraryFile, algorithm::UID::ConstPointer& spUID,
							   ::map::core::String& algProfile)
		{
			DLLHandle::Pointer spHandle = openDeploymentDLL(libraryFile);

			spUID = algorithm::UID::New(spHandle->getAlgorithmUID().getNamespace(),
										spHandle->getAlgorithmUID().getName(), spHandle->getAlgorithmUID().getVersion(),
										spHandle->getAlgorithmUID().getBuildTag());
			algProfile = spHandle->getAlgorithmProfileStr();

			closeDeploymentDLL(spHandle);
		};

		void peekDeploymentDLL(const core::String& libraryFile, algorithm::UID::ConstPointer& spUID,
							   ::map::core::String& algProfile)
		{
			peekDeploymentDLL(libraryFile.c_str(), spUID, algProfile);
		};


		RegistrationAlgorithmBasePointer getRegistrationAlgorithm(const DLLHandle* pDLLHandle)
		{
			RegistrationAlgorithmBasePointer spResult = NULL;

			if (!pDLLHandle)
			{
				mapDefaultExceptionStaticMacro("Error. Passed DLL info pointer is NULL.");
			}

			if (!(pDLLHandle->getLibraryHandle()))
			{
				mapExceptionStaticMacro(InvalidDLLException,
										"Error. Passed library handle is not valid. File path:" << (pDLLHandle->getLibraryFilePath()) <<
										"; handle: " << pDLLHandle->getLibraryHandle());
			}

			//DLL is not correctly loaded. Check for the InterfaceVersion Symbol
			MAP_GET_REGISTRATION_ALGORITHM_INSTANCE_FUNCTION_POINTER pInstanceFunction =
				(MAP_GET_REGISTRATION_ALGORITHM_INSTANCE_FUNCTION_POINTER) itksys::DynamicLoader::GetSymbolAddress(
					pDLLHandle->getLibraryHandle(), "mapGetRegistrationAlgorithmInstance");

			if (pInstanceFunction == NULL)
			{
				mapExceptionStaticMacro(MissingSymbolException,
										"Error. DLL seems to be invalid; mapGetRegistrationAlgorithmInstance symbol is missing. File path: "
										<< pDLLHandle->getLibraryFilePath() << ". Error note: " << itksys::DynamicLoader::LastError());
			}

			//DLL seems to be valid -> Get an algorithm instance

			SyncObject* pSyncObject = Synchronizer::getSyncObject();

			(*pInstanceFunction)(spResult, pSyncObject);

			if (spResult.IsNull())
			{
				mapExceptionStaticMacro(InvalidAlgorithmException,
										"Error. DLL returns NULL pointer as pointer to an algorithm instance. File path: " <<
										pDLLHandle->getLibraryFilePath());
			}

			return spResult;
		};



	} // end namespace deployment
} // end namespace map
