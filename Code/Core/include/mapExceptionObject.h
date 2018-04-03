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


#ifndef __MAP_EXCEPTION_OBJECT_H
#define __MAP_EXCEPTION_OBJECT_H

#include "itkMacro.h"

#include "mapMacros.h"
#include "mapString.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{
		/*! @class ExceptionObject
		* @brief Base exception class used within MatchPoint.
		*
		* This is the base class for any exception that is caused by MatchPoint's own code.
		* @ingroup Exception
		*/
		class MAPCore_EXPORT ExceptionObject : public itk::ExceptionObject
		{
		public:
			typedef itk::ExceptionObject Superclass;
			typedef ExceptionObject BaseExceptionType;

			/*! Default constructor.  Needed to ensure the exception object can be
			 * copied. */
			ExceptionObject();

			/*! Constructor. Needed to ensure the exception object can be copied. */
			ExceptionObject(const char* file, unsigned int lineNumber);

			/*! Constructor. Needed to ensure the exception object can be copied. */
			ExceptionObject(const std::string& file, unsigned int lineNumber);

			/*! Constructor. Needed to ensure the exception object can be copied. */
			ExceptionObject(const std::string& file, unsigned int lineNumber, const std::string& desc,
							const std::string& loc);

			/*! Virtual destructor needed for subclasses. Has to have empty throw(). */
			virtual ~ExceptionObject() throw();

			virtual const char* GetNameOfClass() const;

			/*! Clones the exception object and returns a pointer to a copy of the exception object.
			  * The cloned object is created on the heap and should function caller has to take care about
			  * proper destruction (e.g. using auto pointer or tr1::shared_pointer).
			  * @remark Used a plain pointer as return value in this case to ensure the no throw guarantee.
			  * This feature is needed by some classes like MappingTaskBatch to ensure the feature of
			  * processing tasks in multiple threads and to deal with any exception after joining the threads
			  * and every task is processed (or failed through an exception).
			  * @return Pointer to the cloned exception. If the cloning fails for any reason the return is NULL.
			  * @eguarantee no throw*/
			virtual BaseExceptionType* clone() const throw();
		};

		MAPCore_EXPORT std::ostream& operator<<(std::ostream& os, const ExceptionObject& e);

	} // end namespace core
} // end namespace map


#include "mapExceptionObjectMacros.h"

#endif
