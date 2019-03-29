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



#ifndef __MAP_META_PROPERTY_ACCESS_INTERFACE_H
#define __MAP_META_PROPERTY_ACCESS_INTERFACE_H

#include "mapMacros.h"

namespace map
{
	namespace core
	{
		/*! @class MetaPropertyLightPointerAccessInterface
		* @brief Interface used to access the value of a MetaProperty as itk::LightObject pointer.
		*
		* This interface should only be implemented for MetaProperties that base on a
		* pointer value type. It allows access to the value in an untyped manner.
		* It is usefull for the situation that you want a value as a down casted type
		* but you don't know its real type. It is used by unwrapMetaProperty_cast().
		*
		* @ingroup Core
		*/
		class MetaPropertyLightPointerAccessInterface
		{
		public:
			/** Smart pointer typedef support. */
			using ConstLightPointer = const itk::LightObject *;
			using LightPointer = itk::LightObject *;

			/**
			* @brief Returns the property Value as untyped pointer
			* @return Property value.
			* @eguarantee strong
			*/
			virtual bool getUntypedValue(ConstLightPointer&) const = 0;
			/**
			* @brief Returns the property Value as untyped pointer
			* @return Property value.
			* @eguarantee strong
			*/
			virtual bool getUntypedValue(LightPointer&) const = 0;

		protected:

			virtual ~MetaPropertyLightPointerAccessInterface()
			= default;

			MetaPropertyLightPointerAccessInterface()
			= default;

		private:
			MetaPropertyLightPointerAccessInterface(const
													MetaPropertyLightPointerAccessInterface&) = delete;  //purposely not implemented
			void operator=(const MetaPropertyLightPointerAccessInterface&) = delete;  //purposely not implemented
		};


		/*! @class MetaPropertyAccessInterface
		* @brief Interface used to access the value of a MetaProperty.
		*
		* This template version is only uzsed if the ValueType of the MetaProperty is no
		* pointer type. In the case of a pointer type the template specialication
		* will be used. This differentiation is needed because the access interface
		* of non pointer types and pointer types must behave different (e.g. the
		* ValueSetType and ValueGetType are different and the concrete implementation
		* of the methods will differ).
		*
		* @ingroup Core
		* @template TValueType Type of the value of the property
		*/
		template <typename TValueType>
		class MetaPropertyAccessInterface
		{
		public:
			/** Smart pointer typedef support. */
			using ValueType = TValueType;
			using ValueSetType = const ValueType &;
			using ValueGetType = const ValueType &;

			/**
			* @brief Returns the property value
			* @return Property value.
			* @eguarantee strong
			*/
			virtual ValueGetType getValue() const = 0;

			/**
			* @brief Sets the property to the passed value
			* @param newValue The new value of the property.
			* @eguarantee strong
			*/
			virtual void setValue(ValueSetType newValue) = 0;

		protected:

			virtual ~MetaPropertyAccessInterface()
			= default;

			MetaPropertyAccessInterface()
			= default;

		private:
			MetaPropertyAccessInterface(const MetaPropertyAccessInterface<TValueType>
										&) = delete; //purposely not implemented
			void operator=(const MetaPropertyAccessInterface<TValueType>&) = delete;  //purposely not implemented
		};

		/* Template specialication of the MetaPropertyAccessInterface for pointer types
		*/
		template <typename TValueType>
		class MetaPropertyAccessInterface<TValueType*>
		{
		public:
			/** Smart pointer typedef support. */
			using ValueType = TValueType *;
			using ValueSetType = ValueType;
			using ValueGetType = ValueType;

			/**
			* @brief Returns the property value
			* @return Property value.
			* @eguarantee strong
			*/
			virtual ValueGetType getValue() const = 0;

			/**
			* @brief Sets the property to the passed value
			* @param value The new value of the property.
			* @eguarantee strong
			*/
			virtual void setValue(ValueSetType value) = 0;

		protected:

			virtual ~MetaPropertyAccessInterface()
			= default;

			MetaPropertyAccessInterface()
			= default;

		private:
			MetaPropertyAccessInterface(const MetaPropertyAccessInterface<TValueType*>
										&) = delete;   //purposely not implemented
			void operator=(const MetaPropertyAccessInterface<TValueType*>&) = delete;   //purposely not implemented
		};


	}  // namespace core
}  // namespace map

#endif
