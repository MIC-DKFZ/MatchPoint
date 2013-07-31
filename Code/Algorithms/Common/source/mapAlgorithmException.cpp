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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/source/mapAlgorithmException.cpp $
*/


#include "mapAlgorithmException.h"

namespace map
{
	namespace algorithm
	{

		AlgorithmException::BaseExceptionType *
		AlgorithmException::
		clone() const throw()
		{
			BaseExceptionType *pResult = 0;

			try
			{
				pResult = new AlgorithmException(this->GetFile() , this->GetLine() , this->GetDescription() , this->GetLocation());
			}
			catch (...)
			{
				//no throw guarantee
			}

			return pResult;
		};


		AlgorithmException::
		AlgorithmException() : Superclass()
		{};

		AlgorithmException::
		AlgorithmException(const char *file, unsigned int lineNumber) : Superclass(file, lineNumber)
		{};

		AlgorithmException::
		AlgorithmException(const std::string &file, unsigned int lineNumber) : Superclass(file, lineNumber)
		{};

		AlgorithmException::
		AlgorithmException(const std::string &file, unsigned int lineNumber, const std::string &desc, const std::string &loc) : Superclass(file, lineNumber, desc, loc)
		{};

		AlgorithmException::
		~AlgorithmException() throw()
		{};

		const char *
		AlgorithmException::
		GetNameOfClass() const
		{
			return "map::AlgorithmException";
		};


	} // end namespace algorithm
} // end namespace map