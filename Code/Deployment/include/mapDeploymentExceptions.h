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


#ifndef __MAP_DEPLOYMENT_EXCEPTIONS_H
#define __MAP_DEPLOYMENT_EXCEPTIONS_H

#include "mapExceptionObject.h"
#include "mapMAPDeploymentExports.h"

namespace map
{
	namespace deployment
	{
		/*!@def mapDeclareExceptionClassMacro
		* This macro is used to declare special exception classes.
		* @sa mapDefineExceptionClassMacro
		* @ingroup Exception
		*/
#define mapDeclareDeploymentExceptionClassMacro(newClass, superclass) \
	class MAPDeployment_EXPORT newClass : public superclass\
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

		/*! @class DeploymentException
		* @brief Base exception class used for deployment exceptions or errors within MatchPoint.
		*
		* @ingroup ExceptionDeployment
		*/
		mapDeclareDeploymentExceptionClassMacro(DeploymentException, core::ExceptionObject);

		/*! @class InvalidDLLException
		* @brief Exception class used for exceptions caused by invalid DLLs or the attempts to load such DLLs.
		*
		* @ingroup ExceptionDeployment
		*/
		mapDeclareDeploymentExceptionClassMacro(InvalidDLLException, DeploymentException);

		/*! @class MissingSymbolException
		* @brief Exception class used for exceptions caused by missing DLL symbols.
		*
		* @ingroup ExceptionDeployment
		*/
		mapDeclareDeploymentExceptionClassMacro(MissingSymbolException, InvalidDLLException);

		/*! @class InvalidInterfaceVersionException
		* @brief Exception class used for exceptions caused by an invalid deployment interface.
		*
		* @ingroup ExceptionDeployment
		*/
		mapDeclareDeploymentExceptionClassMacro(InvalidInterfaceVersionException, DeploymentException);

		/*! @class InvalidUIDException
		* @brief Exception class used for exceptions caused by an invalid algorithm UID.
		*
		* @ingroup ExceptionDeployment
		*/
		mapDeclareDeploymentExceptionClassMacro(InvalidUIDException, DeploymentException);

		/*! @class InvalidAlgorithmException
		* @brief Exception class used for exceptions caused by an invalid algorithms.
		*
		* @ingroup ExceptionDeployment
		*/
		mapDeclareDeploymentExceptionClassMacro(InvalidAlgorithmException, DeploymentException);


	} // end namespace deployment
} // end namespace map

#endif
