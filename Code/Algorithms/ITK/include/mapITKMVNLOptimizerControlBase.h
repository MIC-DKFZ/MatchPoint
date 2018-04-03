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




#ifndef __ITK_MVNL_OPTIMIZER_CONTROL_BASE_H
#define __ITK_MVNL_OPTIMIZER_CONTROL_BASE_H

#include "mapITKMVNLOptimizerControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKMVNLOptimizerControlBase
			This class serves as base class for all
			template specialization of itk optimizers that are single valued non linear optimizers.
			It realizes some basic optimizer handling, to reduce the code in the control classes
			@remark ITKOptimizerControl instantiates a concrete optimizer when constructed. You can set
			a new one, but ITKMVNLOptimizerControlBase has always an optimizer under control.
			@template TConcreteOptimizer type of the concrete optimizer controlled by the class
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<class TConcreteOptimizer>
			class ITKMVNLOptimizerControlBase : public ITKMVNLOptimizerControlInterface
			{
			public:
				typedef ITKMVNLOptimizerControlBase<TConcreteOptimizer> Self;
				typedef ITKMVNLOptimizerControlInterface    Superclass;
				typedef ::itk::SmartPointer<Self>         Pointer;
				typedef ::itk::SmartPointer<const Self>   ConstPointer;

				itkTypeMacro(ITKMVNLOptimizerControlBase, ITKMVNLOptimizerControlInterface);

				typedef TConcreteOptimizer ConcreteOptimizerType;
				typedef typename ConcreteOptimizerType::Pointer ConcreteOptimizerPointer;
				typedef ITKMVNLOptimizerControlInterface BaseInterfaceType;

				/*! setter for the optimizer
				@eguarantee no fail
				@param pOptimizer the OptimizerType object that has to be set. Must not be NULL (otherwise an exception will be thrown).
				*/
				virtual void setOptimizer(ConcreteOptimizerType* pOptimizer);

				virtual OptimizerBaseType* getOptimizer();
				virtual const OptimizerBaseType* getOptimizer() const;

				virtual MVNLOptimizerBaseType* getMVNLOptimizer();
				virtual const MVNLOptimizerBaseType* getMVNLOptimizer() const;

				virtual ConcreteOptimizerType* getConcreteOptimizer();
				virtual const ConcreteOptimizerType* getConcreteOptimizer() const;

				/*! The modification time (MT) of an optimizer controler is the the maximum of his MT
				 * and the MT of the controlled optimizer.  */
				virtual unsigned long GetMTime() const;

				virtual bool hasCurrentPosition() const;

				virtual bool hasScales() const;

				/*! clones the optimizer control and the controlled optimizer.
				 * This implementation generates an instance of ConcreteOptimizerType and uses
				 * copyProperties() to transfer the settings. Reimplement copyProperties() to
				 * realize special settings transfer.
				 * @remark: The function guarantees that all settings of controlled optimizer
				 * are cloned, but its optimization state must not be cloned as well. Thus the function
				 * guarantees the same like instancing the same class again and transferring all properties
				 * of the source instance to the destination instance via setter and getter.
				 * @remark: It is a "deep" copy,so the controlled optimizer is a new instance as well.
				 * @eguarantee strong
				 * @remark Implement the function for special optimizer control classes.
				 * @return Smartpointer to the cloned optimizer control.*/
				virtual ITKOptimizerControlInterface::Pointer clone() const;

			protected:

				/*! Method is called by clone() to transfer the properties between the cloned
				 * optimizer and the source.
				 * @remark this base implementation copies the scales and the initial position.*/
				virtual void copyProperties(const ConcreteOptimizerType* source,
											ConcreteOptimizerType* destination) const;

				/*! Method is called by clone() to clone the concrete control type derivated from this class. */
				virtual Pointer doCloneControl() const = 0;

				virtual OptimizerPositionType doGetCurrentPosition() const;

				virtual OptimizerScalesType doGetScales() const;

				virtual ~ITKMVNLOptimizerControlBase();
				ITKMVNLOptimizerControlBase();

				ConcreteOptimizerPointer _spOptimizer;

			private:
				//No copy constructor allowed
				ITKMVNLOptimizerControlBase(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};
		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKMVNLOptimizerControlBase.tpp"
#endif

#endif
