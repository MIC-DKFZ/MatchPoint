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


#ifndef __MAP_TRANS_MATTES_MI_REGISTRATION_ALGORITHM_H
#define __MAP_TRANS_MATTES_MI_REGISTRATION_ALGORITHM_H

#include "mapITKImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMattesMutualInformationImageToImageMetric.h"
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
			const char* const DefaultTransMattesRegistrationAlgorithm_profile =
				"<Profile><Description>A simple Mattes MI based image registration algorithm just supporting translation.</Description><Contact>Ralf Floca; sbr@dkfz-heidelberg.de</Contact><Characteristics><DataType>Image</DataType><TransformModel>translation</TransformModel><TransformDomain>global</TransformDomain><Metric>Mattes mutual information</Metric><Optimization>Regular Step Gradient Descent</Optimization></Characteristics><Keywords><Keyword>basic</Keyword></Keywords></Profile>";
			mapGenerateAlgorithmUIDPolicyMacro(DefaultTransMattesRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "TransMIRegistrationAlgorithm.default", "1.1.0",
											   DefaultTransMattesRegistrationAlgorithm_profile);


			/** @brief Boxing of a simple Mattes MI based image registration algorithm just supporting translation
			 @ingroup Boxed
			*/
			template < class TMovingImage, class TTargetImage = TMovingImage,
					 class TIdentificationPolicy = DefaultTransMattesRegistrationAlgorithmUIDPolicy >
			struct TransMattesMIRegistrationAlgorithmTemplate
			{
public:
				//optional
				typedef ::itk::MattesMutualInformationImageToImageMetric<TTargetImage, TMovingImage> MetricType;
				typedef ::itk::RegularStepGradientDescentOptimizer OptimizerType;
				typedef ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType>
				InterpolatorType;
				typedef ::itk::TranslationTransform<map::core::continuous::ScalarType, TMovingImage::ImageDimension>
				TranformType;

				typedef SealedFixedImageToImageMetricPolicyMacro<MetricType> MetricPolicyType;
				typedef SealedFixedSVNLOptimizerPolicyMacro<OptimizerType> OptimizerPolicyType;
				typedef SealedFixedInterpolatorPolicyMacro<InterpolatorType> InterpolatorPolicyType;
				typedef SealedFixedTransformPolicyMacro<TranformType> TransformPolicyType;

				//default typedefs
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
