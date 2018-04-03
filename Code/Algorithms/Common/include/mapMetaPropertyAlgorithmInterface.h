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




#ifndef __META_PROPERTY_ALGORITHM_INTERFACE_H
#define __META_PROPERTY_ALGORITHM_INTERFACE_H

#include <vector>

#include "mapMetaPropertyInfo.h"
#include "mapMetaPropertyBase.h"
#include "mapExceptionObject.h"
#include "mapMAPAlgorithmsExports.h"


namespace map
{
	namespace algorithm
	{
		namespace facet
		{

			/*! @class MetaPropertyAlgorithmInterface
			@brief This is the interface for algorithms that are able to grant an generic access to their properties.

			A algorithm implementing this interface offers a possibility to set or get values of selected properties
			of the algorithm. This feature is very usefull to establish generic handling interfaces between a host application
			and algorithms.\n\n
			If you want to support the feature of sealed algorithms, its important to regard the remark on how to
			compile the property information (see compileInfos()).
			@ingroup AlgorithmFacets
			*/
			class MAPAlgorithms_EXPORT MetaPropertyAlgorithmInterface
			{
			public:
				typedef MetaPropertyAlgorithmInterface Self;

				typedef std::vector<MetaPropertyInfo::Pointer> MetaPropertyVectorType;
				typedef core::MetaPropertyBase MetaPropertyType;
				typedef MetaPropertyType::Pointer MetaPropertyPointer;
				typedef core::String MetaPropertyNameType;

				/*! Returns the MetaPropertyInfo for the property identified by the passed name
				@eguarantee strong
				@return returns SmartPointer to the MetaPropertyInfo. SmartPointer may be null,
				if the passed property name is unkown.
				@retval NULL-pointer Property is unknown
				*/
				virtual MetaPropertyInfo::Pointer getPropertyInfo(const MetaPropertyNameType& name) const = 0;

				/*! Returns a vector with smart pointer to MetaPropertyInfos for all known and therefor supported
				* properties.
				* @remark this method calls the protectes virtual methods compilePublicInfos() and compileProtectedInfos()
				* to generate the list.
				* @eguarantee strong
				* @return returns vector of smart pointer to the MetaPropertyInfos.
				*/
				virtual MetaPropertyVectorType getPropertyInfos() const = 0;

				/*! Returns a smart pointer to the MetaProperty identified by the passed name.
				* @remark Implement doGetProperty() to realize the handling and forwarding of properties
				* @eguarantee strong
				* @return Returns a smart pointer to the requested MetaProperty. If the property is
				* unkown, not readable or not supported the returned smart pointer will point to NULL.
				* @param name Name that identifies the wanted property.
				*/
				virtual MetaPropertyPointer getProperty(const MetaPropertyNameType& name) const = 0;

				/*! Returns a smart pointer to the MetaProperty identified by the passed name.
				* @remark Implement doGetProperty() to realize the handling and forwarding of properties
				* @eguarantee strong
				* @param pInfo Pointer to the MetaPropertyInfo that specifies the wanted property (by name).
				* Method will throw an exception if passed Pointer is NULL.
				* @return Returns a smart pointer to the requested MetaProperty. If the property is
				* unkown, not readable or not supported the returned smart pointer will point to NULL.
				* @pre The type defined in the pInfo must equal the type of the MetaProperty; otherwise an exception
				* will be raised.
				* @overload
				*/
				virtual MetaPropertyPointer getProperty(const MetaPropertyInfo* pInfo) const = 0;

				/*! Allows the transfering and setting of instance properties via this generic interface.
				* @remark Implement doSetProperty() to realize the handling of passed new property values.
				* @param name Name that identifies the property that should be set.
				* @param pProperty Pointer to the MetaProperty that containes the value that should be set.
				* Method will throw an exception if passed Pointer is NULL.
				* @return Indicates if the property was known and writable (true) or is not supported/writable (false).
				* @remark The function may raise exceptions. It depends on the implementation of the class setters
				* that will be used to finally integrate the passed and unwrapped property value into the instance.
				*/
				virtual bool setProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty) = 0;

				/*! Allows the transfering and setting of instance properties via this generic interface.
				* @remark Implement doSetProperty() to realize the handling of passed new property values.
				* @param pInfo Pointer to the MetaPropertyInfo that specifies the wanted property (by name).
				* Method will throw an exception if passed Pointer is NULL.
				* @param pProperty Pointer to the MetaProperty that containes the value that should be set.
				* Method will throw an exception if passed Pointer is NULL.
				* @return Indicates if the property was known and writable (true) or is not supported/writable (false).
				* @remark The function may raise exceptions. It depends on the implementation of the class setters
				* that will be used to finally integrate the passed and unwrapped property value into the instance.
				* @pre The type defined in the pInfo must equal the type of pProperty; otherwise an exception
				* will be raised.
				* @overload
				*/
				virtual bool setProperty(const MetaPropertyInfo* pInfo, const MetaPropertyType* pProperty) = 0;

			protected:
				MetaPropertyAlgorithmInterface() {};
				virtual ~MetaPropertyAlgorithmInterface() {};

			private:
				//No copy constructor allowed
				MetaPropertyAlgorithmInterface(const Self& source); //purposely not implemented
				void operator=(const Self&);  //purposely not implemented

			};
		}
	}
}

#endif
