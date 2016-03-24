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
			           class TInternalRegistrationMethod >
			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
			                                         TInterpolatorPolicy,
			                                         TMetricInitializationPolicy,
			                                         TOptimizerInitializationPolicy,
			                                         TTransformInitializationPolicy, TInternalRegistrationMethod >::
			                                         ITKInitializedImageRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			           class TIdentificationPolicy,
			           class TInterpolatorPolicy,
			           class TMetricInitializationPolicy,
			           class TOptimizerInitializationPolicy,
			           class TTransformInitializationPolicy,
			           class TInternalRegistrationMethod >
			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
			                                         TInterpolatorPolicy,
			                                         TMetricInitializationPolicy,
			                                         TOptimizerInitializationPolicy,
			                                         TTransformInitializationPolicy, TInternalRegistrationMethod >::
			                                         ~ITKInitializedImageRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			           class TIdentificationPolicy,
			           class TInterpolatorPolicy,
			           class TMetricInitializationPolicy,
			           class TOptimizerInitializationPolicy,
			           class TTransformInitializationPolicy,
			           class TInternalRegistrationMethod >
			void
			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
			                                         TInterpolatorPolicy,
			                                         TMetricInitializationPolicy,
			                                         TOptimizerInitializationPolicy,
			                                         TTransformInitializationPolicy, TInternalRegistrationMethod >::
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
			           class TInternalRegistrationMethod >
			void
			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
			                                         TInterpolatorPolicy,
			                                         TMetricInitializationPolicy,
			                                         TOptimizerInitializationPolicy,
			                                         TTransformInitializationPolicy, TInternalRegistrationMethod >::
			                                         compileInfos(MetaPropertyVectorType& infos) const
			{
				Superclass::compileInfos(infos);

				#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("PreinitTransform", typeid(bool), true,
				                true));
				infos.push_back(::map::algorithm::MetaPropertyInfo::New("PreinitByCenterOfGravity", typeid(bool),
				                true, true));
				#endif
			};

			template < class TMovingImage, class TTargetImage,
			           class TIdentificationPolicy,
			           class TInterpolatorPolicy,
			           class TMetricInitializationPolicy,
			           class TOptimizerInitializationPolicy,
			           class TTransformInitializationPolicy,
			           class TInternalRegistrationMethod >
			typename 			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage,
			                    TIdentificationPolicy,
			                    TInterpolatorPolicy,
			                    TMetricInitializationPolicy,
			                    TOptimizerInitializationPolicy,
			                    TTransformInitializationPolicy, TInternalRegistrationMethod >::MetaPropertyPointer
			                    ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
			                    TInterpolatorPolicy,
			                    TMetricInitializationPolicy,
			                    TOptimizerInitializationPolicy,
			                    TTransformInitializationPolicy, TInternalRegistrationMethod >::
			                    doGetProperty(const MetaPropertyNameType& name) const
			{
				MetaPropertyPointer spResult;

				if (name == "PreinitTransform")
				{
					spResult = ::map::core::MetaProperty<bool>::New(this->_preInitialize);
				}
				else if (name == "PreinitByCenterOfGravity")
				{
					spResult = ::map::core::MetaProperty<bool>::New(this->_useCenterOfGravity);
				}
				else
				{
					spResult = Superclass::doGetProperty(name);
				}

				assert(spResult.IsNotNull()); //any other property name should have been excluded by the calling function.

				return spResult;
			};

			template < class TMovingImage, class TTargetImage,
			           class TIdentificationPolicy,
			           class TInterpolatorPolicy,
			           class TMetricInitializationPolicy,
			           class TOptimizerInitializationPolicy,
			           class TTransformInitializationPolicy,
			           class TInternalRegistrationMethod >
			void
			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
			                                         TInterpolatorPolicy,
			                                         TMetricInitializationPolicy,
			                                         TOptimizerInitializationPolicy,
			                                         TTransformInitializationPolicy, TInternalRegistrationMethod >::
			                                         doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty)
			{
				if (name == "PreinitTransform")
				{
					bool init;
					::map::core::unwrapMetaProperty(pProperty, init);
					this->_preInitialize = init;
				}
				else if (name == "PreinitByCenterOfGravity")
				{
					bool init;
					::map::core::unwrapMetaProperty(pProperty, init);
					this->_useCenterOfGravity = init;
				}
				else
				{
					Superclass::doSetProperty(name, pProperty);
				}
			};

			template < class TMovingImage, class TTargetImage,
			           class TIdentificationPolicy,
			           class TInterpolatorPolicy,
			           class TMetricInitializationPolicy,
			           class TOptimizerInitializationPolicy,
			           class TTransformInitializationPolicy,
			           class TInternalRegistrationMethod >
			void
			ITKInitializedImageRegistrationAlgorithm < TMovingImage, TTargetImage, TIdentificationPolicy,
			                                         TInterpolatorPolicy,
			                                         TMetricInitializationPolicy,
			                                         TOptimizerInitializationPolicy,
			                                         TTransformInitializationPolicy, TInternalRegistrationMethod >::
			                                         prepInitializeTransformation()
			{
				Superclass::prepInitializeTransformation();

				if (this->_preInitialize)
				{
					this->InvokeEvent(::map::events::AlgorithmEvent(this, "Preinitialize transform."));

					typedef ::itk::CenteredTransformInitializer<typename Superclass::ConcreteTransformType, typename Superclass::TargetImageType, typename Superclass::MovingImageType>
					InitializerType;

					typename InitializerType::Pointer spInitializer = InitializerType::New();

					spInitializer->SetMovingImage(this->getInternalMovingImage());
					spInitializer->SetFixedImage(this->getInternalTargetImage());
					spInitializer->SetTransform(this->getConcreteTransformModel());

					if (this->_useCenterOfGravity)
					{
						this->InvokeEvent(::map::events::AlgorithmEvent(this, "Preinitialize by moments."));
						spInitializer->MomentsOn();
					}
					else
					{
						this->InvokeEvent(::map::events::AlgorithmEvent(this, "Preinitialize by image geometry."));
						spInitializer->GeometryOn();
					}

					spInitializer->InitializeTransform();
				}

				::map::core::OStringStream os;

				os << "Preinitialized transform to: " <<
				   this->getConcreteTransformModel()->GetParameters();
				//set the parameter of the transform model to the current transform parameters of the algorithm
				this->setCurrentTransformParameters(this->getConcreteTransformModel()->GetParameters());
				this->getInternalRegistrationMethod().SetInitialTransformParameters( this->getConcreteTransformModel()->GetParameters());

				this->InvokeEvent(::map::events::AlgorithmEvent(this, os.str()));
			};


		}
	}
}

#endif
