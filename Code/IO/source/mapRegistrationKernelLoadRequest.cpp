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

#include "mapRegistrationKernelLoadRequest.h"
#include <assert.h>

namespace map
{
	namespace io
	{

		RegistrationKernelLoadRequest::
		RegistrationKernelLoadRequest(const structuredData::Element* pKernelDescriptor,
									  bool preferLazyLoading,
                    const core::DimensionlessRegistrationKernelBase* pComplementaryKernel): _spKernelDescriptor(pKernelDescriptor),
			_preferLazyLoading(preferLazyLoading),
      _spComplementaryKernel(pComplementaryKernel)
		{
			assert(pKernelDescriptor);
		};

		RegistrationKernelLoadRequest::
		~RegistrationKernelLoadRequest()
		{
		};

		RegistrationKernelLoadRequest::
		RegistrationKernelLoadRequest(const RegistrationKernelLoadRequest& request): _spKernelDescriptor(
				request._spKernelDescriptor), _preferLazyLoading(request._preferLazyLoading)
		{
			assert(_spKernelDescriptor.IsNotNull());
		};

		void
		RegistrationKernelLoadRequest::
		operator=(const RegistrationKernelLoadRequest& request)
		{
			if (&request != this)
			{
				_spKernelDescriptor = request._spKernelDescriptor;
				_preferLazyLoading = request._preferLazyLoading;
        _spComplementaryKernel = request._spComplementaryKernel;
			}
		};

		std::ostream& operator<<(std::ostream& os, const RegistrationKernelLoadRequest& request)
		{
			os << "Data: " << request._spKernelDescriptor << std::endl;
			os << "Lazy loading: " << request._preferLazyLoading << std::endl;
      os << "Complementary kernel: " << request._spComplementaryKernel << std::endl;
			return os;
		};

	} // end namespace io
} // end namespace map
