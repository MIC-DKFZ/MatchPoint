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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/source/mapSDXMLStrReader.cpp $
*/




#include "expat.h"
#include <map>
#include <vector>
#include <deque>
#include <assert.h>

#include "mapSDXMLStrReader.h"
#include "mapSDExceptions.h"
#include "mapSDTags.h"

namespace map
{

	namespace structuredData
	{

		core::String decodeForXmlChar(const core::String &sSrc, const core::String &searchStr, const core::String &newStr)
		{
			core::String sRet = sSrc;

			core::String::size_type pos = sRet.find(searchStr);

			while (pos != core::String::npos)
			{
				sRet.erase(pos, searchStr.size());
				sRet.insert(pos, newStr);
			}

			return sRet;
		}


		core::String decodeForXml(const core::String &sSrc)
		{
			core::String sRet = decodeForXmlChar(sSrc, "&apos;", "\'");
			sRet = decodeForXmlChar(sRet, "&quot;", "\"");
			sRet = decodeForXmlChar(sRet, "&gt;", ">");
			sRet = decodeForXmlChar(sRet, "&lt;", "<'");
			sRet = decodeForXmlChar(sRet, "&amp;", "&");

			return sRet;
		}


		////////////////////////////////////////////////////////////////////////
		/// Implementation of map::XMLStrReaderImpl ///////////////////////////
		////////////////////////////////////////////////////////////////////////

		/** @class XMLStrReaderImpl
		* @brief Private implementation of the XMLStrReader.
		*
		* This class does the real work of XMLStrReader as non public implementation
		* to cover the internals like the use of expat.
		* The concept of the class has been designed for the requirements in free
		* and has been motivated by the wish using present resources of itk and introduce as
		* less as possible third-party libraries.
		*
		* @ingroup XML
		*/
		class XMLStrReaderImpl
		{
		public:
			virtual const char *GetNameOfClass() const
			{
				return "XMLStrReaderImpl";
			};

			typedef std::pair<core::String, core::String> AttributeType;
			typedef std::map<core::String, core::String> AttributesType;
			//uses vector for saving, to avoid automatic sort feature of stl::map
			typedef std::vector<AttributeType> AttributesSaveListType;

			typedef Element::Pointer ElementPointer;

			/** Function to load a structure from a xml string. The function creates
			* an expat parser, manages the callbacks, calls Reset() and ResetRequirements().
			* To control the loading process, the function SubElementLoadProcessing() should be
			* overridden. When the loading is finished, it will be checked, if the requirements
			* are meet, the expat resources will be freed.
			* @param [in] rsData Reference to the whole data of the xml element (with start and end tag and attributes)*/
			ElementPointer LoadFromString(const core::String &rsData);

			/** Resets the object to default/initial state*/
			void Reset();

			/** Default constructor */
			XMLStrReaderImpl();

			/** destructor */
			~XMLStrReaderImpl();

		protected:

			/** Function is called by LoadFromXMLString() to handle the Attributes contained by the xml string
			* for the passed SD element.
			* @param [in] pElement Pointer to the element that should get the attributes set.
			* @param [in] rAttributes Reference to a stl map with the attributes of the element.*/
			static void AttributesLoadProcessing(Element *pElement, const AttributesType &rAttributes);

			static void CB_Static_StartElement(void *parser, const char *name,
			                                   const char **pAttributes);

			static void CB_Static_EndElement(void *parser, const char *name);

			static void CB_Static_CharacterDataHandler(void *parser, const char *data,
			                                           int length);

			/** Callback function -- called from XML parser when starting tag
			* encountered
			*/
			void CB_StartElement(const char *name, const char **pAttributes);

			/** Callback function -- called from XML parser when ending tag
			* encountered
			*/
			void CB_EndElement(const char *name);

			/** Callback function -- called from XML parser with the character data
			* for a XML element
			*/
			void CB_CharacterDataHandler(const char *inData, int inLength);

			/** Function adds the content of m_currentElementText to the Value of the passed element.
			* @param [in] pElement Pointer to the element that should get the content of m_currentElementText.*/
			void TransferCurrentText(Element *pElement);

			/** Converts the attribute structure passed by expat to a stl string map.*/
			static AttributesType ConvertExpatAttrToMap(const char **pAttributes);

			/** pointer to the data string passed with ReadString*/
			const core::String *m_pLoadData;

			ElementPointer m_spRootElement;

			typedef std::deque<ElementPointer> ElementStackType;

			/**Stack of all structured data element that are open right now. Therefor had
			* an start tag but no stop tag yet. An element is added to the stack when its
			* xml start tag occures and is removed if the proper end tag is found.*/
			ElementStackType m_stack;

			/**String containing all data received by CB_CharacterDataHandler
			* it will used to set the current element's value.*/
			core::String m_currentElementText;

			/** Pointer to the expat parser*/
			XML_Parser m_Parser;
		};

		void
		XMLStrReaderImpl::
		CB_Static_StartElement(void *parser, const char *name,
		                       const char **pAttributes)
		{
			// Begin element handler that is registered with the XML_Parser.
			// This just casts the user data to an XMLStrReaderImpl and calls
			// StartElement.
			static_cast<XMLStrReaderImpl *>(parser)->CB_StartElement(name, pAttributes);
		}

		void
		XMLStrReaderImpl::
		CB_Static_EndElement(void *parser, const char *name)
		{
			// End element handler that is registered with the XML_Parser.  This
			// just casts the user data to an XMLStrReaderImpl and calls EndElement.
			static_cast<XMLStrReaderImpl *>(parser)->CB_EndElement(name);
		}

		void
		XMLStrReaderImpl::
		CB_Static_CharacterDataHandler(void *parser, const char *data,
		                               int length)
		{
			// Character data handler that is registered with the XML_Parser.
			// This just casts the user data to an XMLStrReaderImpl and calls
			// CharacterDataHandler.
			static_cast<XMLStrReaderImpl *>(parser)->CB_CharacterDataHandler(data, length);
		}


		XMLStrReaderImpl::ElementPointer
		XMLStrReaderImpl::
		LoadFromString(const core::String &rsRawData)
		{
			Reset();

			m_Parser = XML_ParserCreate(0);
			XML_SetElementHandler(m_Parser, &CB_Static_StartElement, &CB_Static_EndElement);
			XML_SetCharacterDataHandler(m_Parser, &CB_Static_CharacterDataHandler);
			XML_SetUserData(m_Parser, this);

			m_pLoadData = &rsRawData;
			m_spRootElement = Element::createElement("ROOT", "");
			m_stack.push_back(m_spRootElement);

			bool result = XML_Parse(m_Parser, m_pLoadData->c_str(), m_pLoadData->size(), true);

			if (!result)
			{
				core::String errorMsg(XML_ErrorString(XML_GetErrorCode(m_Parser)));
				mapDefaultExceptionMacro( << "Expat error while parsing raw string. Error: " << errorMsg << "; Error position: " << XML_GetCurrentLineNumber(m_Parser) << ":" << XML_GetCurrentColumnNumber(m_Parser));
			}

			ElementPointer spResult = m_spRootElement;

			Reset();

			return spResult;
		};

		void
		XMLStrReaderImpl::
		CB_StartElement(const char *name, const char **pAttributes)
		{
			ElementPointer spNewElement = Element::createElement(core::String(name), "");
			m_stack.back()->addSubElement(spNewElement);

			//any data yet stored in m_CurrentElementText should now be stored to
			//the current last element in stack, befor pushing the new one.
			TransferCurrentText(m_stack.back());

			m_stack.push_back(spNewElement);

			//set attributes
			AttributesLoadProcessing(spNewElement, ConvertExpatAttrToMap(pAttributes));
		};

		void
		XMLStrReaderImpl::
		CB_EndElement(const char *name)
		{
			if (core::String(name) != m_stack.back()->getTag())
			{
				mapDefaultExceptionMacro( << "Error. XML structure seems not to be correct. XML tags seem to be mingeld end tag does not fit the last start tag. Start tag: " << m_stack.back()->getTag() << "; end tag: " << name);
			}

			if (m_stack.size() < 2)
			{
				mapDefaultExceptionMacro( << "Error. XML structure seems not to be correct. End tag found, but no top level element was started. End tag: " << name);
			}

			//any data yet stored in m_CurrentElementText should now be stored to
			//the current last element in stack, befor element is "popped".
			TransferCurrentText(m_stack.back());

			m_stack.pop_back();
		};

		void
		XMLStrReaderImpl::
		CB_CharacterDataHandler(const char *inData, int inLength)
		{
			m_currentElementText.append(inData, inLength);
		};

		void
		XMLStrReaderImpl::
		TransferCurrentText(Element *pElement)
		{
			assert(pElement);
			pElement->setValue(pElement->getValue() + decodeForXml(m_currentElementText));
			m_currentElementText.clear();
		};

		XMLStrReaderImpl::
		XMLStrReaderImpl()
		{
			m_Parser = NULL;
			Reset();
		};

		XMLStrReaderImpl::
		~XMLStrReaderImpl()
		{
			Reset();
		};

		void
		XMLStrReaderImpl::
		AttributesLoadProcessing(Element *pElement, const AttributesType &attributes)
		{
			for (AttributesType::const_iterator pos = attributes.begin(); pos != attributes.end(); ++pos)
			{
				pElement->setAttribute(pos->first, pos->second);
			}
		};

		void
		XMLStrReaderImpl::
		Reset()
		{
			m_stack.clear();
			m_spRootElement = NULL;
			m_pLoadData = NULL;
			m_currentElementText.clear();

			if (m_Parser)
			{
				XML_ParserFree(m_Parser);
				m_Parser = NULL;
			}
		};

		XMLStrReaderImpl::AttributesType
		XMLStrReaderImpl::
		ConvertExpatAttrToMap(const char **pAttributes)
		{
			AttributesType attrs;

			const char **pActAttr = pAttributes;

			while (*pActAttr)
			{
				core::String sKey = *pActAttr;
				pActAttr++;
				core::String sValue = *pActAttr;
				pActAttr++;
				attrs.insert(AttributeType(sKey, sValue));
			};

			return attrs;
		};

		////////////////////////////////////////////////////////////////////////
		/// Implementation of FREE::XMLStrReader ///////////////////////////////
		////////////////////////////////////////////////////////////////////////

		XMLStrReader::ElementPointer
		XMLStrReader::
		read(const XMLRawDataType &data)
		{
			XMLStrReaderImpl implementation;

			ElementPointer spResult = NULL;

			spResult = implementation.LoadFromString(data);

			if (spResult)
			{
				spResult->setAttribute(tags::SDInternalSourceReader, tags::SDInternalSourceReader_string, true);
				spResult->setAttribute(tags::SDInternalSourceFormat, tags::SDInternalSourceFormat_xml, true);
			}

			return spResult;
		};

		XMLStrReader::ElementPointer
		XMLStrReader::
		readXMLContent(const XMLRawDataType &data)
		{
			XMLStrReaderImpl implementation;

			ElementPointer spResult = NULL;

			spResult = implementation.LoadFromString(data);

			if (spResult->getSubElementsCount() < 1)
			{
				mapDefaultExceptionMacro( << "Error. String does not contain any xml elements. String: " << data);
			}

			spResult = spResult->getSubElement(0);

			spResult->setAttribute(tags::SDInternalSourceReader, tags::SDInternalSourceReader_string, true);
			spResult->setAttribute(tags::SDInternalSourceFormat, tags::SDInternalSourceFormat_xml, true);

			return spResult;
		};

		XMLStrReader::
		XMLStrReader()
		{
		};

		XMLStrReader::
		~XMLStrReader()
		{
		};

	} //end of namespace structuredData

} //end of namespace free
