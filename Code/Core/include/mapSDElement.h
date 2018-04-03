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



#ifndef __MAP_SD_ELEMENT_H
#define __MAP_SD_ELEMENT_H

#include <vector>
#include <map>

#include "itkLightObject.h"
#include "itkObjectFactory.h"

#include "mapString.h"
#include "mapMacros.h"
#include "mapMAPCoreExports.h"

namespace map
{

	namespace structuredData
	{

		/** @class Element
		@brief class to store and stream structured data
		This class is inspired by an former f.r.e.e. implementation
		it models an xml like data structuring scheme and can be used
		to store and stream data that is some how structured.
		@ingroup SD
		*/
		class MAPCore_EXPORT Element: public ::itk::LightObject
		{
		public:
			typedef Element Self;
			typedef ::itk::LightObject Superclass;
			typedef ::itk::SmartPointer<Self> Pointer;
			typedef ::itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(Element, ::itk::LightObject);
			itkNewMacro(Self);

			typedef core::String TagType;
			typedef core::String ValueType;

		protected:
			typedef std::vector<Pointer> SubElementVectorType;
			typedef std::map< ::map::core::String, core::String> AttributeMapType;

		public:
			typedef std::vector< ::map::core::String> AttributeNameVectorType;
			typedef SubElementVectorType::iterator SubElementIteratorType;
			typedef SubElementVectorType::const_iterator ConstSubElementIteratorType;
			typedef SubElementVectorType::size_type SubElementIndexType;

			//Sub elements
			//////////////////////////////////////////////////////////////////
			SubElementIteratorType getSubElementBegin();
			ConstSubElementIteratorType getSubElementBegin() const;

			SubElementIteratorType getSubElementEnd();
			ConstSubElementIteratorType getSubElementEnd() const;

			/** Returns the sub element indicated by the passed index.
			* @pre index must be valid
			* @param [in] index Index of the sub element
			* @return Pointer to the sub element. If the function returns successfully
			* the pointer is always valid.*/
			const Self* getSubElement(SubElementIndexType index) const;
			/** @overload non const version*/
			Self* getSubElement(SubElementIndexType index);

			/**Removes the sub element that is located at the passed index.
			* @pre Index must be within the range of the sub elements.
			* @param [in] index Index of the sub element that should be removed.*/
			void removeSubElement(SubElementIndexType index);

			/**Removes the sub element that is located at the passed iterator.
			* @param [in] it Iterator that designates the element that should be removed
			* @return Iterator that designates the first element beyond the removed one or the end of the vector.*/
			SubElementIteratorType removeSubElement(SubElementIteratorType it);

			/**Adds the passed sub element at the end of the sub element vector
			* @pre pNewElement must not be NULL
			* @param [in] pNewElement Pointer to the element that should be added
			* @return Index of the added element*/
			SubElementIndexType addSubElement(Self* pNewElement);

			/**Adds the passed sub element at the location indicated by the iterator
			* also passed with the function call.
			* @pre pNewElement must not be NULL
			* @param [in] pNewElement Pointer to the element that should be added
			* @param [in] location Iterator that designates the insert location
			* @return Iterator that marks the location of the added element.*/
			SubElementIteratorType insertSubElement(Self* pNewElement, SubElementIteratorType location);

			/**Adds the passed sub element at the location indicated by the location index
			* also passed with the function call.
			* @pre pNewElement must not be NULL.
			* @pre location must be within the range of the current sub element vectors.
			* @param [in] pNewElement Pointer to the element that should be added
			* @param [in] location Index that indicates the insert location.*/
			void insertSubElement(Self* pNewElement, SubElementIndexType location);

			/**Removes all sub elements*/
			void resetSubElements();

			/**Returns the number of sub elements*/
			SubElementIndexType getSubElementsCount() const;

			//Attributes
			//////////////////////////////////////////////////////////////////

			/**Removes all attributes */
			void resetAttributes();

			/**Removes an attribute if existing from the element.
			 @param name The name of the attribute
				 @param recursively Indicates if the attribute should be removed from
				  all sub elements (and their sub elements...) after removed from the
				  current element.
			 @return Indicates if the attribute had existed and was
			  deleted (true) or could not be found (false). If the method was
				  called recursively, the return will be true if at least one time
					the attribute was found and removed.*/
			bool removeAttribute(const core::String& name, bool recursively = false);

			/**Sets an existing attribute to the passed value,
			  if the attribute does not exist, it will be added.
			 @param name The name of the attribute
			 @param value The new value of the attribute
				 @param recursively Indicates if the attribute should be also set in
				  all sub elements (and their sub elements...) after set in the
				  current element.
			 @return Indicates if the attribute was just set (true) or if it was
				  added by the call (false). If the method was called recursively,
					the return will be true if at least one time
				  the attribute was just set.*/
			bool setAttribute(const core::String& name, const core::String& value, bool recursively = false);

			/**Returns the value of the specified attribute.
			* If the attribute does not exist an exception (MissingIdentifierException) will be thrown.
			* @param name The name of the attribute
			* @return The value of the attribute.*/
			const core::String& getAttribute(const core::String& name) const;

			/**Indicates if the elements owns the specified attribute.
			* @param name The name of the attribute
			* @return Indicates if the attribute exists for this instance.*/
			bool attributeExists(const core::String& name) const;

			/**Return the names of all existing attributes in a vector.*/
			AttributeNameVectorType getAttributeNames() const;

			//All others
			//////////////////////////////////////////////////////////////////

			const TagType& getTag() const;

			void setTag(const TagType& tag);

			const ValueType& getValue() const;

			void setValue(const ValueType& value);

			void reset();

			/**Clones the values of a given instance in a new instance.
			* @eguarantee strong
			* @return Smart pointer to the clone.*/
			Pointer clone() const;

			/** Convinience function that creates a simple value element.*/
			static Pointer createElement(const TagType& tag, const ValueType& value);

		protected:
			Element();
			~Element();

			virtual void  PrintSelf(std::ostream& os, ::itk::Indent indent) const;

			TagType _Tag;
			ValueType _Value;
			SubElementVectorType _SubElements;
			AttributeMapType _Attributes;

		private:
			//No copy constructor allowed
			Element(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

		MAPCore_EXPORT std::ostream& operator<<(std::ostream& os, const Element& element);

		/** Helper function that takes an sub element iterator, an searches
		 * for the first element that fits the search "description".\n
		 * The search description is always the tag of the element. In addition,
		 * you can specify a attribute and its value to further specify the
		 * searched elements.
		 * @return iterator to a matching element or iterator that equals endPos.
		 * @pre the passed iterators must be from the same container.*/
		MAPCore_EXPORT Element::SubElementIteratorType findNextSubElement(const
				Element::SubElementIteratorType& beginPos,
				const structuredData::Element::SubElementIteratorType& endPos, const core::String& tag,
				const core::String& attrName = "", const core::String& attrValue = "");
		MAPCore_EXPORT Element::ConstSubElementIteratorType findNextSubElement(
			const Element::ConstSubElementIteratorType& beginPos,
			const structuredData::Element::ConstSubElementIteratorType& endPos, const core::String& tag,
			const core::String& attrName = "", const core::String& attrValue = "");


	} //end of namespace structuredData

} //end of namespace map
#endif
