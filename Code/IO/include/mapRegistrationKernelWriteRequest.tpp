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

#ifndef __MAP_REGISTRATION_KERNEL_WRITE_REQUEST_TPP
#define __MAP_REGISTRATION_KERNEL_WRITE_REQUEST_TPP

#include "mapRegistrationKernelWriteRequest.h"

namespace map
{
	namespace io
	{

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		RegistrationKernelWriteRequest<VInputDimensions, VOutputDimensions>::
		RegistrationKernelWriteRequest(const KernelBaseType* pKernel, const core::String& path,
									   const core::String& name, bool expandLazyKernels,
									   const ComplementaryKernelBaseType* pComplementaryKernel):
			_spKernel(pKernel), _path(path), _name(name), _expandLazyKernels(expandLazyKernels),
			_spComplementaryKernel(pComplementaryKernel)
		{
			assert(pKernel);
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		RegistrationKernelWriteRequest<VInputDimensions, VOutputDimensions>::
		RegistrationKernelWriteRequest(const KernelBaseType& kernel, core::String  path,
									   core::String  name, bool expandLazyKernels,
									   const ComplementaryKernelBaseType* pComplementaryKernel):
			_spKernel(&kernel), _path(std::move(path)), _name(std::move(name)), _expandLazyKernels(expandLazyKernels),
			_spComplementaryKernel(pComplementaryKernel)
		{
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		RegistrationKernelWriteRequest<VInputDimensions, VOutputDimensions>::
		~RegistrationKernelWriteRequest()
		{
			// intentionally left blank
		}


		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		RegistrationKernelWriteRequest<VInputDimensions, VOutputDimensions>::
		RegistrationKernelWriteRequest(const RegistrationKernelWriteRequest& req):
			_spKernel(req._spKernel), _path(req._path), _name(req._name),
			_expandLazyKernels(req._expandLazyKernels)
		{
			assert(_spKernel.IsNotNull());
		}

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		RegistrationKernelWriteRequest<VInputDimensions, VOutputDimensions>::
		operator=(const RegistrationKernelWriteRequest& req)
		{
			if (&req != this)
			{
				_spKernel = req._spKernel;
				_path = req._path;
				_name = req._name;
				_expandLazyKernels = req._expandLazyKernels;
				_spComplementaryKernel = req._spComplementaryKernel;
			}
		}


	} // end namespace io
} // end namespace map

#endif
