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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/include/mapITKExhaustiveOptimizer.h $
*/




#ifndef __ITK_EXHAUSTIVE_OPTIMIZER_H
#define __ITK_EXHAUSTIVE_OPTIMIZER_H

#include "mapITKOptimizerControl.h"
#include "mapITKSVNLOptimizerControlBase.h"
#include "itkExhaustiveOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*!
			This class is the template specialization for the itk::ExhaustiveOptimizer.
			*@remark The exhaustive optimizer searches for the minimum and maximum
			* in parallel, but the last result it will return is just the last evaluation
			* in the search grid, thus it is normally not one of the two extremas.
			* Therefore the default ITK implementation is somehow able to minimize
			* or maximize but not in a way you would expect in a normal registration
			* process. That is why for this implementation the getter and setter for Minimize/Maximize
			* are only dummies.
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<>
			class ITKOptimizerControl< ::itk::ExhaustiveOptimizer> : public ITKSVNLOptimizerControlBase< ::itk::ExhaustiveOptimizer>
			{
			public:
				typedef ITKOptimizerControl< ::itk::ExhaustiveOptimizer> Self;
				typedef ITKSVNLOptimizerControlBase< ::itk::ExhaustiveOptimizer> Superclass;
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
					return true;
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
					return true; /*dummy; see class description*/
				};

				/**@remark The exhaustive optimizer searches for the minimum and maximum
				 *in parallel, but the last result it will return is just the last evaluation
				 *in the search grid, thus it is normally not one of the two extremas.
				 *Therefore the default ITK implementation is some how able to minimize
				 * or maximize but not in a way you would expect in a normal registration
				 * process.*/
				virtual bool getMaximize() const
				{
					return true; /*dummy; see class description*/
				};

				virtual void setMinimize(bool)
				{
					/*dummy; see class description*/
				};

				virtual void setMaximize(bool)
				{
					/*dummy; see class description*/
				};

				virtual bool hasCurrentValue() const
				{
					return true;
				};

			protected:

				virtual bool doStop()
				{
					_spOptimizer->StopWalking();
					return true;
				};

				virtual IterationCountType doGetCurrentIteration() const
				{
					return 0;
				};

				virtual IterationCountType doGetMaxIterations() const
				{
					return _spOptimizer->GetMaximumNumberOfIterations();
				};

				virtual SVNLMeasureType doGetCurrentMeasure() const
				{
					return _spOptimizer->GetCurrentValue();
				};


				virtual void copyProperties(const ConcreteOptimizerType *source, ConcreteOptimizerType *destination) const
				{
					Superclass::copyProperties(source, destination);

					destination->SetStepLength(source->GetStepLength());
					destination->SetNumberOfSteps(source->GetNumberOfSteps());
				};

				virtual Superclass::Pointer doCloneControl() const
				{
					Pointer spClone = Self::New();
					Superclass::Pointer spResult = spClone.GetPointer();
					return spResult;
				};
			};

			typedef ITKOptimizerControl< ::itk::ExhaustiveOptimizer> ExhaustiveOptimizerControl;

		}
	}
}

#endif
