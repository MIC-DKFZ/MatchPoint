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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/IO/include/mapRegistrationKernelWriterBase.h $
*/


#ifndef __MAP_REGISTRATION_KERNEL_WRITER_BASE_H
#define __MAP_REGISTRATION_KERNEL_WRITER_BASE_H

#include "mapServiceProvider.h"
#include "mapRegistrationKernelWriteRequest.h"
#include "mapRegistrationKernelBase.h"
#include "mapSDElement.h"

namespace map
{
	namespace io
	{
		/*! @class RegistrationKernelWriterBase
		* @brief Base class for any instance in MatchPoint that provides the service of registration kernel combination.
		*
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the  first kernel.
		* @tparam VInterimDimensions Dimensions of the output space of the first kernel and the input space of the second.
		* @tparam VOutputDimensions Dimensions of the output space of the second kernel.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class RegistrationKernelWriterBase : public core::services::ServiceProvider< RegistrationKernelWriteRequest< VInputDimensions, VOutputDimensions> >
		{
		public:
			typedef core::RegistrationKernelBase<VInputDimensions, VOutputDimensions>			KernelBaseType;
			typedef typename KernelBaseType::Pointer																KernelBasePointer;

			typedef RegistrationKernelWriteRequest<VInputDimensions, VOutputDimensions> RequestType;

			typedef core::FieldRepresentationDescriptor<VInputDimensions>							InputFieldRepresentationType;


			itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
			itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

			/*! Standard class typedefs. */
			typedef RegistrationKernelWriterBase<VInputDimensions, VOutputDimensions>  Self;
			typedef core::services::ServiceProvider<RequestType>	 Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(RegistrationKernelWriterBase, ServiceProvider);

			/*! Combines two kernel.
				 * Returns a smart pointer to a structured data element that containes all information of the stored kernel.
			* Depending on the kernel, associated data may have allready stored in the file system to the location specified
			* by the request (e.g. a Field kernel storing the field as vector image and returning the information in the
			* structuredData::Element.).
				 * @eguarantee strong
				 * @param [in] request Referenz to the request that contains the kernel and all relevant information for the storing process.
				 * @return Smart pointer to structured date element containing the stored information.
				 */
			virtual structuredData::Element::Pointer storeKernel(const RequestType &request) const = 0;

		protected:

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;

			RegistrationKernelWriterBase();
			virtual ~RegistrationKernelWriterBase();

		private:
			RegistrationKernelWriterBase(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapRegistrationKernelWriterBase.tpp"
#endif

#endif
