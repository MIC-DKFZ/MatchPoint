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

#ifndef __MAP_INVERSE_REGISTRATION_KERNEL_GENERATOR_H
#define __MAP_INVERSE_REGISTRATION_KERNEL_GENERATOR_H

#include "mapStaticServiceStack.h"
#include "mapRegistrationKernelInverterBase.h"
#include "mapKernelInverterLoadPolicy.h"

#include "itkObject.h"

namespace map
{
	namespace core
	{
		/*! @class InverseRegistrationKernelGenerator
		* @brief Class generates inverse kernels for a passed registration kernel.
		*
		* This class is used by registration algorithms to establish the inverse counterpart
		* of the registration kernel determined by the algorithm, thus to establish a fully
		* functional Registration instance.\n
		* To invert the kernel the class uses a static service stack populated with
		* RegistrationKernelInverters. You can change the stack content by the static
		* class methods of the member typedef InverterStackType.
		*
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class InverseRegistrationKernelGenerator: public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			typedef InverseRegistrationKernelGenerator<VInputDimensions, VOutputDimensions>  Self;
			using Superclass = itk::Object;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(InverseRegistrationKernelGenerator, itk::Object);
			itkNewMacro(Self);

			typedef RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions> InverterBaseType;
			using KernelBaseType = typename InverterBaseType::KernelBaseType;
			using KernelBasePointer = typename KernelBaseType::Pointer;
			using InverseKernelBaseType = typename InverterBaseType::InverseKernelBaseType;
			using InverseKernelBasePointer = typename InverseKernelBaseType::Pointer;

			using FieldRepresentationType = typename InverterBaseType::FieldRepresentationType;
			using InverseFieldRepresentationType = typename InverterBaseType::InverseFieldRepresentationType;

      using NullPointType = typename InverseKernelBaseType::OutputPointType;

		protected:
			typedef services::ServiceStack<InverterBaseType, KernelInverterLoadPolicy<VInputDimensions, VOutputDimensions> >
			ConcreteInverterStackType;
		public:
			using InverterStackType = services::StaticServiceStack<ConcreteInverterStackType>;

			/*! Generates an inverse kernel by requesting a responsible service provider from InverterStackType.
				 * Returns a smart pointer to an inverted version of the kernel.
				 * @eguarantee strong
				 * @param [in] request reference to the kernel that should be inverted
				 * @param [in] pInverseFieldRepresentation Pointer to the field representation of the input space of the inverse kernel.
				 * @return Smart pointer to the inverse kernel.
				 * @pre The inverter service provider may require one or both field representations, depending on the kernel.
				 * e.g. if the kernel cannot be inverted analytically the inverse field representation descriptor is
				 * needed in order to generate a proper field for the inverse kernel.
				 * To avoid any exceptions always provide the field representation descriptors unless you are sure they
				 * won't be needed.
			* @post If the method returns with no exception, there is always an inverse kernel (smart pointer is not NULL)
				 * @remark This function calls the protected overload version. It assumes that the largest possible representation of kernel
			* can be used as pFieldRepresentation.\n This function might cause an exception/assertion if the responsible service provider needs
				 * a missing field representation descriptor. Also if no suitable provider is available an exception will be thrown.
				 */
			InverseKernelBasePointer generateInverse(const KernelBaseType& kernel,
					const InverseFieldRepresentationType* pInverseFieldRepresentation) const;

      mapSetVarMacro(NullPoint, NullPointType, _nullPoint);
      mapGetConstVarMacro(NullPoint, NullPointType, _nullPoint);
      mapSetVarMacro(NullPointUsage, bool, _useNullPoint);
      mapGetConstVarMacro(NullPointUsage, bool, _useNullPoint);

		protected:
			/*! Generates an inverse kernel by requesting a responsible service provider from InverterStackType.
				 * Returns a smart pointer to an inverted version of the kernel.
				 * @eguarantee strong
				 * @param [in] request Reference to the kernel that should be inverted
				 * @param [in] pFieldRepresentation Pointer to the field representation of the input space of the kernel that should be inverted.
				 * @param [in] pInverseFieldRepresentation Pointer to the field representation of the input space of the inverse kernel.
				 * @return Smart pointer to the inverse kernel.
				 * @pre The inverter service provider may require one or both field representations, depending on the kernel.
				 * e.g. if the kernel cannot be inverted analytically the inverse field representation descriptor is
				 * needed in order to generate a proper field for the inverse kernel.
				 * To avoid any exceptions always provide the field representation descriptors unless you are sure they
				 * won't be needed.
			* @todo It should be rechecked if this version is really needed or if the explicit passing of pFieldRepresentation is
			* unnecessary because the kernel can offer a largest possible representation description of the same space.
				 * @post If the method returns with no exception, there is always an inverse kernel (smart pointer is not NULL)
				 * @remark This function might cause an exception/assertion if the responsible service provider needs
				 * a missing field representation descriptor. Also if no suitable provider is available an exception will be thrown.
				 */
			InverseKernelBasePointer generateInverse(const KernelBaseType& kernel,
					const FieldRepresentationType* pFieldRepresentation,
					const InverseFieldRepresentationType* pInverseFieldRepresentation) const;


			InverseRegistrationKernelGenerator();
			~InverseRegistrationKernelGenerator() override;

      NullPointType _nullPoint;
      bool _useNullPoint;

		private:
			InverseRegistrationKernelGenerator(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapInverseRegistrationKernelGenerator.tpp"
#endif

#endif
