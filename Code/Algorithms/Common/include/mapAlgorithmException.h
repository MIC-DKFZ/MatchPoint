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


#ifndef __MAP_ALGORITHM_EXCEPTION_H
#define __MAP_ALGORITHM_EXCEPTION_H

#include "mapExceptionObject.h"
#include "mapMAPAlgorithmsExports.h"

namespace map
{
	namespace algorithm
	{
		/*! @class AlgorithmException
		* @brief Base exception class for algorithmic exceptions used within MatchPoint.
		*
		* This is the base class for any exception that is caused by MatchPoint's own code.
		* @ingroup Exception
		*/
		class MAPAlgorithms_EXPORT AlgorithmException : public core::ExceptionObject
		{
		public:
			using Superclass = core::ExceptionObject;
			using BaseExceptionType = core::ExceptionObject;

			/*! Default constructor.  Needed to ensure the exception object can be
			 * copied. */
			AlgorithmException();

			/*! Constructor. Needed to ensure the exception object can be copied. */
			AlgorithmException(const char* file, unsigned int lineNumber);

			/*! Constructor. Needed to ensure the exception object can be copied. */
			AlgorithmException(const std::string& file, unsigned int lineNumber);

			/*! Constructor. Needed to ensure the exception object can be copied. */
			AlgorithmException(const std::string& file, unsigned int lineNumber, const std::string& desc,
							   const std::string& loc);

			/*! Virtual destructor needed for subclasses. Has to have empty throw(). */
			~AlgorithmException() noexcept override;

			const char* GetNameOfClass() const override;

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

	} // end namespace algorithm
} // end namespace map

#endif
