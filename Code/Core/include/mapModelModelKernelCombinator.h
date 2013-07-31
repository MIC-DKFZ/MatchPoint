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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapModelModelKernelCombinator.h $
*/


#ifndef __MAP_MODEL_MODEL_KERNEL_COMBINATOR_H
#define __MAP_MODEL_MODEL_KERNEL_COMBINATOR_H

#include "mapRegistrationKernelCombinatorBase.h"
#include "mapModelBasedRegistrationKernel.h"

namespace map
{
	namespace core
	{
		/*! @class ModelModelKernelCombinator
		* @brief Combinator class that combines two transform model kernels to a new kernel.
		*
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the  first kernel.
		* @tparam VInterimDimensions Dimensions of the output space of the first kernel and the input space of the second.
		* @tparam VOutputDimensions Dimensions of the output space of the second kernel.
		*/
		template <unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
		class ModelModelKernelCombinator : public RegistrationKernelCombinatorBase< VInputDimensions, VInterimDimensions, VOutputDimensions >
		{
		public:
			/*! Standard class typedefs. */
			typedef ModelModelKernelCombinator< VInputDimensions, VInterimDimensions, VOutputDimensions >  Self;
			typedef RegistrationKernelCombinatorBase< VInputDimensions, VInterimDimensions, VOutputDimensions >	 Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			typedef typename Superclass::Kernel1BaseType								Kernel1BaseType;
			typedef typename Superclass::Kernel1BasePointer							Kernel1BasePointer;
			typedef typename Superclass::Kernel2BaseType								Kernel2BaseType;
			typedef typename Superclass::Kernel2BasePointer							Kernel2BasePointer;

			typedef typename Superclass::CombinedKernelBaseType					CombinedKernelBaseType;
			typedef typename Superclass::CombinedKernelBasePointer			CombinedKernelBasePointer;

			typedef typename Superclass::RequestType										RequestType;

			typedef typename Superclass::InputFieldRepresentationType		InputFieldRepresentationType;
			typedef typename Superclass::InterimFieldRepresentationType	InterimFieldRepresentationType;

			typedef typename Superclass::PaddingVectorType							PaddingVectorType;

			typedef ModelBasedRegistrationKernel<VInputDimensions, VInterimDimensions> Kernel1Type;
			typedef typename Kernel1Type::Pointer                        Kernel1Pointer;

			typedef ModelBasedRegistrationKernel<VInterimDimensions, VOutputDimensions>  Kernel2Type;
			typedef typename Kernel2Type::Pointer                        Kernel2Pointer;

			itkTypeMacro(ModelModelKernelCombinator, RegistrationKernelCombinatorBase);
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
				 */
			virtual CombinedKernelBasePointer combineKernels(const RequestType &request,
			                                                 const InputFieldRepresentationType *pInputFieldRepresentation,
			                                                 bool usePadding = false,
			                                                 const PaddingVectorType &paddingVector = PaddingVectorType(0.0)) const;

			/*! Uses the passed request data to check if the provider is able to provide the service for
			 * this request.
			 * @return Indicates if the provider offers the right solution.
			 * @retval true Provider can handle the request.
			 * @retval false Provider is not able to handle the request.*/
			virtual bool canHandleRequest(const RequestType &request) const;

			/*! Returns an ID of the provider as string. Calls getStaticProviderName().
			 * @return Service provider ID.*/
			virtual String getProviderName() const;

			/*! Returns an ID of the provider as string.
			 * @return Service provider ID.*/
			static String getStaticProviderName();

			/*! Returns an ID of the provider as string. May be equal to GetClassName(), but it may differ.
			 * @return Service provider ID.
			 * @remark It is a return by value, becaus it might be possible that the description is generated on line
			 * when calling this method.*/
			virtual String getDescription() const;

		protected:
			ModelModelKernelCombinator() {};
			virtual ~ModelModelKernelCombinator() {};

		private:
			ModelModelKernelCombinator(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapModelModelKernelCombinator.tpp"
#endif

#endif
