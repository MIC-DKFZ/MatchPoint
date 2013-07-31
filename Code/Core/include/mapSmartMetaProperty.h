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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapSmartMetaProperty.h $
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
		class SmartMetaProperty : public MetaPropertyBase, public MetaPropertyAccessInterface< TValue * >, public MetaPropertyLightPointerAccessInterface
		{
		public:
			/** Smart pointer typedef support. */
			typedef SmartMetaProperty<TValue>  Self;
			typedef MetaPropertyBase  Superclass;
			typedef ::itk::SmartPointer<Self>  Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;

			typedef TValue ValueType;
			typedef ::itk::SmartPointer<ValueType>  ValueSmartPointerType;
			typedef TValue *ValuePointerType;

			typedef MetaPropertyAccessInterface< ValuePointerType > AccessInterfaceType;
			typedef typename AccessInterfaceType::ValueSetType ValueSetType;
			typedef typename AccessInterfaceType::ValueGetType ValueGetType;

			typedef MetaPropertyLightPointerAccessInterface::ConstLightPointer ConstLightPointer;
			typedef MetaPropertyLightPointerAccessInterface::LightPointer LightPointer;

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
			virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			/**
			* @brief Returns the unique type name of the value type that stores the property.
			* @return A pointer to a const char array containing the unique type name.
			* @eguarantee strong
			*/
			virtual const char *getMetaPropertyTypeName() const;

			/**
			* @brief Returns the type_id of the value type that stores the property.
			* @eguarantee strong
			* @return A constant reference to a std::type_info object
			*/
			virtual const std::type_info &getMetaPropertyTypeInfo(void) const;

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

			/**
			* @brief Returns the property Value as LightObject pointer
			* @return indicates if it is possible to convert
			* @eguarantee strong
			*/
			virtual bool getUntypedValue(ConstLightPointer &) const;
			/**
			* @brief Returns the property Value as LightObject pointer
			* @return indicates if it is possible to convert
			* @eguarantee strong
			*/
			virtual bool getUntypedValue(LightPointer &) const;

		protected:

			/** @reimplementation
			Reimplementation of the itk::LightObject::InternalClone*/
			virtual ::itk::LightObject::Pointer	InternalClone()	const;

			virtual ~SmartMetaProperty();
			SmartMetaProperty(ValueSetType initValue);

			/**
			* Defines the default behavior for printing out this element
			* @eguarantee strong
			* @param os An output stream
			*/
			virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;

		private:

			/*! Property value.*/
			ValueSmartPointerType _spValue;

			SmartMetaProperty(const Self &);//purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapSmartMetaProperty.tpp"
#endif

#endif
