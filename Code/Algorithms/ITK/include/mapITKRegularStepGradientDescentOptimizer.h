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




#ifndef __ITK_REGULAR_STEP_GRADIENT_DESCENT_OPTIMIZER_CONTROL_H
#define __ITK_REGULAR_STEP_GRADIENT_DESCENT_OPTIMIZER_CONTROL_H

#include "mapITKOptimizerControl.h"
#include "mapITKSVNLOptimizerControlBase.h"
#include "itkRegularStepGradientDescentOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::PowellOptimizer.
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<>
			class ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer> : public
				ITKSVNLOptimizerControlBase< ::itk::RegularStepGradientDescentOptimizer>
			{
			public:
				using Self = ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer>;
				using Superclass = ITKSVNLOptimizerControlBase< ::itk::RegularStepGradientDescentOptimizer>;
				using Pointer = ::itk::SmartPointer<Self>;
				using ConstPointer = ::itk::SmartPointer<const Self>;

				itkTypeMacro(ITKOptimizerControl, ITKSVNLOptimizerControlBase);
				itkNewMacro(Self);

				using ConcreteOptimizerType = Superclass::ConcreteOptimizerType;
				using ConcreteOptimizerPointer = ConcreteOptimizerType::Pointer;

			protected:
				~ITKOptimizerControl() override = default;
				ITKOptimizerControl() = default;

			private:
				//No copy constructor allowed
				ITKOptimizerControl(const Self& source) = delete;
				void operator=(const Self&) = delete;  //purposely not implemented

			public:
				bool isStoppable() const override
				{
					return true;
				};

				bool hasIterationCount() const override
				{
					return true;
				};

				bool hasMaxIterationCount() const override
				{
					return true;
				};

				bool hasCurrentValue() const override
				{
					return true;
				};

				bool canMinimize() const override
				{
					return true;
				};

				bool canMaximize() const override
				{
					return true;
				};

				bool getMinimize() const override
				{
					return _spOptimizer->GetMinimize();
				};

				bool getMaximize() const override
				{
					return _spOptimizer->GetMaximize();
				};

				void setMinimize(bool minimize) override
				{
					_spOptimizer->SetMinimize(minimize);
				};

				void setMaximize(bool maximize) override
				{
					_spOptimizer->SetMaximize(maximize);
				};

			protected:

				bool doStop() override
				{
					_spOptimizer->StopOptimization();
					return true;
				};

				IterationCountType doGetCurrentIteration() const override
				{
					return _spOptimizer->GetCurrentIteration();
				};

				IterationCountType doGetMaxIterations() const override
				{
					return _spOptimizer->GetNumberOfIterations();
				};

				SVNLMeasureType doGetCurrentMeasure() const override
				{
					return _spOptimizer->GetValue();
				};

				void copyProperties(const ConcreteOptimizerType* source,
											ConcreteOptimizerType* destination) const override
				{
					Superclass::copyProperties(source, destination);

					destination->SetMaximize(source->GetMaximize());
					destination->SetMaximumStepLength(source->GetMaximumStepLength());
					destination->SetMinimumStepLength(source->GetMinimumStepLength());
					destination->SetRelaxationFactor(source->GetRelaxationFactor());
					destination->SetNumberOfIterations(source->GetNumberOfIterations());
					destination->SetGradientMagnitudeTolerance(source->GetGradientMagnitudeTolerance());
				};

				Superclass::Pointer doCloneControl() const override
				{
					Pointer spClone = Self::New();
					Superclass::Pointer spResult = spClone.GetPointer();
					return spResult;
				};
			};

			using RegularStepGradientDescentOptimizerControl = ITKOptimizerControl< ::itk::RegularStepGradientDescentOptimizer>;
		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#endif
