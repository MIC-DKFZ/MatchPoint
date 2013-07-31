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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/source/mapLogbookImplementation.cpp $
*/


#include "mapLogbookImplementation.h"
#include "mapExceptionObject.h"

#include "itkFastMutexLock.h"

#include <assert.h>

namespace map
{
	namespace core
	{

		/*! @class SharedDefaultLogFileStream
		* @brief Helper class realizing an std stream handled as a object with smart pointer
		*
		* Reason: Need for a shared_ptr to handle the same stream across different logbook
		* implementations. VS2005 has no std::tr1::shared_ptr. Thus uses the itk::SmartPointer
		* functionality.
		* @ingroup Logging
		*/
		class SharedDefaultLogFileStream : public itk::LightObject
		{
		public:
			typedef SharedDefaultLogFileStream  Self;
			typedef itk::LightObject  Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(SharedDefaultLogFileStream, itk::LightObject);
			itkNewMacro(Self);

			std::ofstream &getStream()
			{
				return _stream;
			};

			const std::ofstream &getStream() const
			{
				return _stream;
			};

		protected:
			std::ofstream _stream;

			SharedDefaultLogFileStream()
			{};

			virtual ~SharedDefaultLogFileStream()
			{};

		private:

			SharedDefaultLogFileStream(const SharedDefaultLogFileStream &); //purposely not implemented
			void operator=(const SharedDefaultLogFileStream &); //purposely not implemented
		};


		//*************************************************************************************************
		//********************  class LogbookImplementation  **********************************************
		//*************************************************************************************************


		LogbookImplementation::LoggerType &
		LogbookImplementation::
		getLogger(void)
		{
			return *(_spLogger.GetPointer());
		};

		void
		LogbookImplementation::
		initializeOutputs(const String &defaultOutputFileName)
		{
			SharedDefaultLogFileStream::Pointer spNewStream = SharedDefaultLogFileStream::New();

			spNewStream->getStream().open(defaultOutputFileName.c_str(), std::ios::out | std::ios::app);

			if (!(spNewStream->getStream().is_open()))
			{
				mapLogbookCheckDefaultExceptionMacro( << "Error: cannot open specified file as default logbook output file. Filename: " << defaultOutputFileName);
			}

			_spDefaultFileStream = spNewStream;

			_spDefaultOutput->SetStream(_spDefaultFileStream->getStream());

			initializeAdditionalOutputs();

			if (_spItkOutputWindow.IsNotNull())
			{
				_spItkOutputWindow->SetLogger(_spLogger);
			}
		};

		void
		LogbookImplementation::
		addAdditionalLogOutput(OutputType *pOutput)
		{
			assert(pOutput); //output may not be null.
			std::pair<OutputContainerType::iterator, bool> result;
			result = _additionalOutputs.insert(pOutput);

			if (result.second == true)
			{
				//this output isn't already in the set,
				//so it was added and shall also be added to the logger.
				_spLogger->AddLogOutput(pOutput);
			}
		};

		LogbookImplementation::Pointer
		LogbookImplementation::
		clone(void) const
		{
			Pointer spNewImpl = LogbookImplementation::New();
			spNewImpl->_additionalOutputs = this->_additionalOutputs;
			spNewImpl->_spDefaultFileStream = this->_spDefaultFileStream;
			spNewImpl->_spDefaultOutput->SetStream(spNewImpl->_spDefaultFileStream->getStream());
			spNewImpl->_spItkOutputWindow = this->_spItkOutputWindow;
			spNewImpl->_currentPriorityLevel = this->_currentPriorityLevel;
			spNewImpl->initializeAdditionalOutputs();

			if (spNewImpl->_spItkOutputWindow.IsNotNull())
			{
				spNewImpl->_spItkOutputWindow->SetLogger(spNewImpl->_spLogger);
			}

			return spNewImpl;
		};

		LogbookImplementation::Pointer
		LogbookImplementation::
		clone(const String &newDefaultOutputFileName) const
		{
			Pointer spNewImpl = LogbookImplementation::New();
			spNewImpl->_additionalOutputs = this->_additionalOutputs;
			spNewImpl->_spItkOutputWindow = this->_spItkOutputWindow;
			spNewImpl->_currentPriorityLevel = this->_currentPriorityLevel;
			spNewImpl->initializeOutputs(newDefaultOutputFileName);

			return spNewImpl;
		};

		void
		LogbookImplementation::
		initializeAdditionalOutputs()
		{
			for (OutputContainerType::iterator pos = _additionalOutputs.begin(); pos != _additionalOutputs.end(); ++pos)
			{
				_spLogger->AddLogOutput(*pos);
			}
		};

		LogbookImplementation::
		LogbookImplementation()
		{
			_spItkOutputWindow = NULL;
			_currentPriorityLevel = itk::LoggerBase::INFO;
			_spLogger = LoggerType::New();
			_spDefaultOutput = DefaultOutputType::New();
			_spLogger->AddLogOutput(_spDefaultOutput);
		};

		LogbookImplementation::
		~LogbookImplementation()
		{
			//ensure that the logger is deleted before the default output (because logger flushes on destruction)
			//if the logger isn't used by other parts of the program.
			_spLogger = 0;
			_spDefaultOutput = 0;
		};


	} // end namespace core
} // end namespace map