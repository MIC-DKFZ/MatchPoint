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



#ifndef __MAP_SD_XML_FILE_READER_H
#define __MAP_SD_XML_FILE_READER_H

#include "mapSDElement.h"
#include "mapSDStreamingInterface.h"

namespace map
{

	namespace structuredData
	{

		/** @class XMLFileReader
		 * @brief Takes a xml containing file and converts its content into StructuredData elements
		 * Converts the xml content of a file into StructuredData elements. The root element is always representing
		 * the complete file, all sub elements of the root element are top level xml elemtents found
		 * in the string.
		 * @ingroup SD
		 */
		class MAPCore_EXPORT XMLFileReader: public ::itk::LightObject
		{
		public:
			typedef XMLFileReader Self;
			typedef ::itk::LightObject Superclass;
			typedef ::itk::SmartPointer<Self> Pointer;
			typedef ::itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(XMLFileReader, ::itk::LightObject);
			itkNewMacro(Self);

			typedef Element::Pointer ElementPointer;

			/**Reads the content of a file. The content will be handled as XML and parsed
			 * to generate the according structured data elements.
			 * @param [in] filePath String that defines the location of the file that should be read.
			 * @return SmartPointer to the root element. The root
			 * element designates the file itself. All found
			 * top level xml elements will be added as sub elements
			 * to the root StructuredData element.*/
			ElementPointer read(const core::String& filePath);

			/**Reads StructuredData elements from the the specified filepath and streams it to the passed instance of the StreamingInterface
			 * @param [in] filePath String that defines the location of the file.
			 * @param [in] pInterface Pointer to the streamable interface instance. The pointer must not be NULL.
			 * @pre The Pointer pInterface must not be NULL.
			 * @pre The specified file path must specify a file location within an existing directory.*/
			void read(const core::String& filePath, StreamingInterface* pInterface);

			/**Returns the xml top level element read from the file.
			 * @return SmartPointer to the top level element of the read file. If no file has been read
			 * successfully or the file does not contain an xml element the return is NULL.*/
			ElementPointer getXMLContent();

		protected:
			ElementPointer _spRoot;

			XMLFileReader();
			~XMLFileReader();

		private:
			//No copy constructor allowed
			XMLFileReader(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};


	} //end of namespace structuredData

} //end of namespace map
#endif
