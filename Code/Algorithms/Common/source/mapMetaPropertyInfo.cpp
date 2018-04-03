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



#include "mapMetaPropertyInfo.h"

namespace map
{
	namespace algorithm
	{

		MetaPropertyInfo::Pointer
		MetaPropertyInfo::
		New(const core::String& name, const std::type_info& type_info, bool isReadable, bool isWritable)
		{
			Pointer smartPtr;
			Self* rawPtr = new Self(name, type_info, isReadable, isWritable);
			smartPtr = rawPtr;
			rawPtr->UnRegister();
			return smartPtr;
		};

		::itk::LightObject::Pointer
		MetaPropertyInfo::
		CreateAnother(void) const
		{
			::itk::LightObject::Pointer smartPtr;
			smartPtr = Self::New(this->_name, this->_type_info, this->_isReadable,
								 this->_isWritable).GetPointer();
			return smartPtr;
		};

		const char*
		MetaPropertyInfo::
		getTypeName() const
		{
			return this->_type_info.name();
		};


		const std::type_info&
		MetaPropertyInfo::
		getTypeInfo() const
		{
			return this->_type_info;
		};

		const core::String&
		MetaPropertyInfo::
		getName() const
		{
			return this->_name;
		};

		bool
		MetaPropertyInfo::
		isReadable() const
		{
			return this->_isReadable;
		};

		bool
		MetaPropertyInfo::
		isWritable() const
		{
			return this->_isWritable;
		};

		void
		MetaPropertyInfo::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent << "Name:     " << this->_name << std::endl;
			os << indent << "Type:     " << this->_type_info.name() << std::endl;
			os << indent << "Readable: " << this->_isReadable << std::endl;
			os << indent << "Writable: " << this->_isWritable << std::endl;
		};

		MetaPropertyInfo::
		~MetaPropertyInfo()
		{
		};

		MetaPropertyInfo::
		MetaPropertyInfo(const core::String& name, const std::type_info& type_info, bool isReadable,
						 bool isWritable) :
			_name(name), _type_info(type_info), _isReadable(isReadable), _isWritable(isWritable)
		{};

	}
}


