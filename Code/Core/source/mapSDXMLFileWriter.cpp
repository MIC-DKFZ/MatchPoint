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



#include "mapSDXMLFileWriter.h"
#include "mapSDXMLStrWriter.h"
#include "mapSDExceptions.h"

namespace map
{

	namespace structuredData
	{
		void
		XMLFileWriter::
		setXSLTFile(const core::String& file)
		{
			this->_XSLTFile = file;
		};

		::map::core::String
		XMLFileWriter::
		getXSLTFile() const
		{
			return this->_XSLTFile;
		};

		void
		XMLFileWriter::
		write(const core::String& filePath, const Element* pElement)
		{
			if (pElement == nullptr)
			{
				mapDefaultExceptionMacro( <<
										  "Error, cannot write passed StructuredData element to an xml file. Passed element is NULL.");
			}

			XMLIntendedStrWriter::Pointer spStrWriter = XMLIntendedStrWriter::New();

			::map::core::String savedStr = spStrWriter->write(pElement);

			std::ofstream file;

			std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
			file.open(filePath.c_str(), iOpenFlag);

			if (!file.is_open())
			{
				mapDefaultExceptionMacro( << "Cannot open or create specified file to save. File path: " <<
										  filePath);
			}

			file << R"(<?xml version="1.0" encoding=")" << _EncodingType << "\"?>\n";

			if (!_XSLTFile.empty())
			{
				file << R"(<?xml-stylesheet type="text/xsl" href=")" << _XSLTFile << "\"?>\n";
			}

			file << savedStr;
			file.close();
		};

		void
		XMLFileWriter::
		write(const core::String& filePath, const StreamingInterface* pInterface)
		{
			if (pInterface == nullptr)
			{
				mapDefaultExceptionMacro( <<
										  "Error, cannot write passed object to an xml file. Passed interface is NULL.");
			}

			ElementPointer spData = pInterface->streamToStructuredData();
			this->write(filePath, spData);
		};

		XMLFileWriter::
		XMLFileWriter()
		{
			this->_XSLTFile = "";
			this->_EncodingType = "ISO-8859-1";
		};

		XMLFileWriter::
		~XMLFileWriter()
		= default;

	} //end of namespace structuredData

} //end of namespace map
