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




#ifndef __ITK_SVNL_OPTIMIZER_CONTROL_BASE_H
#define __ITK_SVNL_OPTIMIZER_CONTROL_BASE_H

#include "mapITKSVNLOptimizerControlInterface.h"

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKSVNLOptimizerControlBase
			This class serves as base class for all
			template specialization of itk optimizers that are single valued non linear optimizers.
			It realizes some basic optimizer handling, to reduce the code in the control classes
			@remark ITKOptimizerControl instantiates a concrete optimizer when constructed. You can set
			a new one, but ITKSVNLOptimizerControlBase has always an optimizer under control.
			@template TConcreteOptimizer type of the concrete optimizer controlled by the class
			@ingroup ITK
			@ingroup OptimizerControl
			*/
			template<class TConcreteOptimizer>
			class ITKSVNLOptimizerControlBase : public ITKSVNLOptimizerControlInterface
			{
			public:
				using Self = ITKSVNLOptimizerControlBase<TConcreteOptimizer>;
				using Superclass = ITKSVNLOptimizerControlInterface;
				using Pointer = ::itk::SmartPointer<Self>;
				using ConstPointer = ::itk::SmartPointer<const Self>;

				itkTypeMacro(ITKSVNLOptimizerControlBase, ITKSVNLOptimizerControlInterface);

				using ConcreteOptimizerType = TConcreteOptimizer;
				using ConcreteOptimizerPointer = typename ConcreteOptimizerType::Pointer;
				using BaseInterfaceType = ITKSVNLOptimizerControlInterface;

				/*! setter for the optimizer
				@eguarantee no fail
				@param pOptimizer the OptimizerType object that has to be set. Must not be NULL (otherwise an exception will be thrown).
				*/
				virtual void setOptimizer(ConcreteOptimizerType* pOptimizer);

				OptimizerBaseType* getOptimizer() override;
				const OptimizerBaseType* getOptimizer() const override;

				SVNLOptimizerBaseType* getSVNLOptimizer() override;
				const SVNLOptimizerBaseType* getSVNLOptimizer() const override;

				virtual ConcreteOptimizerType* getConcreteOptimizer();
				virtual const ConcreteOptimizerType* getConcreteOptimizer() const;

				/*! The modification time (MT) of an optimizer controler is the the maximum of his MT
				 * and the MT of the controlled optimizer.  */
				unsigned long GetMTime() const override;

				bool hasCurrentPosition() const override;

				bool hasScales() const override;

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
				ITKOptimizerControlInterface::Pointer clone() const override;

			protected:

				/*! Method is called by clone() to transfer the properties between the cloned
				 * optimizer and the source.
				 * @remark this base implementation copies the scales and the initial position.*/
				virtual void copyProperties(const ConcreteOptimizerType* source,
											ConcreteOptimizerType* destination) const;

				/*! Method is called by clone() to clone the concrete control type derivated from this class. */
				virtual Pointer doCloneControl() const = 0;

				OptimizerPositionType doGetCurrentPosition() const override;

				OptimizerScalesType doGetScales() const override;

				~ITKSVNLOptimizerControlBase() override;
				ITKSVNLOptimizerControlBase();

				ConcreteOptimizerPointer _spOptimizer;

			private:
				//No copy constructor allowed
				ITKSVNLOptimizerControlBase(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};
		}  // namespace itk
	}  // namespace algorithm
}  // namespace map

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKSVNLOptimizerControlBase.tpp"
#endif

#endif
