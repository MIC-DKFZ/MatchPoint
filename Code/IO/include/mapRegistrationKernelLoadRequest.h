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

#ifndef __MAP_REGISTRATION_KERNEL_LOAD_REQUEST_H
#define __MAP_REGISTRATION_KERNEL_LOAD_REQUEST_H

#include "mapSDElement.h"
#include "mapMAPIOExports.h"
#include "mapDimensionlessRegistrationKernelBase.h"

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

			/*! Descriptor for the kernel that should be loaded.*/
			structuredData::Element::ConstPointer _spKernelDescriptor;

			/*! Optional information that specifies the "sibling" kernel of the registration instance _spKernelDescriptor
			 * is a part of.
			 * Default value is NULL, indicating that there is no sibling or it should not regarded in the loading request.*/
			::map::core::DimensionlessRegistrationKernelBase::ConstPointer _spComplementaryKernel;

			bool _preferLazyLoading;

			/*! Constructor
			 * \pre pKernelDescriptor must not be NULL*/
			RegistrationKernelLoadRequest(const structuredData::Element* pKernelDescriptor,
										  bool preferLazyLoading, const core::DimensionlessRegistrationKernelBase* pComplementaryKernel =
											  NULL);
			~RegistrationKernelLoadRequest();

			RegistrationKernelLoadRequest(const RegistrationKernelLoadRequest&);
			void operator=(const RegistrationKernelLoadRequest&);
		};

		std::ostream& operator<<(std::ostream& os, const RegistrationKernelLoadRequest& request);

	} // end namespace io
} // end namespace map


#endif
