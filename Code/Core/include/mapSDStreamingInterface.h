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



#ifndef __MAP_SD_STREAMING_INTERFACE_H
#define __MAP_SD_STREAMING_INTERFACE_H

#include "mapSDElement.h"

namespace map
{

	namespace structuredData
	{

		/** @class StreamingInterface
		* @brief Interface class that should be inherited and implemented by every class that should by
		* able to stream via map::structuredData elements.
		* @ingroup SD
		*/
		class MAPCore_EXPORT StreamingInterface
		{
		public:
			typedef Element::Pointer ElementPointer;

			ElementPointer streamToStructuredData() const;

			void streamFromStructuredData(const Element* pElement);

		protected:

			virtual ElementPointer streamToSDInternal() const = 0;

			virtual void streamFromSDInternal(const Element* pElement) = 0;

			StreamingInterface();
			virtual ~StreamingInterface();

		private:
			//No copy constructor allowed
			StreamingInterface(const StreamingInterface& source);
			void operator=(const StreamingInterface&);  //purposely not implemented
		};


	} //end of namespace structuredData

} //end of namespace map
#endif
