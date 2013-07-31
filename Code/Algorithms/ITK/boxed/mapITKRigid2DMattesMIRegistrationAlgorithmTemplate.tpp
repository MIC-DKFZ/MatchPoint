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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKRigid2DMattesMIRegistrationAlgorithmTemplate.tpp $
*/


#ifndef __MAP_ITK_RIGID2D_MATTES_MI_REGISTRATION_ALGORITHM_TEMPLATE_TPP
#define __MAP_ITK_RIGID2D_MATTES_MI_REGISTRATION_ALGORITHM_TEMPLATE_TPP

#include "mapITKRigid2DMattesMIRegistrationAlgorithmTemplate.h"

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
			         class TInterpolatorPolicy >
			ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        ITKRigid2DMattesMIRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy >
			ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        ~ITKRigid2DMattesMIRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy >
			void
			ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        configureAlgorithm()
			{
				_preInitialize = true;
				_useCenterOfGravity = false;

				typename Superclass::ConcreteOptimizerType::ScalesType scales(3);
				scales[0] = 1.0;
				scales[1] = 1.0 / 1000;
				scales[2] = 1.0 / 1000;

				//optimizer
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetScales(scales);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(2.00);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(0.001);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetNumberOfIterations(200);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetRelaxationFactor(0.8);
				this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetGradientMagnitudeTolerance(1e-4);

				//metric
				this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfHistogramBins(20);
				this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfSpatialSamples(20000);
				this->getConcreteMetricControl()->getConcreteMetric()->ReinitializeSeed();
				this->getConcreteMetricControl()->getConcreteMetric()->UseExplicitPDFDerivativesOn();

				//transform
				this->getConcreteTransformModel()->getConcreteTransform()->SetIdentity();

			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy >
			void
			ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        compileInfos(MetaPropertyVectorType &infos) const
			{
				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::TransformBaseType::ParametersType ParametersType;

#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("TransformParameters", typeid(ParametersType), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("FixedTransformParameters", typeid(ParametersType), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("Scales", typeid(ScalesType), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MaximumStepLength", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("MinimumStepLength", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("RelaxationFactor", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfIterations", typeid(unsigned long), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("GradientMagnitudeTolerance", typeid(double), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfHistogramBins", typeid(unsigned long), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("NumberOfSpatialSamples", typeid(unsigned long), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("UseAllPixels", typeid(bool), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("PreinitTransform", typeid(bool), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("PreinitByCenterOfGravity", typeid(bool), true, true));
#endif
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy >
			typename ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			         TInterpolatorPolicy >::MetaPropertyPointer
			         ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			         TInterpolatorPolicy >::
			         doGetProperty(const MetaPropertyNameType &name) const
			{
				MetaPropertyPointer spResult;
				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::TransformBaseType::ParametersType ParametersType;

				if (name == "TransformParameters")
				{
					spResult = map::core::MetaProperty<ParametersType>::New(this->getTransformInternal()->getTransform()->GetParameters());
				}
				else if (name == "FixedTransformParameters")
				{
					spResult = map::core::MetaProperty<ParametersType>::New(this->getTransformInternal()->getTransform()->GetFixedParameters());
				}
				else if (name == "Scales")
				{
					spResult = map::core::MetaProperty<ScalesType>::New(this->getConcreteITKOptimizer()->GetScales());
				}
				else if (name == "MaximumStepLength")
				{
					spResult = map::core::MetaProperty<double>::New(this->getConcreteITKOptimizer()->GetMaximumStepLength());
				}
				else if (name == "MinimumStepLength")
				{
					spResult = map::core::MetaProperty<double>::New(this->getConcreteITKOptimizer()->GetMinimumStepLength());
				}
				else if (name == "RelaxationFactor")
				{
					spResult = map::core::MetaProperty<double>::New(this->getConcreteITKOptimizer()->GetRelaxationFactor());
				}
				else if (name == "NumberOfIterations")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(this->getConcreteITKOptimizer()->GetNumberOfIterations());
				}
				else if (name == "GradientMagnitudeTolerance")
				{
					spResult = map::core::MetaProperty<double>::New(this->getConcreteITKOptimizer()->GetGradientMagnitudeTolerance());
				}
				else if (name == "NumberOfHistogramBins")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(this->getConcreteMetricControl()->getConcreteMetric()->GetNumberOfHistogramBins());
				}
				else if (name == "NumberOfSpatialSamples")
				{
					spResult = map::core::MetaProperty<unsigned long>::New(this->getConcreteMetricControl()->getConcreteMetric()->GetNumberOfFixedImageSamples());
				}
				else if (name == "UseAllPixels")
				{
					spResult = map::core::MetaProperty<bool>::New(this->getConcreteMetricControl()->getConcreteMetric()->GetUseAllPixels());
				}
				else if (name == "PreinitTransform")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_preInitialize);
				}
				else if (name == "PreinitByCenterOfGravity")
				{
					spResult = map::core::MetaProperty<bool>::New(this->_useCenterOfGravity);
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}


				return spResult;
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy >
			void
			ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty)
			{
				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::TransformBaseType::ParametersType ParametersType;

				if (name == "TransformParameters")
				{
					ParametersType params;
					map::core::unwrapMetaProperty(pProperty, params);
					this->getTransformInternal()->getTransform()->SetParameters(params);
				}
				else if (name == "FixedTransformParameters")
				{
					ParametersType params;
					map::core::unwrapMetaProperty(pProperty, params);
					this->getTransformInternal()->getTransform()->SetFixedParameters(params);
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
				else if (name == "PreinitTransform")
				{
					bool init;
					map::core::unwrapMetaProperty(pProperty, init);
					this->_preInitialize = init;
				}
				else if (name == "PreinitByCenterOfGravity")
				{
					bool init;
					map::core::unwrapMetaProperty(pProperty, init);
					this->_useCenterOfGravity = init;
				}
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}

			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy >
			void
			ITKRigid2DMattesMIRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        prepInitializeTransformation()
			{
				Superclass::prepInitializeTransformation();

				if (this->_preInitialize)
				{
					this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize transform."));

					typedef ::itk::CenteredTransformInitializer<typename Superclass::ConcreteTransformType::TransformType, typename Superclass::TargetImageType, typename Superclass::MovingImageType> InitializerType;

					typename InitializerType::Pointer spInitializer = InitializerType::New();

					spInitializer->SetMovingImage(this->_spInternalMovingImage);
					spInitializer->SetFixedImage(this->_spInternalTargetImage);
					spInitializer->SetTransform(this->getConcreteTransformModel()->getConcreteTransform());

					if (this->_useCenterOfGravity)
					{
						this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize by moments."));
						spInitializer->MomentsOn();
					}
					else
					{
						this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize by image geometry."));
						spInitializer->GeometryOn();
					}

					spInitializer->InitializeTransform();
				}

				typename Superclass::ConcreteTransformType::MatrixType matrix;
				typename Superclass::ConcreteTransformType::OutputVectorType offset;

				this->getConcreteTransformModel()->getAffineMatrixDecomposition(matrix, offset);

				core::OStringStream os;

				os << "Preinitialized transform to: " << this->getConcreteTransformModel()->getConcreteTransform()->GetParameters();
				//set the parameter of the transform model to the current transform parameters of the algorithm
				this->setCurrentTransformParameters(this->getConcreteTransformModel()->getConcreteTransform()->GetParameters());
				this->getInternalRegistrationMethod().SetInitialTransformParameters(this->getConcreteTransformModel()->getConcreteTransform()->GetParameters());

				this->InvokeEvent(events::AlgorithmEvent(this, os.str()));
			};


		}
	}
}

#endif
