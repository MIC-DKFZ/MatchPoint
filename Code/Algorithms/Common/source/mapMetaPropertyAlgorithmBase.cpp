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



#include "mapMetaPropertyAlgorithmBase.h"

namespace map
{
	namespace algorithm
	{

		MetaPropertyInfo::Pointer
		MetaPropertyAlgorithmBase::
		getPropertyInfo(const MetaPropertyNameType& name) const
		{
			MetaPropertyVectorType infos = getPropertyInfos();

			MetaPropertyVectorType::iterator pos = infos.begin();

			MetaPropertyInfo::Pointer spResult = NULL;

			for (pos = infos.begin(); pos != infos.end(); ++pos)
			{
				if ((*pos)->getName() == name)
				{
					spResult = *pos;
					break;
				}
			}

			return spResult;
		};

		MetaPropertyAlgorithmBase::MetaPropertyVectorType
		MetaPropertyAlgorithmBase::
		getPropertyInfos() const
		{
			MetaPropertyVectorType infos;

			compileInfos(infos);

			return infos;
		};

		MetaPropertyAlgorithmBase::MetaPropertyPointer
		MetaPropertyAlgorithmBase::
		getProperty(const MetaPropertyNameType& name) const
		{
			MetaPropertyPointer spResult = NULL;

			MetaPropertyInfo::Pointer spInfo = getPropertyInfo(name);

			if (spInfo.IsNotNull())
			{
				if (spInfo->isReadable())
				{
					//check cache
					MetaPropertyCacheType::const_iterator pos = _metaPropertyCache.find(name);

					if (pos != _metaPropertyCache.end())
					{
						//get from cache
						mapLogDebugObjMacro("Get property from cache. Property: " << pos->first);
						spResult = pos->second;
					}
					else
					{
						//retrieve directly
						mapLogDebugObjMacro("Get property from internal instance. Property: " << name);
						spResult = doGetProperty(name);
					}
				}
			}

			return spResult;
		};

		MetaPropertyAlgorithmBase::MetaPropertyPointer
		MetaPropertyAlgorithmBase::
		getProperty(const MetaPropertyInfo* pInfo) const
		{
			MetaPropertyPointer spResult = NULL;

			if (!pInfo)
			{
				mapDefaultExceptionStaticMacro( << "Error while getting property. Passed property info is NULL.");
			}

			spResult = getProperty(pInfo->getName());

			if (spResult.IsNotNull())
			{
				if (!(spResult->getMetaPropertyTypeInfo() == pInfo->getTypeInfo()))
				{
					mapDefaultExceptionStaticMacro( <<
													"Error while getting property. Property value type differs from specified type in the property info. value type: "
													<< spResult->getMetaPropertyTypeInfo().name() << "; info type: " <<  pInfo->getTypeInfo().name());
				}
			}

			return spResult;
		};

		bool
		MetaPropertyAlgorithmBase::
		setProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
		{
			bool result = false;

			if (!pProperty)
			{
				mapDefaultExceptionStaticMacro( <<
												"Error while setting property. Passed property pointer is NULL. Property name: " << name);
			}

			MetaPropertyInfo::Pointer spInfo = getPropertyInfo(name);

			if (spInfo.IsNotNull())
			{
				if (!(pProperty->getMetaPropertyTypeInfo() == spInfo->getTypeInfo()))
				{
					mapDefaultExceptionStaticMacro("Error while setting property. Property value type differs from type specified by the algorithm. value type: "
												   << pProperty->getMetaPropertyTypeInfo().name() << "; internal type: " <<
												   spInfo->getTypeInfo().name());
				}

				if (spInfo->isWritable())
				{
					result = true;
					_metaPropertyCache[name] = pProperty->Clone();
					_cacheMTime.Modified();
				}
			}

			return result;
		};

		bool
		MetaPropertyAlgorithmBase::
		setProperty(const MetaPropertyInfo* pInfo, const MetaPropertyType* pProperty)
		{
			bool result = false;

			if (!pInfo)
			{
				mapDefaultExceptionStaticMacro( << "Error while setting property. Passed property info is NULL.");
			}

			if (!pProperty)
			{
				mapDefaultExceptionStaticMacro( <<
												"Error while setting property. Passed property pointer is NULL. Property name: " <<
												pInfo->getName());
			}

			if (!(pProperty->getMetaPropertyTypeInfo() == pInfo->getTypeInfo()))
			{
				mapDefaultExceptionStaticMacro("Error while setting property. Property value type differs from specified type in the property info. value type: "
											   << pProperty->getMetaPropertyTypeInfo().name() << "; info type: " <<  pInfo->getTypeInfo().name());
			}

			result = setProperty(pInfo->getName(), pProperty);

			return result;
		};

		void
		MetaPropertyAlgorithmBase::
		configureAlgorithmByMetaProperties()
		{
			for (MetaPropertyCacheType::iterator pos = _metaPropertyCache.begin();
				 pos != _metaPropertyCache.end(); ++pos)
			{
				mapLogDebugObjMacro("Set property: " << pos->first);

				doSetProperty(pos->first, pos->second);
			}

		};

		void
		MetaPropertyAlgorithmBase::
		resetMetaPropertyCache()
		{
			_metaPropertyCache.clear();
			_cacheMTime.Modified();
		};

		unsigned long
		MetaPropertyAlgorithmBase::
		GetMTime() const
		{
			return _cacheMTime.GetMTime();
		};

		MetaPropertyAlgorithmBase::
		MetaPropertyAlgorithmBase()
		{
		};

		MetaPropertyAlgorithmBase::
		~MetaPropertyAlgorithmBase()
		{
		};



	}
}


