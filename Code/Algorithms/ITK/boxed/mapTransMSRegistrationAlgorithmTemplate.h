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
			const char* const DefaultTransMSRegistrationAlgorithm_profile =
				"<Profile><Description>A simple Mattes MI based image registration algorithm just supporting translation.</Description><Contact>Ralf Floca; sbr@dkfz-heidelberg.de</Contact><Characteristics><DataType>Image</DataType><TransformModel>translation</TransformModel><TransformDomain>global</TransformDomain><Metric>Mean square difference</Metric><Optimization>Regular Step Gradient Descent</Optimization></Characteristics><Keywords><Keyword>basic</Keyword></Keywords></Profile>";

			mapGenerateAlgorithmUIDPolicyMacro(DefaultTransMSRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "TransMSRegistrationAlgorithm.default", "1.1.0",
											   DefaultTransMSRegistrationAlgorithm_profile);

			/** @brief Boxing of a simple mean square based image registration algorithm only allow translation
			 @ingroup Boxed
			*/
			template < class TMovingImage, class TTargetImage = TMovingImage,
					 class TIdentificationPolicy = DefaultTransMSRegistrationAlgorithmUIDPolicy >
			struct TransMSRegistrationAlgorithmTemplate
			{
public:
				//optional
				typedef ::itk::MeanSquaresImageToImageMetric<TTargetImage, TMovingImage> MetricType;
				typedef ::itk::RegularStepGradientDescentOptimizer OptimizerType;
				typedef ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType>
				InterpolatorType;
				typedef ::itk::TranslationTransform< map::core::continuous::ScalarType, TMovingImage::ImageDimension >
				TransformType;

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
