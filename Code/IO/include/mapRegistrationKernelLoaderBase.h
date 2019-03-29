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


#ifndef __MAP_REGISTRATION_KERNEL_LOADER_BASE_H
#define __MAP_REGISTRATION_KERNEL_LOADER_BASE_H

#include "mapServiceProvider.h"
#include "mapRegistrationKernelLoadRequest.h"
#include "mapRegistrationKernelBase.h"
#include "mapRegistrationTopology.h"
#include "mapRegistrationBase.h"
#include "mapMAPIOExports.h"

namespace map
{
	namespace io
	{
		/*! @class RegistrationKernelLoaderBase
		* @brief Base class for any instance in MatchPoint that provides the service of registration kernel loading.
		*
		* @ingroup RegOperation
		*/
		class MAPIO_EXPORT RegistrationKernelLoaderBase : public
			::map::core::services::ServiceProvider< RegistrationKernelLoadRequest >
		{
		public:
			using RequestType = RegistrationKernelLoadRequest;

			/*! Standard class typedefs. */
			using Self = RegistrationKernelLoaderBase;
			using Superclass = core::services::ServiceProvider<RequestType>;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			using GenericKernelType = itk::Object;
			using GenericKernelPointer = itk::Object::Pointer;

			itkTypeMacro(RegistrationKernelLoaderBase, ServiceProvider);

			/*! Loads kernel.
				 * Returns a smart pointer to the loaded kernel specified by the request.
			* The methods throws exceptions if the request is invalid.
				 * @eguarantee strong
				 * @param [in] request Reference to the request that contains the loadingh information
				 * @param [in] preferLazzyLoading Indicates if the kernel should use lazy loading if possible (e.g. a vector field is not directly
			* loaded. Only a functor is used that references the file and loads the field on demand)
				 * @return Smart pointer to the loaded kernel.
				 * @pre request must be valid.
				 */
			virtual GenericKernelPointer loadKernel(const RequestType& request) const = 0;

			/*! Adds a given generic kernel to the passed registration as inverse kernel.
				 * @eguarantee strong
			* @param [in] pKernel pointer to the kernel that should be added if the Pointer is null a fitting registration object will be created.
			* @param [in] pRegistration pointer to the registration that should receive the kernel
			* @pre pKernel must be valid and of correct dimensionality or NULL.
			* @pre pRegistration must be valid and of correct dimensionality.
				 */
			virtual void addAsInverseKernel(GenericKernelType* pKernel,
											::map::core::RegistrationBase::Pointer& spRegistration) const = 0;

			/*! Adds a given generic kernel to the passed registration as direct kernel.
				 * @eguarantee strong
				 * @param [in] pKernel pointer to the kernel that should be added if the Pointer is null a fitting registration object will be created.
				 * @param [in] pRegistration pointer to the registration that should receive the kernel
				 * @pre pKernel must be valid and of correct dimensionality or NULL.
			* @pre pRegistration must be valid and of correct dimensionality.
				 */
			virtual void addAsDirectKernel(GenericKernelType* pKernel,
										   core::RegistrationBase::Pointer& spRegistration) const = 0;

		protected:

			/*! Methods invoked by itk::LightObject::Print().  */
			void PrintSelf(std::ostream& os, itk::Indent indent) const override;

			RegistrationKernelLoaderBase();
			~RegistrationKernelLoaderBase() override;

		private:
			RegistrationKernelLoaderBase(const Self&) = delete;  //purposely not implemented
			void operator=(const Self&) = delete;  //purposely not implemented
		};

	} // end namespace io
} // end namespace map

#endif
