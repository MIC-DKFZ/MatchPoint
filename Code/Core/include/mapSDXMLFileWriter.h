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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapSDXMLFileWriter.h $
*/



#ifndef __MAP_SD_XML_FILE_WRITER_H
#define __MAP_SD_XML_FILE_WRITER_H

#include "mapSDElement.h"
#include "mapSDStreamingInterface.h"

namespace map
{

	namespace structuredData
	{
		//* @TODO Und in der XMLStrReader-Implementierung die Encodings oder ähnliches noch freilegen.

		/** @class XMLFileWriter
		 * @brief Transforms StructuredData elements into xml and store it as file.
		 * Converts a StructuredData element instance or object implementing the StreamingInterface into an xml content.
		 * This content is stored as a file specified by the file path.
		 * @ingroup SD
		 */
		class MAPCore_EXPORT XMLFileWriter: public ::itk::LightObject
		{
		public:
			typedef XMLFileWriter Self;
			typedef ::itk::LightObject Superclass;
			typedef ::itk::SmartPointer<Self> Pointer;
			typedef ::itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(XMLFileWriter, ::itk::LightObject);
			itkNewMacro(Self);

			typedef Element::Pointer ElementPointer;

			void setXSLTFile(const core::String &file);
			core::String getXSLTFile() const;

			/**Write the passed StructuredData element as xml to the specified filepath.
			 * @param [in] filePath String that defines the location of the file. If the file already exists,
			 * it will be overwritten.
			 * @param [in] pElement Pointer to the StructuredData element that should be converted into an
			 * xml file. The pointer must not be NULL.
			 * @pre The Pointer pElement must not be NULL.
			 * @pre The specified file path must specify a file location within an existing directory.*/
			void write(const core::String &filePath, const Element *pElement);

			/**Write the passed instance with a StreamingInterface as xml to the specified filepath
			 * by converting the instance to a StructuredData element.
			 * @param [in] filePath String that defines the location of the file. If the file already exists,
			 * it will be overwritten.
			 * @param [in] pInterface Pointer to the streamable interface instance. The pointer must not be NULL.
			 * @pre The Pointer pInterface must not be NULL.
			 * @pre The specified file path must specify a file location within an existing directory.*/
			void write(const core::String &filePath, const StreamingInterface *pInterface);

		protected:
			core::String _XSLTFile;
			core::String _EncodingType;

			XMLFileWriter();
			~XMLFileWriter();

		private:
			//No copy constructor allowed
			XMLFileWriter(const Self &source);
			void operator=(const Self &); //purposely not implemented
		};

	} //end of namespace structuredData

} //end of namespace map
#endif
