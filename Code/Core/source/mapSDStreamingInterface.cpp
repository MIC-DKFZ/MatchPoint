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



#include "mapSDStreamingInterface.h"
#include "mapExceptionObjectMacros.h"

namespace map
{

	namespace structuredData
	{
		StreamingInterface::ElementPointer
		StreamingInterface::
		streamToStructuredData() const
		{
			return this->streamToSDInternal();
		};

		void
		StreamingInterface::
		streamFromStructuredData(const Element* pElement)
		{
			if (!pElement)
			{
				mapDefaultExceptionStaticMacro( <<
												"Error. Cannot stream from StructuredData element. Passed element pointer is NULL.");
			}

			this->streamFromSDInternal(pElement);
		};

		StreamingInterface::
		StreamingInterface() {};

		StreamingInterface::
		~StreamingInterface() {};

	} //end of namespace structuredData

} //end of namespace map
