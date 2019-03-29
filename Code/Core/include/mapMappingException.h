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


#ifndef __MAP_MAPPING_EXCEPTION_H
#define __MAP_MAPPING_EXCEPTION_H

#include "mapRegistrationException.h"

namespace map
{
	namespace core
	{
		/*! @class MappingException
		* @brief Base exception class for exception in the context of data mapping by a registration.
		*
		* This is the base class for any exception that by an illegal mapping processed by a registration performer.
		* @ingroup Exception
		*/
		class MAPCore_EXPORT MappingException : public RegistrationException
		{
		public:
			using Self = MappingException;
			using Superclass = RegistrationException;

			/*! Default constructor.  Needed to ensure the exception object can be
			 * copied. */
			MappingException()  {}

			/*! Constructor. Needed to ensure the exception object can be copied. */
			MappingException(const char* file, unsigned int lineNumber) : Superclass(file, lineNumber) {}

			/*! Constructor. Needed to ensure the exception object can be copied. */
			MappingException(const String& file, unsigned int lineNumber) : Superclass(file, lineNumber) {}

			/*! Constructor. Needed to ensure the exception object can be copied. */
			MappingException(const String& file, unsigned int lineNumber, const String& desc,
							 const std::string& loc) : Superclass(file, lineNumber, desc, loc) {}

			/*! Virtual destructor needed for subclasses. Has to have empty throw(). */
			~MappingException() noexcept override = default;

			const char* GetNameOfClass() const override
			{
				return "map::MappingException";
			}

			/*! Clones the exception object and returns a pointer to a copy of the exception object.
			 * The cloned object is created on the heap and should function caller has to take care about
			 * proper destruction (e.g. using auto pointer or tr1::shared_pointer).
			 * @remark Used a plain pointer as return value in this case to ensure the no throw guarantee.
			 * This feature is needed by some classes like MappingTaskBatch to ensure the feature of
			 * processing tasks in multiple threads and to deal with any exception after joining the threads
			 * and every task is processed (or failed through an exception).
			 * @return Pointer to the cloned exception. If the cloning fails for any reason the return is NULL.
			 * @eguarantee no throw*/
			BaseExceptionType* clone() const noexcept override;
		};

	} // end namespace core
} // end namespace map


#endif
