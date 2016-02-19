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
// @version $Revision: 797 $ (last changed revision)
// @date    $Date: 2014-10-10 11:42:05 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKAffineMattesMIMultiResRegistrationAlgorithmTemplate.h $
*/


#ifndef __MAP_ITK_AFFINE_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_H
#define __MAP_ITK_AFFINE_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_H

#include "mapITKInitializedMultiResImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMattesMutualInformationImageToImageMetric.h"
#include "mapITKAffineTransform.h"
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

			mapGenerateAlgorithmUIDPolicyMacro(DefaultAffineMattesMultiResRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "AffineMattesMIMultiResRegistrationAlgorithm.default", "1.0.0", "");

			template < class TMovingImage, class TTargetImage = TMovingImage,
					 typename TUIDPolicy = DefaultAffineMattesMultiResRegistrationAlgorithmUIDPolicy,
					 class TInterpolatorPolicy =
					 SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType> >,
					 class TPyramideInitializationPolicy = algorithm::itk::NoComponentInitializationPolicy >
			class ITKAffineMattesMIMultiResRegistrationAlgorithm :
				public algorithm::boxed::ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage,
				TTargetImage, TUIDPolicy,
				TInterpolatorPolicy,
				SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
				SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer>,
				SealedFixedTransformPolicyMacro< ::itk::AffineTransform<map::core::continuous::ScalarType, TTargetImage::ImageDimension> >,
				SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TMovingImage, TMovingImage>, ::itk::MultiResolutionPyramidImageFilter<TTargetImage, TTargetImage>, TPyramideInitializationPolicy >
				>
			{
			public:
				typedef ITKAffineMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
						TInterpolatorPolicy,
						TPyramideInitializationPolicy > Self;

				typedef typename algorithm::boxed::ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage,
						TTargetImage, TUIDPolicy,
						TInterpolatorPolicy,
						SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
						SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer >,
            SealedFixedTransformPolicyMacro< ::itk::AffineTransform<map::core::continuous::ScalarType, TTargetImage::ImageDimension> >,
						SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TMovingImage, TMovingImage>, ::itk::MultiResolutionPyramidImageFilter<TTargetImage, TTargetImage>, TPyramideInitializationPolicy >
						>  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(ITKAffineMattesMIMultiResRegistrationAlgorithm,
							 ITKMultiResImageRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef ::itk::Array<double> ParametersType;

				typedef typename Superclass::MetaPropertyType MetaPropertyType;
				typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
				typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
				typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;

			protected:
				ITKAffineMattesMIMultiResRegistrationAlgorithm();
				virtual ~ITKAffineMattesMIMultiResRegistrationAlgorithm();

				virtual void configureAlgorithm();

				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

				virtual void doInterLevelSetup();

			private:

				ITKAffineMattesMIMultiResRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKAffineMattesMIMultiResRegistrationAlgorithmTemplate.tpp"
#endif

#endif
