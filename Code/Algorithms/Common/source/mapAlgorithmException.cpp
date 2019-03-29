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


#include "mapAlgorithmException.h"

namespace map
{
	namespace algorithm
	{

		AlgorithmException::BaseExceptionType*
		AlgorithmException::
		clone() const noexcept
		{
			BaseExceptionType* pResult = nullptr;

			try
			{
				pResult = new AlgorithmException(this->GetFile() , this->GetLine() , this->GetDescription() ,
												 this->GetLocation());
			}
			catch (...)
			{
				//no throw guarantee
			}

			return pResult;
		};


		AlgorithmException::
		AlgorithmException()  
		{};

		AlgorithmException::
		AlgorithmException(const char* file, unsigned int lineNumber) : Superclass(file, lineNumber)
		{};

		AlgorithmException::
		AlgorithmException(const std::string& file, unsigned int lineNumber) : Superclass(file, lineNumber)
		{};

		AlgorithmException::
		AlgorithmException(const std::string& file, unsigned int lineNumber, const std::string& desc,
						   const std::string& loc) : Superclass(file, lineNumber, desc, loc)
		{};

		AlgorithmException::
		~AlgorithmException() noexcept
		= default;

		const char*
		AlgorithmException::
		GetNameOfClass() const
		{
			return "map::AlgorithmException";
		};


	} // end namespace algorithm
} // end namespace map