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

#ifndef __MAP_NULL_REGISTRATION_KERNEL_LOADER_H
#define __MAP_NULL_REGISTRATION_KERNEL_LOADER_H

#include "mapRegistrationKernelLoaderBase.h"
#include "mapNullRegistrationKernel.h"

namespace map
{
	namespace io
	{
		/*! @class NullRegistrationKernelLoader
		* @brief Provider that is able to load NullRegistrationKernels.
		*
		* @sa PreCachedRegistrationKernel
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class NullRegistrationKernelLoader : public RegistrationKernelLoaderBase
		{
		public:
			/*! Standard class typedefs. */
			typedef NullRegistrationKernelLoader<VInputDimensions, VOutputDimensions>				Self;
			using Superclass = RegistrationKernelLoaderBase;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(NullRegistrationKernelLoader, RegistrationKernelLoaderBase);
			itkNewMacro(Self);

			typedef core::RegistrationKernelBase<VInputDimensions, VOutputDimensions>	KernelBaseType;
			using KernelBasePointer = typename KernelBaseType::Pointer;
			using RequestType = typename Superclass::RequestType;
			typedef  core::NullRegistrationKernel<VInputDimensions, VOutputDimensions> KernelType;

			/*! Uses the passed request data to check if the provider is able to provide the service for
			 * this request. Thus if the kernel is model based and a matrix
			 * @return Indicates if the provider offers the right solution.
			 * @retval true Provider can handle the request.
			 * @retval false Provider is not able to handle the request.*/
			bool canHandleRequest(const RequestType& request) const override;

			/*! Returns an ID of the provider as string. Calls getStaticProviderName().
			 * @return Service provider ID.*/
			 core::String getProviderName() const override;

			/*! Returns an ID of the provider as string.
			 * @return Service provider ID.*/
			static  core::String getStaticProviderName();

			/*! Returns an ID of the provider as string. May be equal to GetClassName(), but it may differ.
			 * @return Service provider ID.
			 * @remark It is a return by value, becaus it might be possible that the description is generated on line
			 * when calling this method.*/
			 core::String getDescription() const override;

			/*! Loads kernel.
				 * Returns a smart pointer to the loaded kernel specified by the request.
			* The methods throws exceptions if the request is invalid.
				 * @eguarantee strong
				 * @param [in] request Reference to the request that contains the loadingh information
				 * @return Smart pointer to the loaded kernel.
				 * @pre request must be valid.
				 */
			GenericKernelPointer loadKernel(const RequestType& request) const override;

			/*! Adds a given generic kernel to the passed registration as inverse kernel.
				 * @eguarantee strong
			* @param [in] pKernel pointer to the kernel that should be added if the Pointer is null a fitting registration object will be created.
			* @param [in] pRegistration pointer to the registration that should receive the kernel
			* @pre pKernel must be valid and of correct dimensionality or NULL.
			* @pre pRegistration must be valid and of correct dimensionality.
				 */
			void addAsInverseKernel(GenericKernelType* pKernel,
											::map::core::RegistrationBase::Pointer& spRegistration) const override;

			/*! Adds a given generic kernel to the passed registration as direct kernel.
				 * @eguarantee strong
				 * @param [in] pKernel pointer to the kernel that should be added if the Pointer is null a fitting registration object will be created.
				 * @param [in] pRegistration pointer to the registration that should receive the kernel
				 * @pre pKernel must be valid and of correct dimensionality or NULL.
			* @pre pRegistration must be valid and of correct dimensionality.
				 */
			void addAsDirectKernel(GenericKernelType* pKernel,
										   core::RegistrationBase::Pointer& spRegistration) const override;

		protected:

			NullRegistrationKernelLoader();
			~NullRegistrationKernelLoader() override {};

		private:
			NullRegistrationKernelLoader(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapNullRegistrationKernelLoader.tpp"
#endif

#endif
