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


#ifndef __MAP_EXCEPTION_OBJECT_MACROS_H
#define __MAP_EXCEPTION_OBJECT_MACROS_H

#include "mapExceptionObject.h"
#include "mapMacros.h"
#include "mapString.h"
#include "mapLogbook.h"
#include <sstream>

/*!@def mapDefaultExceptionMacro
 * This macro is used to throw a basic ExceptionObject within an object method.
 * The macro presumes that the object owns a method this->GetNameOfClass().\n
 * The macro will set file name, line number and function signature to the exception
 * and log the exception as error in the logbook before throwing it.\n
 * Use mapGenericDefaultExceptionMacro() for other objects that do not compli with the api or for
 * static functions.\n
 * Use mapExceptionMacro() if you want to specifiy a arbitrary exception class that should be thrown.
 * @sa mapGenericDefaultExceptionMacro
 * @sa mapExceptionMacro
 * Example usage looks like:
 * mapDefaultExceptionMacro(<< "this is an exception" << this->SomeVariable);
 * @ingroup Exception
 */
#define mapDefaultExceptionMacro(x) \
	{ \
		::map::core::OStringStream message; \
		message << "Exception: " << this->GetNameOfClass() \
				<< "(" << this << "): " x; \
		::map::core::ExceptionObject e_(__FILE__, __LINE__, message.str().c_str(),MAP_FUNCTION_SIGNATURE); \
		::map::core::OStringStream exmessage; \
		exmessage << "Throw exception: " << e_;\
		::map::core::Logbook::error(exmessage.str());\
		throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
	}

/*!@def mapDefaultExceptionStaticMacro
 * This macro is used to throw a basic ExceptionObject within an arbitrary object method
 * or static function.
 * The macro will set file name, line number and function signiture to the exception
 * and log the exception as error in the logbook before throwing it.\n
 * Use mapExceptionStaticMacro() if you want to specifiy a arbitrary exception class that should be thrown.
 * @sa mapExceptionStaticMacro
 * Example usage looks like:
 * mapDefaultExceptionStaticMacro(<< "this is an exception" << aVariable);
 * @ingroup Exception
 */
#define mapDefaultExceptionStaticMacro(x) \
	{ \
		::map::core::OStringStream message; \
		message << "Exception: " x; \
		::map::core::ExceptionObject e_(__FILE__, __LINE__, message.str().c_str(),MAP_FUNCTION_SIGNATURE); \
		::map::core::OStringStream exmessage; \
		exmessage << "Throw exception: " << e_;\
		::map::core::Logbook::error(exmessage.str());\
		throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
	}

/*!@def mapLogbookCheckDefaultExceptionMacro
 * This macro is used to throw a basic ExceptionObject within an object method.
 * The macro presumes that the object owns a method this->GetNameOfClass().\n
 * The macro will set file name, line number and function signiture to the exception.
 * If the logbook is already initialized, the exception will also be logged as error in the logbook
 * before throwing it. This Macro is used in cases were the logbook should not be initialized
 * for an exception, e.g. if the exception occures in the logbook implementation.\n
 * Example usage looks like:
 * mapLogbookCheckDefaultExceptionMacro(<< "this is an exception" << this->SomeVariable);
 * @ingroup Exception
 */
#define mapLogbookCheckDefaultExceptionMacro(x) \
	{ \
		::map::core::OStringStream message; \
		message << "Exception: " << this->GetNameOfClass() \
				<< "(" << this << "): " x; \
		::map::core::ExceptionObject e_(__FILE__, __LINE__, message.str().c_str(),MAP_FUNCTION_SIGNATURE); \
		if (::map::core::Logbook::isInitialized()) \
		{ \
			::map::core::OStringStream exmessage; \
			exmessage << "Throw exception: " << e_;\
			::map::core::Logbook::error(exmessage.str());\
		} \
		throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
	}

/*!@def mapExceptionMacro
 * This macro is used to throw the passed exception class within an object method.
 * The macro presumes that the object owns a method this->GetNameOfClass().\n
 * The macro will set file name, line number and function signiture to the exception
 * and log the exception as error in the logbook before throwing it.\n
 * Use mapGenericExceptionMacro() for other objects that do not compli with the api or for
 * static functions.\n
 * @sa mapGenericExceptionMacro
 *
 * Example usage looks like:
 * mapExceptionMacro(AnExceptionClass, << "this is an exception" << this->SomeVariable);
 * @ingroup Exception
 */
#define mapExceptionMacro( EType, x) \
	{ \
		::map::core::OStringStream message; \
		message << "Exception: " << this->GetNameOfClass() \
				<< "(" << this << "): " x; \
		EType e_(__FILE__, __LINE__, message.str().c_str(),MAP_FUNCTION_SIGNATURE); \
		::map::core::OStringStream exmessage; \
		exmessage << "Throw exception: " << e_;\
		::map::core::Logbook::error(exmessage.str());\
		throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
	}

/*!@def mapExceptionStaticMacro
 * This macro is used to throw an object of an abitrary exception class within
 * an arbitrary object method or static function.
 * The macro will set file name, line number and function signiture to the exception
 * and log the exception as error in the logbook before throwing it.\n
 * Example usage looks like:
 * mapExceptionStaticMacro(AnExceptionClass, << "this is an exception" << aVariable);
 * @ingroup Exception
 */
#define mapExceptionStaticMacro( EType, x) \
	{ \
		::map::core::OStringStream message; \
		message << "Exception: " x; \
		EType e_(__FILE__, __LINE__, message.str().c_str(),MAP_FUNCTION_SIGNATURE); \
		::map::core::OStringStream exmessage; \
		exmessage << "Throw exception: " << e_;\
		::map::core::Logbook::error(exmessage.str());\
		throw e_; /* Explicit naming to work around Intel compiler bug.  */ \
	}


/*!@def mapDeclareExceptionClassMacro
 * This macro is used to declare special exception classes.
 * @sa mapDefineExceptionClassMacro
 * @ingroup Exception
 */
#define mapDeclareExceptionClassMacro(newClass, superclass) \
	class MAPCore_EXPORT newClass : public superclass\
	{\
	public:\
		typedef superclass Superclass;\
		typedef Superclass::BaseExceptionType BaseExceptionType;\
		newClass ();\
		newClass (const char *file, unsigned int lineNumber);\
		newClass (const std::string& file, unsigned int lineNumber);\
		newClass (const std::string& file, unsigned int lineNumber, const std::string& desc, const std::string& loc);\
		virtual ~ newClass () throw();\
		virtual const char* GetNameOfClass() const;\
		virtual BaseExceptionType* clone () const throw();\
	}

/*!@def mapDefineExceptionClassMacro
 * This macro is used to define the members of exception classes, which have been declared using the mapDeclareExceptionClassMacro.
 * @sa mapDeclareExceptionClassMacro
 * @ingroup Exception
 */
#define mapDefineExceptionClassMacro(newClass) \
	newClass :: newClass () : Superclass() {}\
	newClass :: newClass (const char *file, unsigned int lineNumber) : Superclass(file, lineNumber){}\
	newClass :: newClass (const std::string& file, unsigned int lineNumber) : Superclass(file, lineNumber){}\
	newClass :: newClass (const std::string& file, unsigned int lineNumber, const std::string& desc, const std::string& loc) : Superclass(file, lineNumber, desc, loc){}\
	newClass :: ~newClass () throw() {}\
	const char* newClass :: GetNameOfClass() const\
	{ return "map::"#newClass; }\
	newClass :: BaseExceptionType* newClass::clone () const throw()\
	{ BaseExceptionType* pResult = 0;\
		try\
		{\
			pResult = new newClass(this->GetFile() , this->GetLine() , this->GetDescription() , this->GetLocation()); \
		}\
		catch(...) { /*no throw guarantee*/ }\
		return pResult;\
	}

#endif
