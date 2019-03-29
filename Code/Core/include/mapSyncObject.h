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


#ifndef __MAP_SYNC_OBJECT_H
#define __MAP_SYNC_OBJECT_H

#include <map>

#include "mapString.h"
#include "mapMetaPropertyBase.h"
#include "mapMetaPropertyAccessor.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace deployment
	{

		/** SyncObject that containes all relevant informations
		 * for deployment DLLs to be synced with the host apllication.
		 * This class is used by deployment::Synchronizer and Objects
		 * that implement the DeploymentSyncInterface.*/
		class MAPCore_EXPORT SyncObject
		{
		public:
			using SyncPropertyTagType = core::String;
			typedef std::map<SyncPropertyTagType, core::MetaPropertyBase::Pointer> SyncPropertyMapType;

			SyncPropertyMapType _map;

			template<typename TPropReturnType> bool getProperty(SyncPropertyTagType tag,
					TPropReturnType& prop) const
			{
				bool result = false;

				auto finding = _map.find(tag);

				if (finding != _map.end())
				{
					result = core::unwrapCastedMetaProperty<TPropReturnType>(finding->second, prop);
				}

				return result;
			}

			SyncObject();
			~SyncObject();

		};

	} // end namespace deployment
} // end namespace map

#endif
