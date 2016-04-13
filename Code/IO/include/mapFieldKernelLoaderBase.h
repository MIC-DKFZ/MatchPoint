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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapFieldKernelLoaderBase.h $
*/

#ifndef __MAP_FIELD_KERNEL_LOADER_BASE_H
#define __MAP_FIELD_KERNEL_LOADER_BASE_H

#include "mapRegistrationKernelLoaderBase.h"
#include "mapRegistrationKernel.h"

namespace map
{
	namespace io
	{
		/*! @class FieldKernelLoaderBase
		* @brief Base class for provider that are able to load stored vector fields as kernels.
		*
		* @sa FieldBasedRegistrationKernels
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class FieldKernelLoaderBase : public RegistrationKernelLoaderBase
		{
		public:
			/*! Standard class typedefs. */
			typedef FieldKernelLoaderBase<VInputDimensions, VOutputDimensions>				Self;
			typedef RegistrationKernelLoaderBase   Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(FieldKernelLoaderBase, RegistrationKernelLoaderBase);

			typedef  core::RegistrationKernel<VInputDimensions, VOutputDimensions>	KernelBaseType;
			typedef typename KernelBaseType::Pointer	KernelBasePointer;
			typedef typename Superclass::RequestType	RequestType;

			/*! Uses the passed request data to check if the provider is able to provide the service for
			 * this request. This implementation only checks for correct dimensionality. The rest must be
			 * checked by derived classes.
			 * @return Indicates if the provider offers the right solution.
			 * @retval true Provider can handle the request.
			 * @retval false Provider is not able to handle the request.*/
			virtual bool canHandleRequest(const RequestType& request) const;

			/*! Adds a given generic kernel to the passed registration as inverse kernel.
				 * @eguarantee strong
			* @param [in] pKernel pointer to the kernel that should be added if the Pointer is null a fitting registration object will be created.
			* @param [in] pRegistration pointer to the registration that should receive the kernel
			* @pre pKernel must be valid and of correct dimensionality or NULL.
			* @pre pRegistration must be valid and of correct dimensionality.
				 */
			virtual void addAsInverseKernel(GenericKernelType* pKernel,
											::map::core::RegistrationBase::Pointer& spRegistration) const;

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

			/** Returns the file path of the field defined in the request.
			 * @eguarantee strong*/
			::map::core::String getFilePath(const RequestType& request) const;
			
			/** Checks the passed request if a null vector is defined and returns its value.
			 * @param nullPoint Values of the null vector. Valid if method returns true. If it returns false, no vector was defined and the value is 0.
			 * @result true if a null vector exists.
			 * @eguarantee strong*/
      bool hasNullPoint(const RequestType& request, typename KernelBaseType::OutputPointType& nullPoint) const;
			
			FieldKernelLoaderBase();
			virtual ~FieldKernelLoaderBase() {};

		private:
			FieldKernelLoaderBase(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldKernelLoaderBase.tpp"
#endif

#endif
