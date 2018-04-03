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


#ifndef __MAP_IMAGE_MAPPING_PERFORMER_BASE_H
#define __MAP_IMAGE_MAPPING_PERFORMER_BASE_H

#include "mapMappingPerformerBase.h"
#include "mapImageMappingPerformerRequest.h"

namespace map
{
	namespace core
	{
		/*! @class ImageMappingPerformerBase
		* @brief Base class for any instance in MatchPoint that provides the service of performing a registration on any kind of data.
		*
		* @ingroup MappingTask
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputData Type of the data in the input space.
		* @tparam TResultData Type of the data in the target space.
		*/
		template <class TRegistration, class TInputData, class TResultData>
		class ImageMappingPerformerBase : public
			MappingPerformerBase< ImageMappingPerformerRequest<TRegistration, TInputData, TResultData> >
		{
		public:
			typedef ImageMappingPerformerRequest<TRegistration, TInputData, TResultData> RequestType;

			/*! Standard class typedefs. */
			typedef ImageMappingPerformerBase<TRegistration, TInputData, TResultData>  Self;
			typedef MappingPerformerBase< RequestType >       Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(ImageMappingPerformerBase, MappingPerformerBase);

			typedef typename Superclass::RegistrationType   RegistrationType;
			typedef typename Superclass::InputDataType      InputDataType;
			typedef typename Superclass::InputDataConstPointer   InputDataConstPointer;
			typedef typename Superclass::ResultDataType     ResultDataType;
			typedef typename Superclass::ResultDataPointer  ResultDataPointer;

			typedef typename RequestType::ResultImageDescriptorType ResultImageDescriptorType;

			/*! Registers the input data and returns the result data.
			 * @eguarantee strong
			 * @param [in] request Referenz to the request that contains all needed information to perform the image registration
			 * @return Smart pointer to the result image.
			 */
			virtual ResultDataPointer performMapping(const RequestType& request) const = 0;

#ifdef ITK_USE_CONCEPT_CHECKING
			/** Begin concept checking */
			itkConceptMacro(InputDataFitsRegistrationCheck,
							(itk::Concept::SameDimension<InputDataType::ImageDimension, RegistrationType::MovingDimensions>));
			itkConceptMacro(ResultDataFitsRegistrationCheck,
							(itk::Concept::SameDimension<ResultDataType::ImageDimension, RegistrationType::TargetDimensions>));
			/** End concept checking */
#endif

		protected:

			ImageMappingPerformerBase();
			virtual ~ImageMappingPerformerBase();

		private:
			ImageMappingPerformerBase(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapImageMappingPerformerBase.tpp"
#endif

#endif
