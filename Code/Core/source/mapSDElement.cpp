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



#include "mapSDElement.h"
#include "mapSDExceptions.h"

namespace map
{

	namespace structuredData
	{

		Element::SubElementIteratorType
		Element::
		getSubElementBegin()
		{
			return _SubElements.begin();
		};

		Element::ConstSubElementIteratorType
		Element::
		getSubElementBegin() const
		{
			return _SubElements.begin();
		};

		Element::SubElementIteratorType
		Element::
		getSubElementEnd()
		{
			return _SubElements.end();
		};

		Element::ConstSubElementIteratorType
		Element::
		getSubElementEnd() const
		{
			return _SubElements.end();
		};

		const Element::Self*
		Element::
		getSubElement(SubElementIndexType index) const
		{
			if (index >= _SubElements.size())
			{
				mapExceptionMacro(::map::core::OutOfRangeException,
								  << "Error. Cannot get element. Passed index is out of sub elements vector range. Index: " << index
								  << "; vector size: " << _SubElements.size());
			}

			return _SubElements[index].GetPointer();
		};

		Element::Self*
		Element::
		getSubElement(SubElementIndexType index)
		{
			if (index >= _SubElements.size())
			{
				mapExceptionMacro(::map::core::OutOfRangeException,
								  << "Error. Cannot get element. Passed index is out of sub elements vector range. Index: " << index
								  << "; vector size: " << _SubElements.size());
			}

			return _SubElements[index].GetPointer();
		};

		void
		Element::
		removeSubElement(SubElementIndexType index)
		{
			if (index >= _SubElements.size())
			{
				mapExceptionMacro(::map::core::OutOfRangeException,
								  << "Error. Cannot remove element. Passed index is out of sub elements vector range. Index: " <<
								  index << "; vector size: " << _SubElements.size());
			}

			_SubElements.erase(_SubElements.begin() + index);
		};

		Element::SubElementIteratorType
		Element::
		removeSubElement(SubElementIteratorType it)
		{
			return _SubElements.erase(it);
		};

		/**Adds the passed sub element at the end of the sub element vector
		* @pre pNewElement must not be NULL
		* @param [in] pNewElement Pointer to the element that should be added
		* @return Index of the added element*/
		Element::SubElementIndexType
		Element::
		addSubElement(Self* pNewElement)
		{
			if (pNewElement == nullptr)
			{
				mapDefaultExceptionMacro( << "Error. Cannot add new element. Passed element pointer is NULL.");
			}

			Pointer smp = pNewElement;

			_SubElements.push_back(smp);

			return _SubElements.size() - 1;
		};

		Element::SubElementIteratorType
		Element::
		insertSubElement(Self* pNewElement, SubElementIteratorType location)
		{
			if (pNewElement == nullptr)
			{
				mapDefaultExceptionMacro( << "Error. Cannot insert new element. Passed element pointer is NULL.");
			}

			Pointer smp = pNewElement;

			return _SubElements.insert(location, smp);
		};

		void
		Element::
		insertSubElement(Self* pNewElement, SubElementIndexType location)
		{
			if (location >= _SubElements.size())
			{
				mapExceptionMacro(::map::core::OutOfRangeException,
								  << "Error. Cannot insert element. Passed index is out of sub elements vector range. Index: " <<
								  location << "; vector size: " << _SubElements.size());
			}

			if (pNewElement == nullptr)
			{
				mapDefaultExceptionMacro( << "Error. Cannot insert new element. Passed element pointer is NULL.");
			}

			Pointer smp = pNewElement;

			_SubElements.insert(_SubElements.begin() + location, smp);
		};

		void
		Element::
		resetSubElements()
		{
			_SubElements.clear();
		};

		Element::SubElementIndexType
		Element::
		getSubElementsCount() const
		{
			return _SubElements.size();
		};

		//Attributes
		//////////////////////////////////////////////////////////////////

		void
		Element::
		resetAttributes()
		{
			_Attributes.clear();
		};

		bool
		Element::
		removeAttribute(const core::String& name, bool recursively)
		{
			bool result = false;
			auto pos = _Attributes.find(name);

			if (pos != _Attributes.end())
			{
				_Attributes.erase(pos);
				result = true;
			}

			if (recursively)
			{
				for (auto & _SubElement : _SubElements)
				{
					bool subResult = _SubElement->removeAttribute(name, recursively);
					result = result || subResult;
				}
			}

			return result;
		};

		bool
		Element::
		setAttribute(const core::String& name, const core::String& value, bool recursively)
		{
			bool result = _Attributes.find(name) != _Attributes.end();

			_Attributes[name] = value;

			if (recursively)
			{
				for (auto & _SubElement : _SubElements)
				{
					bool subResult = _SubElement->setAttribute(name, value, recursively);
					result = result || subResult;
				}
			}

			return result;
		};

		const core::String&
		Element::
		getAttribute(const core::String& name) const
		{
			auto pos = _Attributes.find(name);

			if (pos == _Attributes.end())
			{
				mapExceptionMacro(::map::core::MissingIdentifierException,
								  << "Error. Requested attribute does not exist. Attribute name: " << name);
			}

			return pos->second;
		};

		bool
		Element::
		attributeExists(const core::String& name) const
		{
			bool result = _Attributes.find(name) != _Attributes.end();
			return result;
		};

		/**Return the names of all existing attributes in a vector.*/
		Element::AttributeNameVectorType
		Element::
		getAttributeNames() const
		{
			AttributeNameVectorType names;

			for (const auto & _Attribute : _Attributes)
			{
				names.push_back(_Attribute.first);
			}

			return names;
		};

		//All others
		//////////////////////////////////////////////////////////////////

		const Element::TagType&
		Element::
		getTag() const
		{
			return _Tag;
		};

		void
		Element::
		setTag(const TagType& tag)
		{
			_Tag = tag;
		};

		const Element::ValueType&
		Element::
		getValue() const
		{
			return _Value;
		};

		void
		Element::
		setValue(const ValueType& value)
		{
			_Value = value;
		};

		void
		Element::
		reset()
		{
			resetAttributes();
			resetSubElements();
			_Value = "";
		};

		Element::
		Element()
		{
			_Tag = "";
			reset();
		};

		Element::
		~Element()
		= default;

		Element::Pointer
		Element::
		createElement(const TagType& tag, const ValueType& value)
		{
			Pointer smpNew = Self::New();
			smpNew->setTag(tag);
			smpNew->setValue(value);

			return smpNew;
		};


		Element::Pointer
		Element::
		clone() const
		{
			Pointer spNew = Self::New();
			spNew->setTag(_Tag);
			spNew->setValue(_Value);

			//attributes
			for (const auto & _Attribute : _Attributes)
			{
				spNew->setAttribute(_Attribute.first, _Attribute.second);
			}

			//sub elements
			for (const auto & _SubElement : _SubElements)
			{
				spNew->addSubElement(_SubElement->clone());
			}

			return spNew;
		};

		void
		Element::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent << "Tag: " << _Tag << std::endl;
			os << indent << "Value: " << _Value << std::endl;
			os << indent << "Attributes: (" << _Attributes.size() << ")" << std::endl;

			::itk::Indent indent2 = indent.GetNextIndent();

			for (const auto & _Attribute : _Attributes)
			{
				os << indent2 << _Attribute.first << " = '" << _Attribute.second << "'" << std::endl;
			}

			os << indent << "Sub elements: (" << _SubElements.size() << ")" << std::endl;

		};

		std::ostream& operator<<(std::ostream& os, const Element& element)
		{
			element.Print(os);
			return os;
		};

		structuredData::Element::SubElementIteratorType findNextSubElement(const
				structuredData::Element::SubElementIteratorType& beginPos,
				const structuredData::Element::SubElementIteratorType& endPos, const core::String& tag,
				const core::String& attrName, const core::String& attrValue)
		{
			structuredData::Element::SubElementIteratorType result = endPos;
			structuredData::Element::SubElementIteratorType current = beginPos;

			for (; current != endPos; ++current)
			{
				if ((*current)->getTag() == tag)
				{
					if (attrName.empty())
					{
						result = current;
						break;
					}
					
					
						if ((*current)->attributeExists(attrName))
						{
							if ((*current)->getAttribute(attrName) == attrValue)
							{
								result = current;
								break;
							}
						}
					
				}
			}

			return result;
		};

		structuredData::Element::ConstSubElementIteratorType findNextSubElement(
			const structuredData::Element::ConstSubElementIteratorType& beginPos,
			const structuredData::Element::ConstSubElementIteratorType& endPos, const core::String& tag,
			const core::String& attrName, const core::String& attrValue)
		{
			structuredData::Element::ConstSubElementIteratorType result = endPos;
			structuredData::Element::ConstSubElementIteratorType current = beginPos;

			for (; current != endPos; ++current)
			{
				if ((*current)->getTag() == tag)
				{
					if (attrName.empty())
					{
						result = current;
						break;
					}
					
					
						if ((*current)->attributeExists(attrName))
						{
							if ((*current)->getAttribute(attrName) == attrValue)
							{
								result = current;
								break;
							}
						}
					
				}
			}

			return result;
		}

	} //end of namespace structuredData

} //end of namespace map
