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


#ifndef __MAP_POINT_SET_BY_MODEL_PERFORMER_TPP
#define __MAP_POINT_SET_BY_MODEL_PERFORMER_TPP

#include "mapPointSetByModelPerformer.h"
#include "mapServiceException.h"

namespace map
{
	namespace core
	{

		template <class TRegistration, class TInputData, class TResultData>
		typename PointSetByModelPerformer<TRegistration, TInputData, TResultData>::ResultDataPointer
		PointSetByModelPerformer<TRegistration, TInputData, TResultData>::
		performMapping(const RequestType& request) const
		{
			const DirectKernelBaseType& directKernelBase = request._spRegistration->getDirectMapping();
			const ModelKernelType* pDirectKernel = dynamic_cast<const ModelKernelType*>(&directKernelBase);

			if (pDirectKernel == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map point set. Reason: direct mapping kernel of registration is not model based. Registration: "
								  << request._spRegistration);
			}

			if (pDirectKernel->getTransformModel() == NULL)
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map point set. Reason: direct model based mapping kernel has no transform model. Check correct creation of the registration. Registration: "
								  << request._spRegistration);
			}

			if (request._spInputData.IsNull())
			{
				mapExceptionMacro(ServiceException,
								  << "Error: cannot map point set. Reason: no input point set defined in request. Request: " <<
								  request);
			}

			//get direct access to the transform model
			const typename ModelKernelType::TransformType::TransformBaseType* transform =
				pDirectKernel->getTransformModel()->getTransform();

			//create result point set
			ResultDataPointer spResultPointSet = ResultDataType::New();
			typedef typename InputDataType::PointsContainer::ConstIterator PointIteratorType;
			typedef typename InputDataType::PointsContainer::ConstIterator PointDataIteratorType;

			PointIteratorType pointIter = request._spInputData->GetPoints()->Begin();
			PointIteratorType pointEnd = request._spInputData->GetPoints()->End();

			while (pointIter != pointEnd)
			{
				typename InputDataType::PointIdentifier pointID = pointIter.Index();
				typename InputDataType::PointType currentPoint = pointIter.Value();
				typename InputDataType::PixelType currentPointData;
				bool ownPointData = request._spInputData->GetPointData(pointID, &currentPointData);

				//transform the point
				typename ResultDataType::PointType transformedPoint = transform->TransformPoint(currentPoint);

				//save point and data in the result set
				spResultPointSet->SetPoint(pointID, transformedPoint);

				if (ownPointData)
				{
					spResultPointSet->SetPointData(pointID,
												   static_cast<typename ResultDataType::PixelType>(currentPointData));
				}

				++pointIter;
			}

			return spResultPointSet;
		}

		template <class TRegistration, class TInputData, class TResultData>
		bool
		PointSetByModelPerformer<TRegistration, TInputData, TResultData>::
		canHandleRequest(const RequestType& request) const
		{
			const DirectKernelBaseType& directKernelBase = request._spRegistration->getDirectMapping();
			const ModelKernelType* pDirectKernel = dynamic_cast<const ModelKernelType*>(&directKernelBase);

			return (pDirectKernel != NULL) && (request._spInputData.IsNotNull());
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		PointSetByModelPerformer<TRegistration, TInputData, TResultData>::
		getProviderName() const
		{
			return getStaticProviderName();
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		PointSetByModelPerformer<TRegistration, TInputData, TResultData>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "PointSetByModelPerformer<Registration<" << RegistrationType::MovingDimensions << "," <<
			   RegistrationType::TargetDimensions << ">>";
			return os.str();
		};

		template <class TRegistration, class TInputData, class TResultData>
		String
		PointSetByModelPerformer<TRegistration, TInputData, TResultData>::
		getDescription() const
		{
			OStringStream os;
			os << "PointSetByModelPerformer, Registration<" << RegistrationType::MovingDimensions << "," <<
			   RegistrationType::TargetDimensions << ">";
			return os.str();
		}

		template <class TRegistration, class TInputData, class TResultData>
		PointSetByModelPerformer<TRegistration, TInputData, TResultData>::
		PointSetByModelPerformer() {};

		template <class TRegistration, class TInputData, class TResultData>
		PointSetByModelPerformer<TRegistration, TInputData, TResultData>::
		~PointSetByModelPerformer() {};

	} // end namespace core
} // end namespace map

#endif
