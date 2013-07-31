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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldBasedKernelInverter.h $
*/

#ifndef __MAP_FIELD_BASED_KERNEL_INVERTER_H
#define __MAP_FIELD_BASED_KERNEL_INVERTER_H

#include "mapRegistrationKernelInverterBase.h"
#include "mapFieldBasedRegistrationKernel.h"

namespace map
{
	namespace core
	{
		/*! @class FieldBasedKernelInverter
		* @brief Provider that is able to invert a FieldBasedRegistrationKernel.
		*
		* The provider generates an inverted kernel by creatinge a LazyFieldBasedRegistrationKernel
		* an populates it with a parametrized FieldByFieldInversionFunctor.
		*
		* @sa FieldByFieldInversionFunctor
		* @sa LazyFieldBasedRegistrationKernel
		* @sa FieldBasedRegistrationKernel
		* @ingroup RegOperation
		* @tparam VInputDimensions Dimensions of the input space of the kernel that should be inverted.
		* @tparam VOutputDimensions Dimensions of the output space of the kernel that should be inverted.
		*/
		template <unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class FieldBasedKernelInverter : public RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef FieldBasedKernelInverter<VInputDimensions, VOutputDimensions>				Self;
			typedef RegistrationKernelInverterBase<VInputDimensions, VOutputDimensions>	Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(FieldBasedKernelInverter, RegistrationKernelInverterBase);
			itkNewMacro(Self);

			typedef typename Superclass::KernelBaseType	                KernelBaseType;
			typedef typename Superclass::KernelBasePointer	            KernelBasePointer;
			typedef typename Superclass::InverseKernelBaseType	        InverseKernelBaseType;
			typedef typename Superclass::InverseKernelBasePointer	      InverseKernelBasePointer;
			typedef typename Superclass::FieldRepresentationType	      FieldRepresentationType;
			typedef typename Superclass::InverseFieldRepresentationType	InverseFieldRepresentationType;
			typedef typename Superclass::RequestType	                  RequestType;
			typedef FieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions> KernelType;


			/*! gets the number of iterations that has been set for the numeric inversion
			* @return the number of iterations
			 * @eguarantee no fail */
			unsigned long getFunctorNumberOfIterations() const;

			/*! Sets the number of iterations for the numeric inversion
			* @param [in] nrOfIterations the number of iterations
			 * @eguarantee no fail */
			void setFunctorNumberOfIterations(unsigned long nrOfIterations);

			/*! gets the stop value (exactness delta) that has been set for the numeric inversion
			 * @return the stop value
					 * @eguarantee no fail */
			double getFunctorStopValue() const;

			/*! Sets the stop value for the numeric inversion (exactness)
			 * @param [in] nrOfIterations the number of iterations
					 * @eguarantee no fail */
			void setFunctorStopValue(double stopValue);


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
				 * may not be NULL!.
				 * @return Smart pointer to the inverse kernel.
				 * @pre pInverseFieldRepresentation must not be NULL.
				 * @post If the method returns with no exception, there is always an inverse kernel (smart pointer is not NULL)
				 * @remark This function might cause an exception/assertion if the responsible service provider needs
				 * pInverseFieldRepresentation not to be NULL but it is.
				 */
			virtual InverseKernelBasePointer invertKernel(const KernelBaseType &kernel,
			                                              const FieldRepresentationType *pFieldRepresentation,
			                                              const InverseFieldRepresentationType *pInverseFieldRepresentation) const;

		protected:
			/*!Cached properties that should be used on the FieldByFieldInversionFunctor*/
			unsigned long _functorNrOfIterations;
			/*!Cached properties that should be used on the FieldByFieldInversionFunctor*/
			double _functorStopValue;

			FieldBasedKernelInverter();
			virtual ~FieldBasedKernelInverter() {};

		private:
			FieldBasedKernelInverter(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldBasedKernelInverter.tpp"
#endif

#endif
