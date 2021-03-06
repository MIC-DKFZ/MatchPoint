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


#ifndef __MAP_PRE_CACHED_KERNEL_COMBINATOR_H
#define __MAP_PRE_CACHED_KERNEL_COMBINATOR_H

#include "mapRegistrationKernelCombinatorBase.h"
#include "mapPreCachedRegistrationKernel.h"

namespace map
{
	namespace core
	{
		/*! @class PreCachedKernelCombinator
		* @brief Combinator class that combines two PreCached kernels to a new kernel.
		* If the Kernels can be decomposed to a matrix transform, the will be directly composed to
    * a new matrix transform. In all other cases they will be packed into a aggregating transform
    * wrapper.
    * @remark Currently it can only handle combinations of same dimensionality
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the  first kernel.
		* @tparam VInterimDimensions Dimensions of the output space of the first kernel and the input space of the second.
		* @tparam VOutputDimensions Dimensions of the output space of the second kernel.
		*/
		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		class PreCachedKernelCombinator : public
			RegistrationKernelCombinatorBase< VInputDimensions, VInterimDimensions, VOutputDimensions >
		{
		public:
			/*! Standard class typedefs. */
			typedef PreCachedKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >  Self;
			typedef RegistrationKernelCombinatorBase< VInputDimensions, VInterimDimensions, VOutputDimensions >
			Superclass;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			using Kernel1BaseType = typename Superclass::Kernel1BaseType;
			using Kernel1BasePointer = typename Superclass::Kernel1BasePointer;
			using Kernel2BaseType = typename Superclass::Kernel2BaseType;
			using Kernel2BasePointer = typename Superclass::Kernel2BasePointer;

			using CombinedKernelBaseType = typename Superclass::CombinedKernelBaseType;
			using CombinedKernelBasePointer = typename Superclass::CombinedKernelBasePointer;

			using RequestType = typename Superclass::RequestType;

			using InputFieldRepresentationType = typename Superclass::InputFieldRepresentationType;
			using InterimFieldRepresentationType = typename Superclass::InterimFieldRepresentationType;

			using PaddingVectorType = typename Superclass::PaddingVectorType;

			typedef PreCachedRegistrationKernel<VInputDimensions, VInterimDimensions> Kernel1Type;
			using Kernel1Pointer = typename Kernel1Type::Pointer;

			typedef PreCachedRegistrationKernel<VInterimDimensions, VOutputDimensions>  Kernel2Type;
			using Kernel2Pointer = typename Kernel2Type::Pointer;

			itkTypeMacro(PreCachedKernelCombinator, RegistrationKernelCombinatorBase);
			itkNewMacro(Self);

			/*! Combines two kernel.
				 * Returns a smpart pointer to an kernel that realizes the combination of two registration kernel.
				 * @eguarantee strong
				 * @param [in] request Referenz to the request that contains the both kernels that should be combined
				 * @param [in] pInputFieldRepresentation Pointer to the field representation of the input space of the combined kernel; may be null.
				 * @param [in] usePadding Indicicates how the recombinator and its functor should handel points that cannot be mapped
			* through both kernels (e.g. a point that is mapped by the first kernel outside of the supported region of the second
			* registration kernel). If the _usePadding is true, _paddingVector will be used as padding value in each of the mentioned
			* cases. If _usePadding value is false, than the combinator will throw an RepresentationException.
				 * @param [in] paddingVector Vector that should be used for padding, if usePadding is true.
				 * @return Smart pointer to the inverse kernel.
				 * @pre input representation must be coverd by the first kernel and the mapped input representation must be covered by the input
				 * representation of the second kernel.
				 * @pre in its current implementation matrix combination is only possible when input, interim and output dimension are equal.
				 */
			CombinedKernelBasePointer combineKernels(const RequestType& request,
					const InputFieldRepresentationType* pInputFieldRepresentation,
					bool usePadding = false,
					const PaddingVectorType& paddingVector = PaddingVectorType(0.0)) const override;

			/*! Uses the passed request data to check if the provider is able to provide the service for
			 * this request.
			 * @return Indicates if the provider offers the right solution.
			 * @retval true Provider can handle the request.
			 * @retval false Provider is not able to handle the request.*/
			bool canHandleRequest(const RequestType& request) const override;

			/*! Returns an ID of the provider as string. Calls getStaticProviderName().
			 * @return Service provider ID.*/
			String getProviderName() const override;

			/*! Returns an ID of the provider as string.
			 * @return Service provider ID.*/
			static String getStaticProviderName();

			/*! Returns an ID of the provider as string. May be equal to GetClassName(), but it may differ.
			 * @return Service provider ID.
			 * @remark It is a return by value, becaus it might be possible that the description is generated on line
			 * when calling this method.*/
			String getDescription() const override;

		protected:
			PreCachedKernelCombinator() {};
			~PreCachedKernelCombinator() override {};

			/* Member tries to combine the given kernels as matrices and generate a new matrix
			 * based combined kernel. This will only be successfull if both support matrix
			 * decomposition.
			 * @return Null if kernels cannot be combined as matrices. Otherwise it returns the pointer
			   to the combination result.*/
			CombinedKernelBasePointer combineAsMatrixKernels(const Kernel1Type* kernel1,
					const Kernel2Type* kernel2) const;

		private:
			PreCachedKernelCombinator(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapPreCachedKernelCombinator.tpp"
#endif

#endif
