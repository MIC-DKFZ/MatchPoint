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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapInvertingFieldKernelLoader.h $
*/

#ifndef __MAP_INVERTING_FIELD_KERNEL_LOADER_H
#define __MAP_INVERTING_FIELD_KERNEL_LOADER_H

#include "mapRegistrationKernelLoaderBase.h"
#include "mapInvertingFieldBasedRegistrationKernel.h"

namespace map
{
	namespace io
	{
		/*! @class InvertingFieldKernelLoader
		* @brief Provider that is able to load InvertingFiledBasedKernels.
		*
    * The "loading" is done by using the related kernel of the loader request and inferting that kernel
    * by using the InverseRegistrationKernelGenerator.
    *
		* @sa FieldBasedRegistrationKernels
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class InvertingFieldKernelLoader : public RegistrationKernelLoaderBase
		{
		public:
			/*! Standard class typedefs. */
			typedef InvertingFieldKernelLoader<VInputDimensions, VOutputDimensions>				Self;
			typedef RegistrationKernelLoaderBase   Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(InvertingFieldKernelLoader, RegistrationKernelLoaderBase);
			itkNewMacro(Self);

			typedef  core::InvertingFieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions>	KernelBaseType;
			typedef typename KernelBaseType::Pointer	KernelBasePointer;
			typedef typename Superclass::RequestType	RequestType;

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

			/*! Adds a given generic kernel to the passed registration as inverse kernel.
				 * @eguarantee strong
			* @param [in] pKernel pointer to the kernel that should be added if the Pointer is null a fitting registration object will be created.
			* @param [in] pRegistration pointer to the registration that should receive the kernel
			* @pre pKernel must be valid and of correct dimensionality or NULL.
			* @pre pRegistration must be valid and of correct dimensionality.
				 */
			virtual void addAsInverseKernel(GenericKernelType* pKernel,
											core::RegistrationBase::Pointer& spRegistration) const;

			/*! Adds a given generic kernel to the passed registration as direct kernel.
				 * @eguarantee strong
				 * @param [in] pKernel pointer to the kernel that should be added if the Pointer is null a fitting registration object will be created.
				 * @param [in] pRegistration pointer to the registration that should receive the kernel
				 * @pre pKernel must be valid and of correct dimensionality or NULL.
			* @pre pRegistration must be valid and of correct dimensionality.
				 */
			virtual void addAsDirectKernel(GenericKernelType* pKernel,
										   core::RegistrationBase::Pointer& spRegistration) const;

		protected:

			InvertingFieldKernelLoader();
			virtual ~InvertingFieldKernelLoader() {};

		private:
			InvertingFieldKernelLoader(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapInvertingFieldKernelLoader.tpp"
#endif

#endif
