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


#ifndef __MAP_ITK_RIGID2D_MS_REGISTRATION_ALGORITHM_TEMPLATE_TPP
#define __MAP_ITK_RIGID2D_MS_REGISTRATION_ALGORITHM_TEMPLATE_TPP

#include "mapITKRigid2DMSRegistrationAlgorithmTemplate.h"

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
			ITKRigid2DMSRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        ITKRigid2DMSRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			           typename TUIDPolicy,
			           class TInterpolatorPolicy >
			ITKRigid2DMSRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        ~ITKRigid2DMSRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			           typename TUIDPolicy,
			           class TInterpolatorPolicy >
			void
			ITKRigid2DMSRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        configureAlgorithm()
			{
				this->_preInitialize = true;
				this->_useCenterOfGravity = false;

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

				//transform
				this->getConcreteTransformModel()->SetIdentity();

			};

			template < class TMovingImage, class TTargetImage,
			           typename TUIDPolicy,
			           class TInterpolatorPolicy >
			void
			ITKRigid2DMSRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);

				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::ParametersType ParametersType;

				#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("TransformParameters", typeid(ParametersType),
				                true, true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("FixedTransformParameters",
				                typeid(ParametersType), true, true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("Scales", typeid(ScalesType), true, true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("MaximumStepLength", typeid(double), true,
				                true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("MinimumStepLength", typeid(double), true,
				                true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("RelaxationFactor", typeid(double), true,
				                true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("NumberOfIterations", typeid(unsigned long),
				                true, true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("GradientMagnitudeTolerance", typeid(double),
				                true, true));
				#endif
			};

			template < class TMovingImage, class TTargetImage,
			           typename TUIDPolicy,
			           class TInterpolatorPolicy >
			typename ITKRigid2DMSRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			         TInterpolatorPolicy >::MetaPropertyPointer
			         ITKRigid2DMSRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			         TInterpolatorPolicy >::
			         doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;
				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::ParametersType ParametersType;

				if (name == "TransformParameters")
				{
					spResult = ::map::core::MetaProperty<ParametersType>::New(
					               this->getTransformInternal()->GetParameters());
				}
				else if (name == "FixedTransformParameters")
				{
					spResult = ::map::core::MetaProperty<ParametersType>::New(
					               this->getTransformInternal()->GetFixedParameters());
				}
				else if (name == "Scales")
				{
					spResult = ::map::core::MetaProperty<ScalesType>::New(this->getConcreteITKOptimizer()->GetScales());
				}
				else if (name == "MaximumStepLength")
				{
					spResult = ::map::core::MetaProperty<double>::New(
					               this->getConcreteITKOptimizer()->GetMaximumStepLength());
				}
				else if (name == "MinimumStepLength")
				{
					spResult = ::map::core::MetaProperty<double>::New(
					               this->getConcreteITKOptimizer()->GetMinimumStepLength());
				}
				else if (name == "RelaxationFactor")
				{
					spResult = ::map::core::MetaProperty<double>::New(
					               this->getConcreteITKOptimizer()->GetRelaxationFactor());
				}
				else if (name == "NumberOfIterations")
				{
					spResult = ::map::core::MetaProperty<unsigned long>::New(
					               this->getConcreteITKOptimizer()->GetNumberOfIterations());
				}
				else if (name == "GradientMagnitudeTolerance")
				{
					spResult = ::map::core::MetaProperty<double>::New(
					               this->getConcreteITKOptimizer()->GetGradientMagnitudeTolerance());
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}


				return spResult;
			};

			template < class TMovingImage, class TTargetImage,
			           typename TUIDPolicy,
			           class TInterpolatorPolicy >
			void
			ITKRigid2DMSRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                        TInterpolatorPolicy >::
			                                        doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				typedef typename Superclass::OptimizerBaseType::OptimizerBaseType::ScalesType ScalesType;
				typedef typename Superclass::TransformBaseType::ParametersType ParametersType;

				if (name == "TransformParameters")
				{
					ParametersType params;
					::map::core::unwrapMetaProperty(pProperty, params);
					this->getTransformInternal()->SetParameters(params);
				}
				else if (name == "FixedTransformParameters")
				{
					ParametersType params;
					::map::core::unwrapMetaProperty(pProperty, params);
					this->getTransformInternal()->SetFixedParameters(params);
				}
				else if (name == "Scales")
				{
					ScalesType scales;
					::map::core::unwrapMetaProperty(pProperty, scales);
					this->getConcreteITKOptimizer()->SetScales(scales);
				}
				else if (name == "MaximumStepLength")
				{
					double length;
					::map::core::unwrapMetaProperty(pProperty, length);
					this->getConcreteITKOptimizer()->SetMaximumStepLength(length);
				}
				else if (name == "MinimumStepLength")
				{
					double length;
					::map::core::unwrapMetaProperty(pProperty, length);
					this->getConcreteITKOptimizer()->SetMinimumStepLength(length);
				}
				else if (name == "RelaxationFactor")
				{
					double factor;
					::map::core::unwrapMetaProperty(pProperty, factor);
					this->getConcreteITKOptimizer()->SetRelaxationFactor(factor);
				}
				else if (name == "NumberOfIterations")
				{
					unsigned long iterations;
					::map::core::unwrapMetaProperty(pProperty, iterations);
					this->getConcreteITKOptimizer()->SetNumberOfIterations(iterations);
				}
				else if (name == "GradientMagnitudeTolerance")
				{
					double tolerance;
					::map::core::unwrapMetaProperty(pProperty, tolerance);
					this->getConcreteITKOptimizer()->SetGradientMagnitudeTolerance(tolerance);
				}
				else
				{
					Superclass::doSetProperty(name, pProperty);
				}
			};

		}
	}
}

#endif
