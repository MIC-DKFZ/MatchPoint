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


#ifndef __MAP_LOGBOOK_IMPLEMENTATION_H
#define __MAP_LOGBOOK_IMPLEMENTATION_H


#include "itkLoggerOutput.h"
#include "itkLoggerThreadWrapper.h"
#include "itkStdStreamLogOutput.h"

#include "mapXMLLogger.h"
#include "mapString.h"

#include <memory>

namespace map
{
	namespace core
	{
		//forward declaration
    class SharedFileStreamBase;

		/*! @class LogbookImplementation
		* @brief Helper class realizing the internel implemntation of the logbook.
		*
		* This class is used to abstract the implmentation of the logbook (PIMPL-Idiom) and
		* to realize a strong exception guarantee for the logbook.
		* @ingroup Logging
		*/
		class MAPCore_EXPORT LogbookImplementation : public itk::LightObject
		{
		public:
			typedef LogbookImplementation  Self;
			typedef itk::LightObject  Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(LogbookImplementation, itk::LightObject);
			itkNewMacro(Self);

			typedef itk::LoggerThreadWrapper<XMLLogger>			LoggerType;
			typedef LoggerType::Pointer						LoggerPointer;
			typedef LoggerType::OutputType				OutputType;
			typedef OutputType::Pointer				    OutputPointer;
			typedef LoggerType::PriorityLevelType	PriorityLevelType;;

			/*! Returns a reference to the normal logger.
			 @eguarantee no fail
			 */
			LoggerType& getLogger(void);

			/*! Initializing the default output by opening a stream to the specified file.
			 * If additional outputs exist (e.g. by cloning) they will also be setup.
			 * @eguarantee basis*/
			void initializeOutputs(const String& defaultOutputFileName);

			/*! adds additional log outputs to the logbook.
			 * If the output has already been added to the logbook,
			 * the method doesn't add it once again.
			 * @eguarantee basis
			 * @pre pOuput must be a valid pointer to OutputType.*/
			void addAdditionalLogOutput(OutputType* pOutput);

			/*! clones the logbook implementation.
			* @return Smart pointer to the cloned implementation.*/
			Pointer clone(void) const;

			/*! clones the logbook implementation and sets a new default out put.
			 * @param [in] defaultOutputFileName Name of the new default output file, that should be opened.
			 * @return Smart pointer to the cloned and modified implementation.*/
			Pointer clone(const String& newDefaultOutputFileName) const;

			/*! Pointer to the itk output window != NULL if attachITKOutputWindow() was called.
			 * needed by the logbook if the logger must be updated.*/
			itk::LoggerOutput::Pointer _spItkOutputWindow;
			PriorityLevelType _currentPriorityLevel;

		protected:
			void initializeAdditionalOutputs();

			LoggerPointer _spLogger;

			typedef std::set< OutputPointer >   OutputContainerType;
			OutputContainerType _additionalOutputs;

			typedef itk::StdStreamLogOutput	    DefaultOutputType;
			typedef DefaultOutputType::Pointer  DefaultOutputPointer;
			DefaultOutputPointer _spDefaultOutput;

      typedef itk::SmartPointer<SharedFileStreamBase> StreamPointer;

			StreamPointer _spDefaultStream;

			LogbookImplementation();

			virtual ~LogbookImplementation();

		private:

			LogbookImplementation(const LogbookImplementation&);  //purposely not implemented
			void operator=(const LogbookImplementation&);  //purposely not implemented
		};

	} // end namespace core
} // end namespace map


#include "mapLogbookMacros.h"

#endif
