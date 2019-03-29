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




#ifndef __ITK_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_H
#define __ITK_IMAGE_REGISTRATION_ALGORITHM_INTERFACE_H

#include <itkTransform.h>
#include <itkInterpolateImageFunction.h>

#include "mapITKSVNLOptimizerControlInterface.h"
#include "mapITKImageToImageMetricControlInterface.h"

#include "mapITKSVNLOptimizerSetterInterface.h"
#include "mapITKSVNLOptimizerGetterInterface.h"
#include "mapITKTransformSetterInterface.h"
#include "mapITKTransformGetterInterface.h"
#include "mapITKInterpolatorSetterInterface.h"
#include "mapITKInterpolatorGetterInterface.h"
#include "mapITKImageToImageMetricSetterInterface.h"
#include "mapITKImageToImageMetricGetterInterface.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
    mark code as components of this project
 */
namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKImageRegistrationAlgorithmInterface
			    @brief This is the interface for image registration algorithms from ITK
			    @ingroup AlgorithmFacets
			 */
			template<class TMovingImage, class TTargetImage, class TTransformScalar, class TInterpolatorCoordRep>
			class ITKImageRegistrationAlgorithmInterface
			{
			public:
				typedef ITKImageRegistrationAlgorithmInterface<TMovingImage, TTargetImage, TTransformScalar, TInterpolatorCoordRep>
				Self;

				using OptimizerBaseType = ITKSVNLOptimizerControlInterface;
				typedef ITKImageToImageMetricControlInterface<TMovingImage, TTargetImage> MetricBaseType;
				typedef ::itk::Transform<TTransformScalar, TMovingImage::ImageDimension, TTargetImage::ImageDimension> TransformBaseType;
				typedef ::itk::InterpolateImageFunction<TMovingImage, TInterpolatorCoordRep> InterpolatorBaseType;

				using OptimizerSetterInterfaceType = facet::ITKSVNLOptimizerSetterInterface;
				using OptimizerGetterInterfaceType = facet::ITKSVNLOptimizerGetterInterface;
				typedef facet::ITKTransformSetterInterface<TTransformScalar, TMovingImage::ImageDimension, TTargetImage::ImageDimension>
				TransformSetterInterfaceType;
				typedef facet::ITKTransformGetterInterface<TTransformScalar, TMovingImage::ImageDimension, TTargetImage::ImageDimension>
				TransformGetterInterfaceType;
				typedef facet::ITKInterpolatorSetterInterface<TMovingImage, TInterpolatorCoordRep>
				InterpolatorSetterInterfaceType;
				typedef facet::ITKInterpolatorGetterInterface<TMovingImage, TInterpolatorCoordRep>
				InterpolatorGetterInterfaceType;
				typedef facet::ITKImageToImageMetricSetterInterface<TMovingImage, TTargetImage>
				MetricSetterInterfaceType;
				typedef facet::ITKImageToImageMetricGetterInterface<TMovingImage, TTargetImage>
				MetricGetterInterfaceType;

			protected:
				ITKImageRegistrationAlgorithmInterface();
				virtual ~ITKImageRegistrationAlgorithmInterface();

			private:
				//No copy constructor allowed
				ITKImageRegistrationAlgorithmInterface(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			};

		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKImageRegistrationAlgorithmInterface.tpp"
#endif


#endif
