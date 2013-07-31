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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/include/mapRegistrationKernelWriteRequest.h $
*/

#ifndef __MAP_REGISTRATION_KERNEL_WRITE_REQUEST_H
#define __MAP_REGISTRATION_KERNEL_WRITE_REQUEST_H

#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace io
	{
		/*! @class RegistrationKernelWriteRequest
		* @brief Request class used by RegistrationKernelWriterBase / RegistrationFileWriter.
		*
		* This class is used as request type for the provider stack of RegistrationCombinator
		* @ingroup RegOperation
		* @sa RegistrationFileWriter
			* @tparam VInputDimensions Dimensions of the input space of the  first kernel.
			* @tparam VOutputDimensions Dimensions of the output space of the second kernel.
			*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class RegistrationKernelWriteRequest
		{
		public:
			typedef core::RegistrationKernelBase<VInputDimensions, VOutputDimensions> KernelBaseType;
			typedef typename KernelBaseType::ConstPointer KernelBaseConstPointer;

			/*! Kernel that should be stored with this request*/
			KernelBaseConstPointer _spKernel;

			/*! Path to where the kernel is going to be stored and additional data
			 *(e.g. image of the deformation field) should be stored).*/
			core::String _path;
			/*! "Project name" for the write operation which can be used to generate i.a. file names
			 * if needed*/
			core::String _name;

			/*! Determines if lazy kernels that have not been processed should be stored with there generation functors (false)
			 * or should be generated and stored with the actual kernel data (true). Default is true.*/
			bool _expandLazyKernels;

			/*! Constructor
			 * \pre pKernel1 and pKernel2 must not be NULL*/
			RegistrationKernelWriteRequest(const KernelBaseType *pKernel, const core::String &path, const core::String &name, bool expandLazyKernels);
			RegistrationKernelWriteRequest(const KernelBaseType &kernel, const core::String &path, const core::String &name, bool expandLazyKernels);
			~RegistrationKernelWriteRequest();

			RegistrationKernelWriteRequest(const RegistrationKernelWriteRequest &);
			void operator=(const RegistrationKernelWriteRequest &);
		};

		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		std::ostream &operator<<(std::ostream &os, const RegistrationKernelWriteRequest<VInputDimensions, VOutputDimensions> &request)
		{
			os << "Kernel: " << request._spKernel << std::endl;
			os << "Path: " << request._path << std::endl;
			os << "Name: " << request._name << std::endl;
			os << "ExpandLazyKernels: " << request._expandLazyKernels << std::endl;
			return os;
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapRegistrationKernelWriteRequest.tpp"
#endif

#endif
