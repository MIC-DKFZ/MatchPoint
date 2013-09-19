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


#include "mapExceptionObject.h"

namespace map
{
	namespace core
	{
		ExceptionObject::BaseExceptionType*
		ExceptionObject::
		clone() const throw()
		{
			BaseExceptionType* pResult = 0;

			try
			{
				pResult = new ExceptionObject(this->GetFile() , this->GetLine() , this->GetDescription() ,
											  this->GetLocation());
			}
			catch (...)
			{
				//no throw guarantee
			}

			return pResult;
		};


		ExceptionObject::ExceptionObject()
		{
		}

		ExceptionObject::ExceptionObject(const char* file, unsigned int lineNumber) : Superclass(file,
					lineNumber)
		{

		}

		ExceptionObject::ExceptionObject(const std::string& file,
										 unsigned int lineNumber) : Superclass(file, lineNumber)
		{

		}

		ExceptionObject::ExceptionObject(const std::string& file, unsigned int lineNumber,
										 const std::string& desc, const std::string& loc) : Superclass(file, lineNumber, desc, loc)
		{

		}

		ExceptionObject::~ExceptionObject() throw()
		{
		}

		const char* ExceptionObject::GetNameOfClass() const
		{
			return "map::ExceptionObject";
		}

		std::ostream& operator<<(std::ostream& os, const ExceptionObject& e)
		{
			e.Print(os);
			return os;
		}

	} // end namespace core
} // end namespace map
