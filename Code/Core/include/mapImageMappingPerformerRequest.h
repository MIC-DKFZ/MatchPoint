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


#ifndef __MAP_IMAGE_MAPPING_PERFORMER_REQUEST_H
#define __MAP_IMAGE_MAPPING_PERFORMER_REQUEST_H

#include "mapMappingPerformerRequestBase.h"
#include "mapFieldRepresentationDescriptor.h"

#include "itkInterpolateImageFunction.h"

#include <ostream>

namespace map
{
	namespace core
	{
		/*! @class ImageMappingPerformerRequest
		* This class is used by MappingPerformer for requests dealing with pointsets.
		* @ingroup MappingTask
		* @sa MappingPerformer
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputData Type of the input data.
		* @tparam TResultData Type of the data in the target space.
		*/
		template <class TRegistration, class TInputData, class TResultData>
		class ImageMappingPerformerRequest: public
			MappingPerformerRequestBase<TRegistration, TInputData, TResultData>
		{
		public:
			typedef MappingPerformerRequestBase<TRegistration, TInputData, TResultData> Superclass;
			using ResultDataType = typename Superclass::ResultDataType;
			using RegistrationType = typename Superclass::RegistrationType;
			using InputDataType = typename Superclass::InputDataType;
			using ErrorValueType = typename ResultDataType::PixelType;
			using PaddingValueType = typename ResultDataType::PixelType;
			using ResultImageDescriptorType = FieldRepresentationDescriptor<ResultDataType::ImageDimension>;

			typedef itk::InterpolateImageFunction<TInputData, continuous::ScalarType> InterpolateBaseType;
			using InterpolateBasePointer = typename InterpolateBaseType::Pointer;

			ImageMappingPerformerRequest(const RegistrationType* pRegistration,
										 const InputDataType* pInputData, const ResultImageDescriptorType* pResultDescriptor,
										 InterpolateBaseType* pInterpolateFunction,
										 bool throwOnMappingError, const ErrorValueType& errorValue,
										 bool throwOnOutOfInputAreaError, PaddingValueType paddingValue);

			~ImageMappingPerformerRequest() override;

			ImageMappingPerformerRequest(const ImageMappingPerformerRequest& /*other*/);
			void operator=(const ImageMappingPerformerRequest& /*other*/);

			typename ResultImageDescriptorType::ConstPointer _spResultDescriptor;

			mutable InterpolateBasePointer _spInterpolateFunction;

			bool _throwOnMappingError;
			ErrorValueType _errorValue;

			bool _throwOnOutOfInputAreaError;
			PaddingValueType _paddingValue;
		};

		template <class TRegistration, class TInputData, class TResultData>
		std::ostream& operator<<(std::ostream& os,
								 const ImageMappingPerformerRequest<TRegistration, TInputData, TResultData>& request)
		{
			if (request._spRegistration.IsNull())
			{
				os << "NULL" << std::endl;
			}
			else
			{
				os << request._spRegistration << std::endl;
			};

			os << "Input data: ";

			if (request._spInputData.IsNull())
			{
				os << "NULL" << std::endl;
			}
			else
			{
				os << request._spInputData << std::endl;
			};

			os << "Result descriptor: ";

			if (request._spResultDescriptor.IsNull())
			{
				os << "NULL" << std::endl;
			}
			else
			{
				os << request._spResultDescriptor << std::endl;
			};

			os << "Interpolate function: ";

			if (request._spInterpolateFunction.IsNull())
			{
				os << "NULL" << std::endl;
			}
			else
			{
				os << request._spInterpolateFunction << std::endl;
			};

			os << "ThrowOnMappingError: " << request._throwOnMappingError << std::endl;

			os << "Error value: " << request._errorValue << std::endl;

			os << "ThrowOnOutOfInputAreaError: " << request._throwOnOutOfInputAreaError << std::endl;

			os << "Padding value: " << request._paddingValue << std::endl;

			return os;
		};

	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapImageMappingPerformerRequest.tpp"
#endif

#endif
