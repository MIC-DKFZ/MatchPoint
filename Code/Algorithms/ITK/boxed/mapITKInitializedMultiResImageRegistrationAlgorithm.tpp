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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/ITK/boxed/mapITKInitializedMultiResImageRegistrationAlgorithm.tpp $
*/


#ifndef __MAP_ITK_INITIALIZING_IMAGE_REGISTRATION_ALGORITHM_TPP
#define __MAP_ITK_INITIALIZING_IMAGE_REGISTRATION_ALGORITHM_TPP

#include "mapITKInitializedMultiResImageRegistrationAlgorithm.h"

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
			         typename TUIDPolicy,
			         class TInterpolatorPolicy,
			         class TPyramideInitializationPolicy,
			         class TMetricInitializationPolicy,
			         class TOptimizerInitializationPolicy,
			         class TTransformInitializationPolicy >
			ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                                 TInterpolatorPolicy,
			                                                 TPyramideInitializationPolicy,
			                                                 TMetricInitializationPolicy,
			                                                 TOptimizerInitializationPolicy,
			                                                 TTransformInitializationPolicy >::
			                                                 ITKInitializedMultiResImageRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy,
			         class TPyramideInitializationPolicy,
			         class TMetricInitializationPolicy,
			         class TOptimizerInitializationPolicy,
			         class TTransformInitializationPolicy >
			ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                                 TInterpolatorPolicy,
			                                                 TPyramideInitializationPolicy,
			                                                 TMetricInitializationPolicy,
			                                                 TOptimizerInitializationPolicy,
			                                                 TTransformInitializationPolicy >::
			                                                 ~ITKInitializedMultiResImageRegistrationAlgorithm()
			{
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy,
			         class TPyramideInitializationPolicy,
			         class TMetricInitializationPolicy,
			         class TOptimizerInitializationPolicy,
			         class TTransformInitializationPolicy >
			void
			ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                                 TInterpolatorPolicy,
			                                                 TPyramideInitializationPolicy,
			                                                 TMetricInitializationPolicy,
			                                                 TOptimizerInitializationPolicy,
			                                                 TTransformInitializationPolicy >::
			                                                 configureAlgorithm()
			{
				_preInitialize = false;
				_useCenterOfGravity = false;
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy,
			         class TPyramideInitializationPolicy,
			         class TMetricInitializationPolicy,
			         class TOptimizerInitializationPolicy,
			         class TTransformInitializationPolicy >
			void
			ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                                 TInterpolatorPolicy,
			                                                 TPyramideInitializationPolicy,
			                                                 TMetricInitializationPolicy,
			                                                 TOptimizerInitializationPolicy,
			                                                 TTransformInitializationPolicy >::
			                                                 compileInfos(MetaPropertyVectorType &infos) const
			{
#ifndef MAP_SEAL_ALGORITHMS
				infos.push_back(map::algorithm::MetaPropertyInfo::New("PreinitTransform", typeid(bool), true, true));
				infos.push_back(map::algorithm::MetaPropertyInfo::New("PreinitByCenterOfGravity", typeid(bool), true, true));
#endif
			};

			template < class TMovingImage, class TTargetImage,
			         typename TUIDPolicy,
			         class TInterpolatorPolicy,
			         class TPyramideInitializationPolicy,
			         class TMetricInitializationPolicy,
			         class TOptimizerInitializationPolicy,
			         class TTransformInitializationPolicy >
			typename ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			         TInterpolatorPolicy,
			         TPyramideInitializationPolicy,
			         TMetricInitializationPolicy,
			         TOptimizerInitializationPolicy,
			         TTransformInitializationPolicy >::MetaPropertyPointer
			         ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			         TInterpolatorPolicy,
			         TPyramideInitializationPolicy,
			         TMetricInitializationPolicy,
			         TOptimizerInitializationPolicy,
			         TTransformInitializationPolicy >::
			         doGetProperty(const MetaPropertyNameType &name) const
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
			         typename TUIDPolicy,
			         class TInterpolatorPolicy,
			         class TPyramideInitializationPolicy,
			         class TMetricInitializationPolicy,
			         class TOptimizerInitializationPolicy,
			         class TTransformInitializationPolicy >
			void
			ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                                 TInterpolatorPolicy,
			                                                 TPyramideInitializationPolicy,
			                                                 TMetricInitializationPolicy,
			                                                 TOptimizerInitializationPolicy,
			                                                 TTransformInitializationPolicy >::
			                                                 doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty)
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
			         typename TUIDPolicy,
			         class TInterpolatorPolicy,
			         class TPyramideInitializationPolicy,
			         class TMetricInitializationPolicy,
			         class TOptimizerInitializationPolicy,
			         class TTransformInitializationPolicy >
			void
			ITKInitializedMultiResImageRegistrationAlgorithm < TMovingImage, TTargetImage, TUIDPolicy,
			                                                 TInterpolatorPolicy,
			                                                 TPyramideInitializationPolicy,
			                                                 TMetricInitializationPolicy,
			                                                 TOptimizerInitializationPolicy,
			                                                 TTransformInitializationPolicy >::
			                                                 prepInitializeTransformation()
			{
				Superclass::prepInitializeTransformation();

				if (this->_preInitialize)
				{
					this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize transform."));

					typedef ::itk::CenteredTransformInitializer<typename Superclass::ConcreteTransformType::TransformType, typename Superclass::TargetImageType, typename Superclass::MovingImageType> InitializerType;

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

				typename Superclass::ConcreteTransformType::MatrixType matrix;
				typename Superclass::ConcreteTransformType::OutputVectorType offset;

				this->getConcreteTransformModel()->getAffineMatrixDecomposition(matrix, offset);

				core::OStringStream os;

				os << "Preinitialized transform to: " << this->getConcreteTransformModel()->getConcreteTransform()->GetParameters();
				//set the parameter of the transform model to the current transform parameters of the algorithm
				this->setCurrentTransformParameters(this->getConcreteTransformModel()->getConcreteTransform()->GetParameters());
				this->getInternalRegistrationMethod().SetInitialTransformParameters(this->getConcreteTransformModel()->getConcreteTransform()->GetParameters());

				this->InvokeEvent(events::AlgorithmEvent(this, os.str()));
			};


		}
	}
}

#endif
