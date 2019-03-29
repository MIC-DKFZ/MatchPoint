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




#ifndef __ITK_AMOEBA_OPTIMIZER_H
#define __ITK_AMOEBA_OPTIMIZER_H

#include "mapITKOptimizerControl.h"
#include "mapITKSVNLOptimizerControlBase.h"
#include "itkAmoebaOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::AmoebaOptimizer.
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<>
			class ITKOptimizerControl< ::itk::AmoebaOptimizer> : public
				ITKSVNLOptimizerControlBase< ::itk::AmoebaOptimizer>
			{
			public:
				typedef ITKOptimizerControl< ::itk::AmoebaOptimizer> Self;
				typedef ITKSVNLOptimizerControlBase< ::itk::AmoebaOptimizer> Superclass;
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
					return false;/*optimizer cannot be stopped*/
				};

				virtual IterationCountType doGetCurrentIteration() const
				{
					return 0; /*optimizer cannot return*/
				};

				virtual IterationCountType doGetMaxIterations() const
				{
					return _spOptimizer->GetMaximumNumberOfIterations();
				};

				virtual SVNLMeasureType doGetCurrentMeasure() const
				{
					return _spOptimizer->GetCachedValue();
				};

				virtual void copyProperties(const ConcreteOptimizerType* source,
											ConcreteOptimizerType* destination) const
				{
					Superclass::copyProperties(source, destination);

					destination->SetMaximize(source->GetMaximize());
					destination->SetMaximumNumberOfIterations(source->GetMaximumNumberOfIterations());
					destination->SetAutomaticInitialSimplex(source->GetAutomaticInitialSimplex());
					destination->SetOptimizeWithRestarts(source->GetOptimizeWithRestarts());
					destination->SetInitialSimplexDelta(source->GetInitialSimplexDelta());
					destination->SetParametersConvergenceTolerance(source->GetParametersConvergenceTolerance());
					destination->SetFunctionConvergenceTolerance(source->GetFunctionConvergenceTolerance());
				};

				virtual Superclass::Pointer doCloneControl() const
				{
					Pointer spClone = Self::New();
					Superclass::Pointer spResult = spClone.GetPointer();
					return spResult;
				};
			};

			typedef ITKOptimizerControl< ::itk::AmoebaOptimizer> AmoebaOptimizerControl;
		}
	}
}

#endif
