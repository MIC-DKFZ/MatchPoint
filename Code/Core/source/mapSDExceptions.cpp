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


#include "mapSDExceptions.h"

namespace map
{
	namespace core
	{

		////////////////////////////////////////////////////////////////////////
		/// Implementation of map::MissingIdentifierException //////////////////
		////////////////////////////////////////////////////////////////////////

		MissingIdentifierException::
		MissingIdentifierException() : Superclass()
		{};

		MissingIdentifierException::
		MissingIdentifierException(const String& file, unsigned int lineNumber) : Superclass(file,
					lineNumber)
		{}  ;

		MissingIdentifierException::
		MissingIdentifierException(const String& file, unsigned int lineNumber, const String& desc,
								   const String& loc) : Superclass(file, lineNumber, desc, loc)
		{};

		MissingIdentifierException::
		~MissingIdentifierException() throw()
		{};



		MissingIdentifierException::BaseExceptionType*
		MissingIdentifierException::
		clone() const throw()
		{
			BaseExceptionType* pResult = 0;

			try
			{
				pResult = new MissingIdentifierException(this->GetFile() , this->GetLine() ,
						this->GetDescription() , this->GetLocation());
			}
			catch (...)
			{
				//no throw guarantee
			}

			return pResult;
		};

		std::ostream& operator<<(std::ostream& os, const MissingIdentifierException& exception)
		{
			exception.Print(os);
			return os;
		};

		////////////////////////////////////////////////////////////////////////
		/// Implementation of map::OutOfRangeException //////////////////
		////////////////////////////////////////////////////////////////////////

		OutOfRangeException::
		OutOfRangeException() : Superclass()
		{};

		OutOfRangeException::
		OutOfRangeException(const String& file, unsigned int lineNumber) : Superclass(file, lineNumber)
		{}  ;

		OutOfRangeException::
		OutOfRangeException(const String& file, unsigned int lineNumber, const String& desc,
							const String& loc) : Superclass(file, lineNumber, desc, loc)
		{};

		OutOfRangeException::
		~OutOfRangeException() throw()
		{};



		OutOfRangeException::BaseExceptionType*
		OutOfRangeException::
		clone() const throw()
		{
			BaseExceptionType* pResult = 0;

			try
			{
				pResult = new OutOfRangeException(this->GetFile() , this->GetLine() , this->GetDescription() ,
												  this->GetLocation());
			}
			catch (...)
			{
				//no throw guarantee
			}

			return pResult;
		};

		std::ostream& operator<<(std::ostream& os, const OutOfRangeException& exception)
		{
			exception.Print(os);
			return os;
		};

		////////////////////////////////////////////////////////////////////////
		/// Implementation of map::SDStreamingException //////////////////
		////////////////////////////////////////////////////////////////////////

		SDStreamingException::
		SDStreamingException() : Superclass()
		{};

		SDStreamingException::
		SDStreamingException(const String& file, unsigned int lineNumber) : Superclass(file, lineNumber)
		{}  ;

		SDStreamingException::
		SDStreamingException(const String& file, unsigned int lineNumber, const String& desc,
							 const String& loc) : Superclass(file, lineNumber, desc, loc)
		{};

		SDStreamingException::
		~SDStreamingException() throw()
		{};



		SDStreamingException::BaseExceptionType*
		SDStreamingException::
		clone() const throw()
		{
			BaseExceptionType* pResult = 0;

			try
			{
				pResult = new SDStreamingException(this->GetFile() , this->GetLine() , this->GetDescription() ,
												   this->GetLocation());
			}
			catch (...)
			{
				//no throw guarantee
			}

			return pResult;
		};

		std::ostream& operator<<(std::ostream& os, const SDStreamingException& exception)
		{
			exception.Print(os);
			return os;
		};

	} //end of namespace core
} //end of namespace map
