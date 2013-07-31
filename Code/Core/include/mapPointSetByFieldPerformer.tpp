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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapPointSetByFieldPerformer.tpp $
*/


#ifndef __MAP_POINT_SET_BY_FIELD_PERFORMER_TPP
#define __MAP_POINT_SET_BY_FIELD_PERFORMER_TPP

#include "mapPointSetByFieldPerformer.h"
#include "mapMappingException.h"
#include "mapPointVectorCombinationPolicy.h"
#include "mapServiceException.h"

namespace map
{
	namespace core
	{

		template <class TRegistration, class TInputData, class TResultData>
		typename PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::ResultDataPointer
		PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::
		performMapping(const RequestType &request) const
		{
			const DirectKernelBaseType &directKernelBase = request._spRegistration->getDirectMapping();
			const FieldBasedKernelType *pDirectKernel = dynamic_cast<const FieldBasedKernelType *>(&directKernelBase);

			if (pDirectKernel == NULL)
			{
				mapExceptionMacro(ServiceException, << "Error: cannot map point set. Reason: direct mapping kernel of registration is not model based. Registration: " << request._spRegistration);
			}

			if (request._spInputData.IsNull())
			{
				mapExceptionMacro(ServiceException, << "Error: cannot map point set. Reason: no input point set defined in request. Request: " << request);
			}

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
				typename ResultDataType::PointType transformedPoint;

				if (pDirectKernel->mapPoint(currentPoint, transformedPoint))
				{
					//save point and data in the result set
					spResultPointSet->SetPoint(pointID, transformedPoint);

					if (ownPointData)
					{
						spResultPointSet->SetPointData(pointID, static_cast<typename ResultDataType::PixelType>(currentPointData));
					}
				}
				else
				{
					//error: could not map point
					if (request._throwOnMappingError)
					{
						mapExceptionMacro(MappingException, << "Error: cannot map point by direct field kernel. Current point: " << currentPoint << std::endl << "Direct mapping kernel: " << directKernelBase);
					}
					else
					{
						//convert current point into target space directly and add it to the point set with the error value as point data.
						typename ResultDataType::PointType errorPoint;
						PointVectorCombinationPolicy<RegistrationType::MovingDimensions, RegistrationType::TargetDimensions>::mapPoint(currentPoint, errorPoint);

						spResultPointSet->SetPoint(pointID, errorPoint);
						spResultPointSet->SetPointData(pointID, static_cast<typename ResultDataType::PixelType>(request._errorValue));
					}
				}

				++pointIter;
			}

			return spResultPointSet;
		}

		template <class TRegistration, class TInputData, class TResultData>
		bool
		PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::
		canHandleRequest(const RequestType &request) const
		{
			const DirectKernelBaseType &directKernelBase = request._spRegistration->getDirectMapping();
			const FieldBasedKernelType *pDirectKernel = dynamic_cast<const FieldBasedKernelType *>(&directKernelBase);

			return (pDirectKernel != NULL) && (request._spInputData.IsNotNull());
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::
		getProviderName() const
		{
			return getStaticProviderName();
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::
		getStaticProviderName()
		{
			OStringStream os;
			os << "PointSetByFieldPerformer<Registration<" << RegistrationType::MovingDimensions << "," << RegistrationType::TargetDimensions << ">>";
			return os.str();
		}

		template <class TRegistration, class TInputData, class TResultData>
		String
		PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::
		getDescription() const
		{
			OStringStream os;
			os << "PointSetByFieldPerformer, Registration<" << RegistrationType::MovingDimensions << "," << RegistrationType::TargetDimensions << ">";
			return os.str();
		}

		template <class TRegistration, class TInputData, class TResultData>
		PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::
		PointSetByFieldPerformer() {};


		template <class TRegistration, class TInputData, class TResultData>
		PointSetByFieldPerformer<TRegistration, TInputData, TResultData>::
		~PointSetByFieldPerformer() {};



	} // end namespace core
} // end namespace map

#endif
