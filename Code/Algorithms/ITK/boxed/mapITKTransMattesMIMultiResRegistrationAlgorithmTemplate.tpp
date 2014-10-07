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


#ifndef __MAP_ITK_TRANS_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_TPP
#define __MAP_ITK_TRANS_MATTES_MI_MULTI_RES_REGISTRATION_ALGORITHM_TEMPLATE_TPP

#include "mapITKTransMattesMIMultiResRegistrationAlgorithmTemplate.h"

#include "mapMetaProperty.h"
#include "mapMetaPropertyAccessor.h"

#include "itkCenteredTransformInitializer.h"

#include <assert.h>

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			template < class TMovingImage, class TTargetImage,
					 typename TUIDPolicy,
					 class TInterpolatorPolicy,
					 class TPyramideInitializationPolicy >
			ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
															TInterpolatorPolicy,
															TPyramideInitializationPolicy >::
															ITKTransMattesMIMultiResRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
					 typename TUIDPolicy,
					 class TInterpolatorPolicy,
					 class TPyramideInitializationPolicy >
			ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
															TInterpolatorPolicy,
															TPyramideInitializationPolicy >::
															~ITKTransMattesMIMultiResRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
					 typename TUIDPolicy,
					 class TInterpolatorPolicy,
					 class TPyramideInitializationPolicy >
			void
			ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
															TInterpolatorPolicy,
															TPyramideInitializationPolicy >::
															configureAlgorithm()
			{
				Superclass::configureAlgorithm();

				this->setResolutionLevels(3);

				typename Superclass::ConcreteOptimizerType::ScalesType scales(TMovingImage::ImageDimension);
				scales.Fill(1.0);

				this->getConcreteTransformModel()->getConcreteTransform()->SetIdentity();
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetScales(scales);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(4.00);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(0.01);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetNumberOfIterations(200);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetRelaxationFactor(0.5);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetGradientMagnitudeTolerance(1e-4);

				this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfHistogramBins(20);
				this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfSpatialSamples(20000);
				this->getConcreteMetricControl()->getConcreteMetric()->ReinitializeSeed();
				this->getConcreteMetricControl()->getConcreteMetric()->UseExplicitPDFDerivativesOn();
			};

			template < class TMovingImage, class TTargetImage,
					 typename TUIDPolicy,
					 class TInterpolatorPolicy,
					 class TPyramideInitializationPolicy >
			void
			ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
															TInterpolatorPolicy,
															TPyramideInitializationPolicy >::
															compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);

				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::TransformBaseType::ParametersType ParametersType;

#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("TransformParameters", typeid(ParametersType),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Scales", typeid(ScalesType), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumStepLength", typeid(double), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MinimumStepLength", typeid(double), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("RelaxationFactor", typeid(double), true,
								true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfIterations", typeid(unsigned long),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientMagnitudeTolerance", typeid(double),
								true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfHistogramBins",
								typeid(unsigned long), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfSpatialSamples",
								typeid(unsigned long), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseAllPixels", typeid(bool), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("ResolutionLevels",
								typeid(typename Superclass::ResolutionLevelCountType), true, true));
#endif
			};

			template < class TMovingImage, class TTargetImage,
					 typename TUIDPolicy,
					 class TInterpolatorPolicy,
					 class TPyramideInitializationPolicy >
			typename ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
					 TInterpolatorPolicy,
					 TPyramideInitializationPolicy >::MetaPropertyPointer
					 ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
					 TInterpolatorPolicy,
					 TPyramideInitializationPolicy >::
					 doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;
				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::TransformBaseType::ParametersType ParametersType;

				if (name == "TransformParameters")
				{
					spResult = map::core::MetaProperty<ParametersType>::New(
								   this->getTransformInternal()->getTransform()->GetParameters());
				}
				else if (name == "Scales")
				{
					spResult = map::core::MetaProperty<ScalesType>::New(this->getConcreteITKOptimizer()->GetScales());
				}
				else if (name == "MaximumStepLength")
				{
					spResult = map::core::MetaProperty<double>::New(
								   this->getConcreteITKOptimizer()->GetMaximumStepLength());
				}
				else if (name == "MinimumStepLength")
				{
					spResult = map::core::MetaProperty<double>::New(
								   this->getConcreteITKOptimizer()->GetMinimumStepLength());
				}
				else if (name == "RelaxationFactor")
				{
					spResult = map::core::MetaProperty<double>::New(
								   this->getConcreteITKOptimizer()->GetRelaxationFactor());
				}
				else if (name == "NumberOfIterations")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(
								   this->getConcreteITKOptimizer()->GetNumberOfIterations());
				}
				else if (name == "GradientMagnitudeTolerance")
				{
					spResult = map::core::MetaProperty<double>::New(
								   this->getConcreteITKOptimizer()->GetGradientMagnitudeTolerance());
				}
				else if (name == "NumberOfHistogramBins")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(
								   this->getConcreteMetricControl()->getConcreteMetric()->GetNumberOfHistogramBins());
				}
				else if (name == "NumberOfSpatialSamples")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(
								   this->getConcreteMetricControl()->getConcreteMetric()->GetNumberOfFixedImageSamples());
				}
				else if (name == "UseAllPixels")
				{
					spResult = map::core::MetaProperty<bool>::New(
								   this->getConcreteMetricControl()->getConcreteMetric()->GetUseAllPixels());
				}
				else if (name == "ResolutionLevels")
				{
					spResult = map::core::MetaProperty<typename Superclass::ResolutionLevelCountType>::New(
								   this->getResolutionLevels());
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}


				return spResult;
			};

			template < class TMovingImage, class TTargetImage,
					 typename TUIDPolicy,
					 class TInterpolatorPolicy,
					 class TPyramideInitializationPolicy >
			void
			ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
															TInterpolatorPolicy,
															TPyramideInitializationPolicy >::
															doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::TransformBaseType::ParametersType ParametersType;

				if (name == "TransformParameters")
				{
					ParametersType params;
					map::core::unwrapMetaProperty(pProperty, params);
					this->getTransformInternal()->getTransform()->SetParameters(params);
				}
				else if (name == "Scales")
				{
					ScalesType scales;
					map::core::unwrapMetaProperty(pProperty, scales);
					this->getConcreteITKOptimizer()->SetScales(scales);
				}
				else if (name == "MaximumStepLength")
				{
					double length;
					map::core::unwrapMetaProperty(pProperty, length);
					this->getConcreteITKOptimizer()->SetMaximumStepLength(length);
				}
				else if (name == "MinimumStepLength")
				{
					double length;
					map::core::unwrapMetaProperty(pProperty, length);
					this->getConcreteITKOptimizer()->SetMinimumStepLength(length);
				}
				else if (name == "RelaxationFactor")
				{
					double factor;
					map::core::unwrapMetaProperty(pProperty, factor);
					this->getConcreteITKOptimizer()->SetRelaxationFactor(factor);
				}
				else if (name == "NumberOfIterations")
				{
					unsigned long iterations;
					map::core::unwrapMetaProperty(pProperty, iterations);
					this->getConcreteITKOptimizer()->SetNumberOfIterations(iterations);
				}
				else if (name == "GradientMagnitudeTolerance")
				{
					double tolerance;
					map::core::unwrapMetaProperty(pProperty, tolerance);
					this->getConcreteITKOptimizer()->SetGradientMagnitudeTolerance(tolerance);
				}
				else if (name == "NumberOfHistogramBins")
				{
					unsigned long nr;
					map::core::unwrapMetaProperty(pProperty, nr);
					this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfHistogramBins(nr);
				}
				else if (name == "NumberOfSpatialSamples")
				{
					unsigned long nr;
					map::core::unwrapMetaProperty(pProperty, nr);
					this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfSpatialSamples(nr);
				}
				else if (name == "UseAllPixels")
				{
					bool useAll;
					map::core::unwrapMetaProperty(pProperty, useAll);
					this->getConcreteMetricControl()->getConcreteMetric()->SetUseAllPixels(useAll);
				}
				else if (name == "ResolutionLevels")
				{
					typename Superclass::ResolutionLevelCountType lvls;
					map::core::unwrapMetaProperty(pProperty, lvls);
					this->setResolutionLevels(lvls);
				}
				else
				{
					Superclass::doSetProperty(name, pProperty);
				}

			};

			template < class TMovingImage, class TTargetImage,
					 typename TUIDPolicy,
					 class TInterpolatorPolicy,
					 class TPyramideInitializationPolic >
			void
			ITKTransMattesMIMultiResRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
															TInterpolatorPolicy,
															TPyramideInitializationPolic >::
															doInterLevelSetup()
			{
				if (this->getCurrentLevel() > 0)
				{
					this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(
						this->getConcreteOptimizerControl()->getConcreteOptimizer()->GetCurrentStepLength() * 2.0);
					this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(
						this->getConcreteOptimizerControl()->getConcreteOptimizer()->GetMinimumStepLength() / 10.0);
				}
			};

		}
	}
}

#endif
