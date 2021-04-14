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




#ifndef __ARBITRARY_MVNL_OPTIMIZER_POLICY_H
#define __ARBITRARY_MVNL_OPTIMIZER_POLICY_H

#include "itkCommand.h"

#include "mapITKMVNLOptimizerSetterInterface.h"
#include "mapITKMVNLOptimizerGetterInterface.h"
#include "mapOptimizerGetterInterface.h"
#include "mapModificationTimeValidator.h"
#include "mapMAPAlgorithmsITKExports.h"

#include <mapITKTypeMacroNoParent.h>

namespace map
{
  namespace algorithm
  {
    namespace itk
    {

      /*! @class ArbitraryMVNLOptimizerPolicy
      @brief class for ArbitraryMVNLOptimizerPolicy.

      This class is a ArbitraryMVNLOptimizerPolicy. It is used if an ITKImageRegistrationAlgorithm
      should use an arbitrary multiple valued non linear optimizer (based on itk::MultipleValueNonLinearOptimzer)that is to
      be set by the user (in contrary to FixedMVNLOptimizerPolicy).
      By default the policy will determin the right optimization direction. You can deactivate this feature by setting
      AutomaticOptimizationDirection to false.
      @sa FixedMVNLOptimizerPolicy
      @ingroup ITKPolicies
      */
      class MAPAlgorithmsITK_EXPORT ArbitraryMVNLOptimizerPolicy: public
        facet::ITKMVNLOptimizerSetterInterface, public facet::ITKMVNLOptimizerGetterInterface,
        public facet::OptimizerGetterInterface
      {
      public:
        using Self = ArbitraryMVNLOptimizerPolicy;
        using Superclass = facet::ITKMVNLOptimizerSetterInterface;
        itkTypeMacroNoParent(ArbitraryMVNLOptimizerPolicy);

        using OptimizerControlType = facet::OptimizerGetterInterface::OptimizerControlType;
        using ITKOptimizerControlType = Superclass::ITKOptimizerControlType;

        /*! gets an optimizer control object
        @eguarantee strong
        @return a pointer to an ITKMVNLOptimizerControlInterface object
        */
        OptimizerControlType* getOptimizerControl() override;
        const OptimizerControlType* getOptimizerControl() const override;

        ITKOptimizerControlType* getITKOptimizerControl() override;
        const ITKOptimizerControlType* getITKOptimizerControl() const override;

        void setITKOptimizerControl(ITKOptimizerControlType* pOptimizer) override;

        void setAutomaticOptimizationDirection(bool automatic);
        bool getAutomaticOptimizationDirection() const;

        /*! Returns the modification time of the policy (and its controlled component).
        * In this case the modification time is a pass through of the internal component.
        @eguarantee strong
        @return the modification time
        */
        virtual ::itk::ModifiedTimeType GetMTime() const;

      protected:
        ArbitraryMVNLOptimizerPolicy();
        ~ArbitraryMVNLOptimizerPolicy() override;

        /*! This is a command slot that can be used by any class derivering from this policy
        * to get informed if the component instances is changed. \n
        * Two events will be invoked with this command: \n
        * - UnregisterAlgorithmComponentEvent
        * - RegisterAlgorithmComponentEvent
        * .
        * The first one is used when the current optimizer is going to be replaced (by setOptimizer). The event data in this case
        * is a void pointer to the current (soon outdated) object. The second event will be called when the new optimizer was set
        * (by setOptimizer). In this case the event data is a pointer to the new optimizer.*/
        ::itk::Command::Pointer _spOnChange;

        /*! gets the internal optimizer
        @eguarantee no fail
        @return a pointer to an OptimizerControlType object
        */
        virtual ITKOptimizerControlType* getOptimizerInternal();
        virtual const ITKOptimizerControlType* getOptimizerInternal() const;

        /*! initializes the optimizer
        @eguarantee strong
        */
        void prepareOptimizer();

        /*! initializes the optimizer
        * after it was integrated in a controlling structur (e.g. registration algorithm)
        @eguarantee strong
        */
        void prepareOptimizerAfterAssembly(bool minimizeToOptimize);

      private:
        ITKOptimizerControlType::Pointer _spOptimizerControl;

        /*! The time stamp validator is used to signal changes of the policy that may effect the controlling structur (e.g. registration algorithm)
        * because the controlled object has changed.*/
        mutable core::ModificationTimeValidator _mTime;

        /*! Controlles if the policy sets the optimization automaticaly or
        * if its up to the user to specifiy the direction. Automatic direction
        * detaction will be performed by prepareOptimizerAfterAssembly().*/
        bool _automaticOptimizationDirection{true};

        //No copy constructor allowed
        ArbitraryMVNLOptimizerPolicy(const Self& source) = delete;
        void operator=(const Self&) = delete;  //purposely not implemented
      };

    }  // namespace itk
  }  // namespace algorithm
}  // namespace map

#endif
