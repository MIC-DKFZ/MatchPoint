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

#ifndef __MAP_REGISTRATION_KERNEL_INVERTER_BASE_H
#define __MAP_REGISTRATION_KERNEL_INVERTER_BASE_H

#include "mapServiceProvider.h"
#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace core
	{
		/*! @class RegistrationKernelInverterBase
		* @brief Base class for any instance in MatchPoint that provides kernel inversion services
		*
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class RegistrationKernelInverterBase : public
			services::ServiceProvider< RegistrationKernelBase<VInputDimensions, VOutputDimensions> >
		{
		public:
			typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions>	KernelBaseType;
			using KernelBasePointer = typename KernelBaseType::Pointer;
			typedef RegistrationKernelBase<VOutputDimensions, VInputDimensions>	InverseKernelBaseType;
			using InverseKernelBasePointer = typename InverseKernelBaseType::Pointer;

			using FieldRepresentationType = FieldRepresentationDescriptor<VInputDimensions>;
			using InverseFieldRepresentationType = FieldRepresentationDescriptor<VOutputDimensions>;

			using RequestType = KernelBaseType;

			using NullPointType = typename InverseKernelBaseType::OutputPointType;

			/*! Standard class typedefs. */
			typedef RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions>  Self;
			using Superclass = services::ServiceProvider<RequestType>;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(RegistrationKernelInverterBase, ServiceProvider);

			/*! Generates the inverse kernel.
				 * Returns a smpart pointer to an inverted version of the kernel.
				 * @eguarantee strong
				 * @param [in] request Referenz to the kernel that should be inverted
				 * @param [in] pFieldRepresentation Pointer to the field representation of the kernel.
				 * @param [in] pInverseFieldRepresentation Pointer to the field representation of the inverse kernel.
				 * @return Smart pointer to the inverse kernel.
				 * @pre The inverter service provider may require the field representation, depending on the kernel.
				 * e.g. if the kernel cannot be inverted analyticaly the inverse field representation descriptor is
				 * needed in order to generate a prober field for the inverse kernel.
				 * To avoid any exceptions always provide the field representation descriptors unless you are sure they
				 * won't be needed.
				 * The kernel must be the right type for a concrete inverter. Thus only call this method for kernels for wich
				 * canHandleRequest returned true.
				 * @post If the method returns with no exception, there is always an inverse kernel (smart pointer is not NULL)
				 * @remark This function might cause an exception/assertion if the responsible service provider needs
				 * a missing field representation descriptor. Also if no suitable provider is available an exception will be thrown.
				 */
			virtual InverseKernelBasePointer invertKernel(const KernelBaseType& kernel,
			        const FieldRepresentationType* pFieldRepresentation,
			        const InverseFieldRepresentationType* pInverseFieldRepresentation, bool useNullPoint = false,
			        NullPointType nullPoint = NullPointType(itk::NumericTraits< ::map::core::continuous::ScalarType>::NonpositiveMin()))
			const = 0;

		protected:
			RegistrationKernelInverterBase()
			{
			};

			virtual ~RegistrationKernelInverterBase() {};

		private:
			RegistrationKernelInverterBase(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#endif
