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


#ifndef __ITK_RIGID_3D_MATTESMI_HEADNECK_REGISTRATION_ALGORITHM_TPP
#define __ITK_RIGID_3D_MATTESMI_HEADNECK_REGISTRATION_ALGORITHM_TPP

#include "itkRegionOfInterestImageFilter.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
			MultiModalRigidHeadNeckRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			MultiModalRigidHeadNeckRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
			MultiModalRigidHeadNeckRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			~MultiModalRigidHeadNeckRegistrationAlgorithm()
			{
			};

			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
			void
			MultiModalRigidHeadNeckRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			configureAlgorithm()
			{
			  Superclass::configureAlgorithm();

			  this->setResolutionLevels(3);
			  this->_preInitialize = true;
			  this->_useCenterOfGravity = false;

			  //optimizer
              typename Superclass::ConcreteOptimizerType::ScalesType scales(6);
			  scales[0] = 10.0;
			  scales[1] = 10.0;
			  scales[2] = 10.0;
			  scales[3] = 1.0 / 10000;
			  scales[4] = 1.0 / 10000;
			  scales[5] = 1.0 / 10000;

			  this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetScales(scales);
			  this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(3.00);
			  this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(0.5);
			  this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetNumberOfIterations(200);
			  this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetRelaxationFactor(0.8);
			  this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetGradientMagnitudeTolerance(1e-4);

			  //metric
			  this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfHistogramBins(30);
			  this->getConcreteMetricControl()->getConcreteMetric()->SetUseAllPixels(true);
			  this->getConcreteMetricControl()->getConcreteMetric()->ReinitializeSeed();
			  this->getConcreteMetricControl()->getConcreteMetric()->UseExplicitPDFDerivativesOn();
			}
			
			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
			void
			MultiModalRigidHeadNeckRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			doInterLevelSetup(){
                Superclass::doInterLevelSetup();

				if (this->getCurrentLevel() != 0)
				{
                    this->getConcreteMetricControl()->getConcreteMetric()->SetUseAllPixels(false);

                    typename Superclass::OptimizerBaseType::SVNLOptimizerBaseType::ScalesType scales(6);
					scales[0] = 1.0;
					scales[1] = 1.0;
					scales[2] = 1.0;
					scales[3] = 1.0 / 1000;
					scales[4] = 1.0 / 1000;
					scales[5] = 1.0 / 1000;

                    this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetScales(scales);

					unsigned int nrOfSmpl = ::itk::Math::Round<unsigned int, double>
											(this->getMovingImage()->GetLargestPossibleRegion().GetNumberOfPixels() * 0.15);

                    this->getConcreteMetricControl()->getConcreteMetric()->SetNumberOfSpatialSamples(nrOfSmpl);

					//optimizer adjustment
                    this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMaximumStepLength(
                        this->getConcreteOptimizerControl()->getConcreteOptimizer()->GetCurrentStepLength() * 2.0);
                    this->getConcreteOptimizerControl()->getConcreteOptimizer()->SetMinimumStepLength(
                        this->getConcreteOptimizerControl()->getConcreteOptimizer()->GetMinimumStepLength() * 0.5);
				}
			}
			
			template < class TImageType, class TIdentificationPolicy, class TInterpolatorPolicy, class TPyramideInitializationPolicy>
			void
			MultiModalRigidHeadNeckRegistrationAlgorithm<TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>::
			prepInitializeTransformation(){
				Superclass::Superclass::prepInitializeTransformation();

				if (this->_preInitialize)
				{
					this->InvokeEvent(events::AlgorithmEvent(this, "Preinitialize transform."));

					typedef ::itk::CenteredTransformInitializer<typename Superclass::ConcreteTransformType, typename Superclass::TargetImageType, typename Superclass::MovingImageType>
					InitializerType;
					typedef ::itk::RegionOfInterestImageFilter<typename Superclass::TargetImageType, typename Superclass::TargetImageType>
					ROIFilterType;

                    typename InitializerType::Pointer spInitializer = InitializerType::New();

                    typename ROIFilterType::Pointer spROIFilter = ROIFilterType::New();
					spROIFilter->SetInput(this->getInternalTargetImage());
                    typename ROIFilterType::RegionType region = this->getInternalTargetImage()->GetLargestPossibleRegion();
                    typename ROIFilterType::RegionType::SizeValueType zSize = region.GetSize(2);
					region.SetIndex(2, zSize / 3);
					region.SetSize(2, 2 * zSize / 3);
					spROIFilter->SetRegionOfInterest(region);

					core::OStringStream stream;
					stream << region;
					this->InvokeEvent(events::AlgorithmEvent(this,
										"Prepare target region of interest. region: " + stream.str()));

					spROIFilter->Update();

          spInitializer->SetMovingImage(this->getInternalMovingImage());
					spInitializer->SetFixedImage(spROIFilter->GetOutput());
					spInitializer->SetTransform(this->getConcreteTransformModel());

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

				os << "Preinitialized transform to: " << this->getConcreteTransformModel()->GetParameters();
				//set the parameter of the transform model to the current transform parameters of the algorithm
				this->setCurrentTransformParameters(
					this->getConcreteTransformModel()->GetParameters());
				this->getInternalRegistrationMethod().SetInitialTransformParameters(
					this->getConcreteTransformModel()->GetParameters());

				this->InvokeEvent(events::AlgorithmEvent(this, os.str()));
			}


		} // end namespace itk
	} // end namespace algorithm
} // end namespace map

#endif
