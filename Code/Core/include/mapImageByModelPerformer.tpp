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


#ifndef __MAP_IMAGE_BY_MODEL_PERFORMER_TPP
#define __MAP_IMAGE_BY_MODEL_PERFORMER_TPP

#include "mapImageByModelPerformer.h"
#include "mapServiceException.h"
#include "mapRegistrationKernel.h"

#include "itkResampleImageFilter.h"

namespace map
{
	namespace core
	{

		template <unsigned int VMovingDimensions, unsigned int VTargetDimensions, class TRequest>
		class ImageByModelPerformerHelper
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
			ImageByModelPerformerHelper(); //purposely not implemented
			~ImageByModelPerformerHelper(); //purposely not implemented
			ImageByModelPerformerHelper(const ImageByModelPerformerHelper&);  //purposely not implemented
			ImageByModelPerformerHelper& operator = (const
					ImageByModelPerformerHelper&);  //purposely not implemented
		};

		template <unsigned int VDimensions, class TRequest>
		class ImageByModelPerformerHelper<VDimensions, VDimensions, TRequest>
		{
		public:
			typedef TRequest RequestType;
			typedef typename RequestType::InputDataType InputDataType;
			typedef typename RequestType::ResultDataType ResultDataType;
			typedef typename RequestType::ResultDataType::Pointer ResultDataPointer;
			typedef typename RequestType::RegistrationType::InverseMappingType InverseKernelBaseType;
			typedef RegistrationKernel<InverseKernelBaseType::InputDimensions, InverseKernelBaseType::OutputDimensions>
			ModelKernelType;

			static ResultDataPointer performMapping(const RequestType& request)
			{
				const InverseKernelBaseType& inverseKernelBase = request._spRegistration->getInverseMapping();
				const ModelKernelType* pInverseKernel = dynamic_cast<const ModelKernelType*>(&inverseKernelBase);
				//get direct access to the transform model
				const typename ModelKernelType::TransformType* pTransformModel =
					pInverseKernel->getTransformModel();

				//instantiate resampler
				typedef itk::ResampleImageFilter<InputDataType, ResultDataType, continuous::ScalarType>
				ResampleFilterType;
				typename ResampleFilterType::Pointer spFilter = ResampleFilterType::New();

				spFilter->SetOutputSpacing(request._spResultDescriptor->getSpacing());
				spFilter->SetOutputOrigin(request._spResultDescriptor->getOrigin());
				spFilter->SetSize(request._spResultDescriptor->getRepresentedLocalImageRegion().GetSize());
				spFilter->SetOutputDirection(request._spResultDescriptor->getDirection());

				spFilter->SetTransform(pTransformModel);

				spFilter->SetInput(request._spInputData);
				spFilter->SetInterpolator(request._spInterpolateFunction);
				spFilter->SetDefaultPixelValue(request._paddingValue);

				ResultDataPointer spResultImage = spFilter->GetOutput();
				spFilter->Update();

				return spResultImage;
			};

		protected:
			ImageByModelPerformerHelper(); //purposely not implemented
			~ImageByModelPerformerHelper(); //purposely not implemented
			ImageByModelPerformerHelper(const ImageByModelPerformerHelper&);  //purposely not implemented
			ImageByModelPerformerHelper& operator = (const
					ImageByModelPerformerHelper&);  //purposely not implemented
		};

		template <class TRegistration, class TInputData, class TResultData>
		typename ImageByModelPerformer<TRegistration, TInputData, TResultData>::ResultDataPointer
		ImageByModelPerformer<TRegistration, TInputData, TResultData>::
		performMapping(const RequestType& request) const
		{
      typedef RegistrationKernel<InverseKernelBaseType::InputDimensions, InverseKernelBaseType::OutputDimensions>
            ModelKernelType;
      const InverseKernelBaseType& inverseKernelBase = request._spRegistration->getInverseMapping();
			const ModelKernelType* pInverseKernel = dynamic_cast<const ModelKernelType*>(&inverseKernelBase);

			if (pInverseKernel == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map image. Reason: inverse mapping kernel of registration is not model based. Registration: "
								  << request._spRegistration);
			}

			if (pInverseKernel->getTransformModel() == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map image. Reason: inverse model based mapping kernel has no transform model. Check correct creation of the registration. Registration: "
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

			typedef ImageByModelPerformerHelper<RequestType::MovingDimensions, RequestType::TargetDimensions, RequestType>
			HelperType;
			ResultDataPointer spResultImage =  HelperType::performMapping(request);

			return spResultImage;
		}

		template <class TRegistration, class TInputData, class TResultData>
		bool
		ImageByModelPerformer<TRegistration, TInputData, TResultData>::
		canHandleRequest(const RequestType& request) const
		{
			const InverseKernelBaseType& inverseKernelBase = request._spRegistration->getInverseMapping();
			const ModelKernelType* pInverseKernel = dynamic_cast<const ModelKernelType*>(&inverseKernelBase);

			return (pInverseKernel != NULL) && (request._spInputData.IsNotNull());
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		ImageByModelPerformer<TRegistration, TInputData, TResultData>::
		getProviderName() const
		{
			return getStaticProviderName();
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		ImageByModelPerformer<TRegistration, TInputData, TResultData>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "ImageByModelPerformer<Registration<" << RegistrationType::MovingDimensions << "," <<
			   RegistrationType::TargetDimensions << ">>";
			return os.str();
		};

		template <class TRegistration, class TInputData, class TResultData>
		String
		ImageByModelPerformer<TRegistration, TInputData, TResultData>::
		getDescription() const
		{
			OStringStream os;
			os << "ImageByModelPerformer, Registration<" << RegistrationType::MovingDimensions << "," <<
			   RegistrationType::TargetDimensions << ">";
			return os.str();
		}

		template <class TRegistration, class TInputData, class TResultData>
		ImageByModelPerformer<TRegistration, TInputData, TResultData>::
		ImageByModelPerformer() {};

		template <class TRegistration, class TInputData, class TResultData>
		ImageByModelPerformer<TRegistration, TInputData, TResultData>::
		~ImageByModelPerformer() {};


	} // end namespace core
} // end namespace map

#endif
