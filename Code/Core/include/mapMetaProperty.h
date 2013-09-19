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



#ifndef __MAP_META_PROPERTY_H
#define __MAP_META_PROPERTY_H

#include "mapMetaPropertyBase.h"
#include "mapMetaPropertyAccessInterface.h"

namespace map
{
	namespace core
	{
		/*! @class MetaProperty
		* @brief Property class for default value types.
		*
		* A MetaProperty instance is used to encapsulat normal value types (e.g. int, bool, void*).
		* Following type patterns are supported:
		* - Type         : type (e.g. int, bool)
		* - Type *       : pointer (e.g. char*, void*)
		* - const Type * : pointer-to-const-type (e.g. const Obj*)
		* .
		* Following type patterns are not supported:
		* - const Type   : const value type (e.g. const int)
		* - Type * const : const-pointer-to-type
		* - const Type * const: const-pointer-to-const-type
		* .
		* The used value type must also have a valid assignment/copy-operator and a stl streaming operator (<<).
		* If the value type is a pointer it has to be treated differently, therefor see MetaPropertyAccessInterface.
		* Normal types have a const reference as ValueSetType and ValueGetType.
		* In difference ValueSetType and ValueGetType of pointer types are the pointer types themself.\n\n
		*
		* For types using smart pointer please use SmartMetaProperty.
		* @sa SmartMetaProperty
		*
		* @ingroup Core
		*/

		template <typename TValue>
		class MetaProperty : public MetaPropertyBase, public MetaPropertyAccessInterface<TValue>
		{
		public:
			/** Smart pointer typedef support. */
			typedef MetaProperty<TValue>  Self;
			typedef MetaPropertyBase  Superclass;
			typedef ::itk::SmartPointer<Self>  Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;
			typedef TValue ValueType;
			typedef typename MetaPropertyAccessInterface<TValue>::ValueSetType ValueSetType;
			typedef typename MetaPropertyAccessInterface<TValue>::ValueGetType ValueGetType;

			/** Run-time type information (and related methods). */
			itkTypeMacro(MetaProperty, MetaPropertyBase);

			/**
			* @brief Creates a MetaProperty instance, initializes it and returns it via smartpointer.
			* @return A pointer to the MetaProperty.
			* @param initValue The value that should be used to initialize the MetaProperty
			* @eguarantee strong
			*/
			static Pointer New(ValueSetType initValue);

			/**
			* @brief Dublicates a MetaProperty instance. The value of the property is copied.
			* @return A pointer to the MetaProperty clone.
			* @eguarantee strong
			*/
			virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			/**
			* @brief Returns the unique type name of the value type that stores the property.
			* @return A pointer to a const char array containing the unique type name.
			* @eguarantee strong
			*/
			virtual const char* getMetaPropertyTypeName() const;

			/**
			* @brief Returns the type_id of the value type that stores the property.
			* @eguarantee strong
			* @return A constant reference to a std::type_info object
			*/
			virtual const std::type_info& getMetaPropertyTypeInfo(void) const;

			/**
			* @brief Returns the property value
			* @return Property value.
			* @eguarantee strong
			*/
			virtual ValueGetType getValue() const;

			/**
			* @brief Sets the property to the passed value
			* @param newValue The new value of the property.
			* @eguarantee strong
			*/
			virtual void setValue(ValueSetType newValue);

		protected:
			/** @reimplementation
			Reimplementation of the itk::LightObject::InternalClone*/
			virtual ::itk::LightObject::Pointer	InternalClone()	const;

			virtual ~MetaProperty();
			MetaProperty(ValueSetType initValue);

			/**
			* Defines the default behavior for printing out this element
			* @eguarantee strong
			* @param os An output stream
			*/
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:

			/*! Property value.*/
			ValueType _value;

			MetaProperty(const Self&); //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapMetaProperty.tpp"
#endif

#endif
