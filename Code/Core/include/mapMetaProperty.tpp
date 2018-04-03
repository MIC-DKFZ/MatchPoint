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



#ifndef __MAP_META_PROPERTY_TPP
#define __MAP_META_PROPERTY_TPP

namespace map
{
	namespace core
	{
		template<typename TValue>
		typename MetaProperty<TValue>::Pointer
		MetaProperty<TValue>::
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
		MetaProperty<TValue>::
		CreateAnother(void) const
		{
			::itk::LightObject::Pointer smartPtr;
			smartPtr = Self::New(this->_value).GetPointer();
			return smartPtr;
		}

		template<typename TValue>
		::itk::LightObject::Pointer
		MetaProperty<TValue>::
		InternalClone() 	const
		{
			::itk::LightObject::Pointer smartPtr;
			smartPtr = Self::New(this->_value).GetPointer();
			return smartPtr;
		}

		template<typename TValue>
		const char*
		MetaProperty<TValue>::
		getMetaPropertyTypeName() const
		{
			return typeid(ValueType).name();
		};

		template<typename TValue>
		const std::type_info&
		MetaProperty<TValue>::
		getMetaPropertyTypeInfo(void) const
		{
			return typeid(ValueType);
		};

		template<typename TValue>
		typename MetaProperty<TValue>::ValueGetType
		MetaProperty<TValue>::
		getValue() const
		{
			return _value;
		};

		template<typename TValue>
		void
		MetaProperty<TValue>::
		setValue(ValueSetType newValue)
		{
			_value = newValue;
		};

		template<typename TValue>
		void
		MetaProperty<TValue>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			os << indent << "MetaProperty [" << this->getMetaPropertyTypeName() << "]: " << std::endl;
			os << indent.GetNextIndent() << _value << std::endl;
		};

		template<typename TValue>
		MetaProperty<TValue>::
		~MetaProperty()
		{
		};

		template<typename TValue>
		MetaProperty<TValue>::
		MetaProperty(ValueSetType initValue)
		{
			_value = initValue;
		};

	}
}

#endif