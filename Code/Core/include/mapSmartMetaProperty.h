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



#ifndef __MAP_SMART_META_PROPERTY_H
#define __MAP_SMART_META_PROPERTY_H

#include "mapMetaPropertyBase.h"
#include "mapMetaPropertyAccessInterface.h"

namespace map
{
	namespace core
	{

		/*! @class SmartMetaProperty
		* @brief Property class for smart pointered value types.
		*
		* A SmartMetaProperty instance is used to encapsulat types that use smart pointer (e.g. all derivates of itk::LightObject).
		* The used type must have a valid smart pointer support.
		* If it is a const type the value must be set while constructing the property (see special New() method).
		* For normal data types please use MetaProperty.
		* @sa MetaProperty
		*
		* @ingroup Core
		*/

		template <typename TValue>
		class SmartMetaProperty : public MetaPropertyBase, public MetaPropertyAccessInterface< TValue* >,
			public MetaPropertyLightPointerAccessInterface
		{
		public:
			/** Smart pointer typedef support. */
			using Self = SmartMetaProperty<TValue>;
			using Superclass = MetaPropertyBase;
			using Pointer = ::itk::SmartPointer<Self>;
			using ConstPointer = ::itk::SmartPointer<const Self>;

			using ValueType = TValue;
			using ValueSmartPointerType = ::itk::SmartPointer<ValueType>;
			using ValuePointerType = TValue *;

			using AccessInterfaceType = MetaPropertyAccessInterface<ValuePointerType>;
			using ValueSetType = typename AccessInterfaceType::ValueSetType;
			using ValueGetType = typename AccessInterfaceType::ValueGetType;

			using ConstLightPointer = MetaPropertyLightPointerAccessInterface::ConstLightPointer;
			using LightPointer = MetaPropertyLightPointerAccessInterface::LightPointer;

			/** Run-time type information (and related methods). */
			itkTypeMacro(SmartMetaProperty, MetaPropertyBase);

			/**
			* @brief Creates a MetaProperty instance, initializes it and returns it via smartpointer.
			* @return A pointer to the MetaProperty.
			* @param initValue The value that should be used to initialize the MetaProperty
			* @eguarantee strong
			*/
			static Pointer New(ValueSetType initValue);

			/**
			* @brief Dublicates a MetaProperty instance.
			* @return A pointer to the MetaProperty clone.
			* @eguarantee strong
			*/
			::itk::LightObject::Pointer CreateAnother() const override;

			/**
			* @brief Returns the unique type name of the value type that stores the property.
			* @return A pointer to a const char array containing the unique type name.
			* @eguarantee strong
			*/
			const char* getMetaPropertyTypeName() const override;

			/**
			* @brief Returns the type_id of the value type that stores the property.
			* @eguarantee strong
			* @return A constant reference to a std::type_info object
			*/
			const std::type_info& getMetaPropertyTypeInfo() const override;

			/**
			* @brief Returns the property value
			* @return Property value.
			* @eguarantee strong
			*/
			ValueGetType getValue() const override;

			/**
			* @brief Sets the property to the passed value
			* @param newValue The new value of the property.
			* @eguarantee strong
			*/
			void setValue(ValueSetType newValue) override;

			/**
			* @brief Returns the property Value as LightObject pointer
			* @return indicates if it is possible to convert
			* @eguarantee strong
			*/
			bool getUntypedValue(ConstLightPointer& /*pValue*/) const override;
			/**
			* @brief Returns the property Value as LightObject pointer
			* @return indicates if it is possible to convert
			* @eguarantee strong
			*/
			bool getUntypedValue(LightPointer& /*pValue*/) const override;

		protected:

			/** @reimplementation
			Reimplementation of the itk::LightObject::InternalClone*/
			::itk::LightObject::Pointer	InternalClone()	const override;

			~SmartMetaProperty() override;
			SmartMetaProperty(ValueSetType initValue);

			/**
			* Defines the default behavior for printing out this element
			* @eguarantee strong
			* @param os An output stream
			*/
			void PrintSelf(std::ostream& os, itk::Indent indent) const override;

		private:

			/*! Property value.*/
			ValueSmartPointerType _spValue;

			SmartMetaProperty(const Self&) = delete; //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented
		};

	}  // namespace core
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapSmartMetaProperty.tpp"
#endif

#endif
