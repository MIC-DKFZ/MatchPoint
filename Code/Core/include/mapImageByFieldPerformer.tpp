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


#ifndef __MAP_IMAGE_BY_FIELD_PERFORMER_TPP
#define __MAP_IMAGE_BY_FIELD_PERFORMER_TPP

#include "mapImageByFieldPerformer.h"
#include "mapServiceException.h"
#include "mapMappingException.h"

#include "mapArbitraryWarpImageFilter.h"

namespace map
{
	namespace core
	{

		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions, class TRequest>
		class ImageByFieldPerformerHelper
		{
		public:
			typedef TRequest RequestType;
			typedef typename RequestType::ResultDataType::Pointer ResultDataPointer;

			static ResultDataPointer performMapping(const RequestType& request)
			{
				mapExceptionStaticMacro(ServiceException,
										<< "Error: unimplemented feature. Cannot perform unsymetric registrations right now. Request: " <<
										request);
				//! @TODO unsymmetrische registrierungen müssen auch noch gehandhabt werden; Strategie ist dafür auszuarbeiten, da es dann auch Regeln für fehlende Surjektivität und Injektivität geben muss.
			};

		protected:
			ImageByFieldPerformerHelper(); //purposely not implemented
			~ImageByFieldPerformerHelper(); //purposely not implemented
			ImageByFieldPerformerHelper(const ImageByFieldPerformerHelper&);  //purposely not implemented
			ImageByFieldPerformerHelper& operator = (const
					ImageByFieldPerformerHelper&);  //purposely not implemented
		};

		template <unsigned int VDimensions, class TRequest>
		class ImageByFieldPerformerHelper<VDimensions, VDimensions, TRequest>
		{
		public:
			typedef TRequest RequestType;
			typedef typename RequestType::InputDataType InputDataType;
			typedef typename RequestType::ResultDataType ResultDataType;
			typedef typename RequestType::ResultDataType::Pointer ResultDataPointer;
			typedef typename RequestType::RegistrationType::InverseMappingType InverseKernelBaseType;
			typedef FieldBasedRegistrationKernel<InverseKernelBaseType::InputDimensions, InverseKernelBaseType::OutputDimensions>
			FieldKernelType;

			static ResultDataPointer performMapping(const RequestType& request)
			{
				const InverseKernelBaseType& inverseKernelBase = request._spRegistration->getInverseMapping();
				const FieldKernelType* pInverseKernel = dynamic_cast<const FieldKernelType*>(&inverseKernelBase);

				//instantiate resampler
				typedef itk::map::ArbitraryWarpImageFilter<InputDataType, ResultDataType, typename FieldKernelType::FieldType>
				WarpFilterType;
				typename WarpFilterType::Pointer spFilter = WarpFilterType::New();

				spFilter->SetOutputSpacing(request._spResultDescriptor->getSpacing());
				spFilter->SetOutputOrigin(request._spResultDescriptor->getOrigin());
				spFilter->SetSize(request._spResultDescriptor->getRepresentedLocalImageRegion().GetSize());
				spFilter->SetOutputDirection(request._spResultDescriptor->getDirection());

				spFilter->SetDisplacementField(pInverseKernel->getField());

				spFilter->SetInput(request._spInputData);
				spFilter->SetInterpolator(request._spInterpolateFunction);
				spFilter->SetEdgePaddingValue(request._paddingValue);
				spFilter->SetThrowExceptionOnMappingError(request._throwOnMappingError);
				spFilter->SetMappingErrorValue(request._errorValue);

				ResultDataPointer spResultImage = spFilter->GetOutput();
				spFilter->Update();

				return spResultImage;
			};

		protected:
			ImageByFieldPerformerHelper(); //purposely not implemented
			~ImageByFieldPerformerHelper(); //purposely not implemented
			ImageByFieldPerformerHelper(const ImageByFieldPerformerHelper&);  //purposely not implemented
			ImageByFieldPerformerHelper& operator = (const
					ImageByFieldPerformerHelper&);  //purposely not implemented
		};

		template <class TRegistration, class TInputData, class TResultData>
		typename ImageByFieldPerformer<TRegistration, TInputData, TResultData>::ResultDataPointer
		ImageByFieldPerformer<TRegistration, TInputData, TResultData>::
		performMapping(const RequestType& request) const
		{
			const InverseKernelBaseType& inverseKernelBase = request._spRegistration->getInverseMapping();
			const FieldBasedKernelType* pInverseKernel = dynamic_cast<const FieldBasedKernelType*>
					(&inverseKernelBase);

			if (pInverseKernel == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map image. Reason: inverse mapping kernel of registration is not field based. Registration: "
								  << request._spRegistration);
			}

			if (pInverseKernel->getField() == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map image. Reason: inverse field based mapping kernel has no field. Check correct creation of the registration. Registration: "
								  << request._spRegistration);
			}

			if (request._spInputData.IsNull())
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map image. Reason: no input image defined in request. Request: " << request);
			}

			if (request._spResultDescriptor.IsNull())
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map image. Reason: no result descriptor defined in request. Request: " <<
								  request);
			}

			if (request._spInterpolateFunction.IsNull())
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map image. Reason: no interpolate function defined in request. Request: " <<
								  request);
			}

			if (request._throwOnOutOfInputAreaError)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: unimplemented feature. Cannot throw exception on out of input area error. Only padding is implemented right now");
				//! @todo Prüfen ob auch exception geworfen werden soll, wenn ja muss ein erweiterter resample filter gemacht werden, wenn nein, dann muss der request angepasst werden
			}

			ResultDataPointer spResultImage;

			try
			{
				typedef ImageByFieldPerformerHelper<RequestType::MovingDimensions, RequestType::TargetDimensions, RequestType>
				HelperType;
				spResultImage =  HelperType::performMapping(request);
			}
			catch (itk::ExceptionObject& ex)
			{
				mapExceptionMacro(MappingException, << ex.what());
			}
			catch (...)
			{
				mapExceptionMacro(MappingException, << "Unknown exception");
			}


			return spResultImage;
		}

		template <class TRegistration, class TInputData, class TResultData>
		bool
		ImageByFieldPerformer<TRegistration, TInputData, TResultData>::
		canHandleRequest(const RequestType& request) const
		{
			const InverseKernelBaseType& inverseKernelBase = request._spRegistration->getInverseMapping();
			const FieldBasedKernelType* pInverseKernel = dynamic_cast<const FieldBasedKernelType*>
					(&inverseKernelBase);

			return (pInverseKernel != NULL) && (request._spInputData.IsNotNull());
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		ImageByFieldPerformer<TRegistration, TInputData, TResultData>::
		getProviderName() const
		{
			return getStaticProviderName();
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		ImageByFieldPerformer<TRegistration, TInputData, TResultData>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "ImageByFieldPerformer<Registration<" << RegistrationType::MovingDimensions << "," <<
			   RegistrationType::TargetDimensions << ">>";
			return os.str();
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		ImageByFieldPerformer<TRegistration, TInputData, TResultData>::
		getDescription() const
		{
			OStringStream os;
			os << "ImageByFieldPerformer, Registration<" << RegistrationType::MovingDimensions << "," <<
			   RegistrationType::TargetDimensions << ">";
			return os.str();
		}

		template <class TRegistration, class TInputData, class TResultData>
		ImageByFieldPerformer<TRegistration, TInputData, TResultData>::
		ImageByFieldPerformer() {};

		template <class TRegistration, class TInputData, class TResultData>
		ImageByFieldPerformer<TRegistration, TInputData, TResultData>::
		~ImageByFieldPerformer() {};


	} // end namespace core
} // end namespace map

#endif
