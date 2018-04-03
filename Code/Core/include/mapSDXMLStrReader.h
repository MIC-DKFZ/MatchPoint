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
			typedef XMLStrReader Self;
			typedef ::itk::LightObject Superclass;
			typedef ::itk::SmartPointer<Self> Pointer;
			typedef ::itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(XMLStrReader, ::itk::LightObject);
			itkNewMacro(Self);

			typedef core::String XMLRawDataType;
			typedef Element::Pointer ElementPointer;

			/**Reads the string and converts the xml top level element and all
			 * sub elements into structured data elements.
			 * @param [in] Reference to the xml string
			 * @return SmartPointer to the top level xml element. If the string contains no XML element
			 * an exception will be raised.*/
			ElementPointer readXMLContent(const XMLRawDataType&);

			/**Reads the string and converts it into structured
			 * data elements.
			 * @param [in] Reference to the xml string
			 * @return SmartPointer to the root element. The root
			 * element designates the string itself. All found
			 * top level xml elements and information will be added as sub elements
			 * to the root StructuredData element.*/
			ElementPointer read(const XMLRawDataType&);

		protected:
			XMLStrReader();
			~XMLStrReader();

		private:
			//No copy constructor allowed
			XMLStrReader(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

		/**
		* Helper function that deescapes substrings that are xml encoded (e.g. "&gt;" -> ">")
		* @param sSrc The src string to escape.
		* @return sSrc encoded for insertion into xml.
		* @ingroup SD
		*/
		MAPCore_EXPORT core::String decodeForXml(const core::String& sSrc);

	} //end of namespace StructuredData

} //end of namespace free
#endif
