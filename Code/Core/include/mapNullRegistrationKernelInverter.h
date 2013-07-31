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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapNullRegistrationKernelInverter.h $
*/

#ifndef __MAP_NULL_REGISTRATION_KERNEL_INVERTER_H
#define __MAP_NULL_REGISTRATION_KERNEL_INVERTER_H

#include "mapRegistrationKernelInverterBase.h"
#include "mapNullRegistrationKernel.h"

namespace map
{
	namespace core
	{
		/*! @class NullRegistrationKernelInverter
		* @brief Provider that is able to invert a NullRegistrationKernel.
		*
		* A NullRegistrationKernel will always result in a NullRegistrationKernel if inverted.
		*
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class NullRegistrationKernelInverter : public RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef NullRegistrationKernelInverter<VInputDimensions, VOutputDimensions>				Self;
			typedef RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions>	Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(NullRegistrationKernelInverter, RegistrationKernelInverterBase);
			itkNewMacro(Self);

			typedef typename Superclass::KernelBaseType	KernelBaseType;
			typedef typename Superclass::KernelBasePointer	KernelBasePointer;
			typedef typename Superclass::InverseKernelBaseType	InverseKernelBaseType;
			typedef typename Superclass::InverseKernelBasePointer	InverseKernelBasePointer;
			typedef typename Superclass::FieldRepresentationType	FieldRepresentationType;
			typedef typename Superclass::InverseFieldRepresentationType	InverseFieldRepresentationType;
			typedef typename Superclass::RequestType	RequestType;
			typedef NullRegistrationKernel<VInputDimensions, VOutputDimensions> KernelType;

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

			/*! Generates the inverse kernel.
				 * Returns a smpart pointer to an inverted version of the kernel.
				 * @eguarantee strong
				 * @param [in] request Referenz to the kernel that should be inverted
				 * @param [in] pFieldRepresentation Pointer to the field representation of the kernel,
				 * may be null if no representation is defined.
				 * @param [in] pInverseFieldRepresentation Pointer to the field representation of the inverse kernel,
				 * may not be NULL, if the transform model cannot be inverted analyticaly.
				 * @return Smart pointer to the inverse kernel.
				 * @pre The inverter service provider may require the inverse field representation
				 * @post If the method returns with no exception, there is always an inverse kernel (smart pointer is not NULL)
				 * @remark This function might cause an exception/assertion if the responsible service provider needs
				 * pInverseFieldRepresentation not to be NULL but it is.
				 */
			virtual InverseKernelBasePointer invertKernel(const KernelBaseType &kernel,
			                                              const FieldRepresentationType *pFieldRepresentation,
			                                              const InverseFieldRepresentationType *pInverseFieldRepresentation) const;

		protected:
			NullRegistrationKernelInverter();
			virtual ~NullRegistrationKernelInverter() {};

		private:
			NullRegistrationKernelInverter(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapNullRegistrationKernelInverter.tpp"
#endif

#endif
