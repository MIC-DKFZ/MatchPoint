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




#ifndef __ITK_LEVENBERG_MARQUARDT_OPTIMIZER_H
#define __ITK_LEVENBERG_MARQUARDT_OPTIMIZER_H

#include "mapITKOptimizerControl.h"
#include "mapITKMVNLOptimizerControlBase.h"
#include "mapAlgorithmException.h"

#include "itkLevenbergMarquardtOptimizer.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{
			using LightObject = ::itk::LightObject;
			template<class T> using ObjectFactory = ::itk::ObjectFactory<T>;

			/*!
			This class is the template specialization for the itk::LevenbergMarquardtOptimizer.
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<>
			class ITKOptimizerControl< ::itk::LevenbergMarquardtOptimizer> : public
				ITKMVNLOptimizerControlBase< ::itk::LevenbergMarquardtOptimizer>
			{
			public:
				typedef ITKOptimizerControl< ::itk::LevenbergMarquardtOptimizer> Self;
				typedef ITKMVNLOptimizerControlBase< ::itk::LevenbergMarquardtOptimizer> Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKOptimizerControl, ITKMVNLOptimizerControlBase);
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
					return false;
				};

				virtual bool getMinimize() const
				{
					return true;
				};

				virtual bool getMaximize() const
				{
					return false;
				};

				virtual void setMinimize(bool minimize)
				{
					if (!minimize)
					{
						mapExceptionMacro(AlgorithmException,
										  << "Error. VNL implementation of Levenberg-Marquart optimizer does only minimization. Try to set to maximize.");
					}
				};

				virtual void setMaximize(bool maximize)
				{
					if (maximize)
					{
						mapExceptionMacro(AlgorithmException,
										  << "Error. VNL implementation of Levenberg-Marquart optimizer does only minimization. Try to set to maximize.");
					}
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
					if (_spOptimizer->GetOptimizer())
					{
						return _spOptimizer->GetOptimizer()->get_num_iterations();
					}
					else
					{
						return 0;
					}
				};

				virtual IterationCountType doGetMaxIterations() const
				{
					if (_spOptimizer->GetOptimizer())
					{
						return _spOptimizer->GetOptimizer()->get_max_function_evals();
					}
					else
					{
						return 0;
					}
				};

				virtual MVNLMeasureType doGetCurrentMeasure() const
				{
					return _spOptimizer->GetCachedValue();
				};

				virtual void copyProperties(const ConcreteOptimizerType* source,
											ConcreteOptimizerType* destination) const
				{
					mapDefaultExceptionMacro( <<
											  "Error cannot clone Levenberg Marquardt optimizer. Cannot get internals (protected properties).");
				};

				virtual Superclass::Pointer doCloneControl() const
				{
					Pointer spClone = Self::New();
					Superclass::Pointer spResult = spClone.GetPointer();
					return spResult;
				};
			};

			typedef ITKOptimizerControl< ::itk::LevenbergMarquardtOptimizer> LevenbergMarquardtOptimizerControl;

		}
	}
}

#endif
