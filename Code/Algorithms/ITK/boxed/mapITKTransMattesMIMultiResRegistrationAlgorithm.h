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


#ifndef __MAP_ITK_TRANS_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_H
#define __MAP_ITK_TRANS_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_H

#include "mapITKInitializedMultiResImageRegistrationAlgorithm.h"

#include "mapITKRegularStepGradientDescentOptimizer.h"
#include "mapITKMattesMutualInformationImageToImageMetric.h"
#include "itkMatrixOffsetBasedTranslationTransform.h"
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
        SealedFixedTransformPolicyMacro< ::itk::MatrixOffsetBasedTranslationTransform<map::core::continuous::ScalarType, TMovingImage::ImageDimension> >,
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
                SealedFixedTransformPolicyMacro< ::itk::MatrixOffsetBasedTranslationTransform<map::core::continuous::ScalarType, TMovingImage::ImageDimension> >,
                SealedImagePyramidesPolicy< ::itk::MultiResolutionPyramidImageFilter<TMovingImage, TMovingImage>, ::itk::MultiResolutionPyramidImageFilter<TTargetImage, TTargetImage>, TPyramideInitializationPolicy >
                >  Superclass;

        using Pointer = ::itk::SmartPointer<Self>;
        using ConstPointer = ::itk::SmartPointer<const Self>;

        itkTypeMacro(ITKTransMattesMIMultiResRegistrationAlgorithm,
                     ITKMultiResImageRegistrationAlgorithm);
        mapNewAlgorithmMacro(Self);

        using ParametersType = ::itk::Array<double>;

        using MetaPropertyType = typename Superclass::MetaPropertyType;
        using MetaPropertyPointer = typename Superclass::MetaPropertyPointer;
        using MetaPropertyNameType = typename Superclass::MetaPropertyNameType;
        using MetaPropertyVectorType = typename Superclass::MetaPropertyVectorType;

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

    }  // namespace boxed
  }  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKTransMattesMIMultiResRegistrationAlgorithm.tpp"
#endif

#endif
