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


#ifndef __MAP_REGISTRATION_KERNEL_COMBINATOR_BASE_H
#define __MAP_REGISTRATION_KERNEL_COMBINATOR_BASE_H

#include "mapServiceProvider.h"
#include "mapRegistrationCombinationRequest.h"
#include "mapRegistrationKernelBase.h"
#include "mapRegistrationTopology.h"

namespace map
{
	namespace core
	{
		/*! @class RegistrationKernelCombinatorBase
		* @brief Base class for any instance in MatchPoint that provides the service of registration kernel combination.
		*
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the  first kernel.
		* @tparam VInterimDimensions Dimensions of the output space of the first kernel and the input space of the second.
		* @tparam VOutputDimensions Dimensions of the output space of the second kernel.
		*/
		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		class RegistrationKernelCombinatorBase : public
			services::ServiceProvider< RegistrationCombinationRequest< VInputDimensions, VInterimDimensions, VOutputDimensions> >
		{
		public:
			typedef RegistrationKernelBase<VInputDimensions, VInterimDimensions>			Kernel1BaseType;
			using Kernel1BasePointer = typename Kernel1BaseType::Pointer;
			typedef RegistrationKernelBase<VInterimDimensions, VOutputDimensions>		Kernel2BaseType;
			using Kernel2BasePointer = typename Kernel2BaseType::Pointer;

			typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions>			CombinedKernelBaseType;
			using CombinedKernelBasePointer = typename CombinedKernelBaseType::Pointer;

			typedef RegistrationCombinationRequest<VInputDimensions, VInterimDimensions, VOutputDimensions>
			RequestType;

			using InputFieldRepresentationType = FieldRepresentationDescriptor<VInputDimensions>;
			using InterimFieldRepresentationType = FieldRepresentationDescriptor<VInterimDimensions>;

			typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectMappingVectorType
			PaddingVectorType;

			itkStaticConstMacro(InputDimensions, unsigned int, VInputDimensions);
			itkStaticConstMacro(InterimDimensions, unsigned int, VInterimDimensions);
			itkStaticConstMacro(OutputDimensions, unsigned int, VOutputDimensions);

			/*! Standard class typedefs. */
			typedef RegistrationKernelCombinatorBase<VInputDimensions, VInterimDimensions, VOutputDimensions>
			Self;
			using Superclass = services::ServiceProvider<RequestType>;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(RegistrationKernelCombinatorBase, ServiceProvider);

			/*! Combines two kernel.
				 * Returns a smpart pointer to an kernel that realizes the combination of two registration kernel.
				 * @eguarantee strong
				 * @param [in] request Referenz to the request that contains the both kernels that should be combined
				 * @param [in] pInputFieldRepresentation Pointer to the field representation of the input space of the combined kernel.
			* Some combinators (any handling field kernels) may need this pointer not to be null as a precondition.
				 * @param [in] usePadding Indicicates how the recombinator and its functor should handel points that cannot be mapped
			* through both kernels (e.g. a point that is mapped by the first kernel outside of the supported region of the second
			* registration kernel). If the _usePadding is true, _paddingVector will be used as padding value in each of the mentioned
			* cases. If _usePadding value is false, than the combinator will throw an RepresentationException.
				 * @param [in] paddingVector Vector that should be used for padding, if usePadding is true.
				 * @return Smart pointer to the inverse kernel.
				 * @pre input representation must be coverd by the first kernel and the mapped input representation must be covered by the input
				 * representation of the second kernel.
				 */
			virtual CombinedKernelBasePointer combineKernels(const RequestType& request,
					const InputFieldRepresentationType* pInputFieldRepresentation,
					bool usePadding = false,
					const PaddingVectorType& paddingVector = PaddingVectorType(0)) const = 0;

		protected:

			/*! Methods invoked by itk::LightObject::Print().  */
			void PrintSelf(std::ostream& os, itk::Indent indent) const override;

			RegistrationKernelCombinatorBase();
			~RegistrationKernelCombinatorBase() override;

		private:
			RegistrationKernelCombinatorBase(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapRegistrationKernelCombinatorBase.tpp"
#endif

#endif
