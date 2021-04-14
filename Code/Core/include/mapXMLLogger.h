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


#ifndef __MAP_XML_LOGGER_H
#define __MAP_XML_LOGGER_H

#include "itkLogger.h"

#include "mapMacros.h"
#include "mapMAPCoreExports.h"


namespace map
{
	namespace core
	{

		/*! @class XMLLogger
		* @brief Logger based on itk::Logger but generating XML outputs.
		*
		* Build xml log entries, regarding the following pattern:\n
		* <logentry time='...' priorityLevel='...' logger='...'>\n
		*   ...content...\n
		* </logentry>
		* @remark The logger does not escape any special xml characters,
		* thus it is possible to inject further xml strutcures with the content
		* string. If you want to prevent such an injection you may convert the
		* string we the global function escapeSpecialXMLCharacters() befor you pass
		* the string to the logger.
		* @ingroup Logging
		*/
		class MAPCore_EXPORT XMLLogger: public itk::Logger
		{
		public:
			using Self = XMLLogger;
			using Superclass = Logger;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			/** Run-time type information (and related methods). */
			itkTypeMacro(XMLLogger, itk::Logger);

			/** New macro for creation of through a Smart Pointer */
			itkNewMacro(Self);

			/** Provides a xml formatted log entry */
			std::string BuildFormattedEntry(itk::LoggerBaseEnums::PriorityLevel level, std::string const& content) override;

		protected:

			/** Constructor */
			XMLLogger() = default;

			/** Destructor */
			~XMLLogger() override = default;

		private:
			XMLLogger(const Self&) = delete;  //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented
		};

		/*! Converts the passed content and "escapes" any special xml characters.
		 * (e.g. "<" to "&lt;").
		 * @return Converted string.*/
		MAPCore_EXPORT std::string escapeSpecialXMLCharacters(std::string content);

	} // end namespace core
} // end namespace map

#endif
