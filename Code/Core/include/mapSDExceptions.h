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



#ifndef __MAP_SD_EXCEPTIONS_H
#define __MAP_SD_EXCEPTIONS_H

#include "mapExceptionObject.h"


namespace map
{
	namespace core
	{
		/** @class MissingIdentifierException
		* @brief Exception for missing keys (e.g. in structured data)
		*
		* MissingIdentifierException is used if request specified by a key/name/id was made
		* and this identifier is missing.
		*
		* @ingroup Exception
		*/
		class MAPCore_EXPORT MissingIdentifierException : public ExceptionObject
		{
		public:
			typedef MissingIdentifierException Self;
			typedef ExceptionObject Superclass;

			/*! Default constructor.  Needed to ensure the exception object can be
			* copied. */
			MissingIdentifierException();

			/*! Constructor. Needed to ensure the exception object can be copied. */
			MissingIdentifierException(const String& file, unsigned int lineNumber);

			/*! Constructor. Needed to ensure the exception object can be copied. */
			MissingIdentifierException(const String& file, unsigned int lineNumber, const String& desc,
									   const String& loc);

			/*! Virtual destructor needed for subclasses. Has to have empty throw(). */
			virtual ~MissingIdentifierException() throw();

			virtual const char* GetNameOfClass() const
			{
				return "map::MissingIdentifierException";
			}

			/*! Clones the exception object and returns a pointer to a copy of the exception object.
			* The cloned object is created on the heap and should function caller has to take care about
			* proper destruction (e.g. using auto pointer or tr1::shared_pointer).
			* @remark Used a plain pointer as return value in this case to ensure the no throw guarantee.
			* This feature is needed by some classes like RegistrationTaskBatch to ensure the feature of
			* processing tasks in multiple threads and to deal with any exception after joining the threads
			* and every task is processed (or failed through an exception).
			* @return Pointer to the cloned exception. If the cloning fails for any reason the return is NULL.
			* @eguarantee no throw*/
			virtual BaseExceptionType* clone() const throw();
		};

		MAPCore_EXPORT std::ostream& operator<<(std::ostream& os,
												const MissingIdentifierException& exception);

		/** @class OutOfRangeException
		* @brief Exception for requests that are out of range.
		*
		* OutOfRangeException is used if an index or request is out of range.
		*
		* @ingroup Exception
		*/
		class MAPCore_EXPORT OutOfRangeException : public ExceptionObject
		{
		public:
			typedef OutOfRangeException Self;
			typedef ExceptionObject Superclass;

			/*! Default constructor.  Needed to ensure the exception object can be
			* copied. */
			OutOfRangeException();

			/*! Constructor. Needed to ensure the exception object can be copied. */
			OutOfRangeException(const String& file, unsigned int lineNumber);

			/*! Constructor. Needed to ensure the exception object can be copied. */
			OutOfRangeException(const String& file, unsigned int lineNumber, const String& desc,
								const String& loc);

			/*! Virtual destructor needed for subclasses. Has to have empty throw(). */
			virtual ~OutOfRangeException() throw();

			virtual const char* GetNameOfClass() const
			{
				return "map::OutOfRangeException";
			}

			/*! Clones the exception object and returns a pointer to a copy of the exception object.
			* The cloned object is created on the heap and should function caller has to take care about
			* proper destruction (e.g. using auto pointer or tr1::shared_pointer).
			* @remark Used a plain pointer as return value in this case to ensure the no throw guarantee.
			* This feature is needed by some classes like RegistrationTaskBatch to ensure the feature of
			* processing tasks in multiple threads and to deal with any exception after joining the threads
			* and every task is processed (or failed through an exception).
			* @return Pointer to the cloned exception. If the cloning fails for any reason the return is NULL.
			* @eguarantee no throw*/
			virtual BaseExceptionType* clone() const throw();
		};

		MAPCore_EXPORT std::ostream& operator<<(std::ostream& os, const OutOfRangeException& exception);

		/** @class SDStreamingException
		* @brief Exception for missing keys in f.r.e.e..
		*
		* SDStreamingException is used if there is an error while streaming structured data.
		*
		* @ingroup Exceptions
		*/
		class MAPCore_EXPORT SDStreamingException : public ExceptionObject
		{
		public:
			typedef SDStreamingException Self;
			typedef ExceptionObject Superclass;

			/*! Default constructor.  Needed to ensure the exception object can be
			* copied. */
			SDStreamingException();

			/*! Constructor. Needed to ensure the exception object can be copied. */
			SDStreamingException(const String& file, unsigned int lineNumber);

			/*! Constructor. Needed to ensure the exception object can be copied. */
			SDStreamingException(const String& file, unsigned int lineNumber, const String& desc,
								 const String& loc);

			/*! Virtual destructor needed for subclasses. Has to have empty throw(). */
			virtual ~SDStreamingException() throw();

			virtual const char* GetNameOfClass() const
			{
				return "map::SDStreamingException";
			}

			/*! Clones the exception object and returns a pointer to a copy of the exception object.
			* The cloned object is created on the heap and should function caller has to take care about
			* proper destruction (e.g. using auto pointer or tr1::shared_pointer).
			* @remark Used a plain pointer as return value in this case to ensure the no throw guarantee.
			* This feature is needed by some classes like RegistrationTaskBatch to ensure the feature of
			* processing tasks in multiple threads and to deal with any exception after joining the threads
			* and every task is processed (or failed through an exception).
			* @return Pointer to the cloned exception. If the cloning fails for any reason the return is NULL.
			* @eguarantee no throw*/
			virtual BaseExceptionType* clone() const throw();
		};

		MAPCore_EXPORT std::ostream& operator<<(std::ostream& os, const SDStreamingException& exception);

	} //end of namespace core
} //end of namespace map

#endif
