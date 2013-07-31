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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapImageByFieldPerformer.h $
*/


#ifndef __MAP_IMAGE_BY_FIELD_PERFORMER_H
#define __MAP_IMAGE_BY_FIELD_PERFORMER_H

#include "mapImageMappingPerformerBase.h"
#include "mapFieldBasedRegistrationKernel.h"

namespace map
{
	namespace core
	{
		/*! @class ImageByFieldPerformer
		* @brief Performer class that maps image data by using inverse mapping and a field kernel.
		*
		* @ingroup MappingTask
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputData Type of the data in the input space.
		* @tparam TResultData Type of the data in the target space.
		*/
		template <class TRegistration, class TInputData, class TResultData>
		class ImageByFieldPerformer : public ImageMappingPerformerBase<TRegistration, TInputData, TResultData>
		{
		public:
			/*! Standard class typedefs. */
			typedef ImageByFieldPerformer<TRegistration, TInputData, TResultData>  Self;
			typedef ImageMappingPerformerBase<TRegistration, TInputData, TResultData>	 Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(ImageByFieldPerformer, ImageMappingPerformerBase);
			itkNewMacro(Self);

			typedef typename Superclass::RegistrationType		    RegistrationType;
			typedef typename Superclass::RequestType		RequestType;

			typedef typename Superclass::InputDataType			    InputDataType;
			typedef typename Superclass::InputDataConstPointer	InputDataConstPointer;
			typedef typename Superclass::ResultDataType			    ResultDataType;
			typedef typename Superclass::ResultDataPointer	    ResultDataPointer;

			/*! Registers the input data and returns the result data.
			 * @eguarantee strong
			 * @param [in] request Referenz to the request that contains all needed information to perform the image registration
			 * @return Smart pointer to the result image.
			 */
			virtual ResultDataPointer performMapping(const RequestType &request) const;

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
			typedef typename RegistrationType::InverseMappingType InverseKernelBaseType;
			typedef FieldBasedRegistrationKernel<InverseKernelBaseType::InputDimensions, InverseKernelBaseType::OutputDimensions> FieldBasedKernelType;

			ImageByFieldPerformer();
			virtual ~ImageByFieldPerformer();

		private:
			ImageByFieldPerformer(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapImageByFieldPerformer.tpp"
#endif

#endif
