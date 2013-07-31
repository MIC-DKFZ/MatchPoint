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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/source/mapSDXMLStrWriter.cpp $
*/



#include "mapSDXMLStrWriter.h"
#include "mapExceptionObjectMacros.h"
#include "itkIndent.h"

#include <assert.h>

namespace map
{

	namespace structuredData
	{


		core::String encodeForXml(const core::String &sSrc)
		{
			core::OStringStream sRet;

			for (core::String::const_iterator iter = sSrc.begin(); iter != sSrc.end(); iter++)
			{
				unsigned char c = (unsigned char) * iter;

				switch (c)
				{
					case '&':
						sRet << "&amp;";
						break;

					case '<':
						sRet << "&lt;";
						break;

					case '>':
						sRet << "&gt;";
						break;

					case '"':
						sRet << "&quot;";
						break;

					case '\'':
						sRet << "&apos;";
						break;

					default:
						if (c < 32 || c > 127)
						{
							sRet << "&#" << (unsigned int)c << ";";
						}
						else
						{
							sRet << c;
						}
				}
			}

			return sRet.str();
		}


		core::String
		XMLStrWriter::
		write(const Element *pElement) const
		{
			if (!pElement)
			{
				mapDefaultExceptionMacro( << "Error. Cannot convert structured element to string. Passed element pointer is NULL.");
			}

			ElementLevelType level = 0;
			core::String result = writeElement(pElement, level);

			return result;
		};

		core::String
		XMLStrWriter::
		writeElement(const Element *pElement, const ElementLevelType &level) const
		{
			assert(pElement);

			core::OStringStream stream;

			bool isEmptyElement = (pElement->getSubElementsCount() == 0) && pElement->getValue().empty();

			core::String attributes = writeAttributes(pElement, level);

			stream << "<" << pElement->getTag();

			if (!attributes.empty())
			{
				stream << " " << attributes;
			}

			if (isEmptyElement)
			{
				stream << "/>";
			}
			else
			{
				stream << ">";
				stream << encodeForXml(pElement->getValue()) << writeSubElements(pElement, level);
				stream << "</" << pElement->getTag() << ">";
			}

			return stream.str();
		};

		core::String
		XMLStrWriter::
		writeAttributes(const Element *pElement, const ElementLevelType &level) const
		{
			assert(pElement);

			core::OStringStream stream;

			Element::AttributeNameVectorType attributes = pElement->getAttributeNames();
			bool firstLoop = true;

			for (Element::AttributeNameVectorType::const_iterator pos = attributes.begin(); pos != attributes.end(); ++pos)
			{
				if (pos->find("sdInternal:") != 0)
				{
					if (firstLoop)
					{
						firstLoop = false;
					}
					else
					{
						stream << " ";
					}

					stream << *pos << "='" << encodeForXml(pElement->getAttribute(*pos)) << "'";
				}
			}

			return stream.str();
		};

		core::String
		XMLStrWriter::
		writeSubElements(const Element *pElement, const ElementLevelType &level) const
		{
			assert(pElement);

			core::String result;
			core::OStringStream stream;

			ElementLevelType sublevel = level + 1;

			for (Element::ConstSubElementIteratorType pos = pElement->getSubElementBegin(); pos != pElement->getSubElementEnd(); ++pos)
			{
				stream << writeElement(*pos, sublevel);
			}

			result = stream.str();
			return result;
		};

		XMLStrWriter::
		XMLStrWriter()
		{
		};

		XMLStrWriter::
		~XMLStrWriter()
		{
		};





		core::String
		XMLIntendedStrWriter::
		writeElement(const Element *pElement, const ElementLevelType &level) const
		{
			assert(pElement);

			::itk::Indent indent(2 * level);
			core::OStringStream stream;

			bool isEmptyElement = (pElement->getSubElementsCount() == 0) && pElement->getValue().empty();

			core::String attributes = writeAttributes(pElement, level);

			stream << indent << "<" << pElement->getTag();

			if (!attributes.empty())
			{
				stream << " " << attributes;
			}

			if (isEmptyElement)
			{
				stream << "/>";
			}
			else
			{
				stream << ">" << encodeForXml(pElement->getValue());

				if (pElement->getSubElementsCount() > 0)
				{
					stream << std::endl << writeSubElements(pElement, level) << indent;
				}

				stream << "</" << pElement->getTag() << ">";
			}

			stream << std::endl;

			return stream.str();
		};


		XMLIntendedStrWriter::
		XMLIntendedStrWriter()
		{
		};

		XMLIntendedStrWriter::
		~XMLIntendedStrWriter()
		{
		};



	} //end of namespace structuredData

} //end of namespace map
