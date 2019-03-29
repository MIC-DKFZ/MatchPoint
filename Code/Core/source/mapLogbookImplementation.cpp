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


#include "mapLogbookImplementation.h"
#include "mapExceptionObject.h"

#include "itkFastMutexLock.h"

#include <cassert>

namespace map
{
	namespace core
	{

      /*! @class SharedFileStreamBase
      * @brief Helper class realizing an std stream handled as a object with smart pointer
      *
      * Reason: Need for a shared_ptr to handle the same stream across different logbook
      * implementations. VS2005 has no std::tr1::shared_ptr. Thus uses the itk::SmartPointer
      * functionality.
      * @ingroup Logging
      */
      class SharedFileStreamBase : public itk::LightObject
      {
      public:
          using Self = SharedFileStreamBase;
          using Superclass = itk::LightObject;
          using Pointer = itk::SmartPointer<Self>;
          using ConstPointer = itk::SmartPointer<const Self>;

          itkTypeMacro(SharedFileStreamBase, itk::LightObject);

          virtual std::ostream& getStream() = 0;

          virtual const std::ostream& getStream() const = 0;

      protected:
          SharedFileStreamBase()
          = default;

          ~SharedFileStreamBase() override
          = default;

      private:

          SharedFileStreamBase(const SharedFileStreamBase&) = delete;  //purposely not implemented
          void operator=(const SharedFileStreamBase&) = delete;  //purposely not implemented
      };


    /*! @class SharedDefaultLogFileStream
    * @brief Helper class realizing an dummy stream handled as a object with smart pointer
    *
    * Reason: Need for a shared_ptr to handle the same stream across different logbook
    * implementations. VS2005 has no std::tr1::shared_ptr. Thus uses the itk::SmartPointer
    * functionality.
    * @ingroup Logging
    */
      class SharedNULLStream : public SharedFileStreamBase
    {
    public:
        using Self = SharedNULLStream;
        using Superclass = itk::LightObject;
        using Pointer = itk::SmartPointer<Self>;
        using ConstPointer = itk::SmartPointer<const Self>;

        itkTypeMacro(SharedNULLStream, itk::LightObject);
        itkNewMacro(Self);

        std::ostream& getStream() override
        {
            return _stream;
        };

        const std::ostream& getStream() const  override
        {
            return _stream;
        };

    protected:
        /*! Helper class that allows to generate a dummy os*/
        class NullBuffer : public std::streambuf
        {
        public:
            int overflow(int c) override { return c; }
        };

        NullBuffer _buffer;
        std::ostream _stream;

        SharedNULLStream() : _stream(&_buffer)
        {
        };

        ~SharedNULLStream() override
        = default;

    private:

        SharedNULLStream(const SharedNULLStream&) = delete;  //purposely not implemented
        void operator=(const SharedNULLStream&) = delete;  //purposely not implemented
    };


		/*! @class SharedDefaultLogFileStream
		* @brief Helper class realizing an std stream handled as a object with smart pointer
		*
		* Reason: Need for a shared_ptr to handle the same stream across different logbook
		* implementations. VS2005 has no std::tr1::shared_ptr. Thus uses the itk::SmartPointer
		* functionality.
		* @ingroup Logging
		*/
      class SharedDefaultLogFileStream : public SharedFileStreamBase
		{
		public:
			using Self = SharedDefaultLogFileStream;
      using Superclass = SharedFileStreamBase;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

      itkTypeMacro(SharedDefaultLogFileStream, SharedFileStreamBase);
			itkNewMacro(Self);

			std::ostream& getStream() override
			{
				return _stream;
			};

      const std::ostream& getStream() const override
			{
				return _stream;
			};

      std::ofstream& getOFStream()
      {
          return _stream;
      };

      const std::ofstream& getOFStream() const
      {
          return _stream;
      };

		protected:
			std::ofstream _stream;

			SharedDefaultLogFileStream()
			= default;

			~SharedDefaultLogFileStream() override
			= default;

		private:

			SharedDefaultLogFileStream(const SharedDefaultLogFileStream&) = delete;  //purposely not implemented
			void operator=(const SharedDefaultLogFileStream&) = delete;  //purposely not implemented
		};


		//*************************************************************************************************
		//********************  class LogbookImplementation  **********************************************
		//*************************************************************************************************


		LogbookImplementation::LoggerType&
		LogbookImplementation::
		getLogger()
		{
			return *(_spLogger.GetPointer());
		};

		void
		LogbookImplementation::
		initializeOutputs(const String& defaultOutputFileName)
		{
        if (!defaultOutputFileName.empty())
        {
            SharedDefaultLogFileStream::Pointer spNewStream = SharedDefaultLogFileStream::New();

            spNewStream->getOFStream().open(defaultOutputFileName.c_str(), std::ios::out | std::ios::app);

            if (!(spNewStream->getOFStream().is_open()))
            {
                mapLogbookCheckDefaultExceptionMacro(<<
                    "Error: cannot open specified file as default logbook output file. Filename: " <<
                    defaultOutputFileName);
            }

            _spDefaultStream = spNewStream;

            _spDefaultOutput->SetStream(_spDefaultStream->getStream());
        }
        else
        {
            _spDefaultStream = SharedNULLStream::New();
            _spDefaultOutput->SetStream(_spDefaultStream->getStream());
        }

			initializeAdditionalOutputs();

			if (_spItkOutputWindow.IsNotNull())
			{
				_spItkOutputWindow->SetLogger(_spLogger);
			}
		};

		void
		LogbookImplementation::
		addAdditionalLogOutput(OutputType* pOutput)
		{
			assert(pOutput); //output may not be null.
			std::pair<OutputContainerType::iterator, bool> result;
			result = _additionalOutputs.insert(pOutput);

			if (result.second)
			{
				//this output isn't already in the set,
				//so it was added and shall also be added to the logger.
				_spLogger->AddLogOutput(pOutput);
			}
		};

		LogbookImplementation::Pointer
		LogbookImplementation::
		clone() const
		{
			Pointer spNewImpl = LogbookImplementation::New();
			spNewImpl->_additionalOutputs = this->_additionalOutputs;
			spNewImpl->_spDefaultStream = this->_spDefaultStream;
			spNewImpl->_spDefaultOutput->SetStream(spNewImpl->_spDefaultStream->getStream());
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
		clone(const String& newDefaultOutputFileName) const
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
			for (const auto & _additionalOutput : _additionalOutputs)
			{
				_spLogger->AddLogOutput(_additionalOutput);
			}
		};

		LogbookImplementation::
		LogbookImplementation()
		{
			_spItkOutputWindow = nullptr;
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
			_spLogger = nullptr;
			_spDefaultOutput = nullptr;
		};


	} // end namespace core
} // end namespace map