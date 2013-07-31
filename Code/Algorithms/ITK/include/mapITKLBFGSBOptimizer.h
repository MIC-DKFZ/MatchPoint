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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKLBFGSBOptimizer.h $
*/




#ifndef __ITK_LBFGSB_OPTIMIZER_H
#define __ITK_LBFGSB_OPTIMIZER_H

#include "mapITKOptimizerControl.h"
#include "mapITKSVNLOptimizerControlBase.h"
#include "itkLBFGSBOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::LBFGSBOptimizer.
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<>
			class ITKOptimizerControl< ::itk::LBFGSBOptimizer> : public ITKSVNLOptimizerControlBase< ::itk::LBFGSBOptimizer>
			{
			public:
				typedef ITKOptimizerControl< ::itk::LBFGSBOptimizer> Self;
				typedef ITKSVNLOptimizerControlBase< ::itk::LBFGSBOptimizer> Superclass;
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
				ITKOptimizerControl(const Self &source);
				void operator=(const Self &); //purposely not implemented

			public:
				virtual bool isStoppable() const
				{
					return false;
				};

				virtual bool hasIterationCount() const
				{
					return true;
				};

				virtual bool hasMaxIterationCount() const
				{
					return true;
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
					return _spOptimizer->GetCurrentIteration();
				};

				virtual IterationCountType doGetMaxIterations() const
				{
					return _spOptimizer->GetMaximumNumberOfIterations();
				};

				virtual SVNLMeasureType doGetCurrentMeasure() const
				{
					return _spOptimizer->GetCachedValue();
				};

				virtual void copyProperties(const ConcreteOptimizerType *source, ConcreteOptimizerType *destination) const
				{
					//cast needed because of wrong const correctness in optimizer interface
					ConcreteOptimizerType *nonConstSource = const_cast<ConcreteOptimizerType *>(source);

					destination->SetInitialPosition(source->GetInitialPosition());
					destination->SetTrace(nonConstSource->GetTrace());
					destination->SetLowerBound(nonConstSource->GetLowerBound());
					destination->SetUpperBound(nonConstSource->GetUpperBound());
					destination->SetBoundSelection(nonConstSource->GetBoundSelection());
					destination->SetCostFunctionConvergenceFactor(nonConstSource->GetCostFunctionConvergenceFactor());
					destination->SetProjectedGradientTolerance(nonConstSource->GetProjectedGradientTolerance());
					destination->SetMaximumNumberOfIterations(nonConstSource->GetMaximumNumberOfIterations());
					destination->SetMaximumNumberOfEvaluations(nonConstSource->GetMaximumNumberOfEvaluations());
					destination->SetMaximumNumberOfCorrections(nonConstSource->GetMaximumNumberOfCorrections());
				};

				virtual Superclass::Pointer doCloneControl() const
				{
					Pointer spClone = Self::New();
					Superclass::Pointer spResult = spClone.GetPointer();
					return spResult;
				};
			};

			typedef ITKOptimizerControl< ::itk::LBFGSBOptimizer> LBFGSBOptimizerControl;

		}
	}
}

#endif
