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



#ifndef __MAP_SD_XML_FILE_WRITER_H
#define __MAP_SD_XML_FILE_WRITER_H

#include "mapSDElement.h"
#include "mapSDStreamingInterface.h"

namespace map
{

	namespace structuredData
	{
		//* @TODO Und in der XMLStrReader-Implementierung die Encodings oder �hnliches noch freilegen.

		/** @class XMLFileWriter
		 * @brief Transforms StructuredData elements into xml and store it as file.
		 * Converts a StructuredData element instance or object implementing the StreamingInterface into an xml content.
		 * This content is stored as a file specified by the file path.
		 * @ingroup SD
		 */
		class MAPCore_EXPORT XMLFileWriter: public ::itk::LightObject
		{
		public:
			using Self = XMLFileWriter;
			using Superclass = ::itk::LightObject;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;

			itkTypeMacro(XMLFileWriter, ::itk::LightObject);
			itkNewMacro(Self);

			using ElementPointer = Element::Pointer;

			void setXSLTFile(const core::String& file);
			::map::core::String getXSLTFile() const;

			/**Write the passed StructuredData element as xml to the specified filepath.
			 * @param [in] filePath String that defines the location of the file. If the file already exists,
			 * it will be overwritten.
			 * @param [in] pElement Pointer to the StructuredData element that should be converted into an
			 * xml file. The pointer must not be NULL.
			 * @pre The Pointer pElement must not be NULL.
			 * @pre The specified file path must specify a file location within an existing directory.*/
			void write(const core::String& filePath, const Element* pElement);

			/**Write the passed instance with a StreamingInterface as xml to the specified filepath
			 * by converting the instance to a StructuredData element.
			 * @param [in] filePath String that defines the location of the file. If the file already exists,
			 * it will be overwritten.
			 * @param [in] pInterface Pointer to the streamable interface instance. The pointer must not be NULL.
			 * @pre The Pointer pInterface must not be NULL.
			 * @pre The specified file path must specify a file location within an existing directory.*/
			void write(const core::String& filePath, const StreamingInterface* pInterface);

		protected:
			::map::core::String _XSLTFile;
			::map::core::String _EncodingType;

			XMLFileWriter();
			~XMLFileWriter() override;

		private:
			//No copy constructor allowed
			XMLFileWriter(const Self& source) = delete;
			void operator=(const Self&) = delete;  //purposely not implemented
		};

	} //end of namespace structuredData

} //end of namespace map
#endif
