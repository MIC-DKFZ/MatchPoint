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


#include "mapLogbook.h"
#include "mapLogbookImplementation.h"
#include "mapSmartMetaProperty.h"
#include "mapMetaProperty.h"

#include <mutex>

#include <cassert>

namespace map
{
	namespace core
	{

        Logbook::LogImplPointer Logbook::_spLoggerImpl = nullptr;

		std::mutex Logbook::_testMutex;
		std::mutex Logbook::_initMutex;

		Logbook::PriorityLevelType Logbook::_currentPriorityLevel = itk::LoggerBase::INFO;

		bool Logbook::_syncedAsDedicated = false;

		String Logbook::_defaultFilename = "MatchPoint.log";

		void
		Logbook::
		write(PriorityLevelType level, const String& content)
		{
			if (_spLoggerImpl.IsNull())
			{
				initializeLogger();
			}

			_spLoggerImpl->getLogger().Write(level, content);
		};


		void
		Logbook::
		flush()
		{
			if (_spLoggerImpl.IsNotNull())
			{
				_spLoggerImpl->getLogger().Flush();
			}
		};

		void
		Logbook::
		setDefaultLogFileName(const String& fileName)
		{
			if (_spLoggerImpl.IsNotNull() && _defaultFilename != fileName)
			{
				//we need to exchange the implementation
				mapLogDebugStaticMacro( << "Attempt to change logbook default file. New file name: " << fileName);

				LogImplPointer spNewImpl = _spLoggerImpl->clone(fileName);
				//if we reached this point without exception the implementation
				//with the new file is open and established, thus swap the implmentations,
				//store the new default file and print the header.
				swapImplementations(spNewImpl);
				_defaultFilename = fileName;
			}
			else
			{
				_defaultFilename = fileName;
			}
		};

		void
		Logbook::
		addAdditionalLogOutput(OutputType* pOutput)
		{
			assert(pOutput); //must not be null

			if (_spLoggerImpl.IsNull())
			{
				initializeLogger();
			}

			mapLogDebugStaticMacro( << "Add output to logbook. Output: " << pOutput->GetNameOfClass());

			LogImplPointer spNewImpl = _spLoggerImpl->clone();
			spNewImpl->addAdditionalLogOutput(pOutput);

			swapImplementations(spNewImpl);
		};

		void
		Logbook::
		attachITKOutputWindow()
		{
			if (_spLoggerImpl.IsNull())
			{
				initializeLogger();
			}

			mapLogDebugStaticMacro( << "Attached itk ouput window to MatchPoint logbook");

			std::lock_guard<std::mutex> testHolder(_testMutex);
			std::lock_guard<std::mutex> initHolder(_initMutex);

			if (_spLoggerImpl->_spItkOutputWindow.IsNull())
			{

				itk::LoggerOutput::Pointer spNewLogger = itk::LoggerOutput::New();
				itk::OutputWindow::SetInstance(spNewLogger);
				_spLoggerImpl->_spItkOutputWindow = spNewLogger;
			}

			_spLoggerImpl->_spItkOutputWindow->SetLogger(&(_spLoggerImpl->getLogger()));
		};

		Logbook::PriorityLevelType
		Logbook::
		getLogbookMode()
		{
			return _currentPriorityLevel;
		};

		void
		Logbook::
		setLogbookToDebugMode()
		{
			setLogbookMode(itk::LoggerBase::DEBUG);
		};

		void
		Logbook::
		setLogbookToInfoMode()
		{
			setLogbookMode(itk::LoggerBase::INFO);
		};

		void
		Logbook::
		setLogbookToCriticalMode()
		{
			setLogbookMode(itk::LoggerBase::CRITICAL);
		};

		void
		Logbook::
		setLogbookMode(PriorityLevelType level)
		{
			if (_spLoggerImpl.IsNotNull())
			{
				_spLoggerImpl->getLogger().SetPriorityLevel(level);
			}

			_currentPriorityLevel = level;
		};

		bool
		Logbook::
		isInitialized()
		{
			return _spLoggerImpl.IsNotNull();
		};

		void
		Logbook::
		initializeLogger()
		{
			std::lock_guard<std::mutex> testHolder(_testMutex);

			if (_spLoggerImpl.IsNull())
			{
				{
					//mutex lock holder scope
					std::lock_guard<std::mutex> initHolder(_initMutex);
					LogImplPointer spNewImpl = LogbookImplementation::New();
					spNewImpl->initializeOutputs(_defaultFilename);

					_spLoggerImpl = spNewImpl;
				} // end of mutex lock holder scope
			}
		};

		void
		Logbook::
		swapImplementations(LogbookImplementation* pImpl)
		{
			assert(pImpl); //must not be null;

			_testMutex.lock();
			_initMutex.lock();
			_spLoggerImpl = pImpl;
			_initMutex.unlock();
			_testMutex.unlock();
		};

		void
		Logbook::
		getSynchronization(deployment::SyncObject& syncObject)
		{
            core::MetaPropertyBase::Pointer prop = core::SmartMetaProperty<LogbookImplementation>::New(_spLoggerImpl).GetPointer();
            deployment::SyncObject::SyncPropertyMapType::value_type valuePair("Logbook_Impl", prop);
            syncObject._map.insert(valuePair);

            prop = core::MetaProperty<PriorityLevelType>::New(_currentPriorityLevel).GetPointer();
            deployment::SyncObject::SyncPropertyMapType::value_type valuePair2("Logbook_Priority", prop);
            syncObject._map.insert(valuePair2);
		};

		void
		Logbook::
		setSynchronization(const deployment::SyncObject& syncObject)
		{
			LogImplPointer spNewLogger;

			if (syncObject.getProperty("Logbook_Impl", spNewLogger))
			{
				//there is something to sync for the logbook...
				if (spNewLogger.GetPointer() != _spLoggerImpl)
				{
					_syncedAsDedicated = true;
					swapImplementations(spNewLogger);
				}

				syncObject.getProperty("Logbook_Priority", _currentPriorityLevel);
			}
		};

		void
		Logbook::
		deSynchronize()
		{
			mapLogInfoStaticMacro( << "Attempt to desync logbook.");

			LogImplPointer spNewImpl = _spLoggerImpl->clone(Logbook::_defaultFilename);
			//if we reached this point without exception the implementation
			//with the new file is open and established, thus swap the implmentations,
			//store the new default file and print the header.
			swapImplementations(spNewImpl);
			_syncedAsDedicated = false;
		};

	} // end namespace core
} // end namespace map
