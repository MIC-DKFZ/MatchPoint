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




#ifndef __META_PROPERTY_ALGORITHM_BASE_H
#define __META_PROPERTY_ALGORITHM_BASE_H

#include "mapMetaPropertyAlgorithmInterface.h"

namespace map
{
	namespace algorithm
	{

		/*! @class MetaPropertyAlgorithmBase
		@brief This is the default implementation of the MetaPropertyAlgorithmInterface for algorithms that are able to grant an generic access to their properties.

		A algorithm implementing this interface offers a possibility to set or get values of selected properties
		of the algorithm. This feature is very useful to establish generic handling interfaces between a host application
		and algorithms.\n\n
		This implementation uses a meta property cache to store all properties that are set by the user. The
		Properties will be transfered to the internal algorithm by calling the member\n\n
		If you want to support the feature of sealed algorithms, its important to regard the remark on how to
		compile the property information (see compileInfos()).
		@ingroup AlgorithmFacets
		*/
		class MAPAlgorithms_EXPORT MetaPropertyAlgorithmBase : public facet::MetaPropertyAlgorithmInterface
		{
		public:
			typedef MetaPropertyAlgorithmBase Self;

			typedef facet::MetaPropertyAlgorithmInterface::MetaPropertyVectorType MetaPropertyVectorType;
			typedef facet::MetaPropertyAlgorithmInterface::MetaPropertyType MetaPropertyType;
			typedef facet::MetaPropertyAlgorithmInterface::MetaPropertyPointer MetaPropertyPointer;
			typedef facet::MetaPropertyAlgorithmInterface::MetaPropertyNameType MetaPropertyNameType;


			/*! Returns the MetaPropertyInfo for the property identified by the passed name
			@eguarantee strong
			@return returns SmartPointer to the MetaPropertyInfo. SmartPointer may be null,
			if the passed property name is unkown.
			@retval NULL-pointer Property is unknown
			*/
			virtual MetaPropertyInfo::Pointer getPropertyInfo(const MetaPropertyNameType& name) const;

			/*! Returns a vector with smart pointer to MetaPropertyInfos for all known and therefor supported
			* properties.
			* @remark this method calls the protectes virtual methods compilePublicInfos() and compileProtectedInfos()
			* to generate the list.
			* @eguarantee strong
			* @return returns vector of smart pointer to the MetaPropertyInfos.
			*/
			virtual MetaPropertyVectorType getPropertyInfos() const;

			/*! Returns a smart pointer to the MetaProperty identified by the passed name.
			* This default implementation is:\n
			* 1. Check if getting MetaProperty is legal\n
			* 2. Check the cache. Return cached value if existing.\n
			* 3. Call doGetProperty().\n
			* @remark Implement doGetProperty() to realize the handling and forwarding of properties
			* @eguarantee strong
			* @return Returns a smart pointer to the requested MetaProperty. If the property is
			* unknown, not readable or not supported the returned smart pointer will point to NULL.
			* @param name Name that identifies the wanted property.
			*/
			virtual MetaPropertyPointer getProperty(const MetaPropertyNameType& name) const;

			/*! Returns a smart pointer to the MetaProperty identified by the passed name.
			* This default implementation is:\n
			* 1. Check if getting MetaProperty is legal\n
			* 2. Check the cache. Return cached value if existing.\n
			* 3. Call doGetProperty().\n
			* @remark Implement doGetProperty() to realize the handling and forwarding of properties
			* @eguarantee strong
			* @param pInfo Pointer to the MetaPropertyInfo that specifies the wanted property (by name).
			* Method will throw an exception if passed Pointer is NULL.
			* @return Returns a smart pointer to the requested MetaProperty. If the property is
			* unknown, not readable or not supported the returned smart pointer will point to NULL.
			* @pre The type defined in the pInfo must equal the type of the MetaProperty; otherwise an exception
			* will be raised.
			* @exception ::map::core::ExceptionObject Thrown if the precondition is not satisfied (pInfo is NULL or has wrong type).
			* @overload
			*/
			virtual MetaPropertyPointer getProperty(const MetaPropertyInfo* pInfo) const;

			/*! Allows the transferring and setting of instance properties via this generic interface.
			* This base implementation will store the property in the cache (overwrites an already cached instance
			* of the property if necessary). The internal algorithm will be configured with the MetaProperties by
			* calling configureAlgorithmByMetaProperties().
			* @param name Name that identifies the property that should be set.
			* @param pProperty Pointer to the MetaProperty that contains the value that should be set.
			* Method will throw an exception if passed Pointer is NULL.
			* @return Indicates if the property was known and writable (true) or is not supported/writable (false).
			* @remark The function may raise exceptions. It depends on the implementation of the class setters
			* that will be used to finally integrate the passed and unwrapped property value into the instance.
			* @pre pProperty must point to a valid instance.
			* @exception ::map::core::ExceptionObject Thrown if a precondition is not satisfied
			* (pProperty is not valid).
			*/
			virtual bool setProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

			/*! Allows the transferring and setting of instance properties via this generic interface.
			* This base implementation will store the property in the cache (overwrites an already cached instance
			* of the property if necessary). The internal algorithm will be configured with the MetaProperties by
			* calling configureAlgorithmByMetaProperties().
			* @param pInfo Pointer to the MetaPropertyInfo that specifies the wanted property (by name).
			* Method will throw an exception if passed Pointer is NULL.
			* @param pProperty Pointer to the MetaProperty that contains the value that should be set.
			* Method will throw an exception if passed Pointer is NULL.
			* @return Indicates if the property was known and writable (true) or is not supported/writable (false).
			* @remark The function may raise exceptions. It depends on the implementation of the class setters
			* that will be used to finally integrate the passed and unwrapped property value into the instance.
			* @pre pProperty must point to a valid instance.
			* @pre The type defined in the pInfo must equal the type of pProperty; otherwise an exception
			* will be raised.
			* @exception ::map::core::ExceptionObject Thrown if a precondition is not satisfied
			* (pInfo is NULL or has wrong type; pProperty is not valid).
			* @overload
			*/
			virtual bool setProperty(const MetaPropertyInfo* pInfo, const MetaPropertyType* pProperty);

		protected:
			MetaPropertyAlgorithmBase();
			virtual ~MetaPropertyAlgorithmBase();

			/*! This method should be implemented to define how to compile MetaProperties
			* and add it to the passed info vector.\n\n
			* IMPORTANT REMINDER: You must ensure that in cases of sealed algorithms
			* only properties are added to the infos vector that may be accessed. Otherwise
			* you may have access to internals of sealed algorithms. The best way to take
			* care about this is to use a include guard "#ifndef MAP_SEAL_ALGORITHMS"
			* on the properties that should not be available for sealed algorithms
			* @eguarantee strong
			* @param infos Vector of MetaPropertyInfoPointer. The public MetaPropertyInfos
			* will be added to this vector by the method.
			*/
			virtual void compileInfos(MetaPropertyVectorType& infos) const = 0;

			/*! This method configures the algorithm with the cached MetaProperties.
			* The default implementation does this by calling
			* doSetProperty() for each MetaProperty stored in the cache.
			* @remark Implement doSetProperty() to realize the handling of passed new property values.
			* @eguarantee basic.
			*/
			virtual void configureAlgorithmByMetaProperties();

			/*! Implement this Method to realize the getting of a property specified by name.
			@remark This method only is called by getProperty if getPropertyInfo has a valid return for the passed name
			and the property is identified as readable.
			@eguarantee strong
			@return Returns a smart pointer to the requested MetaProperty.
			@param name Name that identifies the wanted property.
			*/
			virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const = 0;

			/*! Implement this Method to realize the setting of a property specified by name.
			@remark This method only is called by setProperty if getPropertyInfo has a valid return for the passed name
			and the property is identified as writable.
			@param name Name that identifies the wanted property.
			@param pProperty Pointer to the MetaProperty that contains the value that should be set.
			@pre Passed pointer pProperty is not NULL.
			*/
			virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty) = 0;

			void resetMetaPropertyCache();

			unsigned long GetMTime() const;

		private:
			typedef std::map<MetaPropertyNameType, MetaPropertyPointer> MetaPropertyCacheType;

			/*! Cache for meta properties. The default implementation of GetProperty/SetProperty will use the cache in order to store
			user changes. See documentation of these members. The cache will be transfered to internal algorithm via configureAlgorithmByMetaProperties().
			@sa GetProperty
			@sa SetProperty
			*/
			MetaPropertyCacheType _metaPropertyCache;

			::itk::TimeStamp _cacheMTime;

			//No copy constructor allowed
			MetaPropertyAlgorithmBase(const Self& source); //purposely not implemented
			void operator=(const Self&);  //purposely not implemented

		};

	}
}

#endif
