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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapLazyFileFieldKernelLoader.h $
*/

#ifndef __MAP_LAZY_FILE_FIELD_KERNEL_LOADER_H
#define __MAP_LAZY_FILE_FIELD_KERNEL_LOADER_H

#include "mapFieldKernelLoaderBase.h"
#include "mapLazyRegistrationKernel.h"

namespace map
{
	namespace io
	{
		/*! @class LazyFileFieldKernelLoader
		* @brief Provider that is able to load expanded field kernels, but uses a lazy loading scheme (on demand via functor).
		*
		* @sa FieldBasedRegistrationKernels
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class LazyFileFieldKernelLoader : public FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef LazyFileFieldKernelLoader<VInputDimensions, VOutputDimensions>				Self;
			typedef FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>   Superclass;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(LazyFileFieldKernelLoader, FieldKernelLoaderBase);
			itkNewMacro(Self);

			typedef  core::RegistrationKernel<VInputDimensions, VOutputDimensions>	KernelBaseType;
			using KernelBasePointer = typename KernelBaseType::Pointer;
			using RequestType = typename Superclass::RequestType;

            using GenericKernelType = typename Superclass::GenericKernelType;
            using GenericKernelPointer = typename Superclass::GenericKernelPointer;

			/*! Uses the passed request data to check if the provider is able to provide the service for
			 * this request. Thus if the kernel is an expanded field kernel
			 * @return Indicates if the provider offers the right solution.
			 * @retval true Provider can handle the request.
			 * @retval false Provider is not able to handle the request.*/
			virtual bool canHandleRequest(const RequestType& request) const;

			/*! Returns an ID of the provider as string. Calls getStaticProviderName().
			 * @return Service provider ID.*/
			virtual  core::String getProviderName() const;

			/*! Returns an ID of the provider as string.
			 * @return Service provider ID.*/
			static  core::String getStaticProviderName();

			/*! Returns an ID of the provider as string. May be equal to GetClassName(), but it may differ.
			 * @return Service provider ID.
			 * @remark It is a return by value, because it might be possible that the description is generated on line
			 * when calling this method.*/
			virtual  core::String getDescription() const;

			/*! Loads kernel.
				 * Returns a smart pointer to the loaded kernel specified by the request.
			* The methods throws exceptions if the request is invalid.
				 * @eguarantee strong
				 * @param [in] request Reference to the request that contains the loading information
				 * @return Smart pointer to the loaded kernel.
				 * @pre request must be valid.
				 */
			virtual GenericKernelPointer loadKernel(const RequestType& request) const;

		protected:

			LazyFileFieldKernelLoader();
			virtual ~LazyFileFieldKernelLoader() {};

		private:
			LazyFileFieldKernelLoader(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapLazyFileFieldKernelLoader.tpp"
#endif

#endif
