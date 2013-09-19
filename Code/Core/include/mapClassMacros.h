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


#ifndef __MAP_CLASS_MACROS_H
#define __MAP_CLASS_MACROS_H

#include "mapLogbookMacros.h"
#include "mapMetaProperty.h"
#include "mapMetaPropertyAccessor.h"

/** Set built-in type.  Creates member set"name"() (e.g., setVisibility()); */
#define mapSetMacro(name,type) \
	virtual void set##name (const type& value) \
	{ \
		mapLogDebugMacro(<< "setting " #name " to " << value); \
		if (this->_##name != value) \
		{ \
			this->_##name = value; \
			this->Modified(); \
		} \
	}

/** Set built-in type.  Creates member set"name"() (e.g., setVisibility()); */
#define mapSetVarMacro(name,type,variable) \
	virtual void set##name (const type value) \
	{ \
		mapLogDebugMacro(<< "setting " #name " to " << value); \
		if (this->variable != value) \
		{ \
			this->variable = value; \
			this->Modified(); \
		} \
	}

/** Set built-in type with MetaProperty support.
  This macro can only be used with algorithms that derive from MetaPropertyAlgorthimBase
	or implement a similar interface. Creates member set"name"() (e.g., setVisibility()).
	when setting a variable it will be passed as MetaProperty to its own setProperty function. */
#define mapSetMetaMacro(name,type) \
	virtual void set##name (const type value) \
	{ \
		mapLogDebugMacro(<< "setting " #name " to " << value); \
		this->setProperty( #name, ::map::core::MetaProperty< type >::New(value));\
	}

/** Get built-in type.  Creates member get"name"() (e.g., getVisibility()); */
#define mapGetMacro(name,type) \
	virtual type get##name () \
	{ \
		mapLogDebugMacro(<< "returning " << #name " of " << this->_##name ); \
		return this->_##name; \
	}

/** Get built-in type.  Creates member get"name"() (e.g., getVisibility()); */
#define mapGetVarMacro(name,type,variable) \
	virtual type get##name () \
	{ \
		mapLogDebugMacro(<< "returning " << #name " of " << this->variable ); \
		return this->variable; \
	}

/** Get built-in type.  Creates member get"name"() (e.g., getVisibility());
 * This is the "const" form of the mapGetMacro.  It should be used unless
 * the member can be changed through the "get" access routine. */
#define mapGetConstMacro(name,type) \
	virtual type get##name () const \
	{ \
		mapLogDebugMacro(<< "returning " << #name " of " << this->_##name ); \
		return this->_##name; \
	}

/** Get built-in type.  Creates member get"name"() (e.g., getVisibility());
 * This is the "const" form of the mapGetVarMacro.  It should be used unless
 * the member can be changed through the "get" access routine. */
#define mapGetConstVarMacro(name,type,variable) \
	virtual type get##name () const \
	{ \
		mapLogDebugMacro(<< "returning " << #name " of " << this->variable ); \
		return this-> variable; \
	}

/** Get built-in type.  Creates member get"name"() (e.g., getVisibility());
 * This is the "const" form of the mapGetMacro.  It should be used unless
 * the member can be changed through the "get" access routine.
 * This versions returns a const reference to the variable. */
#define mapGetConstReferenceMacro(name,type) \
	virtual const type & get##name () const \
	{ \
		mapLogDebugMacro(<< "returning " << #name " of " << this->_##name ); \
		return this->_##name; \
	}

/** Get built-in type.  Creates member get"name"() (e.g., getVisibility());
 * This is the "const" form of the mapGetVarMacro.  It should be used unless
 * the member can be changed through the "get" access routine.
 * This versions returns a const reference to the variable. */
#define mapGetConstReferenceVarMacro(name,type,variable) \
	virtual const type & get##name () const \
	{ \
		mapLogDebugMacro(<< "returning " << #name " of " << this->variable ); \
		return this-> variable; \
	}

/** Get built-in type via MetaProperty support.
  This macro can only be used with algorithms that derive from MetaPropertyAlgorthimBase
	or implement a similar interface. Creates member get"name"() (e.g., getVisibility());
  It uses the getProperty function to receives the value and unpacks it and returns a
	copy of the value. The result of the function indicates if the value is valid. */
#define mapGetMetaMacro(name,type) \
	virtual bool get##name (type& propValue) const \
	{ \
		mapLogDebugMacro(<< "returning " << #name " via MetaProperty support" ); \
		::map::core::MetaPropertyBase::Pointer spProp = this->getProperty(#name);\
		type tempVal;\
		bool result = ::map::core::unwrapCastedMetaProperty(spProp, tempVal);\
		propValue = tempVal;\
		return result; \
	}

/** Set pointer to object; uses Object reference counting methodology.
 * Creates method set"name"() (e.g., setPoints()). Note that using
 * smart pointers requires using real pointers when setting input,
 * but returning smart pointers on output. */
#define mapSetObjectMacro(name,type) \
	virtual void set##name (type* value) \
	{ \
		mapLogDebugMacro(<<"setting " << #name " to " << value ); \
		if (this->_##name != value) \
		{ \
			this->_##name = value; \
			this->Modified(); \
		} \
	}

/** Get a smart pointer to an object.  Creates the member
 * get"name"() (e.g., getPoints()). */
#define mapGetObjectMacro(name,type) \
	virtual type * get##name () \
	{ \
		mapLogDebugMacro(<<"returning " #name " address " << this->_##name ); \
		return this->_##name.GetPointer(); \
	}

/** Set const pointer to object; uses Object reference counting methodology.
 * Creates method set"name"() (e.g., setPoints()). Note that using
 * smart pointers requires using real pointers when setting input,
 * but returning smart pointers on output. */
#define mapSetConstObjectMacro(name,type) \
	virtual void set##name (const type* value) \
	{ \
		mapLogDebugMacro(<<"setting " << #name " to " << value ); \
		if (this->_##name != value) \
		{ \
			this->_##name = value; \
			this->Modified(); \
		} \
	}

/** Get a smart const pointer to an object.  Creates the member
 * get"name"() (e.g., getPoints()). */
#define mapGetConstObjectMacro(name,type) \
	virtual const type * get##name () const \
	{ \
		mapLogDebugMacro(<<"returning " #name " address " << this->_##name ); \
		return this->_##name.GetPointer(); \
	}

/** Get a const reference to a smart pointer to an object.
 * Creates the member get"name"() (e.g., getPoints()). */
#define mapGetConstReferenceObjectMacro(name,type) \
	virtual const typename type::Pointer & get##name () const \
	{ \
		mapLogDebugMacro(<<"returning " #name " address " << this->_##name ); \
		return this->_##name; \
	}

#endif
