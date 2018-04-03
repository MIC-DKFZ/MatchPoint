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




#ifndef __ITK_LBFGS_OPTIMIZER_H
#define __ITK_LBFGS_OPTIMIZER_H

#include "mapITKOptimizerControl.h"
#include "mapITKSVNLOptimizerControlBase.h"
#include "itkLBFGSOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::LBFGSOptimizer.
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<>
			class ITKOptimizerControl< ::itk::LBFGSOptimizer> : public
				ITKSVNLOptimizerControlBase< ::itk::LBFGSOptimizer>
			{
			public:
				typedef ITKOptimizerControl< ::itk::LBFGSOptimizer> Self;
				typedef ITKSVNLOptimizerControlBase< ::itk::LBFGSOptimizer> Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKOptimizerControl, ITKSVNLOptimizerControlBase);
				itkNewMacro(Self);

				typedef Superclass::ConcreteOptimizerType ConcreteOptimizerType;
				typedef ConcreteOptimizerType::Pointer ConcreteOptimizerPointer;

			protected:
				virtual ~ITKOptimizerControl() {};
				ITKOptimizerControl() {};

			private:
				//No copy constructor allowed
				ITKOptimizerControl(const Self& source);
				void operator=(const Self&);  //purposely not implemented

			public:
				virtual bool isStoppable() const
				{
					return false;
				};

				virtual bool hasIterationCount() const
				{
					return false;
				};

				virtual bool hasMaxIterationCount() const
				{
					return false;
				};

				virtual bool canMinimize() const
				{
					return true;
				};

				virtual bool canMaximize() const
				{
					return true;
				};

				virtual bool getMinimize() const
				{
					return _spOptimizer->GetMinimize();
				};

				virtual bool getMaximize() const
				{
					return _spOptimizer->GetMaximize();
				};

				virtual void setMinimize(bool minimize)
				{
					_spOptimizer->SetMinimize(minimize);
				};

				virtual void setMaximize(bool maximize)
				{
					_spOptimizer->SetMaximize(maximize);
				};

				virtual bool hasCurrentValue() const
				{
					return true;
				};

			protected:

				virtual bool doStop()
				{
					return false;
				};

				virtual IterationCountType doGetCurrentIteration() const
				{
					return 0;
				};

				virtual IterationCountType doGetMaxIterations() const
				{
					return 0;
				};

				virtual SVNLMeasureType doGetCurrentMeasure() const
				{
					return _spOptimizer->GetCachedValue();
				};

				virtual void copyProperties(const ConcreteOptimizerType* source,
											ConcreteOptimizerType* destination) const
				{
					Superclass::copyProperties(source, destination);

					//cast needed because of wrong const correctness in optimizer interface
					ConcreteOptimizerType* nonConstSource = const_cast<ConcreteOptimizerType*>(source);

					destination->SetTrace(nonConstSource->GetTrace());
					destination->SetMaximumNumberOfFunctionEvaluations(
						nonConstSource->GetMaximumNumberOfFunctionEvaluations());
					destination->SetGradientConvergenceTolerance(nonConstSource->GetGradientConvergenceTolerance());
					destination->SetLineSearchAccuracy(nonConstSource->GetLineSearchAccuracy());
					destination->SetDefaultStepLength(nonConstSource->GetDefaultStepLength());
				};

				virtual Superclass::Pointer doCloneControl() const
				{
					Pointer spClone = Self::New();
					Superclass::Pointer spResult = spClone.GetPointer();
					return spResult;
				};
			};

			typedef ITKOptimizerControl< ::itk::LBFGSOptimizer> LBFGSOptimizerControl;

		}
	}
}

#endif
