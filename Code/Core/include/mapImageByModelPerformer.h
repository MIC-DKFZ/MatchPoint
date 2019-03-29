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


#ifndef __MAP_IMAGE_BY_MODEL_PERFORMER_H
#define __MAP_IMAGE_BY_MODEL_PERFORMER_H

#include "mapImageMappingPerformerBase.h"
#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace core
	{
		/*! @class ImageByModelPerformer
		* @brief Performer class that maps image data by using inverse mapping and a transformation model kernel.
		*
		* @ingroup MappingTask
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputData Type of the data in the input space.
		* @tparam TResultData Type of the data in the target space.
		*/
		template <class TRegistration, class TInputData, class TResultData>
		class ImageByModelPerformer : public
			ImageMappingPerformerBase<TRegistration, TInputData, TResultData>
		{
		public:
			/*! Standard class typedefs. */
			typedef ImageByModelPerformer<TRegistration, TInputData, TResultData>  Self;
			typedef ImageMappingPerformerBase<TRegistration, TInputData, TResultData>	 Superclass;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(ImageByModelPerformer, ImageMappingPerformerBase);
			itkNewMacro(Self);

			using RegistrationType = typename Superclass::RegistrationType;
			using RequestType = typename Superclass::RequestType;

			using InputDataType = typename Superclass::InputDataType;
			using InputDataConstPointer = typename Superclass::InputDataConstPointer;
			using ResultDataType = typename Superclass::ResultDataType;
			using ResultDataPointer = typename Superclass::ResultDataPointer;

			/*! Registers the input data and returns the result data.
			 * @eguarantee strong
			 * @param [in] request Referenz to the request that contains all needed information to perform the image registration
			 * @return Smart pointer to the result image.
			 */
			ResultDataPointer performMapping(const RequestType& request) const override;

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
			using InverseKernelBaseType = typename RegistrationType::InverseMappingType;

			ImageByModelPerformer();
			~ImageByModelPerformer() override;

		private:
			ImageByModelPerformer(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapImageByModelPerformer.tpp"
#endif

#endif
