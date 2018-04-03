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


#ifndef __ITK_MVNL_OPTIMIZER_CONTROL_BASE_TPP
#define __ITK_MVNL_OPTIMIZER_CONTROL_BASE_TPP

#include "mapExceptionObjectMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{
			template<class TConcreteOptimizer>
			void
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			setOptimizer(ConcreteOptimizerType* pOptimizer)
			{
				if (!pOptimizer)
				{
					mapDefaultExceptionMacro( << "Cannot set optimizer. Passe pointer to optimizer is NULL");
				}

				_spOptimizer = pOptimizer;
				this->Modified();
			}

			template<class TConcreteOptimizer>
			unsigned long
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			GetMTime() const
			{
				unsigned long mt = Superclass::GetMTime();

				if (mt < _spOptimizer->GetMTime())
				{
					mt = _spOptimizer->GetMTime();
				}

				return mt;
			};

			template<class TConcreteOptimizer>
			bool
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			hasCurrentPosition() const
			{
				return true;
			};

			template<class TConcreteOptimizer>
			typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::OptimizerPositionType
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			doGetCurrentPosition() const
			{
				OptimizerPositionType result = _spOptimizer->GetCurrentPosition();

				return result;
			};

			template<class TConcreteOptimizer>
			bool
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			hasScales() const
			{
				return true;
			};

			template<class TConcreteOptimizer>
			typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::OptimizerScalesType
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			doGetScales() const
			{
				OptimizerScalesType result = _spOptimizer->GetScales();

				return result;
			};

			template<class TConcreteOptimizer>
			typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::MVNLOptimizerBaseType*
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			getMVNLOptimizer()
			{
				return _spOptimizer.GetPointer();
			};

			template<class TConcreteOptimizer>
			const typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::MVNLOptimizerBaseType*
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			getMVNLOptimizer() const
			{
				return _spOptimizer.GetPointer();
			};

			template<class TConcreteOptimizer>
			typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::OptimizerBaseType*
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			getOptimizer()
			{
				return _spOptimizer.GetPointer();
			};

			template<class TConcreteOptimizer>
			const typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::OptimizerBaseType*
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			getOptimizer() const
			{
				return _spOptimizer.GetPointer();
			};

			template<class TConcreteOptimizer>
			typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::ConcreteOptimizerType*
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			getConcreteOptimizer()
			{
				return _spOptimizer.GetPointer();
			};

			template<class TConcreteOptimizer>
			const typename ITKMVNLOptimizerControlBase<TConcreteOptimizer>::ConcreteOptimizerType*
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			getConcreteOptimizer() const
			{
				return _spOptimizer.GetPointer();
			};

			template<class TConcreteOptimizer>
			ITKOptimizerControlInterface::Pointer
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			clone() const
			{
				Pointer spClone = this->doCloneControl();

				this->copyProperties(_spOptimizer, spClone->getConcreteOptimizer());

				ITKOptimizerControlInterface::Pointer spResult = spClone.GetPointer();
				return spResult;
			};

			template<class TConcreteOptimizer>
			void
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			copyProperties(const ConcreteOptimizerType* source, ConcreteOptimizerType* destination) const
			{
				destination->SetInitialPosition(source->GetInitialPosition());
				destination->SetScales(source->GetScales());
				destination->SetUseCostFunctionGradient(source->GetUseCostFunctionGradient());
			};

			template<class TConcreteOptimizer>
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			~ITKMVNLOptimizerControlBase()
			{
			}

			template<class TConcreteOptimizer>
			ITKMVNLOptimizerControlBase<TConcreteOptimizer>::
			ITKMVNLOptimizerControlBase()
			{
				_spOptimizer = ConcreteOptimizerType::New();
			}

		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
