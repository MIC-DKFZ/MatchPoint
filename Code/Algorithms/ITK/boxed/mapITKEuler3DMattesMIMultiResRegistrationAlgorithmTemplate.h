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


#ifndef __MAP_ITK_EULER3D_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_H
#define __MAP_ITK_EULER3D_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_H

#include "mapITKInitializedMultiResImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMattesMutualInformationImageToImageMetric.h"
#include "mapITKEuler3DTransform.h"
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

			mapGenerateAlgorithmUIDPolicyMacro(DefaultEuler3DMattesMultiResRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "Euler3DMattesMIMultiResRegistrationAlgorithm.default", "1.1.0", "");

			template < class TMovingImage, class TTargetImage = TMovingImage,
					 typename TUIDPolicy = DefaultEuler3DMattesMultiResRegistrationAlgorithmUIDPolicy,
					 class TInterpolatorPolicy =
					 SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TTargetImage, map::core::continuous::ScalarType> >,
					 class TPyramideInitializationPolicy = algorithm::itk::NoComponentInitializationPolicy >
			class ITKEuler3DMattesMIMultiResRegistrationAlgorithm :
				public algorithm::boxed::ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage,
				TTargetImage, TUIDPolicy,
				TInterpolatorPolicy,
				SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
				SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer>,
				SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform<map::core::continuous::ScalarType> >,
				SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TMovingImage, TMovingImage>, ::itk::MultiResolutionPyramidImageFilter<TTargetImage, TTargetImage>, TPyramideInitializationPolicy >
				>
			{
			public:
				typedef ITKEuler3DMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
						TInterpolatorPolicy,
						TPyramideInitializationPolicy > Self;

				typedef typename algorithm::boxed::ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage,
						TTargetImage, TUIDPolicy,
						TInterpolatorPolicy,
						SealedFixedImageToImageMetricPolicyMacro< ::itk::MattesMutualInformationImageToImageMetric<TMovingImage, TTargetImage> >,
						SealedFixedSVNLOptimizerPolicyMacro< ::itk::RegularStepGradientDescentOptimizer >,
						SealedFixedTransformPolicyMacro< ::itk::Euler3DTransform<map::core::continuous::ScalarType> >,
						SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TMovingImage, TMovingImage>, ::itk::MultiResolutionPyramidImageFilter<TTargetImage, TTargetImage>, TPyramideInitializationPolicy >
						>  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(ITKEuler3DMattesMIMultiResRegistrationAlgorithm,
							 ITKMultiResImageRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef ::itk::Array<double> ParametersType;

				typedef typename Superclass::MetaPropertyType MetaPropertyType;
				typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
				typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
				typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;

			protected:
				ITKEuler3DMattesMIMultiResRegistrationAlgorithm();
				virtual ~ITKEuler3DMattesMIMultiResRegistrationAlgorithm();

				virtual void configureAlgorithm();

				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

				virtual void doInterLevelSetup();

			private:

				ITKEuler3DMattesMIMultiResRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKEuler3DMattesMIMultiResRegistrationAlgorithmTemplate.tpp"
#endif

#endif
