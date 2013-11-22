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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKTransMattesMIMultiResRegistrationAlgorithmTemplate.h $
*/


#ifndef __MAP_ITK_TRANS_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_H
#define __MAP_ITK_TRANS_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_H

#include "mapITKInitializedMultiResImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMattesMutualInformationImageToImageMetric.h"
#include "mapITKTranslationTransform.h"
#include "mapITKLinearInterpolateImageFunction.h"

#include "mapFixedImageToImageMetricPolicy.h"
#include "mapFixedInterpolatorPolicy.h"
#include "mapFixedSVNLOptimizerPolicy.h"
#include "mapFixedTransformPolicy.h"
#include "mapSealedImagePyramidesPolicy.h"
#include "mapNoComponentInitializationPolicy.h"


namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			mapGenerateAlgorithmUIDPolicyMacro(DefaultTransMattesMultiResRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "TransMattesMIMultiResRegistrationAlgorithm.default", "1.0.0", "");

			template < class TMovingImage, class TTargetImage = TMovingImage,
					 typename TUIDPolicy = DefaultTransMattesMultiResRegistrationAlgorithmUIDPolicy,
					 class TInterpolatorPolicy =
					 SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType> >,
					 class TPyramideInitializationPolicy = algorithm::itk::NoComponentInitializationPolicy >
			class ITKTransMattesMIMultiResRegistrationAlgorithm :
				public algorithm::boxed::ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage,
				TTargetImage, TUIDPolicy,
				TInterpolatorPolicy,
				SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
				SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer>,
				SealedFixedTransformPolicyMacro< ::itk::TranslationTransform<map::core::continuous::ScalarType, TMovingImage::ImageDimension> >,
				SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TMovingImage, TMovingImage>, ::itk::MultiResolutionPyramidImageFilter<TTargetImage, TTargetImage>, TPyramideInitializationPolicy >
				>
			{
			public:
				typedef ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
						TInterpolatorPolicy,
						TPyramideInitializationPolicy > Self;

				typedef typename algorithm::boxed::ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage,
						TTargetImage, TUIDPolicy,
						TInterpolatorPolicy,
						SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
						SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer >,
						SealedFixedTransformPolicyMacro< ::itk::TranslationTransform<map::core::continuous::ScalarType, TMovingImage::ImageDimension> >,
						SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TMovingImage, TMovingImage>, ::itk::MultiResolutionPyramidImageFilter<TTargetImage, TTargetImage>, TPyramideInitializationPolicy >
						>  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(ITKTransMattesMIMultiResRegistrationAlgorithm,
							 ITKMultiResImageRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef ::itk::Array<double> ParametersType;

				typedef typename Superclass::MetaPropertyType MetaPropertyType;
				typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
				typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
				typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;

			protected:
				ITKTransMattesMIMultiResRegistrationAlgorithm();
				virtual ~ITKTransMattesMIMultiResRegistrationAlgorithm();

				virtual void configureAlgorithm();

				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

				virtual void doInterLevelSetup();

			private:

				ITKTransMattesMIMultiResRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKTransMattesMIMultiResRegistrationAlgorithmTemplate.tpp"
#endif

#endif
