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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/source/mapSDXMLFileReader.cpp $
*/



#include <map>
#include <vector>
#include <assert.h>

#include "itksys/SystemTools.hxx"

#include "mapSDXMLStrReader.h"
#include "mapSDXMLFileReader.h"
#include "mapSDExceptions.h"
#include "mapSDTags.h"

namespace map
{

	namespace structuredData
	{

		XMLFileReader::ElementPointer
		XMLFileReader::
		read(const core::String &filePath)
		{
			ElementPointer spResult = NULL;

			std::ifstream file;

			std::ios_base::openmode iOpenFlag = std::ios_base::in;
			file.open(filePath.c_str(), iOpenFlag);

			if (!file.is_open())
			{
				mapDefaultExceptionMacro( << "Cannot open or create specified file to load. File path: " << filePath);
			}

			core::String data;
			bool hasError = false;
			std::streamsize filesize = itksys::SystemTools::FileLength(filePath.c_str());
			char *buffer = new char [filesize];

			try
			{
				file.read(buffer, filesize);

				std::streamsize gsize = file.gcount();

				data.insert(0, buffer, gsize);
			}
			catch (...)
			{
				hasError = true;
			}

			delete[] buffer;
			file.close();

			if (hasError)
			{
				mapDefaultExceptionMacro( << "Error while reading file content into buffer. File path:" << filePath);
			}


			XMLStrReader::Pointer spStrReader = XMLStrReader::New();

			spResult = spStrReader->read(data);

			spResult->setAttribute(tags::SDInternalSourceReader, tags::SDInternalSourceReader_file, true);
			spResult->setAttribute(tags::SDInternalSourceURI, filePath, true);

			_spRoot = spResult;

			return spResult;
		};

		void
		XMLFileReader::
		read(const core::String &filePath, StreamingInterface *pInterface)
		{
			if (!pInterface)
			{
				mapDefaultExceptionMacro( << "Error, cannot read passed object from xml file. Passed interface is NULL.");
			}

			read(filePath);
			pInterface->streamFromStructuredData(getXMLContent());
		};

		XMLFileReader::ElementPointer
		XMLFileReader::
		getXMLContent()
		{
			ElementPointer spResult = NULL;

			if (_spRoot.IsNotNull())
			{
				if (_spRoot->getSubElementsCount() > 0)
				{
					spResult = _spRoot->getSubElement(0);
				}
			}

			return spResult;
		};

		XMLFileReader::
		XMLFileReader()
		{
			_spRoot = NULL;
		};

		XMLFileReader::
		~XMLFileReader()
		{
		};

	} //end of namespace structuredData

} //end of namespace map
