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




#ifndef __MAP_SMART_META_PROPERTY_TPP
#define __MAP_SMART_META_PROPERTY_TPP

namespace map
{
	namespace core
	{

		/******************************************************************
		 * Helper template class that is used to differenciate between
		 * const and non const smart pointer conversion to raw pointer
		******************************************************************/
		template <typename TValue>
		class SmartMetaPropertyUntypeHelper
		{
			//This helper class should only be used and is only defined for pointer types.
			//see below
		};

		template <typename TValue>
		class SmartMetaPropertyUntypeHelper<const TValue*>
		{
		public:
			typedef typename SmartMetaProperty<TValue>::LightPointer LightPointer;
			typedef typename SmartMetaProperty<TValue>::ConstLightPointer ConstLightPointer;

			static bool Convert(const TValue* pValue, LightPointer& pRaw)
			{
				return false;
			};
			static bool Convert(const TValue* pValue, ConstLightPointer& pRaw)
			{
				pRaw = pValue;
				return true;
			};
		};

		template <typename TValue>
		class SmartMetaPropertyUntypeHelper<TValue*>
		{
		public:
			typedef typename SmartMetaProperty<TValue>::LightPointer LightPointer;
			typedef typename SmartMetaProperty<TValue>::ConstLightPointer ConstLightPointer;

			static bool Convert(TValue* pValue, LightPointer& pRaw)
			{
				pRaw = pValue;
				return true;
			};
			static bool Convert(TValue* pValue, ConstLightPointer& pRaw)
			{
				pRaw = pValue;
				return true;
			};
		};

		/******************************************************************
		 * End of helper template classes
		 ******************************************************************/


		template<typename TValue>
		typename SmartMetaProperty<TValue>::Pointer
		SmartMetaProperty<TValue>::
		New(ValueSetType initValue)
		{
			Pointer smartPtr;
			Self* rawPtr = new Self(initValue);
			smartPtr = rawPtr;
			rawPtr->UnRegister();
			return smartPtr;
		}

		template<typename TValue>
		::itk::LightObject::Pointer
		SmartMetaProperty<TValue>::
		CreateAnother(void) const
		{
			::itk::LightObject::Pointer smartPtr;
			smartPtr = Self::New(this->_spValue.GetPointer()).GetPointer();
			return smartPtr;
		}

		template<typename TValue>
		::itk::LightObject::Pointer
		SmartMetaProperty<TValue>::
		InternalClone() 	const
		{
			::itk::LightObject::Pointer smartPtr;
			smartPtr = Self::New(this->_spValue.GetPointer()).GetPointer();
			return smartPtr;
		}

		template<typename TValue>
		const char*
		SmartMetaProperty<TValue>::
		getMetaPropertyTypeName() const
		{
			return typeid(ValuePointerType).name();
		};

		template<typename TValue>
		const std::type_info&
		SmartMetaProperty<TValue>::
		getMetaPropertyTypeInfo(void) const
		{
			return typeid(ValuePointerType);
		};

		template<typename TValue>
		typename SmartMetaProperty<TValue>::ValueGetType
		SmartMetaProperty<TValue>::
		getValue() const
		{
			return _spValue.GetPointer();
		};

		template<typename TValue>
		void
		SmartMetaProperty<TValue>::
		setValue(ValueSetType newValue)
		{
			_spValue = newValue;
		};

		template<typename TValue>
		bool
		SmartMetaProperty<TValue>::
		getUntypedValue(ConstLightPointer& pValue) const
		{
			return SmartMetaPropertyUntypeHelper<ValuePointerType>::Convert(_spValue.GetPointer(), pValue);
		};

		template<typename TValue>
		bool
		SmartMetaProperty<TValue>::
		getUntypedValue(LightPointer& pValue) const
		{
			return SmartMetaPropertyUntypeHelper<ValuePointerType>::Convert(_spValue.GetPointer(), pValue);
		};

		template<typename TValue>
		void
		SmartMetaProperty<TValue>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			os << indent << "SmartMetaProperty [" << this->getMetaPropertyTypeName() << "]: " << std::endl;
			os << indent.GetNextIndent() << _spValue << std::endl;
		};

		template<typename TValue>
		SmartMetaProperty<TValue>::
		~SmartMetaProperty()
		{
		};

		template<typename TValue>
		SmartMetaProperty<TValue>::
		SmartMetaProperty(ValueSetType initValue)
		{
			_spValue = initValue;
		};

	}
}

#endif