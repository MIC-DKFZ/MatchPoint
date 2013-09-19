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



#ifndef __MAP_META_PROPERTY_ACCESSOR_H
#define __MAP_META_PROPERTY_ACCESSOR_H

#include "mapMetaPropertyAccessInterface.h"
#include "mapMetaPropertyBase.h"

namespace map
{
	namespace core
	{
		/*! @class MetaPropertyAccessor
		* @brief Helper class for efficient "unboxing" of property values.
		*
		* This class (and its template specialization) is used to efficiently access the value of a property.
		* By template specialization it is checked if the target value type is const or not.
		* If the type is non const you may also cast for const access to the property if a non const access
		* is not possible.
		*
		* @ingroup Core
		*/
		template <typename TValue>
		class MetaPropertyAccessor
		{
		public:
			typedef TValue ValueType;
			typedef MetaPropertyAccessInterface<ValueType> InterfaceType;

			/**
			* @brief Retrieves the value of a passed property.
			* @return Indication of the value was successfully unwrapped. True: value is valid;
			* False: value is invalid.
			* @param pProperty Pointer to the MetaPropertyBase instance that should be unwrapped.
			* @param value The value that was unwrapped. Value is only valid if return method returns true.
			* @eguarantee strong
			*/
			static bool unwrapPropertyValue(const MetaPropertyBase* pProperty, ValueType& value);

			/**
			* @brief Resets the value of a passed property.
			* @return Indication of the value was successfully wrapped. True: value is valid;
			* False: value is invalid.
			* @param pProperty Pointer to the MetaPropertyBase instance that should be set.
			* @param value The value that should be wrapped into the property.
			* @eguarantee strong
			*/
			static bool wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value);

		private:
			~MetaPropertyAccessor();//purposely not implemented
			MetaPropertyAccessor();//purposely not implemented

			MetaPropertyAccessor(const MetaPropertyAccessor<TValue>&); //purposely not implemented
			void operator=(const MetaPropertyAccessor<TValue>&);  //purposely not implemented
		};

		//specialized template version for const-type-pointer. This version also casts for InterfaceType
		//if the cast for ConstInterfaceType fails.
		template <typename TValue>
		class MetaPropertyAccessor<const TValue*>
		{
		public:
			typedef const TValue* ValueType;
			typedef MetaPropertyAccessInterface<TValue*> InterfaceType;
			typedef MetaPropertyAccessInterface<const TValue*> ConstInterfaceType;

			static bool unwrapPropertyValue(const MetaPropertyBase* pProperty, ValueType& value);

			static bool wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value);

		private:
			~MetaPropertyAccessor();//purposely not implemented
			MetaPropertyAccessor();//purposely not implemented

			MetaPropertyAccessor(const MetaPropertyAccessor<TValue*>&);   //purposely not implemented
			void operator=(const MetaPropertyAccessor<TValue*>&);   //purposely not implemented
		};

		//specialized template version for smart pointer. This version takes care if the
		//property value should be unwrapped to a smart pointer.
		template <typename TValue>
		class MetaPropertyAccessor< itk::SmartPointer<TValue> >
		{
		public:
			typedef TValue* ValueType;
			typedef itk::SmartPointer<TValue> SmartPointerType;
			typedef MetaPropertyAccessInterface<ValueType> InterfaceType;

			static bool unwrapPropertyValue(const MetaPropertyBase* pProperty, SmartPointerType& spValue);

			static bool wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value);

		private:
			~MetaPropertyAccessor();//purposely not implemented
			MetaPropertyAccessor();//purposely not implemented

			MetaPropertyAccessor(const MetaPropertyAccessor< itk::SmartPointer<TValue> >
								 &); //purposely not implemented
			void operator=(const MetaPropertyAccessor< itk::SmartPointer<TValue> >
						   &);  //purposely not implemented
		};

		//specialized template version for const smart pointer.
		//This version takes care if the property value should
		//be unwrapped to a const smart pointer. This version
		//also casts for InterfaceType if the cast for
		//ConstInterfaceType fails.
		template <typename TValue>
		class MetaPropertyAccessor< itk::SmartPointer<const TValue> >
		{
		public:
			typedef const TValue* ValueType;
			typedef itk::SmartPointer<const TValue> SmartPointerType;
			typedef MetaPropertyAccessInterface<TValue*> InterfaceType;
			typedef MetaPropertyAccessInterface<const TValue*> ConstInterfaceType;

			static bool unwrapPropertyValue(const MetaPropertyBase* pProperty, SmartPointerType& spValue);

			static bool wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value);

		private:
			~MetaPropertyAccessor();//purposely not implemented
			MetaPropertyAccessor();//purposely not implemented

			MetaPropertyAccessor(const MetaPropertyAccessor< itk::SmartPointer<const TValue> >
								 &); //purposely not implemented
			void operator=(const MetaPropertyAccessor< itk::SmartPointer<const TValue> >
						   &);  //purposely not implemented
		};

		/*!
		* Convinience function to quickly unwrap and access the value of a MetaProperty if only the pointer
		* to the MetaPropertyBase is given.\n
		* @remark The real unpacking is realized in the helper class MetaPropertyAccessor. This design/seperation of
		* template function and specialized helper template class was chosen to avoid problems and irritating
		* behaviour that could occure when using partial specialization on template functions.\n
		* With this design we have a clean entrance point (the template function) that stays untouched and all
		* the specialization and overloading is done by the template class.
		*
		* @ingroup Core
		*/
		template <typename TValue>
		bool unwrapMetaProperty(const MetaPropertyBase* pProperty, TValue& value)
		{
			return MetaPropertyAccessor<TValue>::unwrapPropertyValue(pProperty, value);
		};

		/*!
		* Helper function that tries to cast to the content of a smart meta property via
		* untyped raw pointer to the passed casted pointer type.
		* If this works the function succfully returns.
		*
		* @ingroup Core
		*/
		template <typename TValue, typename TRawPointer, typename TCastedPointer>
		bool
		castRawMetaProperty(const MetaPropertyBase* pProperty, TValue& spValue)
		{
			bool result = false;

			const MetaPropertyLightPointerAccessInterface* pInterface =
				dynamic_cast<const MetaPropertyLightPointerAccessInterface*>(pProperty);

			if (pInterface)
			{
				//get the untyped pointer
				TRawPointer pRaw;

				if (pInterface->getUntypedValue(pRaw))
				{
					//we have a pointer
					if (pRaw)
					{
						// it is not null so try to cast
						TCastedPointer pCastedContent = dynamic_cast<TCastedPointer>(pRaw);

						if (pCastedContent)
						{
							spValue = pCastedContent;
							result = true;
						}
					}
					else
					{
						result = true;
						spValue = NULL;
					}
				}
			}

			return result;
		};

		/*! @class MetaPropertyCaster
		* @brief Helper class casting pointer meta properties to a given type via untyped pointer.
		* Only smart pointer are currently supported. Therefor default template is just a dummy;
		* see template specializations.
		* @ingroup Core
		*/
		//dummy version for other types then smart pointer. There are not supported.
		template <typename TValue>
		class MetaPropertyCaster
		{
		public:
			static bool cast(const MetaPropertyBase*, TValue&)
			{
				return false;
			};
		private:
			~MetaPropertyCaster();//purposely not implemented
			MetaPropertyCaster();//purposely not implemented

			MetaPropertyCaster(const MetaPropertyCaster< TValue >&); //purposely not implemented
			void operator=(const MetaPropertyCaster< TValue >&);  //purposely not implemented
		};

		template <typename TValue>
		class MetaPropertyCaster< TValue* >
		{
		public:
			typedef TValue* ValueType;
			typedef MetaPropertyLightPointerAccessInterface::LightPointer LightPointerType;

			static bool cast(const MetaPropertyBase* pProperty, ValueType& spValue)
			{
				return castRawMetaProperty<ValueType, LightPointerType, ValueType>(pProperty, spValue);
			};
		private:
			~MetaPropertyCaster();//purposely not implemented
			MetaPropertyCaster();//purposely not implemented

			MetaPropertyCaster(const MetaPropertyCaster< itk::SmartPointer<TValue> >
							   &); //purposely not implemented
			void operator=(const MetaPropertyCaster< itk::SmartPointer<TValue> >&);  //purposely not implemented
		};

		template <typename TValue>
		class MetaPropertyCaster< const TValue* >
		{
		public:
			typedef const TValue* ValueType;
			typedef MetaPropertyLightPointerAccessInterface::ConstLightPointer LightPointerType;

			static bool cast(const MetaPropertyBase* pProperty, ValueType& spValue)
			{
				return castRawMetaProperty<ValueType, LightPointerType, ValueType>(pProperty, spValue);
			};
		private:
			~MetaPropertyCaster();//purposely not implemented
			MetaPropertyCaster();//purposely not implemented

			MetaPropertyCaster(const MetaPropertyCaster< itk::SmartPointer<TValue> >
							   &); //purposely not implemented
			void operator=(const MetaPropertyCaster< itk::SmartPointer<TValue> >&);  //purposely not implemented
		};

		template <typename TValue>
		class MetaPropertyCaster< itk::SmartPointer<TValue> >
		{
		public:
			typedef TValue* ValueType;
			typedef itk::SmartPointer<TValue> SmartPointerType;
			typedef MetaPropertyLightPointerAccessInterface::LightPointer LightPointerType;

			static bool cast(const MetaPropertyBase* pProperty, SmartPointerType& spValue)
			{
				return castRawMetaProperty<SmartPointerType, LightPointerType, ValueType>(pProperty, spValue);
			};
		private:
			~MetaPropertyCaster();//purposely not implemented
			MetaPropertyCaster();//purposely not implemented

			MetaPropertyCaster(const MetaPropertyCaster< itk::SmartPointer<TValue> >
							   &); //purposely not implemented
			void operator=(const MetaPropertyCaster< itk::SmartPointer<TValue> >&);  //purposely not implemented
		};

		//specialized template version for const smart pointer.
		//This version takes care if the property value should
		//be converted to a const smart pointer.
		template <typename TValue>
		class MetaPropertyCaster< itk::SmartPointer<const TValue> >
		{
		public:
			typedef const TValue* ValueType;
			typedef itk::SmartPointer<const TValue> SmartPointerType;
			typedef MetaPropertyLightPointerAccessInterface::ConstLightPointer LightPointerType;

			static bool cast(const MetaPropertyBase* pProperty, SmartPointerType& spValue)
			{
				return castRawMetaProperty<SmartPointerType, LightPointerType, ValueType>(pProperty, spValue);
			};
		private:
			~MetaPropertyCaster();//purposely not implemented
			MetaPropertyCaster();//purposely not implemented

			MetaPropertyCaster(const MetaPropertyCaster< itk::SmartPointer<const TValue> >
							   &); //purposely not implemented
			void operator=(const MetaPropertyCaster< itk::SmartPointer<const TValue> >
						   &);  //purposely not implemented
		};

		/*!
		* Convinience function for smart pointer objectes that enhances the convinience function unwrapMetaProperty()
		* by a casting feature.\n
		* Casting feature: if unwrapMetaProperty() doesnt work the function assumes that the TValue is not the type stored
		* in the MetaPropertyBase. Therefor this function will get the raw untyped pointer and tries a dynamic_cast.
		* If this works the function succfully returns.
		*
		* @ingroup Core
		*/
		template <typename TValue>
		bool unwrapCastedMetaProperty(const MetaPropertyBase* pProperty, TValue& value)
		{
			bool result = false;
			result = MetaPropertyAccessor<TValue>::unwrapPropertyValue(pProperty, value);

			if (!result)
			{
				//try the casting
				result = MetaPropertyCaster<TValue>::cast(pProperty, value);
			}

			return result;
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapMetaPropertyAccessor.tpp"
#endif

#endif
