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
// @version $Revision: 303 $ (last changed revision)
// @date    $Date: 2013-09-19 18:06:33 +0200 (Do, 19 Sep 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKInitializedImageRegistrationAlgorithm.tpp $
*/


#ifndef __MAP_ITK_INITIALIZING_IMAGE_REGISTRATION_ALGORITHM_TPP
#define __MAP_ITK_INITIALIZING_IMAGE_REGISTRATION_ALGORITHM_TPP

#include "mapITKInitializedImageRegistrationAlgorithm.h"

#include "mapMetaProperty.h"
#include "mapMetaPropertyAccessor.h"

#include "itkCenteredTransformInitializer.h"

#include <assert.h>

namespace map
{
  namespace algorithm
  {
    namespace boxed
    {

      template < class TMovingImage, class TTargetImage,
      class TIdentificationPolicy,
      class TInterpolatorPolicy,
      class TMetricInitializationPolicy,
      class TOptimizerInitializationPolicy,
      class TTransformInitializationPolicy,
      class TInternalRegistrationMethod>
        ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::
        ITKInitializedImageRegistrationAlgorithm()
      {
      };

      template < class TMovingImage, class TTargetImage,
      class TIdentificationPolicy,
      class TInterpolatorPolicy,
      class TMetricInitializationPolicy,
      class TOptimizerInitializationPolicy,
      class TTransformInitializationPolicy,
      class TInternalRegistrationMethod>
        ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::
        ~ITKInitializedImageRegistrationAlgorithm()
      {
      };

      template < class TMovingImage, class TTargetImage,
      class TIdentificationPolicy,
      class TInterpolatorPolicy,
      class TMetricInitializationPolicy,
      class TOptimizerInitializationPolicy,
      class TTransformInitializationPolicy,
      class TInternalRegistrationMethod>
        void
        ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::
        configureAlgorithm()
      {
        _preInitialize = false;
        _useCenterOfGravity = false;
      };

      template < class TMovingImage, class TTargetImage,
      class TIdentificationPolicy,
      class TInterpolatorPolicy,
      class TMetricInitializationPolicy,
      class TOptimizerInitializationPolicy,
      class TTransformInitializationPolicy,
      class TInternalRegistrationMethod>
        void
        ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::
        compileInfos(MetaPropertyVectorType& infos) const
      {
#ifndef MAP_SEAL_ALGORITHMS
        infos.push_back(map::algorithm::MetaPropertyInfo::New("PreinitTransform", typeid(bool), true,
          true));
        infos.push_back(map::algorithm::MetaPropertyInfo::New("PreinitByCenterOfGravity", typeid(bool),
          true, true));
#endif
      };

      template < class TMovingImage, class TTargetImage,
      class TIdentificationPolicy,
      class TInterpolatorPolicy,
      class TMetricInitializationPolicy,
      class TOptimizerInitializationPolicy,
      class TTransformInitializationPolicy,
      class TInternalRegistrationMethod>
        typename 			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::MetaPropertyPointer
        ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::
        doGetProperty(const MetaPropertyNameType& name) const
      {
        MetaPropertyPointer spResult;

        if (name == "PreinitTransform")
        {
          spResult = map::core::MetaProperty<bool>::New(this->_preInitialize);
        }
        else if (name == "PreinitByCenterOfGravity")
        {
          spResult = map::core::MetaProperty<bool>::New(this->_useCenterOfGravity);
        }
        else
        {
          assert(false); //any other property name should have been excluded by the calling function.
        }

        return spResult;
      };

      template < class TMovingImage, class TTargetImage,
      class TIdentificationPolicy,
      class TInterpolatorPolicy,
      class TMetricInitializationPolicy,
      class TOptimizerInitializationPolicy,
      class TTransformInitializationPolicy,
      class TInternalRegistrationMethod>
        void
        ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::
        doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
      {
        if (name == "PreinitTransform")
        {
          bool init;
          map::core::unwrapMetaProperty(pProperty, init);
          this->_preInitialize = init;
        }
        else if (name == "PreinitByCenterOfGravity")
        {
          bool init;
          map::core::unwrapMetaProperty(pProperty, init);
          this->_useCenterOfGravity = init;
        }
        else
        {
          assert(false); //any other property name should have been excluded by the calling function.
        }

      };

      template < class TMovingImage, class TTargetImage,
      class TIdentificationPolicy,
      class TInterpolatorPolicy,
      class TMetricInitializationPolicy,
      class TOptimizerInitializationPolicy,
      class TTransformInitializationPolicy,
      class TInternalRegistrationMethod>
        void
        ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
        TInterpolatorPolicy,
        TMetricInitializationPolicy,
        TOptimizerInitializationPolicy,
        TTransformInitializationPolicy, TInternalRegistrationMethod>::
        prepInitializeTransformation()
      {
        Superclass::prepInitializeTransformation();

        if (this->_preInitialize)
        {
          this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize transform."));

          typedef ::itk::CenteredTransformInitializer<typename Superclass::ConcreteTransformType::TransformType, typename Superclass::TargetImageType, typename Superclass::MovingImageType>
            InitializerType;

          typename InitializerType::Pointer spInitializer = InitializerType::New();

          spInitializer->SetMovingImage(this->_spInternalMovingImage);
          spInitializer->SetFixedImage(this->_spInternalTargetImage);
          spInitializer->SetTransform(this->getConcreteTransformModel()->getConcreteTransform());

          if (this->_useCenterOfGravity)
          {
            this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize by moments."));
            spInitializer->MomentsOn();
          }
          else
          {
            this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize by image geometry."));
            spInitializer->GeometryOn();
          }

          spInitializer->InitializeTransform();
        }

        core::OStringStream os;

        os << "Preinitialized transform to: " <<
          this->getConcreteTransformModel()->getConcreteTransform()->GetParameters();
        //set the parameter of the transform model to the current transform parameters of the algorithm
        this->setCurrentTransformParameters(
          this->getConcreteTransformModel()->getConcreteTransform()->GetParameters());
        this->getInternalRegistrationMethod().SetInitialTransformParameters(
          this->getConcreteTransformModel()->getConcreteTransform()->GetParameters());

        this->InvokeEvent(events::AlgorithmEvent(this, os.str()));
      };


    }
  }
}

#endif