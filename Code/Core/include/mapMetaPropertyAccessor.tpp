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



#ifndef __MAP_META_PROPERTY_ACCESSOR_TPP
#define __MAP_META_PROPERTY_ACCESSOR_TPP

namespace map
{
	namespace core
	{

		template<typename TValue>
		bool
		MetaPropertyAccessor<TValue>::
		unwrapPropertyValue(const MetaPropertyBase* pProperty, ValueType& value)
		{
			const InterfaceType* pAccessInterfaces = dynamic_cast<const InterfaceType*>(pProperty);
			bool result = false;

			if (pAccessInterfaces)
			{
				value = pAccessInterfaces->getValue();
				result = true;
			}

			return result;
		};

		template<typename TValue>
		bool
		MetaPropertyAccessor<TValue>::
		wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value)
		{
			InterfaceType* pAccessInterfaces = dynamic_cast<InterfaceType*>(pProperty);
			bool result = false;

			if (pAccessInterfaces)
			{
				pAccessInterfaces->setValue(value);
				result = true;
			}

			return result;
		};

		//////////////////////////////////////////////////////////
		// Specialiced version: const TValue *
		//////////////////////////////////////////////////////////

		template<typename TValue>
		bool
		MetaPropertyAccessor<const TValue*>::
		unwrapPropertyValue(const MetaPropertyBase* pProperty, ValueType& value)
		{
			const ConstInterfaceType* pConstAccessInterfaces = dynamic_cast<const ConstInterfaceType*>
					(pProperty);
			bool result = false;

			if (pConstAccessInterfaces)
			{
				value = pConstAccessInterfaces->getValue();
				result = true;
			}
			else
			{
				//we try to cast for the non const version, because it can also be used to get a const value
				//this is a conviniece for the case a non const proprty value should only be unwrapped as const
				//value
				const InterfaceType* pAccessInterfaces = dynamic_cast<const InterfaceType*>(pProperty);

				if (pAccessInterfaces)
				{
					value = pAccessInterfaces->getValue();
					result = true;
				}
			}

			return result;
		};

		template<typename TValue>
		bool
		MetaPropertyAccessor<const TValue*>::
		wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value)
		{
			ConstInterfaceType* pAccessInterfaces = dynamic_cast<ConstInterfaceType*>(pProperty);
			bool result = false;

			if (pAccessInterfaces)
			{
				pAccessInterfaces->setValue(value);
				result = true;
			}

			return result;
		};

		//////////////////////////////////////////////////////////
		// Specialiced version: itk::SmartPointer<TValue>
		//////////////////////////////////////////////////////////

		template<typename TValue>
		bool
		MetaPropertyAccessor< itk::SmartPointer<TValue> >::
		unwrapPropertyValue(const MetaPropertyBase* pProperty, SmartPointerType& spValue)
		{
			bool result = false;
			const InterfaceType* pAccessInterfaces = dynamic_cast<const InterfaceType*>(pProperty);

			if (pAccessInterfaces)
			{
				spValue = pAccessInterfaces->getValue();
				result = true;
			}

			return result;
		};

		template<typename TValue>
		bool
		MetaPropertyAccessor< itk::SmartPointer<TValue> >::
		wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value)
		{
			InterfaceType* pAccessInterfaces = dynamic_cast<InterfaceType*>(pProperty);
			bool result = false;

			if (pAccessInterfaces)
			{
				pAccessInterfaces->setValue(value);
				result = true;
			}

			return result;
		};

		//////////////////////////////////////////////////////////
		// Specialiced version: itk::SmartPointer< const TValue>
		//////////////////////////////////////////////////////////

		template<typename TValue>
		bool
		MetaPropertyAccessor< itk::SmartPointer<const TValue> >::
		unwrapPropertyValue(const MetaPropertyBase* pProperty, SmartPointerType& spValue)
		{
			const ConstInterfaceType* pConstAccessInterfaces = dynamic_cast<const ConstInterfaceType*>
					(pProperty);
			bool result = false;

			if (pConstAccessInterfaces)
			{
				spValue = pConstAccessInterfaces->getValue();
				result = true;
			}
			else
			{
				//we try to cast for the non const version, because it can also be used to get a const value
				//this is a conviniece for the case a non const proprty value should only be unwrapped as const
				//value
				const InterfaceType* pAccessInterfaces = dynamic_cast<const InterfaceType*>(pProperty);

				if (pAccessInterfaces)
				{
					spValue = pAccessInterfaces->getValue();
					result = true;
				}
			}

			return result;
		};

		template<typename TValue>
		bool
		MetaPropertyAccessor< itk::SmartPointer<const TValue> >::
		wrapPropertyValue(MetaPropertyBase* pProperty, ValueType value)
		{
			ConstInterfaceType* pAccessInterfaces = dynamic_cast<ConstInterfaceType*>(pProperty);
			bool result = false;

			if (pAccessInterfaces)
			{
				pAccessInterfaces->setValue(value);
				result = true;
			}

			return result;
		};

	}
}


#endif