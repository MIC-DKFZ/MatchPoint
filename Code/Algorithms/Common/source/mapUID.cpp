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



#include "mapUID.h"

namespace map
{
	namespace algorithm
	{

		UID::Pointer
		UID::
		New(const NamespaceType& ns, const NameType& name, const VersionType& version,
			const BuildTagType& buildTag)
		{
			Pointer smartPtr;
			Self* rawPtr = new Self(ns, name, version, buildTag);
			smartPtr = rawPtr;
			rawPtr->UnRegister();
			return smartPtr;
		};

		const UID::NamespaceType&
		UID::
		getNamespace() const
		{
			return this->_namespace;
		};

		const UID::NameType&
		UID::
		getName() const
		{
			return this->_name;
		};

		const UID::VersionType&
		UID::
		getVersion() const
		{
			return this->_version;
		};

		const UID::BuildTagType&
		UID::
		getBuildTag() const
		{
			return this->_buildTag;
		};

		const core::String
		UID::
		toStr() const
		{
			core::OStringStream stream;
			stream << this->_namespace << "::" << this->_name << "::" << this->_version << "::" <<
				   this->_buildTag;
			core::String result = stream.str();

			return result;
		};


		void
		UID::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent << "Namespace:    " << this->_namespace << std::endl;
			os << indent << "Name:         " << this->_name << std::endl;
			os << indent << "Version:      " << this->_version << std::endl;
			os << indent << "Build number: " << this->_buildTag << std::endl;
		};

		UID::
		~UID()
		{
		};

		UID::
		UID(const NamespaceType& ns, const NameType& name, const VersionType& version,
			const BuildTagType& buildTag) :
			_namespace(ns), _name(name), _version(version), _buildTag(buildTag)
		{};

		bool compareUIDs(const UID& uid1, const UID& uid2, bool wcNamespace, bool wcName, bool wcVersion,
						 bool wcBuild)
		{
			if ((uid1.getNamespace() != uid2.getNamespace()) && (! wcNamespace))
			{
				return false;
			}

			if ((uid1.getName() != uid2.getName()) && (! wcName))
			{
				return false;
			}

			if ((uid1.getVersion() != uid2.getVersion()) && (! wcVersion))
			{
				return false;
			}

			if ((uid1.getBuildTag() != uid2.getBuildTag()) && (! wcBuild))
			{
				return false;
			}

			return true;
		};

		bool compareUIDs(const UID* uid1, const UID* uid2, bool wcNamespace, bool wcName, bool wcVersion,
						 bool wcBuild)
		{
			if (!uid1 || !uid2)
			{

				return false;
			}

			return compareUIDs(*uid1, *uid2, wcNamespace, wcName, wcVersion, wcBuild);
		};


	}
}


