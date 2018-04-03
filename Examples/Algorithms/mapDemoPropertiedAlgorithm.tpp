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

//----------------------------------------------------------
// !!!EXPERIMENTAL CODE!!!
//
// This code may not be used for release.
// Add #define SIDT_ENFORCE_MATURE_CODE to any release module
// to ensure this policy.
//----------------------------------------------------------


#ifdef SIDT_ENFORCE_MATURE_CODE
#error "This code is marked as experimental code. It must not be used because this build enforces mature code."
#endif
#ifndef SIDT_CONTAINS_EXPERIMENTAL_CODE
#define SIDT_CONTAINS_EXPERIMENTAL_CODE 1
#endif

#ifndef __MAP_DEMO_PROPERTIED_ALGORITHM_TEMPLATE_TPP
#define __MAP_DEMO_PROPERTIED_ALGORITHM_TEMPLATE_TPP


#include <assert.h>

#include "mapDemoPropertiedAlgorithm.h"

#include "mapMetaProperty.h"
#include "mapMetaPropertyAccessor.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			template <class TMovingImage, class TTargetImage, typename TUIDPolicy>
			DemoPropertiedAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>::
			DemoPropertiedAlgorithm()
			{};

			template <class TMovingImage, class TTargetImage, typename TUIDPolicy>
			DemoPropertiedAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>::
			~DemoPropertiedAlgorithm()
			{};

			template <class TMovingImage, class TTargetImage, typename TUIDPolicy>
			void
			DemoPropertiedAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>::
			compileInfos(MetaPropertyVectorType& infos) const
			{
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("TransformParameters", typeid(ParametersType),
								true, true));
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
#endif
			};

			template <class TMovingImage, class TTargetImage, typename TUIDPolicy>
			typename DemoPropertiedAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>::MetaPropertyPointer
			DemoPropertiedAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>::
			doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "TransformParameters")
				{
					spResult = map::core::MetaProperty<ParametersType>::New(
								   this->getTransformInternal()->GetParameters());
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
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}

				return spResult;
			};

			template <class TMovingImage, class TTargetImage, typename TUIDPolicy>
			void
			DemoPropertiedAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>::
			doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "TransformParameters")
				{
					ParametersType params;
					map::core::unwrapMetaProperty(pProperty, params);
					this->getTransformInternal()->SetParameters(params);
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
				else
				{
					assert(false); //any other property name should have been excluded by the calling function.
				}
			};

		}
	}
}


#endif
