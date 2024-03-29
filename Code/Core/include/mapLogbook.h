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


#ifndef __MAP_LOGBOOK_H
#define __MAP_LOGBOOK_H

#include "itkLoggerBase.h"
#include "itkLoggerOutput.h"
#include <mutex>

#include "mapXMLLogger.h"
#include "mapString.h"
#include "mapSyncObject.h"
#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		//forward declarations

		class LogbookImplementation;

		/*! @class Logbook
		* @brief Helper class for centralized logging.
		*
		* This class offers a logger as singeltons and a centralized access to its
		* logging functionality. This class is used within MatchPoint for default logging purposes. By
		* default the logging will be saved in a xml file (matchpoint.log in the current working directory).
    * The file may be changed any time, also you may add additional outputs. You can also deactivate the
    * default file output by setting the default log output file to an empty string.
		* @ingroup Logging
		*/
		class MAPCore_EXPORT Logbook
		{
		public:
			using OutputType = itk::LoggerBase::OutputType;
			using PriorityLevelType = itk::LoggerBaseEnums::PriorityLevel;

			/*! Passes the content to normal and error logger.
			 * @eguarantee strong*/
			static void write(PriorityLevelType level, const String& content);

			/*! Helper methods: Passes the content to normal and error logger with priority level "debug". */
			static void debug(const String& message)
			{
				if (_currentPriorityLevel == itk::LoggerBaseEnums::PriorityLevel::DEBUG)
				{
					//only call the function and "risk" singelton checking and managing overhead
					//if the message will be logged anyway.
					write(itk::LoggerBaseEnums::PriorityLevel::DEBUG, message);
				}
			}

			/*! Helper methods: Passes the content to normal and error logger with priority level "info". */
			static void info(const String& message)
			{
				if (_currentPriorityLevel != itk::LoggerBaseEnums::PriorityLevel::CRITICAL)
				{
					//only call the function and "risk" singelton checking and managing overhead
					//if the message will be logged anyway.
					write(itk::LoggerBaseEnums::PriorityLevel::INFO, message);
				}
			}

			/*! Helper methods: Passes the content to normal and error logger with priority level "warning". */
			static void warning(const String& message)
			{
				if (_currentPriorityLevel != itk::LoggerBaseEnums::PriorityLevel::CRITICAL)
				{
					//only call the function and "risk" singelton checking and managing overhead
					//if the message will be logged anyway.
					write(itk::LoggerBaseEnums::PriorityLevel::WARNING, message);
				}
			}

			/*! Helper methods: Passes the content to normal and error logger with priority level "critical". */
			static void critical(const String& message)
			{
				write(itk::LoggerBaseEnums::PriorityLevel::CRITICAL, message);
			}

			/*! Helper methods: Passes the content to normal and error logger with priority level "critical". */
			static void error(const String& message)
			{
				write(itk::LoggerBaseEnums::PriorityLevel::CRITICAL, message);
			}

			/*! Helper methods: Passes the content to normal and error logger with priority level "fatal". */
			static void fatal(const String& message)
			{
				write(itk::LoggerBaseEnums::PriorityLevel::FATAL, message);
			}

			/*! Flushes both loggers. */
			static void flush();

			/*! opens file stream to the new file. If it succeeds the the current default file stream will be closed and exchanged.
       * You can deactivate the default log out put by passing an empty string.
			 * @eguarantee strong*/
			static void setDefaultLogFileName(const String& fileName);

			/*! adds additional log outputs to the logbook.
			 * @eguarantee strong
			 * @pre pOuput must not be a NULL pointer.*/
			static void addAdditionalLogOutput(OutputType* pOutput);


			/*! Attaches the central itk output window to the MatchPoint logging, by setting the OutputWindow to
			 * a LoggerOutput using _spLogger.*/
			static void attachITKOutputWindow();

			/*!@eguarantee strong*/
			static PriorityLevelType getLogbookMode();

			/*! Calls sets _currentPriorityLevel and _spLogger PriorityLevel to itk::LoggerBaseEnums::PriorityLevel::DEBUG.
			    Thus everything will be logged.*/
			static void setLogbookToDebugMode();
			/*! Calls sets _currentPriorityLevel and _spLogger PriorityLevel to itk::LoggerBaseEnums::PriorityLevel::INFO.
			    Thus everything will be logged except of debug infos.*/
			static void setLogbookToInfoMode();
			/*! Calls sets _currentPriorityLevel and _spLogger PriorityLevel to itk::LoggerBaseEnums::PriorityLevel::CRITICAL.
			    Thus only criticals, errors and fatals will be logged.*/
			static void setLogbookToCriticalMode();

			/*! Calls sets _currentPriorityLevel and _spLogger PriorityLevel to the passed level.
			 * @remark The logbook must not be in deprecated sync mode. The mode can only be changed
			 * by the host or in standalone logbooks.
			 * @pre The logbook must not be in deprecated sync mode.*/
			static void setLogbookMode(PriorityLevelType level);

			/*! Returns true if there is an valid pointer to a logbook implementation. Returns false if the
			 * logbook wasn't used yet and isn't initialized.
			 * @eguarantee no fail*/
			static bool isInitialized();

			/** This function is called to add all information to pSyncObject
			 * that are needed to performe a synchronisation of an other instance*/
			static void getSynchronization(deployment::SyncObject& pSyncObject);
			/** This function is called to synchronize the instance with
			 * the information of pSyncObject.*/
			static void setSynchronization(const deployment::SyncObject& pSyncObject);
			/** This function is called to desynchronize the instance.*/
			static void deSynchronize();

		protected:
			/*! Creates the implementation singelton if it doesn't exist.*/
			static void initializeLogger();

			/*!changes the own logbook implmentation with the passed one.
			 * The exchange is secured by the mutex.
			 * @eguarantee strong
			 * @pre pImpl must be a valid pointer to an implmentation.
			 * @param [in,out] pImpl Pointer to the new implementation.*/
			static void swapImplementations(LogbookImplementation* pImpl);

			using LogImplPointer = itk::SmartPointer<LogbookImplementation>;
			static LogImplPointer _spLoggerImpl;

			static std::mutex _testMutex;
			static std::mutex _initMutex;

			/*! Indicates of the logbook is on its "own" or synced with an other host
			 * logbook */
			static bool _syncedAsDedicated;

			static PriorityLevelType _currentPriorityLevel;

			static String _defaultFilename;

		private:
			Logbook() = delete; //purposely not implemented

			virtual ~Logbook() = delete; //purposely not implemented

			Logbook(const Logbook&) = delete;  //purposely not implemented
			void operator=(const Logbook&) = delete;  //purposely not implemented
		};

	} // end namespace core
} // end namespace map


#include "mapLogbookMacros.h"

#endif
