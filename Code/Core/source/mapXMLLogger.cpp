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


#include "mapXMLLogger.h"
#include "mapSDXMLStrWriter.h"

#include "itksys/SystemTools.hxx"

namespace map
{
	namespace core
	{

		std::string
		escapeSpecialXMLCharacters(std::string content)
		{
			return ::map::structuredData::encodeForXml(content);
		};

		std::string
		XMLLogger::
		BuildFormattedEntry(itk::LoggerBaseEnums::PriorityLevel level, std::string const& content)
		{

			std::string m_LevelString[] = { "MUSTFLUSH", "FATAL", "CRITICAL",
											"WARNING", "INFO", "DEBUG", "NOTSET"
										  };

			OStringStream s;

			s << "<logentry datetime='" << itksys::SystemTools::GetCurrentDateTime("%d/%m/%Y %H:%M:%S") << "'";
			s.precision(30);
			s << " timestamp='" << m_Clock->GetTimeInSeconds() << "'";
			s << " priorityLevel='" << m_LevelString[static_cast<size_t>(level)] << "' logger='" << this->GetName() << "'>" <<
			  content << "</logentry>";

			return s.str();
		};

	} // end namespace core
} // end namespace map