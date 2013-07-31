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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapRigidMSRegistrationAlgorithmTemplate.h $
*/


#ifndef __MAP_RIGID_MS_REGISTRATION_ALGORITHM_H
#define __MAP_RIGID_MS_REGISTRATION_ALGORITHM_H

#include "mapITKImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMeanSquaresImageToImageMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"

#include "mapFixedImageToImageMetricPolicy.h"
#include "mapFixedInterpolatorPolicy.h"
#include "mapFixedSVNLOptimizerPolicy.h"
#include "mapFixedTransformPolicy.h"


namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			mapGenerateAlgorithmUIDPolicyMacro(DefaultRigidMSRegistrationAlgorithmUIDPolicy, "de.dkfz.matchpoint", "RigidMSRegistrationAlgorithm.default", "1.0.0");

			/** @brief Boxing of a simple rigid mean square based image registration algorithm
			 @ingroup Boxed
			*/
			template < class TMovingImage, class TTargetImage = TMovingImage,
			         class TIdentificationPolicy = DefaultRigidMSRegistrationAlgorithmUIDPolicy >
			struct RigidMSRegistrationAlgorithmTemplate
			{
public:
				//optional
				typedef ::itk::MeanSquaresImageToImageMetric<TTargetImage, TMovingImage> MetricType;
				typedef ::itk::RegularStepGradientDescentOptimizer OptimizerType;
				typedef ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType> InterpolatorType;
				typedef ::itk::TranslationTransform< map::core::continuous::ScalarType, TMovingImage::ImageDimension > TransformType;

				typedef SealedFixedImageToImageMetricPolicyMacro<MetricType> MetricPolicyType;
				typedef SealedFixedSVNLOptimizerPolicyMacro<OptimizerType> OptimizerPolicyType;
				typedef SealedFixedInterpolatorPolicyMacro<InterpolatorType> InterpolatorPolicyType;
				typedef SealedFixedTransformPolicyMacro<TransformType> TransformPolicyType;

				//default typdefs
				typedef map::algorithm::itk::ITKImageRegistrationAlgorithm < TMovingImage, TTargetImage,
				        TIdentificationPolicy,
				        InterpolatorPolicyType,
				        MetricPolicyType,
				        OptimizerPolicyType,
				        TransformPolicyType > Type;
				typedef typename Type::Pointer Pointer;
			};
		}
	}
}


#endif
