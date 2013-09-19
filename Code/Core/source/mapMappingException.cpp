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


#include "mapMappingException.h"

namespace map
{
	namespace core
	{
		MappingException::BaseExceptionType*
		MappingException::
		clone() const throw()
		{
			BaseExceptionType* pResult = 0;

			try
			{
				pResult = new MappingException(this->GetFile() , this->GetLine() , this->GetDescription() ,
											   this->GetLocation());
			}
			catch (...)
			{
				//no throw guarantee
			}

			return pResult;
		};

	} // end namespace core
} // end namespace map