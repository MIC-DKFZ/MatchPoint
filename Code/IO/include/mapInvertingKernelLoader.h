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

#ifndef __MAP_INVERTING_FIELD_KERNEL_LOADER_H
#define __MAP_INVERTING_FIELD_KERNEL_LOADER_H

#include "mapFieldKernelLoaderBase.h"
#include "mapInvertingRegistrationKernel.h"

namespace map
{
	namespace io
	{
		/*! @class InvertingKernelLoader
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
		class InvertingKernelLoader : public FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef InvertingKernelLoader<VInputDimensions, VOutputDimensions>				Self;
			typedef FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>   Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(InvertingKernelLoader, FieldKernelLoaderBase);
			itkNewMacro(Self);

			typedef  core::InvertingRegistrationKernel<VInputDimensions, VOutputDimensions>
			KernelBaseType;
			typedef typename KernelBaseType::Pointer	KernelBasePointer;
			typedef typename Superclass::RequestType	RequestType;

            typedef typename Superclass::GenericKernelType       GenericKernelType;
            typedef typename Superclass::GenericKernelPointer    GenericKernelPointer;

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

			InvertingKernelLoader();
			virtual ~InvertingKernelLoader() {};

		private:
			InvertingKernelLoader(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapInvertingKernelLoader.tpp"
#endif

#endif
