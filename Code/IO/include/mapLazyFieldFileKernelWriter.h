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

#ifndef __MAP_LAZY_FIELD_FILE_KERNEL_WRITER_H
#define __MAP_LAZY_FIELD_FILE_KERNEL_WRITER_H

#include "mapRegistrationKernelWriterBase.h"
#include "mapLazyRegistrationKernel.h"

namespace map
{
	namespace io
	{
		/*! @class LazyFieldFileKernelWriter
		* @brief Provider that is able to store lazy field based kernels that use a FieldByFileLoad functor.
		*
		* The writer always copies the file defined FieldByFileLoad functor to the new location defined by the current write operation.
    *
		* @sa FieldBasedRegistrationKernel
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class LazyFieldFileKernelWriter : public
			RegistrationKernelWriterBase<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef LazyFieldFileKernelWriter<VInputDimensions, VOutputDimensions>				Self;
			typedef RegistrationKernelWriterBase<VInputDimensions, VOutputDimensions>	Superclass;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(LazyFieldFileKernelWriter, RegistrationKernelWriterBase);
			itkNewMacro(Self);

			using KernelBaseType = typename Superclass::KernelBaseType;
			using KernelBasePointer = typename Superclass::KernelBasePointer;
			using RequestType = typename Superclass::RequestType;
			typedef core::LazyRegistrationKernel<VInputDimensions, VOutputDimensions> KernelType;

			/*! Uses the passed request data to check if the provider is able to provide the service for
			 * this request. Thus if the kernel is field based with a concrete vector field or expanding is
			* wanted anyway.
			 * @return Indicates if the provider offers the right solution.
			 * @retval true Provider can handle the request.
			 * @retval false Provider is not able to handle the request.*/
			virtual bool canHandleRequest(const RequestType& request) const;

			/*! Returns an ID of the provider as string. Calls getStaticProviderName().
			 * @return Service provider ID.*/
			virtual core::String getProviderName() const;

			/*! Returns an ID of the provider as string.
			 * @return Service provider ID.*/
			static core::String getStaticProviderName();

			/*! Returns an ID of the provider as string. May be equal to GetClassName(), but it may differ.
			 * @return Service provider ID.
			 * @remark It is a return by value, becaus it might be possible that the description is generated on line
			 * when calling this method.*/
			virtual core::String getDescription() const;

			/*! Generates the inverse kernel.
				 * Returns a structured element containing the matrix.
			* @eguarantee strong
			* @param [in] request Referenz to the request that contains the kernel and all relevant information for the storing process.
			* @return Smart pointer to structured date element containing the stored information.
				 */
			virtual structuredData::Element::Pointer storeKernel(const RequestType& request) const;

		protected:

			LazyFieldFileKernelWriter();
			virtual ~LazyFieldFileKernelWriter() {};

		private:
			LazyFieldFileKernelWriter(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapLazyFieldFileKernelWriter.tpp"
#endif

#endif
