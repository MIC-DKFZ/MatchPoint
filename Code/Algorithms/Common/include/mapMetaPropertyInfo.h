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




#ifndef __META_PROPERTY_INFO_H
#define __META_PROPERTY_INFO_H

#include <typeinfo>

#include "itkLightObject.h"

#include "mapMacros.h"
#include "mapString.h"
#include "mapMAPAlgorithmsExports.h"


namespace map
{
	namespace algorithm
	{

		/*! @class MetaPropertyInfo
		@brief This class is used to bundle basic information of a MetaProperty.

		It is used by the MetaPropertyInterface to provide these information for all properties an algorithm supports.
		@sa MetaPropertyInterface
		@ingroup Algorithms
		*/
		class MAPAlgorithms_EXPORT MetaPropertyInfo : public ::itk::LightObject
		{
		public:
			/** Smart pointer typedef support. */
			typedef MetaPropertyInfo  Self;
			typedef ::itk::LightObject  Superclass;
			typedef ::itk::SmartPointer<Self>  Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;

			/** Run-time type information (and related methods). */
			itkTypeMacro(MetaPropertyInfo, LightObject);

			/**
			* @brief Creates a MetaProperty instance, initializes it and returns it via smartpointer.
			* @return A pointer to the MetaProperty.
			* @param name The name of the associated MetaProperty
			* @param type_info The type info of the value type used for the MetaProperty
			* @param isReadable Indicates if the property is readable
			* @param isWritable Indicates if the property is writable
			* @eguarantee strong
			*/
			static Pointer New(const core::String& name, const std::type_info& type_info,
							   bool isReadable = true, bool isWritable = false);

			/**
			* @brief Dublicates a MetaProperty instance. The value of the property is copied.
			* @return A pointer to the MetaProperty clone.
			* @eguarantee strong
			*/
			virtual ::itk::LightObject::Pointer CreateAnother(void) const;

			/**
			* @brief Returns the unique type name of the value type that stores the associated property.
			* @return A pointer to a const char array containing the unique type name.
			* @eguarantee strong
			*/
			const char* getTypeName() const;

			/**
			* @brief Returns the type_id of the value type that stores the associated property.
			* @eguarantee strong
			* @return A constant reference to a std::type_info object
			*/
			const std::type_info& getTypeInfo() const;

			/**
			* @brief Returns the identifying name of the associated property.
			* @eguarantee strong
			* @return A constant reference to a String that is the name
			*/
			const core::String& getName() const;

			/**
			* @brief Returns if the property is supposed to be accessed. This is
			* used by the MetaPropertyInterface to indicate if an reading attempt of
			* this property will fail and is supported respectively.
			* @eguarantee strong
			* @return Indication if property is readable (True).
			*/
			bool isReadable() const;

			/**
			* @brief Returns if the property is supposed to be changed. This is
			* used by the MetaPropertyInterface to indicate if an writting attempt of
			* this property will fail and is supported respectively.
			* @eguarantee strong
			* @return Indication if property is writable (True).
			*/
			bool isWritable() const;

		protected:
			core::String _name;
			const std::type_info& _type_info;
			bool _isReadable;
			bool _isWritable;

			/**
			* Defines the default behavior for printing out this element
			* @eguarantee strong
			* @param os An output stream
			*/
			virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

			~MetaPropertyInfo();
			MetaPropertyInfo(const core::String& name, const std::type_info& type_info, bool isReadable = true,
							 bool isWritable = false);
		private:
			MetaPropertyInfo(const Self&); //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#endif
