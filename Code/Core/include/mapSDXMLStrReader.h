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



#ifndef __MAP_SD_XML_READER_H
#define __MAP_SD_XML_READER_H

#include "mapSDElement.h"

namespace map
{

	namespace structuredData
	{
		//* @TODO Und in der XMLStrReader-Implementierung die Encodings oder ähnliches noch freilegen.

		/** @class XMLStrReader
		 * @brief Takes a xml containing string and converts it into StructuredData elements
		 * Converts the xml string into StructuredData elements. The root element is always representing
		 * the complete string, all sub elements of the root element are top level xml elemtents found
		 * in the string.
		 * @ingroup SD
		 */
		class MAPCore_EXPORT XMLStrReader: public ::itk::LightObject
		{
		public:
			using Self = XMLStrReader;
			using Superclass = ::itk::LightObject;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;

			itkTypeMacro(XMLStrReader, ::itk::LightObject);
			itkNewMacro(Self);

			using XMLRawDataType = core::String;
			using ElementPointer = Element::Pointer;

			/**Reads the string and converts the xml top level element and all
			 * sub elements into structured data elements.
			 * @param [in] Reference to the xml string
			 * @return SmartPointer to the top level xml element. If the string contains no XML element
			 * an exception will be raised.*/
			ElementPointer readXMLContent(const XMLRawDataType& /*data*/);

			/**Reads the string and converts it into structured
			 * data elements.
			 * @param [in] Reference to the xml string
			 * @return SmartPointer to the root element. The root
			 * element designates the string itself. All found
			 * top level xml elements and information will be added as sub elements
			 * to the root StructuredData element.*/
			ElementPointer read(const XMLRawDataType& /*data*/);

		protected:
			XMLStrReader();
			~XMLStrReader() override;

		private:
			//No copy constructor allowed
			XMLStrReader(const Self& source) = delete;
			void operator=(const Self&) = delete;  //purposely not implemented
		};

		/**
		* Helper function that deescapes substrings that are xml encoded (e.g. "&gt;" -> ">")
		* @param sSrc The src string to escape.
		* @return sSrc encoded for insertion into xml.
		* @ingroup SD
		*/
		MAPCore_EXPORT core::String decodeForXml(const core::String& sSrc);

	}  // namespace structuredData

}  // namespace map
#endif
