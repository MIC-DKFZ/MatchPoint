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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/include/mapRegistrationKernelLoadRequest.h $
*/

#ifndef __MAP_REGISTRATION_KERNEL_LOAD_REQUEST_H
#define __MAP_REGISTRATION_KERNEL_LOAD_REQUEST_H

#include "mapSDElement.h"
#include "mapMAPIOExports.h"

namespace map
{
	namespace io
	{
		/*! @class RegistrationKernelLoadRequest
		* @brief Request class used by RegistrationFileReader and RegistrationKernelLoaderBase.
		*
		* This class is used as request type for the provider stack of RegistrationFileReader.
		* @ingroup RegOperation
		* @sa RegistrationFileReader
			*/
		class MAPIO_EXPORT RegistrationKernelLoadRequest
		{
		public:

			structuredData::Element::ConstPointer _spKernelDescriptor;
			bool _preferLazyLoading;

			/*! Constructor
			 * \pre pKernelDescriptor must not be NULL*/
			RegistrationKernelLoadRequest(const structuredData::Element *pKernelDescriptor, bool preferLazyLoading);
			~RegistrationKernelLoadRequest();

			RegistrationKernelLoadRequest(const RegistrationKernelLoadRequest &);
			void operator=(const RegistrationKernelLoadRequest &);
		};

		std::ostream &operator<<(std::ostream &os, const RegistrationKernelLoadRequest &request);

	} // end namespace io
} // end namespace map


#endif
