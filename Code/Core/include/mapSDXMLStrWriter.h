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



#ifndef __MAP_SD_XML_STR_WRITER_H
#define __MAP_SD_XML_STR_WRITER_H

#include <vector>
#include <map>

#include "mapSDElement.h"

namespace map
{

	namespace structuredData
	{
		/** @class XMLStrWriter
		 @brief Takes a StructuredData element and converts it into a plain xml string.
		 @remark Internal attributes (namespace "sdInternal:") will be removed before
			 StructuredData will be converted into a string.
		 @ingroup SD
		*/
		class MAPCore_EXPORT XMLStrWriter: public ::itk::LightObject
		{
		public:
			using Self = XMLStrWriter;
			using Superclass = ::itk::LightObject;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;

			itkTypeMacro(XMLStrWriter, ::itk::LightObject);
			itkNewMacro(Self);

			/**Transforms a passed element into the according xml
			* structure and returns it as a string.
			* @pre Passed element pointer must not be NULL.
			* @param [in] Pointer to the structured data element
			* @return String continingxontmartPointer to the root element. The root
			* element designates the string itself. All found
			* top level xml elements will be added as sub elements
			* to the root StructuredData element.*/
			::map::core::String write(const Element* pElement) const;

		protected:
			using ElementLevelType = unsigned long;

			virtual core::String writeElement(const Element* pElement, const ElementLevelType& level) const;
			virtual core::String writeAttributes(const Element* pElement, const ElementLevelType& level) const;
			virtual core::String writeSubElements(const Element* pElement, const ElementLevelType& level) const;

			XMLStrWriter();
			~XMLStrWriter() override;

		private:
			//No copy constructor allowed
			XMLStrWriter(const Self& source) = delete;
			void operator=(const Self&) = delete;  //purposely not implemented
		};

		/** @class XMLIntendedStrWriter
		 @brief Takes a StructuredData element and converts it into a formated and intended xml string.
		   @remark Internal attributes (namespace "sdInternal:") will be removed before
			StructuredData will be converted into a string.
		 @ingroup SD
		*/
		class MAPCore_EXPORT XMLIntendedStrWriter: public XMLStrWriter
		{
		public:
			using Self = XMLIntendedStrWriter;
			using Superclass = XMLStrWriter;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;

			itkTypeMacro(XMLIntendedStrWriter, XMLStrWriter);
			itkNewMacro(Self);

		protected:
			using ElementLevelType = Superclass::ElementLevelType;

			core::String writeElement(const Element* pElement, const ElementLevelType& level) const override;

			XMLIntendedStrWriter();
			~XMLIntendedStrWriter() override;

		private:
			//No copy constructor allowed
			XMLIntendedStrWriter(const Self& source) = delete;
			void operator=(const Self&) = delete;  //purposely not implemented
		};

		/**
		* Helper function that escape characters that will interfere with xml.
		* @param sSrc The src string to escape.
		* @return sSrc encoded for insertion into xml.
		* @ingroup SD
		*/
		MAPCore_EXPORT core::String encodeForXml(const core::String& sSrc);

	} //end of namespace structuredData

} //end of namespace map
#endif
